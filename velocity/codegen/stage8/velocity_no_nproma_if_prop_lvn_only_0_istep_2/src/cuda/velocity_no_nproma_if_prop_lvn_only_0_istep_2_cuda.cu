#include "reductions_device.cuh"
#define __REDUCE_DEVICE__

#include <cuda_runtime.h>
#include <dace/dace.h>


struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s_288 = {};
    int __f2dace_SA_vn_d_1_s_289 = {};
    int __f2dace_SA_vn_d_2_s_290 = {};
    int __f2dace_SA_w_d_0_s_285 = {};
    int __f2dace_SA_w_d_1_s_286 = {};
    int __f2dace_SA_w_d_2_s_287 = {};
    int __f2dace_SOA_vn_d_0_s_288 = {};
    int __f2dace_SOA_vn_d_1_s_289 = {};
    int __f2dace_SOA_vn_d_2_s_290 = {};
    int __f2dace_SOA_w_d_0_s_285 = {};
    int __f2dace_SOA_w_d_1_s_286 = {};
    int __f2dace_SOA_w_d_2_s_287 = {};
    double* vn = {};
    double* w = {};
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

struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_1_s_301 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_3_s_303 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_0_s_304 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_1_s_305 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_2_s_306 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_3_s_307 = {};
    int __f2dace_SA_vn_ie_d_0_s_294 = {};
    int __f2dace_SA_vn_ie_d_1_s_295 = {};
    int __f2dace_SA_vn_ie_d_2_s_296 = {};
    int __f2dace_SA_vt_d_0_s_291 = {};
    int __f2dace_SA_vt_d_1_s_292 = {};
    int __f2dace_SA_vt_d_2_s_293 = {};
    int __f2dace_SA_w_concorr_c_d_0_s_297 = {};
    int __f2dace_SA_w_concorr_c_d_1_s_298 = {};
    int __f2dace_SA_w_concorr_c_d_2_s_299 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307 = {};
    int __f2dace_SOA_vn_ie_d_0_s_294 = {};
    int __f2dace_SOA_vn_ie_d_1_s_295 = {};
    int __f2dace_SOA_vn_ie_d_2_s_296 = {};
    int __f2dace_SOA_vt_d_0_s_291 = {};
    int __f2dace_SOA_vt_d_1_s_292 = {};
    int __f2dace_SOA_vt_d_2_s_293 = {};
    int __f2dace_SOA_w_concorr_c_d_0_s_297 = {};
    int __f2dace_SOA_w_concorr_c_d_1_s_298 = {};
    int __f2dace_SOA_w_concorr_c_d_2_s_299 = {};
    double* ddt_vn_apc_pc = {};
    double* ddt_w_adv_pc = {};
    double max_vcfl_dyn = {};
    double* vn_ie = {};
    double* vt = {};
    double* w_concorr_c = {};
};

struct t_int_state {
    int __f2dace_SA_c_lin_e_d_0_s_25 = {};
    int __f2dace_SA_c_lin_e_d_1_s_26 = {};
    int __f2dace_SA_c_lin_e_d_2_s_27 = {};
    int __f2dace_SA_cells_aw_verts_d_0_s_31 = {};
    int __f2dace_SA_cells_aw_verts_d_1_s_32 = {};
    int __f2dace_SA_cells_aw_verts_d_2_s_33 = {};
    int __f2dace_SA_e_bln_c_s_d_0_s_28 = {};
    int __f2dace_SA_e_bln_c_s_d_1_s_29 = {};
    int __f2dace_SA_e_bln_c_s_d_2_s_30 = {};
    int __f2dace_SA_geofac_grdiv_d_0_s_37 = {};
    int __f2dace_SA_geofac_grdiv_d_1_s_38 = {};
    int __f2dace_SA_geofac_grdiv_d_2_s_39 = {};
    int __f2dace_SA_geofac_n2s_d_0_s_43 = {};
    int __f2dace_SA_geofac_n2s_d_1_s_44 = {};
    int __f2dace_SA_geofac_n2s_d_2_s_45 = {};
    int __f2dace_SA_geofac_rot_d_0_s_40 = {};
    int __f2dace_SA_geofac_rot_d_1_s_41 = {};
    int __f2dace_SA_geofac_rot_d_2_s_42 = {};
    int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34 = {};
    int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35 = {};
    int __f2dace_SA_rbf_vec_coeff_e_d_2_s_36 = {};
    int __f2dace_SOA_c_lin_e_d_0_s_25 = {};
    int __f2dace_SOA_c_lin_e_d_1_s_26 = {};
    int __f2dace_SOA_c_lin_e_d_2_s_27 = {};
    int __f2dace_SOA_cells_aw_verts_d_0_s_31 = {};
    int __f2dace_SOA_cells_aw_verts_d_1_s_32 = {};
    int __f2dace_SOA_cells_aw_verts_d_2_s_33 = {};
    int __f2dace_SOA_e_bln_c_s_d_0_s_28 = {};
    int __f2dace_SOA_e_bln_c_s_d_1_s_29 = {};
    int __f2dace_SOA_e_bln_c_s_d_2_s_30 = {};
    int __f2dace_SOA_geofac_grdiv_d_0_s_37 = {};
    int __f2dace_SOA_geofac_grdiv_d_1_s_38 = {};
    int __f2dace_SOA_geofac_grdiv_d_2_s_39 = {};
    int __f2dace_SOA_geofac_n2s_d_0_s_43 = {};
    int __f2dace_SOA_geofac_n2s_d_1_s_44 = {};
    int __f2dace_SOA_geofac_n2s_d_2_s_45 = {};
    int __f2dace_SOA_geofac_rot_d_0_s_40 = {};
    int __f2dace_SOA_geofac_rot_d_1_s_41 = {};
    int __f2dace_SOA_geofac_rot_d_2_s_42 = {};
    int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34 = {};
    int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35 = {};
    int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36 = {};
    double* c_lin_e = {};
    double* cells_aw_verts = {};
    double* e_bln_c_s = {};
    double* geofac_grdiv = {};
    double* geofac_n2s = {};
    double* geofac_rot = {};
    double* rbf_vec_coeff_e = {};
};

struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s_332 = {};
    int __f2dace_SA_coeff1_dwdz_d_1_s_333 = {};
    int __f2dace_SA_coeff1_dwdz_d_2_s_334 = {};
    int __f2dace_SA_coeff2_dwdz_d_0_s_335 = {};
    int __f2dace_SA_coeff2_dwdz_d_1_s_336 = {};
    int __f2dace_SA_coeff2_dwdz_d_2_s_337 = {};
    int __f2dace_SA_coeff_gradekin_d_0_s_329 = {};
    int __f2dace_SA_coeff_gradekin_d_1_s_330 = {};
    int __f2dace_SA_coeff_gradekin_d_2_s_331 = {};
    int __f2dace_SA_ddqz_z_full_e_d_0_s_314 = {};
    int __f2dace_SA_ddqz_z_full_e_d_1_s_315 = {};
    int __f2dace_SA_ddqz_z_full_e_d_2_s_316 = {};
    int __f2dace_SA_ddqz_z_half_d_0_s_317 = {};
    int __f2dace_SA_ddqz_z_half_d_1_s_318 = {};
    int __f2dace_SA_ddqz_z_half_d_2_s_319 = {};
    int __f2dace_SA_ddxn_z_full_d_0_s_308 = {};
    int __f2dace_SA_ddxn_z_full_d_1_s_309 = {};
    int __f2dace_SA_ddxn_z_full_d_2_s_310 = {};
    int __f2dace_SA_ddxt_z_full_d_0_s_311 = {};
    int __f2dace_SA_ddxt_z_full_d_1_s_312 = {};
    int __f2dace_SA_ddxt_z_full_d_2_s_313 = {};
    int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_340 = {};
    int __f2dace_SA_deepatmo_gradh_mc_d_0_s_338 = {};
    int __f2dace_SA_deepatmo_invr_ifc_d_0_s_341 = {};
    int __f2dace_SA_deepatmo_invr_mc_d_0_s_339 = {};
    int __f2dace_SA_wgtfac_c_d_0_s_320 = {};
    int __f2dace_SA_wgtfac_c_d_1_s_321 = {};
    int __f2dace_SA_wgtfac_c_d_2_s_322 = {};
    int __f2dace_SA_wgtfac_e_d_0_s_323 = {};
    int __f2dace_SA_wgtfac_e_d_1_s_324 = {};
    int __f2dace_SA_wgtfac_e_d_2_s_325 = {};
    int __f2dace_SA_wgtfacq_e_d_0_s_326 = {};
    int __f2dace_SA_wgtfacq_e_d_1_s_327 = {};
    int __f2dace_SA_wgtfacq_e_d_2_s_328 = {};
    int __f2dace_SOA_coeff1_dwdz_d_0_s_332 = {};
    int __f2dace_SOA_coeff1_dwdz_d_1_s_333 = {};
    int __f2dace_SOA_coeff1_dwdz_d_2_s_334 = {};
    int __f2dace_SOA_coeff2_dwdz_d_0_s_335 = {};
    int __f2dace_SOA_coeff2_dwdz_d_1_s_336 = {};
    int __f2dace_SOA_coeff2_dwdz_d_2_s_337 = {};
    int __f2dace_SOA_coeff_gradekin_d_0_s_329 = {};
    int __f2dace_SOA_coeff_gradekin_d_1_s_330 = {};
    int __f2dace_SOA_coeff_gradekin_d_2_s_331 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_0_s_314 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_1_s_315 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_2_s_316 = {};
    int __f2dace_SOA_ddqz_z_half_d_0_s_317 = {};
    int __f2dace_SOA_ddqz_z_half_d_1_s_318 = {};
    int __f2dace_SOA_ddqz_z_half_d_2_s_319 = {};
    int __f2dace_SOA_ddxn_z_full_d_0_s_308 = {};
    int __f2dace_SOA_ddxn_z_full_d_1_s_309 = {};
    int __f2dace_SOA_ddxn_z_full_d_2_s_310 = {};
    int __f2dace_SOA_ddxt_z_full_d_0_s_311 = {};
    int __f2dace_SOA_ddxt_z_full_d_1_s_312 = {};
    int __f2dace_SOA_ddxt_z_full_d_2_s_313 = {};
    int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_340 = {};
    int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_338 = {};
    int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_341 = {};
    int __f2dace_SOA_deepatmo_invr_mc_d_0_s_339 = {};
    int __f2dace_SOA_wgtfac_c_d_0_s_320 = {};
    int __f2dace_SOA_wgtfac_c_d_1_s_321 = {};
    int __f2dace_SOA_wgtfac_c_d_2_s_322 = {};
    int __f2dace_SOA_wgtfac_e_d_0_s_323 = {};
    int __f2dace_SOA_wgtfac_e_d_1_s_324 = {};
    int __f2dace_SOA_wgtfac_e_d_2_s_325 = {};
    int __f2dace_SOA_wgtfacq_e_d_0_s_326 = {};
    int __f2dace_SOA_wgtfacq_e_d_1_s_327 = {};
    int __f2dace_SOA_wgtfacq_e_d_2_s_328 = {};
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
    int __f2dace_SA_owner_mask_d_0_s_2 = {};
    int __f2dace_SA_owner_mask_d_1_s_3 = {};
    int __f2dace_SOA_owner_mask_d_0_s_2 = {};
    int __f2dace_SOA_owner_mask_d_1_s_3 = {};
    int* owner_mask = {};
};

