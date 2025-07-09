import argparse

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.to_gpu import ToGPU
from dace import nodes
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.state import SDFGState

import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import tile_kernels
from utils.reshape_kernels import reshape_kernels, reshape_kernels_w_coarsening
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
from utils.decrease_bitwidth_of_const_arrays import decrease_bitwidth_of_const_arrays

STAGE_ID = 8
import os

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    print("Array values that can be lowered: {\n" + "\n".join(
        sorted(
            [f'"{array_name}",' for array_name, array in sdfg.arrays.items() if
            ((array.dtype == dace.int32 or array.dtype == dace.int64) and isinstance(array, dace.data.Array) and not isinstance(array, dace.data.View))
            ]
            )
        ) + "}\n"
    )
    do_reduce_bitwidth = os.getenv('_REDUCE_BITWIDTH_TRANSFORMATION', '0').lower() in ('1', 'true', 'yes')
    if do_reduce_bitwidth:
        sdfg = decrease_bitwidth_of_const_arrays(sdfg,
                                        array_names={
                                            "gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask",
                                            "gpu___CG_p_patch__CG_cells__m_edge_blk",
                                            "gpu___CG_p_patch__CG_cells__m_edge_idx",
                                            "gpu___CG_p_patch__CG_cells__m_end_block",
                                            "gpu___CG_p_patch__CG_cells__m_end_index",
                                            "gpu___CG_p_patch__CG_cells__m_neighbor_blk",
                                            "gpu___CG_p_patch__CG_cells__m_neighbor_idx",
                                            "gpu___CG_p_patch__CG_cells__m_start_block",
                                            "gpu___CG_p_patch__CG_cells__m_start_index",
                                            "gpu___CG_p_patch__CG_edges__m_cell_blk",
                                            "gpu___CG_p_patch__CG_edges__m_cell_idx",
                                            "gpu___CG_p_patch__CG_edges__m_end_block",
                                            "gpu___CG_p_patch__CG_edges__m_end_index",
                                            "gpu___CG_p_patch__CG_edges__m_quad_blk",
                                            "gpu___CG_p_patch__CG_edges__m_quad_idx",
                                            "gpu___CG_p_patch__CG_edges__m_start_block",
                                            "gpu___CG_p_patch__CG_edges__m_start_index",
                                            "gpu___CG_p_patch__CG_edges__m_vertex_blk",
                                            "gpu___CG_p_patch__CG_edges__m_vertex_idx",
                                            "gpu___CG_p_patch__CG_verts__m_cell_blk",
                                            "gpu___CG_p_patch__CG_verts__m_cell_idx",
                                            "gpu___CG_p_patch__CG_verts__m_edge_blk",
                                            "gpu___CG_p_patch__CG_verts__m_edge_idx",
                                            "gpu___CG_p_patch__CG_verts__m_end_block",
                                            "gpu___CG_p_patch__CG_verts__m_end_index",
                                            "gpu___CG_p_patch__CG_verts__m_start_block",
                                            "gpu___CG_p_patch__CG_verts__m_start_index",
                                        })
    int64_to_int32(sdfg)
    # start_index and end_index are between [1, nproma] -> ~20k in our data, ~200k in some other cases int16 is -32768, 32767
    # start_block and end_blocks are between [0, nblks] -> usually 1 or 2 as we pass nblocks_c for the science config
    # Force start and end blks to int8?
    # TODO: force start_block and end_block to int8


    # TODO: GPU read-write has unit size of 32-bits, uint8_t won't help unless we tile
    # Assigning a warp to the column is not a very good idea
    # reshape_kernels(sdfg, True)
    # Must be individualized for each kernel
    do_tile = os.getenv('_TILE', '0').lower() in ('1', 'true', 'yes')
    if do_tile:
        x_coarsening = int(os.environ.get("X_COARSENING", 1))
        y_coarsening = int(os.environ.get("Y_COARSENING", 1))
        x_block_size = int(os.environ.get("X_BLOCK_SIZE", 256))
        y_block_size = int(os.environ.get("Y_BLOCK_SIZE", 1))
        y_unroll_factor = int(os.environ.get("Y_UNROLL_FACTOR", 1))
        #reshape_kernels(sdfg)
        reshape_kernels_w_coarsening(sdfg,
                                    x_coarsening=x_coarsening,
                                    y_coarsening=y_coarsening,
                                    x_block_size=x_block_size,
                                    y_block_size=y_block_size,
                                    unroll_x=True,
                                    unroll_x_factor=None,
                                    unroll_y=True,
                                    unroll_y_factor=y_unroll_factor,)
    #tile_kernels(sdfg)
    #sdfg.simplify()
    sdfg.validate()
    return sdfg


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=False)
    args = argp.parse_args()
    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True

    names = common.sdfg_names()

    if args.optimize:
        for name in names:
            infile = common.stage_input(name, STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)

            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")

            sdfg = dace.SDFG.from_file(infile)
            sdfg.name = name
            sdfg.validate()

            sdfg = optimization_action(sdfg)

            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)

    if args.compile:
        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        common.compile_action(STAGE_ID, sdfgs, False, None, False)

if __name__ == "__main__":
    main()
