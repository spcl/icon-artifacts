import argparse

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.to_gpu import ToGPU

import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import tile_kernels
from utils.reshape_kernels import reshape_kernels, reshape_kernels_w_coarsening
STAGE_ID = 7
import os

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    make_arrays_persistent(sdfg)
    int64_to_int32(sdfg)
    reassign_vars(sdfg)
    print("Stage #7: Validate")
    sdfg.validate()
    sdfg.simplify()
    #reshape_kernels(sdfg, True)
    # Must be individualized for each kernel
    x_coarsening = int(os.environ.get("X_COARSENING", 2))
    y_coarsening = int(os.environ.get("Y_COARSENING", 2))
    x_block_size = int(os.environ.get("X_BLOCK_SIZE", 128))
    y_block_size = int(os.environ.get("Y_BLOCK_SIZE", 2))
    y_unroll_factor = int(os.environ.get("Y_UNROLL_FACTOR", 2))
    reshape_kernels_w_coarsening(sdfg,
                                 x_coarsening=x_coarsening,
                                 y_coarsening=y_coarsening,
                                 x_block_size=x_block_size,
                                 y_block_size=y_block_size,
                                 unroll_x=True,
                                 unroll_x_factor=None,
                                 unroll_y=True,
                                 unroll_y_factor=y_unroll_factor,)
    #tile_kernels(sdfg)
    sdfg.simplify()

    # If you run the function it removes out_val_0 but it should not
    #prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
    #prune_unused_inputs_outputs_recursive(sdfg) # A posible error related to ntnd if this is called
    sdfg.validate()
    change_reduction_schedule(sdfg)
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
