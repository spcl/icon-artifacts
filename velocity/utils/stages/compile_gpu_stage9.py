import dace
import argparse
import utils.stages.common as common
from utils.change_flatten_lib_to_shallow_copy import change_flatten_lib_to_shallow_copy
from utils.input_to_gpu import input_to_gpu
from utils.add_set_zero import add_set_zero
STAGE_ID = 9

_allocation_names_to_comment_out = set()

def optimization_action(sdfg):
    global _allocation_names_to_comment_out
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    # Prepares SDFG to be built as a GPU library
    # Move to shallow COPY variant (remove copy in copy out nodes)
    # A good way to remove it from being simplified away
    shallow_copy_used_structs = ["p_prog", "p_int", "p_metrics", "p_patch", "p_diag"]
    deflatten_used_structs = ["p_diag"]
    _allocation_names_to_comment_out =  change_flatten_lib_to_shallow_copy(sdfg, shallow_copy_used_structs, deflatten_used_structs)
    sdfg.validate()
    #add_set_zero(sdfg, "gpu_maxvcfl_arr")
    sdfg.validate()
    input_to_gpu(sdfg, "z_w_concorr_me")
    input_to_gpu(sdfg, "z_kin_hor_e")
    input_to_gpu(sdfg, "z_vt_ie")
    sdfg.validate()
    return sdfg

def main():
    global _allocation_names_to_comment_out
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
        assert _allocation_names_to_comment_out is not None and _allocation_names_to_comment_out != set()
        common.compile_action(STAGE_ID, sdfgs, True, _allocation_names_to_comment_out, True)

if __name__ == "__main__":
    main()
