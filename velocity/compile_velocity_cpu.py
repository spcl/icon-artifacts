from pathlib import Path
import shutil
import dace
import os
from dace.transformation.auto_tile.add_compute_element_map import AddComputeElementBlockMap
from dace.transformation.auto_tile.remainder_loop import RemainderLoop
from dace.transformation.auto_tile.remainder_loop_stencil_map import RemainderLoopStencilMap
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

from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from utils import *
from dace.sdfg import utils as sdutil
from utils.move_scalar_to_array import move_scalar_to_array, _tmp_difcoef
import dace
import sympy
from dace.sdfg import infer_types
from dace.sdfg.state import SDFGState, ControlFlowRegion
from dace.sdfg.graph import SubgraphView
from dace.sdfg.propagation import propagate_states
from dace import config, data as dt, dtypes, Memlet, symbolic
from dace.sdfg import SDFG, nodes, graph as gr
from typing import Set, Tuple, Union, List, Iterable, Dict
import warnings

# Transformations
from dace.transformation.dataflow import MapCollapse, TrivialMapElimination, MapFusion, ReduceExpansion
from dace.transformation.interstate import LoopToMap, RefineNestedAccess
from dace.transformation.subgraph.composite import CompositeFusion
from dace.transformation.subgraph import helpers as xfsh
from dace.transformation import helpers as xfh

# Environments
from dace.libraries.blas.environments import intel_mkl as mkl, openblas

# Enumerator
from dace.transformation.estimator.enumeration import GreedyEnumerator

# FPGA AutoOpt
from dace.transformation.auto import fpga as fpga_auto_opt
from utils.reductions import LibNode