struct t_grid_cells {
    int __f2dace_SA_area_d_0_s_158 = {};
    int __f2dace_SA_area_d_1_s_159 = {};
    int __f2dace_SA_edge_blk_d_0_s_155 = {};
    int __f2dace_SA_edge_blk_d_1_s_156 = {};
    int __f2dace_SA_edge_blk_d_2_s_157 = {};
    int __f2dace_SA_edge_idx_d_0_s_152 = {};
    int __f2dace_SA_edge_idx_d_1_s_153 = {};
    int __f2dace_SA_edge_idx_d_2_s_154 = {};
    int __f2dace_SA_end_block_d_0_s_163 = {};
    int __f2dace_SA_end_index_d_0_s_161 = {};
    int __f2dace_SA_neighbor_blk_d_0_s_149 = {};
    int __f2dace_SA_neighbor_blk_d_1_s_150 = {};
    int __f2dace_SA_neighbor_blk_d_2_s_151 = {};
    int __f2dace_SA_neighbor_idx_d_0_s_146 = {};
    int __f2dace_SA_neighbor_idx_d_1_s_147 = {};
    int __f2dace_SA_neighbor_idx_d_2_s_148 = {};
    int __f2dace_SA_start_block_d_0_s_162 = {};
    int __f2dace_SA_start_index_d_0_s_160 = {};
    int __f2dace_SOA_area_d_0_s_158 = {};
    int __f2dace_SOA_area_d_1_s_159 = {};
    int __f2dace_SOA_edge_blk_d_0_s_155 = {};
    int __f2dace_SOA_edge_blk_d_1_s_156 = {};
    int __f2dace_SOA_edge_blk_d_2_s_157 = {};
    int __f2dace_SOA_edge_idx_d_0_s_152 = {};
    int __f2dace_SOA_edge_idx_d_1_s_153 = {};
    int __f2dace_SOA_edge_idx_d_2_s_154 = {};
    int __f2dace_SOA_end_block_d_0_s_163 = {};
    int __f2dace_SOA_end_index_d_0_s_161 = {};
    int __f2dace_SOA_neighbor_blk_d_0_s_149 = {};
    int __f2dace_SOA_neighbor_blk_d_1_s_150 = {};
    int __f2dace_SOA_neighbor_blk_d_2_s_151 = {};
    int __f2dace_SOA_neighbor_idx_d_0_s_146 = {};
    int __f2dace_SOA_neighbor_idx_d_1_s_147 = {};
    int __f2dace_SOA_neighbor_idx_d_2_s_148 = {};
    int __f2dace_SOA_start_block_d_0_s_162 = {};
    int __f2dace_SOA_start_index_d_0_s_160 = {};
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
    int __f2dace_SA_area_edge_d_0_s_188 = {};
    int __f2dace_SA_area_edge_d_1_s_189 = {};
    int __f2dace_SA_cell_blk_d_0_s_167 = {};
    int __f2dace_SA_cell_blk_d_1_s_168 = {};
    int __f2dace_SA_cell_blk_d_2_s_169 = {};
    int __f2dace_SA_cell_idx_d_0_s_164 = {};
    int __f2dace_SA_cell_idx_d_1_s_165 = {};
    int __f2dace_SA_cell_idx_d_2_s_166 = {};
    int __f2dace_SA_end_block_d_0_s_199 = {};
    int __f2dace_SA_end_index_d_0_s_197 = {};
    int __f2dace_SA_f_e_d_0_s_190 = {};
    int __f2dace_SA_f_e_d_1_s_191 = {};
    int __f2dace_SA_fn_e_d_0_s_192 = {};
    int __f2dace_SA_fn_e_d_1_s_193 = {};
    int __f2dace_SA_ft_e_d_0_s_194 = {};
    int __f2dace_SA_ft_e_d_1_s_195 = {};
    int __f2dace_SA_inv_dual_edge_length_d_0_s_186 = {};
    int __f2dace_SA_inv_dual_edge_length_d_1_s_187 = {};
    int __f2dace_SA_inv_primal_edge_length_d_0_s_184 = {};
    int __f2dace_SA_inv_primal_edge_length_d_1_s_185 = {};
    int __f2dace_SA_quad_blk_d_0_s_181 = {};
    int __f2dace_SA_quad_blk_d_1_s_182 = {};
    int __f2dace_SA_quad_blk_d_2_s_183 = {};
    int __f2dace_SA_quad_idx_d_0_s_178 = {};
    int __f2dace_SA_quad_idx_d_1_s_179 = {};
    int __f2dace_SA_quad_idx_d_2_s_180 = {};
    int __f2dace_SA_start_block_d_0_s_198 = {};
    int __f2dace_SA_start_index_d_0_s_196 = {};
    int __f2dace_SA_tangent_orientation_d_0_s_176 = {};
    int __f2dace_SA_tangent_orientation_d_1_s_177 = {};
    int __f2dace_SA_vertex_blk_d_0_s_173 = {};
    int __f2dace_SA_vertex_blk_d_1_s_174 = {};
    int __f2dace_SA_vertex_blk_d_2_s_175 = {};
    int __f2dace_SA_vertex_idx_d_0_s_170 = {};
    int __f2dace_SA_vertex_idx_d_1_s_171 = {};
    int __f2dace_SA_vertex_idx_d_2_s_172 = {};
    int __f2dace_SOA_area_edge_d_0_s_188 = {};
    int __f2dace_SOA_area_edge_d_1_s_189 = {};
    int __f2dace_SOA_cell_blk_d_0_s_167 = {};
    int __f2dace_SOA_cell_blk_d_1_s_168 = {};
    int __f2dace_SOA_cell_blk_d_2_s_169 = {};
    int __f2dace_SOA_cell_idx_d_0_s_164 = {};
    int __f2dace_SOA_cell_idx_d_1_s_165 = {};
    int __f2dace_SOA_cell_idx_d_2_s_166 = {};
    int __f2dace_SOA_end_block_d_0_s_199 = {};
    int __f2dace_SOA_end_index_d_0_s_197 = {};
    int __f2dace_SOA_f_e_d_0_s_190 = {};
    int __f2dace_SOA_f_e_d_1_s_191 = {};
    int __f2dace_SOA_fn_e_d_0_s_192 = {};
    int __f2dace_SOA_fn_e_d_1_s_193 = {};
    int __f2dace_SOA_ft_e_d_0_s_194 = {};
    int __f2dace_SOA_ft_e_d_1_s_195 = {};
    int __f2dace_SOA_inv_dual_edge_length_d_0_s_186 = {};
    int __f2dace_SOA_inv_dual_edge_length_d_1_s_187 = {};
    int __f2dace_SOA_inv_primal_edge_length_d_0_s_184 = {};
    int __f2dace_SOA_inv_primal_edge_length_d_1_s_185 = {};
    int __f2dace_SOA_quad_blk_d_0_s_181 = {};
    int __f2dace_SOA_quad_blk_d_1_s_182 = {};
    int __f2dace_SOA_quad_blk_d_2_s_183 = {};
    int __f2dace_SOA_quad_idx_d_0_s_178 = {};
    int __f2dace_SOA_quad_idx_d_1_s_179 = {};
    int __f2dace_SOA_quad_idx_d_2_s_180 = {};
    int __f2dace_SOA_start_block_d_0_s_198 = {};
    int __f2dace_SOA_start_index_d_0_s_196 = {};
    int __f2dace_SOA_tangent_orientation_d_0_s_176 = {};
    int __f2dace_SOA_tangent_orientation_d_1_s_177 = {};
    int __f2dace_SOA_vertex_blk_d_0_s_173 = {};
    int __f2dace_SOA_vertex_blk_d_1_s_174 = {};
    int __f2dace_SOA_vertex_blk_d_2_s_175 = {};
    int __f2dace_SOA_vertex_idx_d_0_s_170 = {};
    int __f2dace_SOA_vertex_idx_d_1_s_171 = {};
    int __f2dace_SOA_vertex_idx_d_2_s_172 = {};
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
    int __f2dace_SA_cell_blk_d_0_s_203 = {};
    int __f2dace_SA_cell_blk_d_1_s_204 = {};
    int __f2dace_SA_cell_blk_d_2_s_205 = {};
    int __f2dace_SA_cell_idx_d_0_s_200 = {};
    int __f2dace_SA_cell_idx_d_1_s_201 = {};
    int __f2dace_SA_cell_idx_d_2_s_202 = {};
    int __f2dace_SA_edge_blk_d_0_s_209 = {};
    int __f2dace_SA_edge_blk_d_1_s_210 = {};
    int __f2dace_SA_edge_blk_d_2_s_211 = {};
    int __f2dace_SA_edge_idx_d_0_s_206 = {};
    int __f2dace_SA_edge_idx_d_1_s_207 = {};
    int __f2dace_SA_edge_idx_d_2_s_208 = {};
    int __f2dace_SA_end_block_d_0_s_215 = {};
    int __f2dace_SA_end_index_d_0_s_213 = {};
    int __f2dace_SA_start_block_d_0_s_214 = {};
    int __f2dace_SA_start_index_d_0_s_212 = {};
    int __f2dace_SOA_cell_blk_d_0_s_203 = {};
    int __f2dace_SOA_cell_blk_d_1_s_204 = {};
    int __f2dace_SOA_cell_blk_d_2_s_205 = {};
    int __f2dace_SOA_cell_idx_d_0_s_200 = {};
    int __f2dace_SOA_cell_idx_d_1_s_201 = {};
    int __f2dace_SOA_cell_idx_d_2_s_202 = {};
    int __f2dace_SOA_edge_blk_d_0_s_209 = {};
    int __f2dace_SOA_edge_blk_d_1_s_210 = {};
    int __f2dace_SOA_edge_blk_d_2_s_211 = {};
    int __f2dace_SOA_edge_idx_d_0_s_206 = {};
    int __f2dace_SOA_edge_idx_d_1_s_207 = {};
    int __f2dace_SOA_edge_idx_d_2_s_208 = {};
    int __f2dace_SOA_end_block_d_0_s_215 = {};
    int __f2dace_SOA_end_index_d_0_s_213 = {};
    int __f2dace_SOA_start_block_d_0_s_214 = {};
    int __f2dace_SOA_start_index_d_0_s_212 = {};
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

struct velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t {
    dace::cuda::Context *gpu_context;
    double * __restrict__ __0_gpu_zeta;
    double * __restrict__ __0_gpu_z_ekinh;
    double * __restrict__ __0_gpu_z_w_con_c;
    double * __restrict__ __0_gpu_z_w_v;
    double * __restrict__ __0_gpu_z_w_con_c_full;
    double * __restrict__ __0_gpu_z_v_grad_w;
    double * __restrict__ __0_gpu_maxvcfl_arr;
    double * __restrict__ __0_gpu_vcflmax;
    double * __restrict__ __0_vcflmax;
};



DACE_EXPORTED int __dace_init_cuda_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_area_d_0_s_158_cells_p_patch_2, int __f2dace_SA_area_d_1_s_159_cells_p_patch_2, int __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4, int __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2, int __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4, int __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5, int __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2, int __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4, int __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4, int __f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4, int __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6, int __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6, int __f2dace_SA_geofac_n2s_d_0_s_43_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6, int __f2dace_SA_geofac_n2s_d_2_s_45_p_int_6, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_2_s_151_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_2_s_148_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3, int __f2dace_SA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3, int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6, int __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2, int __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4, int __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5, int __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2, int __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4, int __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vn_d_2_s_290_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SA_vt_d_2_s_293_p_diag_9, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SA_w_d_2_s_287_p_prog_7, int __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8, int __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2, int __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4, int __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5, int __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2, int __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4, int __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2, int __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5, int __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2, int __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4, int __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_11, int tmp_struct_symbol_12, int tmp_struct_symbol_2, int tmp_struct_symbol_3, int tmp_struct_symbol_4, int tmp_struct_symbol_5, int tmp_struct_symbol_6, int tmp_struct_symbol_7, int tmp_struct_symbol_8, int tmp_struct_symbol_9);
DACE_EXPORTED int __dace_exit_cuda_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state);

