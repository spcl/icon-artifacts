#include "reductions_kernel.cuh"
#include "reductions_cpu.h"
#include "timer.h"
/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t {

};

static int tmp_struct_symbol_0;
static int tmp_struct_symbol_1;
static int tmp_struct_symbol_2;
static int tmp_struct_symbol_3;
static int tmp_struct_symbol_4;
static int tmp_struct_symbol_5;
static int tmp_struct_symbol_6;
static int tmp_struct_symbol_7;
static int tmp_struct_symbol_8;
static int tmp_struct_symbol_9;
static int tmp_struct_symbol_10;
static int tmp_struct_symbol_11;
static int tmp_struct_symbol_12;
static int tmp_struct_symbol_13;
static int tmp_struct_symbol_14;
static int __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2;
static int __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_2_s_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_1_s_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_2_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_0_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_1_s_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_2_s_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2;
static int __f2dace_SOA_area_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_area_d_1_s_cells_p_patch_2;
static int __f2dace_SA_area_d_0_s_cells_p_patch_2;
static int __f2dace_SA_area_d_1_s_cells_p_patch_2;
static int __f2dace_SOA_start_index_d_0_s_cells_p_patch_2;
static int __f2dace_SA_start_index_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_end_index_d_0_s_cells_p_patch_2;
static int __f2dace_SA_end_index_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_start_block_d_0_s_cells_p_patch_2;
static int __f2dace_SA_start_block_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_end_block_d_0_s_cells_p_patch_2;
static int __f2dace_SA_end_block_d_0_s_cells_p_patch_2;
static int __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3;
static int __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3;
static int __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3;
static int __f2dace_SA_owner_mask_d_1_s_decomp_info_cells_p_patch_3;
static int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4;
static int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4;
static int __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4;
static int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4;
static int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4;
static int __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4;
static int __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4;
static int __f2dace_SA_inv_dual_edge_length_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4;
static int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4;
static int __f2dace_SA_area_edge_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4;
static int __f2dace_SA_f_e_d_0_s_edges_p_patch_4;
static int __f2dace_SA_f_e_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_fn_e_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_fn_e_d_1_s_edges_p_patch_4;
static int __f2dace_SA_fn_e_d_0_s_edges_p_patch_4;
static int __f2dace_SA_fn_e_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_ft_e_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_ft_e_d_1_s_edges_p_patch_4;
static int __f2dace_SA_ft_e_d_0_s_edges_p_patch_4;
static int __f2dace_SA_ft_e_d_1_s_edges_p_patch_4;
static int __f2dace_SOA_start_index_d_0_s_edges_p_patch_4;
static int __f2dace_SA_start_index_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_end_index_d_0_s_edges_p_patch_4;
static int __f2dace_SA_end_index_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_start_block_d_0_s_edges_p_patch_4;
static int __f2dace_SA_start_block_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_end_block_d_0_s_edges_p_patch_4;
static int __f2dace_SA_end_block_d_0_s_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5;
static int __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_2_s_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_1_s_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_2_s_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_0_s_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_1_s_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_2_s_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5;
static int __f2dace_SOA_start_index_d_0_s_verts_p_patch_5;
static int __f2dace_SA_start_index_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_end_index_d_0_s_verts_p_patch_5;
static int __f2dace_SA_end_index_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_start_block_d_0_s_verts_p_patch_5;
static int __f2dace_SA_start_block_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_end_block_d_0_s_verts_p_patch_5;
static int __f2dace_SA_end_block_d_0_s_verts_p_patch_5;
static int __f2dace_SOA_c_lin_e_d_0_s_p_int_6;
static int __f2dace_SOA_c_lin_e_d_1_s_p_int_6;
static int __f2dace_SOA_c_lin_e_d_2_s_p_int_6;
static int __f2dace_SA_c_lin_e_d_0_s_p_int_6;
static int __f2dace_SA_c_lin_e_d_1_s_p_int_6;
static int __f2dace_SA_c_lin_e_d_2_s_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_2_s_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_0_s_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_1_s_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_2_s_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_2_s_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_2_s_p_int_6;
static int __f2dace_SOA_geofac_rot_d_0_s_p_int_6;
static int __f2dace_SOA_geofac_rot_d_1_s_p_int_6;
static int __f2dace_SOA_geofac_rot_d_2_s_p_int_6;
static int __f2dace_SA_geofac_rot_d_0_s_p_int_6;
static int __f2dace_SA_geofac_rot_d_1_s_p_int_6;
static int __f2dace_SA_geofac_rot_d_2_s_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_0_s_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_1_s_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_2_s_p_int_6;
static int __f2dace_SA_geofac_n2s_d_0_s_p_int_6;
static int __f2dace_SA_geofac_n2s_d_1_s_p_int_6;
static int __f2dace_SA_geofac_n2s_d_2_s_p_int_6;
static int __f2dace_SOA_w_d_0_s_p_prog_7;
static int __f2dace_SOA_w_d_1_s_p_prog_7;
static int __f2dace_SOA_w_d_2_s_p_prog_7;
static int __f2dace_SA_w_d_0_s_p_prog_7;
static int __f2dace_SA_w_d_2_s_p_prog_7;
static int __f2dace_SOA_vn_d_0_s_p_prog_7;
static int __f2dace_SOA_vn_d_1_s_p_prog_7;
static int __f2dace_SOA_vn_d_2_s_p_prog_7;
static int __f2dace_SA_vn_d_0_s_p_prog_7;
static int __f2dace_SA_vn_d_2_s_p_prog_7;
static int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8;
static int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8;
static int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8;
static int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8;
static int __f2dace_SA_ddxn_z_full_d_2_s_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8;
static int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8;
static int __f2dace_SA_ddxt_z_full_d_2_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8;
static int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8;
static int __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8;
static int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8;
static int __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8;
static int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8;
static int __f2dace_SA_wgtfac_c_d_2_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8;
static int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8;
static int __f2dace_SA_wgtfac_e_d_2_s_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_2_s_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8;
static int __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8;
static int __f2dace_SA_coeff1_dwdz_d_2_s_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8;
static int __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8;
static int __f2dace_SA_coeff2_dwdz_d_2_s_p_metrics_8;
static int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_p_metrics_8;
static int __f2dace_SOA_deepatmo_invr_mc_d_0_s_p_metrics_8;
static int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_p_metrics_8;
static int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_p_metrics_8;
static int __f2dace_SOA_vt_d_0_s_p_diag_9;
static int __f2dace_SOA_vt_d_1_s_p_diag_9;
static int __f2dace_SOA_vt_d_2_s_p_diag_9;
static int __f2dace_SA_vt_d_0_s_p_diag_9;
static int __f2dace_SA_vt_d_2_s_p_diag_9;
static int __f2dace_SOA_vn_ie_d_0_s_p_diag_9;
static int __f2dace_SOA_vn_ie_d_1_s_p_diag_9;
static int __f2dace_SOA_vn_ie_d_2_s_p_diag_9;
static int __f2dace_SA_vn_ie_d_0_s_p_diag_9;
static int __f2dace_SA_vn_ie_d_2_s_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9;
static int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9;
static int __f2dace_SA_w_concorr_c_d_2_s_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_3_s_p_diag_9;
inline void loop_body_1_2_5(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_int__m_geofac_rot, int* __restrict__ __CG_p_patch__CG_verts__m_edge_blk, int* __restrict__ __CG_p_patch__CG_verts__m_edge_idx, double* __restrict__ __CG_p_prog__m_vn, double* __restrict__ zeta, int _for_it_3_0, int _for_it_4_0, int _for_it_5_0, int tmp_struct_symbol_8) {
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



    tmp_index_92_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_94_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_104_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_106_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_116_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_118_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_128_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_130_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_140_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_142_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
    tmp_index_152_0 = (__CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
    tmp_index_154_0 = (__CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_p_prog_7);

    {

        {
            double ptr_int_0_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_1_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_2_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_3_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_4_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double ptr_int_5_in_geofac_rot_0 = __CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (6 - __f2dace_SOA_geofac_rot_d_1_s_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_p_int_6) + _for_it_5_0)];
            double vec_e_0_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
            double vec_e_1_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
            double vec_e_2_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
            double vec_e_3_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
            double vec_e_4_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
            double vec_e_5_in_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
            double rot_vec_out_0;

            ///////////////////
            // Tasklet code (T_l296_c296)
            rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
            ///////////////////

            zeta[(((_for_it_5_0 + ((90 * tmp_struct_symbol_8) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_8 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
        }

    }

}

inline void loop_body_0_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, const int&  __CG_global_data__m_nproma, double* __restrict__ __CG_p_int__m_geofac_rot, int* __restrict__ __CG_p_patch__CG_verts__m_edge_blk, int* __restrict__ __CG_p_patch__CG_verts__m_edge_idx, int* __restrict__ __CG_p_patch__CG_verts__m_end_index, int* __restrict__ __CG_p_patch__CG_verts__m_start_index, double* __restrict__ __CG_p_prog__m_vn, double* __restrict__ zeta, int _for_it_3_0, int i_endblk_var_119_0, int i_startblk_var_118_0, int tmp_struct_symbol_8) {
    int i_startidx_in_var_103_0_0;
    int i_endidx_in_var_104_0_0;
    int i_startidx_var_120_0;
    int i_endidx_var_121_0;



    i_startidx_in_var_103_0_0 = __CG_p_patch__CG_verts__m_start_index[(2 - __f2dace_SOA_start_index_d_0_s_verts_p_patch_5)];
    i_endidx_in_var_104_0_0 = __CG_p_patch__CG_verts__m_end_index[((- __f2dace_SOA_end_index_d_0_s_verts_p_patch_5) - 5)];

    if (((_for_it_3_0 == i_startblk_var_118_0) == 1)) {

        i_startidx_var_120_0 = i_startidx_in_var_103_0_0;
        i_endidx_var_121_0 = __CG_global_data__m_nproma;
        if (((_for_it_3_0 == i_endblk_var_119_0) == 1)) {

            i_endidx_var_121_0 = i_endidx_in_var_104_0_0;

        }
    } else if (((! ((_for_it_3_0 == i_startblk_var_118_0) == 1)) && ((_for_it_3_0 == i_endblk_var_119_0) == 1))) {

        i_startidx_var_120_0 = 1;
        i_endidx_var_121_0 = i_endidx_in_var_104_0_0;

    } else {

        i_startidx_var_120_0 = 1;
        i_endidx_var_121_0 = __CG_global_data__m_nproma;

    }

    {

        {
            for (auto _for_it_4_0 = 1; _for_it_4_0 < 91; _for_it_4_0 += 1) {
                for (auto _for_it_5_0 = i_startidx_var_120_0; _for_it_5_0 < (i_endidx_var_121_0 + 1); _for_it_5_0 += 1) {
                    loop_body_1_2_5(__state, &__CG_p_int__m_geofac_rot[0], &__CG_p_patch__CG_verts__m_edge_blk[0], &__CG_p_patch__CG_verts__m_edge_idx[0], &__CG_p_prog__m_vn[0], &zeta[0], _for_it_3_0, _for_it_4_0, _for_it_5_0, tmp_struct_symbol_8);
                }
            }
        }

    }

}

inline void loop_body_9_4_5(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_int__m_e_bln_c_s, int* __restrict__ __CG_p_patch__CG_cells__m_edge_blk, int* __restrict__ __CG_p_patch__CG_cells__m_edge_idx, double* __restrict__ z_kin_hor_e, double* __restrict__ z_ekinh, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_22, int _for_it_23, int _for_it_24, int tmp_struct_symbol_10) {
    int tmp_index_407;
    int tmp_index_409;
    int tmp_index_419;
    int tmp_index_421;
    int tmp_index_431;
    int tmp_index_433;



    tmp_index_407 = (__CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_409 = (__CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_419 = (__CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_421 = (__CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);
    tmp_index_431 = (__CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s);
    tmp_index_433 = (__CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s);

    {

        {
            double p_int_0_in_e_bln_c_s = __CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_1_in_e_bln_c_s = __CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double p_int_2_in_e_bln_c_s = __CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6) + _for_it_24)];
            double z_kin_hor_e_0_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_409) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_407)];
            double z_kin_hor_e_1_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_421) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_419)];
            double z_kin_hor_e_2_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * tmp_index_433) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_23))) + tmp_index_431)];
            double z_ekinh_out_0;

            ///////////////////
            // Tasklet code (T_l515_c515)
            z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s * z_kin_hor_e_2_in_0));
            ///////////////////

            z_ekinh[(((_for_it_24 + ((90 * tmp_struct_symbol_10) * (_for_it_22 - 1))) + (tmp_struct_symbol_10 * (_for_it_23 - 1))) - 1)] = z_ekinh_out_0;
        }

    }

}

