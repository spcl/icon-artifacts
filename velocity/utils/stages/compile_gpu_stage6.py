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
from utils.rm_segmented_reduce import rm_segmented_reduce
STAGE_ID = 6

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
    # TODO: Make sure this does not break numerical validation
    rm_segmented_reduce(sdfg)
    # Rm segmented reduce results with trivial if conditions
    # propagate_if_cond(sdfg, sdfg, None, None, True)
    remove_unused_inconnectors_from_nestedsdfg(sdfg)
    sdfg.simplify()
    sdfg.validate()

    # Transformation does not detect anything, check
    # setzero_to_memset(sdfg)
    sdfg.validate()
    for arr_name, arr in sdfg.arrays.items():
        if "maxvcfl_arr" in arr_name:
            if "gpu" in arr_name:
                arr.storage = dace.dtypes.StorageType.GPU_Global
            else:
                arr.storage = dace.dtypes.StorageType.CPU_Heap
            arr.lifetime = dace.dtypes.AllocationLifetime.SDFG
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

        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            from sc26_layout.extract_gpu_kernel import permute_single_map_gpu
            sdfg = permute_single_map_gpu(sdfg)
            sdfg.validate()
            nsdfgs[name] = sdfg

        common.compile_action(STAGE_ID, nsdfgs, False, None, False,
                              name_suffix="_permuted_single_map", main_name="main_per.cu", tblock_dim="96,2,1",
                              stage_suffix="_permuted_single_map")

        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            from sc26_layout.extract_gpu_kernel import add_timer_single_map_gpu
            sdfg = add_timer_single_map_gpu(sdfg)
            sdfg.validate()
            nsdfgs[name] = sdfg

        common.compile_action(STAGE_ID, nsdfgs, False, None, False,
                              name_suffix="_unpermuted", main_name="main_per.cu", tblock_dim="256,1,1",
                              stage_suffix="_unpermuted")

        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        for name, sdfg in sdfgs.items():
            from sc26_layout.extract_gpu_kernel import add_symbols
            add_symbols(sdfg)
        common.compile_action(STAGE_ID, sdfgs, False, None, False, main_name="main_per.cu", tblock_dim="256,1,1",
                              name_suffix="", stage_suffix="")

if __name__ == "__main__":
    main()
