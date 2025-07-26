import re
import dace
import copy

from dace.sdfg.nodes import CodeBlock


# Same order as the call
gpu_name_mapping_corrector_pre = {
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
  'istep': '??',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': '??',
}
gpu_name_mapping_predictor_pre = {
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
  'gpu___CG_p_prog__m_vn': 'in_gpu___CG_p_nh_prog_nnow__m_vn',
  'gpu___CG_p_prog__m_w': 'in_gpu___CG_p_nh_prog_nnow__m_w',
  'p_diag': 'in_p_nh->diag',
  'p_int': 'in_p_int',
  'p_metrics': 'in_p_nh->metrics',
  'p_patch': 'in_p_patch',
  'p_prog': 'in_p_nh_prog_nnow',
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
  'istep': '??',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': '??',
}
name_mapping_corrector_pre = {
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
  'istep': '??',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': '??',
}
name_mapping_predictor_pre = {
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
  '__CG_p_prog__m_vn': 'in___CG_p_nh_prog_nnow__m_vn',
  '__CG_p_prog__m_w': 'in___CG_p_nh_prog_nnow__m_w',
  'global_data': 'in_global_data',
  'p_diag': 'in_p_nh->diag',
  'p_int': 'in_p_int',
  'p_metrics': 'in_p_nh->metrics',
  'p_patch': 'in_p_patch',
  'p_prog': 'in_p_nh_prog_nnow',
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
  'istep': '??',
  'ldeepatmo': 'in_global_data->ldeepatmo',
  'lvn_only': '??',
  'ntnd': '??',
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
auto* in_p_diag = in_p_nh->diag;
auto* in_p_metrics = in_p_nh->metrics;
auto in_ldeepatmo = in_global_data->ldeepatmo;
velocity_tendencies{gpu_suffix}(
    {input_args}
);
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

    velocity_name_mapping_local = copy.deepcopy(name_mapping_predictor_pre if "predictor" in sdfg.name else name_mapping_corrector_pre)
    velocity_name_mapping_local["istep"] = in_istep
    velocity_name_mapping_local["lvn_only"] = in_lvn_only
    velocity_name_mapping_local["ntnd"] = "in_ntl1" if "predictor" in sdfg.name else "in_ntl2"

    required_in_conns = set()
    for name in velocity_name_mapping_local.values():
        if "->" in name:
            lname = name.split("->")[0].strip()
        else:
            lname = name
        if lname.startswith("in_"):
            required_in_conns.add(lname)

    # Rm all input ouput from the tasklet
    for ie in velocity_state.in_edges(velocity_tasklet):
        state.remove_edge(ie)
        if state.degree(ie.src) == 0:
            state.remove_node(ie.src)
        velocity_tasklet.remove_in_connector(ie.dst_conn)
    for oe in velocity_state.out_edges(velocity_tasklet):
        state.remove_edge(oe)
        if state.degree(oe.dst) == 0:
            state.remove_node(oe.dst)
        velocity_tasklet.remove_out_connector(oe.src_conn)


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
    has_gpu_exit_call = any([("exit_velocity_tendencies_gpu();" in v.as_string) if isinstance(v, CodeBlock) else ("exit_velocity_tendencies_gpu();" in v) for v in sdfg.exit_code.values()])
    has_cpu_exit_call = any([("exit_velocity_tendencies();" in v.as_string) if isinstance(v, CodeBlock) else ("exit_velocity_tendencies();" in v) for v in sdfg.exit_code.values()])
    assert not has_gpu_exit_call, "GPU reinject velocity tasklet should not be already here if calling this function."
    assert has_cpu_exit_call, "CPU reinject velocity tasklet should be already here if calling this function."


def _add_array_and_copyin_copy_out(
    sdfg: dace.SDFG,
    flatten_tasklet: dace.nodes.Tasklet,
    deflatten_tasklet: dace.nodes.Tasklet,
    flatten_state: dace.SDFGState,
    deflatten_state: dace.SDFGState,
    data_name: str,
):
    if data_name not in sdfg.arrays:
        assert data_name[4:] in sdfg.arrays, f"Array {data_name} not found in SDFG."
        if isinstance(sdfg.arrays[data_name[4:]], dace.data.Scalar):
            return None
        # Add array
        copydesc = copy.deepcopy(sdfg.arrays[data_name[4:]])
        copydesc.transient = True
        copydesc.storage = dace.StorageType.GPU_Global
        sdfg.add_datadesc(
            data_name,
            copydesc
        )
        # Add to flatten and deflatten
        flatten_dsts = {e.dst for e in flatten_state.out_edges(flatten_tasklet) if e.dst.data == data_name[4:]}
        assert len(flatten_dsts) == 1, f"Flatten tasklet does not have a single source for {data_name[4:]}, found: {flatten_dsts}."
        deflatten_srcs = {e.src for e in deflatten_state.in_edges(deflatten_tasklet) if e.src.data == data_name[4:]}
        assert len(deflatten_srcs) == 1, f"Deflatten tasklet does not have a single destination for {data_name[4:]}, found: {deflatten_srcs}."
        flatten_dst = flatten_dsts.pop()
        deflatten_src = deflatten_srcs.pop()

        an = flatten_state.add_access(data_name)
        assert isinstance(data_name, str), f"Data name {data_name} should be a string."
        flatten_state.add_edge(
            flatten_dst,
            None,
            an,
            None,
            dace.memlet.Memlet.from_array(
                data_name[4:],
                sdfg.arrays[data_name[4:]]
            )
        )
        an2 = deflatten_state.add_access(data_name)
        deflatten_state.add_edge(
            an2,
            None,
            deflatten_src,
            None,
            dace.memlet.Memlet.from_array(
                data_name,
                sdfg.arrays[data_name]
            )
        )

        return True
    return False

def reinject_velocity_shim_gpu(
    sdfg: dace.SDFG
):

    flatten_tasklet = None
    deflatten_tasklet = None
    flatten_state = None
    deflatten_state = None

    for state in sdfg.all_states():
        for node in state.nodes():
            if ("flatten" in node.label) and ("deflatten" not in node.label):
                flatten_tasklet = node
                flatten_state = state
            if ("deflatten" in node.label):
                deflatten_tasklet = node
                deflatten_state = state
        if flatten_tasklet is not None and deflatten_tasklet is not None:
            break

    assert flatten_tasklet is not None, "Flatten tasklet not found in SDFG."
    assert deflatten_tasklet is not None, "Deflatten tasklet not found in SDFG."


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


    velocity_gpu_name_mapping_local =copy.deepcopy(gpu_name_mapping_predictor_pre if "predictor" in sdfg.name else gpu_name_mapping_corrector_pre)
    velocity_gpu_name_mapping_local["istep"] = in_istep
    velocity_gpu_name_mapping_local["lvn_only"] = in_lvn_only
    velocity_gpu_name_mapping_local["ntnd"] = "in_ntl1" if "predictor" in sdfg.name else "in_ntl2"


    required_in_conns = set()
    for name in velocity_gpu_name_mapping_local.values():
        if "->" in name:
            lname = name.split("->")[0].strip()
        else:
            lname = name
        if lname.startswith("in_"):
            required_in_conns.add(lname)

    # Replace all in connectors, first remove all arrays and velocity tasklet too
    copy_vt = copy.deepcopy(velocity_tasklet)


    # Rm all input ouput from the tasklet
    for ie in velocity_state.in_edges(velocity_tasklet):
        state.remove_edge(ie)
        if state.degree(ie.src) == 0:
            state.remove_node(ie.src)
        velocity_tasklet.remove_in_connector(ie.dst_conn)
    for oe in velocity_state.out_edges(velocity_tasklet):
        state.remove_edge(oe)
        if state.degree(oe.dst) == 0:
            state.remove_node(oe.dst)
        velocity_tasklet.remove_out_connector(oe.src_conn)
    velocity_state.remove_node(velocity_tasklet)

    # Add all missing out connectors (full range), for non const data
    required_out_conns = set()
    for key in non_const_data:
        if key == "__CG_p_diag__m_max_vcfl_dyn":
            continue  # This is a scalar, not an array
        out_name = "out_" + velocity_gpu_name_mapping_local["gpu_" + key][3:]  # Remove 'in_' prefix
        if out_name not in velocity_tasklet.out_connectors:
            required_out_conns.add(out_name)

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

    input_args_str_list = []
    for key, val in velocity_gpu_name_mapping_local.items():
        input_args_str_list.append(f"{val} /* = {key} */")
    input_args_str = ",\n    ".join(input_args_str_list)


    code_str = code_template.format(
        input_args=input_args_str,
        output_assignments=output_assignments_str,
        gpu_suffix="_gpu"
    )

    new_velocity_tasklet = dace.nodes.Tasklet(
        label=copy_vt.name + "_gpu",
        inputs=required_in_conns,
        outputs=required_out_conns,
        code=code_str,
        language=dace.dtypes.Language.CPP,
    )


    velocity_state.add_node(new_velocity_tasklet)

    # Add all missing in connectors (full range)
    new_in_conns = required_in_conns
    #print("New in connectors:", new_in_conns)
    for new_in_conn in new_in_conns:
        data_name = new_in_conn[3:]
        # If not a container group data
        if not data_name.startswith("gpu___CG") and not data_name.startswith("__CG"):
            if data_name.startswith("z_"):
                data_name = "gpu_" + data_name

        if data_name not in velocity_state.sdfg.arrays:
            if data_name.startswith("gpu_"):
                added = _add_array_and_copyin_copy_out(
                    velocity_state.sdfg,
                    flatten_tasklet,
                    deflatten_tasklet,
                    flatten_state,
                    deflatten_state,
                    data_name
                )

        #print(f"Adding in connector {new_in_conn} for data {data_name} to velocity tasklet.")
        #print(new_in_conn, new_in_conn not in velocity_tasklet.in_connectors, data_name, data_name in velocity_state.sdfg.arrays)
        assert data_name in velocity_state.sdfg.arrays, f"Data {data_name} not found in SDFG arrays."
        if (data_name in velocity_state.sdfg.arrays):
            copy_vt.add_in_connector(new_in_conn)
            dataaccess = velocity_state.add_access(data_name)
            velocity_state.add_edge(
                dataaccess,
                None,
                new_velocity_tasklet,
                new_in_conn,
                dace.memlet.Memlet.from_array(
                    data_name,
                    state.sdfg.arrays[data_name]
                )
            )



    # Add all missing out connectors (full range), for non const data
    for key in non_const_data:
        if key != "__CG_p_diag__m_max_vcfl_dyn":
            out_name = "out_" + velocity_gpu_name_mapping_local["gpu_" + key][3:]  # Remove 'in_' prefix
        else:
            out_name = "out___CG_p_nh__CG_diag__m_max_vcfl_dyn"
        if out_name not in velocity_tasklet.out_connectors:
            new_velocity_tasklet.add_out_connector(out_name)
            if key != "__CG_p_diag__m_max_vcfl_dyn":
                data_name = "gpu_" + out_name[4:] if not out_name[4:].startswith("gpu_") else out_name[4:]  # Remove 'out_' prefix
            else:
                data_name = "__CG_p_nh__CG_diag__m_max_vcfl_dyn"
            dataaccess = velocity_state.add_access(data_name)
            velocity_state.add_edge(
                new_velocity_tasklet,
                out_name,
                dataaccess,
                None,
                dace.memlet.Memlet.from_array(
                    data_name,
                    velocity_state.sdfg.arrays[data_name]
                )
            )

    # Reinjecting the CPU velocity -> GPU velocity
    # It means: if existing remove CPU exit and add GPU exit if nto already there
    has_gpu_exit_call = any([("exit_velocity_tendencies_gpu();" in v.as_string) if isinstance(v, CodeBlock) else ("exit_velocity_tendencies_gpu();" in v) for v in sdfg.exit_code.values()])
    has_cpu_exit_call = any([("exit_velocity_tendencies();" in v.as_string) if isinstance(v, CodeBlock) else ("exit_velocity_tendencies();" in v) for v in sdfg.exit_code.values()])
    if has_cpu_exit_call:
        # Remove the CPU exit call, we are replacing it with the GPU one
        sdfg.exit_code = {
            k: CodeBlock(code=v.replace("exit_velocity_tendencies();", "/*exit_velocity_tendencies();*/"), language=dace.dtypes.Language.CPP)
            if isinstance(v, str) else
            CodeBlock(code=v.as_string.replace("exit_velocity_tendencies();", "/*exit_velocity_tendencies();*/"), language=dace.dtypes.Language.CPP)
            for k, v in sdfg.exit_code.items()
        }

    if not has_gpu_exit_call:
        sdfg.append_exit_code(
            cpp_code="exit_velocity_tendencies_gpu();",
        )

    # velocity_tasklet.side_effects = True
    sdfg.validate()