inline void loop_body_12_0_4(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_metrics__m_ddqz_z_half, int* __restrict__ cfl_clipping, const double&  dtime, double* __restrict__ maxvcfl_arr, double* __restrict__ z_w_con_c, int _for_it_22, int _for_it_35, int _for_it_37, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4) {
    int _if_cond_18;
    double vcfl;



    _if_cond_18 = cfl_clipping[((_for_it_37 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];

    if ((_if_cond_18 == 1)) {

        vcfl = ((z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] * dtime) / __CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)]);
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

                maxvcfl_arr[((_for_it_37 + (tmp_struct_symbol_4 * (_for_it_35 - 1))) - 1)] = maxvcfl_out;
            }

        }
        if (((vcfl < -0.85) == 1)) {
            {

                {
                    double dtime_0_in = dtime;
                    double p_metrics_0_in_ddqz_z_half_0 = __CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)];
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l560_c560)
                    z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                    ///////////////////

                    z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] = z_w_con_c_out_0;
                }

            }
        } else if (((! ((vcfl < -0.85) == 1)) && ((vcfl > 0.85) == 1))) {
            {

                {
                    double dtime_0_in = dtime;
                    double p_metrics_0_in_ddqz_z_half_0 = __CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_37)];
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l562_c562)
                    z_w_con_c_out_0 = ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in);
                    ///////////////////

                    z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] = z_w_con_c_out_0;
                }

            }
        }
    }

}

inline void loop_body_9_1_2(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_metrics__m_ddqz_z_half, const double&  cfl_w_limit, const double&  dtime, int* __restrict__ cfl_clipping, int* __restrict__ levmask, double* __restrict__ maxvcfl_arr, double* __restrict__ z_w_con_c, int _for_it_22, int _for_it_35, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_13, int tmp_struct_symbol_14, int tmp_struct_symbol_4) {
    int out_val_0[1]  DACE_ALIGN(64);


    {
        int reduce_sum_to_address_size;

        {
            for (auto _for_it_36 = i_startidx_var_148; _for_it_36 < (i_endidx_var_149 + 1); _for_it_36 += 1) {
                double loop_body_tmp_call_7;
                {
                    double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_36 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)];
                    double tmp_call_7_out;

                    ///////////////////
                    // Tasklet code (T_l550_c550)
                    tmp_call_7_out = abs(z_w_con_c_0_in_0);
                    ///////////////////

                    loop_body_tmp_call_7 = tmp_call_7_out;
                }
                {
                    double tmp_call_7_0_in = loop_body_tmp_call_7;
                    double p_metrics_0_in_ddqz_z_half_0 = __CG_p_metrics__m_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8) + _for_it_36)];
                    double cfl_w_limit_0_in = cfl_w_limit;
                    int cfl_clipping_out_0;

                    ///////////////////
                    // Tasklet code (T_l550_c550)
                    cfl_clipping_out_0 = (tmp_call_7_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                    ///////////////////

                    cfl_clipping[((_for_it_36 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)] = cfl_clipping_out_0;
                }
            }
        }
        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_sum_to_address)
            size = ((i_endidx_var_149 + 1) - i_startidx_var_148);
            ///////////////////

            reduce_sum_to_address_size = size;
        }
        {
            int* in_arr = &cfl_clipping[((i_startidx_var_148 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];
            int in_size = reduce_sum_to_address_size;
            int* out = out_val_0;

            ///////////////////

            #ifdef __REDUCE_DEVICE__
            reduce_sum_to_address_device(in_arr, out, in_size);
            #elif defined(__REDUCE_GPU__)
            reduce_sum_to_address_gpu(in_arr, out, in_size, __dace_current_stream);
            #else
            reduce_sum_to_address_cpu(in_arr, out, in_size);
            #endif

            ///////////////////

        }

    }

    if ((! ((out_val_0[0] == 0) == 1))) {
        {
            int reduce_scan_size_0;

            {
                for (auto _for_it_37 = i_startidx_var_148; _for_it_37 < (i_endidx_var_149 + 1); _for_it_37 += 1) {
                    loop_body_12_0_4(__state, &__CG_p_metrics__m_ddqz_z_half[0], &cfl_clipping[0], dtime, &maxvcfl_arr[0], &z_w_con_c[0], _for_it_22, _for_it_35, _for_it_37, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
                }
            }
            {
                int size;

                ///////////////////
                // Tasklet code (size_reduce_scan)
                size = 1;
                ///////////////////

                reduce_scan_size_0 = size;
            }
            {
                int in_arr = cfl_clipping[((_for_it_22 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];
                int in_size = reduce_scan_size_0;
                int out;

                ///////////////////

                #ifdef __REDUCE_DEVICE__
                out = reduce_scan_device(in_arr, in_size);
                #elif defined(__REDUCE_GPU__)
                out = reduce_scan_gpu(in_arr, in_size, __dace_current_stream);
                #else
                out = reduce_scan_cpu(in_arr, in_size);
                #endif

                ///////////////////

                levmask[((_for_it_22 + (tmp_struct_symbol_13 * (_for_it_35 - 1))) - 1)] = out;
            }

        }
    }

}

inline void loop_body_0_4_0(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, const int&  __CG_global_data__m_nproma, double* __restrict__ __CG_p_diag__m_w_concorr_c, double* __restrict__ __CG_p_int__m_e_bln_c_s, double* __restrict__ __CG_p_metrics__m_ddqz_z_half, int* __restrict__ __CG_p_patch__CG_cells__m_edge_blk, int* __restrict__ __CG_p_patch__CG_cells__m_edge_idx, int* __restrict__ __CG_p_patch__CG_cells__m_end_index, int* __restrict__ __CG_p_patch__CG_cells__m_start_index, double* __restrict__ __CG_p_prog__m_w, const double&  cfl_w_limit, const double&  dtime, double* __restrict__ z_kin_hor_e, int* __restrict__ cfl_clipping, int* __restrict__ levmask, double* __restrict__ vcflmax, double* __restrict__ z_ekinh, double* __restrict__ z_w_con_c_full, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_22, int i_endblk_var_147, int i_startblk_var_146, int nflatlev_jg, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_13, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_4) {
    double *z_w_con_c;
    z_w_con_c = new double DACE_ALIGN(64)[(91 * tmp_struct_symbol_1)];
    double maxvcfl;
    double *maxvcfl_arr;
    maxvcfl_arr = new double DACE_ALIGN(64)[(88 * tmp_struct_symbol_4)];
    int i_startidx_in_var_79_1;
    int i_endidx_in_var_80_1;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_79_1 = __CG_p_patch__CG_cells__m_start_index[(4 - __f2dace_SOA_start_index_d_0_s_cells_p_patch_2)];
    i_endidx_in_var_80_1 = __CG_p_patch__CG_cells__m_end_index[((- __f2dace_SOA_end_index_d_0_s_cells_p_patch_2) - 5)];

    if (((_for_it_22 == i_startblk_var_146) == 1)) {

        i_startidx_var_148 = max(1, i_startidx_in_var_79_1);
        i_endidx_var_149 = __CG_global_data__m_nproma;
        if (((_for_it_22 == i_endblk_var_147) == 1)) {

            i_endidx_var_149 = i_endidx_in_var_80_1;

        }
    } else if (((! ((_for_it_22 == i_startblk_var_146) == 1)) && ((_for_it_22 == i_endblk_var_147) == 1))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_80_1;

    } else {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    }

    {

        {
            for (auto _for_it_23 = 1; _for_it_23 < 91; _for_it_23 += 1) {
                for (auto _for_it_24 = i_startidx_var_148; _for_it_24 < (i_endidx_var_149 + 1); _for_it_24 += 1) {
                    loop_body_9_4_5(__state, &__CG_p_int__m_e_bln_c_s[0], &__CG_p_patch__CG_cells__m_edge_blk[0], &__CG_p_patch__CG_cells__m_edge_idx[0], &z_kin_hor_e[0], &z_ekinh[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_22, _for_it_23, _for_it_24, tmp_struct_symbol_10);
                }
            }
        }
        {
            for (auto _for_it_29 = 1; _for_it_29 < 91; _for_it_29 += 1) {
                for (auto _for_it_30 = i_startidx_var_148; _for_it_30 < (i_endidx_var_149 + 1); _for_it_30 += 1) {
                    {
                        double p_prog_0_in_w_0 = __CG_p_prog__m_w[((((__f2dace_SA_w_d_0_s_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_p_prog_7) + _for_it_29)) + ((91 * __f2dace_SA_w_d_0_s_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_p_prog_7) + _for_it_30)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l532_c532)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        z_w_con_c[((_for_it_30 + (tmp_struct_symbol_1 * (_for_it_29 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }

    }

    {

        {
            for (auto _for_it_34 = Max(3, (nrdmax_jg - 2)); _for_it_34 < 88; _for_it_34 += 1) {
                {
                    int levmask_out_0;

                    ///////////////////
                    // Tasklet code (T_l544_c544)
                    levmask_out_0 = 0;
                    ///////////////////

                    levmask[((_for_it_22 + (tmp_struct_symbol_13 * (_for_it_34 - 1))) - 1)] = levmask_out_0;
                }
            }
        }
        {
            for (auto _for_it_31 = i_startidx_var_148; _for_it_31 < (i_endidx_var_149 + 1); _for_it_31 += 1) {
                {
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l536_c536)
                    z_w_con_c_out_0 = 0.0;
                    ///////////////////

                    z_w_con_c[((_for_it_31 + (90 * tmp_struct_symbol_1)) - 1)] = z_w_con_c_out_0;
                }
            }
        }
        {
            for (auto _for_it_32 = (nflatlev_jg + 1); _for_it_32 < 91; _for_it_32 += 1) {
                for (auto _for_it_33 = i_startidx_var_148; _for_it_33 < (i_endidx_var_149 + 1); _for_it_33 += 1) {
                    {
                        double p_diag_0_in_w_concorr_c_0 = __CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9) + _for_it_32)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9) + _for_it_33)];
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l540_c540)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)] = z_w_con_c_out_0;
                    }
                }
            }
        }

    }

    {

        {
            double maxvcfl_out;

            ///////////////////
            // Tasklet code (T_l546_c546)
            maxvcfl_out = 0;
            ///////////////////

            maxvcfl = maxvcfl_out;
        }
        {
            for (auto _for_it_35 = Max(3, (nrdmax_jg - 2)); _for_it_35 < 88; _for_it_35 += 1) {
                loop_body_9_1_2(__state, &__CG_p_metrics__m_ddqz_z_half[0], cfl_w_limit, dtime, &cfl_clipping[0], &levmask[0], &maxvcfl_arr[0], &z_w_con_c[0], _for_it_22, _for_it_35, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_13, tmp_struct_symbol_14, tmp_struct_symbol_4);
            }
        }

    }

    {
        int reduce_maxZ_to_scalar_size_0;

        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_maxZ_to_scalar)
            size = (((i_endidx_var_149 + 1) - i_startidx_var_148) * 87);
            ///////////////////

            reduce_maxZ_to_scalar_size_0 = size;
        }
        {
            double* in_arr = &maxvcfl_arr[(i_startidx_var_148 - 1)];
            int in_size = reduce_maxZ_to_scalar_size_0;
            double out;

            ///////////////////

            #ifdef __REDUCE_DEVICE__
            out = reduce_maxZ_to_scalar_device(in_arr, in_size);
            #elif defined(__REDUCE_GPU__)
            out = reduce_maxZ_to_scalar_gpu(in_arr, in_size, __dace_current_stream);
            #else
            out = reduce_maxZ_to_scalar_cpu(in_arr, in_size);
            #endif

            ///////////////////

            maxvcfl = out;
        }
        {
            double maxvcfl_0_in = maxvcfl;
            double vcflmax_out_0;

            ///////////////////
            // Tasklet code (T_l572_c572)
            vcflmax_out_0 = maxvcfl_0_in;
            ///////////////////

            vcflmax[(_for_it_22 - 1)] = vcflmax_out_0;
        }
        {
            for (auto _for_it_38 = 1; _for_it_38 < 91; _for_it_38 += 1) {
                for (auto _for_it_39 = i_startidx_var_148; _for_it_39 < (i_endidx_var_149 + 1); _for_it_39 += 1) {
                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_39 + (tmp_struct_symbol_1 * (_for_it_38 - 1))) - 1)];
                        double z_w_con_c_1_in_0 = z_w_con_c[(((_for_it_38 * tmp_struct_symbol_1) + _for_it_39) - 1)];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l569_c569)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        z_w_con_c_full[(((_for_it_39 + ((90 * tmp_struct_symbol_2) * (_for_it_22 - 1))) + (tmp_struct_symbol_2 * (_for_it_38 - 1))) - 1)] = z_w_con_c_full_out_0;
                    }
                }
            }
        }

    }

    delete[] z_w_con_c;
    delete[] maxvcfl_arr;
}

