#include "reductions_device.cuh"
#define __REDUCE_DEVICE__

#include <cuda_runtime.h>
#include <dace/dace.h>


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

struct velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t {
    dace::cuda::Context *gpu_context;
    double * __restrict__ __0_gpu_z_w_con_c;
    uint8_t * __restrict__ __0_gpu_cfl_clipping;
    double * __restrict__ __0_gpu_maxvcfl_arr;
    double * __restrict__ __0_gpu_z_w_con_c_full;
    double * __restrict__ __0_gpu_z_ekinh;
    double * __restrict__ __0_gpu_z_w_concorr_mc;
    uint8_t * __restrict__ __0_gpu_levelmask;
    uint8_t * __restrict__ __0_gpu_levmask;
    double * __restrict__ __0_gpu_zeta;
    double * __restrict__ __0_gpu_vcflmax;
    double * __restrict__ __0_vcflmax;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16;
    int __0_bitwidth_check_done;
    int __0_bitwidth_scalar;
    uint8_t * __restrict__ __0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8;
    uint8_t * __restrict__ __0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8;
    uint8_t * __restrict__ __0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8;
    int __0_nblk_lowering_done;
};



DACE_EXPORTED int __dace_init_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_area_d_0_s_cells_p_patch_2, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_c_lin_e_d_2_s_p_int_6, int __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SA_end_block_d_0_s_cells_p_patch_2, int __f2dace_SA_end_block_d_0_s_edges_p_patch_4, int __f2dace_SA_end_block_d_0_s_verts_p_patch_5, int __f2dace_SA_end_index_d_0_s_cells_p_patch_2, int __f2dace_SA_end_index_d_0_s_edges_p_patch_4, int __f2dace_SA_end_index_d_0_s_verts_p_patch_5, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SA_fn_e_d_0_s_edges_p_patch_4, int __f2dace_SA_ft_e_d_0_s_edges_p_patch_4, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_geofac_rot_d_2_s_p_int_6, int __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SA_neighbor_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SA_start_block_d_0_s_cells_p_patch_2, int __f2dace_SA_start_block_d_0_s_edges_p_patch_4, int __f2dace_SA_start_block_d_0_s_verts_p_patch_5, int __f2dace_SA_start_index_d_0_s_cells_p_patch_2, int __f2dace_SA_start_index_d_0_s_edges_p_patch_4, int __f2dace_SA_start_index_d_0_s_verts_p_patch_5, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_d_2_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vn_ie_d_2_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_vt_d_2_s_p_diag_9, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SA_w_d_2_s_p_prog_7, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SA_wgtfac_c_d_2_s_p_metrics_8, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfac_e_d_2_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_2_s_p_metrics_8, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_end_block_d_0_s_cells_p_patch_2, int __f2dace_SOA_end_block_d_0_s_edges_p_patch_4, int __f2dace_SOA_end_block_d_0_s_verts_p_patch_5, int __f2dace_SOA_end_index_d_0_s_cells_p_patch_2, int __f2dace_SOA_end_index_d_0_s_edges_p_patch_4, int __f2dace_SOA_end_index_d_0_s_verts_p_patch_5, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_start_block_d_0_s_cells_p_patch_2, int __f2dace_SOA_start_block_d_0_s_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_verts_p_patch_5, int __f2dace_SOA_start_index_d_0_s_cells_p_patch_2, int __f2dace_SOA_start_index_d_0_s_edges_p_patch_4, int __f2dace_SOA_start_index_d_0_s_verts_p_patch_5, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int tmp_struct_symbol_0, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_11, int tmp_struct_symbol_12, int tmp_struct_symbol_13, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_3, int tmp_struct_symbol_4, int tmp_struct_symbol_8, int tmp_struct_symbol_9);
DACE_EXPORTED int __dace_exit_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state);

DACE_DFI void loop_body_8_2_5(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int _for_it_4_0, int _for_it_5_0, int tmp_struct_symbol_8) {
    int tmp_index_92_0;
    int tmp_index_94_0;
    int tmp_index_104_0;
    int tmp_index_106_0;
    int tmp_index_116_0;
    int tmp_index_118_0;
    int tmp_index_128_0;
    int tmp_index_130_0;
    int tmp_index_140_0;
    int tmp_index_142_0;
    int tmp_index_152_0;
    int tmp_index_154_0;



    tmp_index_92_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_94_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_104_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_106_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_116_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_118_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_128_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_130_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_140_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_142_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_152_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_154_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);

    {

        {
            double ptr_int_0_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_1_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_2_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_3_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_4_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_5_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (6 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double vec_e_0_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
            double vec_e_1_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
            double vec_e_2_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
            double vec_e_3_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
            double vec_e_4_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
            double vec_e_5_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
            double rot_vec_out_0;

            ///////////////////
            // Tasklet code (T_l296_c296)
            rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
            ///////////////////

            gpu_zeta[(((_for_it_5_0 + ((90 * tmp_struct_symbol_8) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_8 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
        }

    }

}

DACE_DFI void loop_body_16_2_3(const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_diag__m_vt, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int _for_it_7, int _for_it_8) {
    int tmp_index_178;
    int tmp_index_180;
    int tmp_index_190;
    int tmp_index_192;
    int tmp_index_202;
    int tmp_index_204;
    int tmp_index_214;
    int tmp_index_216;



    tmp_index_178 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_180 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_190 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_192 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_202 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_204 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_214 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_216 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);

    {

        {
            double p_int_0_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 1)];
            double p_int_1_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 2)];
            double p_int_2_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 3)];
            double p_int_3_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 4)];
            double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_180) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_178)];
            double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_192) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_190)];
            double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_204) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_202)];
            double p_prog_3_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_216) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_214)];
            double p_diag_out_vt_0;

            ///////////////////
            // Tasklet code (T_l441_c441)
            p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
            ///////////////////

            gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_7)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_8)] = p_diag_out_vt_0;
        }

    }

}

DACE_DFI void loop_body_23_2_5(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_ekinh, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int _for_it_23, int _for_it_24, int tmp_struct_symbol_10) {
    int tmp_index_407;
    int tmp_index_409;
    int tmp_index_419;
    int tmp_index_421;
    int tmp_index_431;
    int tmp_index_433;



    tmp_index_407 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_409 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_419 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_421 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_431 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_433 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);

    {

        {
            double p_int_0_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_1_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_2_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_409) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_407)];
            double z_kin_hor_e_1_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_421) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_419)];
            double z_kin_hor_e_2_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_433) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_431)];
            double z_ekinh_out_0;

            ///////////////////
            // Tasklet code (T_l515_c515)
            z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s * z_kin_hor_e_2_in_0));
            ///////////////////

            gpu_z_ekinh[(((_for_it_24 + ((90 * tmp_struct_symbol_10) * (_for_it_22 - 1))) + (tmp_struct_symbol_10 * (_for_it_23 - 1))) - 1)] = z_ekinh_out_0;
        }

    }

}

DACE_DFI void loop_body_23_2_7(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu_z_w_concorr_me, double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int _for_it_25, int _for_it_26, int tmp_struct_symbol_0) {
    int tmp_index_445;
    int tmp_index_447;
    int tmp_index_457;
    int tmp_index_459;
    int tmp_index_469;
    int tmp_index_471;



    tmp_index_445 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_447 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);
    tmp_index_457 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_459 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);
    tmp_index_469 = (gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_471 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);

    {

        {
            double p_int_0_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double p_int_1_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double p_int_2_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double z_w_concorr_me_0_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_447) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_445)];
            double z_w_concorr_me_1_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_459) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_457)];
            double z_w_concorr_me_2_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_471) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_469)];
            double z_w_concorr_mc_out_0;

            ///////////////////
            // Tasklet code (T_l521_c521)
            z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s * z_w_concorr_me_2_in_0));
            ///////////////////

            gpu_z_w_concorr_mc[((_for_it_26 + (tmp_struct_symbol_0 * (_for_it_25 - 1))) - 1)] = z_w_concorr_mc_out_0;
        }

    }

}

DACE_DFI void loop_body_23_4_0(const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int _for_it_35, int tmp_struct_symbol_14) {


    if ((1 == 1)) {
        {
            int reduce_scan_size_0;

            {
                int size;

                ///////////////////
                // Tasklet code (size_reduce_scan)
                size = 1;
                ///////////////////

                reduce_scan_size_0 = size;
            }
            {
                uint8_t in_arr = gpu_cfl_clipping[((_for_it_22 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];
                int in_size = reduce_scan_size_0;
                uint8_t out;

                ///////////////////

                #define __REDUCE_GPU__

                #ifdef __REDUCE_DEVICE__
                out = reduce_scan_device(in_arr, in_size);
                #elif defined(__REDUCE_GPU__)
                out = reduce_scan_gpu(in_arr, in_size, __dace_current_stream);
                #else
                out = reduce_scan_cpu(in_arr, in_size);
                #endif

                #undef __REDUCE_GPU__

                ///////////////////

                gpu_levmask[(((90 * _for_it_22) + _for_it_35) - 91)] = out;
            }

        }
    }

}

DACE_DFI void loop_body_23_4_10(const double&  dtime, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, int _for_it_35, int _for_it_37, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4) {
    uint8_t _if_cond_18;
    double vcfl;



    _if_cond_18 = gpu_cfl_clipping[((_for_it_37 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];

    if (((1 == 1) && (_if_cond_18 == 1))) {

        vcfl = ((gpu_z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] * dtime) / gpu___CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)]);
        {
            double tmp_call_8;

            {
                double tmp_call_8_out;

                ///////////////////
                // Tasklet code (T_l558_c558)
                tmp_call_8_out = abs(vcfl);
                ///////////////////

                tmp_call_8 = tmp_call_8_out;
            }
            {
                double tmp_call_8_0_in = tmp_call_8;
                double maxvcfl_out;

                ///////////////////
                // Tasklet code (T_l558_c558)
                maxvcfl_out = tmp_call_8_0_in;
                ///////////////////

                gpu_maxvcfl_arr[((_for_it_37 + (tmp_struct_symbol_4 * (_for_it_35 - 1))) - 1)] = maxvcfl_out;
            }

        }
        if (((vcfl < -0.85) == 1)) {
            {

                {
                    double dtime_0_in = dtime;
                    double p_metrics_0_in_ddqz_z_half_0 = gpu___CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)];
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l560_c560)
                    z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                    ///////////////////

                    gpu_z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] = z_w_con_c_out_0;
                }

            }
        } else if (((! ((vcfl < -0.85) == 1)) && ((vcfl > 0.85) == 1))) {
            {

                {
                    double dtime_0_in = dtime;
                    double p_metrics_0_in_ddqz_z_half_0 = gpu___CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)];
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l562_c562)
                    z_w_con_c_out_0 = ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in);
                    ///////////////////

                    gpu_z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] = z_w_con_c_out_0;
                }

            }
        }
    }

}

