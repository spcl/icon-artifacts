
#ifndef __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_2__
#define __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_2__

#include <dace/dace.h>


struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s = {};
int __f2dace_SA_ddt_vn_apc_pc_d_1_s = {};
int __f2dace_SA_ddt_vn_apc_pc_d_2_s = {};
int __f2dace_SA_ddt_vn_apc_pc_d_3_s = {};
int __f2dace_SA_ddt_w_adv_pc_d_0_s = {};
int __f2dace_SA_ddt_w_adv_pc_d_1_s = {};
int __f2dace_SA_ddt_w_adv_pc_d_2_s = {};
int __f2dace_SA_ddt_w_adv_pc_d_3_s = {};
int __f2dace_SA_vn_ie_d_0_s = {};
int __f2dace_SA_vn_ie_d_1_s = {};
int __f2dace_SA_vn_ie_d_2_s = {};
int __f2dace_SA_vt_d_0_s = {};
int __f2dace_SA_vt_d_1_s = {};
int __f2dace_SA_vt_d_2_s = {};
int __f2dace_SA_w_concorr_c_d_0_s = {};
int __f2dace_SA_w_concorr_c_d_1_s = {};
int __f2dace_SA_w_concorr_c_d_2_s = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_0_s = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_1_s = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_2_s = {};
int __f2dace_SOA_ddt_vn_apc_pc_d_3_s = {};
int __f2dace_SOA_ddt_w_adv_pc_d_0_s = {};
int __f2dace_SOA_ddt_w_adv_pc_d_1_s = {};
int __f2dace_SOA_ddt_w_adv_pc_d_2_s = {};
int __f2dace_SOA_ddt_w_adv_pc_d_3_s = {};
int __f2dace_SOA_vn_ie_d_0_s = {};
int __f2dace_SOA_vn_ie_d_1_s = {};
int __f2dace_SOA_vn_ie_d_2_s = {};
int __f2dace_SOA_vt_d_0_s = {};
int __f2dace_SOA_vt_d_1_s = {};
int __f2dace_SOA_vt_d_2_s = {};
int __f2dace_SOA_w_concorr_c_d_0_s = {};
int __f2dace_SOA_w_concorr_c_d_1_s = {};
int __f2dace_SOA_w_concorr_c_d_2_s = {};
double* ddt_vn_apc_pc = {};
double* ddt_w_adv_pc = {};
double max_vcfl_dyn = {};
double* vn_ie = {};
double* vt = {};
double* w_concorr_c = {};
};


struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s = {};
int __f2dace_SA_coeff1_dwdz_d_1_s = {};
int __f2dace_SA_coeff1_dwdz_d_2_s = {};
int __f2dace_SA_coeff2_dwdz_d_0_s = {};
int __f2dace_SA_coeff2_dwdz_d_1_s = {};
int __f2dace_SA_coeff2_dwdz_d_2_s = {};
int __f2dace_SA_coeff_gradekin_d_0_s = {};
int __f2dace_SA_coeff_gradekin_d_1_s = {};
int __f2dace_SA_coeff_gradekin_d_2_s = {};
int __f2dace_SA_ddqz_z_full_e_d_0_s = {};
int __f2dace_SA_ddqz_z_full_e_d_1_s = {};
int __f2dace_SA_ddqz_z_full_e_d_2_s = {};
int __f2dace_SA_ddqz_z_half_d_0_s = {};
int __f2dace_SA_ddqz_z_half_d_1_s = {};
int __f2dace_SA_ddqz_z_half_d_2_s = {};
int __f2dace_SA_ddxn_z_full_d_0_s = {};
int __f2dace_SA_ddxn_z_full_d_1_s = {};
int __f2dace_SA_ddxn_z_full_d_2_s = {};
int __f2dace_SA_ddxt_z_full_d_0_s = {};
int __f2dace_SA_ddxt_z_full_d_1_s = {};
int __f2dace_SA_ddxt_z_full_d_2_s = {};
int __f2dace_SA_deepatmo_gradh_ifc_d_0_s = {};
int __f2dace_SA_deepatmo_gradh_mc_d_0_s = {};
int __f2dace_SA_deepatmo_invr_ifc_d_0_s = {};
int __f2dace_SA_deepatmo_invr_mc_d_0_s = {};
int __f2dace_SA_wgtfac_c_d_0_s = {};
int __f2dace_SA_wgtfac_c_d_1_s = {};
int __f2dace_SA_wgtfac_c_d_2_s = {};
int __f2dace_SA_wgtfac_e_d_0_s = {};
int __f2dace_SA_wgtfac_e_d_1_s = {};
int __f2dace_SA_wgtfac_e_d_2_s = {};
int __f2dace_SA_wgtfacq_e_d_0_s = {};
int __f2dace_SA_wgtfacq_e_d_1_s = {};
int __f2dace_SA_wgtfacq_e_d_2_s = {};
int __f2dace_SOA_coeff1_dwdz_d_0_s = {};
int __f2dace_SOA_coeff1_dwdz_d_1_s = {};
int __f2dace_SOA_coeff1_dwdz_d_2_s = {};
int __f2dace_SOA_coeff2_dwdz_d_0_s = {};
int __f2dace_SOA_coeff2_dwdz_d_1_s = {};
int __f2dace_SOA_coeff2_dwdz_d_2_s = {};
int __f2dace_SOA_coeff_gradekin_d_0_s = {};
int __f2dace_SOA_coeff_gradekin_d_1_s = {};
int __f2dace_SOA_coeff_gradekin_d_2_s = {};
int __f2dace_SOA_ddqz_z_full_e_d_0_s = {};
int __f2dace_SOA_ddqz_z_full_e_d_1_s = {};
int __f2dace_SOA_ddqz_z_full_e_d_2_s = {};
int __f2dace_SOA_ddqz_z_half_d_0_s = {};
int __f2dace_SOA_ddqz_z_half_d_1_s = {};
int __f2dace_SOA_ddqz_z_half_d_2_s = {};
int __f2dace_SOA_ddxn_z_full_d_0_s = {};
int __f2dace_SOA_ddxn_z_full_d_1_s = {};
int __f2dace_SOA_ddxn_z_full_d_2_s = {};
int __f2dace_SOA_ddxt_z_full_d_0_s = {};
int __f2dace_SOA_ddxt_z_full_d_1_s = {};
int __f2dace_SOA_ddxt_z_full_d_2_s = {};
int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s = {};
int __f2dace_SOA_deepatmo_gradh_mc_d_0_s = {};
int __f2dace_SOA_deepatmo_invr_ifc_d_0_s = {};
int __f2dace_SOA_deepatmo_invr_mc_d_0_s = {};
int __f2dace_SOA_wgtfac_c_d_0_s = {};
int __f2dace_SOA_wgtfac_c_d_1_s = {};
int __f2dace_SOA_wgtfac_c_d_2_s = {};
int __f2dace_SOA_wgtfac_e_d_0_s = {};
int __f2dace_SOA_wgtfac_e_d_1_s = {};
int __f2dace_SOA_wgtfac_e_d_2_s = {};
int __f2dace_SOA_wgtfacq_e_d_0_s = {};
int __f2dace_SOA_wgtfacq_e_d_1_s = {};
int __f2dace_SOA_wgtfacq_e_d_2_s = {};
double* coeff1_dwdz = {};
double* coeff2_dwdz = {};
double* coeff_gradekin = {};
double* ddqz_z_full_e = {};
double* ddqz_z_half = {};
double* ddxn_z_full = {};
double* ddxt_z_full = {};
double* deepatmo_gradh_ifc = {};
double* deepatmo_gradh_mc = {};
double* deepatmo_invr_ifc = {};
double* deepatmo_invr_mc = {};
double* wgtfac_c = {};
double* wgtfac_e = {};
double* wgtfacq_e = {};
};


struct t_grid_domain_decomp_info {
    int __f2dace_SA_owner_mask_d_0_s = {};
int __f2dace_SA_owner_mask_d_1_s = {};
int __f2dace_SOA_owner_mask_d_0_s = {};
int __f2dace_SOA_owner_mask_d_1_s = {};
int* owner_mask = {};
};


