import re
import dace
import copy

from dace.sdfg.nodes import CodeBlock


# Same order as the call
velocity_name_mapping = {
  '__CG_global_data__m_nflatlev': 'in___CG_global_data__m_nflatlev',
  '__CG_global_data__m_nrdmax': 'in___CG_global_data__m_nrdmax',
  '__CG_p_diag__m_ddt_vn_apc_pc': 'in___CG_p_nh__CG_diag__m_ddt_vn_apc_pc',
  '__CG_p_diag__m_ddt_w_adv_pc': 'in___CG_p_nh__CG_diag__m_ddt_w_adv_pc',
  '__CG_p_diag__m_vn_ie': 'in___CG_p_nh__CG_diag__m_vn_ie',
  '__CG_p_diag__m_vt': 'in___CG_p_nh__CG_diag__m_vt',
  '__CG_p_diag__m_w_concorr_c': 'in___CG_p_nh__CG_diag__m_w_concorr_c',
  '__CG_p_int__m_c_lin_e': 'in___CG_p_int__m_c_lin_e',
  '__CG_p_int__m_cells_aw_verts': 'in___CG_p_int__m_cells_aw_verts',
  '__CG_p_int__m_e_bln_c_s': 'in___CG_p_int__m_e_bln_c_s',
  '__CG_p_int__m_geofac_grdiv': 'in___CG_p_int__m_geofac_grdiv',
  '__CG_p_int__m_geofac_n2s': 'in___CG_p_int__m_geofac_n2s',
  '__CG_p_int__m_geofac_rot': 'in___CG_p_int__m_geofac_rot',
  '__CG_p_int__m_rbf_vec_coeff_e': 'in___CG_p_int__m_rbf_vec_coeff_e',
  '__CG_p_metrics__m_coeff1_dwdz': 'in___CG_p_nh__CG_metrics__m_coeff1_dwdz',
  '__CG_p_metrics__m_coeff2_dwdz': 'in___CG_p_nh__CG_metrics__m_coeff2_dwdz',
  '__CG_p_metrics__m_coeff_gradekin': 'in___CG_p_nh__CG_metrics__m_coeff_gradekin',
  '__CG_p_metrics__m_ddqz_z_full_e': 'in___CG_p_nh__CG_metrics__m_ddqz_z_full_e',
  '__CG_p_metrics__m_ddqz_z_half': 'in___CG_p_nh__CG_metrics__m_ddqz_z_half',
  '__CG_p_metrics__m_ddxn_z_full': 'in___CG_p_nh__CG_metrics__m_ddxn_z_full',
  '__CG_p_metrics__m_ddxt_z_full': 'in___CG_p_nh__CG_metrics__m_ddxt_z_full',
  '__CG_p_metrics__m_wgtfac_c': 'in___CG_p_nh__CG_metrics__m_wgtfac_c',
  '__CG_p_metrics__m_wgtfac_e': 'in___CG_p_nh__CG_metrics__m_wgtfac_e',
  '__CG_p_metrics__m_wgtfacq_e': 'in___CG_p_nh__CG_metrics__m_wgtfacq_e',
  '__CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask': 'in___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask',
  '__CG_p_patch__CG_cells__m_area': 'in___CG_p_patch__CG_cells__m_area',
  '__CG_p_patch__CG_cells__m_edge_blk': 'in___CG_p_patch__CG_cells__m_edge_blk',
  '__CG_p_patch__CG_cells__m_edge_idx': 'in___CG_p_patch__CG_cells__m_edge_idx',
  '__CG_p_patch__CG_cells__m_end_block': 'in___CG_p_patch__CG_cells__m_end_block',
  '__CG_p_patch__CG_cells__m_end_index': 'in___CG_p_patch__CG_cells__m_end_index',
  '__CG_p_patch__CG_cells__m_neighbor_blk': 'in___CG_p_patch__CG_cells__m_neighbor_blk',
  '__CG_p_patch__CG_cells__m_neighbor_idx': 'in___CG_p_patch__CG_cells__m_neighbor_idx',
  '__CG_p_patch__CG_cells__m_start_block': 'in___CG_p_patch__CG_cells__m_start_block',
  '__CG_p_patch__CG_cells__m_start_index': 'in___CG_p_patch__CG_cells__m_start_index',
  '__CG_p_patch__CG_edges__m_area_edge': 'in___CG_p_patch__CG_edges__m_area_edge',
  '__CG_p_patch__CG_edges__m_cell_blk': 'in___CG_p_patch__CG_edges__m_cell_blk',
  '__CG_p_patch__CG_edges__m_cell_idx': 'in___CG_p_patch__CG_edges__m_cell_idx',
  '__CG_p_patch__CG_edges__m_end_block': 'in___CG_p_patch__CG_edges__m_end_block',
  '__CG_p_patch__CG_edges__m_end_index': 'in___CG_p_patch__CG_edges__m_end_index',
  '__CG_p_patch__CG_edges__m_f_e': 'in___CG_p_patch__CG_edges__m_f_e',
  '__CG_p_patch__CG_edges__m_inv_dual_edge_length': 'in___CG_p_patch__CG_edges__m_inv_dual_edge_length',
  '__CG_p_patch__CG_edges__m_inv_primal_edge_length': 'in___CG_p_patch__CG_edges__m_inv_primal_edge_length',
  '__CG_p_patch__CG_edges__m_quad_blk': 'in___CG_p_patch__CG_edges__m_quad_blk',
  '__CG_p_patch__CG_edges__m_quad_idx': 'in___CG_p_patch__CG_edges__m_quad_idx',
  '__CG_p_patch__CG_edges__m_start_block': 'in___CG_p_patch__CG_edges__m_start_block',
  '__CG_p_patch__CG_edges__m_start_index': 'in___CG_p_patch__CG_edges__m_start_index',
  '__CG_p_patch__CG_edges__m_tangent_orientation': 'in___CG_p_patch__CG_edges__m_tangent_orientation',
  '__CG_p_patch__CG_edges__m_vertex_blk': 'in___CG_p_patch__CG_edges__m_vertex_blk',
  '__CG_p_patch__CG_edges__m_vertex_idx': 'in___CG_p_patch__CG_edges__m_vertex_idx',
  '__CG_p_patch__CG_verts__m_cell_blk': 'in___CG_p_patch__CG_verts__m_cell_blk',
  '__CG_p_patch__CG_verts__m_cell_idx': 'in___CG_p_patch__CG_verts__m_cell_idx',
  '__CG_p_patch__CG_verts__m_edge_blk': 'in___CG_p_patch__CG_verts__m_edge_blk',
  '__CG_p_patch__CG_verts__m_edge_idx': 'in___CG_p_patch__CG_verts__m_edge_idx',
  '__CG_p_patch__CG_verts__m_end_block': 'in___CG_p_patch__CG_verts__m_end_block',
  '__CG_p_patch__CG_verts__m_end_index': 'in___CG_p_patch__CG_verts__m_end_index',
  '__CG_p_patch__CG_verts__m_start_block': 'in___CG_p_patch__CG_verts__m_start_block',
  '__CG_p_patch__CG_verts__m_start_index': 'in___CG_p_patch__CG_verts__m_start_index',
  '__CG_p_prog__m_vn': 'in___CG_p_nh_prog_nnew__m_vn',
  '__CG_p_prog__m_w': 'in___CG_p_nh_prog_nnew__m_w',
  'global_data': 'in_global_data',
  'p_diag': 'in_p_nh->diag',
  'p_int': 'in_p_int',
  'p_metrics': 'in_p_nh->metrics',
  'p_patch': 'in_p_patch',
  'p_prog': 'in_p_nh_prog_nnew',
  'z_kin_hor_e': 'in_z_kin_hor_e',
  'z_vt_ie': 'in_z_vt_ie',
  'z_w_concorr_me': 'in_z_w_concorr_me',
  '__CG_global_data__m_nproma': 'in___CG_global_data__m_nproma',
  '__CG_p_diag__m_max_vcfl_dyn': 'in___CG_p_nh__CG_diag__m_max_vcfl_dyn',
  '__f2dace_A_z_kin_hor_e_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_kin_hor_e_d_1_s': 'in_p_patch->nlev',
  '__f2dace_A_z_vt_ie_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_vt_ie_d_1_s': 'in_p_patch->nlev',
  '__f2dace_A_z_w_concorr_me_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_w_concorr_me_d_1_s': 'in_p_patch->nlev',
  '__f2dace_OA_z_kin_hor_e_d_0_s': '1',
  '__f2dace_OA_z_kin_hor_e_d_1_s': '1',
  '__f2dace_OA_z_kin_hor_e_d_2_s': '1',
  '__f2dace_OA_z_vt_ie_d_0_s': '1',
  '__f2dace_OA_z_vt_ie_d_1_s': '1',
  '__f2dace_OA_z_vt_ie_d_2_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_0_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_1_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_2_s': '1',
  'dt_linintp_ubc': 'in_dt_linintp_ubc',
  'dtime': 'in_dtime',
  'istep': 'in_istep',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': 'in_ntnd',
}

