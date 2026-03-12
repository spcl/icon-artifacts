import argparse
import dace
import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import prune_unused_inputs_outputs
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.change_array_dtypes import change_array_dtypes
STAGE_ID = 7

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    make_arrays_persistent(sdfg)
    int64_to_int32(sdfg)
    reassign_vars(sdfg)
    sdfg.simplify()
    prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
    sdfg.validate()
    change_reduction_schedule(sdfg)
    sdfg.validate()
    # HACK: Remove cfl clippign rleated kernels assuming it is 0. For now: Do not perform this semantics-changing transformation.
    # sdfg = hacky_cfl_clipping_related_kernel_removal(sdfg)
    sdfg.simplify()
    sdfg.validate()
    prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
    remove_unused_inconnectors_from_nestedsdfg(sdfg)
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
