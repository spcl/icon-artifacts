import argparse

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.to_gpu import ToGPU

import utils.config as config
import utils.stages.common as common
from utils.add_gpu_copies_to_flattener import add_gpu_copies_to_flattener
from utils.find import find_node_by_name
from utils.move_ifs_inside_maps import move_ifs_inside_maps
from utils.move_lib_schedules import move_lib_schedules
from utils.pre_gpu_fixes import pre_gpu_fix
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
from utils.remove_unused_inconnectors_from_nestedsdfg import remove_unused_inconnectors_from_nestedsdfg
from utils.segmented_reduction import to_segmented_reduction

STAGE_ID = 6
from utils.rm_segmented_reduce import rm_segmented_reduce

def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    add_gpu_copies_to_flattener(sdfg)
    sdfg.validate()

    pre_gpu_fix(sdfg)

    sdfg.validate()
    move_ifs_inside_maps(sdfg)
    flatten_lib, _ = find_node_by_name(sdfg, "flatten")
    deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

    sdfg.validate()
    ToGPU(verbose=config.verbose, cpu_library_nodes=[flatten_lib, deflatten_lib], exclude=["vcflmax"]).apply_pass(sdfg, {})
    sdfg.validate()

    prune_unused_inputs_outputs(sdfg)
    GPUKernelLaunchRestructure().apply_pass(sdfg, {})
    prune_unused_inputs_outputs(sdfg)
    move_lib_schedules(sdfg, dace.dtypes.ScheduleType.GPU_Device)
    to_segmented_reduction(sdfg)

    for arrname, arr in sdfg.arrays.items():
        if arr.transient:
            if arr.storage == dace.dtypes.StorageType.GPU_Global:
                arr.lifetime = dace.dtypes.AllocationLifetime.SDFG

    for e, graph in sdfg.all_edges_recursive():
        if e.data is not None and hasattr(e.data, "data") and (e.data.data == "gpu_out_val_0" or e.data.data == "out_val_0"):
            sb = dace.subsets.Range.from_string("2*_for_it_35 - 2")
            if sb == e.data.subset:
                e.data.subset = dace.subsets.Range.from_string("_for_it_35 - 1")
    sdfg.validate()
    rm_segmented_reduce(sdfg)
    remove_unused_inconnectors_from_nestedsdfg(sdfg)
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
