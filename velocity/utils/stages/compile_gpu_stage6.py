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
import argparse

STAGE_ID = 6


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    pre_gpu_fix(sdfg)
    move_ifs_inside_maps(sdfg)
    flatten_lib, _ = find_node_by_name(sdfg, "flatten")
    deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

    sdfg.validate()
    sdfg.save("gpu_velocity_transients.sdfgz", compress=True)
    ToGPU(verbose=config.verbose, cpu_library_nodes=[flatten_lib, deflatten_lib], exclude=["vcflmax"]).apply_pass(sdfg, {})
    sdfg.validate()

    prune_unused_inputs_outputs(sdfg)
    GPUKernelLaunchRestructure().apply_pass(sdfg, {})
    prune_unused_inputs_outputs(sdfg)
    #move_lib_schedules(sdfg, dace.dtypes.ScheduleType.GPU_Device)
    #TODO: to_segmented_reduction(sdfg)
    print("SEGMENTED REDUCTION BEG")
    to_segmented_reduction(sdfg)
    for arrname, arr in sdfg.arrays.items():
        if arr.transient:
            if arr.storage == dace.dtypes.StorageType.GPU_Global:
                arr.lifetime = dace.dtypes.AllocationLifetime.SDFG
        #if arrname == "gpu_maxvcfl_arr":
        #    raise Exception(arr, arr.transient, arr.lifetime, arr.storage)
    for e, graph in sdfg.all_edges_recursive():
        if e.data is not None and hasattr(e.data, "data") and e.data.data == "gpu_out_val_0":
            sb = dace.subsets.Range.from_string("2*_for_it_35")
            #print(sb, e.data.subset)
            if sb == e.data.subset:
                #raise Exception(f"{sb}| {e.data.subset} uwu")
                e.data.subset = dace.subsets.Range.from_string("_for_it_35")
            #if e.data.subset =
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
        common.compile_action(STAGE_ID, sdfgs)

if __name__ == "__main__":
    main()
