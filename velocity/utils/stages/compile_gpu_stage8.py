import argparse
import os
import sys
from typing import List

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.fusion_inline import InlineSDFGs
from dace.transformation.passes.to_gpu import ToGPU
from dace import nodes
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.state import CodeBlock, SDFGState

import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import tile_kernels
from utils.reshape_kernels import reshape_kernels, reshape_kernels_w_coarsening
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
from utils.decrease_bitwidth_of_const_arrays import decrease_bitwidth_of_const_arrays, force_decrease_bitwidth_of_nblk_arrays
from utils.profiling_patches import insert_timers_for_profiling, insert_synchronization_for_profiling, insert_event_timers_for_profiling
from utils.assignment_and_copy_kernel_to_memset_and_memcpy import AssignmentAndCopyKernelToMemsetAndMemcpy
from utils.create_profile_sdfg import create_profile_sdfg

STAGE_ID = 8
BEVERIN = os.getenv("BEVERIN", "0") == "1"
_TBLOCK_DIM = "32,4,1" if BEVERIN else "32,16,1"


def get_used_and_const_arrays(sdfg: dace.SDFG):
    permute_in_states      = {s for s in sdfg.all_states() if s.label == "permute_in"}
    permute_out_states     = {s for s in sdfg.all_states() if s.label == "permute_out"}
    entry_interface_states = {s for s in sdfg.all_states() if s.label == "entry_interface"}
    exit_interface_states  = {
        s for s in sdfg.all_states()
        if s.label == "block" and "deflatten" in {n.label for n in s.nodes()}
    }
    assert len(entry_interface_states) == 1
    assert len(exit_interface_states)  == 1

    states = (permute_in_states | permute_out_states
              | entry_interface_states | exit_interface_states)
    all_read_arrs, all_write_arrs = set(), set()

    for s in sdfg.all_states():
        if s in states:
            continue
        read_arrs, write_arrs = s.read_and_write_sets()
        all_read_arrs.update(read_arrs)
        all_write_arrs.update(write_arrs)

    for e in sdfg.all_interstate_edges():
        for k, v in e.data.assignments.items():
            syms = dace.symbolic.symbols_in_code(v, potential_symbols=set(sdfg.arrays.keys()))
            all_read_arrs.update(syms)

    print("All read arrays:\n{")
    for arr in sorted(all_read_arrs):
        print(f'"{arr}",')
    print("}\n")
    print("All written arrays:\n{")
    for arr in sorted(all_write_arrs):
        print(f'"{arr}",')
    print("}\n")


