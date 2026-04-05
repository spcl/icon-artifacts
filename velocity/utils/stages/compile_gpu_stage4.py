import dace
from dace.transformation.passes import InlineSDFGs
from dace.transformation.dataflow import MapCollapse, MapFusion
import utils.stages.common as common
import utils.config as config
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.map_state_fission import MapStateFission
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
import argparse
from utils.propagate_if_cond import propagate_if_cond
from utils.demote_symbol_to_scalar import demote_symbol_to_scalar
import os
from utils.offload_cpu import offload_cpu
from dace.properties import CodeBlock
import utils.stages.common as common
from utils.find import find_node_by_name
from utils.move_scalar_to_array import _tmp_difcoef
from utils.move_transients_to_top_level import move_transients_to_top_level
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.merge_maps import merge_maps_in_sdfg
from utils.change_array_dtypes import change_array_dtypes
from dace.transformation.passes.constant_propagation import ConstantPropagation
STAGE_ID = 4
def merge_its29_30_and_its31(sdfg: dace.SDFG):
    mapentry1, state1 = {
        (n, g) for n, g in sdfg.all_nodes_recursive() if isinstance(n, dace.nodes.MapEntry)
        and "_for_it_29" in n.map.params and "_for_it_30" in n.map.params
    }.pop()
    mapentry2, state2 = {
        (n, g) for n, g in sdfg.all_nodes_recursive() if isinstance(n, dace.nodes.MapEntry)
        and "_for_it_31" in n.map.params
    }.pop()

    # Extend nlev range to be 1 more
    mrange = mapentry1.map.range
    mrange1 = mapentry1.map.range[1]
    mrange = dace.subsets.Range([(1, 91, 1), (mrange1[0], mrange1[1], mrange1[2])])
    mapentry1.map.range = mrange

    # Find tasklet and change tasklet code
    mapexit1 = state1.exit_node(mapentry1)
    mapexit2 = state2.exit_node(mapentry2)
    tasklets = list(state1.all_nodes_between(mapentry1, mapexit1))
    assert len(tasklets) == 1 and isinstance(tasklets[0], dace.nodes.Tasklet)
    tasklet: dace.nodes.Tasklet = tasklets[0]
    
    out_con = next(iter(tasklet.out_connectors.keys()))
    in_con = next(iter(tasklet.in_connectors.keys()))

    code = f"{out_con} = (_for_it_29 == 91)? 0.0: {in_con};"

    tasklet.code = CodeBlock(
        code, language=dace.dtypes.Language.CPP,
    )

    for n in state2.all_nodes_between(mapentry2, mapexit2):
        state2.remove_node(n)
    state2.remove_node(mapentry2)
    state2.remove_node(mapexit2)

    sdfg.validate()

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    sdfg.validate()
    sdfg.simplify(skip=["StateFusion"])
    sdfg.validate()

    prune_unused_inputs_outputs(sdfg)

    InlineSDFGs().apply_pass(sdfg, {})
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapFusion)
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.NestedSDFG):
            if isinstance(n, dace.nodes.NestedSDFG):
                k = n.sdfg.apply_transformations_repeated(MapFusion, permissive=True)
                if config.verbose:
                    print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")

    if config.verbose:
        print(f"Applied MapFusion {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    sdfg.simplify(skip=["StateFusion"])
    prune_unused_inputs_outputs(sdfg)
    InlineSDFGs().apply_pass(sdfg, {})
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    sdfg.simplify(skip=["StateFusion"])
    # I saw trurthy ifs, propagate those conditions and try to fuse states agian
    # TODO: Crashes sometimes
    propagate_if_cond(sdfg, sdfg, None, None, True)
    # Prevents some transformations from being applied
    # This is not a symbol anymore (? - it was before why)
    # TODO: Check if this is necessary, if so fix
    assert "tmp_call_18" in sdfg.symbols
    if "tmp_call_18" in sdfg.symbols:
        demote_symbol_to_scalar(sdfg, "tmp_call_18")

    sdfg.validate()
    sdfg.simplify(skip=["StateFusion"])
    sdfg.validate()
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["z_w_con_c", "z_w_concorr_mc", "levmask", "cfl_clipping"],
        no_dim_change=True,
        offset=-1,
        upper_bounds={
            "z_w_concorr_mc": "tmp_struct_symbol_5",
            "z_w_con_c": "tmp_struct_symbol_5",
            "levmask": "tmp_struct_symbol_5",
            "cfl_clipping": "tmp_struct_symbol_5",
        },
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["z_v_grad_w", "z_ekinh", "zeta", "z_w_v", "z_w_con_c_full"],
        no_dim_change=True,
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        upper_bounds={
            "maxvcfl_arr": "tmp_struct_symbol_11"
        },
        only=["maxvcfl_arr"],
        no_dim_change=False,
        offset=-1,
        set_zero=True,
    )
    move_transients_to_top_level(
        root=sdfg,
        ilifetime=dace.dtypes.AllocationLifetime.SDFG,
        only=["out_val_0"],
        no_dim_change=True,
    )
    if "difcoef" in sdfg.arrays:
        _tmp_difcoef(sdfg)
    sdfg.validate()

    merge_maps_in_sdfg(sdfg)
    merge_its29_30_and_its31(sdfg)
    sdfg.validate()

    remove_unused_inconnectors_from_nestedsdfg(sdfg)
    sdfg.simplify()
    sdfg.validate()


    sdfg.validate()

    ConstantPropagation().apply_pass(sdfg, {})
    sdfg.simplify()
    sdfg.validate()
    return sdfg