struct t_grid_cells {
    int __f2dace_SA_area_d_0_s = {};
int __f2dace_SA_area_d_1_s = {};
int __f2dace_SA_edge_blk_d_0_s = {};
int __f2dace_SA_edge_blk_d_1_s = {};
int __f2dace_SA_edge_blk_d_2_s = {};
int __f2dace_SA_edge_idx_d_0_s = {};
int __f2dace_SA_edge_idx_d_1_s = {};
int __f2dace_SA_edge_idx_d_2_s = {};
int __f2dace_SA_end_block_d_0_s = {};
int __f2dace_SA_end_index_d_0_s = {};
int __f2dace_SA_neighbor_blk_d_0_s = {};
int __f2dace_SA_neighbor_blk_d_1_s = {};
int __f2dace_SA_neighbor_blk_d_2_s = {};
int __f2dace_SA_neighbor_idx_d_0_s = {};
int __f2dace_SA_neighbor_idx_d_1_s = {};
int __f2dace_SA_neighbor_idx_d_2_s = {};
int __f2dace_SA_start_block_d_0_s = {};
int __f2dace_SA_start_index_d_0_s = {};
int __f2dace_SOA_area_d_0_s = {};
int __f2dace_SOA_area_d_1_s = {};
int __f2dace_SOA_edge_blk_d_0_s = {};
int __f2dace_SOA_edge_blk_d_1_s = {};
int __f2dace_SOA_edge_blk_d_2_s = {};
int __f2dace_SOA_edge_idx_d_0_s = {};
int __f2dace_SOA_edge_idx_d_1_s = {};
int __f2dace_SOA_edge_idx_d_2_s = {};
int __f2dace_SOA_end_block_d_0_s = {};
int __f2dace_SOA_end_index_d_0_s = {};
int __f2dace_SOA_neighbor_blk_d_0_s = {};
int __f2dace_SOA_neighbor_blk_d_1_s = {};
int __f2dace_SOA_neighbor_blk_d_2_s = {};
int __f2dace_SOA_neighbor_idx_d_0_s = {};
int __f2dace_SOA_neighbor_idx_d_1_s = {};
int __f2dace_SOA_neighbor_idx_d_2_s = {};
int __f2dace_SOA_start_block_d_0_s = {};
int __f2dace_SOA_start_index_d_0_s = {};
double* area = {};
t_grid_domain_decomp_info* decomp_info = {};
int* edge_blk = {};
int* edge_idx = {};
int* end_block = {};
int* end_index = {};
int* neighbor_blk = {};
int* neighbor_idx = {};
int* start_block = {};
int* start_index = {};
};


struct t_grid_edges {
    int __f2dace_SA_area_edge_d_0_s = {};
int __f2dace_SA_area_edge_d_1_s = {};
int __f2dace_SA_cell_blk_d_0_s = {};
int __f2dace_SA_cell_blk_d_1_s = {};
int __f2dace_SA_cell_blk_d_2_s = {};
int __f2dace_SA_cell_idx_d_0_s = {};
int __f2dace_SA_cell_idx_d_1_s = {};
int __f2dace_SA_cell_idx_d_2_s = {};
int __f2dace_SA_end_block_d_0_s = {};
int __f2dace_SA_end_index_d_0_s = {};
int __f2dace_SA_f_e_d_0_s = {};
int __f2dace_SA_f_e_d_1_s = {};
int __f2dace_SA_fn_e_d_0_s = {};
int __f2dace_SA_fn_e_d_1_s = {};
int __f2dace_SA_ft_e_d_0_s = {};
int __f2dace_SA_ft_e_d_1_s = {};
int __f2dace_SA_inv_dual_edge_length_d_0_s = {};
int __f2dace_SA_inv_dual_edge_length_d_1_s = {};
int __f2dace_SA_inv_primal_edge_length_d_0_s = {};
int __f2dace_SA_inv_primal_edge_length_d_1_s = {};
int __f2dace_SA_quad_blk_d_0_s = {};
int __f2dace_SA_quad_blk_d_1_s = {};
int __f2dace_SA_quad_blk_d_2_s = {};
int __f2dace_SA_quad_idx_d_0_s = {};
int __f2dace_SA_quad_idx_d_1_s = {};
int __f2dace_SA_quad_idx_d_2_s = {};
int __f2dace_SA_start_block_d_0_s = {};
int __f2dace_SA_start_index_d_0_s = {};
int __f2dace_SA_tangent_orientation_d_0_s = {};
int __f2dace_SA_tangent_orientation_d_1_s = {};
int __f2dace_SA_vertex_blk_d_0_s = {};
int __f2dace_SA_vertex_blk_d_1_s = {};
int __f2dace_SA_vertex_blk_d_2_s = {};
int __f2dace_SA_vertex_idx_d_0_s = {};
int __f2dace_SA_vertex_idx_d_1_s = {};
int __f2dace_SA_vertex_idx_d_2_s = {};
int __f2dace_SOA_area_edge_d_0_s = {};
int __f2dace_SOA_area_edge_d_1_s = {};
int __f2dace_SOA_cell_blk_d_0_s = {};
int __f2dace_SOA_cell_blk_d_1_s = {};
int __f2dace_SOA_cell_blk_d_2_s = {};
int __f2dace_SOA_cell_idx_d_0_s = {};
int __f2dace_SOA_cell_idx_d_1_s = {};
int __f2dace_SOA_cell_idx_d_2_s = {};
int __f2dace_SOA_end_block_d_0_s = {};
int __f2dace_SOA_end_index_d_0_s = {};
int __f2dace_SOA_f_e_d_0_s = {};
int __f2dace_SOA_f_e_d_1_s = {};
int __f2dace_SOA_fn_e_d_0_s = {};
int __f2dace_SOA_fn_e_d_1_s = {};
int __f2dace_SOA_ft_e_d_0_s = {};
int __f2dace_SOA_ft_e_d_1_s = {};
int __f2dace_SOA_inv_dual_edge_length_d_0_s = {};
int __f2dace_SOA_inv_dual_edge_length_d_1_s = {};
int __f2dace_SOA_inv_primal_edge_length_d_0_s = {};
int __f2dace_SOA_inv_primal_edge_length_d_1_s = {};
int __f2dace_SOA_quad_blk_d_0_s = {};
int __f2dace_SOA_quad_blk_d_1_s = {};
int __f2dace_SOA_quad_blk_d_2_s = {};
int __f2dace_SOA_quad_idx_d_0_s = {};
int __f2dace_SOA_quad_idx_d_1_s = {};
int __f2dace_SOA_quad_idx_d_2_s = {};
int __f2dace_SOA_start_block_d_0_s = {};
int __f2dace_SOA_start_index_d_0_s = {};
int __f2dace_SOA_tangent_orientation_d_0_s = {};
int __f2dace_SOA_tangent_orientation_d_1_s = {};
int __f2dace_SOA_vertex_blk_d_0_s = {};
int __f2dace_SOA_vertex_blk_d_1_s = {};
int __f2dace_SOA_vertex_blk_d_2_s = {};
int __f2dace_SOA_vertex_idx_d_0_s = {};
int __f2dace_SOA_vertex_idx_d_1_s = {};
int __f2dace_SOA_vertex_idx_d_2_s = {};
double* area_edge = {};
int* cell_blk = {};
int* cell_idx = {};
int* end_block = {};
int* end_index = {};
double* f_e = {};
double* fn_e = {};
double* ft_e = {};
double* inv_dual_edge_length = {};
double* inv_primal_edge_length = {};
int* quad_blk = {};
int* quad_idx = {};
int* start_block = {};
int* start_index = {};
double* tangent_orientation = {};
int* vertex_blk = {};
int* vertex_idx = {};
};