# Load SDFG
sdfg_names = [
    "velocity_no_nproma_if_prop_lvn_only_0_istep_1.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_1.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_2.sdfgz",
    "velocity_no_nproma_if_prop_lvn_only_0_istep_2.sdfgz",
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
        # Tests: (Clean Bad Views is mandatory)
        # StructToContainerGroups => OK
        # ContinueToCondition + StructToContainerGroups => OK
        # ContinueToCondition + StructToContainerGroups + Simplify + SymbolProp + Simplify => ? (probably OK, untested)
        # ContinueToCondition + StructToContainerGroups + Simplify + SymbolProp + Simplify + Reduction => OK
        # Need to remove partial view towers (it is illegal and should not happen, but it happens)
        clean_bad_views(sdfg)
        sdfg.apply_transformations_repeated(ContinueToCondition) # To RM continue blocks - this could made into a nice transformation (living in Main)
        # Flattening needs to run before everything
        StructToContainerGroups(
            validate=False,
            save_steps=False,
            verbose=verbose,
            simplify=False,
            interface_with_struct_copy=True,
            interface_to_gpu=False,
            clean_trivial_views=True,
            shallow_copy=False,
            shallow_copy_to_gpu=False
        ).apply_pass(sdfg, {}) # Flattening pass
        sdfg.simplify(skip=["ArrayElimination"])
        SymbolPropagation().apply_pass(sdfg, {}) # Like ConstProp TODO: can be made into a proper transformation
        sdfg.simplify(skip=["ArrayElimination"]) # ArrayElimination breaks the SDFG (might be f2dace related)
        if reduction:
            add_all_reductions(sdfg) # Name matched reductions - major work necessary to have a "detect reduction" pass
        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage1.sdfgz", compress=True)

    if Path(f"cpu_{sdfg_name}_stage2.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage2.sdfgz")
    else:
        sdfg.apply_transformations_repeated(LoopToMap, permissive=True)
        count_symbols_use_defs(sdfg, verbose=verbose, use_assert=True)
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])
        sdfg.apply_transformations_repeated(MapCollapse)
        sdfg.simplify(skip=["ArrayElimination", "InlineSDFG"])

        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage2.sdfgz", compress=True)

    # Shouldn't have any loops left
    count_loops(sdfg, verbose=verbose, use_assert=True)

    if Path(f"cpu_{sdfg_name}_stage3.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage3.sdfgz")
    else:
        sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})

        prune_unused_inputs_outputs(sdfg) # NestedSDFG gets too many inputs/outputs no transformation exists to remove them
        # prune_unused_inputs_outputs_recursive(sdfg) # An error related to ntnd if this is called, removed
        sdfg.validate()

        sdfg.apply_transformations_repeated(ConditionFusion)
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
            sdfg.save(f"cpu_{sdfg_name}_stage3.sdfgz", compress=True)

    count_symbols_use_defs(sdfg, verbose=verbose, use_assert=True)
    # Step 7 OK at this point

    if Path(f"cpu_{sdfg_name}_stage4.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage4.sdfgz")
    else:
        #TODO: Reenable once we know exact issue
        # merge_maps_in_sdfg(sdfg)

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
        # Currently crashes, TODO: fix
        # propagate_if_cond(sdfg, sdfg, None, None, verbose)
        # Prevents some transformations from being applied
        # This is not a symbol anymore (?)
        # TODO: check if this is necessary, if so fix
        # demote_symbol_to_scalar(sdfg, "tmp_call_18")
        sdfg.validate()
        sdfg.simplify(skip=["StateFusion"])
        sdfg.validate()
        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage4.sdfgz", compress=True)
    # So far OK

    if Path(f"cpu_{sdfg_name}_stage5.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_stage5.sdfgz")
    else:
        sdfg.validate()
        prune_unused_inputs_outputs(sdfg)
        sdfg.validate()
        # prune_unused_inputs_outputs_recursive(sdfg) # Missing symbol ntnd error
        sdfg.validate()
        # Hardcoded fixes for the GPU version
        # pre_gpu_fix(sdfg)
        # move_ifs_inside_maps(sdfg)
        flatten_lib, _ = find_node_by_name(sdfg, "flatten")
        deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

        # if nlev and nlevp1 are propagated
        # z_v_grad_w [ tmp_struct_symbol_4, 90, tmp_struct_symbol_5 ] (nproma,p_patch%nlev,p_patch%nblks_e)
        # tmp_struct_symbol_5 == nblks_e
        # zeta [ tmp_struct_symbol_8, 90, tmp_struct_symbol_9 ] (nproma,p_patch%nlev,p_patch%nblks_v)
        # tmp_struct_symbol_9 == nblks_v
        # z_ekinh [ tmp_struct_symbol_10, 90, tmp_struct_symbol_11 ] (nproma,p_patch%nlev,p_patch%nblks_c)
        # tmp_struct_symbol_11 == nblks_c

        # if nlev and nlevp1 are not propagated
        # z_v_grad_w [ tmp_struct_symbol_7, tmp_struct_symbol_8, tmp_struct_symbol_9 ] (nproma,p_patch%nlev,p_patch%nblks_e)
        # tmp_struct_symbol_9 == nblks_e
        # zeta [ tmp_struct_symbol_13, tmp_struct_symbol_14, tmp_struct_symbol_15 ] (nproma,p_patch%nlev,p_patch%nblks_v)
        # tmp_struct_symbol_15 == nblks_v
        # z_ekinh [ tmp_struct_symbol_16, tmp_struct_symbol_17, tmp_struct_symbol_18 ] (nproma,p_patch%nlev,p_patch%nblks_c)
        # tmp_struct_symbol_18 == nblks_c
        move_transients_to_top_level(
            root=sdfg,
            ilifetime=dace.dtypes.AllocationLifetime.SDFG,
            only=["z_w_concorr_mc", "z_w_con_c", "z_v_grad_w",
                  "z_ekinh", "zeta", "z_w_v", "z_w_con_c_full",
                  "levmask", "cfl_clipping"],
            no_dim_change=True,
        )
        move_transients_to_top_level(
            root=sdfg,
            ilifetime=dace.dtypes.AllocationLifetime.SDFG,
            upper_bounds={
                "maxvcfl_arr": "tmp_struct_symbol_11"
            },
            only=["maxvcfl_arr"],
            no_dim_change=False,
            offset=-1,
            set_zero=True,
        )
        move_transients_to_top_level(
            root=sdfg,
            ilifetime=dace.dtypes.AllocationLifetime.SDFG,
            only=["out_val_0"],
            no_dim_change=True,
        )
        if "difcoef" in sdfg.arrays:
            _tmp_difcoef(sdfg)

        # make_arrays_persistent(sdfg)
        # After this we are in GPU mode
        if use_cache:
            sdfg.save(f"cpu_{sdfg_name}_stage5.sdfgz", compress=True)

    sdfg.validate()
    sdfg.save(f"cpu_{sdfg_name}_result.sdfgz", compress=True)
    sdfg = dace.SDFG.from_file(f"cpu_{sdfg_name}_result.sdfgz")
    resulting_sdfgs.append(sdfg)


dace.Config.set('compiler', 'cuda', 'default_block_size', value="256,1,1")

################################################################################
### Numerically validate the SDFG
################################################################################

# for i in {1..5}; do ./velocity_cpu ${i} ${i}; done

# Compile the SDFG
unique_names(resulting_sdfgs)

# Add instrumentation
if instrument:
    # instrument the SDFG
    instrument_sdfg(resulting_sdfgs)

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=False, release=True,
                            instrument=instrument, generate_code=True, lib=False,
                            stage_suffix="stage3") # stage3 if you need clip_count, else None, TODO: improve this

exit()
# check if execution was successful
if os.system(f"./velocity_cpu") != 0:
    # Compare .got and .want files
    exit(1)
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