import sys

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--unpermuted', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--permutations', type=str, default=None,
                      help='Comma-separated config names from CPU_PERMUTE_CONFIGS (default: single_map)')
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
            offload_cpu(sdfg)
            sdfg.validate()
            sdfg = optimization_action(sdfg)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)
    if args.compile:
        from sc26_layout.extract_kernel import permute_single_map
        from sc26_layout.extract_gpu_kernel import CPU_PERMUTE_CONFIGS

        if args.permutations:
            config_names = [c.strip() for c in args.permutations.split(",")]
        else:
            config_names = []

        for config_name in config_names:
            if config_name not in CPU_PERMUTE_CONFIGS:
                print(f"Unknown config: {config_name}. Available: {list(CPU_PERMUTE_CONFIGS.keys())}")
                sys.exit(1)

            for shuffle_map in [True, False]:
                shuffle_label = "shuffled" if shuffle_map else "unshuffled"
                print(f"=== Compiling permuted config: {config_name} ({shuffle_label}) ===")
                sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
                nsdfgs = {}
                for name, sdfg in sdfgs.items():
                    sdfg = permute_single_map(sdfg, config_name=config_name, shuffle_map=shuffle_map)
                    sdfg.validate()
                    offload_cpu(sdfg)
                    sdfg.validate()
                    nsdfgs[name] = sdfg
                suffix = f"_permuted_{config_name}_{shuffle_label}"
                BEVERIN = os.getenv("BEVERIN", "0") == "1"
                common.compile_action(STAGE_ID, nsdfgs, False, None, False,
                    name_suffix=suffix, main_name="main_per.cu", tblock_dim="32,4,1",
                    stage_suffix=suffix)

    if args.unpermuted:
        from sc26_layout.extract_kernel import add_timer_single_map

        print(f"=== Compiling unpermuted baseline ===")
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            sdfg = add_timer_single_map(sdfg)
            sdfg.validate()
            offload_cpu(sdfg)
            sdfg.validate()
            nsdfgs[name] = sdfg
        common.compile_action(STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_unpermuted", main_name="main_per.cu", tblock_dim="32,4,1",
            stage_suffix="_unpermuted")

if __name__ == "__main__":
    main()
