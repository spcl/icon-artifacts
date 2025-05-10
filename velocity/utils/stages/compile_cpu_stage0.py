import dace
import utils.stages.common as common
import argparse

STAGE_ID = 0


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=True)
    args = argp.parse_args()
    assert args.compile, "That's the only thing we can do here."

    names = common.sdfg_names()

    if args.compile:
        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        common.compile_action(STAGE_ID, sdfgs)

if __name__ == "__main__":
    main()
