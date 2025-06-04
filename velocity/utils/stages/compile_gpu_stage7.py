import dace
from utils.move_ifs_inside_maps import move_ifs_inside_maps
from utils.pre_gpu_fixes import pre_gpu_fix
from utils.segmented_reduction import to_segmented_reduction
import utils.stages.common as common
import utils.config as config
from utils.find import find_node_by_name
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from dace.transformation.passes.to_gpu import ToGPU
from dace.transformation.passes import GPUKernelLaunchRestructure
from utils.add_gpu_copies_to_flattener import add_gpu_copies_to_flattener
import argparse
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.int64_to_int32 import int64_to_int32
from utils.tile import tile_kernels
STAGE_ID = 7


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    make_arrays_persistent(sdfg)
    int64_to_int32(sdfg)
    tile_kernels(sdfg)
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
        common.compile_action(STAGE_ID, sdfgs)

if __name__ == "__main__":
    main()
