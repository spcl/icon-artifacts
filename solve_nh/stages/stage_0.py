import dace
from dace import SDFG
from utils.inject_velocity_shim import inject_velocity_shim
from stages import common
import argparse


STAGE_ID = 0


def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""
    inject_velocity_shim(g)
    g.simplify()
    return g


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument(
        "--optimize", action=argparse.BooleanOptionalAction, default=False
    )
    argp.add_argument("--codegen", action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument("--compile", action=argparse.BooleanOptionalAction, default=False)
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
        common.compile_action(STAGE_ID)


if __name__ == "__main__":
    main()
