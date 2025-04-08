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

from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.dataflow import MapCollapse, MapFusion, TrivialMapElimination
from dace.transformation.passes.to_gpu import ToGPU
from utils import *
from dace.sdfg import utils as sdutil
from utils.move_scalar_to_array import move_scalar_to_array, _tmp_difcoef

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
    if Path(f"gpu_{sdfg_name}_stage1.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage1.sdfgz")
    else:
        # Needed to remove partial view towards (it is illegal and should not happen)
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
            shallow_copy=False,
            shallow_copy_to_gpu=False
        ).apply_pass(sdfg, {})
        sdfg.simplify(skip=["ArrayElimination"])

        # Nproma is not known at compile time anymore
        # TODO: Circumvent this
        # apply_loop_locality_pass(sdfg)

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

        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage2.sdfgz", compress=True)

    # Shouldn't have any loops left
    count_loops(sdfg, verbose=verbose, use_assert=True)

    if Path(f"gpu_{sdfg_name}_stage3.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage3.sdfgz")
    else:
        sdfg.apply_transformations_repeated(MapStateFission, {"allow_transients": True})

        # With kernel launch restructuring we do not collapse and do not need this
        # sdfg.apply_transformations(YoloMapFission)

        # These simplified by DaCe when nblks_c and nblks_v were known to be 2 and nblocks_e was 2
        # Now should not be needed
        #move_transients_to_top_level(
        #    root=sdfg,
        #    upper_bounds={
        #        "z_w_con_c": 2, # TODO: ensure it works with nblocks, and not 2
        #        "maxvcfl_arr": 2, # TODO: ensure it works with nblocks, and not 2
        #        "cfl_clipping": 2, # TODO: ensure it works with nblocks, and not 2
        #        "z_w_concorr_mc": 2, # TODO: ensure it works with nblocks, and not 2
        #        "levmask": 2, # TODO: ensure it works with nblocks, and not 2
        #    },
        #)

        #preprocess_tough_nut(sdfg)
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
        sdfg.validate()
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
        pre_gpu_fix(sdfg)
        move_ifs_inside_maps(sdfg)
        flatten_lib, _ = find_node_by_name(sdfg, "flatten")
        deflatten_lib, _ = find_node_by_name(sdfg, "deflatten")

        # z_v_grad_w [ tmp_struct_symbol_4, 90, tmp_struct_symbol_5 ] (nproma,p_patch%nlev,p_patch%nblks_e)
        # tmp_struct_symbol_5 == nblks_e
        # zeta [ tmp_struct_symbol_8, 90, tmp_struct_symbol_9 ] (nproma,p_patch%nlev,p_patch%nblks_v)
        # tmp_struct_symbol_9 == nblks_v
        # z_ekinh [ tmp_struct_symbol_10, 90, tmp_struct_symbol_11 ] (nproma,p_patch%nlev,p_patch%nblks_c)
        # tmp_struct_symbol_11 == nblks_c
        sdfg.save("before_move.sdfgz", compress=True)
        move_transients_to_top_level(
            root=sdfg,
            ilifetime=dace.dtypes.AllocationLifetime.SDFG,
            only=["z_w_concorr_mc", "z_w_con_c", "z_v_grad_w",
                  "z_ekinh", "zeta", "z_w_v", "z_w_con_c_full",
                  "levmask", "cfl_clipping"],
            no_dim_change=True,
        )
        #cfl clipping 2
        #levelmask 2
        #vcflmax 1
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
            #move_scalar_to_array(
            #    root=sdfg,
            #    name="difcoef",
            #    double_size=True,
            #)
            _tmp_difcoef(sdfg)
        sdfg.save("after_move.sdfgz", compress=True)

        sdfg.validate()
        sdfg.save("gpu_velocity_transients.sdfgz", compress=True)
        ToGPU(verbose=verbose, cpu_library_nodes=[flatten_lib, deflatten_lib], exclude=["vcflmax"]).apply_pass(sdfg, {})
        sdfg.validate()
        if use_cache and verbose:
            sdfg.save(f"gpu_{sdfg_name}_stage4_5.sdfgz", compress=True)
        #
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
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage5.sdfgz", compress=True)

    if Path(f"gpu_{sdfg_name}_stage6.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage6.sdfgz")
    else:
        # Add ThreadBlock map and coarsen a bit
        dace.Config.set('compiler', 'cuda', 'default_block_size', value="256,1,1")
        # Uncomment if you want to tile
        # tile_kernels(sdfg)
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage6.sdfgz", compress=True)

    """
    if Path(f"gpu_{sdfg_name}_stage7.sdfgz").exists() and use_cache:
        sdfg = dace.SDFG.from_file(f"gpu_{sdfg_name}_stage7.sdfgz")
    else:
        # Add ThreadBlock map and coarsen a bit
        permute_index(sdfg, sdfg,
        {
"gpu___CG_p_patch__CG_edges__m_quad_idx": [1, 0, 2],
"gpu___CG_p_int__m_geofac_n2s": [1, 0, 2],
"gpu___CG_p_patch__CG_verts__m_cell_blk": [1, 0, 2],
"gpu___CG_p_patch__CG_verts__m_edge_blk": [1, 0, 2],
"gpu___CG_p_int__m_rbf_vec_coeff_e": [1, 0, 2],
"gpu___CG_p_int__m_cells_aw_verts": [1, 0, 2],
"gpu___CG_p_metrics__m_coeff2_dwdz": [1, 0, 2],
"gpu___CG_p_prog__m_w": [1, 0, 2],
"gpu___CG_p_diag__m_w_concorr_c": [1, 0, 2],
"gpu___CG_p_metrics__m_coeff1_dwdz": [1, 0, 2],
"gpu___CG_p_metrics__m_wgtfac_e": [1, 0, 2],
"gpu___CG_p_patch__CG_edges__m_vertex_idx": [1, 0, 2],
"gpu___CG_p_metrics__m_ddqz_z_full_e": [1, 0, 2],
"gpu___CG_p_patch__CG_edges__m_quad_blk": [1, 0, 2],
"gpu___CG_p_int__m_geofac_rot": [1, 0, 2],
"gpu___CG_p_metrics__m_ddxt_z_full": [1, 0, 2],
"gpu___CG_p_patch__CG_edges__m_vertex_blk": [1, 0, 2],
"gpu___CG_p_diag__m_vn_ie": [1, 0, 2],
"gpu___CG_p_patch__CG_cells__m_neighbor_idx": [1, 0, 2],
"gpu___CG_p_diag__m_vt": [1, 0, 2],
"gpu___CG_p_patch__CG_edges__m_cell_idx": [1, 0, 2],
"gpu___CG_p_metrics__m_coeff_gradekin": [1, 0, 2],
"gpu___CG_p_patch__CG_verts__m_edge_idx": [1, 0, 2],
"gpu___CG_p_metrics__m_wgtfacq_e": [1, 0, 2],
"gpu___CG_p_metrics__m_ddqz_z_half": [1, 0, 2],
"gpu___CG_p_metrics__m_wgtfac_c": [1, 0, 2],
"gpu___CG_p_diag__m_ddt_w_adv_pc": [1, 0, 2, 3],
"gpu___CG_p_prog__m_vn": [1, 0, 2],
"gpu___CG_p_int__m_c_lin_e": [1, 0, 2],
"gpu___CG_p_metrics__m_ddxn_z_full": [1, 0, 2],
"gpu___CG_p_patch__CG_edges__m_cell_blk": [1, 0, 2],
"gpu___CG_p_int__m_geofac_grdiv": [1, 0, 2],
"gpu___CG_p_patch__CG_cells__m_edge_idx": [1, 0, 2],
"gpu___CG_p_patch__CG_cells__m_edge_blk": [1, 0, 2],
"gpu___CG_p_patch__CG_cells__m_neighbor_blk": [1, 0, 2],
"gpu___CG_p_patch__CG_verts__m_cell_idx": [1, 0, 2],
"gpu___CG_p_diag__m_ddt_vn_apc_pc": [1, 0, 2, 3],
"gpu___CG_p_int__m_e_bln_c_s": [1, 0, 2],
"gpu_maxvcfl_arr": [1, 0, 2],
"gpu_z_kin_hor_e": [1, 0, 2],
"gpu_z_w_con_c_full": [1, 0, 2],
"gpu_z_w_v": [1, 0, 2],
"gpu_z_vt_ie": [1, 0, 2],
"gpu_z_w_concorr_me": [1, 0, 2],
"gpu_zeta": [1, 0, 2],
"gpu_z_v_grad_w": [1, 0, 2],
"gpu_z_ekinh": [1, 0, 2],
        })
        #permute_all_maps(sdfg, [1, 0, 2])
        sdfg.validate()
        if use_cache:
            sdfg.save(f"gpu_{sdfg_name}_stage7.sdfgz", compress=True)
        """

    #input_to_gpu(sdfg, "z_w_concorr_me")
    #input_to_gpu(sdfg, "z_kin_hor_e")
    #input_to_gpu(sdfg, "z_vt_ie")
    make_arrays_persistent(sdfg)
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

compile_if_propagated_sdfgs(resulting_sdfgs, gpu=True, release=release, instrument=instrument, generate_code=True, lib=True)

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