struct t_grid_vertices {
    int __f2dace_SA_cell_blk_d_0_s = {};
int __f2dace_SA_cell_blk_d_1_s = {};
int __f2dace_SA_cell_blk_d_2_s = {};
int __f2dace_SA_cell_idx_d_0_s = {};
int __f2dace_SA_cell_idx_d_1_s = {};
int __f2dace_SA_cell_idx_d_2_s = {};
int __f2dace_SA_edge_blk_d_0_s = {};
int __f2dace_SA_edge_blk_d_1_s = {};
int __f2dace_SA_edge_blk_d_2_s = {};
int __f2dace_SA_edge_idx_d_0_s = {};
int __f2dace_SA_edge_idx_d_1_s = {};
int __f2dace_SA_edge_idx_d_2_s = {};
int __f2dace_SA_end_block_d_0_s = {};
int __f2dace_SA_end_index_d_0_s = {};
int __f2dace_SA_start_block_d_0_s = {};
int __f2dace_SA_start_index_d_0_s = {};
int __f2dace_SOA_cell_blk_d_0_s = {};
int __f2dace_SOA_cell_blk_d_1_s = {};
int __f2dace_SOA_cell_blk_d_2_s = {};
int __f2dace_SOA_cell_idx_d_0_s = {};
int __f2dace_SOA_cell_idx_d_1_s = {};
int __f2dace_SOA_cell_idx_d_2_s = {};
int __f2dace_SOA_edge_blk_d_0_s = {};
int __f2dace_SOA_edge_blk_d_1_s = {};
int __f2dace_SOA_edge_blk_d_2_s = {};
int __f2dace_SOA_edge_idx_d_0_s = {};
int __f2dace_SOA_edge_idx_d_1_s = {};
int __f2dace_SOA_edge_idx_d_2_s = {};
int __f2dace_SOA_end_block_d_0_s = {};
int __f2dace_SOA_end_index_d_0_s = {};
int __f2dace_SOA_start_block_d_0_s = {};
int __f2dace_SOA_start_index_d_0_s = {};
int* cell_blk = {};
int* cell_idx = {};
int* edge_blk = {};
int* edge_idx = {};
int* end_block = {};
int* end_index = {};
int* start_block = {};
int* start_index = {};
};


