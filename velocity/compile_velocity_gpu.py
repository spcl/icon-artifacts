from pathlib import Path
import shutil
import dace
import os
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

# from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from dace.transformation.passes.to_gpu import ToGPU
from utils import *


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
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
        sdfg.apply_transformations_repeated(MapCollapse)
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
        if verbose:
            sdfg.save("parallel.sdfgz", compress=True)
        move_transients_to_top_level(
            root=sdfg,
            upper_bounds={
                "z_w_con_c": 2, # Within cell kernel, 1 block
                "maxvcfl_arr": 2, # Within cell kernel, 1 block
                "cfl_clipping": 2, # Within cell kernel, 1 block
                "z_w_concorr_mc": 2, # Within cell kernel, 1 block
            },
            verbose=verbose,
        )
        if verbose:
            sdfg.save("transients_moved.sdfgz", compress=True)

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

        ToGPU().apply_pass(sdfg, {"verbose": verbose})

        #if not reduction:
        #    for cfg in sdfg.nodes():
        #        if cfg.label == "FOR_l_568_c_568{sdfg.function_suffix}":
        #            s = sdfg.add_state_before(cfg, "copy_vcflmax")
        #            a0 = s.add_access("gpu_vcflmax")
        #            a1 = s.add_access("vcflmax")
        #            s.add_edge(a0, None, a1, None, dace.Memlet(expr="gpu_vcflmax"))

        # GPUKernelLaunchRestructure().apply_pass(sdfg, {})
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage2.sdfgz", compress=True)

    # Shouldn't have any loops left
    #count_loops(sdfg, verbose=verbose, assert_loops=True)


    if Path(f"gpu_{sdfg_name}_stage3.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage3.sdfgz")
    else:
        sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})
        # This can only be safely applied to selected cases. Skip for now.
        # sdfg.apply_transformations(YoloMapFission)
        # preprocess_tough_nut(sdfg)

        sdfg.validate()


        #sdfg.apply_transformations_repeated(ConditionFusion)
        sdfg.apply_transformations_repeated(ConditionFusion)
        # Some NestedSDFGs with if conditions can be split only after moving up invariant ifs
        # split_map_sdfg(sdfg, True, verbose)
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
        sdfg.simplify()
        prune_unused_inputs_outputs(sdfg)
        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")

        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage3.sdfgz", compress=True)

    if Path(f"gpu_{sdfg_name}_stage4.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage4.sdfgz")
    else:
        propagate_block_var(sdfg)
        sdfg.validate()
        sdfg.simplify()
        sdfg.validate()

        sdfg.validate()
        for s in sdfg.states():
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    if (len(n.map.range) == 1) and n.map.schedule != dace.dtypes.ScheduleType.GPU_Device:
                        b,e,s = n.map.range[0]
                        expr = (e+1-b)//s
                        try:
                            expr = int(expr)
                            # Makes the SDFG invalid, missing inconnectors
                            # MapUnroll().apply_to(sdfg=sdfg, map_entry=n)
                            n.map.unroll = True
                            n.map.unroll_factor = expr
                            n.map.schedule = dace.ScheduleType.Sequential
                        except:
                            pass
                            #n.map.unroll = True
                            #n.map.unroll_factor = int(expr)
                            #n.map.schedule = dace.ScheduleType.Sequential
                    #return self._subgraph_user ?? same
                    #AttributeError: 'TrivialMapElimination' object has no attribute '_subgraph_user'
                    #if MapUnroll().can_be_applied(s, s.node_id(n), sdfg):

        prune_unused_inputs_outputs(sdfg)
        sdfg.apply_transformations_repeated(StateFusion)
        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.NestedSDFG):
                if isinstance(n, dace.nodes.NestedSDFG):
                    n.sdfg.apply_transformations_repeated(StateFusion, permissive=True)
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
        sdfg.simplify()
        prune_unused_inputs_outputs(sdfg)
        InlineSDFGs().apply_pass(sdfg, {})
        k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
        if verbose:
            print(f"Applied MapCollapse {k} time(s)")

        sdfg.simplify()
        # I saw trurthy ifs, propagate those conditions and try to fuse states agian
        propagate_if_cond(sdfg, sdfg, None, None, verbose)
        demote_symbol_to_scalar(sdfg, "tmp_call_18")
        sdfg.apply_transformations_repeated(StateFusion)
        for n, g in sdfg.all_nodes_recursive():
            if isinstance(n, dace.nodes.NestedSDFG):
                if isinstance(n, dace.nodes.NestedSDFG):
                    n.sdfg.apply_transformations_repeated(StateFusion, permissive=True)
        propagate_if_cond(sdfg, sdfg, None, None, verbose)
        sdfg.apply_transformations_repeated(StateFusion)
        sdfg.validate()

        # Breaks the SDFG
        #sdfg.apply_transformations_once_everywhere(MapFusion)
        #for n, g in sdfg.all_nodes_recursive():
        #    if isinstance(n, dace.nodes.NestedSDFG):
        #        if isinstance(n, dace.nodes.NestedSDFG):
        #            n.sdfg.apply_transformations_once_everywhere(MapFusion, permissive=True)

        sdfg.simplify()

        sdfg.validate()
        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage4.sdfgz", compress=True)


    # Validate the SDFG
    sdfg.validate()
    sdfg.save(f"gpu_{sdfg_name}_result.sdfgz", compress=True)
    resulting_sdfgs.append(sdfg)

################################################################################
### Numerically validate the SDFG
################################################################################

# Compile the SDFG
unique_names(resulting_sdfgs)
compile_if_propagated_sdfgs(resulting_sdfgs, gpu=True, release=release)

# check if execution was successful
if os.system(f"./velocity_gpu") != 0:
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
        "GPU",
        gpu=True,
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