velocity_gpu_name_mapping = {
  '__CG_global_data__m_nflatlev': 'in___CG_global_data__m_nflatlev',
  '__CG_global_data__m_nrdmax': 'in___CG_global_data__m_nrdmax',
  '__CG_p_patch__CG_cells__m_end_block': 'in___CG_p_patch__CG_cells__m_end_block',
  '__CG_p_patch__CG_cells__m_end_index': 'in___CG_p_patch__CG_cells__m_end_index',
  '__CG_p_patch__CG_cells__m_start_block': 'in___CG_p_patch__CG_cells__m_start_block',
  '__CG_p_patch__CG_cells__m_start_index': 'in___CG_p_patch__CG_cells__m_start_index',
  '__CG_p_patch__CG_edges__m_end_block': 'in___CG_p_patch__CG_edges__m_end_block',
  '__CG_p_patch__CG_edges__m_end_index': 'in___CG_p_patch__CG_edges__m_end_index',
  '__CG_p_patch__CG_edges__m_start_block': 'in___CG_p_patch__CG_edges__m_start_block',
  '__CG_p_patch__CG_edges__m_start_index': 'in___CG_p_patch__CG_edges__m_start_index',
  '__CG_p_patch__CG_verts__m_end_block': 'in___CG_p_patch__CG_verts__m_end_block',
  '__CG_p_patch__CG_verts__m_end_index': 'in___CG_p_patch__CG_verts__m_end_index',
  '__CG_p_patch__CG_verts__m_start_block': 'in___CG_p_patch__CG_verts__m_start_block',
  '__CG_p_patch__CG_verts__m_start_index': 'in___CG_p_patch__CG_verts__m_start_index',
  'global_data': 'in_global_data',
  'gpu___CG_p_diag__m_ddt_vn_apc_pc': 'in_gpu___CG_p_nh__CG_diag__m_ddt_vn_apc_pc',
  'gpu___CG_p_diag__m_ddt_w_adv_pc': 'in_gpu___CG_p_nh__CG_diag__m_ddt_w_adv_pc',
  'gpu___CG_p_diag__m_vn_ie': 'in_gpu___CG_p_nh__CG_diag__m_vn_ie',
  'gpu___CG_p_diag__m_vt': 'in_gpu___CG_p_nh__CG_diag__m_vt',
  'gpu___CG_p_diag__m_w_concorr_c': 'in_gpu___CG_p_nh__CG_diag__m_w_concorr_c',
  'gpu___CG_p_int__m_c_lin_e': 'in_gpu___CG_p_int__m_c_lin_e',
  'gpu___CG_p_int__m_cells_aw_verts': 'in_gpu___CG_p_int__m_cells_aw_verts',
  'gpu___CG_p_int__m_e_bln_c_s': 'in_gpu___CG_p_int__m_e_bln_c_s',
  'gpu___CG_p_int__m_geofac_grdiv': 'in_gpu___CG_p_int__m_geofac_grdiv',
  'gpu___CG_p_int__m_geofac_n2s': 'in_gpu___CG_p_int__m_geofac_n2s',
  'gpu___CG_p_int__m_geofac_rot': 'in_gpu___CG_p_int__m_geofac_rot',
  'gpu___CG_p_int__m_rbf_vec_coeff_e': 'in_gpu___CG_p_int__m_rbf_vec_coeff_e',
  'gpu___CG_p_metrics__m_coeff1_dwdz': 'in_gpu___CG_p_nh__CG_metrics__m_coeff1_dwdz',
  'gpu___CG_p_metrics__m_coeff2_dwdz': 'in_gpu___CG_p_nh__CG_metrics__m_coeff2_dwdz',
  'gpu___CG_p_metrics__m_coeff_gradekin': 'in_gpu___CG_p_nh__CG_metrics__m_coeff_gradekin',
  'gpu___CG_p_metrics__m_ddqz_z_full_e': 'in_gpu___CG_p_nh__CG_metrics__m_ddqz_z_full_e',
  'gpu___CG_p_metrics__m_ddqz_z_half': 'in_gpu___CG_p_nh__CG_metrics__m_ddqz_z_half',
  'gpu___CG_p_metrics__m_ddxn_z_full': 'in_gpu___CG_p_nh__CG_metrics__m_ddxn_z_full',
  'gpu___CG_p_metrics__m_ddxt_z_full': 'in_gpu___CG_p_nh__CG_metrics__m_ddxt_z_full',
  'gpu___CG_p_metrics__m_wgtfac_c': 'in_gpu___CG_p_nh__CG_metrics__m_wgtfac_c',
  'gpu___CG_p_metrics__m_wgtfac_e': 'in_gpu___CG_p_nh__CG_metrics__m_wgtfac_e',
  'gpu___CG_p_metrics__m_wgtfacq_e': 'in_gpu___CG_p_nh__CG_metrics__m_wgtfacq_e',
  'gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask': 'in_gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask',
  'gpu___CG_p_patch__CG_cells__m_area': 'in_gpu___CG_p_patch__CG_cells__m_area',
  'gpu___CG_p_patch__CG_cells__m_edge_blk': 'in_gpu___CG_p_patch__CG_cells__m_edge_blk',
  'gpu___CG_p_patch__CG_cells__m_edge_idx': 'in_gpu___CG_p_patch__CG_cells__m_edge_idx',
  'gpu___CG_p_patch__CG_cells__m_neighbor_blk': 'in_gpu___CG_p_patch__CG_cells__m_neighbor_blk',
  'gpu___CG_p_patch__CG_cells__m_neighbor_idx': 'in_gpu___CG_p_patch__CG_cells__m_neighbor_idx',
  'gpu___CG_p_patch__CG_edges__m_area_edge': 'in_gpu___CG_p_patch__CG_edges__m_area_edge',
  'gpu___CG_p_patch__CG_edges__m_cell_blk': 'in_gpu___CG_p_patch__CG_edges__m_cell_blk',
  'gpu___CG_p_patch__CG_edges__m_cell_idx': 'in_gpu___CG_p_patch__CG_edges__m_cell_idx',
  'gpu___CG_p_patch__CG_edges__m_f_e': 'in_gpu___CG_p_patch__CG_edges__m_f_e',
  'gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length': 'in_gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length',
  'gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length': 'in_gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length',
  'gpu___CG_p_patch__CG_edges__m_quad_blk': 'in_gpu___CG_p_patch__CG_edges__m_quad_blk',
  'gpu___CG_p_patch__CG_edges__m_quad_idx': 'in_gpu___CG_p_patch__CG_edges__m_quad_idx',
  'gpu___CG_p_patch__CG_edges__m_tangent_orientation': 'in_gpu___CG_p_patch__CG_edges__m_tangent_orientation',
  'gpu___CG_p_patch__CG_edges__m_vertex_blk': 'in_gpu___CG_p_patch__CG_edges__m_vertex_blk',
  'gpu___CG_p_patch__CG_edges__m_vertex_idx': 'in_gpu___CG_p_patch__CG_edges__m_vertex_idx',
  'gpu___CG_p_patch__CG_verts__m_cell_blk': 'in_gpu___CG_p_patch__CG_verts__m_cell_blk',
  'gpu___CG_p_patch__CG_verts__m_cell_idx': 'in_gpu___CG_p_patch__CG_verts__m_cell_idx',
  'gpu___CG_p_patch__CG_verts__m_edge_blk': 'in_gpu___CG_p_patch__CG_verts__m_edge_blk',
  'gpu___CG_p_patch__CG_verts__m_edge_idx': 'in_gpu___CG_p_patch__CG_verts__m_edge_idx',
  'gpu___CG_p_prog__m_vn': 'in_gpu___CG_p_nh_prog_nnew__m_vn',
  'gpu___CG_p_prog__m_w': 'in_gpu___CG_p_nh_prog_nnew__m_w',
  'p_diag': 'in_p_nh->diag',
  'p_int': 'in_p_int',
  'p_metrics': 'in_p_nh->metrics',
  'p_patch': 'in_p_patch',
  'p_prog': 'in_p_nh_prog_nnew',
  'z_kin_hor_e': 'in_z_kin_hor_e',
  'z_vt_ie': 'in_z_vt_ie',
  'z_w_concorr_me': 'in_z_w_concorr_me',
  '__CG_global_data__m_nproma': 'in___CG_global_data__m_nproma',
  '__CG_p_diag__m_max_vcfl_dyn': 'in___CG_p_nh__CG_diag__m_max_vcfl_dyn',
  '__f2dace_A_z_kin_hor_e_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_kin_hor_e_d_1_s': 'in_p_patch->nlev',
  '__f2dace_A_z_vt_ie_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_vt_ie_d_1_s': 'in_p_patch->nlev',
  '__f2dace_A_z_w_concorr_me_d_0_s': 'in_global_data->nproma',
  '__f2dace_A_z_w_concorr_me_d_1_s': 'in_p_patch->nlev',
  '__f2dace_OA_z_kin_hor_e_d_0_s': '1',
  '__f2dace_OA_z_kin_hor_e_d_1_s': '1',
  '__f2dace_OA_z_kin_hor_e_d_2_s': '1',
  '__f2dace_OA_z_vt_ie_d_0_s': '1',
  '__f2dace_OA_z_vt_ie_d_1_s': '1',
  '__f2dace_OA_z_vt_ie_d_2_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_0_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_1_s': '1',
  '__f2dace_OA_z_w_concorr_me_d_2_s': '1',
  'dt_linintp_ubc': 'in_dt_linintp_ubc',
  'dtime': 'in_dtime',
  'istep': 'in_istep',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': 'in_ntnd',
}

