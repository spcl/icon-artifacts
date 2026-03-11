import argparse
from typing import List
import shutil
from pathlib import Path

import dace
from dace.transformation.passes import GPUKernelLaunchRestructure
from dace.transformation.passes.fusion_inline import InlineSDFGs
from dace.transformation.passes.to_gpu import ToGPU
from dace import nodes
from dace.sdfg.sdfg import InterstateEdge
from dace.sdfg.state import CodeBlock, SDFGState

import utils.stages.common as common
from utils.int64_to_int32 import int64_to_int32
from utils.pre_gpu_fixes import make_arrays_persistent
from utils.reassign_vars import reassign_vars
from utils.change_reduction_schedule import change_reduction_schedule
from utils.tile import tile_kernels
from utils.reshape_kernels import reshape_kernels, reshape_kernels_w_coarsening
from utils.hacky_cfl_clipping_related_kernel_removal import hacky_cfl_clipping_related_kernel_removal
from utils.decrease_bitwidth_of_const_arrays import decrease_bitwidth_of_const_arrays, force_decrease_bitwidth_of_nblk_arrays

from utils.profiling_patches import insert_timers_for_profiling, insert_synchronization_for_profiling, insert_event_timers_for_profiling

from utils.assignment_and_copy_kernel_to_memset_and_memcpy import AssignmentAndCopyKernelToMemsetAndMemcpy
from utils.create_profile_sdfg import create_profile_sdfg
STAGE_ID = 8
import os

def update_reductions(sdfg: dace.SDFG, permuted_levmask:bool=False):
    # reads levmask[0:tmp_struct_13, 0:90] (block)
    # for it 46 make it to a block reduction
    # writes to gpu levelmask[0:90]
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry):
            params: List[str] = n.map.params
            if params == ["_for_it_46"]:
                exit_node: dace.nodes.MapExit = g.exit_node(n)
                nds = g.all_nodes_between(n, exit_node)
                src_nodes = {e.src for e in g.in_edges(n)}
                dst_nodes = {e.dst for e in g.out_edges(exit_node)}
                assert len(src_nodes) == 1
                assert len(dst_nodes) == 1
                src_node = src_nodes.pop()
                dst_node = dst_nodes.pop()

                for nd in list(nds) + [n, exit_node]:
                    g.remove_node(nd)
                
                begin = "(replaced_var_3 - 1)"
                end = "(replaced_var_2 - 1)"

                if permuted_levmask:
                    D = "90"
                    N = "tmp_struct_symbol_13"
                    tasklet_code = f"reduce_scan_last_dim(in_gpu_levmask, out_gpu_levelmask, {begin}, {end}, {D}, {N});"
                else:
                    D = "90"
                    N = "tmp_struct_symbol_13"
                    tasklet_code = f"reduce_scan_first_dim(in_gpu_levmask, out_gpu_levelmask, {begin}, {end}, {D}, {N});"
                
                assert isinstance(g, dace.SDFGState)
                t = g.add_tasklet(
                    "red_levmask",
                    {"in_gpu_levmask"},
                    {"out_gpu_levelmask"},
                    code = tasklet_code,
                    language = dace.dtypes.Language.CPP,
                )
                g.add_edge(src_node, None, t, "in_gpu_levmask",
                            dace.Memlet.from_array("gpu_levmask", g.sdfg.arrays["gpu_levmask"]))
                g.add_edge(t, "out_gpu_levelmask", dst_node, None,
                            dace.Memlet.from_array("gpu_levelmask", g.sdfg.arrays["gpu_levelmask"]))

    # reduce_maxZ_to_address  / gpu_maxvcfl_arr -> to full array size
    upded = False
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.Tasklet) and \
            len(g.out_edges(n)) == 1 and \
            len(g.in_edges(n)) == 0 and \
            "i_endidx_var_149" in n.code.as_string and \
            "i_startidx_var_148" in n.code.as_string and \
            "size_reduce_maxZ_to_scalar" in str(n.label) and \
            "size" in n.out_connectors:
            n.code = CodeBlock("size = (tmp_struct_symbol_4 * 88)")
            upded = True
        else:
            if  isinstance(n, dace.nodes.Tasklet) and "size" in n.out_connectors:
                print(n)
                print(n.code.as_string)
    assert upded

