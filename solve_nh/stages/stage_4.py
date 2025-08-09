import dace
from dace import SDFG
from stages import common
from utils.codegen_from_sdfg import ArtifactMode, OptimizationMode

import argparse


from utils.to_library_transformations import (
    nontransient_inputs_to_gpu,
    change_flatten_lib_to_shallow_copy
)
from utils.profiling_and_sync_patches import (
    remove_profiling_states,
    remove_sync_states,
    insert_program_entry_exit_syncs
)

STAGE_ID = 4

def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # === Sub-Phase 0: Remove profiling timers and additional profiling sync ===
    remove_profiling_states(g)
    remove_sync_states(g)
    insert_program_entry_exit_syncs(g)
    g.append_global_code(
        cpp_code="#define DYCORE_GPU_INTEGRATION"
    )
    g.validate()
    # === Sub-Phase 0: Remove profiling timers and additional profiling sync ===

    # === Sub-Phase 1: Move inputs to GPU storage without changing the names ===
    nontransient_inputs_to_gpu(g)
    g.validate()
    # === Sub-Phase 1: Move inputs to GPU storage without changing the names ===

    # === Sub-Phase 2: Replace Flattening with shallow copy ===
    # Important this requires flattening and deflattening code to be generated
    # and in `solve_nh` folder (some are committed to the repository)
    change_flatten_lib_to_shallow_copy(g)
    g.validate()
    # === Sub-Phase 2: Replace Flattening with shallow copy ===

    return g


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument(
        "--optimize", action=argparse.BooleanOptionalAction, default=False
    )
    argp.add_argument("--codegen", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument("--compile", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument(
        "--release",
        action=argparse.BooleanOptionalAction,
        default=False,
        help="Enable release mode optimizations and hardening.",
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
        common.compile_action(STAGE_ID, ArtifactMode.SHARED, OptimizationMode.RELEASE if args.release else OptimizationMode.DEBUG)


if __name__ == "__main__":
    main()