non_const_data = {
    "__CG_p_prog__m_w",
    "__CG_p_prog__m_vn",
    "__CG_p_diag__m_max_vcfl_dyn",
    "__CG_p_metrics__m_ddqz_z_full_e",
    "__CG_p_metrics__m_ddqz_z_half",
    "__CG_p_metrics__m_coeff_gradekin",
    "__CG_p_int__m_geofac_grdiv",
    "__CG_p_int__m_e_bln_c_s",
    "__CG_p_int__m_c_lin_e",
    "__CG_p_diag__m_w_concorr_c",
    "__CG_p_diag__m_vn_ie",
    "__CG_p_diag__m_vt",
    "__CG_p_diag__m_ddt_vn_apc_pc",
}


non_const_scalar_data = {
    "__CG_p_diag__m_max_vcfl_dyn",
}


code_template = """
auto* in_p_diag = in_p_nh -> diag;
auto* in_p_metrics = in_p_nh -> metrics;
auto in_ldeepatmo = in_global_data -> ldeepatmo;
velocity_tendencies{gpu_suffix}(
    {input_args}
);
out_global_data = in_global_data;
out_p_nh = in_p_nh;
out_p_int = in_p_int;
out_p_patch = in_p_patch;
out_p_prog = in_p_prog;
{output_assignments}
"""

