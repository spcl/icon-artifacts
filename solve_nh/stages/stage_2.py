import dace
from dace import SDFG
from dace.transformation.dataflow import MapCollapse
from stages import common
from utils.codegen_from_sdfg import Mode
from dace.transformation.interstate import InlineSDFG
from utils.count import count_map_dimensions
from utils.count import count_uncollapsed_maps

from utils.clean_unused_data_from_nsdfg_connectors import (
    clean_unused_data_from_nsdfg,
    clean_unused_symbols_from_nsdfg,
)
import argparse


STAGE_ID = 2

def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 1: Clean Unused Data and Symbols From NSDFGs ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 1: Clean Unused Data and Symbols From NSDFGs ===

    # === Sub-Phase 2: InlineSDFG + MapCollapse For GPU Offloading ===
    for _ in range(3): # TODO: Maybe 2 is enough
        g.apply_transformations_repeated(
            InlineSDFG
        )
        g.apply_transformations_repeated(
            MapCollapse
        )
    count_map_dimensions(g)
    count_uncollapsed_maps(g, verbose=False, use_assert=True)
    # === Sub-Phase 2: InlineSDFG + MapCollapse For GPU Offloading  ===

    # === Sub-Phase 3: Clean Again ===
    clean_unused_data_from_nsdfg(g)
    clean_unused_symbols_from_nsdfg(g)
    g.validate()
    # === Sub-Phase 3: Clean Again ===


    return g


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument(
        "--optimize", action=argparse.BooleanOptionalAction, default=False
    )
    argp.add_argument("--codegen", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument("--compile", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument(
        "--mode",
        type=Mode,
        choices=list(Mode),
        required=False,
        default=Mode.EXEC,
        help="Select the mode: static, shared, or exec",
    )
    args = argp.parse_args()
    if not args.optimize and not args.codegen and not args.compile:
        args.optimize, args.codegen, args.compile = True, True, True

    names = common.sdfg_names()

    if args.optimize:
        sdfgs = {}
        for name in names:
            infile = common.stage_input(name, STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)

            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")

            g = SDFG.from_file(infile)
            g.name = name
            g.validate()

            g = optimization_action(g)

            g.save(outfile, compress=True)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfgs[name] = g

    if args.codegen:
        # Read back the written files as we prepare for compilation.
        sdfgs = {
            name: SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names
        }
        print(f"Stage #{STAGE_ID}: Generating code for {len(sdfgs)} SDFGs")
        common.codegen_action(STAGE_ID, sdfgs)

    if args.compile:
        print(f"Stage #{STAGE_ID}: Compiling SDFGs")
        common.compile_action(STAGE_ID, args.mode)


if __name__ == "__main__":
    main()
