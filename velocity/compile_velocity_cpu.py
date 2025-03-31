import os
import shutil
from pathlib import Path
import dace
from dace.transformation.interstate import (
    LoopToMap,
    ContinueToCondition,
    ConditionFusion,
    StateFusion,
)
from dace.transformation.passes import InlineSDFGs, SymbolPropagation, StructToContainerGroups
from dace.transformation.dataflow import MapCollapse, MapFusion, MapUnroll, TrivialMapElimination
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
                "z_w_con_c": 2,
                "maxvcfl_arr": 2,
                "cfl_clipping": 2,
                "z_w_concorr_mc": 2,
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

    if Path(f"cpu_{sdfg_name}_stage4.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage4.sdfgz")
    else:
        propagate_block_var(sdfg)
        sdfg.validate()
        sdfg.simplify()
        sdfg.validate()
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
        sdfg.validate()
        for s in sdfg.states():
            for n in s.nodes():
                if isinstance(n, dace.nodes.MapEntry):
                    if (len(n.map.range) == 1):
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
    sdfg.save(f"cpu_{sdfg_name}_result.sdfgz", compress=True)
    resulting_sdfgs.append(sdfg)



################################################################################
### Numerically validate the SDFG
################################################################################

if instrument is True:
    # instrument the SDFG
    instrument_sdfg(resulting_sdfgs)

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=False, release=release)

# check if execution was successful
if os.system(f"./velocity_cpu") != 0:
    print("Execution failed")
    exit(1)

if instrument is True:
    # collect reports
    for sdfg in resulting_sdfgs:
        sdfg.save_report(sdfg.get_latest_report_path())
    collect_reports(resulting_sdfgs)

# Compare .got and .want files
compare_got_and_want()


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