def optimization_action(sdfg: dace.SDFG) -> dace.SDFG:
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    gpu_levmask_desc = sdfg.arrays.get("gpu_levmask")
    print("gpu_levmask shape:", gpu_levmask_desc.shape,
          "strides:", gpu_levmask_desc.strides)

    do_reduce_bitwidth = os.getenv('_REDUCE_BITWIDTH_TRANSFORMATION', '0').lower() in ('1', 'true', 'yes')
    if do_reduce_bitwidth:
        sdfg = decrease_bitwidth_of_const_arrays(
            sdfg,
            array_names={
                "gpu___CG_p_patch__CG_cells__m_edge_idx",
                "gpu___CG_p_patch__CG_cells__m_neighbor_idx",
                "gpu___CG_p_patch__CG_edges__m_cell_idx",
                "gpu___CG_p_patch__CG_edges__m_quad_idx",
                "gpu___CG_p_patch__CG_edges__m_vertex_idx",
                "gpu___CG_p_patch__CG_verts__m_cell_idx",
                "gpu___CG_p_patch__CG_verts__m_edge_idx",
            },
            assume_can_lower=False,
            nproma_name="__CG_global_data__m_nproma",
        )
        sdfg = force_decrease_bitwidth_of_nblk_arrays(
            sdfg,
            multi_val_array_names={
                "gpu___CG_p_patch__CG_cells__m_edge_blk",
                "gpu___CG_p_patch__CG_edges__m_quad_blk",
                "gpu___CG_p_patch__CG_edges__m_neighbor_blk",
                "gpu___CG_p_patch__CG_verts__m_edge_blk",
            },
            single_val_array_names={
                "gpu___CG_p_patch__CG_cells__m_neighbor_blk",
                "gpu___CG_p_patch__CG_edges__m_cell_blk",
                "gpu___CG_p_patch__CG_edges__m_vertex_blk",
                "gpu___CG_p_patch__CG_verts__m_cell_blk",
                "gpu___CG_p_patch__CG_edges__m_neighbor_blk",
            },
        )

    int64_to_int32(sdfg)

    do_tile = os.getenv('_TILE', '0').lower() in ('1', 'true', 'yes')
    if do_tile:
        x_coarsening  = int(os.environ.get("X_COARSENING",  1))
        y_coarsening  = int(os.environ.get("Y_COARSENING",  1))
        x_block_size  = int(os.environ.get("X_BLOCK_SIZE",  256))
        y_block_size  = int(os.environ.get("Y_BLOCK_SIZE",  1))
        y_unroll_factor = int(os.environ.get("Y_UNROLL_FACTOR", 1))
        reshape_kernels_w_coarsening(
            sdfg,
            x_coarsening=x_coarsening,
            y_coarsening=y_coarsening,
            x_block_size=x_block_size,
            y_block_size=y_block_size,
            unroll_x=True,
            unroll_x_factor=None,
            unroll_y=True,
            unroll_y_factor=y_unroll_factor,
        )

    # Permutaiton adds that
    #insert_synchronization_for_profiling(sdfg)
    #insert_timers_for_profiling(sdfg)
    sdfg.validate()

    do_profile = os.getenv('_PROFILE', '0').lower() in ('1', 'true', 'yes')
    if do_profile:
        create_profile_sdfg(sdfg)

    return sdfg

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize',     action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile',      action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--unpermuted',   action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--permutations', type=str, default=None,
                      help='Comma-separated config names from PERMUTE_CONFIGS')
    args = argp.parse_args()

    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True

    names = common.sdfg_names()

    # ------------------------------------------------------------------
    # Optimize
    # ------------------------------------------------------------------
    if args.optimize:
        for name in names:
            infile  = common.stage_input(name,  STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)
            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")
            sdfg = dace.SDFG.from_file(infile)
            sdfg.name = name
            sdfg.validate()
            sdfg = optimization_action(sdfg)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)

    do_reduce_bitwidth = os.getenv('_REDUCE_BITWIDTH_TRANSFORMATION', '0').lower() in ('1', 'true', 'yes')

    # ------------------------------------------------------------------
    # Compile unpermuted baseline
    # ------------------------------------------------------------------
    if args.unpermuted:
        from sc26_layout.permute_stage8 import add_timers, add_timers_after_lowering, add_symbols

        print(f"=== Compiling unpermuted baseline ===")
        sdfgs = {
            name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID))
            for name in names
        }
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            if not do_reduce_bitwidth:
                add_timers(sdfg)
            else:
                add_timers_after_lowering(sdfg)
            # insert_synchronization_for_profiling(sdfg)
            sdfg.validate()
            add_symbols(sdfg)
            nsdfgs[name] = sdfg

        common.compile_action(
            STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_unpermuted",
            main_name="main_per.cu",
            tblock_dim=_TBLOCK_DIM,
            stage_suffix="_unpermuted",
        )
        return

    # ------------------------------------------------------------------
    # Compile permuted variants (both shuffled and unshuffled)
    # ------------------------------------------------------------------
    if args.compile:
        from sc26_layout.permute_stage8 import (
            PERMUTE_CONFIGS,
            permute_sdfg,
            permute_sdfg_after_lowering,
        )

        if args.permutations:
            config_names = [c.strip() for c in args.permutations.split(",")]
        else:
            config_names = ["cv1_ch1_f1_s1_n201"]   # default: all-groups config



        for config_name in config_names:
            if config_name not in PERMUTE_CONFIGS:
                print(f"Unknown config: {config_name}. "
                      f"Available: {list(PERMUTE_CONFIGS.keys())}", file=sys.stderr)
                sys.exit(1)

            for shuffle_map in [True, False]:
                shuffle_label = "ms" if shuffle_map else "mu"
                print(f"=== Compiling config: {config_name} ({shuffle_label}) ===")

                sdfgs = {
                    name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID))
                    for name in names
                }
                nsdfgs = {}
                for name, sdfg in sdfgs.items():
                    if not do_reduce_bitwidth:
                        sdfg = permute_sdfg(
                            sdfg,
                            config_name=config_name,
                            shuffle_map=shuffle_map,
                        )
                    else:
                        #sdfg = permute_sdfg_after_lowering(
                        sdfg = permute_sdfg_after_lowering(
                            sdfg,
                            config_name=config_name,
                            shuffle_map=shuffle_map,
                        )
                    # insert_synchronization_for_profiling(sdfg)
                    sdfg.validate()
                    sdfg.validate()
                    nsdfgs[name] = sdfg

                suffix = f"_permuted_{config_name}_{shuffle_label}"
                common.compile_action(
                    STAGE_ID, nsdfgs, False, None, False,
                    name_suffix=suffix,
                    main_name="main_per.cu",
                    tblock_dim=_TBLOCK_DIM,
                    stage_suffix=suffix,
                )




if __name__ == "__main__":
    main()