def reinject_velocity_shim(
    sdfg: dace.SDFG
):
    velocity_tasklet = None
    velocity_state = None
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.Tasklet) and ("velocity_tendencies" in node.name or "velocity_tendencies" in node.label):
                velocity_tasklet = node
                velocity_state = state
                break
        if velocity_tasklet is not None:
            break

    if velocity_tasklet is None:
        return

    if "predictor" in sdfg.name:
        in_istep = f"1"
    else:
        in_istep = f"2"
    if "in_lvn_only" in velocity_tasklet.in_connectors:
        in_lvn_only = f"in_lvn_only"
    else:
        in_lvn_only = f"0"

    velocity_name_mapping_local = copy.deepcopy(velocity_name_mapping)
    velocity_name_mapping_local["istep"] = in_istep
    velocity_name_mapping_local["lvn_only"] = in_lvn_only

    required_in_conns = set()
    for name in velocity_name_mapping_local.values():
        if "->" in name:
            lname = name.split("->")[0].strip()
        else:
            lname = name
        if lname.startswith("in_"):
            required_in_conns.add(lname)

    # Add all missing in connectors (full range)
    new_in_conns = required_in_conns - set(velocity_tasklet.in_connectors)
    for new_in_conn in new_in_conns:
        data_name = new_in_conn[3:]  # Remove 'in_' prefix
        if (new_in_conn not in velocity_tasklet.in_connectors and
            data_name in state.sdfg.arrays):
            velocity_tasklet.add_in_connector(new_in_conn)
            dataaccess = state.add_access(data_name)
            state.add_edge(
                dataaccess,
                None,
                velocity_tasklet,
                new_in_conn,
                dace.memlet.Memlet.from_array(
                    data_name,
                    state.sdfg.arrays[data_name]
                )
            )

    input_args_str_list = []
    for key, val in velocity_name_mapping_local.items():
        input_args_str_list.append(f"{val} /* = {key} */")
    input_args_str = ",\n    ".join(input_args_str_list)

    # Add all missing out connectors (full range), for non const data
    for key in non_const_data:
        out_name = "out_" + velocity_name_mapping_local[key][3:]  # Remove 'in_' prefix
        if out_name not in velocity_tasklet.out_connectors:
            velocity_tasklet.add_out_connector(out_name)
            data_name = out_name[4:]
            dataaccess = state.add_access(data_name)
            state.add_edge(
                velocity_tasklet,
                out_name,
                dataaccess,
                None,
                dace.memlet.Memlet.from_array(
                    data_name,
                    state.sdfg.arrays[data_name]
                )
            )

    output_assignments_list = []
    for key in non_const_scalar_data:
        in_name = velocity_name_mapping_local[key]
        out_name = "out_" + in_name[3:]
        output_assignments_list.append(f"{out_name} = {in_name};")
    for key in non_const_data:
        in_name = velocity_name_mapping_local[key]
        out_name = "out_" + in_name[3:]
        output_assignments_list.append(f"{out_name} = {in_name};")
    output_assignments_str = "\n    ".join(output_assignments_list)

    code_str = code_template.format(
        input_args=input_args_str,
        output_assignments=output_assignments_str,
        gpu_suffix=""
    )

    velocity_tasklet.code = CodeBlock(code_str, language=dace.dtypes.Language.CPP)

    # Reinjecting the old (struct only) velocity -> flattened velocity tasklet
    # It means: if existing exit call, do not do anything else add it
    has_gpu_exit_call = any([("exit_velocity_tendencies_gpu();" in v.as_string) for v in sdfg.exit_code.values()])
    has_cpu_exit_call = any([("exit_velocity_tendencies();" in v.as_string) for v in sdfg.exit_code.values()])
    assert not has_gpu_exit_call, "GPU reinject velocity tasklet should not be already here if calling this function."
    if not has_cpu_exit_call:
        sdfg.append_exit_code(
            cpp_code="exit_velocity_tendencies();",
        )
    """
    has_gpu_init_call = any([
        re.search(r'\binit_velocity_tendencies_gpu\(.*?\);', v.as_string)
        for v in sdfg.init_code.values()
    ])

    has_cpu_init_call = any([
        re.search(r'\binit_velocity_tendencies\(.*?\);', v.as_string)
        for v in sdfg.init_code.values()
    ])
    assert not has_gpu_init_call, "GPU init velocity tasklet should not be already here if calling this function."
    if not has_cpu_init_call:
        sdfg.append_init_code(
            cpp_code=f"init_velocity_tendencies({input_args_str});",
        )
    """