DACE_DFI void loop_body_41_2_6(const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int _for_it_48, int _for_it_49, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int tmp_index_698;
    int tmp_index_700;
    int tmp_index_710;
    int tmp_index_712;
    int tmp_index_724;
    int tmp_index_726;
    int tmp_index_733;
    int tmp_index_735;
    int tmp_index_745;
    int tmp_index_747;
    int tmp_index_757;
    int tmp_index_759;



    tmp_index_698 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_700 = (1 - 1);
    tmp_index_710 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_712 = (1 - 1);
    tmp_index_724 = (gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_726 = (1 - 1);
    tmp_index_733 = (gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_735 = (1 - 1);
    tmp_index_745 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_747 = (1 - 1);
    tmp_index_757 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_759 = (1 - 1);

    {

        {
            double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_48)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_1_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_2_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[(((((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47)) + (__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48) + 1))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_int_0_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_int_1_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_metrics_0_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_1_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_2_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_3_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_4_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_48)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_49)];
            double p_patch_0_in_edges_f_e_0 = gpu___CG_p_patch__CG_edges__m_f_e[(((__f2dace_SA_f_e_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_f_e_d_0_s_edges_p_patch_4) + _for_it_49)];
            double z_ekinh_0_in_0 = gpu_z_ekinh[((tmp_index_698 + ((90 * tmp_index_700) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_ekinh_1_in_0 = gpu_z_ekinh[((tmp_index_710 + ((90 * tmp_index_712) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_49)];
            double z_w_con_c_full_0_in_0 = gpu_z_w_con_c_full[((tmp_index_745 + ((90 * tmp_index_747) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double z_w_con_c_full_1_in_0 = gpu_z_w_con_c_full[((tmp_index_757 + ((90 * tmp_index_759) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double zeta_0_in_0 = gpu_zeta[((tmp_index_724 + ((90 * tmp_index_726) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double zeta_1_in_0 = gpu_zeta[((tmp_index_733 + ((90 * tmp_index_735) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double p_diag_out_ddt_vn_apc_pc_0;

            ///////////////////
            // Tasklet code (T_l611_c611)
            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
            ///////////////////

            gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_48))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_49)] = p_diag_out_ddt_vn_apc_pc_0;
        }

    }

}

DACE_DFI void loop_body_41_2_28(const double&  cfl_w_limit, const double&  dtime, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, const double&  scalfac_exdiff, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, int _for_it_52, int _for_it_53, int ntnd, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    double w_con_e;
    double tmp_call_17;
    double _if_cond_29;
    int tmp_index_881;
    int tmp_index_883;
    int tmp_index_893;
    int tmp_index_895;
    int _if_cond_28;
    int tmp_index_927;
    int tmp_index_929;
    int tmp_index_939;
    int tmp_index_941;
    int tmp_index_951;
    int tmp_index_953;
    int tmp_index_963;
    int tmp_index_965;
    int tmp_index_976;
    int tmp_index_978;
    int tmp_index_985;
    int tmp_index_987;



    tmp_index_881 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_883 = (1 - 1);
    tmp_index_893 = (gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_895 = (1 - 1);

    {
        double tmp_call_15;

        {
            double p_int_0_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double p_int_1_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double z_w_con_c_full_0_in_0 = gpu_z_w_con_c_full[((tmp_index_881 + ((90 * tmp_index_883) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
            double z_w_con_c_full_1_in_0 = gpu_z_w_con_c_full[((tmp_index_893 + ((90 * tmp_index_895) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
            double w_con_e_out;

            ///////////////////
            // Tasklet code (T_l640_c640)
            w_con_e_out = ((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0));
            ///////////////////

            w_con_e = w_con_e_out;
        }
        {
            double w_con_e_0_in = w_con_e;
            double tmp_call_15_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            tmp_call_15_out = abs(w_con_e_0_in);
            ///////////////////

            tmp_call_15 = tmp_call_15_out;
        }
        {
            double cfl_w_limit_0_in = cfl_w_limit;
            double p_metrics_0_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
            double tmp_call_15_0_in = tmp_call_15;
            double _if_cond_29_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_29_out = (tmp_call_15_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
            ///////////////////

            _if_cond_29 = _if_cond_29_out;
        }

    }
    _if_cond_28 = (gpu_levelmask[(_for_it_52 - 1)] || gpu_levelmask[_for_it_52]);

    if (((_if_cond_28 == 1) && (_if_cond_29 == 1))) {
        {

            {
                double w_con_e_0_in = w_con_e;
                double tmp_call_17_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_call_17_out = abs(w_con_e_0_in);
                ///////////////////

                tmp_call_17 = tmp_call_17_out;
            }

        }
        tmp_index_927 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_929 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_939 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_941 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_951 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_953 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_963 = (gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_965 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_976 = (gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_978 = (1 - 1);
        tmp_index_985 = (gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_987 = (1 - 1);
        {
            double tmp_arg_19;
            double tmp_arg_18;
            double tmp_call_16;
            double difcoef;

            {
                double cfl_w_limit_0_in = cfl_w_limit;
                double dtime_0_in = dtime;
                double tmp_arg_18_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_arg_18_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                ///////////////////

                tmp_arg_18 = tmp_arg_18_out;
            }
            {
                double cfl_w_limit_0_in = cfl_w_limit;
                double dtime_0_in = dtime;
                double dtime_1_in = dtime;
                double p_metrics_0_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
                double tmp_call_17_0_in = tmp_call_17;
                double tmp_arg_19_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_arg_19_out = (((tmp_call_17_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
                ///////////////////

                tmp_arg_19 = tmp_arg_19_out;
            }
            {
                double tmp_arg_18_0_in = tmp_arg_18;
                double tmp_arg_19_0_in = tmp_arg_19;
                double tmp_call_16_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_call_16_out = min(tmp_arg_18_0_in, tmp_arg_19_0_in);
                ///////////////////

                tmp_call_16 = tmp_call_16_out;
            }
            {
                double scalfac_exdiff_0_in = scalfac_exdiff;
                double tmp_call_16_0_in = tmp_call_16;
                double difcoef_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                difcoef_out = (scalfac_exdiff_0_in * tmp_call_16_0_in);
                ///////////////////

                difcoef = difcoef_out;
            }
            {
                double difcoef_0_in = difcoef;
                double p_diag_0_in_ddt_vn_apc_pc_0 = gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)];
                double p_int_0_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_1_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_2_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_3_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_4_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_patch_0_in_edges_area_edge_0 = gpu___CG_p_patch__CG_edges__m_area_edge[(((__f2dace_SA_area_edge_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_1_in_edges_tangent_orientation_0 = gpu___CG_p_patch__CG_edges__m_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_2_in_edges_inv_primal_edge_length_0 = gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_47))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_53)];
                double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_929) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_927)];
                double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_941) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_939)];
                double p_prog_3_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_953) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_951)];
                double p_prog_4_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_965) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_963)];
                double zeta_0_in_0 = gpu_zeta[((tmp_index_976 + ((90 * tmp_index_978) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double zeta_1_in_0 = gpu_zeta[((tmp_index_985 + ((90 * tmp_index_987) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double p_diag_out_ddt_vn_apc_pc_0;

                ///////////////////
                // Tasklet code (T_l643_c643)
                p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                ///////////////////

                gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)] = p_diag_out_ddt_vn_apc_pc_0;
            }

        }
    }

}

DACE_DFI void loop_body_52_2_5(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int _for_it_4_0, int _for_it_5_0, int tmp_struct_symbol_8) {
    int tmp_index_92_0;
    int tmp_index_94_0;
    int tmp_index_104_0;
    int tmp_index_106_0;
    int tmp_index_116_0;
    int tmp_index_118_0;
    int tmp_index_128_0;
    int tmp_index_130_0;
    int tmp_index_140_0;
    int tmp_index_142_0;
    int tmp_index_152_0;
    int tmp_index_154_0;



    tmp_index_92_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_94_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_104_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_106_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_116_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_118_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_128_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_130_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_140_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_142_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_152_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_154_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);

    {

        {
            double ptr_int_0_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_1_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_2_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_3_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_4_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_5_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (6 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double vec_e_0_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
            double vec_e_1_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
            double vec_e_2_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
            double vec_e_3_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
            double vec_e_4_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
            double vec_e_5_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
            double rot_vec_out_0;

            ///////////////////
            // Tasklet code (T_l296_c296)
            rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
            ///////////////////

            gpu_zeta[(((_for_it_5_0 + ((90 * tmp_struct_symbol_8) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_8 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
        }

    }

}

DACE_DFI void loop_body_60_2_3(const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_diag__m_vt, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int _for_it_7, int _for_it_8) {
    int tmp_index_178;
    int tmp_index_180;
    int tmp_index_190;
    int tmp_index_192;
    int tmp_index_202;
    int tmp_index_204;
    int tmp_index_214;
    int tmp_index_216;



    tmp_index_178 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_180 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_190 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_192 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_202 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_204 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_214 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_216 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_p_prog_7);

    {

        {
            double p_int_0_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 1)];
            double p_int_1_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 2)];
            double p_int_2_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 3)];
            double p_int_3_in_rbf_vec_coeff_e_0 = gpu___CG_p_int__m_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6) + 4)];
            double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_180) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_178)];
            double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_192) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_190)];
            double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_204) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_202)];
            double p_prog_3_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_216) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_7))) + tmp_index_214)];
            double p_diag_out_vt_0;

            ///////////////////
            // Tasklet code (T_l441_c441)
            p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
            ///////////////////

            gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_7)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_8)] = p_diag_out_vt_0;
        }

    }

}

DACE_DFI void loop_body_67_2_5(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_ekinh, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int _for_it_23, int _for_it_24, int tmp_struct_symbol_10) {
    int tmp_index_407;
    int tmp_index_409;
    int tmp_index_419;
    int tmp_index_421;
    int tmp_index_431;
    int tmp_index_433;



    tmp_index_407 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_409 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_419 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_421 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_431 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_433 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);

    {

        {
            double p_int_0_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_1_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_2_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_409) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_407)];
            double z_kin_hor_e_1_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_421) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_419)];
            double z_kin_hor_e_2_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_433) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_431)];
            double z_ekinh_out_0;

            ///////////////////
            // Tasklet code (T_l515_c515)
            z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s * z_kin_hor_e_2_in_0));
            ///////////////////

            gpu_z_ekinh[(((_for_it_24 + ((90 * tmp_struct_symbol_10) * (_for_it_22 - 1))) + (tmp_struct_symbol_10 * (_for_it_23 - 1))) - 1)] = z_ekinh_out_0;
        }

    }

}

