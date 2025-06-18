#include "reductions_kernel.cuh"
#include "reductions_cpu.h"
#include "timer.h"
/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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

struct velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t {
    dace::cuda::Context *gpu_context;
    double * __restrict__ __0_gpu_z_w_con_c_full;
    double * __restrict__ __0_gpu_maxvcfl_arr;
    int * __restrict__ __0_gpu_levmask;
    int * __restrict__ __0_gpu_levelmask;
    double * __restrict__ __0_gpu_z_w_concorr_mc;
    double * __restrict__ __0_gpu_z_ekinh;
    double * __restrict__ __0_gpu_zeta;
    int * __restrict__ __0_gpu_cfl_clipping;
    double * __restrict__ __0_gpu_z_w_con_c;
    double * __restrict__ __0_gpu_vcflmax;
    double * __restrict__ __0_vcflmax;
    int * __restrict__ __16_out_val_0;
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
static int __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2;
static int __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2;
static int __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2;
static int __f2dace_SA_neighbor_idx_d_2_s_148_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2;
static int __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2;
static int __f2dace_SA_neighbor_blk_d_2_s_151_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2;
static int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2;
static int __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2;
static int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2;
static int __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2;
static int __f2dace_SOA_area_d_0_s_158_cells_p_patch_2;
static int __f2dace_SOA_area_d_1_s_159_cells_p_patch_2;
static int __f2dace_SA_area_d_0_s_158_cells_p_patch_2;
static int __f2dace_SA_area_d_1_s_159_cells_p_patch_2;
static int __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2;
static int __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2;
static int __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2;
static int __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2;
static int __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2;
static int __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2;
static int __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2;
static int __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2;
static int __f2dace_SOA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3;
static int __f2dace_SOA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3;
static int __f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3;
static int __f2dace_SA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3;
static int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4;
static int __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4;
static int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4;
static int __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4;
static int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4;
static int __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4;
static int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4;
static int __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4;
static int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4;
static int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4;
static int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4;
static int __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4;
static int __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4;
static int __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4;
static int __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4;
static int __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4;
static int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4;
static int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4;
static int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4;
static int __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4;
static int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4;
static int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4;
static int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4;
static int __f2dace_SA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4;
static int __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4;
static int __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4;
static int __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4;
static int __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4;
static int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4;
static int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4;
static int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4;
static int __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4;
static int __f2dace_SOA_fn_e_d_0_s_192_edges_p_patch_4;
static int __f2dace_SOA_fn_e_d_1_s_193_edges_p_patch_4;
static int __f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4;
static int __f2dace_SA_fn_e_d_1_s_193_edges_p_patch_4;
static int __f2dace_SOA_ft_e_d_0_s_194_edges_p_patch_4;
static int __f2dace_SOA_ft_e_d_1_s_195_edges_p_patch_4;
static int __f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4;
static int __f2dace_SA_ft_e_d_1_s_195_edges_p_patch_4;
static int __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4;
static int __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4;
static int __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4;
static int __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4;
static int __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4;
static int __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4;
static int __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4;
static int __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4;
static int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5;
static int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5;
static int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5;
static int __f2dace_SA_cell_idx_d_2_s_202_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5;
static int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5;
static int __f2dace_SA_cell_blk_d_2_s_205_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5;
static int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5;
static int __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5;
static int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5;
static int __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5;
static int __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5;
static int __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5;
static int __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5;
static int __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5;
static int __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5;
static int __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5;
static int __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5;
static int __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5;
static int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6;
static int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6;
static int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6;
static int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6;
static int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6;
static int __f2dace_SA_c_lin_e_d_2_s_27_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6;
static int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6;
static int __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6;
static int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6;
static int __f2dace_SA_cells_aw_verts_d_2_s_33_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6;
static int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6;
static int __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6;
static int __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6;
static int __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6;
static int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6;
static int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6;
static int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6;
static int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6;
static int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6;
static int __f2dace_SA_geofac_rot_d_2_s_42_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6;
static int __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6;
static int __f2dace_SA_geofac_n2s_d_0_s_43_p_int_6;
static int __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6;
static int __f2dace_SA_geofac_n2s_d_2_s_45_p_int_6;
static int __f2dace_SOA_w_d_0_s_285_p_prog_7;
static int __f2dace_SOA_w_d_1_s_286_p_prog_7;
static int __f2dace_SOA_w_d_2_s_287_p_prog_7;
static int __f2dace_SA_w_d_0_s_285_p_prog_7;
static int __f2dace_SA_w_d_2_s_287_p_prog_7;
static int __f2dace_SOA_vn_d_0_s_288_p_prog_7;
static int __f2dace_SOA_vn_d_1_s_289_p_prog_7;
static int __f2dace_SOA_vn_d_2_s_290_p_prog_7;
static int __f2dace_SA_vn_d_0_s_288_p_prog_7;
static int __f2dace_SA_vn_d_2_s_290_p_prog_7;
static int __f2dace_SOA_ddxn_z_full_d_0_s_308_p_metrics_8;
static int __f2dace_SOA_ddxn_z_full_d_1_s_309_p_metrics_8;
static int __f2dace_SOA_ddxn_z_full_d_2_s_310_p_metrics_8;
static int __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8;
static int __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_0_s_311_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_1_s_312_p_metrics_8;
static int __f2dace_SOA_ddxt_z_full_d_2_s_313_p_metrics_8;
static int __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8;
static int __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8;
static int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8;
static int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8;
static int __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8;
static int __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8;
static int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8;
static int __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8;
static int __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8;
static int __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8;
static int __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8;
static int __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8;
static int __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8;
static int __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8;
static int __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8;
static int __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8;
static int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8;
static int __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8;
static int __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8;
static int __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8;
static int __f2dace_SA_coeff1_dwdz_d_2_s_334_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8;
static int __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8;
static int __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8;
static int __f2dace_SA_coeff2_dwdz_d_2_s_337_p_metrics_8;
static int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_338_p_metrics_8;
static int __f2dace_SOA_deepatmo_invr_mc_d_0_s_339_p_metrics_8;
static int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_340_p_metrics_8;
static int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_341_p_metrics_8;
static int __f2dace_SOA_vt_d_0_s_291_p_diag_9;
static int __f2dace_SOA_vt_d_1_s_292_p_diag_9;
static int __f2dace_SOA_vt_d_2_s_293_p_diag_9;
static int __f2dace_SA_vt_d_0_s_291_p_diag_9;
static int __f2dace_SA_vt_d_2_s_293_p_diag_9;
static int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9;
static int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9;
static int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9;
static int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9;
static int __f2dace_SA_vn_ie_d_2_s_296_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9;
static int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9;
static int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9;
static int __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9;
static int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9;
static int __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9;
static int __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9;
static int __f2dace_SA_ddt_w_adv_pc_d_3_s_307_p_diag_9;
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_1_2_8(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_geofac_rot, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_3_0, int i_endidx_var_121_0, int i_startidx_var_120_0, int tmp_struct_symbol_8);
inline void loop_body_0_0_5(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, double * __restrict__ gpu___CG_p_int__m_geofac_rot, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_verts__m_edge_idx, int* __restrict__ gpu___CG_p_patch__CG_verts__m_end_index, int* __restrict__ gpu___CG_p_patch__CG_verts__m_start_index, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_zeta, int _for_it_3_0, int i_endblk_var_119_0, int i_startblk_var_118_0, int tmp_struct_symbol_8) {
    int i_startidx_in_var_103_0_0;
    int i_endidx_in_var_104_0_0;
    int i_startidx_var_120_0;
    int i_endidx_var_121_0;



    i_startidx_in_var_103_0_0 = gpu___CG_p_patch__CG_verts__m_start_index[(2 - __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5)];
    i_endidx_in_var_104_0_0 = gpu___CG_p_patch__CG_verts__m_end_index[((- __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5) - 5)];

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

        __dace_runkernel_GPU_DeviceMap_2_2_1_2_8(__state, gpu___CG_p_int__m_geofac_rot, gpu___CG_p_patch__CG_verts__m_edge_blk, gpu___CG_p_patch__CG_verts__m_edge_idx, gpu___CG_p_prog__m_vn, gpu_zeta, __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5, __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5, __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5, __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5, __f2dace_SA_geofac_rot_d_0_s_40_p_int_6, __f2dace_SA_geofac_rot_d_1_s_41_p_int_6, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5, __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5, __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5, __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5, __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5, __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5, __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6, __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6, __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, _for_it_3_0, i_endidx_var_121_0, i_startidx_var_120_0, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

}

DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_9_2_19(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6, int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4, int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6, int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_9_2_21(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8, int __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_9_3_24(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, const double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, int __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8, int __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_ddxn_z_full_d_0_s_308_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_1_s_309_p_metrics_8, int __f2dace_SOA_ddxn_z_full_d_2_s_310_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_0_s_311_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_1_s_312_p_metrics_8, int __f2dace_SOA_ddxt_z_full_d_2_s_313_p_metrics_8, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_9_3_22(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, const double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8, int __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8, int __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8, int _for_it_6, int i_endidx_var_149, int i_startidx_var_148);
inline void loop_body_0_0_16(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, double * __restrict__ gpu___CG_p_int__m_rbf_vec_coeff_e, double * __restrict__ gpu___CG_p_metrics__m_ddxn_z_full, double * __restrict__ gpu___CG_p_metrics__m_ddxt_z_full, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_e, double * __restrict__ gpu___CG_p_metrics__m_wgtfacq_e, int* __restrict__ gpu___CG_p_patch__CG_edges__m_end_index, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, int* __restrict__ gpu___CG_p_patch__CG_edges__m_start_index, double * __restrict__ gpu___CG_p_prog__m_vn, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_vt_ie, double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, int _for_it_6, int i_endblk_var_147, int i_startblk_var_146, int nflatlev_jg) {
    int i_startidx_in_var_91_3;
    int i_endidx_in_var_92_3;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_3 = gpu___CG_p_patch__CG_edges__m_start_index[(5 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
    i_endidx_in_var_92_3 = gpu___CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 10)];

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

        __dace_runkernel_GPU_DeviceMap_2_2_9_2_19(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_patch__CG_edges__m_quad_blk, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_prog__m_vn, __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6, __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4, __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6, __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148);
        __dace_runkernel_GPU_DeviceMap_2_2_9_2_21(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfac_e, gpu___CG_p_prog__m_vn, gpu_z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8, __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8, __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

    {

        __dace_runkernel_GPU_DeviceMap_2_2_9_3_24(__state, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxt_z_full, gpu___CG_p_prog__m_vn, gpu_z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8, __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_ddxn_z_full_d_0_s_308_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_1_s_309_p_metrics_8, __f2dace_SOA_ddxn_z_full_d_2_s_310_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_0_s_311_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_1_s_312_p_metrics_8, __f2dace_SOA_ddxt_z_full_d_2_s_313_p_metrics_8, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, _for_it_6, i_endidx_var_149, i_startidx_var_148, nflatlev_jg);
        __dace_runkernel_GPU_DeviceMap_2_2_9_3_22(__state, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_metrics__m_wgtfacq_e, gpu___CG_p_prog__m_vn, gpu_z_kin_hor_e, gpu_z_vt_ie, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8, __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8, __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8, _for_it_6, i_endidx_var_149, i_startidx_var_148);
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

}

DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_2_23(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_10);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_2_27(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_0_s_285_p_prog_7, int __f2dace_SOA_w_d_1_s_286_p_prog_7, int __f2dace_SOA_w_d_2_s_287_p_prog_7, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_2_25(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, const int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, double * __restrict__ gpu_z_w_concorr_mc, const double * __restrict__ gpu_z_w_concorr_me, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_2_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, const double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, const double * __restrict__ gpu_z_w_concorr_mc, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8, int __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_0);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_3_27(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu_z_w_con_c, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_3_30(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, int __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, int __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int nflatlev_jg, int tmp_struct_symbol_1);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_3_32(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, int * __restrict__ gpu_cfl_clipping, const double * __restrict__ gpu_z_w_con_c, int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8, int _for_it_22, const double cfl_w_limit, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_3_29(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, int * __restrict__ gpu_levmask, int _for_it_22, int nrdmax_jg, int tmp_struct_symbol_13);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_4_23(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const int * __restrict__ gpu_cfl_clipping, int * __restrict__ gpu_levmask, const double * __restrict__ gpu_z_w_con_c, int * __restrict__ __16_out_val_0, int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, int _for_it_22, const double dtime, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_13, int tmp_struct_symbol_14);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_4_27(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, const int * __restrict__ gpu_cfl_clipping, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_w_con_c, int * __restrict__ __16_out_val_0, int __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8, int __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8, int _for_it_22, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int tmp_struct_symbol_1, int tmp_struct_symbol_14, int tmp_struct_symbol_4);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_16_4_25(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, int _for_it_22, int i_endidx_var_149, int i_startidx_var_148, int tmp_struct_symbol_1, int tmp_struct_symbol_2);
inline void loop_body_0_0_34(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, const double&  cfl_w_limit, const double&  dtime, double * __restrict__ gpu___CG_p_int__m_e_bln_c_s, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_half, double * __restrict__ gpu___CG_p_metrics__m_wgtfac_c, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_blk, int * __restrict__ gpu___CG_p_patch__CG_cells__m_edge_idx, int* __restrict__ gpu___CG_p_patch__CG_cells__m_end_index, int* __restrict__ gpu___CG_p_patch__CG_cells__m_start_index, double * __restrict__ gpu___CG_p_prog__m_w, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_concorr_me, double * __restrict__ gpu___CG_p_diag__m_w_concorr_c, int * __restrict__ gpu_cfl_clipping, int * __restrict__ gpu_levmask, double * __restrict__ gpu_maxvcfl_arr, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_w_con_c, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_z_w_concorr_mc, double* __restrict__ vcflmax, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, int _for_it_22, int i_endblk_var_147, int i_startblk_var_146, int nflatlev_jg, int nrdmax_jg, int tmp_struct_symbol_0, int tmp_struct_symbol_1, int tmp_struct_symbol_10, int tmp_struct_symbol_13, int tmp_struct_symbol_14, int tmp_struct_symbol_2, int tmp_struct_symbol_4) {
    int i_startidx_in_var_79_1;
    int i_endidx_in_var_80_1;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_79_1 = gpu___CG_p_patch__CG_cells__m_start_index[(4 - __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2)];
    i_endidx_in_var_80_1 = gpu___CG_p_patch__CG_cells__m_end_index[((- __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2) - 5)];

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

        __dace_runkernel_GPU_DeviceMap_2_2_16_2_23(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu_z_ekinh, gpu_z_kin_hor_e, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_10);
        __dace_runkernel_GPU_DeviceMap_2_2_16_2_27(__state, gpu___CG_p_prog__m_w, gpu_z_w_con_c, __f2dace_SA_w_d_0_s_285_p_prog_7, __f2dace_SOA_w_d_0_s_285_p_prog_7, __f2dace_SOA_w_d_1_s_286_p_prog_7, __f2dace_SOA_w_d_2_s_287_p_prog_7, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1);
        __dace_runkernel_GPU_DeviceMap_2_2_16_2_25(__state, gpu___CG_p_int__m_e_bln_c_s, gpu___CG_p_patch__CG_cells__m_edge_blk, gpu___CG_p_patch__CG_cells__m_edge_idx, gpu_z_w_concorr_mc, gpu_z_w_concorr_me, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6, __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6, __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6, __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2, __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2, __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2, __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2, __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2, __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);
        __dace_runkernel_GPU_DeviceMap_2_2_16_2_29(__state, gpu___CG_p_diag__m_w_concorr_c, gpu___CG_p_metrics__m_wgtfac_c, gpu_z_w_concorr_mc, __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8, __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8, __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8, __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_0);


    }

    {
        int segment_size;
        int batch_size;

        {
            int _out;

            ///////////////////
            // Tasklet code (t_segment_size)
            _out = tmp_struct_symbol_14;
            ///////////////////

            segment_size = _out;
        }
        {
            int _out;

            ///////////////////
            // Tasklet code (t_batch_size)
            _out = (88 - Max(3, (nrdmax_jg - 2)));
            ///////////////////

            batch_size = _out;
        }
        __dace_runkernel_GPU_DeviceMap_2_2_16_3_27(__state, gpu_z_w_con_c, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1);
        __dace_runkernel_GPU_DeviceMap_2_2_16_3_30(__state, gpu___CG_p_diag__m_w_concorr_c, gpu_z_w_con_c, __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9, __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9, __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9, __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9, _for_it_22, i_endidx_var_149, i_startidx_var_148, nflatlev_jg, tmp_struct_symbol_1);
        __dace_runkernel_GPU_DeviceMap_2_2_16_3_32(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_z_w_con_c, __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8, _for_it_22, cfl_w_limit, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14);
        {
            int * in_arr = &gpu_cfl_clipping[(tmp_struct_symbol_14 * (Max(3, (nrdmax_jg - 2)) - 1))];
            int in_batch_size = batch_size;
            int in_segment_size = segment_size;
            int* out_arr = __state->__16_out_val_0 + (Max(3, (nrdmax_jg - 2)) - 1);

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];

            reduce_segmented_to_address_gpu(in_arr, out_arr, in_segment_size, in_batch_size, __dace_current_stream);
            ///////////////////

        }
        __dace_runkernel_GPU_DeviceMap_2_2_16_3_29(__state, gpu_levmask, _for_it_22, nrdmax_jg, tmp_struct_symbol_13);
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

    {
        double maxvcfl;
        int reduce_maxZ_to_scalar_size_0;

        __dace_runkernel_GPU_DeviceMap_2_2_16_4_23(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_levmask, gpu_z_w_con_c, __state->__16_out_val_0, __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, _for_it_22, dtime, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_13, tmp_struct_symbol_14);
        __dace_runkernel_GPU_DeviceMap_2_2_16_4_27(__state, gpu___CG_p_metrics__m_ddqz_z_half, gpu_cfl_clipping, gpu_maxvcfl_arr, gpu_z_w_con_c, __state->__16_out_val_0, __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8, __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8, _for_it_22, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, tmp_struct_symbol_1, tmp_struct_symbol_14, tmp_struct_symbol_4);
        __dace_runkernel_GPU_DeviceMap_2_2_16_4_25(__state, gpu_z_w_con_c, gpu_z_w_con_c_full, _for_it_22, i_endidx_var_149, i_startidx_var_148, tmp_struct_symbol_1, tmp_struct_symbol_2);
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
            double out;

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = __state->gpu_context->streams[__dace_current_stream_id];

            #define __REDUCE_GPU__

            #ifdef __REDUCE_DEVICE__
            out = reduce_maxZ_to_scalar_device(in_arr, in_size);
            #elif defined(__REDUCE_GPU__)
            out = reduce_maxZ_to_scalar_gpu(in_arr, in_size, __dace_current_stream);
            #else
            out = reduce_maxZ_to_scalar_cpu(in_arr, in_size);
            #endif

            #undef __REDUCE_GPU__

            ///////////////////

            maxvcfl = out;
        }
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
        {
            double maxvcfl_0_in = maxvcfl;
            double vcflmax_out_0;

            ///////////////////
            // Tasklet code (T_l572_c572)
            vcflmax_out_0 = maxvcfl_0_in;
            ///////////////////

            vcflmax[(_for_it_22 - 1)] = vcflmax_out_0;
        }
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

}

DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_0_0_81(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, int * __restrict__ gpu_levelmask, const int * __restrict__ gpu_levmask, int nrdmax_jg, int replaced_var_1, int replaced_var_3, int tmp_struct_symbol_13);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_34_2_33(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_diag__m_vn_ie, const double * __restrict__ gpu___CG_p_diag__m_vt, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu_z_ekinh, const double * __restrict__ gpu_z_kin_hor_e, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, int __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, int __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, int __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, int __f2dace_SOA_vt_d_0_s_291_p_diag_9, int __f2dace_SOA_vt_d_1_s_292_p_diag_9, int __f2dace_SOA_vt_d_2_s_293_p_diag_9, int _for_it_47, int i_endidx_var_149, int i_startidx_var_148, int ntnd, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
DACE_EXPORTED void __dace_runkernel_GPU_DeviceMap_2_2_34_2_35(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, const double * __restrict__ gpu___CG_p_int__m_c_lin_e, const double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, const double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, const double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, const int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, const double * __restrict__ gpu___CG_p_prog__m_vn, const int * __restrict__ gpu_levelmask, const double * __restrict__ gpu_z_w_con_c_full, const double * __restrict__ gpu_zeta, int __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4, int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6, int __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6, int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4, int __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4, int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, int __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, int __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, int __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6, int __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6, int __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6, int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4, int __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4, int __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, int __f2dace_SOA_vn_d_0_s_288_p_prog_7, int __f2dace_SOA_vn_d_1_s_289_p_prog_7, int __f2dace_SOA_vn_d_2_s_290_p_prog_7, int _for_it_47, const double cfl_w_limit, const double dtime, int i_endidx_var_149, int i_startidx_var_148, int nrdmax_jg, int ntnd, const double scalfac_exdiff, int tmp_struct_symbol_2, int tmp_struct_symbol_8);
inline void loop_body_0_0_64(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, const int&  __CG_global_data__m_nproma, const double&  cfl_w_limit, const double&  dtime, double * __restrict__ gpu___CG_p_diag__m_vn_ie, double * __restrict__ gpu___CG_p_diag__m_vt, double * __restrict__ gpu___CG_p_int__m_c_lin_e, double * __restrict__ gpu___CG_p_int__m_geofac_grdiv, double * __restrict__ gpu___CG_p_metrics__m_coeff_gradekin, double * __restrict__ gpu___CG_p_metrics__m_ddqz_z_full_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_area_edge, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_cell_idx, int* __restrict__ gpu___CG_p_patch__CG_edges__m_end_index, double * __restrict__ gpu___CG_p_patch__CG_edges__m_f_e, double * __restrict__ gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_quad_idx, int* __restrict__ gpu___CG_p_patch__CG_edges__m_start_index, double * __restrict__ gpu___CG_p_patch__CG_edges__m_tangent_orientation, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_blk, int * __restrict__ gpu___CG_p_patch__CG_edges__m_vertex_idx, double * __restrict__ gpu___CG_p_prog__m_vn, int * __restrict__ gpu_levelmask, double * __restrict__ gpu_z_ekinh, double * __restrict__ gpu_z_kin_hor_e, double * __restrict__ gpu_z_w_con_c_full, double * __restrict__ gpu_zeta, const double&  scalfac_exdiff, double * __restrict__ gpu___CG_p_diag__m_ddt_vn_apc_pc, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int _for_it_47, int i_endblk_var_147, int nrdmax_jg, int ntnd, int replaced_var_4, int replaced_var_5, int tmp_struct_symbol_10, int tmp_struct_symbol_2, int tmp_struct_symbol_8) {
    int i_startidx_in_var_91_0;
    int i_endidx_in_var_92_0;
    int i_startidx_var_148;
    int i_endidx_var_149;



    i_startidx_in_var_91_0 = gpu___CG_p_patch__CG_edges__m_start_index[(10 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
    i_endidx_in_var_92_0 = gpu___CG_p_patch__CG_edges__m_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 8)];

    if (((_for_it_47 != replaced_var_4) && (_for_it_47 != replaced_var_5))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((! (_for_it_47 != replaced_var_4)) && (_for_it_47 != replaced_var_5))) {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = __CG_global_data__m_nproma;

    } else if (((_for_it_47 != replaced_var_4) && (! (_for_it_47 != i_endblk_var_147)))) {

        i_startidx_var_148 = 1;
        i_endidx_var_149 = i_endidx_in_var_92_0;

    } else {

        i_startidx_var_148 = max(1, i_startidx_in_var_91_0);
        i_endidx_var_149 = i_endidx_in_var_92_0;

    }

    {

        __dace_runkernel_GPU_DeviceMap_2_2_34_2_33(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vt, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_cell_blk, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_vertex_blk, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu_z_ekinh, gpu_z_kin_hor_e, gpu_z_w_con_c_full, gpu_zeta, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8, __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8, __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4, __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8, __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4, __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9, __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9, __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9, __f2dace_SOA_vt_d_0_s_291_p_diag_9, __f2dace_SOA_vt_d_1_s_292_p_diag_9, __f2dace_SOA_vt_d_2_s_293_p_diag_9, _for_it_47, i_endidx_var_149, i_startidx_var_148, ntnd, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
        __dace_runkernel_GPU_DeviceMap_2_2_34_2_35(__state, gpu___CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_int__m_c_lin_e, gpu___CG_p_int__m_geofac_grdiv, gpu___CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_cell_blk, gpu___CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_quad_blk, gpu___CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_vertex_blk, gpu___CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_prog__m_vn, gpu_levelmask, gpu_z_w_con_c_full, gpu_zeta, __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4, __f2dace_SA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6, __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6, __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4, __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4, __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4, __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4, __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4, __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4, __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4, __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6, __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6, __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6, __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4, __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4, __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4, __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4, __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4, __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4, __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8, __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8, __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9, __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9, __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6, __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6, __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6, __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4, __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4, __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4, __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4, __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4, __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4, __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4, __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4, __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4, __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4, __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4, __f2dace_SOA_vn_d_0_s_288_p_prog_7, __f2dace_SOA_vn_d_1_s_289_p_prog_7, __f2dace_SOA_vn_d_2_s_290_p_prog_7, _for_it_47, cfl_w_limit, dtime, i_endidx_var_149, i_startidx_var_148, nrdmax_jg, ntnd, scalfac_exdiff, tmp_struct_symbol_2, tmp_struct_symbol_8);
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

}

void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1_internal(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int *__CG_global_data__m_nflatlev;
    __CG_global_data__m_nflatlev = new int DACE_ALIGN(64)[10];
    int *__CG_global_data__m_nrdmax;
    __CG_global_data__m_nrdmax = new int DACE_ALIGN(64)[10];
    int *__CG_p_patch__CG_cells__m_edge_idx;
    __CG_p_patch__CG_cells__m_edge_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (__f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * (__f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2 - 1))) + __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2)];
    int *__CG_p_patch__CG_cells__m_edge_blk;
    __CG_p_patch__CG_cells__m_edge_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (__f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * (__f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2 - 1))) + __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2)];
    int *__CG_p_patch__CG_cells__m_start_index;
    __CG_p_patch__CG_cells__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_160_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_end_index;
    __CG_p_patch__CG_cells__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_161_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_start_block;
    __CG_p_patch__CG_cells__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_162_cells_p_patch_2];
    int *__CG_p_patch__CG_cells__m_end_block;
    __CG_p_patch__CG_cells__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_163_cells_p_patch_2];
    int *__CG_p_patch__CG_edges__m_cell_idx;
    __CG_p_patch__CG_edges__m_cell_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (__f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * (__f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4 - 1))) + __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_cell_blk;
    __CG_p_patch__CG_edges__m_cell_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (__f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * (__f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4 - 1))) + __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_vertex_idx;
    __CG_p_patch__CG_edges__m_vertex_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (__f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * (__f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_vertex_blk;
    __CG_p_patch__CG_edges__m_vertex_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (__f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * (__f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_tangent_orientation;
    __CG_p_patch__CG_edges__m_tangent_orientation = new double DACE_ALIGN(64)[((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * (__f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4 - 1)) + __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_quad_idx;
    __CG_p_patch__CG_edges__m_quad_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (__f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * (__f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4 - 1))) + __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_quad_blk;
    __CG_p_patch__CG_edges__m_quad_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (__f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * (__f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4 - 1))) + __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_inv_primal_edge_length;
    __CG_p_patch__CG_edges__m_inv_primal_edge_length = new double DACE_ALIGN(64)[((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * (__f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4 - 1)) + __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_area_edge;
    __CG_p_patch__CG_edges__m_area_edge = new double DACE_ALIGN(64)[((__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * (__f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4 - 1)) + __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4)];
    double *__CG_p_patch__CG_edges__m_f_e;
    __CG_p_patch__CG_edges__m_f_e = new double DACE_ALIGN(64)[((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * (__f2dace_SA_f_e_d_1_s_191_edges_p_patch_4 - 1)) + __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4)];
    int *__CG_p_patch__CG_edges__m_start_index;
    __CG_p_patch__CG_edges__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_196_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_end_index;
    __CG_p_patch__CG_edges__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_197_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_start_block;
    __CG_p_patch__CG_edges__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_198_edges_p_patch_4];
    int *__CG_p_patch__CG_edges__m_end_block;
    __CG_p_patch__CG_edges__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_199_edges_p_patch_4];
    int *__CG_p_patch__CG_verts__m_edge_idx;
    __CG_p_patch__CG_verts__m_edge_idx = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (__f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * (__f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5 - 1))) + __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5)];
    int *__CG_p_patch__CG_verts__m_edge_blk;
    __CG_p_patch__CG_verts__m_edge_blk = new int DACE_ALIGN(64)[((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (__f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * (__f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5 - 1))) + __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5)];
    int *__CG_p_patch__CG_verts__m_start_index;
    __CG_p_patch__CG_verts__m_start_index = new int DACE_ALIGN(64)[__f2dace_SA_start_index_d_0_s_212_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_end_index;
    __CG_p_patch__CG_verts__m_end_index = new int DACE_ALIGN(64)[__f2dace_SA_end_index_d_0_s_213_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_start_block;
    __CG_p_patch__CG_verts__m_start_block = new int DACE_ALIGN(64)[__f2dace_SA_start_block_d_0_s_214_verts_p_patch_5];
    int *__CG_p_patch__CG_verts__m_end_block;
    __CG_p_patch__CG_verts__m_end_block = new int DACE_ALIGN(64)[__f2dace_SA_end_block_d_0_s_215_verts_p_patch_5];
    double *__CG_p_int__m_c_lin_e;
    __CG_p_int__m_c_lin_e = new double DACE_ALIGN(64)[((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * (__f2dace_SA_c_lin_e_d_2_s_27_p_int_6 - 1)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (__f2dace_SA_c_lin_e_d_1_s_26_p_int_6 - 1))) + __f2dace_SA_c_lin_e_d_0_s_25_p_int_6)];
    double *__CG_p_int__m_e_bln_c_s;
    __CG_p_int__m_e_bln_c_s = new double DACE_ALIGN(64)[((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * (__f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6 - 1)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (__f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6 - 1))) + __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6)];
    double *__CG_p_int__m_rbf_vec_coeff_e;
    __CG_p_int__m_rbf_vec_coeff_e = new double DACE_ALIGN(64)[((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * (__f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6 - 1)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * (__f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6 - 1))) + __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6)];
    double *__CG_p_int__m_geofac_grdiv;
    __CG_p_int__m_geofac_grdiv = new double DACE_ALIGN(64)[((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * (__f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6 - 1)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (__f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6 - 1))) + __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6)];
    double *__CG_p_int__m_geofac_rot;
    __CG_p_int__m_geofac_rot = new double DACE_ALIGN(64)[((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * (__f2dace_SA_geofac_rot_d_2_s_42_p_int_6 - 1)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (__f2dace_SA_geofac_rot_d_1_s_41_p_int_6 - 1))) + __f2dace_SA_geofac_rot_d_0_s_40_p_int_6)];
    double *__CG_p_prog__m_w;
    __CG_p_prog__m_w = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * (__f2dace_SA_w_d_2_s_287_p_prog_7 - 1)) + (91 * __f2dace_SA_w_d_0_s_285_p_prog_7))];
    double *__CG_p_prog__m_vn;
    __CG_p_prog__m_vn = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * (__f2dace_SA_vn_d_2_s_290_p_prog_7 - 1)) + (90 * __f2dace_SA_vn_d_0_s_288_p_prog_7))];
    double *__CG_p_metrics__m_ddxn_z_full;
    __CG_p_metrics__m_ddxn_z_full = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8) * (__f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8))];
    double *__CG_p_metrics__m_ddxt_z_full;
    __CG_p_metrics__m_ddxt_z_full = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8) * (__f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8))];
    double *__CG_p_metrics__m_ddqz_z_full_e;
    __CG_p_metrics__m_ddqz_z_full_e = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * (__f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8))];
    double *__CG_p_metrics__m_ddqz_z_half;
    __CG_p_metrics__m_ddqz_z_half = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * (__f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8 - 1)) + (91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8))];
    double *__CG_p_metrics__m_wgtfac_c;
    __CG_p_metrics__m_wgtfac_c = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * (__f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8 - 1)) + (91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8))];
    double *__CG_p_metrics__m_wgtfac_e;
    __CG_p_metrics__m_wgtfac_e = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * (__f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8 - 1)) + (91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8))];
    double *__CG_p_metrics__m_wgtfacq_e;
    __CG_p_metrics__m_wgtfacq_e = new double DACE_ALIGN(64)[((((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * (__f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8 - 1)) + (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * (__f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8 - 1))) + __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8)];
    double *__CG_p_metrics__m_coeff_gradekin;
    __CG_p_metrics__m_coeff_gradekin = new double DACE_ALIGN(64)[((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * (__f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8 - 1)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (__f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8 - 1))) + __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8)];
    double *__CG_p_diag__m_vt;
    __CG_p_diag__m_vt = new double DACE_ALIGN(64)[(((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * (__f2dace_SA_vt_d_2_s_293_p_diag_9 - 1)) + (90 * __f2dace_SA_vt_d_0_s_291_p_diag_9))];
    double *__CG_p_diag__m_vn_ie;
    __CG_p_diag__m_vn_ie = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * (__f2dace_SA_vn_ie_d_2_s_296_p_diag_9 - 1)) + (91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9))];
    double *__CG_p_diag__m_w_concorr_c;
    __CG_p_diag__m_w_concorr_c = new double DACE_ALIGN(64)[(((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * (__f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9 - 1)) + (91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9))];
    double *__CG_p_diag__m_ddt_vn_apc_pc;
    __CG_p_diag__m_ddt_vn_apc_pc = new double DACE_ALIGN(64)[(((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9 - 1)) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9 - 1))) + (90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9))];
    int __CG_global_data__m_nproma;
    double __CG_p_diag__m_max_vcfl_dyn;
    int * gpu___CG_global_data__m_nflatlev;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_global_data__m_nflatlev, 10 * sizeof(int)));
    int * gpu___CG_global_data__m_nrdmax;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_global_data__m_nrdmax, 10 * sizeof(int)));
    double * gpu___CG_p_diag__m_ddt_vn_apc_pc;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_diag__m_ddt_vn_apc_pc, (((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9 - 1)) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * (__f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9 - 1))) + (90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9)) * sizeof(double)));
    double * gpu___CG_p_diag__m_vn_ie;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_diag__m_vn_ie, (((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * (__f2dace_SA_vn_ie_d_2_s_296_p_diag_9 - 1)) + (91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9)) * sizeof(double)));
    double * gpu___CG_p_diag__m_vt;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_diag__m_vt, (((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * (__f2dace_SA_vt_d_2_s_293_p_diag_9 - 1)) + (90 * __f2dace_SA_vt_d_0_s_291_p_diag_9)) * sizeof(double)));
    double * gpu___CG_p_diag__m_w_concorr_c;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_diag__m_w_concorr_c, (((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * (__f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9 - 1)) + (91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)) * sizeof(double)));
    double * gpu___CG_p_int__m_c_lin_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_int__m_c_lin_e, ((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * (__f2dace_SA_c_lin_e_d_2_s_27_p_int_6 - 1)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (__f2dace_SA_c_lin_e_d_1_s_26_p_int_6 - 1))) + __f2dace_SA_c_lin_e_d_0_s_25_p_int_6) * sizeof(double)));
    double * gpu___CG_p_int__m_e_bln_c_s;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_int__m_e_bln_c_s, ((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * (__f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6 - 1)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (__f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6 - 1))) + __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6) * sizeof(double)));
    double * gpu___CG_p_int__m_geofac_grdiv;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_int__m_geofac_grdiv, ((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * (__f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6 - 1)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (__f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6 - 1))) + __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6) * sizeof(double)));
    double * gpu___CG_p_int__m_geofac_rot;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_int__m_geofac_rot, ((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * (__f2dace_SA_geofac_rot_d_2_s_42_p_int_6 - 1)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (__f2dace_SA_geofac_rot_d_1_s_41_p_int_6 - 1))) + __f2dace_SA_geofac_rot_d_0_s_40_p_int_6) * sizeof(double)));
    double * gpu___CG_p_int__m_rbf_vec_coeff_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_int__m_rbf_vec_coeff_e, ((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * (__f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6 - 1)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * (__f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6 - 1))) + __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6) * sizeof(double)));
    double * gpu___CG_p_metrics__m_coeff_gradekin;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_coeff_gradekin, ((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * (__f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8 - 1)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (__f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8 - 1))) + __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8) * sizeof(double)));
    double * gpu___CG_p_metrics__m_ddqz_z_full_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_ddqz_z_full_e, (((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * (__f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_ddqz_z_half;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_ddqz_z_half, (((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * (__f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8 - 1)) + (91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_ddxn_z_full;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_ddxn_z_full, (((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8) * (__f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_ddxt_z_full;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_ddxt_z_full, (((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8) * (__f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8 - 1)) + (90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_wgtfac_c;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_wgtfac_c, (((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * (__f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8 - 1)) + (91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_wgtfac_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_wgtfac_e, (((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * (__f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8 - 1)) + (91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)) * sizeof(double)));
    double * gpu___CG_p_metrics__m_wgtfacq_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_metrics__m_wgtfacq_e, ((((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * (__f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8 - 1)) + (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * (__f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8 - 1))) + __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8) * sizeof(double)));
    int * gpu___CG_p_patch__CG_cells__m_edge_blk;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_edge_blk, ((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (__f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * (__f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2 - 1))) + __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2) * sizeof(int)));
    int * gpu___CG_p_patch__CG_cells__m_edge_idx;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_edge_idx, ((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (__f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2 - 1)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * (__f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2 - 1))) + __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2) * sizeof(int)));
    int * gpu___CG_p_patch__CG_cells__m_end_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_end_block, __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2 * sizeof(int)));
    int * gpu___CG_p_patch__CG_cells__m_end_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_end_index, __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2 * sizeof(int)));
    int * gpu___CG_p_patch__CG_cells__m_start_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_start_block, __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2 * sizeof(int)));
    int * gpu___CG_p_patch__CG_cells__m_start_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_cells__m_start_index, __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2 * sizeof(int)));
    double * gpu___CG_p_patch__CG_edges__m_area_edge;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_area_edge, ((__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * (__f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4 - 1)) + __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4) * sizeof(double)));
    int * gpu___CG_p_patch__CG_edges__m_cell_blk;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_cell_blk, ((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (__f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * (__f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4 - 1))) + __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_cell_idx;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_cell_idx, ((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (__f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4 - 1)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * (__f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4 - 1))) + __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_end_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_end_block, __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4 * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_end_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_end_index, __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4 * sizeof(int)));
    double * gpu___CG_p_patch__CG_edges__m_f_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_f_e, ((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * (__f2dace_SA_f_e_d_1_s_191_edges_p_patch_4 - 1)) + __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4) * sizeof(double)));
    double * gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, ((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * (__f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4 - 1)) + __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4) * sizeof(double)));
    int * gpu___CG_p_patch__CG_edges__m_quad_blk;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_quad_blk, ((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (__f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * (__f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4 - 1))) + __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_quad_idx;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_quad_idx, ((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (__f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4 - 1)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * (__f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4 - 1))) + __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_start_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_start_block, __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4 * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_start_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_start_index, __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4 * sizeof(int)));
    double * gpu___CG_p_patch__CG_edges__m_tangent_orientation;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_tangent_orientation, ((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * (__f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4 - 1)) + __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4) * sizeof(double)));
    int * gpu___CG_p_patch__CG_edges__m_vertex_blk;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_vertex_blk, ((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (__f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * (__f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_edges__m_vertex_idx;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_edges__m_vertex_idx, ((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (__f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4 - 1)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * (__f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4 - 1))) + __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4) * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_edge_blk;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_edge_blk, ((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (__f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * (__f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5 - 1))) + __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5) * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_edge_idx;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_edge_idx, ((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (__f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5 - 1)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * (__f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5 - 1))) + __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5) * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_end_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_end_block, __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5 * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_end_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_end_index, __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5 * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_start_block;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_start_block, __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5 * sizeof(int)));
    int * gpu___CG_p_patch__CG_verts__m_start_index;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_patch__CG_verts__m_start_index, __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5 * sizeof(int)));
    double * gpu___CG_p_prog__m_vn;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_prog__m_vn, (((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * (__f2dace_SA_vn_d_2_s_290_p_prog_7 - 1)) + (90 * __f2dace_SA_vn_d_0_s_288_p_prog_7)) * sizeof(double)));
    double * gpu___CG_p_prog__m_w;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu___CG_p_prog__m_w, (((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * (__f2dace_SA_w_d_2_s_287_p_prog_7 - 1)) + (91 * __f2dace_SA_w_d_0_s_285_p_prog_7)) * sizeof(double)));
    double * gpu_z_kin_hor_e;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu_z_kin_hor_e, ((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * (__f2dace_A_z_kin_hor_e_d_2_s_365 - 1)) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * (__f2dace_A_z_kin_hor_e_d_1_s_364 - 1))) + __f2dace_A_z_kin_hor_e_d_0_s_363) * sizeof(double)));
    double * gpu_z_vt_ie;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu_z_vt_ie, ((((__f2dace_A_z_vt_ie_d_0_s_366 * __f2dace_A_z_vt_ie_d_1_s_367) * (__f2dace_A_z_vt_ie_d_2_s_368 - 1)) + (__f2dace_A_z_vt_ie_d_0_s_366 * (__f2dace_A_z_vt_ie_d_1_s_367 - 1))) + __f2dace_A_z_vt_ie_d_0_s_366) * sizeof(double)));
    double * gpu_z_w_concorr_me;
    DACE_GPU_CHECK(cudaMalloc((void**)&gpu_z_w_concorr_me, ((((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * (__f2dace_A_z_w_concorr_me_d_2_s_362 - 1)) + (__f2dace_A_z_w_concorr_me_d_0_s_360 * (__f2dace_A_z_w_concorr_me_d_1_s_361 - 1))) + __f2dace_A_z_w_concorr_me_d_0_s_360) * sizeof(double)));
    int nrdmax_jg;
    int nflatlev_jg;
    int i_startblk_var_118_0;
    int i_endblk_var_119_0;
    int i_startblk_var_146;
    int i_endblk_var_147;
    int replaced_var_1;
    int replaced_var_3;
    int replaced_var_4;
    int replaced_var_5;
    int replaced_var_6;
    int replaced_var_7;


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
            double* __cg_p_int__m_rbf_vec_coeff_e = __CG_p_int__m_rbf_vec_coeff_e;
            double* __cg_p_metrics__m_coeff_gradekin = __CG_p_metrics__m_coeff_gradekin;
            double* __cg_p_metrics__m_ddqz_z_full_e = __CG_p_metrics__m_ddqz_z_full_e;
            double* __cg_p_metrics__m_ddqz_z_half = __CG_p_metrics__m_ddqz_z_half;
            double* __cg_p_metrics__m_ddxn_z_full = __CG_p_metrics__m_ddxn_z_full;
            double* __cg_p_metrics__m_ddxt_z_full = __CG_p_metrics__m_ddxt_z_full;
            double* __cg_p_metrics__m_wgtfac_c = __CG_p_metrics__m_wgtfac_c;
            double* __cg_p_metrics__m_wgtfac_e = __CG_p_metrics__m_wgtfac_e;
            double* __cg_p_metrics__m_wgtfacq_e = __CG_p_metrics__m_wgtfacq_e;
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
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2; i++){
                                    __cg_p_patch__cg_cells__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2)))] = p_patch->cells->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2; i++){
                                    __cg_p_patch__cg_cells__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2)))] = p_patch->cells->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_start_index[(i * (1))] = p_patch->cells->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_end_index[(i * (1))] = p_patch->cells->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_start_block[(i * (1))] = p_patch->cells->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2; i++){
                            __cg_p_patch__cg_cells__m_end_block[(i * (1))] = p_patch->cells->end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4)))] = p_patch->edges->cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4)))] = p_patch->edges->cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4)))] = p_patch->edges->vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4)))] = p_patch->edges->vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4))] = p_patch->edges->tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4))];
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4)))] = p_patch->edges->quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4; i++){
                                    __cg_p_patch__cg_edges__m_quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4)))] = p_patch->edges->quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4))] = p_patch->edges->inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4))] = p_patch->edges->area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4; i++){
                                __cg_p_patch__cg_edges__m_f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4))] = p_patch->edges->f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4))];
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_start_index[(i * (1))] = p_patch->edges->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_end_index[(i * (1))] = p_patch->edges->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_start_block[(i * (1))] = p_patch->edges->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4; i++){
                            __cg_p_patch__cg_edges__m_end_block[(i * (1))] = p_patch->edges->end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5; i++){
                                    __cg_p_patch__cg_verts__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5)))] = p_patch->verts->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5; i++){
                                    __cg_p_patch__cg_verts__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5)))] = p_patch->verts->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_start_index[(i * (1))] = p_patch->verts->start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_end_index[(i * (1))] = p_patch->verts->end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_start_block[(i * (1))] = p_patch->verts->start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5; i++){
                            __cg_p_patch__cg_verts__m_end_block[(i * (1))] = p_patch->verts->end_block[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_c_lin_e_d_2_s_27_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_c_lin_e_d_1_s_26_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_c_lin_e_d_0_s_25_p_int_6; i++){
                                    __cg_p_int__m_c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6)))] = p_int->c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6; i++){
                                    __cg_p_int__m_e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6)))] = p_int->e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6; i++){
                                    __cg_p_int__m_rbf_vec_coeff_e[(i * (1)) + (j * (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6)) + (k * ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6)))] = p_int->rbf_vec_coeff_e[(i * (1)) + (j * (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6)) + (k * ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6; i++){
                                    __cg_p_int__m_geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6)))] = p_int->geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_rot_d_2_s_42_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_rot_d_1_s_41_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_rot_d_0_s_40_p_int_6; i++){
                                    __cg_p_int__m_geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6)))] = p_int->geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_d_2_s_287_p_prog_7; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_d_0_s_285_p_prog_7; i++){
                                    __cg_p_prog__m_w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_285_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7)))] = p_prog->w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_285_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_d_2_s_290_p_prog_7; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_d_0_s_288_p_prog_7; i++){
                                    __cg_p_prog__m_vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_288_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7)))] = p_prog->vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_288_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddxn_z_full[(i * (1)) + (j * (__f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)))] = p_metrics->ddxn_z_full[(i * (1)) + (j * (__f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddxt_z_full[(i * (1)) + (j * (__f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)))] = p_metrics->ddxt_z_full[(i * (1)) + (j * (__f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)))] = p_metrics->ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8; i++){
                                    __cg_p_metrics__m_ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)))] = p_metrics->ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8; i++){
                                    __cg_p_metrics__m_wgtfac_c[(i * (1)) + (j * (__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)))] = p_metrics->wgtfac_c[(i * (1)) + (j * (__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8; i++){
                                    __cg_p_metrics__m_wgtfac_e[(i * (1)) + (j * (__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)))] = p_metrics->wgtfac_e[(i * (1)) + (j * (__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8; i++){
                                    __cg_p_metrics__m_wgtfacq_e[(i * (1)) + (j * (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8)) + (k * ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8)))] = p_metrics->wgtfacq_e[(i * (1)) + (j * (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8)) + (k * ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8; i++){
                                    __cg_p_metrics__m_coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8)))] = p_metrics->coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8)))];
                                }
                            }
                        }


                        __cg_p_diag__m_max_vcfl_dyn = p_diag->max_vcfl_dyn;

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vt_d_2_s_293_p_diag_9; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vt_d_0_s_291_p_diag_9; i++){
                                    __cg_p_diag__m_vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_291_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9)))] = p_diag->vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_291_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_ie_d_2_s_296_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_ie_d_0_s_294_p_diag_9; i++){
                                    __cg_p_diag__m_vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9)))] = p_diag->vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9; i++){
                                    __cg_p_diag__m_w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)))] = p_diag->w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto l = 0; l < __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9; l++){
                            for (auto k = 0; k < __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9; k++){
                                for (auto j = 0; j < 90; j++){
                                    #pragma omp simd
                                    for (auto i = 0; i < __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9; i++){
                                        __cg_p_diag__m_ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9)))] = p_diag->ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9)))];
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
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_global_data__m_nflatlev, __CG_global_data__m_nflatlev, 10 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_global_data__m_nrdmax, __CG_global_data__m_nrdmax, 10 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_diag__m_ddt_vn_apc_pc, __CG_p_diag__m_ddt_vn_apc_pc, (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_diag__m_vn_ie, __CG_p_diag__m_vn_ie, ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * __f2dace_SA_vn_ie_d_2_s_296_p_diag_9) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_diag__m_vt, __CG_p_diag__m_vt, ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * __f2dace_SA_vt_d_2_s_293_p_diag_9) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_diag__m_w_concorr_c, __CG_p_diag__m_w_concorr_c, ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_int__m_c_lin_e, __CG_p_int__m_c_lin_e, ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * __f2dace_SA_c_lin_e_d_2_s_27_p_int_6) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_int__m_e_bln_c_s, __CG_p_int__m_e_bln_c_s, ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_int__m_geofac_grdiv, __CG_p_int__m_geofac_grdiv, ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_int__m_geofac_rot, __CG_p_int__m_geofac_rot, ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * __f2dace_SA_geofac_rot_d_2_s_42_p_int_6) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_int__m_rbf_vec_coeff_e, __CG_p_int__m_rbf_vec_coeff_e, ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_coeff_gradekin, __CG_p_metrics__m_coeff_gradekin, ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_ddqz_z_full_e, __CG_p_metrics__m_ddqz_z_full_e, ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_ddqz_z_half, __CG_p_metrics__m_ddqz_z_half, ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_ddxn_z_full, __CG_p_metrics__m_ddxn_z_full, ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8) * __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_ddxt_z_full, __CG_p_metrics__m_ddxt_z_full, ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8) * __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_wgtfac_c, __CG_p_metrics__m_wgtfac_c, ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_wgtfac_e, __CG_p_metrics__m_wgtfac_e, ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_metrics__m_wgtfacq_e, __CG_p_metrics__m_wgtfacq_e, ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_edge_blk, __CG_p_patch__CG_cells__m_edge_blk, ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_edge_idx, __CG_p_patch__CG_cells__m_edge_idx, ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_end_block, __CG_p_patch__CG_cells__m_end_block, __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_end_index, __CG_p_patch__CG_cells__m_end_index, __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_start_block, __CG_p_patch__CG_cells__m_start_block, __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_cells__m_start_index, __CG_p_patch__CG_cells__m_start_index, __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_area_edge, __CG_p_patch__CG_edges__m_area_edge, (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_cell_blk, __CG_p_patch__CG_edges__m_cell_blk, ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_cell_idx, __CG_p_patch__CG_edges__m_cell_idx, ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_end_block, __CG_p_patch__CG_edges__m_end_block, __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_end_index, __CG_p_patch__CG_edges__m_end_index, __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_f_e, __CG_p_patch__CG_edges__m_f_e, (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, __CG_p_patch__CG_edges__m_inv_primal_edge_length, (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_quad_blk, __CG_p_patch__CG_edges__m_quad_blk, ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_quad_idx, __CG_p_patch__CG_edges__m_quad_idx, ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_start_block, __CG_p_patch__CG_edges__m_start_block, __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_start_index, __CG_p_patch__CG_edges__m_start_index, __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_tangent_orientation, __CG_p_patch__CG_edges__m_tangent_orientation, (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_vertex_blk, __CG_p_patch__CG_edges__m_vertex_blk, ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_edges__m_vertex_idx, __CG_p_patch__CG_edges__m_vertex_idx, ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_edge_blk, __CG_p_patch__CG_verts__m_edge_blk, ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_edge_idx, __CG_p_patch__CG_verts__m_edge_idx, ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5) * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_end_block, __CG_p_patch__CG_verts__m_end_block, __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_end_index, __CG_p_patch__CG_verts__m_end_index, __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_start_block, __CG_p_patch__CG_verts__m_start_block, __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_patch__CG_verts__m_start_index, __CG_p_patch__CG_verts__m_start_index, __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5 * sizeof(int), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_prog__m_vn, __CG_p_prog__m_vn, ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * __f2dace_SA_vn_d_2_s_290_p_prog_7) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu___CG_p_prog__m_w, __CG_p_prog__m_w, ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * __f2dace_SA_w_d_2_s_287_p_prog_7) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu_z_w_concorr_me, z_w_concorr_me, ((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * __f2dace_A_z_w_concorr_me_d_2_s_362) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu_z_kin_hor_e, z_kin_hor_e, ((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * __f2dace_A_z_kin_hor_e_d_2_s_365) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(gpu_z_vt_ie, z_vt_ie, ((__f2dace_A_z_vt_ie_d_0_s_366 * __f2dace_A_z_vt_ie_d_1_s_367) * __f2dace_A_z_vt_ie_d_2_s_368) * sizeof(double), cudaMemcpyHostToDevice, __state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }
   cudaDeviceSynchronize();
    measure_time("Run");
    cudaEvent_t start1, stop1;
    cudaEventCreate(&start1);
    cudaEventCreate(&stop1);
    cudaEventRecord(start1); 
    nrdmax_jg = __CG_global_data__m_nrdmax[0];
    nflatlev_jg = __CG_global_data__m_nflatlev[0];
    i_startblk_var_118_0 = __CG_p_patch__CG_verts__m_start_block[(2 - __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5)];
    i_endblk_var_119_0 = __CG_p_patch__CG_verts__m_end_block[((- __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5) - 5)];
    i_startblk_var_146 = __CG_p_patch__CG_edges__m_start_block[(5 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];
    i_endblk_var_147 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 10)];
    replaced_var_1 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];
    replaced_var_3 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 5)];
    replaced_var_4 = __CG_p_patch__CG_edges__m_start_block[(10 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];
    replaced_var_5 = __CG_p_patch__CG_edges__m_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 8)];

    {
        double cfl_w_limit;
        double scalfac_exdiff;

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
            for (auto _for_it_3_0 = i_startblk_var_118_0; _for_it_3_0 < (i_endblk_var_119_0 + 1); _for_it_3_0 += 1) {
                loop_body_0_0_5(__state, __CG_global_data__m_nproma, &gpu___CG_p_int__m_geofac_rot[0], &gpu___CG_p_patch__CG_verts__m_edge_blk[0], &gpu___CG_p_patch__CG_verts__m_edge_idx[0], &__CG_p_patch__CG_verts__m_end_index[0], &__CG_p_patch__CG_verts__m_start_index[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_zeta[0], _for_it_3_0, i_endblk_var_119_0, i_startblk_var_118_0, tmp_struct_symbol_8);
            }
        }
        {
            for (auto _for_it_6 = i_startblk_var_146; _for_it_6 < (i_endblk_var_147 + 1); _for_it_6 += 1) {
                loop_body_0_0_16(__state, __CG_global_data__m_nproma, &gpu___CG_p_int__m_rbf_vec_coeff_e[0], &gpu___CG_p_metrics__m_ddxn_z_full[0], &gpu___CG_p_metrics__m_ddxt_z_full[0], &gpu___CG_p_metrics__m_wgtfac_e[0], &gpu___CG_p_metrics__m_wgtfacq_e[0], &__CG_p_patch__CG_edges__m_end_index[0], &gpu___CG_p_patch__CG_edges__m_quad_blk[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_prog__m_vn[0], &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu_z_kin_hor_e[0], &gpu_z_vt_ie[0], &gpu_z_w_concorr_me[0], __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, _for_it_6, i_endblk_var_147, i_startblk_var_146, nflatlev_jg);
            }
        }
        {
            for (auto _for_it_22 = replaced_var_1; _for_it_22 < (replaced_var_3 + 1); _for_it_22 += 1) {
                loop_body_0_0_34(__state, __CG_global_data__m_nproma, cfl_w_limit, dtime, &gpu___CG_p_int__m_e_bln_c_s[0], &gpu___CG_p_metrics__m_ddqz_z_half[0], &gpu___CG_p_metrics__m_wgtfac_c[0], &gpu___CG_p_patch__CG_cells__m_edge_blk[0], &gpu___CG_p_patch__CG_cells__m_edge_idx[0], &__CG_p_patch__CG_cells__m_end_index[0], &__CG_p_patch__CG_cells__m_start_index[0], &gpu___CG_p_prog__m_w[0], &gpu_z_kin_hor_e[0], &gpu_z_w_concorr_me[0], &gpu___CG_p_diag__m_w_concorr_c[0], &__state->__0_gpu_cfl_clipping[0], &__state->__0_gpu_levmask[0], &__state->__0_gpu_maxvcfl_arr[0], &__state->__0_gpu_z_ekinh[0], &__state->__0_gpu_z_w_con_c[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_z_w_concorr_mc[0], &__state->__0_gpu_vcflmax[0], __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, _for_it_22, replaced_var_3, replaced_var_1, nflatlev_jg, nrdmax_jg, tmp_struct_symbol_0, tmp_struct_symbol_1, tmp_struct_symbol_10, tmp_struct_symbol_13, tmp_struct_symbol_14, tmp_struct_symbol_2, tmp_struct_symbol_4);
            }
        }
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));

        dace::CopyNDDynamic<double, 1, false, 1>::template ConstDst<1>::Copy(
        __state->__0_gpu_vcflmax, __state->__0_vcflmax, tmp_struct_symbol_12, 1);
        __dace_runkernel_GPU_DeviceMap_2_2_0_0_81(__state, __state->__0_gpu_levelmask, __state->__0_gpu_levmask, nrdmax_jg, replaced_var_1, replaced_var_3, tmp_struct_symbol_13);
        {
            for (auto _for_it_47 = replaced_var_4; _for_it_47 < (replaced_var_5 + 1); _for_it_47 += 1) {
                loop_body_0_0_64(__state, __CG_global_data__m_nproma, cfl_w_limit, dtime, &gpu___CG_p_diag__m_vn_ie[0], &gpu___CG_p_diag__m_vt[0], &gpu___CG_p_int__m_c_lin_e[0], &gpu___CG_p_int__m_geofac_grdiv[0], &gpu___CG_p_metrics__m_coeff_gradekin[0], &gpu___CG_p_metrics__m_ddqz_z_full_e[0], &gpu___CG_p_patch__CG_edges__m_area_edge[0], &gpu___CG_p_patch__CG_edges__m_cell_blk[0], &gpu___CG_p_patch__CG_edges__m_cell_idx[0], &__CG_p_patch__CG_edges__m_end_index[0], &gpu___CG_p_patch__CG_edges__m_f_e[0], &gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length[0], &gpu___CG_p_patch__CG_edges__m_quad_blk[0], &gpu___CG_p_patch__CG_edges__m_quad_idx[0], &__CG_p_patch__CG_edges__m_start_index[0], &gpu___CG_p_patch__CG_edges__m_tangent_orientation[0], &gpu___CG_p_patch__CG_edges__m_vertex_blk[0], &gpu___CG_p_patch__CG_edges__m_vertex_idx[0], &gpu___CG_p_prog__m_vn[0], &__state->__0_gpu_levelmask[0], &__state->__0_gpu_z_ekinh[0], &gpu_z_kin_hor_e[0], &__state->__0_gpu_z_w_con_c_full[0], &__state->__0_gpu_zeta[0], scalfac_exdiff, &gpu___CG_p_diag__m_ddt_vn_apc_pc[0], __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, _for_it_47, replaced_var_5, nrdmax_jg, ntnd, replaced_var_4, replaced_var_5, tmp_struct_symbol_10, tmp_struct_symbol_2, tmp_struct_symbol_8);
            }
        }


    }
    replaced_var_6 = __CG_p_patch__CG_cells__m_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];
    replaced_var_7 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];

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
  cudaEventRecord(stop1);
    cudaEventSynchronize(stop1);
    float milliseconds1 = 0;
    cudaEventElapsedTime(&milliseconds1, start1, stop1);
    std::cout << "Total time: " << milliseconds1 << " ms" << std::endl;
    cudaEventDestroy(start1);
    cudaEventDestroy(stop1);
    cudaDeviceSynchronize();
  measure_time("Run");

            ///////////////////
            // Tasklet code (T_l653_c653)
            p_diag_out_max_vcfl_dyn = max_vcfl_dyn_var_152_0_in;
            ///////////////////

            __CG_p_diag__m_max_vcfl_dyn = p_diag_out_max_vcfl_dyn;
        }
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_global_data__m_nflatlev, gpu___CG_global_data__m_nflatlev, 10 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_global_data__m_nrdmax, gpu___CG_global_data__m_nrdmax, 10 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_diag__m_ddt_vn_apc_pc, gpu___CG_p_diag__m_ddt_vn_apc_pc, (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_diag__m_vn_ie, gpu___CG_p_diag__m_vn_ie, ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * __f2dace_SA_vn_ie_d_2_s_296_p_diag_9) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_diag__m_vt, gpu___CG_p_diag__m_vt, ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * __f2dace_SA_vt_d_2_s_293_p_diag_9) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_diag__m_w_concorr_c, gpu___CG_p_diag__m_w_concorr_c, ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_int__m_c_lin_e, gpu___CG_p_int__m_c_lin_e, ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * __f2dace_SA_c_lin_e_d_2_s_27_p_int_6) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_int__m_e_bln_c_s, gpu___CG_p_int__m_e_bln_c_s, ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_int__m_geofac_grdiv, gpu___CG_p_int__m_geofac_grdiv, ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_int__m_geofac_rot, gpu___CG_p_int__m_geofac_rot, ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * __f2dace_SA_geofac_rot_d_2_s_42_p_int_6) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_int__m_rbf_vec_coeff_e, gpu___CG_p_int__m_rbf_vec_coeff_e, ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_coeff_gradekin, gpu___CG_p_metrics__m_coeff_gradekin, ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_ddqz_z_full_e, gpu___CG_p_metrics__m_ddqz_z_full_e, ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_ddqz_z_half, gpu___CG_p_metrics__m_ddqz_z_half, ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_ddxn_z_full, gpu___CG_p_metrics__m_ddxn_z_full, ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8) * __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_ddxt_z_full, gpu___CG_p_metrics__m_ddxt_z_full, ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8) * __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_wgtfac_c, gpu___CG_p_metrics__m_wgtfac_c, ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_wgtfac_e, gpu___CG_p_metrics__m_wgtfac_e, ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_metrics__m_wgtfacq_e, gpu___CG_p_metrics__m_wgtfacq_e, ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_edge_blk, gpu___CG_p_patch__CG_cells__m_edge_blk, ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_edge_idx, gpu___CG_p_patch__CG_cells__m_edge_idx, ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_end_block, gpu___CG_p_patch__CG_cells__m_end_block, __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_end_index, gpu___CG_p_patch__CG_cells__m_end_index, __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_start_block, gpu___CG_p_patch__CG_cells__m_start_block, __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_cells__m_start_index, gpu___CG_p_patch__CG_cells__m_start_index, __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_area_edge, gpu___CG_p_patch__CG_edges__m_area_edge, (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_cell_blk, gpu___CG_p_patch__CG_edges__m_cell_blk, ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_cell_idx, gpu___CG_p_patch__CG_edges__m_cell_idx, ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_end_block, gpu___CG_p_patch__CG_edges__m_end_block, __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_end_index, gpu___CG_p_patch__CG_edges__m_end_index, __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_f_e, gpu___CG_p_patch__CG_edges__m_f_e, (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_inv_primal_edge_length, gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length, (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_quad_blk, gpu___CG_p_patch__CG_edges__m_quad_blk, ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_quad_idx, gpu___CG_p_patch__CG_edges__m_quad_idx, ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_start_block, gpu___CG_p_patch__CG_edges__m_start_block, __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_start_index, gpu___CG_p_patch__CG_edges__m_start_index, __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_tangent_orientation, gpu___CG_p_patch__CG_edges__m_tangent_orientation, (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_vertex_blk, gpu___CG_p_patch__CG_edges__m_vertex_blk, ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_edges__m_vertex_idx, gpu___CG_p_patch__CG_edges__m_vertex_idx, ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_edge_blk, gpu___CG_p_patch__CG_verts__m_edge_blk, ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_edge_idx, gpu___CG_p_patch__CG_verts__m_edge_idx, ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5) * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_end_block, gpu___CG_p_patch__CG_verts__m_end_block, __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_end_index, gpu___CG_p_patch__CG_verts__m_end_index, __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_start_block, gpu___CG_p_patch__CG_verts__m_start_block, __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_patch__CG_verts__m_start_index, gpu___CG_p_patch__CG_verts__m_start_index, __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5 * sizeof(int), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_prog__m_vn, gpu___CG_p_prog__m_vn, ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * __f2dace_SA_vn_d_2_s_290_p_prog_7) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(__CG_p_prog__m_w, gpu___CG_p_prog__m_w, ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * __f2dace_SA_w_d_2_s_287_p_prog_7) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));
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
            double* __cg_p_int__m_rbf_vec_coeff_e = &__CG_p_int__m_rbf_vec_coeff_e[0];
            double* __cg_p_metrics__m_coeff_gradekin = &__CG_p_metrics__m_coeff_gradekin[0];
            double* __cg_p_metrics__m_ddqz_z_full_e = &__CG_p_metrics__m_ddqz_z_full_e[0];
            double* __cg_p_metrics__m_ddqz_z_half = &__CG_p_metrics__m_ddqz_z_half[0];
            double* __cg_p_metrics__m_ddxn_z_full = &__CG_p_metrics__m_ddxn_z_full[0];
            double* __cg_p_metrics__m_ddxt_z_full = &__CG_p_metrics__m_ddxt_z_full[0];
            double* __cg_p_metrics__m_wgtfac_c = &__CG_p_metrics__m_wgtfac_c[0];
            double* __cg_p_metrics__m_wgtfac_e = &__CG_p_metrics__m_wgtfac_e[0];
            double* __cg_p_metrics__m_wgtfacq_e = &__CG_p_metrics__m_wgtfacq_e[0];
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
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2; i++){
                                    p_patch->cells->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2)))] = __cg_p_patch__cg_cells__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2; i++){
                                    p_patch->cells->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2)))] = __cg_p_patch__cg_cells__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2)) + (k * ((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2; i++){
                            p_patch->cells->start_index[(i * (1))] = __cg_p_patch__cg_cells__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2; i++){
                            p_patch->cells->end_index[(i * (1))] = __cg_p_patch__cg_cells__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2; i++){
                            p_patch->cells->start_block[(i * (1))] = __cg_p_patch__cg_cells__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2; i++){
                            p_patch->cells->end_block[(i * (1))] = __cg_p_patch__cg_cells__m_end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4; i++){
                                    p_patch->edges->cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_cell_idx[(i * (1)) + (j * (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4; i++){
                                    p_patch->edges->cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_cell_blk[(i * (1)) + (j * (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4)) + (k * ((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4; i++){
                                    p_patch->edges->vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_vertex_idx[(i * (1)) + (j * (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4; i++){
                                    p_patch->edges->vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_vertex_blk[(i * (1)) + (j * (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4)) + (k * ((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4; i++){
                                p_patch->edges->tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_tangent_orientation[(i * (1)) + (j * (__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4))];
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4; i++){
                                    p_patch->edges->quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_quad_idx[(i * (1)) + (j * (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4; k++){
                            for (auto j = 0; j < __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4; i++){
                                    p_patch->edges->quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4)))] = __cg_p_patch__cg_edges__m_quad_blk[(i * (1)) + (j * (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4)) + (k * ((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4)))];
                                }
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4; i++){
                                p_patch->edges->inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_inv_primal_edge_length[(i * (1)) + (j * (__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4; i++){
                                p_patch->edges->area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_area_edge[(i * (1)) + (j * (__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4))];
                            }
                        }


                        for (auto j = 0; j < __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4; j++){
                            #pragma omp simd
                            for (auto i = 0; i < __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4; i++){
                                p_patch->edges->f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4))] = __cg_p_patch__cg_edges__m_f_e[(i * (1)) + (j * (__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4))];
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4; i++){
                            p_patch->edges->start_index[(i * (1))] = __cg_p_patch__cg_edges__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4; i++){
                            p_patch->edges->end_index[(i * (1))] = __cg_p_patch__cg_edges__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4; i++){
                            p_patch->edges->start_block[(i * (1))] = __cg_p_patch__cg_edges__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4; i++){
                            p_patch->edges->end_block[(i * (1))] = __cg_p_patch__cg_edges__m_end_block[(i * (1))];
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5; i++){
                                    p_patch->verts->edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5)))] = __cg_p_patch__cg_verts__m_edge_idx[(i * (1)) + (j * (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5; k++){
                            for (auto j = 0; j < __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5; i++){
                                    p_patch->verts->edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5)))] = __cg_p_patch__cg_verts__m_edge_blk[(i * (1)) + (j * (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5)) + (k * ((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5)))];
                                }
                            }
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5; i++){
                            p_patch->verts->start_index[(i * (1))] = __cg_p_patch__cg_verts__m_start_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5; i++){
                            p_patch->verts->end_index[(i * (1))] = __cg_p_patch__cg_verts__m_end_index[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5; i++){
                            p_patch->verts->start_block[(i * (1))] = __cg_p_patch__cg_verts__m_start_block[(i * (1))];
                        }

                        #pragma omp simd
                        for (auto i = 0; i < __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5; i++){
                            p_patch->verts->end_block[(i * (1))] = __cg_p_patch__cg_verts__m_end_block[(i * (1))];
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_c_lin_e_d_2_s_27_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_c_lin_e_d_1_s_26_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_c_lin_e_d_0_s_25_p_int_6; i++){
                                    p_int->c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6)))] = __cg_p_int__m_c_lin_e[(i * (1)) + (j * (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6)) + (k * ((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6; i++){
                                    p_int->e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6)))] = __cg_p_int__m_e_bln_c_s[(i * (1)) + (j * (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6)) + (k * ((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6; i++){
                                    p_int->rbf_vec_coeff_e[(i * (1)) + (j * (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6)) + (k * ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6)))] = __cg_p_int__m_rbf_vec_coeff_e[(i * (1)) + (j * (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6)) + (k * ((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6; i++){
                                    p_int->geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6)))] = __cg_p_int__m_geofac_grdiv[(i * (1)) + (j * (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6)) + (k * ((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_geofac_rot_d_2_s_42_p_int_6; k++){
                            for (auto j = 0; j < __f2dace_SA_geofac_rot_d_1_s_41_p_int_6; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_geofac_rot_d_0_s_40_p_int_6; i++){
                                    p_int->geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6)))] = __cg_p_int__m_geofac_rot[(i * (1)) + (j * (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6)) + (k * ((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_d_2_s_287_p_prog_7; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_d_0_s_285_p_prog_7; i++){
                                    p_prog->w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_285_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7)))] = __cg_p_prog__m_w[(i * (1)) + (j * (__f2dace_SA_w_d_0_s_285_p_prog_7)) + (k * ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_d_2_s_290_p_prog_7; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_d_0_s_288_p_prog_7; i++){
                                    p_prog->vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_288_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7)))] = __cg_p_prog__m_vn[(i * (1)) + (j * (__f2dace_SA_vn_d_0_s_288_p_prog_7)) + (k * ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7)))];
                                }
                            }
                        }


                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8; i++){
                                    p_metrics->ddxn_z_full[(i * (1)) + (j * (__f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)))] = __cg_p_metrics__m_ddxn_z_full[(i * (1)) + (j * (__f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8; i++){
                                    p_metrics->ddxt_z_full[(i * (1)) + (j * (__f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)))] = __cg_p_metrics__m_ddxt_z_full[(i * (1)) + (j * (__f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8; i++){
                                    p_metrics->ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)))] = __cg_p_metrics__m_ddqz_z_full_e[(i * (1)) + (j * (__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)) + (k * ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8; i++){
                                    p_metrics->ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)))] = __cg_p_metrics__m_ddqz_z_half[(i * (1)) + (j * (__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)) + (k * ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8; i++){
                                    p_metrics->wgtfac_c[(i * (1)) + (j * (__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)))] = __cg_p_metrics__m_wgtfac_c[(i * (1)) + (j * (__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8; i++){
                                    p_metrics->wgtfac_e[(i * (1)) + (j * (__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)))] = __cg_p_metrics__m_wgtfac_e[(i * (1)) + (j * (__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)) + (k * ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8; i++){
                                    p_metrics->wgtfacq_e[(i * (1)) + (j * (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8)) + (k * ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8)))] = __cg_p_metrics__m_wgtfacq_e[(i * (1)) + (j * (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8)) + (k * ((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8; k++){
                            for (auto j = 0; j < __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8; i++){
                                    p_metrics->coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8)))] = __cg_p_metrics__m_coeff_gradekin[(i * (1)) + (j * (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8)) + (k * ((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8)))];
                                }
                            }
                        }


                        p_diag->max_vcfl_dyn = __cg_p_diag__m_max_vcfl_dyn;

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vt_d_2_s_293_p_diag_9; k++){
                            for (auto j = 0; j < 90; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vt_d_0_s_291_p_diag_9; i++){
                                    p_diag->vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_291_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9)))] = __cg_p_diag__m_vt[(i * (1)) + (j * (__f2dace_SA_vt_d_0_s_291_p_diag_9)) + (k * ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_vn_ie_d_2_s_296_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_vn_ie_d_0_s_294_p_diag_9; i++){
                                    p_diag->vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9)))] = __cg_p_diag__m_vn_ie[(i * (1)) + (j * (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9)) + (k * ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto k = 0; k < __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9; k++){
                            for (auto j = 0; j < 91; j++){
                                #pragma omp simd
                                for (auto i = 0; i < __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9; i++){
                                    p_diag->w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)))] = __cg_p_diag__m_w_concorr_c[(i * (1)) + (j * (__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)) + (k * ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9)))];
                                }
                            }
                        }

                        #pragma omp parallel for
                        for (auto l = 0; l < __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9; l++){
                            for (auto k = 0; k < __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9; k++){
                                for (auto j = 0; j < 90; j++){
                                    #pragma omp simd
                                    for (auto i = 0; i < __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9; i++){
                                        p_diag->ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9)))] = __cg_p_diag__m_ddt_vn_apc_pc[(i * (1)) + (j * (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9)) + (k * ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9))) + (l * (((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9)))];
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
        DACE_GPU_CHECK(cudaMemcpyAsync(z_w_concorr_me, gpu_z_w_concorr_me, ((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * __f2dace_A_z_w_concorr_me_d_2_s_362) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(z_kin_hor_e, gpu_z_kin_hor_e, ((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * __f2dace_A_z_kin_hor_e_d_2_s_365) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
        DACE_GPU_CHECK(cudaMemcpyAsync(z_vt_ie, gpu_z_vt_ie, ((__f2dace_A_z_vt_ie_d_0_s_366 * __f2dace_A_z_vt_ie_d_1_s_367) * __f2dace_A_z_vt_ie_d_2_s_368) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));
//        DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));


    }

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
    delete[] __CG_p_int__m_rbf_vec_coeff_e;
    delete[] __CG_p_int__m_geofac_grdiv;
    delete[] __CG_p_int__m_geofac_rot;
    delete[] __CG_p_prog__m_w;
    delete[] __CG_p_prog__m_vn;
    delete[] __CG_p_metrics__m_ddxn_z_full;
    delete[] __CG_p_metrics__m_ddxt_z_full;
    delete[] __CG_p_metrics__m_ddqz_z_full_e;
    delete[] __CG_p_metrics__m_ddqz_z_half;
    delete[] __CG_p_metrics__m_wgtfac_c;
    delete[] __CG_p_metrics__m_wgtfac_e;
    delete[] __CG_p_metrics__m_wgtfacq_e;
    delete[] __CG_p_metrics__m_coeff_gradekin;
    delete[] __CG_p_diag__m_vt;
    delete[] __CG_p_diag__m_vn_ie;
    delete[] __CG_p_diag__m_w_concorr_c;
    delete[] __CG_p_diag__m_ddt_vn_apc_pc;
    DACE_GPU_CHECK(cudaFree(gpu___CG_global_data__m_nflatlev));
    DACE_GPU_CHECK(cudaFree(gpu___CG_global_data__m_nrdmax));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_diag__m_ddt_vn_apc_pc));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_diag__m_vn_ie));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_diag__m_vt));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_diag__m_w_concorr_c));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_int__m_c_lin_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_int__m_e_bln_c_s));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_int__m_geofac_grdiv));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_int__m_geofac_rot));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_int__m_rbf_vec_coeff_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_coeff_gradekin));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_ddqz_z_full_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_ddqz_z_half));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_ddxn_z_full));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_ddxt_z_full));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_wgtfac_c));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_wgtfac_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_metrics__m_wgtfacq_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_edge_blk));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_edge_idx));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_end_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_end_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_start_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_cells__m_start_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_area_edge));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_cell_blk));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_cell_idx));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_end_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_end_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_f_e));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_inv_primal_edge_length));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_quad_blk));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_quad_idx));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_start_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_start_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_tangent_orientation));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_vertex_blk));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_edges__m_vertex_idx));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_edge_blk));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_edge_idx));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_end_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_end_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_start_block));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_patch__CG_verts__m_start_index));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_prog__m_vn));
    DACE_GPU_CHECK(cudaFree(gpu___CG_p_prog__m_w));
    DACE_GPU_CHECK(cudaFree(gpu_z_kin_hor_e));
    DACE_GPU_CHECK(cudaFree(gpu_z_vt_ie));
    DACE_GPU_CHECK(cudaFree(gpu_z_w_concorr_me));
}

DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_kin_hor_e_d_2_s_365, __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_A_z_vt_ie_d_2_s_368, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_A_z_w_concorr_me_d_2_s_362, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}
DACE_EXPORTED int __dace_init_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd);
DACE_EXPORTED int __dace_exit_cuda_2(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state);

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_kin_hor_e_d_2_s_365, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_vt_ie_d_2_s_368, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_A_z_w_concorr_me_d_2_s_362, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state = new velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t;


    __result |= __dace_init_cuda_2(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_kin_hor_e_d_2_s_365, __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_A_z_vt_ie_d_2_s_368, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_A_z_w_concorr_me_d_2_s_362, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
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
    __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_0_s_146;
    __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_1_s_147;
    __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_idx_d_2_s_148;
    __f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_0_s_146;
    __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_1_s_147;
    __f2dace_SA_neighbor_idx_d_2_s_148_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_idx_d_2_s_148;
    __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_0_s_149;
    __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_1_s_150;
    __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_neighbor_blk_d_2_s_151;
    __f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_0_s_149;
    __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_1_s_150;
    __f2dace_SA_neighbor_blk_d_2_s_151_cells_p_patch_2 = p_patch->cells->__f2dace_SA_neighbor_blk_d_2_s_151;
    __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_0_s_152;
    __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_1_s_153;
    __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_idx_d_2_s_154;
    __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_0_s_152;
    __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_1_s_153;
    __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_idx_d_2_s_154;
    __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_0_s_155;
    __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_1_s_156;
    __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_edge_blk_d_2_s_157;
    __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_0_s_155;
    __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_1_s_156;
    __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2 = p_patch->cells->__f2dace_SA_edge_blk_d_2_s_157;
    __f2dace_SOA_area_d_0_s_158_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_area_d_0_s_158;
    __f2dace_SOA_area_d_1_s_159_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_area_d_1_s_159;
    __f2dace_SA_area_d_0_s_158_cells_p_patch_2 = p_patch->cells->__f2dace_SA_area_d_0_s_158;
    __f2dace_SA_area_d_1_s_159_cells_p_patch_2 = p_patch->cells->__f2dace_SA_area_d_1_s_159;
    __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_start_index_d_0_s_160;
    __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2 = p_patch->cells->__f2dace_SA_start_index_d_0_s_160;
    __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_end_index_d_0_s_161;
    __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2 = p_patch->cells->__f2dace_SA_end_index_d_0_s_161;
    __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_start_block_d_0_s_162;
    __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2 = p_patch->cells->__f2dace_SA_start_block_d_0_s_162;
    __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2 = p_patch->cells->__f2dace_SOA_end_block_d_0_s_163;
    __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2 = p_patch->cells->__f2dace_SA_end_block_d_0_s_163;
    __f2dace_SOA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SOA_owner_mask_d_0_s_2;
    __f2dace_SOA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SOA_owner_mask_d_1_s_3;
    __f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SA_owner_mask_d_0_s_2;
    __f2dace_SA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3 = p_patch->cells->decomp_info->__f2dace_SA_owner_mask_d_1_s_3;
    __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_0_s_164;
    __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_1_s_165;
    __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_idx_d_2_s_166;
    __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_0_s_164;
    __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_1_s_165;
    __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_idx_d_2_s_166;
    __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_0_s_167;
    __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_1_s_168;
    __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_cell_blk_d_2_s_169;
    __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_0_s_167;
    __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_1_s_168;
    __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4 = p_patch->edges->__f2dace_SA_cell_blk_d_2_s_169;
    __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_0_s_170;
    __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_1_s_171;
    __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_idx_d_2_s_172;
    __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_0_s_170;
    __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_1_s_171;
    __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_idx_d_2_s_172;
    __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_0_s_173;
    __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_1_s_174;
    __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_vertex_blk_d_2_s_175;
    __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_0_s_173;
    __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_1_s_174;
    __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4 = p_patch->edges->__f2dace_SA_vertex_blk_d_2_s_175;
    __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_tangent_orientation_d_0_s_176;
    __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_tangent_orientation_d_1_s_177;
    __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 = p_patch->edges->__f2dace_SA_tangent_orientation_d_0_s_176;
    __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4 = p_patch->edges->__f2dace_SA_tangent_orientation_d_1_s_177;
    __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_0_s_178;
    __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_1_s_179;
    __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_idx_d_2_s_180;
    __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_0_s_178;
    __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_1_s_179;
    __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_idx_d_2_s_180;
    __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_0_s_181;
    __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_1_s_182;
    __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_quad_blk_d_2_s_183;
    __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_0_s_181;
    __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_1_s_182;
    __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4 = p_patch->edges->__f2dace_SA_quad_blk_d_2_s_183;
    __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_primal_edge_length_d_0_s_184;
    __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_primal_edge_length_d_1_s_185;
    __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_primal_edge_length_d_0_s_184;
    __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_primal_edge_length_d_1_s_185;
    __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_dual_edge_length_d_0_s_186;
    __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_inv_dual_edge_length_d_1_s_187;
    __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_dual_edge_length_d_0_s_186;
    __f2dace_SA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4 = p_patch->edges->__f2dace_SA_inv_dual_edge_length_d_1_s_187;
    __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_area_edge_d_0_s_188;
    __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_area_edge_d_1_s_189;
    __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 = p_patch->edges->__f2dace_SA_area_edge_d_0_s_188;
    __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4 = p_patch->edges->__f2dace_SA_area_edge_d_1_s_189;
    __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_f_e_d_0_s_190;
    __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_f_e_d_1_s_191;
    __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 = p_patch->edges->__f2dace_SA_f_e_d_0_s_190;
    __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4 = p_patch->edges->__f2dace_SA_f_e_d_1_s_191;
    __f2dace_SOA_fn_e_d_0_s_192_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_fn_e_d_0_s_192;
    __f2dace_SOA_fn_e_d_1_s_193_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_fn_e_d_1_s_193;
    __f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4 = p_patch->edges->__f2dace_SA_fn_e_d_0_s_192;
    __f2dace_SA_fn_e_d_1_s_193_edges_p_patch_4 = p_patch->edges->__f2dace_SA_fn_e_d_1_s_193;
    __f2dace_SOA_ft_e_d_0_s_194_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_ft_e_d_0_s_194;
    __f2dace_SOA_ft_e_d_1_s_195_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_ft_e_d_1_s_195;
    __f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4 = p_patch->edges->__f2dace_SA_ft_e_d_0_s_194;
    __f2dace_SA_ft_e_d_1_s_195_edges_p_patch_4 = p_patch->edges->__f2dace_SA_ft_e_d_1_s_195;
    __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_start_index_d_0_s_196;
    __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4 = p_patch->edges->__f2dace_SA_start_index_d_0_s_196;
    __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_end_index_d_0_s_197;
    __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4 = p_patch->edges->__f2dace_SA_end_index_d_0_s_197;
    __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_start_block_d_0_s_198;
    __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4 = p_patch->edges->__f2dace_SA_start_block_d_0_s_198;
    __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4 = p_patch->edges->__f2dace_SOA_end_block_d_0_s_199;
    __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4 = p_patch->edges->__f2dace_SA_end_block_d_0_s_199;
    __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_0_s_200;
    __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_1_s_201;
    __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_idx_d_2_s_202;
    __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_0_s_200;
    __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_1_s_201;
    __f2dace_SA_cell_idx_d_2_s_202_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_idx_d_2_s_202;
    __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_0_s_203;
    __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_1_s_204;
    __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_cell_blk_d_2_s_205;
    __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_0_s_203;
    __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_1_s_204;
    __f2dace_SA_cell_blk_d_2_s_205_verts_p_patch_5 = p_patch->verts->__f2dace_SA_cell_blk_d_2_s_205;
    __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_0_s_206;
    __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_1_s_207;
    __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_idx_d_2_s_208;
    __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_0_s_206;
    __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_1_s_207;
    __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_idx_d_2_s_208;
    __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_0_s_209;
    __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_1_s_210;
    __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_edge_blk_d_2_s_211;
    __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_0_s_209;
    __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_1_s_210;
    __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5 = p_patch->verts->__f2dace_SA_edge_blk_d_2_s_211;
    __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_start_index_d_0_s_212;
    __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5 = p_patch->verts->__f2dace_SA_start_index_d_0_s_212;
    __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_end_index_d_0_s_213;
    __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5 = p_patch->verts->__f2dace_SA_end_index_d_0_s_213;
    __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_start_block_d_0_s_214;
    __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5 = p_patch->verts->__f2dace_SA_start_block_d_0_s_214;
    __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5 = p_patch->verts->__f2dace_SOA_end_block_d_0_s_215;
    __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5 = p_patch->verts->__f2dace_SA_end_block_d_0_s_215;
    __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_0_s_25;
    __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_1_s_26;
    __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6 = p_int->__f2dace_SOA_c_lin_e_d_2_s_27;
    __f2dace_SA_c_lin_e_d_0_s_25_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_0_s_25;
    __f2dace_SA_c_lin_e_d_1_s_26_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_1_s_26;
    __f2dace_SA_c_lin_e_d_2_s_27_p_int_6 = p_int->__f2dace_SA_c_lin_e_d_2_s_27;
    __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_0_s_28;
    __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_1_s_29;
    __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6 = p_int->__f2dace_SOA_e_bln_c_s_d_2_s_30;
    __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_0_s_28;
    __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_1_s_29;
    __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6 = p_int->__f2dace_SA_e_bln_c_s_d_2_s_30;
    __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_0_s_31;
    __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_1_s_32;
    __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6 = p_int->__f2dace_SOA_cells_aw_verts_d_2_s_33;
    __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_0_s_31;
    __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_1_s_32;
    __f2dace_SA_cells_aw_verts_d_2_s_33_p_int_6 = p_int->__f2dace_SA_cells_aw_verts_d_2_s_33;
    __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_0_s_34;
    __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_1_s_35;
    __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6 = p_int->__f2dace_SOA_rbf_vec_coeff_e_d_2_s_36;
    __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_0_s_34;
    __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_1_s_35;
    __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6 = p_int->__f2dace_SA_rbf_vec_coeff_e_d_2_s_36;
    __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_0_s_37;
    __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_1_s_38;
    __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6 = p_int->__f2dace_SOA_geofac_grdiv_d_2_s_39;
    __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_0_s_37;
    __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_1_s_38;
    __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6 = p_int->__f2dace_SA_geofac_grdiv_d_2_s_39;
    __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_0_s_40;
    __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_1_s_41;
    __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6 = p_int->__f2dace_SOA_geofac_rot_d_2_s_42;
    __f2dace_SA_geofac_rot_d_0_s_40_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_0_s_40;
    __f2dace_SA_geofac_rot_d_1_s_41_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_1_s_41;
    __f2dace_SA_geofac_rot_d_2_s_42_p_int_6 = p_int->__f2dace_SA_geofac_rot_d_2_s_42;
    __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_0_s_43;
    __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_1_s_44;
    __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6 = p_int->__f2dace_SOA_geofac_n2s_d_2_s_45;
    __f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_0_s_43;
    __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_1_s_44;
    __f2dace_SA_geofac_n2s_d_2_s_45_p_int_6 = p_int->__f2dace_SA_geofac_n2s_d_2_s_45;
    __f2dace_SOA_w_d_0_s_285_p_prog_7 = p_prog->__f2dace_SOA_w_d_0_s_285;
    __f2dace_SOA_w_d_1_s_286_p_prog_7 = p_prog->__f2dace_SOA_w_d_1_s_286;
    __f2dace_SOA_w_d_2_s_287_p_prog_7 = p_prog->__f2dace_SOA_w_d_2_s_287;
    __f2dace_SA_w_d_0_s_285_p_prog_7 = p_prog->__f2dace_SA_w_d_0_s_285;
    __f2dace_SA_w_d_2_s_287_p_prog_7 = p_prog->__f2dace_SA_w_d_2_s_287;
    __f2dace_SOA_vn_d_0_s_288_p_prog_7 = p_prog->__f2dace_SOA_vn_d_0_s_288;
    __f2dace_SOA_vn_d_1_s_289_p_prog_7 = p_prog->__f2dace_SOA_vn_d_1_s_289;
    __f2dace_SOA_vn_d_2_s_290_p_prog_7 = p_prog->__f2dace_SOA_vn_d_2_s_290;
    __f2dace_SA_vn_d_0_s_288_p_prog_7 = p_prog->__f2dace_SA_vn_d_0_s_288;
    __f2dace_SA_vn_d_2_s_290_p_prog_7 = p_prog->__f2dace_SA_vn_d_2_s_290;
    __f2dace_SOA_ddxn_z_full_d_0_s_308_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_0_s_308;
    __f2dace_SOA_ddxn_z_full_d_1_s_309_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_1_s_309;
    __f2dace_SOA_ddxn_z_full_d_2_s_310_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_2_s_310;
    __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_0_s_308;
    __f2dace_SA_ddxn_z_full_d_2_s_310_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_2_s_310;
    __f2dace_SOA_ddxt_z_full_d_0_s_311_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_0_s_311;
    __f2dace_SOA_ddxt_z_full_d_1_s_312_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_1_s_312;
    __f2dace_SOA_ddxt_z_full_d_2_s_313_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_2_s_313;
    __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_0_s_311;
    __f2dace_SA_ddxt_z_full_d_2_s_313_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_2_s_313;
    __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_0_s_314;
    __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_1_s_315;
    __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_2_s_316;
    __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_0_s_314;
    __f2dace_SA_ddqz_z_full_e_d_2_s_316_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_2_s_316;
    __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_0_s_317;
    __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_1_s_318;
    __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_2_s_319;
    __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_0_s_317;
    __f2dace_SA_ddqz_z_half_d_2_s_319_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_2_s_319;
    __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_0_s_320;
    __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_1_s_321;
    __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_2_s_322;
    __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_0_s_320;
    __f2dace_SA_wgtfac_c_d_2_s_322_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_2_s_322;
    __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_0_s_323;
    __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_1_s_324;
    __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_2_s_325;
    __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_0_s_323;
    __f2dace_SA_wgtfac_e_d_2_s_325_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_2_s_325;
    __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_0_s_326;
    __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_1_s_327;
    __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_2_s_328;
    __f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_0_s_326;
    __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_1_s_327;
    __f2dace_SA_wgtfacq_e_d_2_s_328_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_2_s_328;
    __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_0_s_329;
    __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_1_s_330;
    __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_2_s_331;
    __f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_0_s_329;
    __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_1_s_330;
    __f2dace_SA_coeff_gradekin_d_2_s_331_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_2_s_331;
    __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_0_s_332;
    __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_1_s_333;
    __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_2_s_334;
    __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_0_s_332;
    __f2dace_SA_coeff1_dwdz_d_2_s_334_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_2_s_334;
    __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_0_s_335;
    __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_1_s_336;
    __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_2_s_337;
    __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_0_s_335;
    __f2dace_SA_coeff2_dwdz_d_2_s_337_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_2_s_337;
    __f2dace_SOA_deepatmo_gradh_mc_d_0_s_338_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_338;
    __f2dace_SOA_deepatmo_invr_mc_d_0_s_339_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_mc_d_0_s_339;
    __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_340_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_340;
    __f2dace_SOA_deepatmo_invr_ifc_d_0_s_341_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_341;
    __f2dace_SOA_vt_d_0_s_291_p_diag_9 = p_diag->__f2dace_SOA_vt_d_0_s_291;
    __f2dace_SOA_vt_d_1_s_292_p_diag_9 = p_diag->__f2dace_SOA_vt_d_1_s_292;
    __f2dace_SOA_vt_d_2_s_293_p_diag_9 = p_diag->__f2dace_SOA_vt_d_2_s_293;
    __f2dace_SA_vt_d_0_s_291_p_diag_9 = p_diag->__f2dace_SA_vt_d_0_s_291;
    __f2dace_SA_vt_d_2_s_293_p_diag_9 = p_diag->__f2dace_SA_vt_d_2_s_293;
    __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_0_s_294;
    __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_1_s_295;
    __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_2_s_296;
    __f2dace_SA_vn_ie_d_0_s_294_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_0_s_294;
    __f2dace_SA_vn_ie_d_2_s_296_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_2_s_296;
    __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_0_s_297;
    __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_1_s_298;
    __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_2_s_299;
    __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_0_s_297;
    __f2dace_SA_w_concorr_c_d_2_s_299_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_2_s_299;
    __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_300;
    __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_301;
    __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_302;
    __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_303;
    __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_0_s_300;
    __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_2_s_302;
    __f2dace_SA_ddt_vn_apc_pc_d_3_s_303_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_3_s_303;
    __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_0_s_304;
    __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_1_s_305;
    __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_2_s_306;
    __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_3_s_307;
    __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_0_s_304;
    __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_2_s_306;
    __f2dace_SA_ddt_w_adv_pc_d_3_s_307_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_3_s_307;
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_con_c_full, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_maxvcfl_arr, (((88 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (88 * tmp_struct_symbol_4)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMemset(__state->__0_gpu_maxvcfl_arr, 0, (((88 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (88 * tmp_struct_symbol_4)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_levmask, (90 * tmp_struct_symbol_13) * sizeof(int)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_levelmask, 90 * sizeof(int)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_concorr_mc, (((90 * tmp_struct_symbol_0) * (tmp_struct_symbol_5 - 1)) + (90 * tmp_struct_symbol_0)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_ekinh, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_zeta, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_cfl_clipping, (91 * tmp_struct_symbol_14) * sizeof(int)));
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__0_gpu_z_w_con_c, (((91 * tmp_struct_symbol_1) * (tmp_struct_symbol_5 - 1)) + (91 * tmp_struct_symbol_1)) * sizeof(double)));
    __state->__0_gpu_vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_12];
    __state->__0_vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_12];
    DACE_GPU_CHECK(cudaMalloc((void**)&__state->__16_out_val_0, 89 * sizeof(int)));

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state)
{
    int __err = 0;
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_con_c_full));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_maxvcfl_arr));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_levmask));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_levelmask));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_concorr_mc));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_ekinh));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_zeta));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_cfl_clipping));
    DACE_GPU_CHECK(cudaFree(__state->__0_gpu_z_w_con_c));
    delete[] __state->__0_gpu_vcflmax;
    delete[] __state->__0_vcflmax;
    DACE_GPU_CHECK(cudaFree(__state->__16_out_val_0));

    int __err_cuda = __dace_exit_cuda_2(__state);
    if (__err_cuda) {
        __err = __err_cuda;
    }
    delete __state;
    return __err;
}
