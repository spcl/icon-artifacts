import dace
from dace.transformation.interstate import LoopToMap
from dace.transformation.dataflow import MapCollapse
from utils.count import count_symbols_use_defs
import utils.stages.common as common
import utils.config as config
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
import argparse

STAGE_ID = 2


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    sdfg.apply_transformations_repeated(LoopToMap, permissive=True)
    count_symbols_use_defs(sdfg, verbose=config.verbose, use_assert=True)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
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

        # TODO: THE REST OF THE COMMON COMPILE ACTION SHOULD BE ABSTRACTED AWAY.
        for name, g in sdfgs.items():
            g.build_folder = f"{common.DEFAULT_CODEGEN_DIR}/stage{STAGE_ID}/{name}"
        sdfgs = list(sdfgs.values())
        # Avoid name conflicts.
        unique_names(sdfgs)
        # Add instrumentation if necessary.
        if config.instrument:
            instrument_sdfg(sdfgs)

        dace.Config.set('compiler', 'cuda', 'default_block_size', value="256,1,1")
        compile_if_propagated_sdfgs(
            sdfgs, gpu=False, release=True,
            instrument=config.instrument,  # Redundant. TODO: Remove from the interface.
            generate_code=True, lib=False,
            stage_suffix=None, # stage3 if you need clip_count, else None, TODO: improve this
            )

if __name__ == "__main__":
    main()