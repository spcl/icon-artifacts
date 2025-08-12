#include "reductions_kernel.cuh"
#include "reductions_cpu.h"
#include "timer.h"
/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t {
    dace::cuda::Context *gpu_context;
    double * __restrict__ __0_gpu_z_w_con_c;
    uint8_t * __restrict__ __0_gpu_cfl_clipping;
    double * __restrict__ __0_gpu_z_v_grad_w;
    double * __restrict__ __0_gpu_zeta;
    double * __restrict__ __0_gpu_maxvcfl_arr;
    double * __restrict__ __0_gpu_z_ekinh;
    double * __restrict__ __0_gpu_z_w_concorr_mc;
    uint8_t * __restrict__ __0_gpu_levelmask;
    double * __restrict__ __0_gpu_z_w_v;
    uint8_t * __restrict__ __0_gpu_levmask;
    double * __restrict__ __0_gpu_z_w_con_c_full;
    double * __restrict__ __0_gpu_vcflmax;
    double * __restrict__ __0_vcflmax;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16;
    uint16_t * __restrict__ __0_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16;
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
#include "dace_wait_device.h"


#include <stdexcept>
#include <string>

DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_0_0_150_0_0(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_0_0_150_0_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_0_0_150_0_10(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5);

#include <limits>
#include <stdio.h>


DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_0_0_4_0_0(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_cell_idx_to_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16_0_0_4_0_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_2_s_verts_p_patch_5);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_neighbor_idx_to_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16_0_0_4_0_10(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_2_s_cells_p_patch_2);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_0_0_4_0_15(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_0_0_4_0_20(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_0_0_4_0_25(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4);
DACE_EXPORTED void __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_0_0_4_0_30(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4);
DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_8_1_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_0_0_0, int i_endidx_var_47_0_0, int i_startidx_var_46_0_0, int tmp_struct_symbol_6);
inline void loop_body_7_0_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, double* __restrict__ gpu___CG_p_int__m_cells_aw_verts, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int _for_it_0_0_0, int i_endblk_var_141_0, int i_endidx_in_var_143_0, int i_startblk_var_140_0, int i_startidx_in_var_142_0, int tmp_struct_symbol_6) {
    int i_startidx_var_46_0_0;
    int i_endidx_var_47_0_0;


    if (((_for_it_0_0_0 == i_startblk_var_140_0) == 1)) {

        i_startidx_var_46_0_0 = i_startidx_in_var_142_0;
        i_endidx_var_47_0_0 = __CG_global_data__m_nproma;
        if (((_for_it_0_0_0 == i_endblk_var_141_0) == 1)) {

            i_endidx_var_47_0_0 = i_endidx_in_var_143_0;

        }
    } else if (((! ((_for_it_0_0_0 == i_startblk_var_140_0) == 1)) && ((_for_it_0_0_0 == i_endblk_var_141_0) == 1))) {

        i_startidx_var_46_0_0 = 1;
        i_endidx_var_47_0_0 = i_endidx_in_var_143_0;

    } else {

        i_startidx_var_46_0_0 = 1;
        i_endidx_var_47_0_0 = __CG_global_data__m_nproma;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_8_1_5(__state, gpu___CG_p_int__m_cells_aw_verts, gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, gpu___CG_p_prog__m_w, gpu_z_w_v, __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6, __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6, __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_0_0_0, i_endidx_var_47_0_0, i_startidx_var_46_0_0, tmp_struct_symbol_6);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_16_2_6(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
inline void loop_body_7_0_13(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_verts__m_end_index, int* __restrict__ __CG_p_patch__CG_verts__m_start_index, double* __restrict__ gpu___CG_p_int__m_geofac_rot, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, uint16_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int _for_it_3_0, int i_endblk_var_119_0, int i_startblk_var_118_0, int tmp_struct_symbol_8) {
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

        __dace_runkernel_single_state_body_map_0_0_16_2_6(__state, gpu___CG_p_int__m_geofac_rot, gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, gpu___CG_p_prog__m_vn, gpu_zeta, __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_p_int_6, __f2dace_SA_geofac_rot_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_3_0, i_endidx_var_121_0, i_startidx_var_120_0, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_24_2_17(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_24_2_19(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_0_0_24_3_10(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_0_0_24_3_20(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg);
inline void loop_body_7_0_23(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, double* __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double* __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double* __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double* __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double* __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_vn, double* __restrict__ gpu___CG_p_diag__m_vn_ie, double* __restrict__ gpu___CG_p_diag__m_vt, double* __restrict__ z_kin_hor_e, double* __restrict__ z_vt_ie, double* __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int _for_it_6, int i_endblk_var_147, int i_startblk_var_146, int nflatlev_jg) {
    int i_startidx_in_var_91_3;
    int i_endidx_in_var_92_3;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_3 = __CG_p_patch__CG_edges__m_start_index[(5 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_3 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 10)];

    if (((_for_it_6 != i_startblk_var_146) && (_for_it_6 != i_endblk_var_147))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_6 != i_startblk_var_146)) && (_for_it_6 != i_endblk_var_147))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_3);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_6 != i_startblk_var_146) && (! (_for_it_6 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_3;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_3);
        i_endidx_var_149 = i_endidx_in_var_92_3;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_24_2_17(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, gpu___CG_p_prog__m_vn, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148);
        __dace_runkernel_single_state_body_0_map_0_0_24_2_19(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfac_e, gpu___CG_p_prog__m_vn, z_kin_hor_e, z_vt_ie, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

    {

        __dace_runkernel_single_state_body_2_map_0_0_24_3_10(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfacq_e, gpu___CG_p_prog__m_vn, z_kin_hor_e, z_vt_ie, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
        __dace_runkernel_single_state_body_1_map_0_0_24_3_20(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxt_z_full, gpu___CG_p_prog__m_vn, z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148, nflatlev_jg);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_31_2_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double * __restrict__ gpu_z_w_v, const double * __restrict__ z_vt_ie, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_16, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_4, int tmp_struct_symbol_6);
inline void loop_body_7_0_41(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, double* __restrict__ gpu___CG_p_diag__m_vn_ie, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, double* __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, double* __restrict__ z_vt_ie, double * __restrict__ gpu_z_v_grad_w, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int _for_it_16, int i_endblk_var_147, int replaced_var_0, int replaced_var_1, int tmp_struct_symbol_4, int tmp_struct_symbol_6) {
    int i_startidx_in_var_91_2;
    int i_endidx_in_var_92_2;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_2 = __CG_p_patch__CG_edges__m_start_index[(7 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_2 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 9)];

    if (((_for_it_16 != replaced_var_1) && (_for_it_16 != replaced_var_0))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_16 != replaced_var_1)) && (_for_it_16 != replaced_var_0))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_2);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_16 != replaced_var_1) && (! (_for_it_16 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_2;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_2);
        i_endidx_var_149 = i_endidx_in_var_92_2;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_31_2_11(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, gpu___CG_p_prog__m_w, gpu_z_v_grad_w, gpu_z_w_v, z_vt_ie, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_16, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_4, tmp_struct_symbol_6);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_38_3_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c, const double * __restrict__ z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10);
DACE_EXPORTED void __dace_runkernel_single_state_body_6_map_0_0_38_3_13(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
DACE_EXPORTED void __dace_runkernel_single_state_body_7_map_0_0_38_3_19(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
#include <cuda_runtime.h>

DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_0_0_38_4_3(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_38_4_12(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
#include <cuda_runtime.h>

DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_38_5_6(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14);
DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_38_5_18(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4);
DACE_EXPORTED void __dace_runkernel_single_state_body_5_map_0_0_38_5_16(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_40_2_3(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, const double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_40_2_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, const double * __restrict__ gpu_z_v_grad_w, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_4);
DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_0_0_40_2_28(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_geofac_n2s, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, const double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, const uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_w, const uint8_t * __restrict__ gpu_cfl_clipping, const uint8_t * __restrict__ gpu_levmask, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_area_d_0_s_cells_p_patch_2, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_area_d_0_s_cells_p_patch_2, int __f2dace_SOA_area_d_1_s_cells_p_patch_2, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SOA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SOA_geofac_n2s_d_2_s_p_int_6, int __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, const double cfl_w_limit, const double dtime, int i_endidx_2, int i_startidx_2, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
inline void loop_body_7_0_50(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_cells__m_end_index, int* __restrict__ __CG_p_patch__CG_cells__m_start_index, const double&  cfl_w_limit, const double&  dtime, double* __restrict__ gpu___CG_p_int__m_e_bln_c_s, double* __restrict__ gpu___CG_p_int__m_geofac_n2s, double* __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double* __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double* __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double* __restrict__ gpu___CG_p_metrics__m_wgtfac_c, int* __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double* __restrict__ gpu___CG_p_patch__CG_cells__m_area, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, uint16_t * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double&  scalfac_exdiff, double* __restrict__ z_kin_hor_e, double* __restrict__ z_w_concorr_me, double* __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double* __restrict__ gpu___CG_p_diag__m_w_concorr_c, uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_vcflmax, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int _for_it_22, int i_endblk_2, int i_endblk_var_147, int i_startblk_2, int i_startblk_var_146, int nflatlev_jg, int nrdmax_jg, int ntnd, int tmp_struct_symbol_0, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_4) {
    int i_startidx_in_var_79_1;
    int i_endidx_in_var_80_1;
    int i_startidx_in_var_79_0;
    int i_endidx_in_var_80_0;
    int i_startidx_2;
    int i_endidx_2;
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

        __dace_runkernel_single_state_body_map_0_0_38_3_11(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, gpu___CG_p_prog__m_w, gpu_z_ekinh, gpu_z_w_con_c, z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_10);
        __dace_runkernel_single_state_body_6_map_0_0_38_3_13(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, gpu_z_w_concorr_mc, z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);
        __dace_runkernel_single_state_body_7_map_0_0_38_3_19(__state, gpu___CG_p_diag__m_w_concorr_c, gpu___CG_p_metrics__m_wgtfac_c, gpu_z_w_concorr_mc, __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);


    }

    {

        {
            double* _out = gpu_z_w_con_c + ((i_startidx_var_148 + (90 * tmp_struct_symbol_1)) - 1);

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];
            cudaMemsetAsync(_out, 0, ((i_endidx_var_149 - i_startidx_var_148) + 1) * sizeof(double), nullptr);
            ///////////////////

        }
        __dace_runkernel_single_state_body_2_map_0_0_38_4_3(__state, gpu___CG_p_diag__m_w_concorr_c, gpu_z_w_con_c, __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_1);
        __dace_runkernel_single_state_body_4_map_0_0_38_4_12(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_z_w_con_c, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, cfl_w_limit, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14);
        {
            uint8_t* _out = gpu_levmask + (((90 * _for_it_22) + Max(3, (nrdmax_jg - 2))) - 91);

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];
            cudaMemsetAsync(_out, 0, (88 - Max(3, (nrdmax_jg - 2))) * sizeof(uint8_t), nullptr);
            ///////////////////

        }


    }

    {
        int reduce_maxZ_to_scalar_size_0;

        __dace_runkernel_single_state_body_4_map_0_0_38_5_6(__state, gpu_cfl_clipping, gpu_levmask, _for_it_22, nrdmax_jg, tmp_struct_symbol_14);
        __dace_runkernel_single_state_body_4_map_0_0_38_5_18(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_maxvcfl_arr, gpu_z_w_con_c, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
        __dace_runkernel_single_state_body_5_map_0_0_38_5_16(__state, gpu_z_w_con_c, gpu_z_w_con_c_full, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_2);
        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_maxZ_to_scalar)
            size = (((i_endidx_var_149 + 1) - i_startidx_var_148) * 87);
            ///////////////////

            reduce_maxZ_to_scalar_size_0 = size;
        }
        {
            double * in_arr = &gpu_maxvcfl_arr[((i_startidx_var_148 + ((88 * tmp_struct_symbol_4) * (_for_it_22 - 1))) - 1)];
            int in_size = reduce_maxZ_to_scalar_size_0;
            double * out = &gpu_vcflmax[(_for_it_22 - 1)];

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];

            #define __REDUCE_GPU__

            #ifdef __REDUCE_DEVICE__
            reduce_maxZ_to_address_device(in_arr, out, in_size);
            #elif defined(__REDUCE_GPU__)
            reduce_maxZ_to_address_gpu(in_arr, out, in_size, __dace_current_stream);
            #else
            reduce_maxZ_to_address_cpu(in_arr, out, in_size);
            #endif

            #undef __REDUCE_GPU__

            ///////////////////

        }
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

    if ((! (((_for_it_22 < i_startblk_2) || (_for_it_22 > i_endblk_2)) == 1))) {

        i_startidx_in_var_79_0 = __CG_p_patch__CG_cells__m_start_index[(5 - __f2dace_SOA_start_index_d_0_s_cells_p_patch_2)];
        i_endidx_in_var_80_0 = __CG_p_patch__CG_cells__m_end_index[((- __f2dace_SOA_end_index_d_0_s_cells_p_patch_2) - 4)];
        if (((_for_it_22 == i_startblk_2) == 1)) {

            i_startidx_2 = max(1, i_startidx_in_var_79_0);
            i_endidx_2 = __CG_global_data__m_nproma;
            if (((_for_it_22 == i_endblk_2) == 1)) {

                i_endidx_2 = i_endidx_in_var_80_0;

            }
        } else if (((! ((_for_it_22 == i_startblk_2) == 1)) && ((_for_it_22 == i_endblk_2) == 1))) {

            i_startidx_2 = 1;
            i_endidx_2 = i_endidx_in_var_80_0;

        } else {

            i_startidx_2 = 1;
            i_endidx_2 = __CG_global_data__m_nproma;

        }
        {

            __dace_runkernel_single_state_body_map_0_0_40_2_3(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_metrics__m_coeff1_dwdz, gpu___CG_p_metrics__m_coeff2_dwdz, gpu___CG_p_prog__m_w, gpu_z_w_con_c, __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8, __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8, __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, i_endidx_2, i_startidx_2, ntnd, tmp_struct_symbol_1);
            __dace_runkernel_single_state_body_0_map_0_0_40_2_11(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, gpu_z_v_grad_w, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, i_endidx_2, i_startidx_2, ntnd, tmp_struct_symbol_4);
            __dace_runkernel_single_state_body_1_map_0_0_40_2_28(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_int__m_geofac_n2s, gpu___CG_p_metrics__m_ddqz_z_half, gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, gpu___CG_p_patch__CG_cells__m_area, gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, gpu___CG_p_prog__m_w, gpu_cfl_clipping, gpu_levmask, gpu_z_w_con_c, __f2dace_SA_area_d_0_s_cells_p_patch_2, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_n2s_d_0_s_p_int_6, __f2dace_SA_geofac_n2s_d_1_s_p_int_6, __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_area_d_0_s_cells_p_patch_2, __f2dace_SOA_area_d_1_s_cells_p_patch_2, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_n2s_d_0_s_p_int_6, __f2dace_SOA_geofac_n2s_d_1_s_p_int_6, __f2dace_SOA_geofac_n2s_d_2_s_p_int_6, __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2, __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, cfl_w_limit, dtime, i_endidx_2, i_startidx_2, nrdmax_jg, ntnd, scalfac_exdiff, tmp_struct_symbol_1, tmp_struct_symbol_14);
//            DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


        }
    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_7_0_79(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_68_2_7(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, const double * __restrict__ z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_68_2_29(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
inline void loop_body_7_0_88(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, const double&  cfl_w_limit, const double&  dtime, double* __restrict__ gpu___CG_p_diag__m_vn_ie, double* __restrict__ gpu___CG_p_diag__m_vt, double* __restrict__ gpu___CG_p_int__m_c_lin_e, double* __restrict__ gpu___CG_p_int__m_geofac_grdiv, double* __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double* __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double* __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, double* __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, double* __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, uint16_t * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, double* __restrict__ gpu___CG_p_prog__m_vn, uint8_t * __restrict__ gpu_levelmask, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_zeta, const double&  scalfac_exdiff, double* __restrict__ z_kin_hor_e, double* __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_47, int i_endblk_var_147, int nrdmax_jg, int ntnd, int replaced_var_4, int replaced_var_5, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int i_startidx_in_var_91_0;
    int i_endidx_in_var_92_0;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_0 = __CG_p_patch__CG_edges__m_start_index[(10 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_0 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 8)];

    if (((_for_it_47 != replaced_var_5) && (_for_it_47 != replaced_var_4))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_47 != replaced_var_5)) && (_for_it_47 != replaced_var_4))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_47 != replaced_var_5) && (! (_for_it_47 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_0;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = i_endidx_in_var_92_0;

    }

    {

        __dace_runkernel_single_state_body_0_map_0_0_68_2_7(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, gpu___CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, gpu_z_ekinh, gpu_z_w_con_c_full, gpu_zeta, z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_f_e_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_47, i_endidx_var_149, i_startidx_var_148, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
        __dace_runkernel_single_state_body_map_0_0_68_2_29(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_int__m_geofac_grdiv, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, gpu___CG_p_prog__m_vn, gpu_levelmask, gpu_z_w_con_c_full, gpu_zeta, __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_47, cfl_w_limit, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, ntnd, scalfac_exdiff, tmp_struct_symbol_2, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_79_1_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_0_0_0, int i_endidx_var_47_0_0, int i_startidx_var_46_0_0, int tmp_struct_symbol_6);
inline void loop_body_78_0_5(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, double* __restrict__ gpu___CG_p_int__m_cells_aw_verts, int* __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int _for_it_0_0_0, int i_endblk_var_141_0, int i_endidx_in_var_143_0, int i_startblk_var_140_0, int i_startidx_in_var_142_0, int tmp_struct_symbol_6) {
    int i_startidx_var_46_0_0;
    int i_endidx_var_47_0_0;


    if (((_for_it_0_0_0 == i_startblk_var_140_0) == 1)) {

        i_startidx_var_46_0_0 = i_startidx_in_var_142_0;
        i_endidx_var_47_0_0 = __CG_global_data__m_nproma;
        if (((_for_it_0_0_0 == i_endblk_var_141_0) == 1)) {

            i_endidx_var_47_0_0 = i_endidx_in_var_143_0;

        }
    } else if (((! ((_for_it_0_0_0 == i_startblk_var_140_0) == 1)) && ((_for_it_0_0_0 == i_endblk_var_141_0) == 1))) {

        i_startidx_var_46_0_0 = 1;
        i_endidx_var_47_0_0 = i_endidx_in_var_143_0;

    } else {

        i_startidx_var_46_0_0 = 1;
        i_endidx_var_47_0_0 = __CG_global_data__m_nproma;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_79_1_5(__state, gpu___CG_p_int__m_cells_aw_verts, gpu___CG_p_patch__CG_verts__m_cell_idx, gpu___CG_p_prog__m_w, gpu_z_w_v, __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, __f2dace_SA_cells_aw_verts_d_0_s_p_int_6, __f2dace_SA_cells_aw_verts_d_1_s_p_int_6, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_cell_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_cell_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_cell_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_cells_aw_verts_d_0_s_p_int_6, __f2dace_SOA_cells_aw_verts_d_1_s_p_int_6, __f2dace_SOA_cells_aw_verts_d_2_s_p_int_6, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_0_0_0, i_endidx_var_47_0_0, i_startidx_var_46_0_0, tmp_struct_symbol_6);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_87_2_6(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
inline void loop_body_78_0_13(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_verts__m_end_index, int* __restrict__ __CG_p_patch__CG_verts__m_start_index, double* __restrict__ gpu___CG_p_int__m_geofac_rot, uint8_t * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, int* __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double* __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int _for_it_3_0, int i_endblk_var_119_0, int i_startblk_var_118_0, int tmp_struct_symbol_8) {
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

        __dace_runkernel_single_state_body_map_0_0_87_2_6(__state, gpu___CG_p_int__m_geofac_rot, gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, gpu___CG_p_patch__CG_verts__m_edge_idx, gpu___CG_p_prog__m_vn, gpu_zeta, __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_p_int_6, __f2dace_SA_geofac_rot_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_3_0, i_endidx_var_121_0, i_startidx_var_120_0, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_95_2_17(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_95_2_19(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_0_0_95_3_10(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_0_0_95_3_20(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg);
inline void loop_body_78_0_23(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, double* __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double* __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double* __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double* __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double* __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int* __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double* __restrict__ gpu___CG_p_prog__m_vn, double* __restrict__ gpu___CG_p_diag__m_vn_ie, double* __restrict__ gpu___CG_p_diag__m_vt, double* __restrict__ z_kin_hor_e, double* __restrict__ z_vt_ie, double* __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int _for_it_6, int i_endblk_var_147, int i_startblk_var_146, int nflatlev_jg) {
    int i_startidx_in_var_91_3;
    int i_endidx_in_var_92_3;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_3 = __CG_p_patch__CG_edges__m_start_index[(5 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_3 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 10)];

    if (((_for_it_6 != i_startblk_var_146) && (_for_it_6 != i_endblk_var_147))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_6 != i_startblk_var_146)) && (_for_it_6 != i_endblk_var_147))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_3);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_6 != i_startblk_var_146) && (! (_for_it_6 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_3;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_3);
        i_endidx_var_149 = i_endidx_in_var_92_3;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_95_2_17(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_prog__m_vn, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_rbf_vec_coeff_e_d_0_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_1_s_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_2_s_p_int_6, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148);
        __dace_runkernel_single_state_body_0_map_0_0_95_2_19(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfac_e, gpu___CG_p_prog__m_vn, z_kin_hor_e, z_vt_ie, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SA_wgtfac_e_d_0_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, __f2dace_SOA_wgtfac_e_d_0_s_p_metrics_8, __f2dace_SOA_wgtfac_e_d_1_s_p_metrics_8, __f2dace_SOA_wgtfac_e_d_2_s_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

    {

        __dace_runkernel_single_state_body_2_map_0_0_95_3_10(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfacq_e, gpu___CG_p_prog__m_vn, z_kin_hor_e, z_vt_ie, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SA_wgtfacq_e_d_0_s_p_metrics_8, __f2dace_SA_wgtfacq_e_d_1_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, __f2dace_SOA_wgtfacq_e_d_0_s_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_1_s_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_2_s_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
        __dace_runkernel_single_state_body_1_map_0_0_95_3_20(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxt_z_full, gpu___CG_p_prog__m_vn, z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_ddxn_z_full_d_0_s_p_metrics_8, __f2dace_SA_ddxt_z_full_d_0_s_p_metrics_8, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_ddxn_z_full_d_0_s_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_1_s_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_2_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_0_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_1_s_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_2_s_p_metrics_8, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148, nflatlev_jg);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_102_2_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double * __restrict__ gpu_z_w_v, const double * __restrict__ z_vt_ie, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_16, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_4, int tmp_struct_symbol_6);
inline void loop_body_78_0_41(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, double* __restrict__ gpu___CG_p_diag__m_vn_ie, int* __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, double* __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int* __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, double* __restrict__ z_vt_ie, double * __restrict__ gpu_z_v_grad_w, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int _for_it_16, int i_endblk_var_147, int replaced_var_0, int replaced_var_1, int tmp_struct_symbol_4, int tmp_struct_symbol_6) {
    int i_startidx_in_var_91_2;
    int i_endidx_in_var_92_2;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_2 = __CG_p_patch__CG_edges__m_start_index[(7 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_2 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 9)];

    if (((_for_it_16 != replaced_var_1) && (_for_it_16 != replaced_var_0))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_16 != replaced_var_1)) && (_for_it_16 != replaced_var_0))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_2);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_16 != replaced_var_1) && (! (_for_it_16 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_2;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_2);
        i_endidx_var_149 = i_endidx_in_var_92_2;

    }

    {

        __dace_runkernel_single_state_body_map_0_0_102_2_11(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_prog__m_w, gpu_z_v_grad_w, gpu_z_w_v, z_vt_ie, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_inv_dual_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_16, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_4, tmp_struct_symbol_6);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_109_3_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c, const double * __restrict__ z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10);
DACE_EXPORTED void __dace_runkernel_single_state_body_6_map_0_0_109_3_13(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
DACE_EXPORTED void __dace_runkernel_single_state_body_7_map_0_0_109_3_19(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
#include <cuda_runtime.h>

#include <cuda_runtime.h>

DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_0_0_109_4_3(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_109_4_12(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, uint8_t * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_109_5_6(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_14);
DACE_EXPORTED void __dace_runkernel_single_state_body_4_map_0_0_109_5_18(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const uint8_t * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4);
DACE_EXPORTED void __dace_runkernel_single_state_body_5_map_0_0_109_5_16(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_111_2_3(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, const double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_111_2_11(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_v_grad_w, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_4);
DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_0_0_111_2_28(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_geofac_n2s, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, const double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, const double * __restrict__ gpu___CG_p_prog__m_w, const uint8_t * __restrict__ gpu_cfl_clipping, const uint8_t * __restrict__ gpu_levmask, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_area_d_0_s_cells_p_patch_2, int __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SA_w_d_0_s_p_prog_7, int __f2dace_SOA_area_d_0_s_cells_p_patch_2, int __f2dace_SOA_area_d_1_s_cells_p_patch_2, int __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_n2s_d_0_s_p_int_6, int __f2dace_SOA_geofac_n2s_d_1_s_p_int_6, int __f2dace_SOA_geofac_n2s_d_2_s_p_int_6, int __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2, int __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2, int __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2, int __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, int __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3, int __f2dace_SOA_w_d_0_s_p_prog_7, int __f2dace_SOA_w_d_1_s_p_prog_7, int __f2dace_SOA_w_d_2_s_p_prog_7, int _for_it_22, const double cfl_w_limit, const double dtime, int i_endidx_2, int i_startidx_2, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
inline void loop_body_78_0_50(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_cells__m_end_index, int* __restrict__ __CG_p_patch__CG_cells__m_start_index, const double&  cfl_w_limit, const double&  dtime, double* __restrict__ gpu___CG_p_int__m_e_bln_c_s, double* __restrict__ gpu___CG_p_int__m_geofac_n2s, double* __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double* __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double* __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double* __restrict__ gpu___CG_p_metrics__m_wgtfac_c, int* __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double* __restrict__ gpu___CG_p_patch__CG_cells__m_area, uint8_t * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, int* __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int* __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, double* __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double&  scalfac_exdiff, double* __restrict__ z_kin_hor_e, double* __restrict__ z_w_concorr_me, double* __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double* __restrict__ gpu___CG_p_diag__m_w_concorr_c, uint8_t * __restrict__ gpu_cfl_clipping, uint8_t * __restrict__ gpu_levmask, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_vcflmax, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, int _for_it_22, int i_endblk_2, int i_endblk_var_147, int i_startblk_2, int i_startblk_var_146, int nflatlev_jg, int nrdmax_jg, int ntnd, int tmp_struct_symbol_0, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_4) {
    int i_startidx_in_var_79_1;
    int i_endidx_in_var_80_1;
    int i_startidx_in_var_79_0;
    int i_endidx_in_var_80_0;
    int i_startidx_2;
    int i_endidx_2;
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

        __dace_runkernel_single_state_body_map_0_0_109_3_11(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu___CG_p_prog__m_w, gpu_z_ekinh, gpu_z_w_con_c, z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_10);
        __dace_runkernel_single_state_body_6_map_0_0_109_3_13(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu_z_w_concorr_mc, z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);
        __dace_runkernel_single_state_body_7_map_0_0_109_3_19(__state, gpu___CG_p_diag__m_w_concorr_c, gpu___CG_p_metrics__m_wgtfac_c, gpu_z_w_concorr_mc, __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SA_wgtfac_c_d_0_s_p_metrics_8, __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, __f2dace_SOA_wgtfac_c_d_0_s_p_metrics_8, __f2dace_SOA_wgtfac_c_d_1_s_p_metrics_8, __f2dace_SOA_wgtfac_c_d_2_s_p_metrics_8, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);


    }

    {

        {
            uint8_t* _out = gpu_levmask + (((90 * _for_it_22) + Max(3, (nrdmax_jg - 2))) - 91);

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];
            cudaMemsetAsync(_out, 0, (88 - Max(3, (nrdmax_jg - 2))) * sizeof(uint8_t), nullptr);
            ///////////////////

        }
        {
            double* _out = gpu_z_w_con_c + ((i_startidx_var_148 + (90 * tmp_struct_symbol_1)) - 1);

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];
            cudaMemsetAsync(_out, 0, ((i_endidx_var_149 - i_startidx_var_148) + 1) * sizeof(double), nullptr);
            ///////////////////

        }
        __dace_runkernel_single_state_body_2_map_0_0_109_4_3(__state, gpu___CG_p_diag__m_w_concorr_c, gpu_z_w_con_c, __f2dace_SA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_0_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_p_diag_9, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_1);
        __dace_runkernel_single_state_body_4_map_0_0_109_4_12(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_z_w_con_c, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, cfl_w_limit, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14);


    }

    {
        int reduce_maxZ_to_scalar_size_0;

        __dace_runkernel_single_state_body_4_map_0_0_109_5_6(__state, gpu_cfl_clipping, gpu_levmask, _for_it_22, nrdmax_jg, tmp_struct_symbol_14);
        __dace_runkernel_single_state_body_4_map_0_0_109_5_18(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_maxvcfl_arr, gpu_z_w_con_c, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, _for_it_22, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
        __dace_runkernel_single_state_body_5_map_0_0_109_5_16(__state, gpu_z_w_con_c, gpu_z_w_con_c_full, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_2);
        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_maxZ_to_scalar)
            size = (((i_endidx_var_149 + 1) - i_startidx_var_148) * 87);
            ///////////////////

            reduce_maxZ_to_scalar_size_0 = size;
        }
        {
            double * in_arr = &gpu_maxvcfl_arr[((i_startidx_var_148 + ((88 * tmp_struct_symbol_4) * (_for_it_22 - 1))) - 1)];
            int in_size = reduce_maxZ_to_scalar_size_0;
            double * out = &gpu_vcflmax[(_for_it_22 - 1)];

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];

            #define __REDUCE_GPU__

            #ifdef __REDUCE_DEVICE__
            reduce_maxZ_to_address_device(in_arr, out, in_size);
            #elif defined(__REDUCE_GPU__)
            reduce_maxZ_to_address_gpu(in_arr, out, in_size, __dace_current_stream);
            #else
            reduce_maxZ_to_address_cpu(in_arr, out, in_size);
            #endif

            #undef __REDUCE_GPU__

            ///////////////////

        }
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

    if ((! (((_for_it_22 < i_startblk_2) || (_for_it_22 > i_endblk_2)) == 1))) {

        i_startidx_in_var_79_0 = __CG_p_patch__CG_cells__m_start_index[(5 - __f2dace_SOA_start_index_d_0_s_cells_p_patch_2)];
        i_endidx_in_var_80_0 = __CG_p_patch__CG_cells__m_end_index[((- __f2dace_SOA_end_index_d_0_s_cells_p_patch_2) - 4)];
        if (((_for_it_22 == i_startblk_2) == 1)) {

            i_startidx_2 = max(1, i_startidx_in_var_79_0);
            i_endidx_2 = __CG_global_data__m_nproma;
            if (((_for_it_22 == i_endblk_2) == 1)) {

                i_endidx_2 = i_endidx_in_var_80_0;

            }
        } else if (((! ((_for_it_22 == i_startblk_2) == 1)) && ((_for_it_22 == i_endblk_2) == 1))) {

            i_startidx_2 = 1;
            i_endidx_2 = i_endidx_in_var_80_0;

        } else {

            i_startidx_2 = 1;
            i_endidx_2 = __CG_global_data__m_nproma;

        }
        {

            __dace_runkernel_single_state_body_map_0_0_111_2_3(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_metrics__m_coeff1_dwdz, gpu___CG_p_metrics__m_coeff2_dwdz, gpu___CG_p_prog__m_w, gpu_z_w_con_c, __f2dace_SA_coeff1_dwdz_d_0_s_p_metrics_8, __f2dace_SA_coeff2_dwdz_d_0_s_p_metrics_8, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_coeff1_dwdz_d_0_s_p_metrics_8, __f2dace_SOA_coeff1_dwdz_d_1_s_p_metrics_8, __f2dace_SOA_coeff1_dwdz_d_2_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_0_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_1_s_p_metrics_8, __f2dace_SOA_coeff2_dwdz_d_2_s_p_metrics_8, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, i_endidx_2, i_startidx_2, ntnd, tmp_struct_symbol_1);
            __dace_runkernel_single_state_body_0_map_0_0_111_2_11(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu_z_v_grad_w, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_e_bln_c_s_d_0_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_p_int_6, __f2dace_SOA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_cells_p_patch_2, _for_it_22, i_endidx_2, i_startidx_2, ntnd, tmp_struct_symbol_4);
            __dace_runkernel_single_state_body_1_map_0_0_111_2_28(__state, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_int__m_geofac_n2s, gpu___CG_p_metrics__m_ddqz_z_half, gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, gpu___CG_p_patch__CG_cells__m_area, gpu___CG_p_patch__CG_cells__m_neighbor_idx, gpu___CG_p_prog__m_w, gpu_cfl_clipping, gpu_levmask, gpu_z_w_con_c, __f2dace_SA_area_d_0_s_cells_p_patch_2, __f2dace_SA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_n2s_d_0_s_p_int_6, __f2dace_SA_geofac_n2s_d_1_s_p_int_6, __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, __f2dace_SA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, __f2dace_SA_w_d_0_s_p_prog_7, __f2dace_SOA_area_d_0_s_cells_p_patch_2, __f2dace_SOA_area_d_1_s_cells_p_patch_2, __f2dace_SOA_ddqz_z_half_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_p_metrics_8, __f2dace_SOA_ddt_w_adv_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_n2s_d_0_s_p_int_6, __f2dace_SOA_geofac_n2s_d_1_s_p_int_6, __f2dace_SOA_geofac_n2s_d_2_s_p_int_6, __f2dace_SOA_neighbor_idx_d_0_s_cells_p_patch_2, __f2dace_SOA_neighbor_idx_d_1_s_cells_p_patch_2, __f2dace_SOA_neighbor_idx_d_2_s_cells_p_patch_2, __f2dace_SOA_owner_mask_d_0_s_decomp_info_cells_p_patch_3, __f2dace_SOA_owner_mask_d_1_s_decomp_info_cells_p_patch_3, __f2dace_SOA_w_d_0_s_p_prog_7, __f2dace_SOA_w_d_1_s_p_prog_7, __f2dace_SOA_w_d_2_s_p_prog_7, _for_it_22, cfl_w_limit, dtime, i_endidx_2, i_startidx_2, nrdmax_jg, ntnd, scalfac_exdiff, tmp_struct_symbol_1, tmp_struct_symbol_14);
//            DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


        }
    }

}

DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_78_0_79(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, uint8_t * __restrict__ gpu_levelmask, const uint8_t * __restrict__ gpu_levmask, int loop_body_reduce_scan_size, int nrdmax_jg, int replaced_var_2, int replaced_var_3, int tmp_struct_symbol_13);
DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_0_0_139_2_7(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, const double * __restrict__ z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_p_diag_9, int __f2dace_SA_vt_d_0_s_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_p_diag_9, int __f2dace_SOA_vt_d_0_s_p_diag_9, int __f2dace_SOA_vt_d_1_s_p_diag_9, int __f2dace_SOA_vt_d_2_s_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
DACE_EXPORTED void __dace_runkernel_single_state_body_map_0_0_139_2_29(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const uint8_t * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_p_int_6, int __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_p_int_6, int __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_p_prog_7, int __f2dace_SOA_vn_d_1_s_p_prog_7, int __f2dace_SOA_vn_d_2_s_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
inline void loop_body_78_0_88(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, int* __restrict__ __CG_p_patch__CG_edges__m_end_index, int* __restrict__ __CG_p_patch__CG_edges__m_start_index, const double&  cfl_w_limit, const double&  dtime, double* __restrict__ gpu___CG_p_diag__m_vn_ie, double* __restrict__ gpu___CG_p_diag__m_vt, double* __restrict__ gpu___CG_p_int__m_c_lin_e, double* __restrict__ gpu___CG_p_int__m_geofac_grdiv, double* __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double* __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double* __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int* __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double* __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double* __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, uint8_t * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, int* __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double* __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int* __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, double* __restrict__ gpu___CG_p_prog__m_vn, uint8_t * __restrict__ gpu_levelmask, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_zeta, const double&  scalfac_exdiff, double* __restrict__ z_kin_hor_e, double* __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int _for_it_47, int i_endblk_var_147, int nrdmax_jg, int ntnd, int replaced_var_4, int replaced_var_5, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int i_startidx_in_var_91_0;
    int i_endidx_in_var_92_0;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_0 = __CG_p_patch__CG_edges__m_start_index[(10 - __f2dace_SOA_start_index_d_0_s_edges_p_patch_4)];
    i_endidx_in_var_92_0 = __CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_edges_p_patch_4) - 8)];

    if (((_for_it_47 != replaced_var_5) && (_for_it_47 != replaced_var_4))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_47 != replaced_var_5)) && (_for_it_47 != replaced_var_4))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_47 != replaced_var_5) && (! (_for_it_47 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_0;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = i_endidx_in_var_92_0;

    }

    {

        __dace_runkernel_single_state_body_0_map_0_0_139_2_7(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu_z_ekinh, gpu_z_w_con_c_full, gpu_zeta, z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_f_e_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_p_diag_9, __f2dace_SA_vt_d_0_s_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_f_e_d_0_s_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_p_diag_9, __f2dace_SOA_vt_d_0_s_p_diag_9, __f2dace_SOA_vt_d_1_s_p_diag_9, __f2dace_SOA_vt_d_2_s_p_diag_9, _for_it_47, i_endidx_var_149, i_startidx_var_148, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
        __dace_runkernel_single_state_body_map_0_0_139_2_29(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_int__m_geofac_grdiv, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_prog__m_vn, gpu_levelmask, gpu_z_w_con_c_full, gpu_zeta, __f2dace_SA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SA_c_lin_e_d_0_s_p_int_6, __f2dace_SA_c_lin_e_d_1_s_p_int_6, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vn_d_0_s_p_prog_7, __f2dace_SOA_area_edge_d_0_s_edges_p_patch_4, __f2dace_SOA_area_edge_d_1_s_edges_p_patch_4, __f2dace_SOA_c_lin_e_d_0_s_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_p_int_6, __f2dace_SOA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_ddqz_z_full_e_d_0_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_p_diag_9, __f2dace_SOA_geofac_grdiv_d_0_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_1_s_p_int_6, __f2dace_SOA_geofac_grdiv_d_2_s_p_int_6, __f2dace_SOA_inv_primal_edge_length_d_0_s_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_edges_p_patch_4, __f2dace_SOA_vn_d_0_s_p_prog_7, __f2dace_SOA_vn_d_1_s_p_prog_7, __f2dace_SOA_vn_d_2_s_p_prog_7, _for_it_47, cfl_w_limit, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, ntnd, scalfac_exdiff, tmp_struct_symbol_2, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


    }

}

void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1_internal(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t*__state, int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_n2s, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double cfl_w_limit;
    double scalfac_exdiff;
    int loop_body_reduce_scan_size;
    int nrdmax_jg;
    int nflatlev_jg;
    int i_startblk_var_140_0;
    int i_endblk_var_141_0;
    int i_startidx_in_var_142_0;
    int i_endidx_in_var_143_0;
    int i_startblk_var_118_0;
    int i_endblk_var_119_0;
    int i_startblk_var_146;
    int i_endblk_var_147;
    int replaced_var_0;
    int replaced_var_1;
    int i_startblk_2;
    int i_endblk_2;
    int replaced_var_2;
    int replaced_var_3;
    int replaced_var_4;
    int replaced_var_5;
    int bitwidth_check_done_sym;
    int nblk_lowering_done_sym;
    int bitwidth_sym;
    int replaced_var_6;
    int replaced_var_7;


    {

        {

            ///////////////////
            dace_wait_device();
            ///////////////////

        }

    }

    {

        {

            ///////////////////

            if (p_patch->nblks_c != 1){
                throw std::runtime_error("Expected exactly 1 for nblk_c, got " + std::to_string(p_patch->nblks_c));
            }
            if (p_patch->nblks_v != 1){
                throw std::runtime_error("Expected exactly 1 for nblk_v, got " + std::to_string(p_patch->nblks_v));
            }
            if (p_patch->nblks_e != 2){
                throw std::runtime_error("Expected exactly 2 for nblk_e, got " + std::to_string(p_patch->nblks_e));
            }
            ///////////////////

        }

    }
    nrdmax_jg = __CG_global_data__m_nrdmax[0];
    nflatlev_jg = __CG_global_data__m_nflatlev[0];
    i_startblk_var_140_0 = __CG_p_patch__CG_verts__m_start_block[(2 - __f2dace_SOA_start_block_d_0_s_verts_p_patch_5)];
    i_endblk_var_141_0 = __CG_p_patch__CG_verts__m_end_block[((- __f2dace_SOA_end_block_d_0_s_verts_p_patch_5) - 5)];
    i_startidx_in_var_142_0 = __CG_p_patch__CG_verts__m_start_index[(2 - __f2dace_SOA_start_index_d_0_s_verts_p_patch_5)];
    i_endidx_in_var_143_0 = __CG_p_patch__CG_verts__m_end_index[((- __f2dace_SOA_end_index_d_0_s_verts_p_patch_5) - 5)];
    i_startblk_var_118_0 = __CG_p_patch__CG_verts__m_start_block[(2 - __f2dace_SOA_start_block_d_0_s_verts_p_patch_5)];
    i_endblk_var_119_0 = __CG_p_patch__CG_verts__m_end_block[((- __f2dace_SOA_end_block_d_0_s_verts_p_patch_5) - 5)];
    i_startblk_var_146 = __CG_p_patch__CG_edges__m_start_block[(5 - __f2dace_SOA_start_block_d_0_s_edges_p_patch_4)];
    i_endblk_var_147 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_edges_p_patch_4) - 10)];
    replaced_var_0 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_edges_p_patch_4) - 9)];
    replaced_var_1 = __CG_p_patch__CG_edges__m_start_block[(7 - __f2dace_SOA_start_block_d_0_s_edges_p_patch_4)];
    i_startblk_2 = __CG_p_patch__CG_cells__m_start_block[(5 - __f2dace_SOA_start_block_d_0_s_cells_p_patch_2)];
    i_endblk_2 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_cells_p_patch_2) - 4)];
    replaced_var_2 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_cells_p_patch_2) - 5)];
    replaced_var_3 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_cells_p_patch_2)];
    replaced_var_4 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_edges_p_patch_4) - 8)];
    replaced_var_5 = __CG_p_patch__CG_edges__m_start_block[(10 - __f2dace_SOA_start_block_d_0_s_edges_p_patch_4)];
    bitwidth_check_done_sym = __state->__0_bitwidth_check_done;
    nblk_lowering_done_sym = __state->__0_nblk_lowering_done;

    if ((nblk_lowering_done_sym == 0)) {
        {

            __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_blk_to_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8_0_0_150_0_0(__state, gpu___CG_p_patch__CG_cells__m_edge_blk, __state->__0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2, __f2dace_SA_edge_blk_d_2_s_cells_p_patch_2);
            __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_blk_to_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8_0_0_150_0_5(__state, gpu___CG_p_patch__CG_edges__m_quad_blk, __state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4, __f2dace_SA_quad_blk_d_2_s_edges_p_patch_4);
            __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_blk_to_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8_0_0_150_0_10(__state, gpu___CG_p_patch__CG_verts__m_edge_blk, __state->__0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5, __f2dace_SA_edge_blk_d_2_s_verts_p_patch_5);
            {
                int _out_nblk_lowering_done;

                ///////////////////
                _out_nblk_lowering_done = 1;
                ///////////////////

                __state->__0_nblk_lowering_done = _out_nblk_lowering_done;
            }
//            DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


        }
    }

    if ((bitwidth_check_done_sym == 0)) {
        {

            {
                int _in___CG_global_data__m_nproma = __CG_global_data__m_nproma;
                int _out_bitwidth_check_done;
                int _out_bitwidth_scalar;

                ///////////////////

                if (_in___CG_global_data__m_nproma <= static_cast<int>(std::numeric_limits<uint16_t>::max())){
                    _out_bitwidth_scalar = 16;
                } else {
                    _out_bitwidth_scalar = 32;
                }
                _out_bitwidth_check_done = 1;
                #if defined(DACE_VELOCITY_DEBUG)
                printf("Bitwidth for __CG_global_data__m_nproma: %d bits\n", _out_bitwidth_scalar);
                #endif

                ///////////////////

                __state->__0_bitwidth_check_done = _out_bitwidth_check_done;
                __state->__0_bitwidth_scalar = _out_bitwidth_scalar;
            }

        }
        bitwidth_sym = __state->__0_bitwidth_scalar;
        if ((bitwidth_sym == 16)) {
            {

                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_edge_idx_to_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16_0_0_4_0_0(__state, gpu___CG_p_patch__CG_cells__m_edge_idx, __state->__0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2, __f2dace_SA_edge_idx_d_2_s_cells_p_patch_2);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_cell_idx_to_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16_0_0_4_0_5(__state, gpu___CG_p_patch__CG_verts__m_cell_idx, __state->__0_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5, __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5, __f2dace_SA_cell_idx_d_2_s_verts_p_patch_5);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_cells__m_neighbor_idx_to_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16_0_0_4_0_10(__state, gpu___CG_p_patch__CG_cells__m_neighbor_idx, __state->__0_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2, __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2, __f2dace_SA_neighbor_idx_d_2_s_cells_p_patch_2);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_verts__m_edge_idx_to_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16_0_0_4_0_15(__state, gpu___CG_p_patch__CG_verts__m_edge_idx, __state->__0_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5, __f2dace_SA_edge_idx_d_2_s_verts_p_patch_5);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_cell_idx_to_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16_0_0_4_0_20(__state, gpu___CG_p_patch__CG_edges__m_cell_idx, __state->__0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4, __f2dace_SA_cell_idx_d_2_s_edges_p_patch_4);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_vertex_idx_to_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16_0_0_4_0_25(__state, gpu___CG_p_patch__CG_edges__m_vertex_idx, __state->__0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4, __f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4);
                __dace_runkernel_copy_map_gpu___CG_p_patch__CG_edges__m_quad_idx_to_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16_0_0_4_0_30(__state, gpu___CG_p_patch__CG_edges__m_quad_idx, __state->__0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4, __f2dace_SA_quad_idx_d_2_s_edges_p_patch_4);
//                DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


            }
        } else if (((bitwidth_sym == 32) || (bitwidth_sym == 64))) {

        }
    }
    bitwidth_sym = __state->__0_bitwidth_scalar;

    if ((bitwidth_sym == 16)) {
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
                for (auto _for_it_0_0_0 = i_startblk_var_140_0; _for_it_0_0_0 < (i_endblk_var_141_0 + 1); _for_it_0_0_0 += 1) {
                    loop_body_7_0_5(__state, __CG_global_data__m_nproma, &gpu___CG_p_int__m_cells_aw_verts[0], &__state->__0_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_w_v[0], _for_it_0_0_0, i_endblk_var_141_0, i_endidx_in_var_143_0, i_startblk_var_140_0, i_startidx_in_var_142_0, tmp_struct_symbol_6);
                }
            }
            {
                for (auto _for_it_3_0 = i_startblk_var_118_0; _for_it_3_0 < (i_endblk_var_119_0 + 1); _for_it_3_0 += 1) {
                    loop_body_7_0_13(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_verts__m_end_index[0], &__CG_p_patch__CG_verts__m_start_index[0], &gpu___CG_p_int__m_geofac_rot[0], &__state->__0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[0], &__state->__0_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_zeta[0], _for_it_3_0, i_endblk_var_119_0, i_startblk_var_118_0, tmp_struct_symbol_8);
                }
            }
            {
                for (auto _for_it_6 = i_startblk_var_146; _for_it_6 < (i_endblk_var_147 + 1); _for_it_6 += 1) {
                    loop_body_7_0_23(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_int__m_rbf_vec_coeff_e[0], &gpu___CG_p_metrics__m_ddxn_z_full[0], &gpu___CG_p_metrics__m_ddxt_z_full[0], &gpu___CG_p_metrics__m_wgtfac_e[0], &gpu___CG_p_metrics__m_wgtfacq_e[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &z_kin_hor_e[0], &z_vt_ie[0], &z_w_concorr_me[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, _for_it_6, i_endblk_var_147, i_startblk_var_146, nflatlev_jg);
                }
            }
            {
                for (auto _for_it_16 = replaced_var_1; _for_it_16 < (replaced_var_0 + 1); _for_it_16 += 1) {
                    loop_body_7_0_41(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_diag__m_vn_ie[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_w_v[0], &z_vt_ie[0], &__state->__0_gpu_z_v_grad_w[0], __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, _for_it_16, replaced_var_0, replaced_var_0, replaced_var_1, tmp_struct_symbol_4, tmp_struct_symbol_6);
                }
            }
            {
                for (auto _for_it_22 = replaced_var_3; _for_it_22 < (replaced_var_2 + 1); _for_it_22 += 1) {
                    loop_body_7_0_50(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_cells__m_end_index[0], &__CG_p_patch__CG_cells__m_start_index[0], cfl_w_limit, dtime, &gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_int__m_geofac_n2s[0], &gpu___CG_p_metrics__m_coeff1_dwdz[0], &gpu___CG_p_metrics__m_coeff2_dwdz[0], &gpu___CG_p_metrics__m_ddqz_z_half[0], &gpu___CG_p_metrics__m_wgtfac_c[0], &gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask[0], &gpu___CG_p_patch__CG_cells__m_area[0], &__state->__0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &__state->__0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16[0], &__state->__0_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_v_grad_w[0], scalfac_exdiff, &z_kin_hor_e[0], &z_w_concorr_me[0], &gpu___CG_p_diag__m_ddt_w_adv_pc[0], &gpu___CG_p_diag__m_w_concorr_c[0], &__state->__0_gpu_cfl_clipping[0], &__state->__0_gpu_levmask[0], &__state->__0_gpu_maxvcfl_arr[0], &__state->__0_gpu_vcflmax[0], &__state->__0_gpu_z_ekinh[0], &__state->__0_gpu_z_w_con_c[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_z_w_concorr_mc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, _for_it_22, i_endblk_2, replaced_var_2, i_startblk_2, replaced_var_3, nflatlev_jg, nrdmax_jg, ntnd, tmp_struct_symbol_0, tmp_struct_symbol_1, tmp_struct_symbol_10, tmp_struct_symbol_14, tmp_struct_symbol_2, tmp_struct_symbol_4);
                }
            }
            DACE_GPU_CHECK(cudaMemcpyAsync(__state->__0_vcflmax, __state->__0_gpu_vcflmax, tmp_struct_symbol_12 * sizeof(double), cudaMemcpyDeviceToHost, nullptr));
            __dace_runkernel_single_state_body_0_map_0_0_7_0_79(__state, __state->__0_gpu_levelmask, __state->__0_gpu_levmask, loop_body_reduce_scan_size, nrdmax_jg, replaced_var_2, replaced_var_3, tmp_struct_symbol_13);
//            cudaEventRecord(__state->gpu_context->events[6], nullptr);
//            cudaStreamWaitEvent(nullptr, __state->gpu_context->events[6], 0);
            {
                for (auto _for_it_47 = replaced_var_5; _for_it_47 < (replaced_var_4 + 1); _for_it_47 += 1) {
                    loop_body_7_0_88(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], cfl_w_limit, dtime, &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_int__m_geofac_grdiv[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_area_edge[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_levelmask[0], &__state->__0_gpu_z_ekinh[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_zeta[0], scalfac_exdiff, &z_kin_hor_e[0], &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_47, replaced_var_4, nrdmax_jg, ntnd, replaced_var_4, replaced_var_5, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
//            DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


        }
    } else if (((bitwidth_sym == 32) || (bitwidth_sym == 64))) {
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
                for (auto _for_it_0_0_0 = i_startblk_var_140_0; _for_it_0_0_0 < (i_endblk_var_141_0 + 1); _for_it_0_0_0 += 1) {
                    loop_body_78_0_5(__state, __CG_global_data__m_nproma, &gpu___CG_p_int__m_cells_aw_verts[0], &gpu___CG_p_patch__CG_verts__m_cell_idx[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_w_v[0], _for_it_0_0_0, i_endblk_var_141_0, i_endidx_in_var_143_0, i_startblk_var_140_0, i_startidx_in_var_142_0, tmp_struct_symbol_6);
                }
            }
            {
                for (auto _for_it_3_0 = i_startblk_var_118_0; _for_it_3_0 < (i_endblk_var_119_0 + 1); _for_it_3_0 += 1) {
                    loop_body_78_0_13(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_verts__m_end_index[0], &__CG_p_patch__CG_verts__m_start_index[0], &gpu___CG_p_int__m_geofac_rot[0], &__state->__0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_verts__m_edge_idx[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_zeta[0], _for_it_3_0, i_endblk_var_119_0, i_startblk_var_118_0, tmp_struct_symbol_8);
                }
            }
            {
                for (auto _for_it_6 = i_startblk_var_146; _for_it_6 < (i_endblk_var_147 + 1); _for_it_6 += 1) {
                    loop_body_78_0_23(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_int__m_rbf_vec_coeff_e[0], &gpu___CG_p_metrics__m_ddxn_z_full[0], &gpu___CG_p_metrics__m_ddxt_z_full[0], &gpu___CG_p_metrics__m_wgtfac_e[0], &gpu___CG_p_metrics__m_wgtfacq_e[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &gpu___CG_p_prog__m_vn[0], &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &z_kin_hor_e[0], &z_vt_ie[0], &z_w_concorr_me[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, _for_it_6, i_endblk_var_147, i_startblk_var_146, nflatlev_jg);
                }
            }
            {
                for (auto _for_it_16 = replaced_var_1; _for_it_16 < (replaced_var_0 + 1); _for_it_16 += 1) {
                    loop_body_78_0_41(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_w_v[0], &z_vt_ie[0], &__state->__0_gpu_z_v_grad_w[0], __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, _for_it_16, replaced_var_0, replaced_var_0, replaced_var_1, tmp_struct_symbol_4, tmp_struct_symbol_6);
                }
            }
            {
                for (auto _for_it_22 = replaced_var_3; _for_it_22 < (replaced_var_2 + 1); _for_it_22 += 1) {
                    loop_body_78_0_50(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_cells__m_end_index[0], &__CG_p_patch__CG_cells__m_start_index[0], cfl_w_limit, dtime, &gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_int__m_geofac_n2s[0], &gpu___CG_p_metrics__m_coeff1_dwdz[0], &gpu___CG_p_metrics__m_coeff2_dwdz[0], &gpu___CG_p_metrics__m_ddqz_z_half[0], &gpu___CG_p_metrics__m_wgtfac_c[0], &gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask[0], &gpu___CG_p_patch__CG_cells__m_area[0], &__state->__0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &gpu___CG_p_patch__CG_cells__m_neighbor_idx[0], &gpu___CG_p_prog__m_w[0], &__state->__0_gpu_z_v_grad_w[0], scalfac_exdiff, &z_kin_hor_e[0], &z_w_concorr_me[0], &gpu___CG_p_diag__m_ddt_w_adv_pc[0], &gpu___CG_p_diag__m_w_concorr_c[0], &__state->__0_gpu_cfl_clipping[0], &__state->__0_gpu_levmask[0], &__state->__0_gpu_maxvcfl_arr[0], &__state->__0_gpu_vcflmax[0], &__state->__0_gpu_z_ekinh[0], &__state->__0_gpu_z_w_con_c[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_z_w_concorr_mc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, _for_it_22, i_endblk_2, replaced_var_2, i_startblk_2, replaced_var_3, nflatlev_jg, nrdmax_jg, ntnd, tmp_struct_symbol_0, tmp_struct_symbol_1, tmp_struct_symbol_10, tmp_struct_symbol_14, tmp_struct_symbol_2, tmp_struct_symbol_4);
                }
            }
            DACE_GPU_CHECK(cudaMemcpyAsync(__state->__0_vcflmax, __state->__0_gpu_vcflmax, tmp_struct_symbol_12 * sizeof(double), cudaMemcpyDeviceToHost, nullptr));
            __dace_runkernel_single_state_body_0_map_0_0_78_0_79(__state, __state->__0_gpu_levelmask, __state->__0_gpu_levmask, loop_body_reduce_scan_size, nrdmax_jg, replaced_var_2, replaced_var_3, tmp_struct_symbol_13);
//            cudaEventRecord(__state->gpu_context->events[6], nullptr);
//            cudaStreamWaitEvent(nullptr, __state->gpu_context->events[6], 0);
            {
                for (auto _for_it_47 = replaced_var_5; _for_it_47 < (replaced_var_4 + 1); _for_it_47 += 1) {
                    loop_body_78_0_88(__state, __CG_global_data__m_nproma, &__CG_p_patch__CG_edges__m_end_index[0], &__CG_p_patch__CG_edges__m_start_index[0], cfl_w_limit, dtime, &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_int__m_geofac_grdiv[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_area_edge[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_levelmask[0], &__state->__0_gpu_z_ekinh[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_zeta[0], scalfac_exdiff, &z_kin_hor_e[0], &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, _for_it_47, replaced_var_4, nrdmax_jg, ntnd, replaced_var_4, replaced_var_5, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
//            DACE_GPU_CHECK(cudaStreamSynchronize(nullptr));


        }
    }
    replaced_var_6 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_cells_p_patch_2)];
    replaced_var_7 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_cells_p_patch_2) - 4)];
    bitwidth_check_done_sym = __state->__0_bitwidth_check_done;

    {
        double max_vcfl_dyn_var_152;
        int reduce_maxZ_to_scalar_size;
        double tmp_call_18;

        {
            int size;

            ///////////////////
            // Tasklet code (size_reduce_maxZ_to_scalar)
            size = ((replaced_var_7 + 1) - replaced_var_6);
            ///////////////////

            reduce_maxZ_to_scalar_size = size;
        }
        {
            double* in_arr = &__state->__0_vcflmax[(replaced_var_6 - 1)];
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

            tmp_call_18 = out;
        }
        {
            double __in_tmp_call_18 = tmp_call_18;
            double max_vcfl_dyn_var_152_out;

            ///////////////////
            // Tasklet code (T_l652_c652)
            max_vcfl_dyn_var_152_out = __in_tmp_call_18;
            ///////////////////

            max_vcfl_dyn_var_152 = max_vcfl_dyn_var_152_out;
        }
        {
            double max_vcfl_dyn_var_152_0_in = max_vcfl_dyn_var_152;
            double p_diag_out_max_vcfl_dyn;

            ///////////////////
            // Tasklet code (T_l653_c653)
            p_diag_out_max_vcfl_dyn = max_vcfl_dyn_var_152_0_in;
            ///////////////////

            __CG_p_diag__m_max_vcfl_dyn = p_diag_out_max_vcfl_dyn;
        }

    }

    {

        {

            ///////////////////
            dace_wait_device();
            ///////////////////

        }

    }

}

DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_n2s, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1_internal(__state, __CG_global_data__m_nflatlev, __CG_global_data__m_nrdmax, __CG_p_patch__CG_cells__m_end_block, __CG_p_patch__CG_cells__m_end_index, __CG_p_patch__CG_cells__m_start_block, __CG_p_patch__CG_cells__m_start_index, __CG_p_patch__CG_edges__m_end_block, __CG_p_patch__CG_edges__m_end_index, __CG_p_patch__CG_edges__m_start_block, __CG_p_patch__CG_edges__m_start_index, __CG_p_patch__CG_verts__m_end_block, __CG_p_patch__CG_verts__m_end_index, __CG_p_patch__CG_verts__m_start_block, __CG_p_patch__CG_verts__m_start_index, global_data, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_diag__m_w_concorr_c, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_int__m_cells_aw_verts, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_int__m_geofac_grdiv, gpu___CG_p_int__m_geofac_n2s, gpu___CG_p_int__m_geofac_rot, gpu___CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_metrics__m_coeff1_dwdz, gpu___CG_p_metrics__m_coeff2_dwdz, gpu___CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_metrics__m_ddqz_z_half, gpu___CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxt_z_full, gpu___CG_p_metrics__m_wgtfac_c, gpu___CG_p_metrics__m_wgtfac_e, gpu___CG_p_metrics__m_wgtfacq_e, gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, gpu___CG_p_patch__CG_cells__m_area, gpu___CG_p_patch__CG_cells__m_edge_blk, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu___CG_p_patch__CG_cells__m_neighbor_blk, gpu___CG_p_patch__CG_cells__m_neighbor_idx, gpu___CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_cell_blk, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_quad_blk, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_blk, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_patch__CG_verts__m_cell_blk, gpu___CG_p_patch__CG_verts__m_cell_idx, gpu___CG_p_patch__CG_verts__m_edge_blk, gpu___CG_p_patch__CG_verts__m_edge_idx, gpu___CG_p_prog__m_vn, gpu___CG_p_prog__m_w, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __CG_global_data__m_nproma, __CG_p_diag__m_max_vcfl_dyn, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}
DACE_EXPORTED int __dace_init_cuda_0(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state, int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_n2s, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_cuda_0(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state);

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(int * __restrict__ __CG_global_data__m_nflatlev, int * __restrict__ __CG_global_data__m_nrdmax, int * __restrict__ __CG_p_patch__CG_cells__m_end_block, int * __restrict__ __CG_p_patch__CG_cells__m_end_index, int * __restrict__ __CG_p_patch__CG_cells__m_start_block, int * __restrict__ __CG_p_patch__CG_cells__m_start_index, int * __restrict__ __CG_p_patch__CG_edges__m_end_block, int * __restrict__ __CG_p_patch__CG_edges__m_end_index, int * __restrict__ __CG_p_patch__CG_edges__m_start_block, int * __restrict__ __CG_p_patch__CG_edges__m_start_index, int * __restrict__ __CG_p_patch__CG_verts__m_end_block, int * __restrict__ __CG_p_patch__CG_verts__m_end_index, int * __restrict__ __CG_p_patch__CG_verts__m_start_block, int * __restrict__ __CG_p_patch__CG_verts__m_start_index, global_data_type* global_data, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_int__m_geofac_n2s, double * __restrict__ gpu___CG_p_int__m_geofac_rot, double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, int * __restrict__ gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, double * __restrict__ gpu___CG_p_patch__CG_cells__m_area, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_neighbor_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_prog__m_w, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __CG_global_data__m_nproma, double &__CG_p_diag__m_max_vcfl_dyn, int __f2dace_A_z_kin_hor_e_d_0_s, int __f2dace_A_z_kin_hor_e_d_1_s, int __f2dace_A_z_vt_ie_d_0_s, int __f2dace_A_z_vt_ie_d_1_s, int __f2dace_A_z_w_concorr_me_d_0_s, int __f2dace_A_z_w_concorr_me_d_1_s, int __f2dace_OA_z_kin_hor_e_d_0_s, int __f2dace_OA_z_kin_hor_e_d_1_s, int __f2dace_OA_z_kin_hor_e_d_2_s, int __f2dace_OA_z_vt_ie_d_0_s, int __f2dace_OA_z_vt_ie_d_1_s, int __f2dace_OA_z_vt_ie_d_2_s, int __f2dace_OA_z_w_concorr_me_d_0_s, int __f2dace_OA_z_w_concorr_me_d_1_s, int __f2dace_OA_z_w_concorr_me_d_2_s, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state = new velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t;


    __result |= __dace_init_cuda_0(__state, __CG_global_data__m_nflatlev, __CG_global_data__m_nrdmax, __CG_p_patch__CG_cells__m_end_block, __CG_p_patch__CG_cells__m_end_index, __CG_p_patch__CG_cells__m_start_block, __CG_p_patch__CG_cells__m_start_index, __CG_p_patch__CG_edges__m_end_block, __CG_p_patch__CG_edges__m_end_index, __CG_p_patch__CG_edges__m_start_block, __CG_p_patch__CG_edges__m_start_index, __CG_p_patch__CG_verts__m_end_block, __CG_p_patch__CG_verts__m_end_index, __CG_p_patch__CG_verts__m_start_block, __CG_p_patch__CG_verts__m_start_index, global_data, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_ddt_w_adv_pc, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_diag__m_w_concorr_c, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_int__m_cells_aw_verts, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_int__m_geofac_grdiv, gpu___CG_p_int__m_geofac_n2s, gpu___CG_p_int__m_geofac_rot, gpu___CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_metrics__m_coeff1_dwdz, gpu___CG_p_metrics__m_coeff2_dwdz, gpu___CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_metrics__m_ddqz_z_half, gpu___CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxt_z_full, gpu___CG_p_metrics__m_wgtfac_c, gpu___CG_p_metrics__m_wgtfac_e, gpu___CG_p_metrics__m_wgtfacq_e, gpu___CG_p_patch__CG_cells__CG_decomp_info__m_owner_mask, gpu___CG_p_patch__CG_cells__m_area, gpu___CG_p_patch__CG_cells__m_edge_blk, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu___CG_p_patch__CG_cells__m_neighbor_blk, gpu___CG_p_patch__CG_cells__m_neighbor_idx, gpu___CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_cell_blk, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_quad_blk, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_blk, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_patch__CG_verts__m_cell_blk, gpu___CG_p_patch__CG_verts__m_cell_idx, gpu___CG_p_patch__CG_verts__m_edge_blk, gpu___CG_p_patch__CG_verts__m_edge_idx, gpu___CG_p_prog__m_vn, gpu___CG_p_prog__m_w, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __CG_global_data__m_nproma, __CG_p_diag__m_max_vcfl_dyn, __f2dace_A_z_kin_hor_e_d_0_s, __f2dace_A_z_kin_hor_e_d_1_s, __f2dace_A_z_vt_ie_d_0_s, __f2dace_A_z_vt_ie_d_1_s, __f2dace_A_z_w_concorr_me_d_0_s, __f2dace_A_z_w_concorr_me_d_1_s, __f2dace_OA_z_kin_hor_e_d_0_s, __f2dace_OA_z_kin_hor_e_d_1_s, __f2dace_OA_z_kin_hor_e_d_2_s, __f2dace_OA_z_vt_ie_d_0_s, __f2dace_OA_z_vt_ie_d_1_s, __f2dace_OA_z_vt_ie_d_2_s, __f2dace_OA_z_w_concorr_me_d_0_s, __f2dace_OA_z_w_concorr_me_d_1_s, __f2dace_OA_z_w_concorr_me_d_2_s, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
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
    __state->__0_bitwidth_check_done = 0;
    __state->__0_bitwidth_scalar = -1;
    __state->__0_nblk_lowering_done = 0;
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_con_c, (91 * tmp_struct_symbol_1) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_cfl_clipping, (91 * tmp_struct_symbol_14) * sizeof(uint8_t)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_v_grad_w, (((90 * tmp_struct_symbol_4) * (tmp_struct_symbol_5 - 1)) + (90 * tmp_struct_symbol_4)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_zeta, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_maxvcfl_arr, (((88 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (88 * tmp_struct_symbol_4)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMemset(__state->__0_gpu_maxvcfl_arr, 0, (((88 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (88 * tmp_struct_symbol_4)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_ekinh, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_concorr_mc, (90 * tmp_struct_symbol_0) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_levelmask, 90 * sizeof(uint8_t)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_v, (((91 * tmp_struct_symbol_6) * (tmp_struct_symbol_7 - 1)) + (91 * tmp_struct_symbol_6)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_levmask, (90 * tmp_struct_symbol_13) * sizeof(uint8_t)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_con_c_full, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_vcflmax, tmp_struct_symbol_12 * sizeof(double)));
    __state->__0_vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_12];
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16, ((((__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_cells_p_patch_2) * (__f2dace_SA_edge_idx_d_2_s_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_idx_d_0_s_cells_p_patch_2 * (__f2dace_SA_edge_idx_d_1_s_cells_p_patch_2 - 1))) + __f2dace_SA_edge_idx_d_0_s_cells_p_patch_2) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16, ((((__f2dace_SA_cell_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_verts_p_patch_5) * (__f2dace_SA_cell_idx_d_2_s_verts_p_patch_5 - 1)) + (__f2dace_SA_cell_idx_d_0_s_verts_p_patch_5 * (__f2dace_SA_cell_idx_d_1_s_verts_p_patch_5 - 1))) + __f2dace_SA_cell_idx_d_0_s_verts_p_patch_5) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16, ((((__f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2) * (__f2dace_SA_neighbor_idx_d_2_s_cells_p_patch_2 - 1)) + (__f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2 * (__f2dace_SA_neighbor_idx_d_1_s_cells_p_patch_2 - 1))) + __f2dace_SA_neighbor_idx_d_0_s_cells_p_patch_2) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16, ((((__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_verts_p_patch_5) * (__f2dace_SA_edge_idx_d_2_s_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_idx_d_0_s_verts_p_patch_5 * (__f2dace_SA_edge_idx_d_1_s_verts_p_patch_5 - 1))) + __f2dace_SA_edge_idx_d_0_s_verts_p_patch_5) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16, ((((__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_cell_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_cell_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_cell_idx_d_0_s_edges_p_patch_4) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16, ((((__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_vertex_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_vertex_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_idx_d_0_s_edges_p_patch_4) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16, ((((__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_edges_p_patch_4) * (__f2dace_SA_quad_idx_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_idx_d_0_s_edges_p_patch_4 * (__f2dace_SA_quad_idx_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_quad_idx_d_0_s_edges_p_patch_4) * sizeof(uint16_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8, ((((__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_cells_p_patch_2) * (__f2dace_SA_edge_blk_d_2_s_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_blk_d_0_s_cells_p_patch_2 * (__f2dace_SA_edge_blk_d_1_s_cells_p_patch_2 - 1))) + __f2dace_SA_edge_blk_d_0_s_cells_p_patch_2) * sizeof(uint8_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8, ((((__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_edges_p_patch_4) * (__f2dace_SA_quad_blk_d_2_s_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_blk_d_0_s_edges_p_patch_4 * (__f2dace_SA_quad_blk_d_1_s_edges_p_patch_4 - 1))) + __f2dace_SA_quad_blk_d_0_s_edges_p_patch_4) * sizeof(uint8_t)));
    //DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8, ((((__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_verts_p_patch_5) * (__f2dace_SA_edge_blk_d_2_s_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_blk_d_0_s_verts_p_patch_5 * (__f2dace_SA_edge_blk_d_1_s_verts_p_patch_5 - 1))) + __f2dace_SA_edge_blk_d_0_s_verts_p_patch_5) * sizeof(uint8_t)));

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *__state)
{
cleanup_reduce_sum_gpu();
cleanup_reduce_maxZ_gpu();
    int __err = 0;
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_con_c));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_cfl_clipping));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_v_grad_w));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_zeta));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_maxvcfl_arr));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_ekinh));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_concorr_mc));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_levelmask));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_v));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_levmask));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_con_c_full));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_vcflmax));
    delete[] __state->__0_vcflmax;
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_cells__m_edge_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_verts__m_cell_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_cells__m_neighbor_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_verts__m_edge_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_edges__m_cell_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_edges__m_vertex_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_edges__m_quad_idx_uint16));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_cells__m_edge_blk_uint8));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_edges__m_quad_blk_uint8));
    //DACE_GPU_CHECK(cudaFree(__state->__0_gpu___CG_p_patch__CG_verts__m_edge_blk_uint8));

    int __err_cuda = __dace_exit_cuda_0(__state);
    if (__err_cuda) {
        __err = __err_cuda;
    }
    delete __state;
    return __err;
}