def get_used_and_const_arrays(sdfg: dace.SDFG):
    permute_in_states = {s for s in sdfg.all_states() if s.label == "permute_in"}
    permute_out_states = {s for s in sdfg.all_states() if s.label == "permute_out"}
    entry_interface_states = {s for s in sdfg.all_states() if s.label == "entry_interface"}
    exit_interface_states = {
        s for s in sdfg.all_states()
        if s.label == "block" and "deflatten" in {n.label for n in s.nodes()}
    }
    assert len(entry_interface_states) == 1
    assert len(exit_interface_states) == 1

    states = permute_in_states | permute_out_states | entry_interface_states | exit_interface_states
    all_read_arrs = set()
    all_write_arrs = set()

    for s in sdfg.all_states():
        if s in states:
            continue
        read_arrs, write_arrs = s.read_and_write_sets()
        all_read_arrs.update(read_arrs)
        all_write_arrs.update(write_arrs)

    for e in sdfg.all_interstate_edges():
        for k, v in e.data.assignments.items():
            read_arrs = dace.symbolic.symbols_in_code(v, potential_symbols=set(sdfg.arrays.keys()))
            all_read_arrs.update(read_arrs)

    print("All read arrays:\n{")
    for arr in sorted(all_read_arrs):
        print(f'"{arr}",')
    print("}\n")
    print("All written arrays:\n{")
    for arr in sorted(all_write_arrs):
        print(f'"{arr}",')
    print("}\n")