inline void loop_body_26_2_6(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_diag__m_vn_ie, double* __restrict__ __CG_p_diag__m_vt, double* __restrict__ __CG_p_int__m_c_lin_e, double* __restrict__ __CG_p_metrics__m_coeff_gradekin, double* __restrict__ __CG_p_metrics__m_ddqz_z_full_e, int* __restrict__ __CG_p_patch__CG_edges__m_cell_blk, int* __restrict__ __CG_p_patch__CG_edges__m_cell_idx, double* __restrict__ __CG_p_patch__CG_edges__m_f_e, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_blk, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ z_ekinh, double* __restrict__ z_kin_hor_e, double* __restrict__ z_w_con_c_full, double* __restrict__ zeta, double* __restrict__ __CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_47, int _for_it_48, int _for_it_49, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
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



    tmp_index_698 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_700 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_710 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_712 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_724 = (__CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_726 = (__CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_733 = (__CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_735 = (__CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_745 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_747 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_757 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_759 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_49)] - 1);

    {

        {
            double p_diag_0_in_vt_0 = __CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_p_diag_9) + _for_it_48)) + ((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vt_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_1_in_vn_ie_0 = __CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48)) + ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_diag_2_in_vn_ie_0 = __CG_p_diag__m_vn_ie[(((((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_p_diag_9) + _for_it_47)) + (__f2dace_SA_vn_ie_d_0_s_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_p_diag_9) + _for_it_48) + 1))) - __f2dace_SOA_vn_ie_d_0_s_p_diag_9) + _for_it_49)];
            double p_int_0_in_c_lin_e_0 = __CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_int_1_in_c_lin_e_0 = __CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_49)];
            double p_metrics_0_in_coeff_gradekin_0 = __CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_1_in_coeff_gradekin_0 = __CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_2_in_coeff_gradekin_0 = __CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_3_in_coeff_gradekin_0 = __CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8) + _for_it_49)];
            double p_metrics_4_in_ddqz_z_full_e_0 = __CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_48)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_49)];
            double p_patch_0_in_edges_f_e_0 = __CG_p_patch__CG_edges__m_f_e[(((__f2dace_SA_f_e_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_f_e_d_0_s_edges_p_patch_4) + _for_it_49)];
            double z_ekinh_0_in_0 = z_ekinh[((tmp_index_698 + ((90 * tmp_index_700) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_ekinh_1_in_0 = z_ekinh[((tmp_index_710 + ((90 * tmp_index_712) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s * __f2dace_A_z_kin_hor_e_d_1_s) * ((- __f2dace_OA_z_kin_hor_e_d_2_s) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s * ((- __f2dace_OA_z_kin_hor_e_d_1_s) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s) + _for_it_49)];
            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_745 + ((90 * tmp_index_747) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_757 + ((90 * tmp_index_759) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double zeta_0_in_0 = zeta[((tmp_index_724 + ((90 * tmp_index_726) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double zeta_1_in_0 = zeta[((tmp_index_733 + ((90 * tmp_index_735) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double p_diag_out_ddt_vn_apc_pc_0;

            ///////////////////
            // Tasklet code (T_l611_c611)
            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
            ///////////////////

            __CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_48))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_49)] = p_diag_out_ddt_vn_apc_pc_0;
        }

    }

}

inline void loop_body_35_0_0(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_int__m_c_lin_e, double* __restrict__ __CG_p_int__m_geofac_grdiv, double* __restrict__ __CG_p_metrics__m_ddqz_z_full_e, double* __restrict__ __CG_p_patch__CG_edges__m_area_edge, int* __restrict__ __CG_p_patch__CG_edges__m_cell_blk, int* __restrict__ __CG_p_patch__CG_edges__m_cell_idx, double* __restrict__ __CG_p_patch__CG_edges__m_inv_primal_edge_length, int* __restrict__ __CG_p_patch__CG_edges__m_quad_blk, int* __restrict__ __CG_p_patch__CG_edges__m_quad_idx, double* __restrict__ __CG_p_patch__CG_edges__m_tangent_orientation, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_blk, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ __CG_p_prog__m_vn, const double&  cfl_w_limit, const double&  dtime, const double&  scalfac_exdiff, double* __restrict__ z_w_con_c_full, double* __restrict__ zeta, double* __restrict__ __CG_p_diag__m_ddt_vn_apc_pc, int _for_it_47, int _for_it_52, int _for_it_53, int ntnd, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    double _if_cond_29;
    double w_con_e;
    double tmp_call_17;
    int tmp_index_881;
    int tmp_index_883;
    int tmp_index_893;
    int tmp_index_895;
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



    tmp_index_881 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_883 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_893 = (__CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
    tmp_index_895 = (__CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);

    {
        double tmp_call_15;

        {
            double p_int_0_in_c_lin_e_0 = __CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double p_int_1_in_c_lin_e_0 = __CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_p_int_6) + _for_it_53)];
            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_881 + ((90 * tmp_index_883) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_893 + ((90 * tmp_index_895) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_52 - 1)))];
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
            double p_metrics_0_in_ddqz_z_full_e_0 = __CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
            double tmp_call_15_0_in = tmp_call_15;
            double _if_cond_29_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_29_out = (tmp_call_15_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
            ///////////////////

            _if_cond_29 = _if_cond_29_out;
        }

    }

    if ((_if_cond_29 == 1)) {
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
        tmp_index_927 = (__CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_929 = (__CG_p_patch__CG_edges__m_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_939 = (__CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_941 = (__CG_p_patch__CG_edges__m_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_951 = (__CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_953 = (__CG_p_patch__CG_edges__m_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_963 = (__CG_p_patch__CG_edges__m_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_p_prog_7);
        tmp_index_965 = (__CG_p_patch__CG_edges__m_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_p_prog_7);
        tmp_index_976 = (__CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_978 = (__CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_985 = (__CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        tmp_index_987 = (__CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4) + _for_it_53)] - 1);
        {
            double tmp_arg_19;
            double difcoef;
            double tmp_arg_18;
            double tmp_call_16;

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
                double p_metrics_0_in_ddqz_z_full_e_0 = __CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8) + _for_it_53)];
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
                double p_diag_0_in_ddt_vn_apc_pc_0 = __CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)];
                double p_int_0_in_geofac_grdiv_0 = __CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (1 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_1_in_geofac_grdiv_0 = __CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (2 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_2_in_geofac_grdiv_0 = __CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (3 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_3_in_geofac_grdiv_0 = __CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (4 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_int_4_in_geofac_grdiv_0 = __CG_p_int__m_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (5 - __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6) + _for_it_53)];
                double p_patch_0_in_edges_area_edge_0 = __CG_p_patch__CG_edges__m_area_edge[(((__f2dace_SA_area_edge_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_1_in_edges_tangent_orientation_0 = __CG_p_patch__CG_edges__m_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_patch_2_in_edges_inv_primal_edge_length_0 = __CG_p_patch__CG_edges__m_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4) + _for_it_53)];
                double p_prog_0_in_vn_0 = __CG_p_prog__m_vn[((((__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52)) + ((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_p_prog_7) + _for_it_47))) - __f2dace_SOA_vn_d_0_s_p_prog_7) + _for_it_53)];
                double p_prog_1_in_vn_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_929) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_927)];
                double p_prog_2_in_vn_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_941) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_939)];
                double p_prog_3_in_vn_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_953) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_951)];
                double p_prog_4_in_vn_0 = __CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * tmp_index_965) + (__f2dace_SA_vn_d_0_s_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_p_prog_7) + _for_it_52))) + tmp_index_963)];
                double zeta_0_in_0 = zeta[((tmp_index_976 + ((90 * tmp_index_978) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double zeta_1_in_0 = zeta[((tmp_index_985 + ((90 * tmp_index_987) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                double p_diag_out_ddt_vn_apc_pc_0;

                ///////////////////
                // Tasklet code (T_l643_c643)
                p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                ///////////////////

                __CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9) + _for_it_53)] = p_diag_out_ddt_vn_apc_pc_0;
            }

        }
    }

}

inline void loop_body_26_2_31(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, double* __restrict__ __CG_p_int__m_c_lin_e, double* __restrict__ __CG_p_int__m_geofac_grdiv, double* __restrict__ __CG_p_metrics__m_ddqz_z_full_e, double* __restrict__ __CG_p_patch__CG_edges__m_area_edge, int* __restrict__ __CG_p_patch__CG_edges__m_cell_blk, int* __restrict__ __CG_p_patch__CG_edges__m_cell_idx, double* __restrict__ __CG_p_patch__CG_edges__m_inv_primal_edge_length, int* __restrict__ __CG_p_patch__CG_edges__m_quad_blk, int* __restrict__ __CG_p_patch__CG_edges__m_quad_idx, double* __restrict__ __CG_p_patch__CG_edges__m_tangent_orientation, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_blk, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ __CG_p_prog__m_vn, const double&  cfl_w_limit, const double&  dtime, int* __restrict__ levelmask, const double&  scalfac_exdiff, double* __restrict__ z_w_con_c_full, double* __restrict__ zeta, double* __restrict__ __CG_p_diag__m_ddt_vn_apc_pc, int _for_it_47, int _for_it_52, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    bool _if_cond_28;



    _if_cond_28 = (levelmask[(_for_it_52 - 1)] || levelmask[_for_it_52]);

    if ((_if_cond_28 == 1)) {
        {

            {
                for (auto _for_it_53 = i_startidx_var_148; _for_it_53 < (i_endidx_var_149 + 1); _for_it_53 += 1) {
                    loop_body_35_0_0(__state, &__CG_p_int__m_c_lin_e[0], &__CG_p_int__m_geofac_grdiv[0], &__CG_p_metrics__m_ddqz_z_full_e[0], &__CG_p_patch__CG_edges__m_area_edge[0], &__CG_p_patch__CG_edges__m_cell_blk[0], &__CG_p_patch__CG_edges__m_cell_idx[0], &__CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &__CG_p_patch__CG_edges__m_quad_blk[0], &__CG_p_patch__CG_edges__m_quad_idx[0], &__CG_p_patch__CG_edges__m_tangent_orientation[0], &__CG_p_patch__CG_edges__m_vertex_blk[0], &__CG_p_patch__CG_edges__m_vertex_idx[0], &__CG_p_prog__m_vn[0], cfl_w_limit, dtime, scalfac_exdiff, &z_w_con_c_full[0], &zeta[0], &__CG_p_diag__m_ddt_vn_apc_pc[0], _for_it_47, _for_it_52, _for_it_53, ntnd, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }

        }
    }

}

inline void loop_body_0_5_0(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, const int&  __CG_global_data__m_nproma, double* __restrict__ __CG_p_diag__m_vn_ie, double* __restrict__ __CG_p_diag__m_vt, double* __restrict__ __CG_p_int__m_c_lin_e, double* __restrict__ __CG_p_int__m_geofac_grdiv, double* __restrict__ __CG_p_metrics__m_coeff_gradekin, double* __restrict__ __CG_p_metrics__m_ddqz_z_full_e, double* __restrict__ __CG_p_patch__CG_edges__m_area_edge, int* __restrict__ __CG_p_patch__CG_edges__m_cell_blk, int* __restrict__ __CG_p_patch__CG_edges__m_cell_idx, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, double* __restrict__ __CG_p_patch__CG_edges__m_f_e, double* __restrict__ __CG_p_patch__CG_edges__m_inv_primal_edge_length, int* __restrict__ __CG_p_patch__CG_edges__m_quad_blk, int* __restrict__ __CG_p_patch__CG_edges__m_quad_idx, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, double* __restrict__ __CG_p_patch__CG_edges__m_tangent_orientation, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_blk, int* __restrict__ __CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ __CG_p_prog__m_vn, const double&  cfl_w_limit, const double&  dtime, int* __restrict__ levelmask, const double&  scalfac_exdiff, double* __restrict__ z_ekinh, double* __restrict__ z_kin_hor_e, double* __restrict__ z_w_con_c_full, double* __restrict__ zeta, double* __restrict__ __CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_47, int i_endblk_var_147, int i_startblk_var_146, int nrdmax_jg, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int i_startidx_in_var_91_0;
    int i_endidx_in_var_92_0;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_0 = __CG_p_patch__CG_edges__m_start_index[(10 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_0 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 8)];

    if (((_for_it_47 != i_startblk_var_146) && (_for_it_47 != i_endblk_var_147))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_47 != i_startblk_var_146)) && (_for_it_47 != i_endblk_var_147))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_47 != i_startblk_var_146) && (! (_for_it_47 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_0;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = i_endidx_in_var_92_0;

    }

    {

        {
            for (auto _for_it_48 = 1; _for_it_48 < 91; _for_it_48 += 1) {
                for (auto _for_it_49 = i_startidx_var_148; _for_it_49 < (i_endidx_var_149 + 1); _for_it_49 += 1) {
                    loop_body_26_2_6(__state, &__CG_p_diag__m_vn_ie[0], &__CG_p_diag__m_vt[0], &__CG_p_int__m_c_lin_e[0], &__CG_p_metrics__m_coeff_gradekin[0], &__CG_p_metrics__m_ddqz_z_full_e[0], &__CG_p_patch__CG_edges__m_cell_blk[0], &__CG_p_patch__CG_edges__m_cell_idx[0], &__CG_p_patch__CG_edges__m_f_e[0], &__CG_p_patch__CG_edges__m_vertex_blk[0], &__CG_p_patch__CG_edges__m_vertex_idx[0], &z_ekinh[0], &z_kin_hor_e[0], &z_w_con_c_full[0], &zeta[0], &__CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_47, _for_it_48, _for_it_49, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
        {
            for (auto _for_it_52 = Max(3, (nrdmax_jg - 2)); _for_it_52 < 87; _for_it_52 += 1) {
                loop_body_26_2_31(__state, &__CG_p_int__m_c_lin_e[0], &__CG_p_int__m_geofac_grdiv[0], &__CG_p_metrics__m_ddqz_z_full_e[0], &__CG_p_patch__CG_edges__m_area_edge[0], &__CG_p_patch__CG_edges__m_cell_blk[0], &__CG_p_patch__CG_edges__m_cell_idx[0], &__CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &__CG_p_patch__CG_edges__m_quad_blk[0], &__CG_p_patch__CG_edges__m_quad_idx[0], &__CG_p_patch__CG_edges__m_tangent_orientation[0], &__CG_p_patch__CG_edges__m_vertex_blk[0], &__CG_p_patch__CG_edges__m_vertex_idx[0], &__CG_p_prog__m_vn[0], cfl_w_limit, dtime, &levelmask[0], scalfac_exdiff, &z_w_con_c_full[0], &zeta[0], &__CG_p_diag__m_ddt_vn_apc_pc[0], _for_it_47, _for_it_52, i_endidx_var_149, i_startidx_var_148, ntnd, tmp_struct_symbol_2, tmp_struct_symbol_8);
            }
        }

    }

}

void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2_internal(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double *z_w_con_c_full;
    z_w_con_c_full = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2))];
    double *zeta;
    zeta = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8))];
    double *z_ekinh;
    z_ekinh = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10))];
    double cfl_w_limit;
    double *vcflmax;
    vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_12];
    double scalfac_exdiff;
    int *levelmask;
    levelmask = new int DACE_ALIGN(64)[90];
    int *__CG_global_data__m_nflatlev;
    __CG_global_data__m_nflatlev = new int DACE_ALIGN(64)[10];
    int *__CG_global_data__m_nrdmax;
    __CG_global_data__m_nrdmax = new int DACE_ALIGN(64)[10];
    int *__CG_p_patch__CG_cells__m_edge_idx;
    __CG_p_patch__CG_cells__m_edge_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * (__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2 - 1))) + __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2)];
    int *__CG_p_patch__CG_cells__m_edge_blk;
    __CG_p_patch__CG_cells__m_edge_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * (__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2 - 1))) + __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2)];
    int *__CG_p_patch__CG_cells__m_start_index;
    __CG_p_patch__CG_cells__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_end_index;
    __CG_p_patch__CG_cells__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_start_block;
    __CG_p_patch__CG_cells__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_end_block;
    __CG_p_patch__CG_cells__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_cells_p_patch_2];
    int *__CG_p_patch__CG_edges__m_cell_idx;
    __CG_p_patch__CG_edges__m_cell_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_cell_blk;
    __CG_p_patch__CG_edges__m_cell_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4) * (__f2dace_SA_cell_blk_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * (__f2dace_SA_cell_blk_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_vertex_idx;
    __CG_p_patch__CG_edges__m_vertex_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_vertex_blk;
    __CG_p_patch__CG_edges__m_vertex_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4) * (__f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * (__f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_tangent_orientation;
    __CG_p_patch__CG_edges__m_tangent_orientation = new double DACE_ALIGN(64)[((__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4 * (__f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4 - 1)) + __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_quad_idx;
    __CG_p_patch__CG_edges__m_quad_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_quad_blk;
    __CG_p_patch__CG_edges__m_quad_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * (__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_inv_primal_edge_length;
    __CG_p_patch__CG_edges__m_inv_primal_edge_length = new double DACE_ALIGN(64)[((__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4 * (__f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4 - 1)) + __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_area_edge;
    __CG_p_patch__CG_edges__m_area_edge = new double DACE_ALIGN(64)[((__f2dace_SA_area_edge_d_0_s_edges_p_patch_4 * (__f2dace_SA_area_edge_d_1_s_edges_p_patch_4 - 1)) + __f2dace_SA_area_edge_d_0_s_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_f_e;
    __CG_p_patch__CG_edges__m_f_e = new double DACE_ALIGN(64)[((__f2dace_SA_f_e_d_0_s_edges_p_patch_4 * (__f2dace_SA_f_e_d_1_s_edges_p_patch_4 - 1)) + __f2dace_SA_f_e_d_0_s_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_start_index;
    __CG_p_patch__CG_edges__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_end_index;
    __CG_p_patch__CG_edges__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_start_block;
    __CG_p_patch__CG_edges__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_end_block;
    __CG_p_patch__CG_edges__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_edges_p_patch_4];
    int *__CG_p_patch__CG_verts__m_edge_idx;
    __CG_p_patch__CG_verts__m_edge_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * (__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5 - 1))) + __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5)];
    int *__CG_p_patch__CG_verts__m_edge_blk;
    __CG_p_patch__CG_verts__m_edge_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * (__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5 - 1))) + __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5)];
    int *__CG_p_patch__CG_verts__m_start_index;
    __CG_p_patch__CG_verts__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_end_index;
    __CG_p_patch__CG_verts__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_start_block;
    __CG_p_patch__CG_verts__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_end_block;
    __CG_p_patch__CG_verts__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_verts_p_patch_5];
    double *__CG_p_int__m_c_lin_e;
    __CG_p_int__m_c_lin_e = new double DACE_ALIGN(64)[((((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6) * (__f2dace_SA_c_lin_e_d_2_s_p_int_6 - 1)) + (__f2dace_SA_c_lin_e_d_0_s_p_int_6 * (__f2dace_SA_c_lin_e_d_1_s_p_int_6 - 1))) + __f2dace_SA_c_lin_e_d_0_s_p_int_6)];
    double *__CG_p_int__m_e_bln_c_s;
    __CG_p_int__m_e_bln_c_s = new double DACE_ALIGN(64)[((((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6) * (__f2dace_SA_e_bln_c_s_d_2_s_p_int_6 - 1)) + (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * (__f2dace_SA_e_bln_c_s_d_1_s_p_int_6 - 1))) + __f2dace_SA_e_bln_c_s_d_0_s_p_int_6)];
    double *__CG_p_int__m_geofac_grdiv;
    __CG_p_int__m_geofac_grdiv = new double DACE_ALIGN(64)[((((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6) * (__f2dace_SA_geofac_grdiv_d_2_s_p_int_6 - 1)) + (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * (__f2dace_SA_geofac_grdiv_d_1_s_p_int_6 - 1))) + __f2dace_SA_geofac_grdiv_d_0_s_p_int_6)];
    double *__CG_p_int__m_geofac_rot;
    __CG_p_int__m_geofac_rot = new double DACE_ALIGN(64)[((((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6) * (__f2dace_SA_geofac_rot_d_2_s_p_int_6 - 1)) + (__f2dace_SA_geofac_rot_d_0_s_p_int_6 * (__f2dace_SA_geofac_rot_d_1_s_p_int_6 - 1))) + __f2dace_SA_geofac_rot_d_0_s_p_int_6)];
    double *__CG_p_prog__m_w;
    __CG_p_prog__m_w = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_w_d_0_s_p_prog_7) * (__f2dace_SA_w_d_2_s_p_prog_7 - 1)) + (91 * __f2dace_SA_w_d_0_s_p_prog_7))];
    double *__CG_p_prog__m_vn;
    __CG_p_prog__m_vn = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_vn_d_0_s_p_prog_7) * (__f2dace_SA_vn_d_2_s_p_prog_7 - 1)) + (90 * __f2dace_SA_vn_d_0_s_p_prog_7))];
    double *__CG_p_metrics__m_ddqz_z_full_e;
    __CG_p_metrics__m_ddqz_z_full_e = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8) * (__f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8))];
    double *__CG_p_metrics__m_ddqz_z_half;
    __CG_p_metrics__m_ddqz_z_half = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8) * (__f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8 - 1)) + (91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8))];
    double *__CG_p_metrics__m_coeff_gradekin;
    __CG_p_metrics__m_coeff_gradekin = new double DACE_ALIGN(64)[((((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8) * (__f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8 - 1)) + (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * (__f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8 - 1))) + __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8)];
    double *__CG_p_diag__m_vt;
    __CG_p_diag__m_vt = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_vt_d_0_s_p_diag_9) * (__f2dace_SA_vt_d_2_s_p_diag_9 - 1)) + (90 * __f2dace_SA_vt_d_0_s_p_diag_9))];
    double *__CG_p_diag__m_vn_ie;
    __CG_p_diag__m_vn_ie = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9) * (__f2dace_SA_vn_ie_d_2_s_p_diag_9 - 1)) + (91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9))];
    double *__CG_p_diag__m_w_concorr_c;
    __CG_p_diag__m_w_concorr_c = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9) * (__f2dace_SA_w_concorr_c_d_2_s_p_diag_9 - 1)) + (91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9))];
    double *__CG_p_diag__m_ddt_vn_apc_pc;
    __CG_p_diag__m_ddt_vn_apc_pc = new double DACE_ALIGN(64)[(((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9 - 1)) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9 - 1))) + (90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9))];
    int __CG_global_data__m_nproma;
    double __CG_p_diag__m_max_vcfl_dyn;
    double out_val;
    int nrdmax_jg;
    int nflatlev_jg;
    int i_startblk_var_118_0;
    int i_endblk_var_119_0;
    int i_startblk_var_146;
    int i_endblk_var_147;
    double tmp_call_18;


    {

        {
            int* __cg_global_data__m_nflatlev = __CG_global_data__m_nflatlev;
            int __cg_global_data__m_nproma;
            int* __cg_global_data__m_nrdmax = __CG_global_data__m_nrdmax;
            double* __cg_p_diag__m_ddt_vn_apc_pc = __CG_p_diag__m_ddt_vn_apc_pc;
            double __cg_p_diag__m_max_vcfl_dyn;
            double* __cg_p_diag__m_vn_ie = __CG_p_diag__m_vn_ie;
            double* __cg_p_diag__m_vt = __CG_p_diag__m_vt;
            double* __cg_p_diag__m_w_concorr_c = __CG_p_diag__m_w_concorr_c;
            double* __cg_p_int__m_c_lin_e = __CG_p_int__m_c_lin_e;
            double* __cg_p_int__m_e_bln_c_s = __CG_p_int__m_e_bln_c_s;
            double* __cg_p_int__m_geofac_grdiv = __CG_p_int__m_geofac_grdiv;
            double* __cg_p_int__m_geofac_rot = __CG_p_int__m_geofac_rot;
            double* __cg_p_metrics__m_coeff_gradekin = __CG_p_metrics__m_coeff_gradekin;
            double* __cg_p_metrics__m_ddqz_z_full_e = __CG_p_metrics__m_ddqz_z_full_e;
            double* __cg_p_metrics__m_ddqz_z_half = __CG_p_metrics__m_ddqz_z_half;
            int* __cg_p_patch__cg_cells__m_edge_blk = __CG_p_patch__CG_cells__m_edge_blk;
            int* __cg_p_patch__cg_cells__m_edge_idx = __CG_p_patch__CG_cells__m_edge_idx;
            int* __cg_p_patch__cg_cells__m_end_block = __CG_p_patch__CG_cells__m_end_block;
            int* __cg_p_patch__cg_cells__m_end_index = __CG_p_patch__CG_cells__m_end_index;
            int* __cg_p_patch__cg_cells__m_start_block = __CG_p_patch__CG_cells__m_start_block;
            int* __cg_p_patch__cg_cells__m_start_index = __CG_p_patch__CG_cells__m_start_index;
            double* __cg_p_patch__cg_edges__m_area_edge = __CG_p_patch__CG_edges__m_area_edge;
            int* __cg_p_patch__cg_edges__m_cell_blk = __CG_p_patch__CG_edges__m_cell_blk;
            int* __cg_p_patch__cg_edges__m_cell_idx = __CG_p_patch__CG_edges__m_cell_idx;
            int* __cg_p_patch__cg_edges__m_end_block = __CG_p_patch__CG_edges__m_end_block;
            int* __cg_p_patch__cg_edges__m_end_index = __CG_p_patch__CG_edges__m_end_index;
            double* __cg_p_patch__cg_edges__m_f_e = __CG_p_patch__CG_edges__m_f_e;
            double* __cg_p_patch__cg_edges__m_inv_primal_edge_length = __CG_p_patch__CG_edges__m_inv_primal_edge_length;
            int* __cg_p_patch__cg_edges__m_quad_blk = __CG_p_patch__CG_edges__m_quad_blk;
            int* __cg_p_patch__cg_edges__m_quad_idx = __CG_p_patch__CG_edges__m_quad_idx;
            int* __cg_p_patch__cg_edges__m_start_block = __CG_p_patch__CG_edges__m_start_block;
            int* __cg_p_patch__cg_edges__m_start_index = __CG_p_patch__CG_edges__m_start_index;
            double* __cg_p_patch__cg_edges__m_tangent_orientation = __CG_p_patch__CG_edges__m_tangent_orientation;
            int* __cg_p_patch__cg_edges__m_vertex_blk = __CG_p_patch__CG_edges__m_vertex_blk;
            int* __cg_p_patch__cg_edges__m_vertex_idx = __CG_p_patch__CG_edges__m_vertex_idx;
            int* __cg_p_patch__cg_verts__m_edge_blk = __CG_p_patch__CG_verts__m_edge_blk;
            int* __cg_p_patch__cg_verts__m_edge_idx = __CG_p_patch__CG_verts__m_edge_idx;
            int* __cg_p_patch__cg_verts__m_end_block = __CG_p_patch__CG_verts__m_end_block;
            int* __cg_p_patch__cg_verts__m_end_index = __CG_p_patch__CG_verts__m_end_index;
            int* __cg_p_patch__cg_verts__m_start_block = __CG_p_patch__CG_verts__m_start_block;
            int* __cg_p_patch__cg_verts__m_start_index = __CG_p_patch__CG_verts__m_start_index;
            double* __cg_p_prog__m_vn = __CG_p_prog__m_vn;
            double* __cg_p_prog__m_w = __CG_p_prog__m_w;

            ///////////////////

            // Start flatten

            {

                {
                    {

                        #pragma omp simd
                        for (auto i = 0; i < 10; i++){
                            __cg_global_data__m_nflatlev[(i * (1))] = global_data->nflatlev[(i * (1))];
                        }

                        __cg_global_data__m_nproma = global_data->nproma;

                        #pragma omp simd
                        for (auto i = 0; i < 10; i++){
                            __cg_global_data__m_nrdmax[(i * (1))] = global_data->nrdmax[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2; i++){
                                    __cg_p_patch__cg_cells__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2)))] = p_patch->cells->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2; i++){
                                    __cg_p_patch__cg_cells__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2)))] = p_patch->cells->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_start_index[(i * (1))] = p_patch->cells->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_end_index[(i * (1))] = p_patch->cells->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_start_block[(i * (1))] = p_patch->cells->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_end_block[(i * (1))] = p_patch->cells->end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4)))] = p_patch->edges->cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4)))] = p_patch->edges->cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4)))] = p_patch->edges->vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4)))] = p_patch->edges->vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4))] = p_patch->edges->tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4))];
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4)))] = p_patch->edges->quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4)))] = p_patch->edges->quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4))] = p_patch->edges->inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_area_edge_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_area_edge_d_0_s_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_edges_p_patch_4))] = p_patch->edges->area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_f_e_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_f_e_d_0_s_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_edges_p_patch_4))] = p_patch->edges->f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_edges_p_patch_4))];
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_start_index[(i * (1))] = p_patch->edges->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_end_index[(i * (1))] = p_patch->edges->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_start_block[(i * (1))] = p_patch->edges->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_end_block[(i * (1))] = p_patch->edges->end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5; i++){
                                    __cg_p_patch__cg_verts__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5)))] = p_patch->verts->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5; i++){
                                    __cg_p_patch__cg_verts__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5)))] = p_patch->verts->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_start_index[(i * (1))] = p_patch->verts->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_end_index[(i * (1))] = p_patch->verts->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_start_block[(i * (1))] = p_patch->verts->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_end_block[(i * (1))] = p_patch->verts->end_block[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_c_lin_e_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_c_lin_e_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_c_lin_e_d_0_s_p_int_6; i++){
                                    __cg_p_int__m_c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6)))] = p_int->c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_e_bln_c_s_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_e_bln_c_s_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_e_bln_c_s_d_0_s_p_int_6; i++){
                                    __cg_p_int__m_e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6)))] = p_int->e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_grdiv_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_grdiv_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_grdiv_d_0_s_p_int_6; i++){
                                    __cg_p_int__m_geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6)))] = p_int->geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_rot_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_rot_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_rot_d_0_s_p_int_6; i++){
                                    __cg_p_int__m_geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6)))] = p_int->geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_d_2_s_p_prog_7; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_d_0_s_p_prog_7; i++){
                                    __cg_p_prog__m_w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_p_prog_7)))] = p_prog->w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_p_prog_7)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_d_2_s_p_prog_7; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_d_0_s_p_prog_7; i++){
                                    __cg_p_prog__m_vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_p_prog_7)))] = p_prog->vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_p_prog_7)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)))] = p_metrics->ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)))] = p_metrics->ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8; i++){
                                    __cg_p_metrics__m_coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8)))] = p_metrics->coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8)))];
                                }
                            }
                        }


                        __cg_p_diag__m_max_vcfl_dyn = p_diag->max_vcfl_dyn;

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vt_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vt_d_0_s_p_diag_9; i++){
                                    __cg_p_diag__m_vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_p_diag_9)))] = p_diag->vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_ie_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_ie_d_0_s_p_diag_9; i++){
                                    __cg_p_diag__m_vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9)))] = p_diag->vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_concorr_c_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_concorr_c_d_0_s_p_diag_9; i++){
                                    __cg_p_diag__m_w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9)))] = p_diag->w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto l = 0; l < __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9; l++){
                            for (auto k = 0; k < __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9; k++){
                                for (auto j = 0; j < 90; j++){
                                    #pragma omp simd
                                    for (auto i = 0; i < __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9; i++){
                                        __cg_p_diag__m_ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9)))] = p_diag->ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9)))];
                                    }
                                }
                            }
                        }


                    }

                }
            }
            // End flatten
            ///////////////////

            __CG_global_data__m_nproma = __cg_global_data__m_nproma;
            __CG_p_diag__m_max_vcfl_dyn = __cg_p_diag__m_max_vcfl_dyn;
        }

    }
   cudaDeviceSynchronize(); //EntryStreamSync
      //cudaEvent_t start1, stop1;
    //cudaEventCreate(&start1);
    //cudaEventCreate(&stop1);
    //cudaEventRecord(start1); 
 measure_time("Run");
     nrdmax_jg = __CG_global_data__m_nrdmax[0];
    nflatlev_jg = __CG_global_data__m_nflatlev[0];
    i_startblk_var_118_0 = __CG_p_patch__CG_verts__m_start_block[(2 - __f2dace_SOA_start_block_d_0_s_verts_p_patch_5)];
    i_endblk_var_119_0 = __CG_p_patch__CG_verts__m_end_block[((- __f2dace_SOA_end_block_d_0_s_verts_p_patch_5) - 5)];
    i_startblk_var_146 = __CG_p_patch__CG_edges__m_start_block[(7 - __f2dace_SOA_start_block_d_0_s_edges_p_patch_4)];
    i_endblk_var_147 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_edges_p_patch_4) - 9)];

    {

        {
            double dtime_0_in = dtime;
            double cfl_w_limit_out;

            ///////////////////
            // Tasklet code (T_l424_c424)
            cfl_w_limit_out = (0.65 / dtime_0_in);
            ///////////////////

            cfl_w_limit = cfl_w_limit_out;
        }
        {
            double cfl_w_limit_0_in = cfl_w_limit;
            double dtime_0_in = dtime;
            double dtime_1_in = dtime;
            double scalfac_exdiff_out;

            ///////////////////
            // Tasklet code (T_l425_c425)
            scalfac_exdiff_out = (0.05 / (dtime_0_in * (0.85 - (cfl_w_limit_0_in * dtime_1_in))));
            ///////////////////

            scalfac_exdiff = scalfac_exdiff_out;
        }
        {
            #pragma omp parallel for
            for (auto _for_it_3_0 = i_startblk_var_118_0; _for_it_3_0 < (i_endblk_var_119_0 + 1); _for_it_3_0 += 1) {
                loop_body_0_0_5(__state, __CG_global_data__m_nproma, &__CG_p_int__m_geofac_rot[0], &__CG_p_patch__CG_verts__m_edge_blk[0], &__CG_p_patch__CG_verts__m_edge_idx[0], &__CG_p_patch__CG_verts__m_end_index[0], &__CG_p_patch__CG_verts__m_start_index[0], &__CG_p_prog__m_vn[0], &zeta[0], _for_it_3_0, i_endblk_var_119_0, i_startblk_var_118_0, tmp_struct_symbol_8);
            }
        }

    }
    i_startblk_var_146 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_cells_p_patch_2)];
    i_endblk_var_147 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_cells_p_patch_2) - 5)];

    {
        int *levmask;
        levmask = new int DACE_ALIGN(64)[(90 * tmp_struct_symbol_13)];
        int *cfl_clipping;
        cfl_clipping = new int DACE_ALIGN(64)[(91 * tmp_struct_symbol_14)];

        {
            #pragma omp parallel for
            for (auto _for_it_22 = i_startblk_var_146; _for_it_22 < (i_endblk_var_147 + 1); _for_it_22 += 1) {
                loop_body_0_4_0(__state, __CG_global_data__m_nproma, &__CG_p_diag__m_w_concorr_c[0], &__CG_p_int__m_e_bln_c_s[0], &__CG_p_metrics__m_ddqz_z_half[0], &__CG_p_patch__CG_cells__m_edge_blk[0], &__CG_p_patch__CG_cells__m_edge_idx[0], &__CG_p_patch__CG_cells__m_end_index[0], &__CG_p_patch__CG_cells__m_start_index[0], &__CG_p_prog__m_w[0], cfl_w_limit, dtime, &z_kin_hor_e[0], &cfl_clipping[0], &levmask[0], &vcflmax[0], &z_ekinh[0], &z_w_con_c_full[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_22, i_endblk_var_147, i_startblk_var_146, nflatlev_jg, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_10, tmp_struct_symbol_13, tmp_struct_symbol_14, tmp_struct_symbol_2, tmp_struct_symbol_4);
            }
        }
        {
            #pragma omp parallel for
            for (auto _for_it_46 = Max(3, (nrdmax_jg - 2)); _for_it_46 < 88; _for_it_46 += 1) {
                int loop_body_reduce_scan_size;
                {
                    int size;

                    ///////////////////
                    // Tasklet code (size_reduce_scan)
                    size = ((i_endblk_var_147 + 1) - i_startblk_var_146);
                    ///////////////////

                    loop_body_reduce_scan_size = size;
                }
                {
                    int in_size = loop_body_reduce_scan_size;
                    int* in_arr = &levmask[((i_startblk_var_146 + (tmp_struct_symbol_13 * (_for_it_46 - 1))) - 1)];
                    int out;

                    ///////////////////

                    #ifdef __REDUCE_DEVICE__
                    out = reduce_scan_device(in_arr, in_size);
                    #elif defined(__REDUCE_GPU__)
                    out = reduce_scan_gpu(in_arr, in_size, __dace_current_stream);
                    #else
                    out = reduce_scan_cpu(in_arr, in_size);
                    #endif

                    ///////////////////

                    levelmask[(_for_it_46 - 1)] = out;
                }
            }
        }
        delete[] levmask;
        delete[] cfl_clipping;

    }
    i_startblk_var_146 = __CG_p_patch__CG_edges__m_start_block[(10 - __f2dace_SOA_start_block_d_0_s_edges_p_patch_4)];
    i_endblk_var_147 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_edges_p_patch_4) - 8)];

    {

        {
            #pragma omp parallel for
            for (auto _for_it_47 = i_startblk_var_146; _for_it_47 < (i_endblk_var_147 + 1); _for_it_47 += 1) {
                loop_body_0_5_0(__state, __CG_global_data__m_nproma, &__CG_p_diag__m_vn_ie[0], &__CG_p_diag__m_vt[0], &__CG_p_int__m_c_lin_e[0], &__CG_p_int__m_geofac_grdiv[0], &__CG_p_metrics__m_coeff_gradekin[0], &__CG_p_metrics__m_ddqz_z_full_e[0], &__CG_p_patch__CG_edges__m_area_edge[0], &__CG_p_patch__CG_edges__m_cell_blk[0], &__CG_p_patch__CG_edges__m_cell_idx[0], &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_f_e[0], &__CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &__CG_p_patch__CG_edges__m_quad_blk[0], &__CG_p_patch__CG_edges__m_quad_idx[0], &__CG_p_patch__CG_edges__m_start_index[0], &__CG_p_patch__CG_edges__m_tangent_orientation[0], &__CG_p_patch__CG_edges__m_vertex_blk[0], &__CG_p_patch__CG_edges__m_vertex_idx[0], &__CG_p_prog__m_vn[0], cfl_w_limit, dtime, &levelmask[0], scalfac_exdiff, &z_ekinh[0], &z_kin_hor_e[0], &z_w_con_c_full[0], &zeta[0], &__CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_47, i_endblk_var_147, i_startblk_var_146, nrdmax_jg, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
            }
        }

    }
    i_startblk_var_146 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_cells_p_patch_2)];
    i_endblk_var_147 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_cells_p_patch_2) - 4)];
    tmp_call_18 = -1.7976931348623157e+308;

    {
        int reduce_maxZ_to_scalar_size;

        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_maxZ_to_scalar)
            size = ((i_endblk_var_147 + 1) - i_startblk_var_146);
            ///////////////////

            reduce_maxZ_to_scalar_size = size;
        }
        {
            double* in_arr = &vcflmax[(i_startblk_var_146 - 1)];
            int in_size = reduce_maxZ_to_scalar_size;
            double out;

            ///////////////////

            #ifdef __REDUCE_DEVICE__
            out = reduce_maxZ_to_scalar_device(in_arr, in_size);
            #elif defined(__REDUCE_GPU__)
            out = reduce_maxZ_to_scalar_gpu(in_arr, in_size, __dace_current_stream);
            #else
            out = reduce_maxZ_to_scalar_cpu(in_arr, in_size);
            #endif

            ///////////////////

            out_val = out;
        }

    }
    tmp_call_18 = out_val;

    {
        double max_vcfl_dyn_var_152;

        {
            double max_vcfl_dyn_var_152_out;

            ///////////////////
            // Tasklet code (T_l652_c652)
            max_vcfl_dyn_var_152_out = tmp_call_18;
            ///////////////////

            max_vcfl_dyn_var_152 = max_vcfl_dyn_var_152_out;
        }
        {
            double max_vcfl_dyn_var_152_0_in = max_vcfl_dyn_var_152;
            double p_diag_out_max_vcfl_dyn;
  //cudaEventRecord(stop1);
    //cudaEventSynchronize(stop1);
    //float milliseconds1 = 0;
    //cudaEventElapsedTime(&milliseconds1, start1, stop1);
     measure_time("Host Based C++ Timer"); 
  //cudaEventDestroy(start1);
    //cudaEventDestroy(stop1);
    //cudaDeviceSynchronize(); 
  //std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;

            ///////////////////
            // Tasklet code (T_l653_c653)
            p_diag_out_max_vcfl_dyn = max_vcfl_dyn_var_152_0_in;
            ///////////////////

            __CG_p_diag__m_max_vcfl_dyn = p_diag_out_max_vcfl_dyn;
        }
        {
            int* __cg_global_data__m_nflatlev = &__CG_global_data__m_nflatlev[0];
            int __cg_global_data__m_nproma = __CG_global_data__m_nproma;
            int* __cg_global_data__m_nrdmax = &__CG_global_data__m_nrdmax[0];
            double* __cg_p_diag__m_ddt_vn_apc_pc = &__CG_p_diag__m_ddt_vn_apc_pc[0];
            double __cg_p_diag__m_max_vcfl_dyn = __CG_p_diag__m_max_vcfl_dyn;
            double* __cg_p_diag__m_vn_ie = &__CG_p_diag__m_vn_ie[0];
            double* __cg_p_diag__m_vt = &__CG_p_diag__m_vt[0];
            double* __cg_p_diag__m_w_concorr_c = &__CG_p_diag__m_w_concorr_c[0];
            double* __cg_p_int__m_c_lin_e = &__CG_p_int__m_c_lin_e[0];
            double* __cg_p_int__m_e_bln_c_s = &__CG_p_int__m_e_bln_c_s[0];
            double* __cg_p_int__m_geofac_grdiv = &__CG_p_int__m_geofac_grdiv[0];
            double* __cg_p_int__m_geofac_rot = &__CG_p_int__m_geofac_rot[0];
            double* __cg_p_metrics__m_coeff_gradekin = &__CG_p_metrics__m_coeff_gradekin[0];
            double* __cg_p_metrics__m_ddqz_z_full_e = &__CG_p_metrics__m_ddqz_z_full_e[0];
            double* __cg_p_metrics__m_ddqz_z_half = &__CG_p_metrics__m_ddqz_z_half[0];
            int* __cg_p_patch__cg_cells__m_edge_blk = &__CG_p_patch__CG_cells__m_edge_blk[0];
            int* __cg_p_patch__cg_cells__m_edge_idx = &__CG_p_patch__CG_cells__m_edge_idx[0];
            int* __cg_p_patch__cg_cells__m_end_block = &__CG_p_patch__CG_cells__m_end_block[0];
            int* __cg_p_patch__cg_cells__m_end_index = &__CG_p_patch__CG_cells__m_end_index[0];
            int* __cg_p_patch__cg_cells__m_start_block = &__CG_p_patch__CG_cells__m_start_block[0];
            int* __cg_p_patch__cg_cells__m_start_index = &__CG_p_patch__CG_cells__m_start_index[0];
            double* __cg_p_patch__cg_edges__m_area_edge = &__CG_p_patch__CG_edges__m_area_edge[0];
            int* __cg_p_patch__cg_edges__m_cell_blk = &__CG_p_patch__CG_edges__m_cell_blk[0];
            int* __cg_p_patch__cg_edges__m_cell_idx = &__CG_p_patch__CG_edges__m_cell_idx[0];
            int* __cg_p_patch__cg_edges__m_end_block = &__CG_p_patch__CG_edges__m_end_block[0];
            int* __cg_p_patch__cg_edges__m_end_index = &__CG_p_patch__CG_edges__m_end_index[0];
            double* __cg_p_patch__cg_edges__m_f_e = &__CG_p_patch__CG_edges__m_f_e[0];
            double* __cg_p_patch__cg_edges__m_inv_primal_edge_length = &__CG_p_patch__CG_edges__m_inv_primal_edge_length[0];
            int* __cg_p_patch__cg_edges__m_quad_blk = &__CG_p_patch__CG_edges__m_quad_blk[0];
            int* __cg_p_patch__cg_edges__m_quad_idx = &__CG_p_patch__CG_edges__m_quad_idx[0];
            int* __cg_p_patch__cg_edges__m_start_block = &__CG_p_patch__CG_edges__m_start_block[0];
            int* __cg_p_patch__cg_edges__m_start_index = &__CG_p_patch__CG_edges__m_start_index[0];
            double* __cg_p_patch__cg_edges__m_tangent_orientation = &__CG_p_patch__CG_edges__m_tangent_orientation[0];
            int* __cg_p_patch__cg_edges__m_vertex_blk = &__CG_p_patch__CG_edges__m_vertex_blk[0];
            int* __cg_p_patch__cg_edges__m_vertex_idx = &__CG_p_patch__CG_edges__m_vertex_idx[0];
            int* __cg_p_patch__cg_verts__m_edge_blk = &__CG_p_patch__CG_verts__m_edge_blk[0];
            int* __cg_p_patch__cg_verts__m_edge_idx = &__CG_p_patch__CG_verts__m_edge_idx[0];
            int* __cg_p_patch__cg_verts__m_end_block = &__CG_p_patch__CG_verts__m_end_block[0];
            int* __cg_p_patch__cg_verts__m_end_index = &__CG_p_patch__CG_verts__m_end_index[0];
            int* __cg_p_patch__cg_verts__m_start_block = &__CG_p_patch__CG_verts__m_start_block[0];
            int* __cg_p_patch__cg_verts__m_start_index = &__CG_p_patch__CG_verts__m_start_index[0];
            double* __cg_p_prog__m_vn = &__CG_p_prog__m_vn[0];
            double* __cg_p_prog__m_w = &__CG_p_prog__m_w[0];

            ///////////////////

            // Start deflatten

            {

                {
                    {

                        #pragma omp simd
                        for (auto i = 0; i < 10; i++){
                            global_data->nflatlev[(i * (1))] = __cg_global_data__m_nflatlev[(i * (1))];
                        }

                        global_data->nproma = __cg_global_data__m_nproma;

                        #pragma omp simd
                        for (auto i = 0; i < 10; i++){
                            global_data->nrdmax[(i * (1))] = __cg_global_data__m_nrdmax[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2; i++){
                                    p_patch->cells->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2)))] = __cg_p_patch__cg_cells__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2; i++){
                                    p_patch->cells->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2)))] = __cg_p_patch__cg_cells__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_cells_p_patch_2; i++){
                            p_patch->cells->start_index[(i * (1))] = __cg_p_patch__cg_cells__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_cells_p_patch_2; i++){
                            p_patch->cells->end_index[(i * (1))] = __cg_p_patch__cg_cells__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_cells_p_patch_2; i++){
                            p_patch->cells->start_block[(i * (1))] = __cg_p_patch__cg_cells__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_cells_p_patch_2; i++){
                            p_patch->cells->end_block[(i * (1))] = __cg_p_patch__cg_cells__m_end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4; i++){
                                p_patch->edges->tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4))];
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4; i++){
                                    p_patch->edges->quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4; i++){
                                p_patch->edges->inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_area_edge_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_area_edge_d_0_s_edges_p_patch_4; i++){
                                p_patch->edges->area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_f_e_d_1_s_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_f_e_d_0_s_edges_p_patch_4; i++){
                                p_patch->edges->f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_edges_p_patch_4))];
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_edges_p_patch_4; i++){
                            p_patch->edges->start_index[(i * (1))] = __cg_p_patch__cg_edges__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_edges_p_patch_4; i++){
                            p_patch->edges->end_index[(i * (1))] = __cg_p_patch__cg_edges__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_edges_p_patch_4; i++){
                            p_patch->edges->start_block[(i * (1))] = __cg_p_patch__cg_edges__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_edges_p_patch_4; i++){
                            p_patch->edges->end_block[(i * (1))] = __cg_p_patch__cg_edges__m_end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5; i++){
                                    p_patch->verts->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5)))] = __cg_p_patch__cg_verts__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5; i++){
                                    p_patch->verts->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5)))] = __cg_p_patch__cg_verts__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_verts_p_patch_5; i++){
                            p_patch->verts->start_index[(i * (1))] = __cg_p_patch__cg_verts__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_verts_p_patch_5; i++){
                            p_patch->verts->end_index[(i * (1))] = __cg_p_patch__cg_verts__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_verts_p_patch_5; i++){
                            p_patch->verts->start_block[(i * (1))] = __cg_p_patch__cg_verts__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_verts_p_patch_5; i++){
                            p_patch->verts->end_block[(i * (1))] = __cg_p_patch__cg_verts__m_end_block[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_c_lin_e_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_c_lin_e_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_c_lin_e_d_0_s_p_int_6; i++){
                                    p_int->c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6)))] = __cg_p_int__m_c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_e_bln_c_s_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_e_bln_c_s_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_e_bln_c_s_d_0_s_p_int_6; i++){
                                    p_int->e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6)))] = __cg_p_int__m_e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_grdiv_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_grdiv_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_grdiv_d_0_s_p_int_6; i++){
                                    p_int->geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6)))] = __cg_p_int__m_geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_rot_d_2_s_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_rot_d_1_s_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_rot_d_0_s_p_int_6; i++){
                                    p_int->geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6)))] = __cg_p_int__m_geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_p_int_6)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_d_2_s_p_prog_7; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_d_0_s_p_prog_7; i++){
                                    p_prog->w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_p_prog_7)))] = __cg_p_prog__m_w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_p_prog_7)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_d_2_s_p_prog_7; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_d_0_s_p_prog_7; i++){
                                    p_prog->vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_p_prog_7)))] = __cg_p_prog__m_vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_p_prog_7)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8; i++){
                                    p_metrics->ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)))] = __cg_p_metrics__m_ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8; i++){
                                    p_metrics->ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)))] = __cg_p_metrics__m_ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8; i++){
                                    p_metrics->coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8)))] = __cg_p_metrics__m_coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8)))];
                                }
                            }
                        }


                        p_diag->max_vcfl_dyn = __cg_p_diag__m_max_vcfl_dyn;

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vt_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vt_d_0_s_p_diag_9; i++){
                                    p_diag->vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_p_diag_9)))] = __cg_p_diag__m_vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_ie_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_ie_d_0_s_p_diag_9; i++){
                                    p_diag->vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9)))] = __cg_p_diag__m_vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_concorr_c_d_2_s_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_concorr_c_d_0_s_p_diag_9; i++){
                                    p_diag->w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9)))] = __cg_p_diag__m_w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto l = 0; l < __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9; l++){
                            for (auto k = 0; k < __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9; k++){
                                for (auto j = 0; j < 90; j++){
                                    #pragma omp simd
                                    for (auto i = 0; i < __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9; i++){
                                        p_diag->ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9)))] = __cg_p_diag__m_ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9)))];
                                    }
                                }
                            }
                        }


                    }

                }
            }
            // End deflatten
            ///////////////////

        }

    }

    delete[] z_w_con_c_full;
    delete[] zeta;
    delete[] z_ekinh;
    delete[] vcflmax;
    delete[] levelmask;
    delete[] __CG_global_data__m_nflatlev;
    delete[] __CG_global_data__m_nrdmax;
    delete[] __CG_p_patch__CG_cells__m_edge_idx;
    delete[] __CG_p_patch__CG_cells__m_edge_blk;
    delete[] __CG_p_patch__CG_cells__m_start_index;
    delete[] __CG_p_patch__CG_cells__m_end_index;
    delete[] __CG_p_patch__CG_cells__m_start_block;
    delete[] __CG_p_patch__CG_cells__m_end_block;
    delete[] __CG_p_patch__CG_edges__m_cell_idx;
    delete[] __CG_p_patch__CG_edges__m_cell_blk;
    delete[] __CG_p_patch__CG_edges__m_vertex_idx;
    delete[] __CG_p_patch__CG_edges__m_vertex_blk;
    delete[] __CG_p_patch__CG_edges__m_tangent_orientation;
    delete[] __CG_p_patch__CG_edges__m_quad_idx;
    delete[] __CG_p_patch__CG_edges__m_quad_blk;
    delete[] __CG_p_patch__CG_edges__m_inv_primal_edge_length;
    delete[] __CG_p_patch__CG_edges__m_area_edge;
    delete[] __CG_p_patch__CG_edges__m_f_e;
    delete[] __CG_p_patch__CG_edges__m_start_index;
    delete[] __CG_p_patch__CG_edges__m_end_index;
    delete[] __CG_p_patch__CG_edges__m_start_block;
    delete[] __CG_p_patch__CG_edges__m_end_block;
    delete[] __CG_p_patch__CG_verts__m_edge_idx;
    delete[] __CG_p_patch__CG_verts__m_edge_blk;
    delete[] __CG_p_patch__CG_verts__m_start_index;
    delete[] __CG_p_patch__CG_verts__m_end_index;
    delete[] __CG_p_patch__CG_verts__m_start_block;
    delete[] __CG_p_patch__CG_verts__m_end_block;
    delete[] __CG_p_int__m_c_lin_e;
    delete[] __CG_p_int__m_e_bln_c_s;
    delete[] __CG_p_int__m_geofac_grdiv;
    delete[] __CG_p_int__m_geofac_rot;
    delete[] __CG_p_prog__m_w;
    delete[] __CG_p_prog__m_vn;
    delete[] __CG_p_metrics__m_ddqz_z_full_e;
    delete[] __CG_p_metrics__m_ddqz_z_half;
    delete[] __CG_p_metrics__m_coeff_gradekin;
    delete[] __CG_p_diag__m_vt;
    delete[] __CG_p_diag__m_vn_ie;
    delete[] __CG_p_diag__m_w_concorr_c;
    delete[] __CG_p_diag__m_ddt_vn_apc_pc;
}

DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state = new velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t;


    tmp_struct_symbol_0=global_data->nproma;
    tmp_struct_symbol_1=global_data->nproma;
    tmp_struct_symbol_2=global_data->nproma;
    tmp_struct_symbol_3=p_patch->nblks_c;
    tmp_struct_symbol_4=global_data->nproma;
    tmp_struct_symbol_5=p_patch->nblks_e;
    tmp_struct_symbol_6=global_data->nproma;
    tmp_struct_symbol_7=p_patch->nblks_v;
    tmp_struct_symbol_8=global_data->nproma;
    tmp_struct_symbol_9=p_patch->nblks_v;
    tmp_struct_symbol_10=global_data->nproma;
    tmp_struct_symbol_11=p_patch->nblks_c;
    tmp_struct_symbol_12=p_patch->nblks_c;
    tmp_struct_symbol_13=p_patch->nblks_c;
    tmp_struct_symbol_14=global_data->nproma;
    __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_0_s;
    __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_1_s;
    __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_2_s;
    __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_0_s;
    __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_1_s;
    __f2dace_SA_neighbor_idx_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_2_s;
    __f2dace_SOA_neighbor_blk_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_0_s;
    __f2dace_SOA_neighbor_blk_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_1_s;
    __f2dace_SOA_neighbor_blk_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_2_s;
    __f2dace_SA_neighbor_blk_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_0_s;
    __f2dace_SA_neighbor_blk_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_1_s;
    __f2dace_SA_neighbor_blk_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_2_s;
    __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_0_s;
    __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_1_s;
    __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_2_s;
    __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_0_s;
    __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_1_s;
    __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_2_s;
    __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_0_s;
    __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_1_s;
    __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_2_s;
    __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_0_s;
    __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_1_s;
    __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_2_s;
    __f2dace_SOA_area_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_area_d_0_s;
    __f2dace_SOA_area_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_area_d_1_s;
    __f2dace_SA_area_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_area_d_0_s;
    __f2dace_SA_area_d_1_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_area_d_1_s;
    __f2dace_SOA_start_index_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_start_index_d_0_s;
    __f2dace_SA_start_index_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_start_index_d_0_s;
    __f2dace_SOA_end_index_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_end_index_d_0_s;
    __f2dace_SA_end_index_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_end_index_d_0_s;
    __f2dace_SOA_start_block_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_start_block_d_0_s;
    __f2dace_SA_start_block_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_start_block_d_0_s;
    __f2dace_SOA_end_block_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_end_block_d_0_s;
    __f2dace_SA_end_block_d_0_s_cells_p_patch_2 = p_patch->cells->__f2dace_SA_end_block_d_0_s;
    __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SOA_owner_mask_d_0_s;
    __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SOA_owner_mask_d_1_s;
    __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SA_owner_mask_d_0_s;
    __f2dace_SA_owner_mask_d_1_s_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SA_owner_mask_d_1_s;
    __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_0_s;
    __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_1_s;
    __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_2_s;
    __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_0_s;
    __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_1_s;
    __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_2_s;
    __f2dace_SOA_cell_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_0_s;
    __f2dace_SOA_cell_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_1_s;
    __f2dace_SOA_cell_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_2_s;
    __f2dace_SA_cell_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_0_s;
    __f2dace_SA_cell_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_1_s;
    __f2dace_SA_cell_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_2_s;
    __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_0_s;
    __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_1_s;
    __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_2_s;
    __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_0_s;
    __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_1_s;
    __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_2_s;
    __f2dace_SOA_vertex_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_0_s;
    __f2dace_SOA_vertex_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_1_s;
    __f2dace_SOA_vertex_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_2_s;
    __f2dace_SA_vertex_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_0_s;
    __f2dace_SA_vertex_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_1_s;
    __f2dace_SA_vertex_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_2_s;
    __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_tangent_orientation_d_0_s;
    __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_tangent_orientation_d_1_s;
    __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_tangent_orientation_d_0_s;
    __f2dace_SA_tangent_orientation_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_tangent_orientation_d_1_s;
    __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_0_s;
    __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_1_s;
    __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_2_s;
    __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_0_s;
    __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_1_s;
    __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_2_s;
    __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_0_s;
    __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_1_s;
    __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_2_s;
    __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_0_s;
    __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_1_s;
    __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_2_s;
    __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_primal_edge_length_d_0_s;
    __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_primal_edge_length_d_1_s;
    __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_primal_edge_length_d_0_s;
    __f2dace_SA_inv_primal_edge_length_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_primal_edge_length_d_1_s;
    __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_dual_edge_length_d_0_s;
    __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_dual_edge_length_d_1_s;
    __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_dual_edge_length_d_0_s;
    __f2dace_SA_inv_dual_edge_length_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_dual_edge_length_d_1_s;
    __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_area_edge_d_0_s;
    __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_area_edge_d_1_s;
    __f2dace_SA_area_edge_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_area_edge_d_0_s;
    __f2dace_SA_area_edge_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_area_edge_d_1_s;
    __f2dace_SOA_f_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_f_e_d_0_s;
    __f2dace_SOA_f_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_f_e_d_1_s;
    __f2dace_SA_f_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_f_e_d_0_s;
    __f2dace_SA_f_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_f_e_d_1_s;
    __f2dace_SOA_fn_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_fn_e_d_0_s;
    __f2dace_SOA_fn_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_fn_e_d_1_s;
    __f2dace_SA_fn_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_fn_e_d_0_s;
    __f2dace_SA_fn_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_fn_e_d_1_s;
    __f2dace_SOA_ft_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_ft_e_d_0_s;
    __f2dace_SOA_ft_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_ft_e_d_1_s;
    __f2dace_SA_ft_e_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_ft_e_d_0_s;
    __f2dace_SA_ft_e_d_1_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_ft_e_d_1_s;
    __f2dace_SOA_start_index_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_start_index_d_0_s;
    __f2dace_SA_start_index_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_start_index_d_0_s;
    __f2dace_SOA_end_index_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_end_index_d_0_s;
    __f2dace_SA_end_index_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_end_index_d_0_s;
    __f2dace_SOA_start_block_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_start_block_d_0_s;
    __f2dace_SA_start_block_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_start_block_d_0_s;
    __f2dace_SOA_end_block_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_end_block_d_0_s;
    __f2dace_SA_end_block_d_0_s_edges_p_patch_4 = p_patch->edges->__f2dace_SA_end_block_d_0_s;
    __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_0_s;
    __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_1_s;
    __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_2_s;
    __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_0_s;
    __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_1_s;
    __f2dace_SA_cell_idx_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_2_s;
    __f2dace_SOA_cell_blk_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_0_s;
    __f2dace_SOA_cell_blk_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_1_s;
    __f2dace_SOA_cell_blk_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_2_s;
    __f2dace_SA_cell_blk_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_0_s;
    __f2dace_SA_cell_blk_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_1_s;
    __f2dace_SA_cell_blk_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_2_s;
    __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_0_s;
    __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_1_s;
    __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_2_s;
    __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_0_s;
    __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_1_s;
    __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_2_s;
    __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_0_s;
    __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_1_s;
    __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_2_s;
    __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_0_s;
    __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_1_s;
    __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_2_s;
    __f2dace_SOA_start_index_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_start_index_d_0_s;
    __f2dace_SA_start_index_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_start_index_d_0_s;
    __f2dace_SOA_end_index_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_end_index_d_0_s;
    __f2dace_SA_end_index_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_end_index_d_0_s;
    __f2dace_SOA_start_block_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_start_block_d_0_s;
    __f2dace_SA_start_block_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_start_block_d_0_s;
    __f2dace_SOA_end_block_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_end_block_d_0_s;
    __f2dace_SA_end_block_d_0_s_verts_p_patch_5 = p_patch->verts->__f2dace_SA_end_block_d_0_s;
    __f2dace_SOA_c_lin_e_d_0_s_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_0_s;
    __f2dace_SOA_c_lin_e_d_1_s_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_1_s;
    __f2dace_SOA_c_lin_e_d_2_s_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_2_s;
    __f2dace_SA_c_lin_e_d_0_s_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_0_s;
    __f2dace_SA_c_lin_e_d_1_s_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_1_s;
    __f2dace_SA_c_lin_e_d_2_s_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_2_s;
    __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_0_s;
    __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_1_s;
    __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_2_s;
    __f2dace_SA_e_bln_c_s_d_0_s_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_0_s;
    __f2dace_SA_e_bln_c_s_d_1_s_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_1_s;
    __f2dace_SA_e_bln_c_s_d_2_s_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_2_s;
    __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_0_s;
    __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_1_s;
    __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_2_s;
    __f2dace_SA_cells_aw_verts_d_0_s_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_0_s;
    __f2dace_SA_cells_aw_verts_d_1_s_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_1_s;
    __f2dace_SA_cells_aw_verts_d_2_s_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_2_s;
    __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_0_s;
    __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_1_s;
    __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_2_s;
    __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_0_s;
    __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_1_s;
    __f2dace_SA_rbf_vec_coeff_e_d_2_s_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_2_s;
    __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_0_s;
    __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_1_s;
    __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_2_s;
    __f2dace_SA_geofac_grdiv_d_0_s_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_0_s;
    __f2dace_SA_geofac_grdiv_d_1_s_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_1_s;
    __f2dace_SA_geofac_grdiv_d_2_s_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_2_s;
    __f2dace_SOA_geofac_rot_d_0_s_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_0_s;
    __f2dace_SOA_geofac_rot_d_1_s_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_1_s;
    __f2dace_SOA_geofac_rot_d_2_s_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_2_s;
    __f2dace_SA_geofac_rot_d_0_s_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_0_s;
    __f2dace_SA_geofac_rot_d_1_s_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_1_s;
    __f2dace_SA_geofac_rot_d_2_s_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_2_s;
    __f2dace_SOA_geofac_n2s_d_0_s_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_0_s;
    __f2dace_SOA_geofac_n2s_d_1_s_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_1_s;
    __f2dace_SOA_geofac_n2s_d_2_s_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_2_s;
    __f2dace_SA_geofac_n2s_d_0_s_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_0_s;
    __f2dace_SA_geofac_n2s_d_1_s_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_1_s;
    __f2dace_SA_geofac_n2s_d_2_s_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_2_s;
    __f2dace_SOA_w_d_0_s_p_prog_7 = p_prog->__f2dace_SOA_w_d_0_s;
    __f2dace_SOA_w_d_1_s_p_prog_7 = p_prog->__f2dace_SOA_w_d_1_s;
    __f2dace_SOA_w_d_2_s_p_prog_7 = p_prog->__f2dace_SOA_w_d_2_s;
    __f2dace_SA_w_d_0_s_p_prog_7 = p_prog->__f2dace_SA_w_d_0_s;
    __f2dace_SA_w_d_2_s_p_prog_7 = p_prog->__f2dace_SA_w_d_2_s;
    __f2dace_SOA_vn_d_0_s_p_prog_7 = p_prog->__f2dace_SOA_vn_d_0_s;
    __f2dace_SOA_vn_d_1_s_p_prog_7 = p_prog->__f2dace_SOA_vn_d_1_s;
    __f2dace_SOA_vn_d_2_s_p_prog_7 = p_prog->__f2dace_SOA_vn_d_2_s;
    __f2dace_SA_vn_d_0_s_p_prog_7 = p_prog->__f2dace_SA_vn_d_0_s;
    __f2dace_SA_vn_d_2_s_p_prog_7 = p_prog->__f2dace_SA_vn_d_2_s;
    __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_0_s;
    __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_1_s;
    __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_2_s;
    __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_0_s;
    __f2dace_SA_ddxn_z_full_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_2_s;
    __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_0_s;
    __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_1_s;
    __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_2_s;
    __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_0_s;
    __f2dace_SA_ddxt_z_full_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_2_s;
    __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_0_s;
    __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_1_s;
    __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_2_s;
    __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_0_s;
    __f2dace_SA_ddqz_z_full_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_2_s;
    __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_0_s;
    __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_1_s;
    __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_2_s;
    __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_0_s;
    __f2dace_SA_ddqz_z_half_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_2_s;
    __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_0_s;
    __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_1_s;
    __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_2_s;
    __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_0_s;
    __f2dace_SA_wgtfac_c_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_2_s;
    __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_0_s;
    __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_1_s;
    __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_2_s;
    __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_0_s;
    __f2dace_SA_wgtfac_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_2_s;
    __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_0_s;
    __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_1_s;
    __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_2_s;
    __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_0_s;
    __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_1_s;
    __f2dace_SA_wgtfacq_e_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_2_s;
    __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_0_s;
    __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_1_s;
    __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_2_s;
    __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_0_s;
    __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_1_s;
    __f2dace_SA_coeff_gradekin_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_2_s;
    __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_0_s;
    __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_1_s;
    __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_2_s;
    __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_0_s;
    __f2dace_SA_coeff1_dwdz_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_2_s;
    __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_0_s;
    __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_1_s;
    __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_2_s;
    __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_0_s;
    __f2dace_SA_coeff2_dwdz_d_2_s_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_2_s;
    __f2dace_SOA_deepatmo_gradh_mc_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_mc_d_0_s;
    __f2dace_SOA_deepatmo_invr_mc_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_mc_d_0_s;
    __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s;
    __f2dace_SOA_deepatmo_invr_ifc_d_0_s_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_ifc_d_0_s;
    __f2dace_SOA_vt_d_0_s_p_diag_9 = p_diag->__f2dace_SOA_vt_d_0_s;
    __f2dace_SOA_vt_d_1_s_p_diag_9 = p_diag->__f2dace_SOA_vt_d_1_s;
    __f2dace_SOA_vt_d_2_s_p_diag_9 = p_diag->__f2dace_SOA_vt_d_2_s;
    __f2dace_SA_vt_d_0_s_p_diag_9 = p_diag->__f2dace_SA_vt_d_0_s;
    __f2dace_SA_vt_d_2_s_p_diag_9 = p_diag->__f2dace_SA_vt_d_2_s;
    __f2dace_SOA_vn_ie_d_0_s_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_0_s;
    __f2dace_SOA_vn_ie_d_1_s_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_1_s;
    __f2dace_SOA_vn_ie_d_2_s_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_2_s;
    __f2dace_SA_vn_ie_d_0_s_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_0_s;
    __f2dace_SA_vn_ie_d_2_s_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_2_s;
    __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_0_s;
    __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_1_s;
    __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_2_s;
    __f2dace_SA_w_concorr_c_d_0_s_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_0_s;
    __f2dace_SA_w_concorr_c_d_2_s_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_2_s;
    __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_0_s;
    __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_1_s;
    __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_2_s;
    __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_3_s;
    __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_0_s;
    __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_2_s;
    __f2dace_SA_ddt_vn_apc_pc_d_3_s_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_3_s;
    __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_0_s;
    __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_1_s;
    __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_2_s;
    __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_3_s;
    __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_0_s;
    __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_2_s;
    __f2dace_SA_ddt_w_adv_pc_d_3_s_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_3_s;

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *__state)
{
cleanup_reduce_sum_gpu();
cleanup_reduce_maxZ_gpu();
    int __err = 0;
    delete __state;
    return __err;
}
