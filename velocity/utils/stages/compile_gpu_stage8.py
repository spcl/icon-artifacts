import argparse

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.to_gpu import ToGPU
from dace import nodes
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.state import SDFGState

import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import tile_kernels
from utils.reshape_kernels import reshape_kernels, reshape_kernels_w_coarsening
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
STAGE_ID = 8
import os

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    # Assigning a warp to the column is not a very good idea
    # reshape_kernels(sdfg, True)
    # Must be individualized for each kernel
    x_coarsening = int(os.environ.get("X_COARSENING", 1))
    y_coarsening = int(os.environ.get("Y_COARSENING", 1))
    x_block_size = int(os.environ.get("X_BLOCK_SIZE", 256))
    y_block_size = int(os.environ.get("Y_BLOCK_SIZE", 1))
    y_unroll_factor = int(os.environ.get("Y_UNROLL_FACTOR", 1))
    #reshape_kernels(sdfg)
    #reshape_kernels_w_coarsening(sdfg,
    #                             x_coarsening=x_coarsening,
    #                             y_coarsening=y_coarsening,
    #                             x_block_size=x_block_size,
    #                             y_block_size=y_block_size,
    #                             unroll_x=True,
    #                             unroll_x_factor=None,
    #                             unroll_y=True,
    #                             unroll_y_factor=y_unroll_factor,)
    #tile_kernels(sdfg)
    sdfg.simplify()
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