struct t_patch {
    t_grid_cells* cells = {};
t_grid_edges* edges = {};
int nblks_c = {};
int nblks_e = {};
int nblks_v = {};
t_grid_vertices* verts = {};
};


struct t_int_state {
    int __f2dace_SA_c_lin_e_d_0_s = {};
int __f2dace_SA_c_lin_e_d_1_s = {};
int __f2dace_SA_c_lin_e_d_2_s = {};
int __f2dace_SA_cells_aw_verts_d_0_s = {};
int __f2dace_SA_cells_aw_verts_d_1_s = {};
int __f2dace_SA_cells_aw_verts_d_2_s = {};
int __f2dace_SA_e_bln_c_s_d_0_s = {};
int __f2dace_SA_e_bln_c_s_d_1_s = {};
int __f2dace_SA_e_bln_c_s_d_2_s = {};
int __f2dace_SA_geofac_grdiv_d_0_s = {};
int __f2dace_SA_geofac_grdiv_d_1_s = {};
int __f2dace_SA_geofac_grdiv_d_2_s = {};
int __f2dace_SA_geofac_n2s_d_0_s = {};
int __f2dace_SA_geofac_n2s_d_1_s = {};
int __f2dace_SA_geofac_n2s_d_2_s = {};
int __f2dace_SA_geofac_rot_d_0_s = {};
int __f2dace_SA_geofac_rot_d_1_s = {};
int __f2dace_SA_geofac_rot_d_2_s = {};
int __f2dace_SA_rbf_vec_coeff_e_d_0_s = {};
int __f2dace_SA_rbf_vec_coeff_e_d_1_s = {};
int __f2dace_SA_rbf_vec_coeff_e_d_2_s = {};
int __f2dace_SOA_c_lin_e_d_0_s = {};
int __f2dace_SOA_c_lin_e_d_1_s = {};
int __f2dace_SOA_c_lin_e_d_2_s = {};
int __f2dace_SOA_cells_aw_verts_d_0_s = {};
int __f2dace_SOA_cells_aw_verts_d_1_s = {};
int __f2dace_SOA_cells_aw_verts_d_2_s = {};
int __f2dace_SOA_e_bln_c_s_d_0_s = {};
int __f2dace_SOA_e_bln_c_s_d_1_s = {};
int __f2dace_SOA_e_bln_c_s_d_2_s = {};
int __f2dace_SOA_geofac_grdiv_d_0_s = {};
int __f2dace_SOA_geofac_grdiv_d_1_s = {};
int __f2dace_SOA_geofac_grdiv_d_2_s = {};
int __f2dace_SOA_geofac_n2s_d_0_s = {};
int __f2dace_SOA_geofac_n2s_d_1_s = {};
int __f2dace_SOA_geofac_n2s_d_2_s = {};
int __f2dace_SOA_geofac_rot_d_0_s = {};
int __f2dace_SOA_geofac_rot_d_1_s = {};
int __f2dace_SOA_geofac_rot_d_2_s = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_0_s = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_1_s = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_2_s = {};
double* c_lin_e = {};
double* cells_aw_verts = {};
double* e_bln_c_s = {};
double* geofac_grdiv = {};
double* geofac_n2s = {};
double* geofac_rot = {};
double* rbf_vec_coeff_e = {};
};


struct global_data_type {
    int i_am_accel_node = {};
int lextra_diffu = {};
int* nflatlev = {};
int nproma = {};
int* nrdmax = {};
int timer_intp = {};
int timer_solve_nh_veltend = {};
int timers_level = {};
};


struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s = {};
int __f2dace_SA_vn_d_1_s = {};
int __f2dace_SA_vn_d_2_s = {};
int __f2dace_SA_w_d_0_s = {};
int __f2dace_SA_w_d_1_s = {};
int __f2dace_SA_w_d_2_s = {};
int __f2dace_SOA_vn_d_0_s = {};
int __f2dace_SOA_vn_d_1_s = {};
int __f2dace_SOA_vn_d_2_s = {};
int __f2dace_SOA_w_d_0_s = {};
int __f2dace_SOA_w_d_1_s = {};
int __f2dace_SOA_w_d_2_s = {};
double* vn = {};
double* w = {};
};




struct velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t;  // Forward declaration.

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state);
DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);

#endif // __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_1_ISTEP_2__