def reinject_velocity_shim_gpu(
    sdfg: dace.SDFG
):
    velocity_tasklet = None
    velocity_state = None
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.Tasklet) and ("velocity_tendencies" in node.name or "velocity_tendencies" in node.label):
                velocity_tasklet = node
                velocity_state = state
                break
        if velocity_tasklet is not None:
            break

    if velocity_tasklet is None:
        return

    if "predictor" in sdfg.name:
        in_istep = f"1"
    else:
        in_istep = f"2"
    if "in_lvn_only" in velocity_tasklet.in_connectors:
        in_lvn_only = f"in_lvn_only"
    else:
        in_lvn_only = f"0"

    velocity_gpu_name_mapping_local = copy.deepcopy(velocity_gpu_name_mapping)
    velocity_gpu_name_mapping_local["istep"] = in_istep
    velocity_gpu_name_mapping_local["lvn_only"] = in_lvn_only

    required_in_conns = set()
    for name in velocity_gpu_name_mapping_local.values():
        if "->" in name:
            lname = name.split("->")[0].strip()
        else:
            lname = name
        if lname.startswith("in_"):
            required_in_conns.add(lname)

    # Replace all in connectors, first remove all arrays
    for ie in velocity_state.in_edges(velocity_tasklet):
        if isinstance(sdfg.arrays[ie.src.data], dace.data.Array):
            velocity_state.remove_edge(ie)
            if velocity_state.degree(ie.src) == 0:
                velocity_state.remove_node(ie.src)
            velocity_tasklet.remove_in_connector(ie.dst_conn)

    # Add all missing in connectors (full range)
    new_in_conns = required_in_conns - set(velocity_tasklet.in_connectors)
    for new_in_conn in new_in_conns:
        data_name = new_in_conn[3:]
        # If not a container group data
        if not data_name.startswith("gpu___CG") and not data_name.startswith("__CG"):
            if data_name.startswith("z_"):
                data_name = "gpu_" + data_name
        if (new_in_conn not in velocity_tasklet.in_connectors and
            data_name in state.sdfg.arrays):
            velocity_tasklet.add_in_connector(new_in_conn)
            dataaccess = state.add_access(data_name)
            state.add_edge(
                dataaccess,
                None,
                velocity_tasklet,
                new_in_conn,
                dace.memlet.Memlet.from_array(
                    data_name,
                    state.sdfg.arrays[data_name]
                )
            )

    input_args_str_list = []
    for key, val in velocity_gpu_name_mapping_local.items():
        input_args_str_list.append(f"{val} /* = {key} */")
    input_args_str = ",\n    ".join(input_args_str_list)

    # Replace all out connectors, first remove all arrays
    for oe in velocity_state.out_edges(velocity_tasklet):
        if isinstance(sdfg.arrays[oe.dst.data], dace.data.Array):
            velocity_state.remove_edge(oe)
            if velocity_state.degree(oe.dst) == 0:
                velocity_state.remove_node(oe.dst)
            velocity_tasklet.remove_out_connector(oe.src_conn)

    # Add all missing out connectors (full range), for non const data
    for key in non_const_data:
        if key == "__CG_p_diag__m_max_vcfl_dyn":
            continue  # This is a scalar, not an array
        out_name = "out_" + velocity_gpu_name_mapping_local["gpu_" + key][3:]  # Remove 'in_' prefix
        if out_name not in velocity_tasklet.out_connectors:
            velocity_tasklet.add_out_connector(out_name)
            data_name = "gpu_" + out_name[4:] if not out_name[4:].startswith("gpu_") else out_name[4:]  # Remove 'out_' prefix
            dataaccess = state.add_access(data_name)
            state.add_edge(
                velocity_tasklet,
                out_name,
                dataaccess,
                None,
                dace.memlet.Memlet.from_array(
                    data_name,
                    state.sdfg.arrays[data_name]
                )
            )

    output_assignments_list = []
    for key in non_const_scalar_data:
        in_name = velocity_gpu_name_mapping_local[key]
        out_name = "out_" + in_name[3:]
        output_assignments_list.append(f"{out_name} = {in_name};")
    for key in non_const_data:
        if key == "__CG_p_diag__m_max_vcfl_dyn":
            continue  # This is a scalar, not an array
        in_name = velocity_gpu_name_mapping_local["gpu_" + key]
        out_name = "out_" + in_name[3:]
        output_assignments_list.append(f"{out_name} = {in_name};")
    output_assignments_str = "\n    ".join(output_assignments_list)

    code_str = code_template.format(
        input_args=input_args_str,
        output_assignments=output_assignments_str,
        gpu_suffix="_gpu"
    )

    velocity_tasklet.code = CodeBlock(code_str, language=dace.dtypes.Language.CPP)

    # Reinjecting the CPU velocity -> GPU velocity
    # It means: if existing remove CPU exit and add GPU exit if nto already there
    has_gpu_exit_call = any([("exit_velocity_tendencies_gpu();" in v.as_string) for v in sdfg.exit_code.values()])
    has_cpu_exit_call = any([("exit_velocity_tendencies();" in v.as_string) for v in sdfg.exit_code.values()])
    if has_cpu_exit_call:
        # Remove the CPU exit call, we are replacing it with the GPU one
        sdfg.exit_code = {k: CodeBlock(v.as_string.replace("exit_velocity_tendencies();", "")) for k, v in sdfg.exit_code.items()}

    if not has_gpu_exit_call:
        sdfg.append_exit_code(
            cpp_code="exit_velocity_tendencies_gpu();",
        )
    """
    has_gpu_init_call = any([
        re.search(r'\binit_velocity_tendencies_gpu\(.*?\);', v.as_string)
        for v in sdfg.init_code.values()
    ])

    has_cpu_init_call = any([
        re.search(r'\binit_velocity_tendencies\(.*?\);', v.as_string)
        for v in sdfg.init_code.values()
    ])
    if has_cpu_init_call:
        # Remove the CPU init call, we are replacing it with the GPU one
        pattern = r'\binit_velocity_tendencies_gpu\s*\(.*?\);?'
        sdfg.init_code = {
            k: CodeBlock(re.sub(pattern, '', v.as_string))
            for k, v in sdfg.init_code.items()
        }

    if not has_gpu_init_call:
        sdfg.append_init_code(
            cpp_code=f"init_velocity_tendencies_gpu({input_args_str});",
        )
    """