DACE_DFI void loop_body_67_2_7(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_w_concorr_me, double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int _for_it_25, int _for_it_26, int tmp_struct_symbol_0) {
    int tmp_index_445;
    int tmp_index_447;
    int tmp_index_457;
    int tmp_index_459;
    int tmp_index_469;
    int tmp_index_471;



    tmp_index_445 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_447 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);
    tmp_index_457 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_459 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);
    tmp_index_469 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s);
    tmp_index_471 = (gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s);

    {

        {
            double p_int_0_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double p_int_1_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double p_int_2_in_e_bln_c_s = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_26)];
            double z_w_concorr_me_0_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_447) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_445)];
            double z_w_concorr_me_1_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_459) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_457)];
            double z_w_concorr_me_2_in_0 = gpu_z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * tmp_index_471) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_25))) + tmp_index_469)];
            double z_w_concorr_mc_out_0;

            ///////////////////
            // Tasklet code (T_l521_c521)
            z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s * z_w_concorr_me_2_in_0));
            ///////////////////

            gpu_z_w_concorr_mc[((_for_it_26 + (tmp_struct_symbol_0 * (_for_it_25 - 1))) - 1)] = z_w_concorr_mc_out_0;
        }

    }

}

DACE_DFI void loop_body_85_2_6(const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int _for_it_48, int _for_it_49, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int tmp_index_698;
    int tmp_index_700;
    int tmp_index_710;
    int tmp_index_712;
    int tmp_index_724;
    int tmp_index_726;
    int tmp_index_733;
    int tmp_index_735;
    int tmp_index_745;
    int tmp_index_747;
    int tmp_index_757;
    int tmp_index_759;



    tmp_index_698 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_700 = (1 - 1);
    tmp_index_710 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_712 = (1 - 1);
    tmp_index_724 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_726 = (1 - 1);
    tmp_index_733 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_735 = (1 - 1);
    tmp_index_745 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_747 = (1 - 1);
    tmp_index_757 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_759 = (1 - 1);

    {

        {
            double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_48)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_1_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_2_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[(((((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47)) + (__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48) + 1))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_int_0_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_int_1_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_metrics_0_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_1_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_2_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_3_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_4_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_48)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_49)];
            double p_patch_0_in_edges_f_e_0 = gpu___CG_p_patch__CG_edges__m_f_e[(((__f2dace_SA_f_e_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_f_e_d_0_s_edges_p_patch_4) + _for_it_49)];
            double z_ekinh_0_in_0 = gpu_z_ekinh[((tmp_index_698 + ((90 * tmp_index_700) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_ekinh_1_in_0 = gpu_z_ekinh[((tmp_index_710 + ((90 * tmp_index_712) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_49)];
            double z_w_con_c_full_0_in_0 = gpu_z_w_con_c_full[((tmp_index_745 + ((90 * tmp_index_747) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double z_w_con_c_full_1_in_0 = gpu_z_w_con_c_full[((tmp_index_757 + ((90 * tmp_index_759) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double zeta_0_in_0 = gpu_zeta[((tmp_index_724 + ((90 * tmp_index_726) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double zeta_1_in_0 = gpu_zeta[((tmp_index_733 + ((90 * tmp_index_735) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double p_diag_out_ddt_vn_apc_pc_0;

            ///////////////////
            // Tasklet code (T_l611_c611)
            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
            ///////////////////

            gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_48))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_49)] = p_diag_out_ddt_vn_apc_pc_0;
        }

    }

}

DACE_DFI void loop_body_85_2_28(const double&  cfl_w_limit, const double&  dtime, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, const double&  scalfac_exdiff, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, int _for_it_52, int _for_it_53, int ntnd, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    double w_con_e;
    double tmp_call_17;
    double _if_cond_29;
    int tmp_index_881;
    int tmp_index_883;
    int tmp_index_893;
    int tmp_index_895;
    int _if_cond_28;
    int tmp_index_927;
    int tmp_index_929;
    int tmp_index_939;
    int tmp_index_941;
    int tmp_index_951;
    int tmp_index_953;
    int tmp_index_963;
    int tmp_index_965;
    int tmp_index_976;
    int tmp_index_978;
    int tmp_index_985;
    int tmp_index_987;



    tmp_index_881 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_883 = (1 - 1);
    tmp_index_893 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_895 = (1 - 1);

    {
        double tmp_call_15;

        {
            double p_int_0_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double p_int_1_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double z_w_con_c_full_0_in_0 = gpu_z_w_con_c_full[((tmp_index_881 + ((90 * tmp_index_883) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
            double z_w_con_c_full_1_in_0 = gpu_z_w_con_c_full[((tmp_index_893 + ((90 * tmp_index_895) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
            double w_con_e_out;

            ///////////////////
            // Tasklet code (T_l640_c640)
            w_con_e_out = ((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0));
            ///////////////////

            w_con_e = w_con_e_out;
        }
        {
            double w_con_e_0_in = w_con_e;
            double tmp_call_15_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            tmp_call_15_out = abs(w_con_e_0_in);
            ///////////////////

            tmp_call_15 = tmp_call_15_out;
        }
        {
            double cfl_w_limit_0_in = cfl_w_limit;
            double p_metrics_0_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
            double tmp_call_15_0_in = tmp_call_15;
            double _if_cond_29_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_29_out = (tmp_call_15_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
            ///////////////////

            _if_cond_29 = _if_cond_29_out;
        }

    }
    _if_cond_28 = (gpu_levelmask[(_for_it_52 - 1)] || gpu_levelmask[_for_it_52]);

    if (((_if_cond_28 == 1) && (_if_cond_29 == 1))) {
        {

            {
                double w_con_e_0_in = w_con_e;
                double tmp_call_17_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_call_17_out = abs(w_con_e_0_in);
                ///////////////////

                tmp_call_17 = tmp_call_17_out;
            }

        }
        tmp_index_927 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_929 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_939 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_941 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_951 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_953 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_963 = (gpu___CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_965 = (gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_976 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_978 = (1 - 1);
        tmp_index_985 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_987 = (1 - 1);
        {
            double tmp_arg_19;
            double tmp_arg_18;
            double tmp_call_16;
            double difcoef;

            {
                double cfl_w_limit_0_in = cfl_w_limit;
                double dtime_0_in = dtime;
                double tmp_arg_18_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_arg_18_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                ///////////////////

                tmp_arg_18 = tmp_arg_18_out;
            }
            {
                double cfl_w_limit_0_in = cfl_w_limit;
                double dtime_0_in = dtime;
                double dtime_1_in = dtime;
                double p_metrics_0_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
                double tmp_call_17_0_in = tmp_call_17;
                double tmp_arg_19_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_arg_19_out = (((tmp_call_17_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
                ///////////////////

                tmp_arg_19 = tmp_arg_19_out;
            }
            {
                double tmp_arg_18_0_in = tmp_arg_18;
                double tmp_arg_19_0_in = tmp_arg_19;
                double tmp_call_16_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                tmp_call_16_out = min(tmp_arg_18_0_in, tmp_arg_19_0_in);
                ///////////////////

                tmp_call_16 = tmp_call_16_out;
            }
            {
                double scalfac_exdiff_0_in = scalfac_exdiff;
                double tmp_call_16_0_in = tmp_call_16;
                double difcoef_out;

                ///////////////////
                // Tasklet code (T_l642_c642)
                difcoef_out = (scalfac_exdiff_0_in * tmp_call_16_0_in);
                ///////////////////

                difcoef = difcoef_out;
            }
            {
                double difcoef_0_in = difcoef;
                double p_diag_0_in_ddt_vn_apc_pc_0 = gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)];
                double p_int_0_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_1_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_2_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_3_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_4_in_geofac_grdiv_0 = gpu___CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_patch_0_in_edges_area_edge_0 = gpu___CG_p_patch__CG_edges__m_area_edge[(((__f2dace_SA_area_edge_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_1_in_edges_tangent_orientation_0 = gpu___CG_p_patch__CG_edges__m_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_2_in_edges_inv_primal_edge_length_0 = gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_47))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_53)];
                double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_929) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_927)];
                double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_941) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_939)];
                double p_prog_3_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_953) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_951)];
                double p_prog_4_in_vn_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_965) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_963)];
                double zeta_0_in_0 = gpu_zeta[((tmp_index_976 + ((90 * tmp_index_978) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double zeta_1_in_0 = gpu_zeta[((tmp_index_985 + ((90 * tmp_index_987) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double p_diag_out_ddt_vn_apc_pc_0;

                ///////////////////
                // Tasklet code (T_l643_c643)
                p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                ///////////////////

                gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)] = p_diag_out_ddt_vn_apc_pc_0;
            }

        }
    }

}



DACE_EXPORTED int __dace_init_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_kin_hor_e_d_2_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_vt_ie_d_2_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_A_z_w_concorr_me_d_2_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_area_d_0_s_cells_p_patch_2, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_c_lin_e_d_2_s_p_int_6, int __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SA_end_block_d_0_s_cells_p_patch_2, int __f2dace_SA_end_block_d_0_s_edges_p_patch_4, int __f2dace_SA_end_block_d_0_s_verts_p_patch_5, int __f2dace_SA_end_index_d_0_s_cells_p_patch_2, int __f2dace_SA_end_index_d_0_s_edges_p_patch_4, int __f2dace_SA_end_index_d_0_s_verts_p_patch_5, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SA_fn_e_d_0_s_edges_p_patch_4, int __f2dace_SA_ft_e_d_0_s_edges_p_patch_4, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_geofac_rot_d_2_s_p_int_6, int __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SA_neighbor_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SA_start_block_d_0_s_cells_p_patch_2, int __f2dace_SA_start_block_d_0_s_edges_p_patch_4, int __f2dace_SA_start_block_d_0_s_verts_p_patch_5, int __f2dace_SA_start_index_d_0_s_cells_p_patch_2, int __f2dace_SA_start_index_d_0_s_edges_p_patch_4, int __f2dace_SA_start_index_d_0_s_verts_p_patch_5, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_d_2_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vn_ie_d_2_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_vt_d_2_s_p_diag_9, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SA_w_d_2_s_p_prog_7, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SA_wgtfac_c_d_2_s_p_metrics_8, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfac_e_d_2_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_2_s_p_metrics_8, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_end_block_d_0_s_cells_p_patch_2, int __f2dace_SOA_end_block_d_0_s_edges_p_patch_4, int __f2dace_SOA_end_block_d_0_s_verts_p_patch_5, int __f2dace_SOA_end_index_d_0_s_cells_p_patch_2, int __f2dace_SOA_end_index_d_0_s_edges_p_patch_4, int __f2dace_SOA_end_index_d_0_s_verts_p_patch_5, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_start_block_d_0_s_cells_p_patch_2, int __f2dace_SOA_start_block_d_0_s_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_verts_p_patch_5, int __f2dace_SOA_start_index_d_0_s_cells_p_patch_2, int __f2dace_SOA_start_index_d_0_s_edges_p_patch_4, int __f2dace_SOA_start_index_d_0_s_verts_p_patch_5, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int tmp_struct_symbol_0, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_11, int tmp_struct_symbol_12, int tmp_struct_symbol_13, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_3, int tmp_struct_symbol_4, int tmp_struct_symbol_8, int tmp_struct_symbol_9) {
    int count;

    // Check that we are able to run cuda code
    if (cudaGetDeviceCount(&count) != cudaSuccess)
    {
        printf("ERROR: GPU drivers are not configured or cuda-capable device "
               "not found\n");
        return 1;
    }
    if (count == 0)
    {
        printf("ERROR: No cuda-capable devices found\n");
        return 2;
    }

    // Initialize cuda before we run the application
    float *dev_X;
    DACE_GPU_CHECK(cudaMalloc((void **) &dev_X, 1));
    DACE_GPU_CHECK(cudaFree(dev_X));

    

    __state->gpu_context = new dace::cuda::Context(1, 47);

    // Create cuda streams and events
    for(int i = 0; i < 1; ++i) {
        DACE_GPU_CHECK(cudaStreamCreateWithFlags(&__state->gpu_context->internal_streams[i], cudaStreamNonBlocking));
        __state->gpu_context->streams[i] = __state->gpu_context->internal_streams[i]; // Allow for externals to modify streams
    }
    for(int i = 0; i < 47; ++i) {
        DACE_GPU_CHECK(cudaEventCreateWithFlags(&__state->gpu_context->events[i], cudaEventDisableTiming));
    }

    

    return 0;
}

DACE_EXPORTED int __dace_exit_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state) {
    

    // Synchronize and check for CUDA errors
    int __err = static_cast<int>(__state->gpu_context->lasterror);
    if (__err == 0)
        __err = static_cast<int>(cudaDeviceSynchronize());

    // Destroy cuda streams and events
    for(int i = 0; i < 1; ++i) {
        DACE_GPU_CHECK(cudaStreamDestroy(__state->gpu_context->internal_streams[i]));
    }
    for(int i = 0; i < 47; ++i) {
        DACE_GPU_CHECK(cudaEventDestroy(__state->gpu_context->events[i]));
    }

    delete __state->gpu_context;
    return __err;
}

DACE_EXPORTED bool __dace_gpu_set_stream_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, int streamid, gpuStream_t stream)
{
    if (streamid < 0 || streamid >= 1)
        return false;

    __state->gpu_context->streams[streamid] = stream;

    return true;
}

DACE_EXPORTED void __dace_gpu_set_all_streams_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, gpuStream_t stream)
{
    for (int i = 0; i < 1; ++i)
        __state->gpu_context->streams[i] = stream;
}

__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0(const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_cells__m_edge_blk[((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * i2) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * i1)) + i0)];
                                uint8_t out;

                                ///////////////////
                                out = static_cast<uint8_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * i2) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2)
{

    if ((int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0_args[] = { (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, (void *)&__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0, dim3(int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_2_2_96_0_0", int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5(const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_edges__m_quad_blk[((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * i1)) + i0)];
                                uint8_t out;

                                ///////////////////
                                out = static_cast<uint8_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4)
{

    if ((int_ceil(int_ceil(__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5_args[] = { (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk, (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, (void *)&__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5, dim3(int_ceil(int_ceil(__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_2_2_96_0_5", int_ceil(int_ceil(__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10(const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_verts__m_edge_blk[((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * i2) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * i1)) + i0)];
                                uint8_t out;

                                ///////////////////
                                out = static_cast<uint8_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * i2) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5)
{

    if ((int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10_args[] = { (void *)&gpu___CG_p_patch__CG_verts__m_edge_blk, (void *)&gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, (void *)&__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10, dim3(int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_2_2_96_0_10", int_ceil(int_ceil(__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0(const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_cells__m_edge_idx[((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * i2) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * i1)) + i0)];
                                uint16_t out;

                                ///////////////////
                                out = static_cast<uint16_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * i2) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2)
{

    if ((int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0_args[] = { (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, (void *)&__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0, dim3(int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_2_2_4_0_0", int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5(const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_verts__m_edge_idx[((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * i2) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * i1)) + i0)];
                                uint16_t out;

                                ///////////////////
                                out = static_cast<uint16_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * i2) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5)
{

    if ((int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5_args[] = { (void *)&gpu___CG_p_patch__CG_verts__m_edge_idx, (void *)&gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, (void *)&__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5, dim3(int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_2_2_4_0_5", int_ceil(int_ceil(__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5, 1), 256), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, 1), 1), int_ceil(int_ceil(__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10(const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_edges__m_cell_idx[((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * i1)) + i0)];
                                uint16_t out;

                                ///////////////////
                                out = static_cast<uint16_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4)
{

    if ((int_ceil(int_ceil(__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10_args[] = { (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, (void *)&__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10, dim3(int_ceil(int_ceil(__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_2_2_4_0_10", int_ceil(int_ceil(__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15(const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_edges__m_vertex_idx[((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * i1)) + i0)];
                                uint16_t out;

                                ///////////////////
                                out = static_cast<uint16_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4)
{

    if ((int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15_args[] = { (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, (void *)&__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15, dim3(int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_2_2_4_0_15", int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20(const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4) {
    {
        {
            {
                int i2 = (blockIdx.x * 256 + threadIdx.x);
                int i1 = (blockIdx.y * 1 + threadIdx.y);
                int i0 = (blockIdx.z * 1 + threadIdx.z);
                if (i2 < __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4) {
                    {
                        {
                            {
                                int in = gpu___CG_p_patch__CG_edges__m_quad_idx[((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * i1)) + i0)];
                                uint16_t out;

                                ///////////////////
                                out = static_cast<uint16_t>(in);
                                ///////////////////

                                gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * i2) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * i1)) + i0)] = out;
                            }
                        }
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4);
void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4)
{

    if ((int_ceil(int_ceil(__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4, 1), 256)) == 0 || (int_ceil(int_ceil(__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, 1), 1)) == 0 || (int_ceil(int_ceil(__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, 1), 1)) == 0) {

        return;
    }

    void  *copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20_args[] = { (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx, (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, (void *)&__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4 };
    gpuError_t __err = cudaLaunchKernel((void*)copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20, dim3(int_ceil(int_ceil(__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, 1), 1)), dim3(256, 1, 1), copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_2_2_4_0_20", int_ceil(int_ceil(__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4, 1), 256), int_ceil(int_ceil(__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, 1), 1), int_ceil(int_ceil(__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, 1), 1), 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_8_2_6(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_5_0 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_120_0);
            int _for_it_4_0 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_5_0 >= i_startidx_var_120_0 && _for_it_5_0 < (i_endidx_var_121_0 + 1)) {
                if (_for_it_4_0 >= 1) {
                    loop_body_8_2_5(&gpu___CG_p_int__m_geofac_rot[0], &gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &gpu_zeta[0], __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_p_int_6, __f2dace_SA_geofac_rot_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_3_0, _for_it_4_0, _for_it_5_0, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_8_2_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_map_2_2_8_2_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_8_2_6_args[] = { (void *)&gpu___CG_p_int__m_geofac_rot, (void *)&gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_zeta, (void *)&__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_geofac_rot_d_0_s_p_int_6, (void *)&__f2dace_SA_geofac_rot_d_1_s_p_int_6, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, (void *)&__f2dace_SOA_geofac_rot_d_0_s_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_1_s_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_2_s_p_int_6, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&_for_it_3_0, (void *)&i_endidx_var_121_0, (void *)&i_startidx_var_120_0, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_8_2_6, dim3(int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_8_2_6_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_8_2_6", int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_16_2_4(double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        {
            int _for_it_8 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_7 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_8 >= i_startidx_var_148 && _for_it_8 < (i_endidx_var_149 + 1)) {
                if (_for_it_7 >= 1) {
                    loop_body_16_2_3(&gpu___CG_p_int__m_rbf_vec_coeff_e[0], &gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &gpu___CG_p_diag__m_vt[0], __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, _for_it_7, _for_it_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_16_2_4(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_map_2_2_16_2_4(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_16_2_4_args[] = { (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_int__m_rbf_vec_coeff_e, (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, (void *)&gpu___CG_p_prog__m_vn, (void *)&__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, (void *)&__f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_16_2_4, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_16_2_4_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_16_2_4", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_16_2_10(double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        {
            int _for_it_10 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_9 = ((blockIdx.y * 1 + threadIdx.y) + 2);
            double loop_body_tmp_call_2;
            double loop_body_tmp_call_1;
            if (_for_it_10 >= i_startidx_var_148 && _for_it_10 < (i_endidx_var_149 + 1)) {
                if (_for_it_9 >= 2) {
                    {
                        double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_10)];
                        double tmp_call_2_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_2_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                        ///////////////////

                        loop_body_tmp_call_2 = tmp_call_2_out;
                    }
                    {
                        double p_metrics_0_in_wgtfac_e_0 = gpu___CG_p_metrics__m_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8) + _for_it_10)];
                        double p_metrics_1_in_wgtfac_e_0 = gpu___CG_p_metrics__m_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8) + _for_it_10)];
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[(((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_p_prog_7 * (((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9) - 1))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double p_diag_out_vn_ie_0;

                        ///////////////////
                        // Tasklet code (T_l446_c446)
                        p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                        ///////////////////

                        gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_10)] = p_diag_out_vn_ie_0;
                    }
                    {
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double tmp_call_1_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_1_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                        ///////////////////

                        loop_body_tmp_call_1 = tmp_call_1_out;
                    }
                    {
                        double tmp_call_1_0_in = loop_body_tmp_call_1;
                        double tmp_call_2_0_in = loop_body_tmp_call_2;
                        double z_kin_hor_e_out_0;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        z_kin_hor_e_out_0 = (0.5 * (tmp_call_1_0_in + tmp_call_2_0_in));
                        ///////////////////

                        gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_10)] = z_kin_hor_e_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_16_2_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_0_map_2_2_16_2_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_16_2_10_args[] = { (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_wgtfac_e, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_kin_hor_e, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_16_2_10, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 89, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_16_2_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_16_2_10", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 89, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_2_map_2_2_16_3_10(double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        int _for_it_15 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
        double loop_body_tmp_call_4;
        double loop_body_tmp_call_3;
        if (_for_it_15 >= i_startidx_var_148 && _for_it_15 < (i_endidx_var_149 + 1)) {
            {
                double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_15)];
                double z_vt_ie_out_0;

                ///////////////////
                // Tasklet code (T_l465_c465)
                z_vt_ie_out_0 = p_diag_0_in_vt_0;
                ///////////////////

                gpu_z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s * __f2dace_A_z_vt_ie_d_1_s) * ((- __f2dace_OA_z_vt_ie_d_2_s) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s * (1 - __f2dace_OA_z_vt_ie_d_1_s))) - __f2dace_OA_z_vt_ie_d_0_s) + _for_it_15)] = z_vt_ie_out_0;
            }
            {
                double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_15)];
                double tmp_call_4_out;

                ///////////////////
                // Tasklet code (T_l466_c466)
                tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                ///////////////////

                loop_body_tmp_call_4 = tmp_call_4_out;
            }
            {
                double p_metrics_0_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_metrics_1_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_metrics_2_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (90 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (89 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (88 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_diag_out_vn_ie_0;

                ///////////////////
                // Tasklet code (T_l467_c467)
                p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                ///////////////////

                gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (91 - __f2dace_SOA_vn_ie_d_1_s_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
            }
            {
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_diag_out_vn_ie_0;

                ///////////////////
                // Tasklet code (T_l464_c464)
                p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                ///////////////////

                gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vn_ie_d_1_s_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
            }
            {
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double tmp_call_3_out;

                ///////////////////
                // Tasklet code (T_l466_c466)
                tmp_call_3_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                ///////////////////

                loop_body_tmp_call_3 = tmp_call_3_out;
            }
            {
                double tmp_call_3_0_in = loop_body_tmp_call_3;
                double tmp_call_4_0_in = loop_body_tmp_call_4;
                double z_kin_hor_e_out_0;

                ///////////////////
                // Tasklet code (T_l466_c466)
                z_kin_hor_e_out_0 = (0.5 * (tmp_call_3_0_in + tmp_call_4_0_in));
                ///////////////////

                gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s * (1 - __f2dace_OA_z_kin_hor_e_d_1_s))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_15)] = z_kin_hor_e_out_0;
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_2_2_16_3_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_2_map_2_2_16_3_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_2_map_2_2_16_3_10_args[] = { (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_wgtfacq_e, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_vt_ie, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_A_z_vt_ie_d_0_s, (void *)&__f2dace_A_z_vt_ie_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_OA_z_vt_ie_d_0_s, (void *)&__f2dace_OA_z_vt_ie_d_1_s, (void *)&__f2dace_OA_z_vt_ie_d_2_s, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_2_map_2_2_16_3_10, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_2_map_2_2_16_3_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_2_map_2_2_16_3_10", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_1_map_2_2_16_3_20(const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg) {
    {
        {
            int _for_it_14 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_13 = ((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg);
            if (_for_it_14 >= i_startidx_var_148 && _for_it_14 < (i_endidx_var_149 + 1)) {
                if (_for_it_13 >= nflatlev_jg) {
                    {
                        double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_13)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_14)];
                        double p_metrics_0_in_ddxn_z_full_0 = gpu___CG_p_metrics__m_ddxn_z_full[((((__f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8) + _for_it_14)];
                        double p_metrics_1_in_ddxt_z_full_0 = gpu___CG_p_metrics__m_ddxt_z_full[((((__f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8) + _for_it_14)];
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_13)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_14)];
                        double z_w_concorr_me_out_0;

                        ///////////////////
                        // Tasklet code (T_l459_c459)
                        z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                        ///////////////////

                        gpu_z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * ((- __f2dace_OA_z_w_concorr_me_d_2_s) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s) + _for_it_14)] = z_w_concorr_me_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_2_2_16_3_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg);
void __dace_runkernel_single_state_body_1_map_2_2_16_3_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((91 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_1_map_2_2_16_3_20_args[] = { (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_ddxn_z_full, (void *)&gpu___CG_p_metrics__m_ddxt_z_full, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_w_concorr_me, (void *)&__f2dace_A_z_w_concorr_me_d_0_s, (void *)&__f2dace_A_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_0_s, (void *)&__f2dace_OA_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_2_s, (void *)&__f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_1_map_2_2_16_3_20, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_1_map_2_2_16_3_20_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_1_map_2_2_16_3_20", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_23_2_11(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10) {
    {
        {
            int _for_it_24 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_23 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_24 >= i_startidx_var_148 && _for_it_24 < (i_endidx_var_149 + 1)) {
                if (_for_it_23 >= 1) {
                    loop_body_23_2_5(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[0], &gpu_z_kin_hor_e[0], &gpu_z_ekinh[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, _for_it_23, _for_it_24, tmp_struct_symbol_10);
                    {
                        double p_prog_0_in_w_0 = gpu___CG_p_prog__m_w[((((__f2dace_SA_w_d_0_s_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_p_prog_7) + _for_it_23)) + ((91 * __f2dace_SA_w_d_0_s_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_p_prog_7) + _for_it_24)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l532_c532)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        gpu_z_w_con_c[((_for_it_24 + (tmp_struct_symbol_1 * (_for_it_23 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_23_2_11(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10);
void __dace_runkernel_single_state_body_map_2_2_23_2_11(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_23_2_11_args[] = { (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_w_d_0_s_p_prog_7, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_w_d_0_s_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_p_prog_7, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_10 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_23_2_11, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_23_2_11_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_23_2_11", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_6_map_2_2_23_2_13(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0) {
    {
        {
            int _for_it_26 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_25 = ((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg);
            if (_for_it_26 >= i_startidx_var_148 && _for_it_26 < (i_endidx_var_149 + 1)) {
                if (_for_it_25 >= nflatlev_jg) {
                    loop_body_23_2_7(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[0], &gpu_z_w_concorr_me[0], &gpu_z_w_concorr_mc[0], __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, _for_it_25, _for_it_26, tmp_struct_symbol_0);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_6_map_2_2_23_2_13(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
void __dace_runkernel_single_state_body_6_map_2_2_23_2_13(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((91 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_6_map_2_2_23_2_13_args[] = { (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, (void *)&gpu_z_w_concorr_mc, (void *)&gpu_z_w_concorr_me, (void *)&__f2dace_A_z_w_concorr_me_d_0_s, (void *)&__f2dace_A_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_0_s, (void *)&__f2dace_OA_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_2_s, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_0 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_6_map_2_2_23_2_13, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_6_map_2_2_23_2_13_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_6_map_2_2_23_2_13", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_7_map_2_2_23_2_17(double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0) {
    {
        {
            int _for_it_28 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_27 = (((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg) + 1);
            if (_for_it_28 >= i_startidx_var_148 && _for_it_28 < (i_endidx_var_149 + 1)) {
                if (_for_it_27 >= (nflatlev_jg + 1)) {
                    {
                        double z_w_concorr_mc_0_in_0 = gpu_z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 1))) - 1)];
                        double z_w_concorr_mc_1_in_0 = gpu_z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 2))) - 1)];
                        double p_metrics_0_in_wgtfac_c_0 = gpu___CG_p_metrics__m_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8) + _for_it_28)];
                        double p_metrics_1_in_wgtfac_c_0 = gpu___CG_p_metrics__m_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8) + _for_it_28)];
                        double p_diag_out_w_concorr_c_0;

                        ///////////////////
                        // Tasklet code (T_l526_c526)
                        p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                        ///////////////////

                        gpu___CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9) + _for_it_27)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9) + _for_it_28)] = p_diag_out_w_concorr_c_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_7_map_2_2_23_2_17(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
void __dace_runkernel_single_state_body_7_map_2_2_23_2_17(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((90 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_7_map_2_2_23_2_17_args[] = { (void *)&gpu___CG_p_diag__m_w_concorr_c, (void *)&gpu___CG_p_metrics__m_wgtfac_c, (void *)&gpu_z_w_concorr_mc, (void *)&__f2dace_SA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_0 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_7_map_2_2_23_2_17, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_7_map_2_2_23_2_17_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_7_map_2_2_23_2_17", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_2_map_2_2_23_3_5(const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1) {
    {
        {
            int _for_it_33 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_32 = (((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg) + 1);
            if (_for_it_33 >= i_startidx_var_148 && _for_it_33 < (i_endidx_var_149 + 1)) {
                if (_for_it_32 >= (nflatlev_jg + 1)) {
                    {
                        double p_diag_0_in_w_concorr_c_0 = gpu___CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9) + _for_it_32)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9) + _for_it_33)];
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l540_c540)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        gpu_z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_2_2_23_3_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
void __dace_runkernel_single_state_body_2_map_2_2_23_3_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((90 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_2_map_2_2_23_3_5_args[] = { (void *)&gpu___CG_p_diag__m_w_concorr_c, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_1 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_2_map_2_2_23_3_5, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_2_map_2_2_23_3_5_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_2_map_2_2_23_3_5", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_23_3_12(const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14) {
    {
        {
            int _for_it_36 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_35 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            double loop_body_tmp_call_7;
            if (_for_it_36 >= i_startidx_var_148 && _for_it_36 < (i_endidx_var_149 + 1)) {
                if (_for_it_35 >= Max(3, (nrdmax_jg - 2))) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_36 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)];
                        double tmp_call_7_out;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        tmp_call_7_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        loop_body_tmp_call_7 = tmp_call_7_out;
                    }
                    {
                        double tmp_call_7_0_in = loop_body_tmp_call_7;
                        double p_metrics_0_in_ddqz_z_half_0 = gpu___CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_36)];
                        double cfl_w_limit_0_in = cfl_w_limit;
                        uint8_t cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        cfl_clipping_out_0 = (tmp_call_7_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        gpu_cfl_clipping[((_for_it_36 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)] = cfl_clipping_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_23_3_12(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
void __dace_runkernel_single_state_body_4_map_2_2_23_3_12(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_23_3_12_args[] = { (void *)&gpu___CG_p_metrics__m_ddqz_z_half, (void *)&gpu_cfl_clipping, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&cfl_w_limit, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_14 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_23_3_12, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_4_map_2_2_23_3_12_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_23_3_12", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_23_4_6(const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14) {
    {
        int _for_it_35 = ((blockIdx.x * 256 + threadIdx.x) + Max(3, (nrdmax_jg - 2)));
        if (_for_it_35 >= Max(3, (nrdmax_jg - 2)) && _for_it_35 < 88) {
            loop_body_23_4_0(&gpu_cfl_clipping[0], &gpu_levmask[0], _for_it_22, _for_it_35, tmp_struct_symbol_14);
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_23_4_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14);
void __dace_runkernel_single_state_body_4_map_2_2_23_4_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14)
{

    if ((int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_23_4_6_args[] = { (void *)&gpu_cfl_clipping, (void *)&gpu_levmask, (void *)&_for_it_22, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_14 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_23_4_6, dim3(int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_4_map_2_2_23_4_6_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_23_4_6", int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_23_4_18(const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4) {
    {
        {
            int _for_it_37 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_35 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            if (_for_it_37 >= i_startidx_var_148 && _for_it_37 < (i_endidx_var_149 + 1)) {
                if (_for_it_35 >= Max(3, (nrdmax_jg - 2))) {
                    loop_body_23_4_10(dtime, &gpu___CG_p_metrics__m_ddqz_z_half[0], &gpu_cfl_clipping[0], &gpu_maxvcfl_arr[((88 * tmp_struct_symbol_4) * (_for_it_22 - 1))], &gpu_z_w_con_c[0], __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, _for_it_35, _for_it_37, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_23_4_18(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4);
void __dace_runkernel_single_state_body_4_map_2_2_23_4_18(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_23_4_18_args[] = { (void *)&gpu___CG_p_metrics__m_ddqz_z_half, (void *)&gpu_cfl_clipping, (void *)&gpu_maxvcfl_arr, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&dtime, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_14, (void *)&tmp_struct_symbol_4 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_23_4_18, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_4_map_2_2_23_4_18_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_23_4_18", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_5_map_2_2_23_4_16(const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2) {
    {
        {
            int _for_it_39 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_38 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_39 >= i_startidx_var_148 && _for_it_39 < (i_endidx_var_149 + 1)) {
                if (_for_it_38 >= 1) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_39 + (tmp_struct_symbol_1 * (_for_it_38 - 1))) - 1)];
                        double z_w_con_c_1_in_0 = gpu_z_w_con_c[(((_for_it_38 * tmp_struct_symbol_1) + _for_it_39) - 1)];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l569_c569)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        gpu_z_w_con_c_full[(((_for_it_39 + ((90 * tmp_struct_symbol_2) * (_for_it_22 - 1))) + (tmp_struct_symbol_2 * (_for_it_38 - 1))) - 1)] = z_w_con_c_full_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_5_map_2_2_23_4_16(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
void __dace_runkernel_single_state_body_5_map_2_2_23_4_16(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_5_map_2_2_23_4_16_args[] = { (void *)&gpu_z_w_con_c, (void *)&gpu_z_w_con_c_full, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_2 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_5_map_2_2_23_4_16, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_5_map_2_2_23_4_16_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_5_map_2_2_23_4_16", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_7_0_56(uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13) {
    {
        int _for_it_46 = ((blockIdx.x * 256 + threadIdx.x) + Max(3, (nrdmax_jg - 2)));
        if (_for_it_46 >= Max(3, (nrdmax_jg - 2)) && _for_it_46 < 88) {
            {
                int size;

                ///////////////////
                // Tasklet code (size_reduce_scan)
                size = ((replaced_var_3 + 1) - replaced_var_2);
                ///////////////////

                loop_body_reduce_scan_size = size;
            }
            {
                int in_size = loop_body_reduce_scan_size;
                const uint8_t * in_arr = &gpu_levmask[((_for_it_46 + (90 * replaced_var_2)) - 91)];
                uint8_t out;

                ///////////////////

                #define __REDUCE_GPU__

                #ifdef __REDUCE_DEVICE__
                out = reduce_scan_device(in_arr, in_size);
                #elif defined(__REDUCE_GPU__)
                out = reduce_scan_gpu(in_arr, in_size, __dace_current_stream);
                #else
                out = reduce_scan_cpu(in_arr, in_size);
                #endif

                #undef __REDUCE_GPU__

                ///////////////////

                gpu_levelmask[(_for_it_46 - 1)] = out;
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_7_0_56(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13);
void __dace_runkernel_single_state_body_0_map_2_2_7_0_56(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13)
{

    if ((int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_7_0_56_args[] = { (void *)&gpu_levelmask, (void *)&gpu_levmask, (void *)&loop_body_reduce_scan_size, (void *)&nrdmax_jg, (void *)&replaced_var_2, (void *)&replaced_var_3, (void *)&tmp_struct_symbol_13 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_7_0_56, dim3(int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_7_0_56_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_7_0_56", int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_41_2_7(double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_49 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_48 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_49 >= i_startidx_var_148 && _for_it_49 < (i_endidx_var_149 + 1)) {
                if (_for_it_48 >= 1) {
                    loop_body_41_2_6(&gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[0], &gpu_z_ekinh[0], &gpu_z_kin_hor_e[0], &gpu_z_w_con_c_full[0], &gpu_zeta[0], &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_f_e_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_47, _for_it_48, _for_it_49, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_41_2_7(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_0_map_2_2_41_2_7(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_41_2_7_args[] = { (void *)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_int__m_c_lin_e, (void *)&gpu___CG_p_metrics__m_coeff_gradekin, (void *)&gpu___CG_p_metrics__m_ddqz_z_full_e, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, (void *)&gpu___CG_p_patch__CG_edges__m_f_e, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c_full, (void *)&gpu_zeta, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, (void *)&__f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, (void *)&__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SA_f_e_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, (void *)&__f2dace_SOA_f_e_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_f_e_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_47, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&ntnd, (void *)&tmp_struct_symbol_10, (void *)&tmp_struct_symbol_2, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_41_2_7, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_41_2_7_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_41_2_7", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_41_2_29(double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_53 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_52 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            if (_for_it_53 >= i_startidx_var_148 && _for_it_53 < (i_endidx_var_149 + 1)) {
                if (_for_it_52 >= Max(3, (nrdmax_jg - 2))) {
                    loop_body_41_2_28(cfl_w_limit, dtime, &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_int__m_geofac_grdiv[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_area_edge[0], &gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &gpu_levelmask[0], &gpu_z_w_con_c_full[0], &gpu_zeta[0], scalfac_exdiff, &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_47, _for_it_52, _for_it_53, ntnd, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_41_2_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_map_2_2_41_2_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_41_2_29_args[] = { (void *)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (void *)&gpu___CG_p_int__m_c_lin_e, (void *)&gpu___CG_p_int__m_geofac_grdiv, (void *)&gpu___CG_p_metrics__m_ddqz_z_full_e, (void *)&gpu___CG_p_patch__CG_edges__m_area_edge, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, (void *)&gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, (void *)&gpu___CG_p_patch__CG_edges__m_tangent_orientation, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_levelmask, (void *)&gpu_z_w_con_c_full, (void *)&gpu_zeta, (void *)&__f2dace_SA_area_edge_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SA_geofac_grdiv_d_0_s_p_int_6, (void *)&__f2dace_SA_geofac_grdiv_d_1_s_p_int_6, (void *)&__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, (void *)&__f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, (void *)&__f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, (void *)&__f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, (void *)&__f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&_for_it_47, (void *)&cfl_w_limit, (void *)&dtime, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&ntnd, (void *)&scalfac_exdiff, (void *)&tmp_struct_symbol_2, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_41_2_29, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_map_2_2_41_2_29_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_41_2_29", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_52_2_6(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_5_0 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_120_0);
            int _for_it_4_0 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_5_0 >= i_startidx_var_120_0 && _for_it_5_0 < (i_endidx_var_121_0 + 1)) {
                if (_for_it_4_0 >= 1) {
                    loop_body_52_2_5(&gpu___CG_p_int__m_geofac_rot[0], &gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_verts__m_edge_idx[0], &gpu___CG_p_prog__m_vn[0], &gpu_zeta[0], __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_p_int_6, __f2dace_SA_geofac_rot_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_3_0, _for_it_4_0, _for_it_5_0, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_52_2_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_map_2_2_52_2_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_52_2_6_args[] = { (void *)&gpu___CG_p_int__m_geofac_rot, (void *)&gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_verts__m_edge_idx, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_zeta, (void *)&__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, (void *)&__f2dace_SA_geofac_rot_d_0_s_p_int_6, (void *)&__f2dace_SA_geofac_rot_d_1_s_p_int_6, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, (void *)&__f2dace_SOA_geofac_rot_d_0_s_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_1_s_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_2_s_p_int_6, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&_for_it_3_0, (void *)&i_endidx_var_121_0, (void *)&i_startidx_var_120_0, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_52_2_6, dim3(int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_52_2_6_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_52_2_6", int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_60_2_4(double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        {
            int _for_it_8 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_7 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_8 >= i_startidx_var_148 && _for_it_8 < (i_endidx_var_149 + 1)) {
                if (_for_it_7 >= 1) {
                    loop_body_60_2_3(&gpu___CG_p_int__m_rbf_vec_coeff_e[0], &gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &gpu___CG_p_prog__m_vn[0], &gpu___CG_p_diag__m_vt[0], __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, _for_it_7, _for_it_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_60_2_4(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_map_2_2_60_2_4(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_60_2_4_args[] = { (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_int__m_rbf_vec_coeff_e, (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx, (void *)&gpu___CG_p_prog__m_vn, (void *)&__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, (void *)&__f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_60_2_4, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_60_2_4_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_60_2_4", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_60_2_10(double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        {
            int _for_it_10 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_9 = ((blockIdx.y * 1 + threadIdx.y) + 2);
            double loop_body_tmp_call_2;
            double loop_body_tmp_call_1;
            if (_for_it_10 >= i_startidx_var_148 && _for_it_10 < (i_endidx_var_149 + 1)) {
                if (_for_it_9 >= 2) {
                    {
                        double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_10)];
                        double tmp_call_2_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_2_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                        ///////////////////

                        loop_body_tmp_call_2 = tmp_call_2_out;
                    }
                    {
                        double p_metrics_0_in_wgtfac_e_0 = gpu___CG_p_metrics__m_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8) + _for_it_10)];
                        double p_metrics_1_in_wgtfac_e_0 = gpu___CG_p_metrics__m_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8) + _for_it_10)];
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[(((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_p_prog_7 * (((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9) - 1))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double p_diag_out_vn_ie_0;

                        ///////////////////
                        // Tasklet code (T_l446_c446)
                        p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                        ///////////////////

                        gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_10)] = p_diag_out_vn_ie_0;
                    }
                    {
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_10)];
                        double tmp_call_1_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_1_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                        ///////////////////

                        loop_body_tmp_call_1 = tmp_call_1_out;
                    }
                    {
                        double tmp_call_1_0_in = loop_body_tmp_call_1;
                        double tmp_call_2_0_in = loop_body_tmp_call_2;
                        double z_kin_hor_e_out_0;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        z_kin_hor_e_out_0 = (0.5 * (tmp_call_1_0_in + tmp_call_2_0_in));
                        ///////////////////

                        gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_10)] = z_kin_hor_e_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_60_2_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_0_map_2_2_60_2_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_60_2_10_args[] = { (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_wgtfac_e, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_kin_hor_e, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_60_2_10, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 89, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_60_2_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_60_2_10", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 89, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_2_map_2_2_60_3_10(double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148) {
    {
        int _for_it_15 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
        double loop_body_tmp_call_4;
        double loop_body_tmp_call_3;
        if (_for_it_15 >= i_startidx_var_148 && _for_it_15 < (i_endidx_var_149 + 1)) {
            {
                double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_15)];
                double z_vt_ie_out_0;

                ///////////////////
                // Tasklet code (T_l465_c465)
                z_vt_ie_out_0 = p_diag_0_in_vt_0;
                ///////////////////

                gpu_z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s * __f2dace_A_z_vt_ie_d_1_s) * ((- __f2dace_OA_z_vt_ie_d_2_s) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s * (1 - __f2dace_OA_z_vt_ie_d_1_s))) - __f2dace_OA_z_vt_ie_d_0_s) + _for_it_15)] = z_vt_ie_out_0;
            }
            {
                double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_15)];
                double tmp_call_4_out;

                ///////////////////
                // Tasklet code (T_l466_c466)
                tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                ///////////////////

                loop_body_tmp_call_4 = tmp_call_4_out;
            }
            {
                double p_metrics_0_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_metrics_1_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_metrics_2_in_wgtfacq_e_0 = gpu___CG_p_metrics__m_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8) + _for_it_15)];
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (90 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_prog_1_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (89 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_prog_2_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (88 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_diag_out_vn_ie_0;

                ///////////////////
                // Tasklet code (T_l467_c467)
                p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                ///////////////////

                gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (91 - __f2dace_SOA_vn_ie_d_1_s_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
            }
            {
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double p_diag_out_vn_ie_0;

                ///////////////////
                // Tasklet code (T_l464_c464)
                p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                ///////////////////

                gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (1 - __f2dace_SOA_vn_ie_d_1_s_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
            }
            {
                double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_15)];
                double tmp_call_3_out;

                ///////////////////
                // Tasklet code (T_l466_c466)
                tmp_call_3_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                ///////////////////

                loop_body_tmp_call_3 = tmp_call_3_out;
            }
            {
                double tmp_call_3_0_in = loop_body_tmp_call_3;
                double tmp_call_4_0_in = loop_body_tmp_call_4;
                double z_kin_hor_e_out_0;

                ///////////////////
                // Tasklet code (T_l466_c466)
                z_kin_hor_e_out_0 = (0.5 * (tmp_call_3_0_in + tmp_call_4_0_in));
                ///////////////////

                gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s * (1 - __f2dace_OA_z_kin_hor_e_d_1_s))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_15)] = z_kin_hor_e_out_0;
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_2_2_60_3_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
void __dace_runkernel_single_state_body_2_map_2_2_60_3_10(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_2_map_2_2_60_3_10_args[] = { (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_wgtfacq_e, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_vt_ie, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_A_z_vt_ie_d_0_s, (void *)&__f2dace_A_z_vt_ie_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_OA_z_vt_ie_d_0_s, (void *)&__f2dace_OA_z_vt_ie_d_1_s, (void *)&__f2dace_OA_z_vt_ie_d_2_s, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_2_map_2_2_60_3_10, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_2_map_2_2_60_3_10_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_2_map_2_2_60_3_10", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_1_map_2_2_60_3_20(const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg) {
    {
        {
            int _for_it_14 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_13 = ((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg);
            if (_for_it_14 >= i_startidx_var_148 && _for_it_14 < (i_endidx_var_149 + 1)) {
                if (_for_it_13 >= nflatlev_jg) {
                    {
                        double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_13)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_14)];
                        double p_metrics_0_in_ddxn_z_full_0 = gpu___CG_p_metrics__m_ddxn_z_full[((((__f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8) + _for_it_14)];
                        double p_metrics_1_in_ddxt_z_full_0 = gpu___CG_p_metrics__m_ddxt_z_full[((((__f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8) + _for_it_14)];
                        double p_prog_0_in_vn_0 = gpu___CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_13)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_14)];
                        double z_w_concorr_me_out_0;

                        ///////////////////
                        // Tasklet code (T_l459_c459)
                        z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                        ///////////////////

                        gpu_z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s * __f2dace_A_z_w_concorr_me_d_1_s) * ((- __f2dace_OA_z_w_concorr_me_d_2_s) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s * ((- __f2dace_OA_z_w_concorr_me_d_1_s) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s) + _for_it_14)] = z_w_concorr_me_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_2_2_60_3_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg);
void __dace_runkernel_single_state_body_1_map_2_2_60_3_20(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((91 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_1_map_2_2_60_3_20_args[] = { (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_metrics__m_ddxn_z_full, (void *)&gpu___CG_p_metrics__m_ddxt_z_full, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_z_w_concorr_me, (void *)&__f2dace_A_z_w_concorr_me_d_0_s, (void *)&__f2dace_A_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_0_s, (void *)&__f2dace_OA_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_2_s, (void *)&__f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_6, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_1_map_2_2_60_3_20, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_1_map_2_2_60_3_20_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_1_map_2_2_60_3_20", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_67_2_11(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10) {
    {
        {
            int _for_it_24 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_23 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_24 >= i_startidx_var_148 && _for_it_24 < (i_endidx_var_149 + 1)) {
                if (_for_it_23 >= 1) {
                    loop_body_67_2_5(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &gpu_z_kin_hor_e[0], &gpu_z_ekinh[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, _for_it_23, _for_it_24, tmp_struct_symbol_10);
                    {
                        double p_prog_0_in_w_0 = gpu___CG_p_prog__m_w[((((__f2dace_SA_w_d_0_s_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_p_prog_7) + _for_it_23)) + ((91 * __f2dace_SA_w_d_0_s_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_p_prog_7) + _for_it_24)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l532_c532)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        gpu_z_w_con_c[((_for_it_24 + (tmp_struct_symbol_1 * (_for_it_23 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_67_2_11(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10);
void __dace_runkernel_single_state_body_map_2_2_67_2_11(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_67_2_11_args[] = { (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_w_d_0_s_p_prog_7, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_w_d_0_s_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_p_prog_7, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_10 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_67_2_11, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_2_2_67_2_11_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_67_2_11", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_6_map_2_2_67_2_13(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0) {
    {
        {
            int _for_it_26 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_25 = ((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg);
            if (_for_it_26 >= i_startidx_var_148 && _for_it_26 < (i_endidx_var_149 + 1)) {
                if (_for_it_25 >= nflatlev_jg) {
                    loop_body_67_2_7(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &gpu_z_w_concorr_me[0], &gpu_z_w_concorr_mc[0], __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, _for_it_25, _for_it_26, tmp_struct_symbol_0);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_6_map_2_2_67_2_13(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
void __dace_runkernel_single_state_body_6_map_2_2_67_2_13(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((91 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_6_map_2_2_67_2_13_args[] = { (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx, (void *)&gpu_z_w_concorr_mc, (void *)&gpu_z_w_concorr_me, (void *)&__f2dace_A_z_w_concorr_me_d_0_s, (void *)&__f2dace_A_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_0_s, (void *)&__f2dace_OA_z_w_concorr_me_d_1_s, (void *)&__f2dace_OA_z_w_concorr_me_d_2_s, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_0 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_6_map_2_2_67_2_13, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_6_map_2_2_67_2_13_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_6_map_2_2_67_2_13", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((91 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_7_map_2_2_67_2_17(double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0) {
    {
        {
            int _for_it_28 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_27 = (((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg) + 1);
            if (_for_it_28 >= i_startidx_var_148 && _for_it_28 < (i_endidx_var_149 + 1)) {
                if (_for_it_27 >= (nflatlev_jg + 1)) {
                    {
                        double z_w_concorr_mc_0_in_0 = gpu_z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 1))) - 1)];
                        double z_w_concorr_mc_1_in_0 = gpu_z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 2))) - 1)];
                        double p_metrics_0_in_wgtfac_c_0 = gpu___CG_p_metrics__m_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8) + _for_it_28)];
                        double p_metrics_1_in_wgtfac_c_0 = gpu___CG_p_metrics__m_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8) + _for_it_28)];
                        double p_diag_out_w_concorr_c_0;

                        ///////////////////
                        // Tasklet code (T_l526_c526)
                        p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                        ///////////////////

                        gpu___CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9) + _for_it_27)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9) + _for_it_28)] = p_diag_out_w_concorr_c_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_7_map_2_2_67_2_17(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
void __dace_runkernel_single_state_body_7_map_2_2_67_2_17(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((90 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_7_map_2_2_67_2_17_args[] = { (void *)&gpu___CG_p_diag__m_w_concorr_c, (void *)&gpu___CG_p_metrics__m_wgtfac_c, (void *)&gpu_z_w_concorr_mc, (void *)&__f2dace_SA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, (void *)&__f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_0 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_7_map_2_2_67_2_17, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_7_map_2_2_67_2_17_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_7_map_2_2_67_2_17", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_2_map_2_2_67_3_5(const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1) {
    {
        {
            int _for_it_33 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_32 = (((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg) + 1);
            if (_for_it_33 >= i_startidx_var_148 && _for_it_33 < (i_endidx_var_149 + 1)) {
                if (_for_it_32 >= (nflatlev_jg + 1)) {
                    {
                        double p_diag_0_in_w_concorr_c_0 = gpu___CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9) + _for_it_32)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9) + _for_it_33)];
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l540_c540)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        gpu_z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_2_2_67_3_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
void __dace_runkernel_single_state_body_2_map_2_2_67_3_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((90 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_2_map_2_2_67_3_5_args[] = { (void *)&gpu___CG_p_diag__m_w_concorr_c, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_1 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_2_map_2_2_67_3_5, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_2_map_2_2_67_3_5_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_2_map_2_2_67_3_5", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_67_3_12(const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14) {
    {
        {
            int _for_it_36 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_35 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            double loop_body_tmp_call_7;
            if (_for_it_36 >= i_startidx_var_148 && _for_it_36 < (i_endidx_var_149 + 1)) {
                if (_for_it_35 >= Max(3, (nrdmax_jg - 2))) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_36 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)];
                        double tmp_call_7_out;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        tmp_call_7_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        loop_body_tmp_call_7 = tmp_call_7_out;
                    }
                    {
                        double tmp_call_7_0_in = loop_body_tmp_call_7;
                        double p_metrics_0_in_ddqz_z_half_0 = gpu___CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_36)];
                        double cfl_w_limit_0_in = cfl_w_limit;
                        uint8_t cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        cfl_clipping_out_0 = (tmp_call_7_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        gpu_cfl_clipping[((_for_it_36 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)] = cfl_clipping_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_67_3_12(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
void __dace_runkernel_single_state_body_4_map_2_2_67_3_12(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_67_3_12_args[] = { (void *)&gpu___CG_p_metrics__m_ddqz_z_half, (void *)&gpu_cfl_clipping, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&cfl_w_limit, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_14 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_67_3_12, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_4_map_2_2_67_3_12_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_67_3_12", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_67_4_6(const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14) {
    {
        int _for_it_35 = ((blockIdx.x * 256 + threadIdx.x) + Max(3, (nrdmax_jg - 2)));
        if (_for_it_35 >= Max(3, (nrdmax_jg - 2)) && _for_it_35 < 88) {
            loop_body_23_4_0(&gpu_cfl_clipping[0], &gpu_levmask[0], _for_it_22, _for_it_35, tmp_struct_symbol_14);
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_67_4_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14);
void __dace_runkernel_single_state_body_4_map_2_2_67_4_6(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14)
{

    if ((int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_67_4_6_args[] = { (void *)&gpu_cfl_clipping, (void *)&gpu_levmask, (void *)&_for_it_22, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_14 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_67_4_6, dim3(int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_4_map_2_2_67_4_6_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_67_4_6", int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_4_map_2_2_67_4_18(const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4) {
    {
        {
            int _for_it_37 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_35 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            if (_for_it_37 >= i_startidx_var_148 && _for_it_37 < (i_endidx_var_149 + 1)) {
                if (_for_it_35 >= Max(3, (nrdmax_jg - 2))) {
                    loop_body_23_4_10(dtime, &gpu___CG_p_metrics__m_ddqz_z_half[0], &gpu_cfl_clipping[0], &gpu_maxvcfl_arr[((88 * tmp_struct_symbol_4) * (_for_it_22 - 1))], &gpu_z_w_con_c[0], __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, _for_it_35, _for_it_37, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_2_2_67_4_18(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4);
void __dace_runkernel_single_state_body_4_map_2_2_67_4_18(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_4_map_2_2_67_4_18_args[] = { (void *)&gpu___CG_p_metrics__m_ddqz_z_half, (void *)&gpu_cfl_clipping, (void *)&gpu_maxvcfl_arr, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, (void *)&_for_it_22, (void *)&dtime, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_14, (void *)&tmp_struct_symbol_4 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_4_map_2_2_67_4_18, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_4_map_2_2_67_4_18_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_4_map_2_2_67_4_18", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_5_map_2_2_67_4_16(const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2) {
    {
        {
            int _for_it_39 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_38 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_39 >= i_startidx_var_148 && _for_it_39 < (i_endidx_var_149 + 1)) {
                if (_for_it_38 >= 1) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_39 + (tmp_struct_symbol_1 * (_for_it_38 - 1))) - 1)];
                        double z_w_con_c_1_in_0 = gpu_z_w_con_c[(((_for_it_38 * tmp_struct_symbol_1) + _for_it_39) - 1)];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l569_c569)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        gpu_z_w_con_c_full[(((_for_it_39 + ((90 * tmp_struct_symbol_2) * (_for_it_22 - 1))) + (tmp_struct_symbol_2 * (_for_it_38 - 1))) - 1)] = z_w_con_c_full_out_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_5_map_2_2_67_4_16(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
void __dace_runkernel_single_state_body_5_map_2_2_67_4_16(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_5_map_2_2_67_4_16_args[] = { (void *)&gpu_z_w_con_c, (void *)&gpu_z_w_con_c_full, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_2 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_5_map_2_2_67_4_16, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_5_map_2_2_67_4_16_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_5_map_2_2_67_4_16", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_51_0_56(uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13) {
    {
        int _for_it_46 = ((blockIdx.x * 256 + threadIdx.x) + Max(3, (nrdmax_jg - 2)));
        if (_for_it_46 >= Max(3, (nrdmax_jg - 2)) && _for_it_46 < 88) {
            {
                int size;

                ///////////////////
                // Tasklet code (size_reduce_scan)
                size = ((replaced_var_3 + 1) - replaced_var_2);
                ///////////////////

                loop_body_reduce_scan_size = size;
            }
            {
                int in_size = loop_body_reduce_scan_size;
                const uint8_t * in_arr = &gpu_levmask[((_for_it_46 + (90 * replaced_var_2)) - 91)];
                uint8_t out;

                ///////////////////

                #define __REDUCE_GPU__

                #ifdef __REDUCE_DEVICE__
                out = reduce_scan_device(in_arr, in_size);
                #elif defined(__REDUCE_GPU__)
                out = reduce_scan_gpu(in_arr, in_size, __dace_current_stream);
                #else
                out = reduce_scan_cpu(in_arr, in_size);
                #endif

                #undef __REDUCE_GPU__

                ///////////////////

                gpu_levelmask[(_for_it_46 - 1)] = out;
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_51_0_56(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13);
void __dace_runkernel_single_state_body_0_map_2_2_51_0_56(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13)
{

    if ((int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_51_0_56_args[] = { (void *)&gpu_levelmask, (void *)&gpu_levmask, (void *)&loop_body_reduce_scan_size, (void *)&nrdmax_jg, (void *)&replaced_var_2, (void *)&replaced_var_3, (void *)&tmp_struct_symbol_13 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_51_0_56, dim3(int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_51_0_56_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_51_0_56", int_ceil(int_ceil((88 - Max(3, (nrdmax_jg - 2))), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_2_2_85_2_7(double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_49 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_48 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_49 >= i_startidx_var_148 && _for_it_49 < (i_endidx_var_149 + 1)) {
                if (_for_it_48 >= 1) {
                    loop_body_85_2_6(&gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu_z_ekinh[0], &gpu_z_kin_hor_e[0], &gpu_z_w_con_c_full[0], &gpu_zeta[0], &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_f_e_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_47, _for_it_48, _for_it_49, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_2_2_85_2_7(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_0_map_2_2_85_2_7(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_2_2_85_2_7_args[] = { (void *)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_int__m_c_lin_e, (void *)&gpu___CG_p_metrics__m_coeff_gradekin, (void *)&gpu___CG_p_metrics__m_ddqz_z_full_e, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx, (void *)&gpu___CG_p_patch__CG_edges__m_f_e, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c_full, (void *)&gpu_zeta, (void *)&__f2dace_A_z_kin_hor_e_d_0_s, (void *)&__f2dace_A_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s, (void *)&__f2dace_SA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, (void *)&__f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, (void *)&__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SA_f_e_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, (void *)&__f2dace_SOA_f_e_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_f_e_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_vn_ie_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_p_diag_9, (void *)&_for_it_47, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&ntnd, (void *)&tmp_struct_symbol_10, (void *)&tmp_struct_symbol_2, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_2_2_85_2_7, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_0_map_2_2_85_2_7_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_2_2_85_2_7", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_2_2_85_2_29(double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_53 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_52 = ((blockIdx.y * 1 + threadIdx.y) + Max(3, (nrdmax_jg - 2)));
            if (_for_it_53 >= i_startidx_var_148 && _for_it_53 < (i_endidx_var_149 + 1)) {
                if (_for_it_52 >= Max(3, (nrdmax_jg - 2))) {
                    loop_body_85_2_28(cfl_w_limit, dtime, &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_int__m_geofac_grdiv[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_area_edge[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu___CG_p_prog__m_vn[0], &gpu_levelmask[0], &gpu_z_w_con_c_full[0], &gpu_zeta[0], scalfac_exdiff, &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_47, _for_it_52, _for_it_53, ntnd, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_2_2_85_2_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_map_2_2_85_2_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_map_2_2_85_2_29_args[] = { (void *)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (void *)&gpu___CG_p_int__m_c_lin_e, (void *)&gpu___CG_p_int__m_geofac_grdiv, (void *)&gpu___CG_p_metrics__m_ddqz_z_full_e, (void *)&gpu___CG_p_patch__CG_edges__m_area_edge, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx, (void *)&gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, (void *)&gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, (void *)&gpu___CG_p_patch__CG_edges__m_quad_idx, (void *)&gpu___CG_p_patch__CG_edges__m_tangent_orientation, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_levelmask, (void *)&gpu_z_w_con_c_full, (void *)&gpu_zeta, (void *)&__f2dace_SA_area_edge_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SA_geofac_grdiv_d_0_s_p_int_6, (void *)&__f2dace_SA_geofac_grdiv_d_1_s_p_int_6, (void *)&__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_c_lin_e_d_0_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_1_s_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_2_s_p_int_6, (void *)&__f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, (void *)&__f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, (void *)&__f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, (void *)&__f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, (void *)&__f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, (void *)&__f2dace_SOA_vn_d_0_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_p_prog_7, (void *)&_for_it_47, (void *)&cfl_w_limit, (void *)&dtime, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nrdmax_jg, (void *)&ntnd, (void *)&scalfac_exdiff, (void *)&tmp_struct_symbol_2, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_2_2_85_2_29, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1), 1), dim3(256, 1, 1), single_state_body_map_2_2_85_2_29_args, 0, nullptr);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_2_2_85_2_29", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((87 - Max(3, (nrdmax_jg - 2))), 1), 1), 1, 256, 1, 1);
}

