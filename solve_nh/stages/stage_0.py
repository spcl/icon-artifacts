import dace
from dace import SDFG
from utils.stage0_hack_split_predictor_pre_omp_loop import split_predictor_pre_omp_loop
from utils.inject_velocity_shim import inject_velocity_shim
from stages import common
from utils.codegen_from_sdfg import ArtifactMode
from utils.propagate_if_conditions import propagate_if_conditions

import argparse


STAGE_ID = 0


def optimization_action(g: SDFG, velicity_shim: bool):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    # This map is split manually, because if this is the case in the front-end, f2dac crashes
    # === Sub-phase 0: Fixes that should have been in the front-end (but it breaks) and inject velocity as a tasklet ===
    if g.name == 'solve_nh_predictor_pre':
        split_predictor_pre_omp_loop(g)
    # Replaces velocity tendencies subgraph with a tasklet that expects struct-only input
    # We do not build that library anymore and it needs to be replaced again to be able to compile
    # Reinjection of velocity tendencies require finding a tasklet called `velocity_tendencies` thus
    # you can't remove.
    if velicity_shim:
        inject_velocity_shim(g)
    # Simplify does not much while we have structs and views
    g.simplify()
    # === Sub-phase 0: Fixes that should have been in the front-end (but it breaks) and inject velocity as a tasklet ===

    # === Sub-phase 1: Propagate if conditions ===
    # Propagate special constants
    # Commented out as you can also use `specialize_scalar in stage 2`, probably better to use that
    #config_constants = {
    #    'divdamp_type': '3',
    #    'rayleigh_type': '2',
    #}
    #propagate_if_conditions(
    #    sdfg=g,
    #    replace_dict=config_constants,
    #    verbose=True)
    # === Sub-phase 1: Propagate if conditions ===
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
        type=ArtifactMode,
        choices=list(ArtifactMode),
        required=False,
        default=ArtifactMode.EXEC,
        help="Select the mode: static, shared, or exec",
    )
    argp.add_argument("--shim", action=argparse.BooleanOptionalAction, default=True)
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

            g = optimization_action(g, velicity_shim=args.shim)

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
