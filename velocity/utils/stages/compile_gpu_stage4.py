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
STAGE_ID = 4


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
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            from sc26_layout.extract_kernel import permute_single_map
            sdfg = permute_single_map(sdfg, True)
            sdfg.validate()
            nsdfgs[name] = sdfg

        common.compile_action(STAGE_ID, nsdfgs, False, None, False, name_suffix="_permuted_single_map", main_name="main_per.cu")

        import shutil
        from pathlib import Path

        base_dir = Path(__file__).resolve().parent

        src = base_dir / "../../codegen/stage4"
        dst = base_dir / "../../codegen/stage4_permuted"

        shutil.copytree(src, dst, dirs_exist_ok=True)


        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            from sc26_layout.extract_kernel import add_timer_single_map
            sdfg = add_timer_single_map(sdfg, True)
            sdfg.validate()
            nsdfgs[name] = sdfg

        common.compile_action(STAGE_ID, nsdfgs, False, None, False, name_suffix="_unpermuted", main_name="main_per.cu")

        #sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        #common.compile_action(STAGE_ID, sdfgs, False, None, False)

if __name__ == "__main__":
    main()
