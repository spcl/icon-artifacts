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
sdfg_names = [
    "velocity_nproma20480_if_prop_lvn_only_0_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_2.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_0_istep_2.sdfgz",
]
use_cache = False
resulting_sdfgs = []
for sdfg_name in sdfg_names:
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
        apply_loop_locality_pass(sdfg)
        sdfg.simplify(skip=["ArrayElimination"], verbose=verbose)
        if reduction:
            add_all_reductions(sdfg)
        sdfg.simplify(skip=["ArrayElimination"])
        move_transients_to_top_level(
            root=sdfg,
            upper_bounds={
                "z_w_con_c": 1,
                "maxvcfl_arr": 1,
                "cfl_clipping": 1,
                "z_w_concorr_mc": 1,
            },
        )
        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage1.sdfgz", compress=True)

    if Path(f"cpu_{sdfg_name}_stage2.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage2.sdfgz")
    else:
        # XXX: Permissive will ignore any read/write conflicts.
        sdfg.apply_transformations_repeated(LoopToMap, permissive=True)
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
        # This can only be safely applied to selected cases. Skip for now.
        # sdfg.apply_transformations(YoloMapFission)
        #untangle_if_sdfg(sdfg, verbose=verbose)
        #split_map_sdfg(sdfg, False, verbose=verbose)
        sdfg.validate()

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
    resulting_sdfgs.append(sdfg)

################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
compile_if_propagated_sdfgs(resulting_sdfgs, gpu=False, release=release)

# check if execution was successful
if os.system(f"./velocity_cpu") != 0:
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