DACE_DFI void loop_body_9_2_5(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_3_0, int _for_it_4_0, int _for_it_5_0, int tmp_struct_symbol_8) {
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



    tmp_index_92_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_94_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
    tmp_index_104_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_106_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
    tmp_index_116_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_118_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
    tmp_index_128_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_130_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
    tmp_index_140_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_142_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
    tmp_index_152_0 = (gpu___CG_p_patch__CG_verts__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
    tmp_index_154_0 = (gpu___CG_p_patch__CG_verts__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);

    {

        {
            double ptr_int_0_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (1 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double ptr_int_1_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (2 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double ptr_int_2_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (3 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double ptr_int_3_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (4 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double ptr_int_4_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (5 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double ptr_int_5_in_geofac_rot_0 = gpu___CG_p_int__m_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (6 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
            double vec_e_0_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
            double vec_e_1_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
            double vec_e_2_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
            double vec_e_3_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
            double vec_e_4_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
            double vec_e_5_in_0 = gpu___CG_p_prog__m_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
            double rot_vec_out_0;

            ///////////////////
            // Tasklet code (T_l296_c296)
            rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
            ///////////////////

            gpu_zeta[(((_for_it_5_0 + ((90 * tmp_struct_symbol_8) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_8 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
        }

    }

}

DACE_DFI void loop_body_1_1_5(const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_0_0_0, int _for_it_1_0_0, int _for_it_2_0_0, int tmp_struct_symbol_6) {
    int tmp_index_48_0_0;
    int tmp_index_72_0_0;
    int tmp_index_50_0_0;
    int tmp_index_14_0_0;
    int tmp_index_24_0_0;
    int tmp_index_26_0_0;
    int tmp_index_62_0_0;
    int tmp_index_38_0_0;
    int tmp_index_60_0_0;
    int tmp_index_36_0_0;
    int tmp_index_74_0_0;
    int tmp_index_12_0_0;



    tmp_index_48_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (4 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_72_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (6 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_50_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (4 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_14_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (1 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_24_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (2 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_26_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (2 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_62_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (5 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_38_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (3 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_60_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (5 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_36_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (3 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_74_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (6 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_12_0_0 = (gpu___CG_p_patch__CG_verts__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (1 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);

    {

        {
            double c_int_var_33_0_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (1 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double c_int_var_33_1_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (2 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double c_int_var_33_2_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (3 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double c_int_var_33_3_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (4 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double c_int_var_33_4_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (5 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double c_int_var_33_5_in_0 = gpu___CG_p_int__m_cells_aw_verts[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (6 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
            double p_cell_in_var_32_0_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_14_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_12_0_0)];
            double p_cell_in_var_32_1_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_26_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_24_0_0)];
            double p_cell_in_var_32_2_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_38_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_36_0_0)];
            double p_cell_in_var_32_3_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_50_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_48_0_0)];
            double p_cell_in_var_32_4_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_62_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_60_0_0)];
            double p_cell_in_var_32_5_in_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_74_0_0) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_1_0_0))) + tmp_index_72_0_0)];
            double p_vert_out_var_34_out_0;

            ///////////////////
            // Tasklet code (T_l117_c117)
            p_vert_out_var_34_out_0 = ((((((c_int_var_33_0_in_0 * p_cell_in_var_32_0_in_0) + (c_int_var_33_1_in_0 * p_cell_in_var_32_1_in_0)) + (c_int_var_33_2_in_0 * p_cell_in_var_32_2_in_0)) + (c_int_var_33_3_in_0 * p_cell_in_var_32_3_in_0)) + (c_int_var_33_4_in_0 * p_cell_in_var_32_4_in_0)) + (c_int_var_33_5_in_0 * p_cell_in_var_32_5_in_0));
            ///////////////////

            gpu_z_w_v[(((_for_it_2_0_0 + ((91 * tmp_struct_symbol_6) * (_for_it_0_0_0 - 1))) + (tmp_struct_symbol_6 * (_for_it_1_0_0 - 1))) - 1)] = p_vert_out_var_34_out_0;
        }

    }

}

DACE_DFI void loop_body_17_2_12(const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_vt_ie, const double * __restrict__ gpu_z_w_v, double * __restrict__ gpu_z_v_grad_w, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_16, int _for_it_17, int _for_it_18, int tmp_struct_symbol_4, int tmp_struct_symbol_6) {
    int tmp_index_329;
    int tmp_index_331;
    int tmp_index_338;
    int tmp_index_340;
    int tmp_index_354;
    int tmp_index_356;
    int tmp_index_363;
    int tmp_index_365;



    tmp_index_329 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_18)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_331 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_18)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_338 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_18)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
    tmp_index_340 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_18)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
    tmp_index_354 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_18)] - 1);
    tmp_index_356 = (gpu___CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_18)] - 1);
    tmp_index_363 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_18)] - 1);
    tmp_index_365 = (gpu___CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_16))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_18)] - 1);

    {

        {
            double p_diag_0_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_17)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_16))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_18)];
            double p_patch_0_in_edges_inv_dual_edge_length_0 = gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length[(((__f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4 * ((- __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4) + _for_it_16)) - __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4) + _for_it_18)];
            double p_patch_1_in_edges_inv_primal_edge_length_0 = gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) + _for_it_16)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4) + _for_it_18)];
            double p_patch_2_in_edges_tangent_orientation_0 = gpu___CG_p_patch__CG_edges__m_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4) + _for_it_16)) - __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4) + _for_it_18)];
            double p_prog_0_in_w_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_331) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_17))) + tmp_index_329)];
            double p_prog_1_in_w_0 = gpu___CG_p_prog__m_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_340) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_17))) + tmp_index_338)];
            double z_vt_ie_0_in_0 = gpu_z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_366 * __f2dace_A_z_vt_ie_d_1_s_367) * ((- __f2dace_OA_z_vt_ie_d_2_s_368) + _for_it_16)) + (__f2dace_A_z_vt_ie_d_0_s_366 * ((- __f2dace_OA_z_vt_ie_d_1_s_367) + _for_it_17))) - __f2dace_OA_z_vt_ie_d_0_s_366) + _for_it_18)];
            double z_w_v_0_in_0 = gpu_z_w_v[((tmp_index_354 + ((91 * tmp_index_356) * tmp_struct_symbol_6)) + (tmp_struct_symbol_6 * (_for_it_17 - 1)))];
            double z_w_v_1_in_0 = gpu_z_w_v[((tmp_index_363 + ((91 * tmp_index_365) * tmp_struct_symbol_6)) + (tmp_struct_symbol_6 * (_for_it_17 - 1)))];
            double z_v_grad_w_out_0;

            ///////////////////
            // Tasklet code (T_l488_c488)
            z_v_grad_w_out_0 = (((p_diag_0_in_vn_ie_0 * p_patch_0_in_edges_inv_dual_edge_length_0) * (p_prog_0_in_w_0 - p_prog_1_in_w_0)) + (((z_vt_ie_0_in_0 * p_patch_1_in_edges_inv_primal_edge_length_0) * p_patch_2_in_edges_tangent_orientation_0) * (z_w_v_0_in_0 - z_w_v_1_in_0)));
            ///////////////////

            gpu_z_v_grad_w[(((_for_it_18 + ((90 * tmp_struct_symbol_4) * (_for_it_16 - 1))) + (tmp_struct_symbol_4 * (_for_it_17 - 1))) - 1)] = z_v_grad_w_out_0;
        }

    }

}

