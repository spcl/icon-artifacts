import os
import shutil
from pathlib import Path
import dace
from dace.transformation.interstate import (
    LoopToMap,
    ContinueToCondition,
    ConditionFusion,
)
from dace.transformation.passes import SymbolPropagation, StructToContainerGroups
from dace.transformation.dataflow import MapCollapse
from utils import *

# Load SDFG
sdfg_name = "velocity_nproma20480.sdfgz"
sdfg = dace.SDFG.from_file(sdfg_name)
sdfg.name = sdfg_name.split(".")[0]
sdfg.validate()
build_loc = sdfg.build_folder
sdfg_name = sdfg.name


################################################################################
### Apply Optimizations
################################################################################


# Apply transformations
if Path(f"cpu_{sdfg_name}_stage1.sdfgz").exists() and use_cache:
    sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage1.sdfgz")
else:
    clean_bad_views(sdfg)
    sdfg.apply_transformations_repeated(ContinueToCondition)
    sdfg.simplify(verbose=verbose)
    SymbolPropagation().apply_pass(sdfg, {})
    sdfg.simplify(verbose=verbose)
    StructToContainerGroups(
        save_steps=False,
        verbose=verbose,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=False,
    ).apply_pass(sdfg, {})
    sdfg.simplify(skip=["ArrayElimination"], verbose=verbose)
    make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
    make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_555_c_555")
    sdfg.simplify(skip=["ArrayElimination"], verbose=verbose)
    if reduction:
        loop_to_max_reduction(sdfg)
        cfl_clipping_to_reduction(sdfg)
        maxvcfl_to_reduction(sdfg)
        tmp_call_13_to_reduction(sdfg)
        levmask_to_reduction(sdfg)
    sdfg.simplify(skip=["ArrayElimination"])
    move_transients_to_top_level(
        root=sdfg,
        upper_bounds={
            "z_w_con_c": 960,
            "maxvcfl_arr": 960,
            "cfl_clipping": 960,
            "z_w_concorr_mc": 960,
        },
    )
    if use_cache:
        sdfg.save(f"cpu_{sdfg_name}_stage1.sdfgz", compress=True)

if Path(f"cpu_{sdfg_name}_stage2.sdfgz").exists() and use_cache:
    sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage2.sdfgz")
else:
    sdfg.apply_transformations_repeated(LoopToMap)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"], verbose=verbose)
    sdfg.apply_transformations_repeated(MapCollapse)
    sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"], verbose=verbose)
    if use_cache:
        sdfg.save(f"cpu_{sdfg_name}_stage2.sdfgz", compress=True)

# Shouldn't have any loops left
count_loops(sdfg, verbose=verbose, assert_loops=True)

if Path(f"cpu_{sdfg_name}_stage3.sdfgz").exists() and use_cache:
    sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage3.sdfgz")
else:
    sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})
    sdfg.apply_transformations(YoloMapFission, validate=False)
    sdfg.validate()
    untangle_if_sdfg(sdfg, verbose=verbose)
    split_map_sdfg(sdfg, False, verbose=verbose)
    sdfg.validate()

    raise_loop_invariant_if(
        sdfg,
        check_invariant_if_conds=["1 - ldeepatmo == 1", "_if_cond_27 == 1"],
        copy_edge_before=[False, True],
    )
    raise_loop_invariant_if(
        sdfg, check_invariant_if_conds=["not (lvn_only == 1)"], copy_edge_before=[False]
    )
    raise_loop_invariant_if(
        sdfg, check_invariant_if_conds=["(istep == 1) == 1"], copy_edge_before=[False]
    )
    sdfg.apply_transformations_repeated(ConditionFusion)
    if use_cache:
        sdfg.save(f"cpu_{sdfg_name}_stage3.sdfgz", compress=True)

# Turn all maps to CPU_Multicore
for node, state in sdfg.all_nodes_recursive():
    if isinstance(node, dace.nodes.MapEntry):
        node.map.schedule = dace.ScheduleType.CPU_Multicore

# Validate the SDFG
sdfg.validate()
sdfg.save(f"cpu_{sdfg_name}_result.sdfgz", compress=True)


################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
compile_sdfg(sdfg, gpu=False, release=release)

# check if execution was successful
if os.system(f"./{sdfg_name}") != 0:
    print("Execution failed")
    exit(1)

# Compare .got and .want files
compare_got_and_want()

################################################################################
### Measure performance
################################################################################

if run_benchmark:
    benchmark_sdfg(
        sdfg,
        "CPU",
        gpu=False,
        release=release,
        warmups=1,
        measurements=1,
        profile=True,
        save_kernel_sdfg=False,
    )

################################################################################
### Cleanup
################################################################################

# remove the compiled program
if cleanup:
    os.remove(sdfg_name)

    # remove .got and .want files
    for f in os.listdir():
        if f.endswith(".got") or f.endswith(".want"):
            os.remove(f)

    # remove the .dacecache folder
    shutil.rmtree(build_loc)