def permute_array_dimensions(sdfg: dace.SDFG):
    get_used_and_const_arrays(sdfg)
    """
    {
    "__CG_global_data__m_nflatlev",
    "__CG_global_data__m_nproma",
    "__CG_global_data__m_nrdmax",
    "__CG_p_patch__CG_cells__m_end_block",
    "__CG_p_patch__CG_cells__m_end_index",
    "__CG_p_patch__CG_cells__m_start_block",
    "__CG_p_patch__CG_cells__m_start_index",
    "__CG_p_patch__CG_edges__m_end_block",
    "__CG_p_patch__CG_edges__m_end_index",
    "__CG_p_patch__CG_edges__m_start_block",
    "__CG_p_patch__CG_edges__m_start_index",
    "__CG_p_patch__CG_verts__m_end_block",
    "__CG_p_patch__CG_verts__m_end_index",
    "__CG_p_patch__CG_verts__m_start_block",
    "__CG_p_patch__CG_verts__m_start_index",
    "cfl_w_limit",
    "dtime",
    "gpu___CG_p_diag__m_ddt_vn_apc_pc",
    "gpu___CG_p_diag__m_ddt_w_adv_pc",
    "gpu___CG_p_diag__m_vn_ie",
    "gpu___CG_p_diag__m_vt",
    "gpu___CG_p_diag__m_w_concorr_c",
    "gpu___CG_p_int__m_c_lin_e",
    "gpu___CG_p_int__m_cells_aw_verts",
    "gpu___CG_p_int__m_e_bln_c_s",
    "gpu___CG_p_int__m_geofac_grdiv",
    "gpu___CG_p_int__m_geofac_n2s",
    "gpu___CG_p_int__m_geofac_rot",
    "gpu___CG_p_int__m_rbf_vec_coeff_e",
    "gpu___CG_p_metrics__m_coeff1_dwdz",
    "gpu___CG_p_metrics__m_coeff2_dwdz",
    "gpu___CG_p_metrics__m_coeff_gradekin",
    "gpu___CG_p_metrics__m_ddqz_z_full_e",
    "gpu___CG_p_metrics__m_ddqz_z_half",
    "gpu___CG_p_metrics__m_ddxn_z_full",
    "gpu___CG_p_metrics__m_ddxt_z_full",
    "gpu___CG_p_metrics__m_wgtfac_c",
    "gpu___CG_p_metrics__m_wgtfac_e",
    "gpu___CG_p_metrics__m_wgtfacq_e",
    "gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask",
    "gpu___CG_p_patch__CG_cells__m_area",
    "gpu___CG_p_patch__CG_cells__m_edge_blk",
    "gpu___CG_p_patch__CG_cells__m_edge_idx",
    "gpu___CG_p_patch__CG_cells__m_neighbor_blk",
    "gpu___CG_p_patch__CG_cells__m_neighbor_idx",
    "gpu___CG_p_patch__CG_edges__m_area_edge",
    "gpu___CG_p_patch__CG_edges__m_cell_blk",
    "gpu___CG_p_patch__CG_edges__m_cell_idx",
    "gpu___CG_p_patch__CG_edges__m_f_e",
    "gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length",
    "gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length",
    "gpu___CG_p_patch__CG_edges__m_quad_blk",
    "gpu___CG_p_patch__CG_edges__m_quad_idx",
    "gpu___CG_p_patch__CG_edges__m_tangent_orientation",
    "gpu___CG_p_patch__CG_edges__m_vertex_blk",
    "gpu___CG_p_patch__CG_edges__m_vertex_idx",
    "gpu___CG_p_patch__CG_verts__m_cell_blk",
    "gpu___CG_p_patch__CG_verts__m_cell_idx",
    "gpu___CG_p_patch__CG_verts__m_edge_blk",
    "gpu___CG_p_patch__CG_verts__m_edge_idx",
    "gpu___CG_p_prog__m_vn",
    "gpu___CG_p_prog__m_w",
    "gpu_cfl_clipping",
    "gpu_levelmask",
    "gpu_levmask",
    "gpu_maxvcfl_arr",
    "gpu_vcflmax",
    "gpu_z_ekinh",
    "gpu_z_kin_hor_e",
    "gpu_z_v_grad_w",
    "gpu_z_vt_ie",
    "gpu_z_w_con_c",
    "gpu_z_w_con_c_full",
    "gpu_z_w_concorr_mc",
    "gpu_z_w_concorr_me",
    "gpu_z_w_v",
    "gpu_zeta",
    "scalfac_exdiff",
    }

    All written arrays:
    {
    "cfl_w_limit",
    "gpu___CG_p_diag__m_ddt_vn_apc_pc",
    "gpu___CG_p_diag__m_ddt_w_adv_pc",
    "gpu___CG_p_diag__m_vn_ie",
    "gpu___CG_p_diag__m_vt",
    "gpu___CG_p_diag__m_w_concorr_c",
    "gpu_cfl_clipping",
    "gpu_levelmask",
    "gpu_levmask",
    "gpu_maxvcfl_arr",
    "gpu_vcflmax",
    "gpu_z_ekinh",
    "gpu_z_kin_hor_e",
    "gpu_z_v_grad_w",
    "gpu_z_vt_ie",
    "gpu_z_w_con_c",
    "gpu_z_w_con_c_full",
    "gpu_z_w_concorr_mc",
    "gpu_z_w_concorr_me",
    "gpu_z_w_v",
    "gpu_zeta",
    "scalfac_exdiff",
    "vcflmax",
    }
    """

    permute_map = {
        # Work arrays — transform A: (nproma, nlev, nblks) → (nlev, nproma, nblks)
        "gpu_z_ekinh":                        [1, 0, 2],
        "gpu_z_kin_hor_e":                    [1, 0, 2],
        "gpu_z_v_grad_w":                     [1, 0, 2],
        "gpu_z_w_v":                          [1, 0, 2],
        "gpu_zeta":                           [1, 0, 2],
        "gpu_z_vt_ie":                        [1, 0, 2],
        "gpu_z_w_concorr_me":                 [1, 0, 2],
        "gpu_z_w_concorr_mc":                 [1, 0],
        "gpu_z_w_con_c_full":                 [1, 0, 2],
        "gpu_z_w_con_c":                      [1, 0],
        "gpu_maxvcfl_arr":                    [1, 0, 2],
        "gpu_cfl_clipping":                   [1, 0],
        "gpu_levmask":                        [1, 0],

        # Prognostic fields — transform A
        "gpu___CG_p_prog__m_vn":                      [1, 0, 2],
        "gpu___CG_p_prog__m_w":                       [1, 0, 2],

        # Diagnostic fields — transform A (3D and 4D)
        "gpu___CG_p_diag__m_vt":                      [1, 0, 2],
        "gpu___CG_p_diag__m_vn_ie":                   [1, 0, 2],
        "gpu___CG_p_diag__m_vn_ie_ubc":               [1, 0, 2],
        "gpu___CG_p_diag__m_w_concorr_c":             [1, 0, 2],
        "gpu___CG_p_diag__m_ddt_vn_apc_pc":           [1, 0, 2, 3],
        "gpu___CG_p_diag__m_ddt_w_adv_pc":            [1, 0, 2, 3],
        "gpu___CG_p_diag__m_ddt_vn_cor_pc":           [1, 0, 2, 3],
        "gpu___CG_p_diag__m_vn_ie_ubc":               [1, 0, 2],

        # Metric fields — transform A
        "gpu___CG_p_metrics__m_wgtfac_e":             [1, 0, 2],
        "gpu___CG_p_metrics__m_wgtfac_c":             [1, 0, 2],
        "gpu___CG_p_metrics__m_ddxn_z_full":          [1, 0, 2],
        "gpu___CG_p_metrics__m_ddxt_z_full":          [1, 0, 2],
        "gpu___CG_p_metrics__m_ddqz_z_half":          [1, 0, 2],
        "gpu___CG_p_metrics__m_ddqz_z_full_e":        [1, 0, 2],
        "gpu___CG_p_metrics__m_coeff1_dwdz":          [1, 0, 2],
        "gpu___CG_p_metrics__m_coeff2_dwdz":          [1, 0, 2],
        # Metric fields — transform B: (nproma, N, nblks) → (N, nproma, nblks)
        # Only accessed on first layer, should be ok
        #"gpu___CG_p_metrics__m_wgtfacq_e":            [1, 0, 2],
        "gpu___CG_p_metrics__m_coeff_gradekin":       [1, 0, 2],

        # Interpolation coefficients — transform B: (nproma, N, nblks) → (N, nproma, nblks)
        "gpu___CG_p_int__m_e_bln_c_s":                [1, 0, 2],
        "gpu___CG_p_int__m_c_lin_e":                  [1, 0, 2],
        "gpu___CG_p_int__m_geofac_n2s":               [1, 0, 2],
        "gpu___CG_p_int__m_geofac_grdiv":             [1, 0, 2],
        "gpu___CG_p_int__m_cells_aw_verts":            [1, 0, 2],
        "gpu___CG_p_int__m_geofac_rot":               [1, 0, 2],


        # Connectivity tables — transform B: (nproma, nblks, N) → (N, nproma, nblks)
        "gpu___CG_p_patch__CG_edges__m_tangent_orientation":    [1, 0],
        "gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length": [1, 0],
        "gpu___CG_p_patch__CG_edges__m_area_edge":              [1, 0],
        "gpu___CG_p_patch__CG_verts__m_cell_blk":         [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_f_e":         [1, 0],
        "gpu___CG_p_patch__CG_edges__m_cell_idx":         [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_cell_blk":         [2, 0, 1],
        "gpu___CG_p_patch__CG_cells__m_edge_idx":         [2, 0, 1],
        "gpu___CG_p_patch__CG_cells__m_edge_blk":         [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_vertex_idx":       [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_vertex_blk":       [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_quad_idx":         [2, 0, 1],
        "gpu___CG_p_patch__CG_edges__m_quad_blk":         [2, 0, 1],
        "gpu___CG_p_patch__CG_cells__m_neighbor_idx":     [2, 0, 1],
        "gpu___CG_p_patch__CG_cells__m_neighbor_blk":     [2, 0, 1],
    }

    inverse_permute_map = {
        k: [p.index(i) for i in range(len(p))]
        for k, p in permute_map.items()
    }

    from dace.transformation.layout.permute_dimensions import PermuteDimensions
    PermuteDimensions(
        permute_map=permute_map,
        add_permute_maps=True,
        use_permute_libnodes=False,
        column_major=True,
    ).apply_pass(sdfg=sdfg, pipeline_results={})


    permute_in_state = {s for s in sdfg.all_states() if s.label == "permute_in"}.pop()
    permute_out_state = {s for s in sdfg.all_states() if s.label == "permute_out"}.pop()

    entry_interface_state = {s for s in sdfg.all_states() if s.label == "entry_interface"}.pop()
    exit_interface_state = {s for s in sdfg.all_states() if s.label == "block" and "deflatten" in {n.label for n in s.nodes()} }.pop()

    from dace.sdfg.construction_utils import move_state_after, move_state_before
    move_state_after(sdfg, permute_in_state, entry_interface_state)
    move_state_before(sdfg, permute_out_state, exit_interface_state)

    # Change names back in interface states
    for s in {entry_interface_state, exit_interface_state}:
        for e in s.edges():
            if e.data.data is not None and e.data.data.startswith("permuted_"):
                e.data.data = e.data.data.removeprefix("permuted_")
                if e.data.data in inverse_permute_map:
                                        
                    # Permute the memlet subset with the inverse
                    new_subset = []
                    permute_indices = inverse_permute_map[e.data.data]
                    for i in range(len(permute_indices)):
                        new_subset.append(e.data.subset[permute_indices[i]])
                    e.data.subset = dace.subsets.Range(new_subset)

        for n in s.data_nodes():
            if n.data is not None and n.data.startswith("permuted_"):
                n.data = n.data.removeprefix("permuted_")

    from dace.transformation.dataflow import MapDimShuffle

    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.MapEntry):
            if len(n.map.params) == 2:
                new_params = list(reversed(n.map.params))
                MapDimShuffle().apply_to(sdfg=g.sdfg, map_entry=n,
                                options={"parameters": new_params})

    sdfg.validate()
    sdfg.save("after_permute.sdfgz", compress=True)



def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    """
    print("Array values that can be lowered: {\n" + "\n".join(
        sorted(
            [f'"{array_name}",' for array_name, array in sdfg.arrays.items() if
            ((array.dtype == dace.int32 or array.dtype == dace.int64) and isinstance(array, dace.data.Array) and not isinstance(array, dace.data.View))
            ]
            )
        ) + "}\n"
    )
    """
    # Apply transformations
    gpu_levmask_desc = sdfg.arrays.get("gpu_levmask")
    print("gpu_levmask shape:", gpu_levmask_desc.shape, "strides:", gpu_levmask_desc.strides)
    """
    PermuteArrayDimensions(
        permute_map={"gpu_levmask": [1, 0]},
        add_permute_maps=False,
    ).apply_pass(sdfg=sdfg, pipeline_results={})
    """

    # Need to fix sizes
    # reduce_maxZ_to_address  / gpu_maxvcfl_arr -> to full array size
    # reduce scan of length 1 ok (cfl clipping)
    # gpu levmask in 88 length map:
    # reads levmask[0:tmp_struct_13, 0:90] (block)
    # for it 46 make it to a block reduction
    # writes to gpu levelmask[0:90]
    # final vcflmax is over blocks it is fine
    do_permute = os.getenv('_PERMUTE_DIMS', '0').lower() in ('1', 'true', 'yes')
    update_reductions(sdfg, do_permute)

    #inverse_strides(sdfg, "gpu_levmask")
    #sdfg.validate()
    #gpu_levmask_desc = sdfg.arrays.get("gpu_levmask")
    #print("gpu_levmask new shape:", gpu_levmask_desc.shape, "new strides:", gpu_levmask_desc.strides)
    #raise Exception("DEBUG: PermuteArrayDimensions applied, check gpu_levmask shape and strides")

    do_reduce_bitwidth = os.getenv('_REDUCE_BITWIDTH_TRANSFORMATION', '0').lower() in ('1', 'true', 'yes')
    if do_reduce_bitwidth:
        # nproma dependent ones
        sdfg = decrease_bitwidth_of_const_arrays(sdfg,
                                        array_names={
                                            "gpu___CG_p_patch__CG_cells__m_edge_idx",
                                            #"gpu___CG_p_patch__CG_cells__m_end_index", #CPU Only
                                            "gpu___CG_p_patch__CG_cells__m_neighbor_idx",
                                            #"gpu___CG_p_patch__CG_cells__m_start_index", #CPU Only
                                            "gpu___CG_p_patch__CG_edges__m_cell_idx",
                                            #"gpu___CG_p_patch__CG_edges__m_end_index", #CPU Only
                                            "gpu___CG_p_patch__CG_edges__m_quad_idx",
                                            #"gpu___CG_p_patch__CG_edges__m_start_index", #CPU Only
                                            "gpu___CG_p_patch__CG_edges__m_vertex_idx",
                                            "gpu___CG_p_patch__CG_verts__m_cell_idx",
                                            "gpu___CG_p_patch__CG_verts__m_edge_idx",
                                            #"gpu___CG_p_patch__CG_verts__m_end_index", #CPU Only
                                            #"gpu___CG_p_patch__CG_verts__m_start_index", #CPU Only
                                        },
                                        assume_can_lower=False,
                                        nproma_name="__CG_global_data__m_nproma")
        # nlock dependent ones
        sdfg = force_decrease_bitwidth_of_nblk_arrays(sdfg,
                                        multi_val_array_names={
                                            #"gpu___CG_p_patch__CG_cells__m_neighbor_blk", #1
                                            "gpu___CG_p_patch__CG_cells__m_edge_blk", #1,2
                                            #"gpu___CG_p_patch__CG_edges__m_cell_blk", #1
                                            "gpu___CG_p_patch__CG_edges__m_quad_blk", #1,2
                                            "gpu___CG_p_patch__CG_edges__m_neighbor_blk", #1,2
                                            #"gpu___CG_p_patch__CG_edges__m_vertex_blk", #1
                                            #"gpu___CG_p_patch__CG_verts__m_cell_blk", #1
                                            "gpu___CG_p_patch__CG_verts__m_edge_blk", #1,2
                                            #"gpu___CG_p_patch__CG_edges__m_neighbor_blk", #1
                                        },
                                        single_val_array_names={
                                            "gpu___CG_p_patch__CG_cells__m_neighbor_blk", #1
                                            #"gpu___CG_p_patch__CG_cells__m_edge_blk", #1,2
                                            "gpu___CG_p_patch__CG_edges__m_cell_blk", #1
                                            #"gpu___CG_p_patch__CG_edges__m_quad_blk", #1,2
                                            #"gpu___CG_p_patch__CG_edges__m_neighbor_blk", #1,2
                                            "gpu___CG_p_patch__CG_edges__m_vertex_blk", #1
                                            "gpu___CG_p_patch__CG_verts__m_cell_blk", #1
                                            #"gpu___CG_p_patch__CG_verts__m_edge_blk", #1,2
                                            "gpu___CG_p_patch__CG_edges__m_neighbor_blk", #1
                                        },
                                        )

    # vertex_blk, cell_blk, cell_neighbor_blk, vertex_neighbor_blk are always 1 if nblocks_c is 1
    # if nblocks_c is 1 then edge_start_block, edge_end_block, edge_blk are 1 or 2 (can do uint8)
    # Force these variables to have lower bitwidths, always

    int64_to_int32(sdfg)
    # start_index and end_index are between [1, nproma] -> ~20k in our data, ~200k in some other cases int16 is -32768, 32767
    # start_block and end_blocks are between [0, nblks] -> usually 1 or 2 as we pass nblocks_c for the science config
    # Force start and end blks to int8?
    # TODO: force start_block and end_block to int8

    # Rm copy/memset kernels with API calls
    # AssignmentAndCopyKernelToMemsetAndMemcpy().apply_pass(sdfg, {})


    # TODO: GPU read-write has unit size of 32-bits, uint8_t won't help unless we tile
    # Assigning a warp to the column is not a very good idea
    # reshape_kernels(sdfg, True)
    # Must be individualized for each kernel
    do_tile = os.getenv('_TILE', '0').lower() in ('1', 'true', 'yes')
    if do_tile:
        x_coarsening = int(os.environ.get("X_COARSENING", 1))
        y_coarsening = int(os.environ.get("Y_COARSENING", 1))
        x_block_size = int(os.environ.get("X_BLOCK_SIZE", 256))
        y_block_size = int(os.environ.get("Y_BLOCK_SIZE", 1))
        y_unroll_factor = int(os.environ.get("Y_UNROLL_FACTOR", 1))
        #reshape_kernels(sdfg)
        reshape_kernels_w_coarsening(sdfg,
                                    x_coarsening=x_coarsening,
                                    y_coarsening=y_coarsening,
                                    x_block_size=x_block_size,
                                    y_block_size=y_block_size,
                                    unroll_x=True,
                                    unroll_x_factor=None,
                                    unroll_y=True,
                                    unroll_y_factor=y_unroll_factor,)
    #tile_kernels(sdfg)
    #sdfg.simplify()
    # Sync first
    insert_synchronization_for_profiling(sdfg)
    insert_timers_for_profiling(sdfg)
    #insert_event_timers_for_profiling(sdfg)
    #set_default_stream(sdfg)
    sdfg.validate()

    # Permute arrays
    do_permute = os.getenv('_PERMUTE_DIMS', '0').lower() in ('1', 'true', 'yes')

    if do_permute:
        permute_array_dimensions(sdfg)

    do_profile = os.getenv('_PROFILE', '0').lower() in ('1', 'true', 'yes')
    if do_profile:
        create_profile_sdfg(sdfg)


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
            from sc26_layout.extract_gpu_kernel import add_symbols
            add_symbols(sdfg)
            sdfg.validate()
            nsdfgs[name] = sdfg

        do_permute = os.getenv('_PERMUTE_DIMS', '0').lower() in ('1', 'true', 'yes')

        if do_permute:
            common.compile_action(STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_dim_permuted", main_name="main_per.cu", tblock_dim="96,2,1",
            stage_suffix="_permuted")
        else:
            common.compile_action(STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_unpermuted", main_name="main_per.cu", tblock_dim="256,1,1",
            stage_suffix="_unpermuted")

if __name__ == "__main__":
    main()