DACE_DFI void loop_body_24_3_5(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_ekinh, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int _for_it_23, int _for_it_24, int tmp_struct_symbol_10) {
    int tmp_index_407;
    int tmp_index_409;
    int tmp_index_419;
    int tmp_index_421;
    int tmp_index_431;
    int tmp_index_433;



    tmp_index_407 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
    tmp_index_409 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);
    tmp_index_419 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
    tmp_index_421 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);
    tmp_index_431 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
    tmp_index_433 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);

    {

        {
            double p_int_0_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
            double p_int_1_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
            double p_int_2_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_409) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_407)];
            double z_kin_hor_e_1_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_421) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_419)];
            double z_kin_hor_e_2_in_0 = gpu_z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_433) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_431)];
            double z_ekinh_out_0;

            ///////////////////
            // Tasklet code (T_l515_c515)
            z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_kin_hor_e_2_in_0));
            ///////////////////

            gpu_z_ekinh[(((_for_it_24 + ((90 * tmp_struct_symbol_10) * (_for_it_22 - 1))) + (tmp_struct_symbol_10 * (_for_it_23 - 1))) - 1)] = z_ekinh_out_0;
        }

    }

}

DACE_DFI void loop_body_26_2_13(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_v_grad_w, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int _for_it_42, int _for_it_43, int ntnd, int tmp_struct_symbol_4) {
    int tmp_index_581;
    int tmp_index_583;
    int tmp_index_593;
    int tmp_index_595;
    int tmp_index_605;
    int tmp_index_607;



    tmp_index_581 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
    tmp_index_583 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);
    tmp_index_593 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
    tmp_index_595 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);
    tmp_index_605 = (gpu___CG_p_patch__CG_cells__m_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
    tmp_index_607 = (gpu___CG_p_patch__CG_cells__m_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);

    {

        {
            double p_diag_0_in_ddt_w_adv_pc_0 = gpu___CG_p_diag__m_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_42))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_43)];
            double p_int_0_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
            double p_int_1_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
            double p_int_2_in_e_bln_c_s_0 = gpu___CG_p_int__m_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
            double z_v_grad_w_0_in_0 = gpu_z_v_grad_w[((tmp_index_581 + ((90 * tmp_index_583) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
            double z_v_grad_w_1_in_0 = gpu_z_v_grad_w[((tmp_index_593 + ((90 * tmp_index_595) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
            double z_v_grad_w_2_in_0 = gpu_z_v_grad_w[((tmp_index_605 + ((90 * tmp_index_607) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
            double p_diag_out_ddt_w_adv_pc_0;

            ///////////////////
            // Tasklet code (T_l583_c583)
            p_diag_out_ddt_w_adv_pc_0 = (((p_diag_0_in_ddt_w_adv_pc_0 + (p_int_0_in_e_bln_c_s_0 * z_v_grad_w_0_in_0)) + (p_int_1_in_e_bln_c_s_0 * z_v_grad_w_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_v_grad_w_2_in_0));
            ///////////////////

            gpu___CG_p_diag__m_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_42))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_43)] = p_diag_out_ddt_w_adv_pc_0;
        }

    }

}

DACE_DFI void loop_body_41_2_6(const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_47, int _for_it_48, int _for_it_49, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
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



    tmp_index_698 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_700 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_710 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_712 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_724 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_726 = (gpu___CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_733 = (gpu___CG_p_patch__CG_edges__m_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_735 = (gpu___CG_p_patch__CG_edges__m_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_745 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_747 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_757 = (gpu___CG_p_patch__CG_edges__m_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
    tmp_index_759 = (gpu___CG_p_patch__CG_edges__m_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);

    {

        {
            double p_diag_0_in_vt_0 = gpu___CG_p_diag__m_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_292_p_diag_9) + _for_it_48)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_47))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_49)];
            double p_diag_1_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_48)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_47))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_49)];
            double p_diag_2_in_vn_ie_0 = gpu___CG_p_diag__m_vn_ie[(((((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_47)) + (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_48) + 1))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_49)];
            double p_int_0_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_49)];
            double p_int_1_in_c_lin_e_0 = gpu___CG_p_int__m_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_49)];
            double p_metrics_0_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
            double p_metrics_1_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
            double p_metrics_2_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
            double p_metrics_3_in_coeff_gradekin_0 = gpu___CG_p_metrics__m_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
            double p_metrics_4_in_ddqz_z_full_e_0 = gpu___CG_p_metrics__m_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8) + _for_it_48)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8) + _for_it_49)];
            double p_patch_0_in_edges_f_e_0 = gpu___CG_p_patch__CG_edges__m_f_e[(((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4) + _for_it_49)];
            double z_ekinh_0_in_0 = gpu_z_ekinh[((tmp_index_698 + ((90 * tmp_index_700) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_ekinh_1_in_0 = gpu_z_ekinh[((tmp_index_710 + ((90 * tmp_index_712) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
            double z_kin_hor_e_0_in_0 = gpu_z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_365) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s_363) + _for_it_49)];
            double z_w_con_c_full_0_in_0 = gpu_z_w_con_c_full[((tmp_index_745 + ((90 * tmp_index_747) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double z_w_con_c_full_1_in_0 = gpu_z_w_con_c_full[((tmp_index_757 + ((90 * tmp_index_759) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
            double zeta_0_in_0 = gpu_zeta[((tmp_index_724 + ((90 * tmp_index_726) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double zeta_1_in_0 = gpu_zeta[((tmp_index_733 + ((90 * tmp_index_735) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
            double p_diag_out_ddt_vn_apc_pc_0;

            ///////////////////
            // Tasklet code (T_l611_c611)
            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
            ///////////////////

            gpu___CG_p_diag__m_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9) + _for_it_48))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) + _for_it_49)] = p_diag_out_ddt_vn_apc_pc_0;
        }

    }

}



DACE_EXPORTED int __dace_init_cuda_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_area_d_0_s_158_cells_p_patch_2, int __f2dace_SA_area_d_1_s_159_cells_p_patch_2, int __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4, int __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2, int __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4, int __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5, int __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2, int __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4, int __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4, int __f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4, int __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6, int __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6, int __f2dace_SA_geofac_n2s_d_0_s_43_p_int_6, int __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6, int __f2dace_SA_geofac_n2s_d_2_s_45_p_int_6, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2, int __f2dace_SA_neighbor_blk_d_2_s_151_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2, int __f2dace_SA_neighbor_idx_d_2_s_148_cells_p_patch_2, int __f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3, int __f2dace_SA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3, int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6, int __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2, int __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4, int __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5, int __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2, int __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4, int __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vn_d_2_s_290_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SA_vt_d_2_s_293_p_diag_9, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SA_w_d_2_s_287_p_prog_7, int __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8, int __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2, int __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4, int __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5, int __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2, int __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4, int __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2, int __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4, int __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5, int __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2, int __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4, int __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_11, int tmp_struct_symbol_12, int tmp_struct_symbol_2, int tmp_struct_symbol_3, int tmp_struct_symbol_4, int tmp_struct_symbol_5, int tmp_struct_symbol_6, int tmp_struct_symbol_7, int tmp_struct_symbol_8, int tmp_struct_symbol_9) {
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

    

    __state->gpu_context = new dace::cuda::Context(1, 53);

    // Create cuda streams and events
    for(int i = 0; i < 1; ++i) {
        DACE_GPU_CHECK(cudaStreamCreateWithFlags(&__state->gpu_context->internal_streams[i], cudaStreamNonBlocking));
        __state->gpu_context->streams[i] = __state->gpu_context->internal_streams[i]; // Allow for externals to modify streams
    }
    for(int i = 0; i < 53; ++i) {
        DACE_GPU_CHECK(cudaEventCreateWithFlags(&__state->gpu_context->events[i], cudaEventDisableTiming));
    }

    

    return 0;
}

DACE_EXPORTED int __dace_exit_cuda_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state) {
    

    // Synchronize and check for CUDA errors
    int __err = static_cast<int>(__state->gpu_context->lasterror);
    if (__err == 0)
        __err = static_cast<int>(cudaDeviceSynchronize());

    // Destroy cuda streams and events
    for(int i = 0; i < 1; ++i) {
        DACE_GPU_CHECK(cudaStreamDestroy(__state->gpu_context->internal_streams[i]));
    }
    for(int i = 0; i < 53; ++i) {
        DACE_GPU_CHECK(cudaEventDestroy(__state->gpu_context->events[i]));
    }

    delete __state->gpu_context;
    return __err;
}

DACE_EXPORTED bool __dace_gpu_set_stream_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, int streamid, gpuStream_t stream)
{
    if (streamid < 0 || streamid >= 1)
        return false;

    __state->gpu_context->streams[streamid] = stream;

    return true;
}

DACE_EXPORTED void __dace_gpu_set_all_streams_1(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, gpuStream_t stream)
{
    for (int i = 0; i < 1; ++i)
        __state->gpu_context->streams[i] = stream;
}

__global__ void __launch_bounds__(256) single_state_body_map_1_1_9_2_6(const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_5_0 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_120_0);
            int _for_it_4_0 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_5_0 >= i_startidx_var_120_0 && _for_it_5_0 < (i_endidx_var_121_0 + 1)) {
                if (_for_it_4_0 >= 1) {
                    loop_body_9_2_5(&gpu___CG_p_int__m_geofac_rot[0], &gpu___CG_p_patch__CG_verts__m_edge_blk[0], &gpu___CG_p_patch__CG_verts__m_edge_idx[0], &gpu___CG_p_prog__m_vn[0], &gpu_zeta[0], __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, _for_it_3_0, _for_it_4_0, _for_it_5_0, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_1_1_9_2_6(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_map_1_1_9_2_6(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_1_1_9_2_6_args[] = { (void *)&gpu___CG_p_int__m_geofac_rot, (void *)&gpu___CG_p_patch__CG_verts__m_edge_blk, (void *)&gpu___CG_p_patch__CG_verts__m_edge_idx, (void *)&gpu___CG_p_prog__m_vn, (void *)&gpu_zeta, (void *)&__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, (void *)&__f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, (void *)&__f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, (void *)&__f2dace_SA_geofac_rot_d_0_s_40_p_int_6, (void *)&__f2dace_SA_geofac_rot_d_1_s_41_p_int_6, (void *)&__f2dace_SA_vn_d_0_s_288_p_prog_7, (void *)&__f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, (void *)&__f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, (void *)&__f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, (void *)&__f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, (void *)&__f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, (void *)&__f2dace_SOA_vn_d_0_s_288_p_prog_7, (void *)&__f2dace_SOA_vn_d_1_s_289_p_prog_7, (void *)&__f2dace_SOA_vn_d_2_s_290_p_prog_7, (void *)&_for_it_3_0, (void *)&i_endidx_var_121_0, (void *)&i_startidx_var_120_0, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_1_1_9_2_6, dim3(int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_1_1_9_2_6_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_1_1_9_2_6", int_ceil(int_ceil(((i_endidx_var_121_0 - i_startidx_var_120_0) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_1_1_1_1_6(const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_0_0_0, int i_endidx_var_47_0_0, int i_startidx_var_46_0_0, int tmp_struct_symbol_6) {
    {
        {
            int _for_it_2_0_0 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_46_0_0);
            int _for_it_1_0_0 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_2_0_0 >= i_startidx_var_46_0_0 && _for_it_2_0_0 < (i_endidx_var_47_0_0 + 1)) {
                if (_for_it_1_0_0 >= 1) {
                    loop_body_1_1_5(&gpu___CG_p_int__m_cells_aw_verts[0], &gpu___CG_p_patch__CG_verts__m_cell_blk[0], &gpu___CG_p_patch__CG_verts__m_cell_idx[0], &gpu___CG_p_prog__m_w[0], &gpu_z_w_v[0], __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, __f2dace_SA_w_d_0_s_285_p_prog_7, __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, __f2dace_SOA_w_d_0_s_285_p_prog_7, __f2dace_SOA_w_d_1_s_286_p_prog_7, __f2dace_SOA_w_d_2_s_287_p_prog_7, _for_it_0_0_0, _for_it_1_0_0, _for_it_2_0_0, tmp_struct_symbol_6);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_1_1_1_1_6(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_0_0_0, int i_endidx_var_47_0_0, int i_startidx_var_46_0_0, int tmp_struct_symbol_6);
void __dace_runkernel_single_state_body_map_1_1_1_1_6(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_cells_aw_verts, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_cell_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_v, int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_0_0_0, int i_endidx_var_47_0_0, int i_startidx_var_46_0_0, int tmp_struct_symbol_6)
{

    if ((int_ceil(int_ceil(((i_endidx_var_47_0_0 - i_startidx_var_46_0_0) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_1_1_1_1_6_args[] = { (void *)&gpu___CG_p_int__m_cells_aw_verts, (void *)&gpu___CG_p_patch__CG_verts__m_cell_blk, (void *)&gpu___CG_p_patch__CG_verts__m_cell_idx, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_w_v, (void *)&__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5, (void *)&__f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5, (void *)&__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5, (void *)&__f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5, (void *)&__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6, (void *)&__f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6, (void *)&__f2dace_SA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5, (void *)&__f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5, (void *)&__f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5, (void *)&__f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5, (void *)&__f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5, (void *)&__f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5, (void *)&__f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6, (void *)&__f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6, (void *)&__f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6, (void *)&__f2dace_SOA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_286_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_287_p_prog_7, (void *)&_for_it_0_0_0, (void *)&i_endidx_var_47_0_0, (void *)&i_startidx_var_46_0_0, (void *)&tmp_struct_symbol_6 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_1_1_1_1_6, dim3(int_ceil(int_ceil(((i_endidx_var_47_0_0 - i_startidx_var_46_0_0) + 1), 1), 256), 91, 1), dim3(256, 1, 1), single_state_body_map_1_1_1_1_6_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_1_1_1_1_6", int_ceil(int_ceil(((i_endidx_var_47_0_0 - i_startidx_var_46_0_0) + 1), 1), 256), 91, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_1_1_17_2_13(const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double * __restrict__ gpu_z_vt_ie, const double * __restrict__ gpu_z_w_v, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_16, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_4, int tmp_struct_symbol_6) {
    {
        {
            int _for_it_18 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_17 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_18 >= i_startidx_var_148 && _for_it_18 < (i_endidx_var_149 + 1)) {
                if (_for_it_17 >= 1) {
                    loop_body_17_2_12(&gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_patch__CG_edges__m_cell_blk[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_blk[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu___CG_p_prog__m_w[0], &gpu_z_vt_ie[0], &gpu_z_w_v[0], &gpu_z_v_grad_w[0], __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SA_w_d_0_s_285_p_prog_7, __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, __f2dace_SOA_w_d_0_s_285_p_prog_7, __f2dace_SOA_w_d_1_s_286_p_prog_7, __f2dace_SOA_w_d_2_s_287_p_prog_7, _for_it_16, _for_it_17, _for_it_18, tmp_struct_symbol_4, tmp_struct_symbol_6);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_1_1_17_2_13(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double * __restrict__ gpu_z_vt_ie, const double * __restrict__ gpu_z_w_v, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_16, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_4, int tmp_struct_symbol_6);
void __dace_runkernel_single_state_body_map_1_1_17_2_13(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_v_grad_w, const double * __restrict__ gpu_z_vt_ie, const double * __restrict__ gpu_z_w_v, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_16, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_4, int tmp_struct_symbol_6)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_1_1_17_2_13_args[] = { (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_patch__CG_edges__m_cell_blk, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx, (void *)&gpu___CG_p_patch__CG_edges__m_inv_dual_edge_length, (void *)&gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, (void *)&gpu___CG_p_patch__CG_edges__m_tangent_orientation, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_blk, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_v_grad_w, (void *)&gpu_z_vt_ie, (void *)&gpu_z_w_v, (void *)&__f2dace_A_z_vt_ie_d_0_s_366, (void *)&__f2dace_A_z_vt_ie_d_1_s_367, (void *)&__f2dace_OA_z_vt_ie_d_0_s_366, (void *)&__f2dace_OA_z_vt_ie_d_1_s_367, (void *)&__f2dace_OA_z_vt_ie_d_2_s_368, (void *)&__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, (void *)&__f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, (void *)&__f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, (void *)&__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, (void *)&__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, (void *)&__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, (void *)&__f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, (void *)&__f2dace_SA_vn_ie_d_0_s_294_p_diag_9, (void *)&__f2dace_SA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, (void *)&__f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, (void *)&__f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, (void *)&__f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4, (void *)&__f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4, (void *)&__f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, (void *)&__f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, (void *)&__f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, (void *)&__f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, (void *)&__f2dace_SOA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_286_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_287_p_prog_7, (void *)&_for_it_16, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_4, (void *)&tmp_struct_symbol_6 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_1_1_17_2_13, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_1_1_17_2_13_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_1_1_17_2_13", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_1_1_24_3_9(const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10) {
    {
        {
            int _for_it_24 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_23 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_24 >= i_startidx_var_148 && _for_it_24 < (i_endidx_var_149 + 1)) {
                if (_for_it_23 >= 1) {
                    loop_body_24_3_5(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &gpu_z_kin_hor_e[0], &gpu_z_ekinh[0], __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, _for_it_22, _for_it_23, _for_it_24, tmp_struct_symbol_10);
                    {
                        double p_prog_0_in_w_0 = gpu___CG_p_prog__m_w[((((__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_23)) + ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_24)];
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


DACE_EXPORTED void __dace_runkernel_single_state_body_map_1_1_24_3_9(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10);
void __dace_runkernel_single_state_body_map_1_1_24_3_9(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_10)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_1_1_24_3_9_args[] = { (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c, (void *)&__f2dace_A_z_kin_hor_e_d_0_s_363, (void *)&__f2dace_A_z_kin_hor_e_d_1_s_364, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s_363, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s_364, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s_365, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, (void *)&__f2dace_SA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, (void *)&__f2dace_SOA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_286_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_287_p_prog_7, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_10 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_1_1_24_3_9, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_map_1_1_24_3_9_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_1_1_24_3_9", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_1_map_1_1_24_4_0(double * __restrict__ gpu_z_w_con_c, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1) {
    {
        int _for_it_31 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
        if (_for_it_31 >= i_startidx_var_148 && _for_it_31 < (i_endidx_var_149 + 1)) {
            {
                double z_w_con_c_out_0;

                ///////////////////
                // Tasklet code (T_l536_c536)
                z_w_con_c_out_0 = 0.0;
                ///////////////////

                gpu_z_w_con_c[((_for_it_31 + (90 * tmp_struct_symbol_1)) - 1)] = z_w_con_c_out_0;
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_1_map_1_1_24_4_0(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu_z_w_con_c, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1);
void __dace_runkernel_single_state_body_1_map_1_1_24_4_0(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu_z_w_con_c, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_1_map_1_1_24_4_0_args[] = { (void *)&gpu_z_w_con_c, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_1_map_1_1_24_4_0, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1), dim3(256, 1, 1), single_state_body_1_map_1_1_24_4_0_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_1_map_1_1_24_4_0", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 1, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_2_map_1_1_24_4_7(const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1) {
    {
        {
            int _for_it_33 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_32 = (((blockIdx.y * 1 + threadIdx.y) + nflatlev_jg) + 1);
            if (_for_it_33 >= i_startidx_var_148 && _for_it_33 < (i_endidx_var_149 + 1)) {
                if (_for_it_32 >= (nflatlev_jg + 1)) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_33 + (tmp_struct_symbol_1 * (_for_it_32 - 1))) - 1)];
                        double p_diag_0_in_w_concorr_c_0 = gpu___CG_p_diag__m_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9) + _for_it_32)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9) + _for_it_33)];
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


DACE_EXPORTED void __dace_runkernel_single_state_body_2_map_1_1_24_4_7(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
void __dace_runkernel_single_state_body_2_map_1_1_24_4_7(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0 || (int_ceil(int_ceil((90 - nflatlev_jg), 1), 1)) == 0) {

        return;
    }

    void  *single_state_body_2_map_1_1_24_4_7_args[] = { (void *)&gpu___CG_p_diag__m_w_concorr_c, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, (void *)&__f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&nflatlev_jg, (void *)&tmp_struct_symbol_1 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_2_map_1_1_24_4_7, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1), dim3(256, 1, 1), single_state_body_2_map_1_1_24_4_7_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_2_map_1_1_24_4_7", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), int_ceil(int_ceil((90 - nflatlev_jg), 1), 1), 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_5_map_1_1_24_4_15(const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2) {
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


DACE_EXPORTED void __dace_runkernel_single_state_body_5_map_1_1_24_4_15(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
void __dace_runkernel_single_state_body_5_map_1_1_24_4_15(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_5_map_1_1_24_4_15_args[] = { (void *)&gpu_z_w_con_c, (void *)&gpu_z_w_con_c_full, (void *)&_for_it_22, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&tmp_struct_symbol_1, (void *)&tmp_struct_symbol_2 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_5_map_1_1_24_4_15, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_5_map_1_1_24_4_15_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_5_map_1_1_24_4_15", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_map_1_1_26_2_3(double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, const double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_1) {
    {
        {
            int _for_it_41 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_2);
            int _for_it_40 = ((blockIdx.y * 1 + threadIdx.y) + 2);
            if (_for_it_41 >= i_startidx_2 && _for_it_41 < (i_endidx_2 + 1)) {
                if (_for_it_40 >= 2) {
                    {
                        double z_w_con_c_0_in_0 = gpu_z_w_con_c[((_for_it_41 + (tmp_struct_symbol_1 * (_for_it_40 - 1))) - 1)];
                        double p_metrics_0_in_coeff1_dwdz_0 = gpu___CG_p_metrics__m_coeff1_dwdz[((((__f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8) + _for_it_41)];
                        double p_metrics_3_in_coeff1_dwdz_0 = gpu___CG_p_metrics__m_coeff1_dwdz[((((__f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8) + _for_it_41)];
                        double p_metrics_1_in_coeff2_dwdz_0 = gpu___CG_p_metrics__m_coeff2_dwdz[((((__f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8) + _for_it_41)];
                        double p_metrics_2_in_coeff2_dwdz_0 = gpu___CG_p_metrics__m_coeff2_dwdz[((((__f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8) + _for_it_41)];
                        double p_prog_0_in_w_0 = gpu___CG_p_prog__m_w[(((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22)) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40) - 1))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double p_prog_1_in_w_0 = gpu___CG_p_prog__m_w[(((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22)) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40) + 1))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double p_prog_2_in_w_0 = gpu___CG_p_prog__m_w[((((__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40)) + ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l578_c578)
                        p_diag_out_ddt_w_adv_pc_0 = (- (z_w_con_c_0_in_0 * (((p_prog_0_in_w_0 * p_metrics_0_in_coeff1_dwdz_0) - (p_prog_1_in_w_0 * p_metrics_1_in_coeff2_dwdz_0)) + (p_prog_2_in_w_0 * (p_metrics_2_in_coeff2_dwdz_0 - p_metrics_3_in_coeff1_dwdz_0)))));
                        ///////////////////

                        gpu___CG_p_diag__m_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9) + ntnd)) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_40))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_41)] = p_diag_out_ddt_w_adv_pc_0;
                    }
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_map_1_1_26_2_3(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, const double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_1);
void __dace_runkernel_single_state_body_map_1_1_26_2_3(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_metrics__m_coeff1_dwdz, const double * __restrict__ gpu___CG_p_metrics__m_coeff2_dwdz, const double * __restrict__ gpu___CG_p_prog__m_w, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_1)
{

    if ((int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_map_1_1_26_2_3_args[] = { (void *)&gpu___CG_p_diag__m_ddt_w_adv_pc, (void *)&gpu___CG_p_metrics__m_coeff1_dwdz, (void *)&gpu___CG_p_metrics__m_coeff2_dwdz, (void *)&gpu___CG_p_prog__m_w, (void *)&gpu_z_w_con_c, (void *)&__f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8, (void *)&__f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8, (void *)&__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, (void *)&__f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, (void *)&__f2dace_SA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8, (void *)&__f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8, (void *)&__f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8, (void *)&__f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8, (void *)&__f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8, (void *)&__f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, (void *)&__f2dace_SOA_w_d_0_s_285_p_prog_7, (void *)&__f2dace_SOA_w_d_1_s_286_p_prog_7, (void *)&__f2dace_SOA_w_d_2_s_287_p_prog_7, (void *)&_for_it_22, (void *)&i_endidx_2, (void *)&i_startidx_2, (void *)&ntnd, (void *)&tmp_struct_symbol_1 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_map_1_1_26_2_3, dim3(int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256), 89, 1), dim3(256, 1, 1), single_state_body_map_1_1_26_2_3_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_map_1_1_26_2_3", int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256), 89, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_1_1_26_2_10(double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_v_grad_w, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_4) {
    {
        {
            int _for_it_43 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_2);
            int _for_it_42 = ((blockIdx.y * 1 + threadIdx.y) + 2);
            if (_for_it_43 >= i_startidx_2 && _for_it_43 < (i_endidx_2 + 1)) {
                if (_for_it_42 >= 2) {
                    loop_body_26_2_13(&gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_patch__CG_cells__m_edge_blk[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &gpu_z_v_grad_w[0], &gpu___CG_p_diag__m_ddt_w_adv_pc[0], __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, _for_it_22, _for_it_42, _for_it_43, ntnd, tmp_struct_symbol_4);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_1_1_26_2_10(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_v_grad_w, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_4);
void __dace_runkernel_single_state_body_0_map_1_1_26_2_10(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_w_adv_pc, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, const double * __restrict__ gpu_z_v_grad_w, int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int i_endidx_2, int i_startidx_2, int ntnd, int tmp_struct_symbol_4)
{

    if ((int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_1_1_26_2_10_args[] = { (void *)&gpu___CG_p_diag__m_ddt_w_adv_pc, (void *)&gpu___CG_p_int__m_e_bln_c_s, (void *)&gpu___CG_p_patch__CG_cells__m_edge_blk, (void *)&gpu___CG_p_patch__CG_cells__m_edge_idx, (void *)&gpu_z_v_grad_w, (void *)&__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9, (void *)&__f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9, (void *)&__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, (void *)&__f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, (void *)&__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, (void *)&__f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, (void *)&__f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9, (void *)&__f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9, (void *)&__f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, (void *)&__f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, (void *)&__f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, (void *)&__f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, (void *)&__f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, (void *)&_for_it_22, (void *)&i_endidx_2, (void *)&i_startidx_2, (void *)&ntnd, (void *)&tmp_struct_symbol_4 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_1_1_26_2_10, dim3(int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256), 89, 1), dim3(256, 1, 1), single_state_body_0_map_1_1_26_2_10_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_1_1_26_2_10", int_ceil(int_ceil(((i_endidx_2 - i_startidx_2) + 1), 1), 256), 89, 1, 256, 1, 1);
}
__global__ void __launch_bounds__(256) single_state_body_0_map_1_1_41_2_7(double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    {
        {
            int _for_it_49 = ((blockIdx.x * 256 + threadIdx.x) + i_startidx_var_148);
            int _for_it_48 = ((blockIdx.y * 1 + threadIdx.y) + 1);
            if (_for_it_49 >= i_startidx_var_148 && _for_it_49 < (i_endidx_var_149 + 1)) {
                if (_for_it_48 >= 1) {
                    loop_body_41_2_6(&gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_cell_blk[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_vertex_blk[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu_z_ekinh[0], &gpu_z_kin_hor_e[0], &gpu_z_w_con_c_full[0], &gpu_zeta[0], &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, _for_it_47, _for_it_48, _for_it_49, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
                }
            }
        }
    }
}


DACE_EXPORTED void __dace_runkernel_single_state_body_0_map_1_1_41_2_7(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
void __dace_runkernel_single_state_body_0_map_1_1_41_2_7(velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8)
{

    if ((int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256)) == 0) {

        return;
    }

    void  *single_state_body_0_map_1_1_41_2_7_args[] = { (void *)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (void *)&gpu___CG_p_diag__m_vn_ie, (void *)&gpu___CG_p_diag__m_vt, (void *)&gpu___CG_p_int__m_c_lin_e, (void *)&gpu___CG_p_metrics__m_coeff_gradekin, (void *)&gpu___CG_p_metrics__m_ddqz_z_full_e, (void *)&gpu___CG_p_patch__CG_edges__m_cell_blk, (void *)&gpu___CG_p_patch__CG_edges__m_cell_idx, (void *)&gpu___CG_p_patch__CG_edges__m_f_e, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_blk, (void *)&gpu___CG_p_patch__CG_edges__m_vertex_idx, (void *)&gpu_z_ekinh, (void *)&gpu_z_kin_hor_e, (void *)&gpu_z_w_con_c_full, (void *)&gpu_zeta, (void *)&__f2dace_A_z_kin_hor_e_d_0_s_363, (void *)&__f2dace_A_z_kin_hor_e_d_1_s_364, (void *)&__f2dace_OA_z_kin_hor_e_d_0_s_363, (void *)&__f2dace_OA_z_kin_hor_e_d_1_s_364, (void *)&__f2dace_OA_z_kin_hor_e_d_2_s_365, (void *)&__f2dace_SA_c_lin_e_d_0_s_25_p_int_6, (void *)&__f2dace_SA_c_lin_e_d_1_s_26_p_int_6, (void *)&__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, (void *)&__f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, (void *)&__f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, (void *)&__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, (void *)&__f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, (void *)&__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, (void *)&__f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, (void *)&__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, (void *)&__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, (void *)&__f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, (void *)&__f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, (void *)&__f2dace_SA_vn_ie_d_0_s_294_p_diag_9, (void *)&__f2dace_SA_vt_d_0_s_291_p_diag_9, (void *)&__f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, (void *)&__f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, (void *)&__f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, (void *)&__f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, (void *)&__f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, (void *)&__f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, (void *)&__f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, (void *)&__f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, (void *)&__f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, (void *)&__f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, (void *)&__f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, (void *)&__f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, (void *)&__f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, (void *)&__f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, (void *)&__f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, (void *)&__f2dace_SOA_vt_d_0_s_291_p_diag_9, (void *)&__f2dace_SOA_vt_d_1_s_292_p_diag_9, (void *)&__f2dace_SOA_vt_d_2_s_293_p_diag_9, (void *)&_for_it_47, (void *)&i_endidx_var_149, (void *)&i_startidx_var_148, (void *)&ntnd, (void *)&tmp_struct_symbol_10, (void *)&tmp_struct_symbol_2, (void *)&tmp_struct_symbol_8 };
    gpuError_t __err = cudaLaunchKernel((void*)single_state_body_0_map_1_1_41_2_7, dim3(int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1), dim3(256, 1, 1), single_state_body_0_map_1_1_41_2_7_args, 0, __state->gpu_context->streams[0]);
    DACE_KERNEL_LAUNCH_CHECK(__err, "single_state_body_0_map_1_1_41_2_7", int_ceil(int_ceil(((i_endidx_var_149 - i_startidx_var_148) + 1), 1), 256), 90, 1, 256, 1, 1);
}

