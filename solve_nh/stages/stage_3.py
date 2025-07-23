import dace
from dace import SDFG
from dace.sdfg.state import LoopRegion
from dace.transformation.interstate.loop_to_map import LoopToMap
from stages import common
from utils.codegen_from_sdfg import Mode
from utils.gpu_offloading_wo_host_dev_copies import (
    gpu_offloading_wo_host_dev_copies,
    replace_cpu_velocity_call_with_gpu_velocity_call,
)
from utils.flattener_modifications import (
    add_gpu_copies_to_flattener,
)
import argparse


STAGE_ID = 3

def optimization_action(g: SDFG):
    """DEFINE THE OPTIMIZATION ACTION HERE"""

    # === Sub-Phase 2: Offloading ===
    # Add GPU copy-in and copy-out to the flattener/copy-in and deflattener/copy-out states
    # add_gpu_copies_to_flattener(g)
    # Perform the offloading with the assumption that all kernels purely run on the GPU
    gpu_offloading_wo_host_dev_copies(g)
    # Replace the call to CPU velocity with the GPU call
    replace_cpu_velocity_call_with_gpu_velocity_call(g)
    g.validate()
    # === Sub-Phase 2: Offloading ===

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
