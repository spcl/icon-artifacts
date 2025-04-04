from pathlib import Path
import shutil
import dace
import os
from dace.transformation.auto_tile.add_compute_element_map import AddComputeElementBlockMap
from dace.transformation.auto_tile.remainder_loop import RemainderLoop
from dace.transformation.auto_tile.thread_coarsening import ThreadCoarsening
from dace.transformation.interstate import (
    LoopToMap,
    ContinueToCondition,
    ConditionFusion,
    StateFusion,
)
from dace.transformation.passes import (
    InlineSDFGs,
    SymbolPropagation,
    StructToContainerGroups,
)

from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from dace.transformation.passes.to_gpu import ToGPU
from utils import *
from dace.sdfg import utils as sdutil

# Load SDFG
sdfg_names = [
    "velocity_nproma20480_if_prop_lvn_only_0_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_1.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_1_istep_2.sdfgz",
    "velocity_nproma20480_if_prop_lvn_only_0_istep_2.sdfgz",
]
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
    if Path(f"gpu_{sdfg_name}_stage1.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage1.sdfgz")
    else:
        clean_bad_views(sdfg)
        sdfg.apply_transformations_repeated(ContinueToCondition)
        sdfg.simplify()
        SymbolPropagation().apply_pass(sdfg, {})
        sdfg.simplify()
        StructToContainerGroups(
            validate=False,
            save_steps=False,
            verbose=verbose,
            simplify=False,
            interface_with_struct_copy=True,
            interface_to_gpu=True,
            clean_trivial_views=True,
        ).apply_pass(sdfg, {})
        sdfg.simplify(skip=["ArrayElimination"])
        apply_loop_locality_pass(sdfg)
        if reduction:
            add_all_reductions(sdfg)
        sdfg.simplify(skip=["ArrayElimination"])
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage1.sdfgz", compress=True)

    if Path(f"gpu_{sdfg_name}_stage2.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage2.sdfgz")
    else:
        # XXX: Permissive will ignore any read/write conflicts.
        sdfg.apply_transformations_repeated(LoopToMap, permissive=True)
        # Ensure no symbols are captured by LoopToMap
        count_symbols_use_defs(sdfg, verbose=verbose, use_assert=True)
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
        sdfg.apply_transformations_repeated(MapCollapse)
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
        if verbose:
            sdfg.save("parallel.sdfgz", compress=True)

        # Creates segfault with 2GPU applied
        """
        for s in sdfg.states():
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    if (n.map.range == dace.subsets.Range([[1, 1, 1]]) or
                        n.map.range == dace.subsets.Range([[0, 0, 1]])):
                        #return self._subgraph_user fails checking can be applied??
                        #if TrivialMapElimination().can_be_applied(s, s.node_id(n), sdfg):
                        TrivialMapElimination().apply_to(sdfg=sdfg, map_entry=n)
                        #else:
                        #    print(f"Cannot eliminate map {n.map} in state {s} in SDFG {sdfg.label}")
        """


        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage2.sdfgz", compress=True)

    # Shouldn't have any loops left
    count_loops(sdfg, verbose=verbose, use_assert=True)

    if Path(f"gpu_{sdfg_name}_stage3.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage3.sdfgz")
    else:
        sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})
        # This can only be safely applied to selected cases. Skip for now.
        # sdfg.apply_transformations(YoloMapFission)
        # preprocess_tough_nut(sdfg)
        move_transients_to_top_level(
            root=sdfg,
            upper_bounds={
                "z_w_con_c": 2,
                "maxvcfl_arr": 2,
                "cfl_clipping": 2,
                "z_w_concorr_mc": 2,
                "levmask": 2,
            },
        )
        preprocess_tough_nut(sdfg)
        prune_unused_inputs_outputs(sdfg)
        prune_unused_inputs_outputs_recursive(sdfg)
        sdfg.validate()

        # Do not call mapcollapse or mapfusion with permissive=True, because collapsing
        # Sequential -> GPU _ Device map into one will not result well
        #sdfg.apply_transformations_repeated(ConditionFusion)
        sdfg.apply_transformations_repeated(ConditionFusion)
        # Some NestedSDFGs with if conditions can be split only after moving up invariant ifs
        # split_map_sdfg(sdfg, True, verbose)
        prune_unused_inputs_outputs(sdfg)
        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")
        k = sdfg.apply_transformations_repeated(MapFusion)
        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.NestedSDFG):
                if isinstance(n, dace.nodes.NestedSDFG):
                    k = n.sdfg.apply_transformations_repeated(MapFusion)
                    if verbose:
                        print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")
        if verbose:
            print(f"Applied MapFusion {k} time(s)")
        k = sdfg.apply_transformations_repeated(MapCollapse)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")
        sdfg.simplify(skip=["StateFusion"])
        prune_unused_inputs_outputs(sdfg)
        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")

        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage3.sdfgz", compress=True)
    # Currently makes the SDFG invalid, thrust error illegal address

    # Ensure no symbols are captured
    count_symbols_use_defs(sdfg, verbose=verbose, use_assert=True)

    if Path(f"gpu_{sdfg_name}_stage4.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage4.sdfgz")
    else:
        merge_maps_in_sdfg(sdfg)
        # pre_gpu_fix(sdfg)
        # make_unique_block_var(sdfg)
        # Skip state fusion until we offload to GPU as having both GPU and CPU usage in the same state
        # prevents GPU offloading form working
        sdfg.validate()
        sdfg.simplify(skip=["StateFusion"])
        sdfg.validate()

        prune_unused_inputs_outputs(sdfg)

        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")
        k = sdfg.apply_transformations_repeated(MapFusion)
        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.NestedSDFG):
                if isinstance(n, dace.nodes.NestedSDFG):
                    k = n.sdfg.apply_transformations_repeated(MapFusion, permissive=True)
                    if verbose:
                        print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")
        if verbose:
            print(f"Applied MapFusion {k} time(s)")
        k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")
        sdfg.simplify(skip=["StateFusion"])
        prune_unused_inputs_outputs(sdfg)
        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")

        sdfg.simplify(skip=["StateFusion"])
        # I saw trurthy ifs, propagate those conditions and try to fuse states agian
        propagate_if_cond(sdfg, sdfg, None, None, verbose)
        demote_symbol_to_scalar(sdfg, "tmp_call_18")

        sdfg.validate()

        # Breaks the SDFG
        #sdfg.apply_transformations_once_everywhere(MapFusion)
        #for n, g in sdfg.all_nodes_recursive():
        #    if isinstance(n, dace.nodes.NestedSDFG):
        #        if isinstance(n, dace.nodes.NestedSDFG):
        #            n.sdfg.apply_transformations_once_everywhere(MapFusion, permissive=True)

        sdfg.simplify(skip=["StateFusion"])

        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage4.sdfgz", compress=True)

    if Path(f"gpu_{sdfg_name}_stage5.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage5.sdfgz")
    else:
        sdfg.validate()
        prune_unused_inputs_outputs(sdfg)
        sdfg.validate()
        prune_unused_inputs_outputs_recursive(sdfg)
        sdfg.validate()
        ToGPU(verbose=verbose).apply_pass(sdfg, {})
        sdfg.validate()
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage4_5.sdfgz", compress=True)
        #
        GPUKernelLaunchRestructure().apply_pass(sdfg, {})
        sdfg.validate()
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage5.sdfgz", compress=True)



    if Path(f"gpu_{sdfg_name}_stage6.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage6.sdfgz")
    else:
        # Add ThreadBlock map and coarsen a bit
        dace.Config.set('compiler', 'cuda', 'default_block_size', value="128,1,1")
        for n, graph in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.MapEntry):
                if n.schedule == dace.ScheduleType.GPU_Device:
                    AddComputeElementBlockMap.apply_to(
                        sdfg=graph.sdfg,
                        verify=False,
                        map_entry=n,
                        options={
                            "compute_element_group_dims": [128, 1, 1],
                            "map_schedule": dace.dtypes.ScheduleType.GPU_Device,
                            "schedule_to_add": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                        },
                    )
        # Only if we can have a dimension we can divide nicely
        """
        for n, graph in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.MapEntry):
                if n.schedule == dace.ScheduleType.GPU_Device:
                    for n2 in sdutil.dfs_topological_sort(graph, n):
                        if (
                            isinstance(n2, dace.nodes.MapEntry)
                            and n2.map.schedule == dace.dtypes.ScheduleType.GPU_ThreadBlock
                        ):
                            #print(n.map.range) # 1:91(0:90) or 1:92(0:91) -> meaning 90 and 91 elements
                            coarsening_factors = []
                            for (b, e, s), (tb, te, ts) in zip(n.map.range, n2.map.range):
                                range1 = (e+1-b)//s
                                range2 = (te+1-tb)//ts
                                print(f"Range1: {range1}, Range2: {range2}")
                                dim = 1
                                try:
                                    dim = int(range1 // range2)
                                except:
                                    dim = 1
                                if dim == 91:
                                    coarsening_factor = 7
                                    print("Coarsening factor: 7 for range 91")
                                elif dim == 90:
                                    coarsening_factor = 9
                                    print("Coarsening factor: 9 for range 90")
                                elif dim == 89:
                                    coarsening_factor = 1
                                    print("Coarsening factor: 1 for range 89")
                                else:
                                    coarsening_factor = 1
                                coarsening_factors.append(coarsening_factor)

                            if not all([v == 1 for v in coarsening_factors]):
                                ThreadCoarsening.apply_to(
                                    sdfg=graph.sdfg,
                                    verify=False,
                                    thread_group_map_entry=n2,
                                    device_map_entry=n,
                                    options={
                                        "tile_sizes": list(reversed(coarsening_factors)),
                                    },
                                )
        sdfg.validate()
        """
        # Fix remainder loop for tiling
        """
        for n, graph in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.MapEntry):
                if n.schedule == dace.ScheduleType.GPU_Device:
                    for n2 in sdutil.dfs_topological_sort(graph, n):
                        if (
                            isinstance(n2, dace.nodes.MapEntry)
                            and n2.map.label.startswith("ThreadCoarsenedMap")
                        ):
                            RemainderLoop.apply_to(
                                sdfg=graph.sdfg,
                                verify=True,
                                inner_work_map_entry=n2,
                                tblock_type=dace.dtypes.ScheduleType.GPU_ThreadBlock,
                                options={
                                    "tblock_type": dace.dtypes.ScheduleType.GPU_ThreadBlock,
                                }
                            )
                            break
        """
        sdfg.validate()
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage6.sdfgz", compress=True)

    # Validate the SDFG
    sdfg.validate()
    sdfg.save(f"gpu_{sdfg_name}_result.sdfgz", compress=True)
    sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_result.sdfgz")
    resulting_sdfgs.append(sdfg)



################################################################################
### Numerically validate the SDFG
################################################################################

# for i in {1..5}; do ./velocity_gpu ${i} ${i}; done

# Compile the SDFG
unique_names(resulting_sdfgs)

# Add instrumentation
if instrument:
    # instrument the SDFG
    instrument_sdfg(resulting_sdfgs)

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=True, release=release, instrument=instrument, generate_code=True)

# check if execution was successful
if os.system(f"./velocity_gpu") != 0:
    print("Execution failed")
    exit(1)

# Compare .got and .want files
compare_got_and_want()

################################################################################
### Measure performance
################################################################################

if instrument:
    # collect reports
    #for sdfg in resulting_sdfgs:
    #    sdfg.save_report(sdfg.get_latest_report_path())
    collect_reports(resulting_sdfgs)

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
