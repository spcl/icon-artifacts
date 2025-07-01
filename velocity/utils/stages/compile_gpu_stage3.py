import dace
from dace.transformation.interstate import ConditionFusion
from dace.transformation.passes import InlineSDFGs
from dace.transformation.dataflow import MapCollapse, MapFusion
import utils.stages.common as common
import utils.config as config
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.map_state_fission import MapStateFission
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs, prune_unused_inputs_outputs_recursive
from utils.preprocess_tough_nut import preprocess_tough_nut
import argparse

STAGE_ID = 3


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})

    prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
    prune_unused_inputs_outputs_recursive(sdfg)
    sdfg.validate()

    sdfg.apply_transformations_repeated(ConditionFusion)
    prune_unused_inputs_outputs(sdfg)
    InlineSDFGs().apply_pass(sdfg, {})

    k = sdfg.apply_transformations_repeated(MapCollapse)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapFusion)
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.NestedSDFG):
            if isinstance(n, dace.nodes.NestedSDFG):
                k = n.sdfg.apply_transformations_repeated(MapFusion)
                if config.verbose:
                    print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")
    if config.verbose:
        print(f"Applied MapFusion {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapCollapse)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    sdfg.simplify(skip=["StateFusion"])
    prune_unused_inputs_outputs(sdfg)
    InlineSDFGs().apply_pass(sdfg, {})
    k = sdfg.apply_transformations_repeated(MapCollapse)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
    prune_unused_inputs_outputs_recursive(sdfg)
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
