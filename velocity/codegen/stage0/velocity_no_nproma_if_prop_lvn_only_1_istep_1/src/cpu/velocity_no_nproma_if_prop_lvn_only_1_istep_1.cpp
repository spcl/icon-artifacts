#include "reductions_cpu.h"
#include "timer.h"
/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

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
void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1_internal(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double *z_w_concorr_mc;
    z_w_concorr_mc = new double DACE_ALIGN(64)[(90 * tmp_struct_symbol_0)];
    double *z_w_con_c;
    z_w_con_c = new double DACE_ALIGN(64)[(91 * tmp_struct_symbol_1)];
    double *z_w_con_c_full;
    z_w_con_c_full = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2))];
    double *zeta;
    zeta = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8))];
    double *z_ekinh;
    z_ekinh = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10))];
    double cfl_w_limit;
    double vcfl;
    double maxvcfl;
    double *vcflmax;
    vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_12];
    double w_con_e;
    double scalfac_exdiff;
    double difcoef;
    int nrdmax_jg;
    int nflatlev_jg;
    int *levmask;
    levmask = new int DACE_ALIGN(64)[(90 * tmp_struct_symbol_13)];
    int *levelmask;
    levelmask = new int DACE_ALIGN(64)[90];
    int *cfl_clipping;
    cfl_clipping = new int DACE_ALIGN(64)[(91 * tmp_struct_symbol_14)];
    double tmp_call_2;
    double tmp_call_11;
    double tmp_call_17;
    int _if_cond_16;
    double _if_cond_29;
    t_grid_edges** v_p_patch_edges;
    v_p_patch_edges = (t_grid_edges**)(&(p_patch->edges));
    t_grid_cells** v_p_patch_cells;
    v_p_patch_cells = (t_grid_cells**)(&(p_patch->cells));
    double* v_p_prog_vn;
    v_p_prog_vn = (double*)(&(p_prog->vn)[0]);
    double* v_p_diag_vt;
    v_p_diag_vt = (double*)(&(p_diag->vt)[0]);
    double* v_p_diag_vn_ie;
    v_p_diag_vn_ie = (double*)(&(p_diag->vn_ie)[0]);
    double* v_p_prog_w;
    v_p_prog_w = (double*)(&(p_prog->w)[0]);
    double* v_p_int_e_bln_c_s;
    v_p_int_e_bln_c_s = (double*)(&(p_int->e_bln_c_s)[0]);
    double* v_p_diag_w_concorr_c;
    v_p_diag_w_concorr_c = (double*)(&(p_diag->w_concorr_c)[0]);
    double* v_p_metrics_ddqz_z_half;
    v_p_metrics_ddqz_z_half = (double*)(&(p_metrics->ddqz_z_half)[0]);
    double* v_p_diag_ddt_w_adv_pc;
    v_p_diag_ddt_w_adv_pc = (double*)(&(p_diag->ddt_w_adv_pc)[0]);
    double* v_p_int_c_lin_e;
    v_p_int_c_lin_e = (double*)(&(p_int->c_lin_e)[0]);
    double* v_p_metrics_ddqz_z_full_e;
    v_p_metrics_ddqz_z_full_e = (double*)(&(p_metrics->ddqz_z_full_e)[0]);
    double* v_p_diag_ddt_vn_apc_pc;
    v_p_diag_ddt_vn_apc_pc = (double*)(&(p_diag->ddt_vn_apc_pc)[0]);
    int* v_v_p_patch_edges_start_block;
    v_v_p_patch_edges_start_block = (int*)(&((*v_p_patch_edges)->start_block)[0]);
    int* v_v_p_patch_edges_end_block;
    v_v_p_patch_edges_end_block = (int*)(&((*v_p_patch_edges)->end_block)[0]);
    int* v_v_p_patch_cells_start_block;
    v_v_p_patch_cells_start_block = (int*)(&((*v_p_patch_cells)->start_block)[0]);
    int* v_v_p_patch_cells_end_block;
    v_v_p_patch_cells_end_block = (int*)(&((*v_p_patch_cells)->end_block)[0]);
    int* v_v_p_patch_edges_quad_idx;
    v_v_p_patch_edges_quad_idx = (int*)(&((*v_p_patch_edges)->quad_idx)[0]);
    int* v_v_p_patch_edges_quad_blk;
    v_v_p_patch_edges_quad_blk = (int*)(&((*v_p_patch_edges)->quad_blk)[0]);
    int* v_v_p_patch_edges_cell_idx;
    v_v_p_patch_edges_cell_idx = (int*)(&((*v_p_patch_edges)->cell_idx)[0]);
    int* v_v_p_patch_edges_cell_blk;
    v_v_p_patch_edges_cell_blk = (int*)(&((*v_p_patch_edges)->cell_blk)[0]);
    int* v_v_p_patch_edges_vertex_idx;
    v_v_p_patch_edges_vertex_idx = (int*)(&((*v_p_patch_edges)->vertex_idx)[0]);
    int* v_v_p_patch_edges_vertex_blk;
    v_v_p_patch_edges_vertex_blk = (int*)(&((*v_p_patch_edges)->vertex_blk)[0]);
    int* v_v_p_patch_cells_edge_idx;
    v_v_p_patch_cells_edge_idx = (int*)(&((*v_p_patch_cells)->edge_idx)[0]);
    int* v_v_p_patch_cells_edge_blk;
    v_v_p_patch_cells_edge_blk = (int*)(&((*v_p_patch_cells)->edge_blk)[0]);
    t_grid_domain_decomp_info** v_v_p_patch_cells_decomp_info;
    v_v_p_patch_cells_decomp_info = (t_grid_domain_decomp_info**)(&((*v_p_patch_cells)->decomp_info));
    int* v_v_p_patch_cells_neighbor_idx;
    v_v_p_patch_cells_neighbor_idx = (int*)(&((*v_p_patch_cells)->neighbor_idx)[0]);
    int* v_v_p_patch_cells_neighbor_blk;
    v_v_p_patch_cells_neighbor_blk = (int*)(&((*v_p_patch_cells)->neighbor_blk)[0]);
    int* v_v_v_p_patch_cells_decomp_info_owner_mask;
    v_v_v_p_patch_cells_decomp_info_owner_mask = (int*)(&((*v_v_p_patch_cells_decomp_info)->owner_mask)[0]);
    global_data_type** global_data_var_81_0;
    global_data_var_81_0 = &global_data;
    int* global_data_var_81_nproma_14;
    global_data_var_81_nproma_14 = (int*)(&((*global_data_var_81_0)->nproma));
    t_patch** p_patch_var_82_3;
    p_patch_var_82_3 = &p_patch;
    t_grid_edges** v_p_patch_var_82_edges;
    v_p_patch_var_82_edges = (t_grid_edges**)(&((*p_patch_var_82_3)->edges));
    int* v_v_p_patch_var_82_edges_start_index;
    v_v_p_patch_var_82_edges_start_index = (int*)(&((*v_p_patch_var_82_edges)->start_index)[0]);
    int* v_v_p_patch_var_82_edges_end_index;
    v_v_p_patch_var_82_edges_end_index = (int*)(&((*v_p_patch_var_82_edges)->end_index)[0]);
    t_patch** p_patch_var_82_0;
    p_patch_var_82_0 = &p_patch;
    global_data_type** global_data_var_69_0;
    global_data_var_69_0 = &global_data;
    int* global_data_var_69_nproma_13;
    global_data_var_69_nproma_13 = (int*)(&((*global_data_var_69_0)->nproma));
    t_patch** p_patch_var_70_1;
    p_patch_var_70_1 = &p_patch;
    t_grid_cells** v_p_patch_var_70_cells;
    v_p_patch_var_70_cells = (t_grid_cells**)(&((*p_patch_var_70_1)->cells));
    int* v_v_p_patch_var_70_cells_start_index;
    v_v_p_patch_var_70_cells_start_index = (int*)(&((*v_p_patch_var_70_cells)->start_index)[0]);
    int* v_v_p_patch_var_70_cells_end_index;
    v_v_p_patch_var_70_cells_end_index = (int*)(&((*v_p_patch_var_70_cells)->end_index)[0]);
    t_patch** p_patch_var_70_0;
    p_patch_var_70_0 = &p_patch;
    global_data_type** global_data_var_69_1;
    global_data_var_69_1 = &global_data;
    int* global_data_var_69_nproma_12;
    global_data_var_69_nproma_12 = (int*)(&((*global_data_var_69_1)->nproma));
    global_data_type** global_data_var_81_3;
    global_data_var_81_3 = &global_data;
    int* global_data_var_81_nproma_9;
    global_data_var_81_nproma_9 = (int*)(&((*global_data_var_81_3)->nproma));
    t_patch** ptr_patch_var_106_0;
    ptr_patch_var_106_0 = &p_patch;
    t_grid_vertices** v_ptr_patch_var_106_verts;
    v_ptr_patch_var_106_verts = (t_grid_vertices**)(&((*ptr_patch_var_106_0)->verts));
    int* v_v_ptr_patch_var_106_verts_start_block;
    v_v_ptr_patch_var_106_verts_start_block = (int*)(&((*v_ptr_patch_var_106_verts)->start_block)[0]);
    int* v_v_ptr_patch_var_106_verts_end_block;
    v_v_ptr_patch_var_106_verts_end_block = (int*)(&((*v_ptr_patch_var_106_verts)->end_block)[0]);
    int* v_v_ptr_patch_var_106_verts_edge_idx;
    v_v_ptr_patch_var_106_verts_edge_idx = (int*)(&((*v_ptr_patch_var_106_verts)->edge_idx)[0]);
    int* v_v_ptr_patch_var_106_verts_edge_blk;
    v_v_ptr_patch_var_106_verts_edge_blk = (int*)(&((*v_ptr_patch_var_106_verts)->edge_blk)[0]);
    global_data_type** global_data_var_105_0;
    global_data_var_105_0 = &global_data;
    global_data_type** global_data_var_93_0;
    global_data_var_93_0 = &(*global_data_var_105_0);
    int* global_data_var_93_nproma_8;
    global_data_var_93_nproma_8 = (int*)(&((*global_data_var_93_0)->nproma));
    t_patch** p_patch_var_94_0;
    p_patch_var_94_0 = &(*ptr_patch_var_106_0);
    t_grid_vertices** v_p_patch_var_94_verts;
    v_p_patch_var_94_verts = (t_grid_vertices**)(&((*p_patch_var_94_0)->verts));
    int* v_v_p_patch_var_94_verts_start_index;
    v_v_p_patch_var_94_verts_start_index = (int*)(&((*v_p_patch_var_94_verts)->start_index)[0]);
    int* v_v_p_patch_var_94_verts_end_index;
    v_v_p_patch_var_94_verts_end_index = (int*)(&((*v_p_patch_var_94_verts)->end_index)[0]);
    int i_startblk_var_118_0;
    int i_endblk_var_119_0;
    int i_startblk_var_146;
    int i_endblk_var_147;
    int i_startblk_2;
    int i_endblk_2;
    int tmp_arg_15;
    double tmp_call_18;
    int i_startidx_in_var_79_1;
    int i_endidx_in_var_80_1;
    int tmp_arg_9;
    int tmp_arg_10;
    int i_startidx_in_var_79_0;
    int i_endidx_in_var_80_0;
    int tmp_arg_12;
    int _for_it_22;
    int _for_it_23;
    int tmp_index_407;
    int tmp_index_409;
    int tmp_index_419;
    int tmp_index_421;
    int tmp_index_431;
    int tmp_index_433;
    int _for_it_24;
    int _for_it_29;
    int _for_it_30;
    int _for_it_31;
    int _for_it_32;
    int _for_it_33;
    int _for_it_34;
    int clip_count;
    int _for_it_35;
    int _for_it_36;
    int _if_cond_18;
    int _for_it_37;
    double _if_cond_19;
    double _if_cond_20;
    int _for_it_38;
    int _for_it_39;
    int _for_it_40;
    int tmp_index_540;
    int _for_it_41;
    int _for_it_42;
    int tmp_index_567;
    int tmp_index_571;
    int tmp_index_581;
    int tmp_index_583;
    int tmp_index_593;
    int tmp_index_595;
    int tmp_index_605;
    int tmp_index_607;
    int _for_it_43;
    int i_startidx_2;
    int i_endidx_2;
    int i_startidx_var_148;
    int i_endidx_var_149;
    int _for_it_25;
    int tmp_index_445;
    int tmp_index_447;
    int tmp_index_457;
    int tmp_index_459;
    int tmp_index_469;
    int tmp_index_471;
    int _for_it_26;
    int _for_it_27;
    int _for_it_28;
    int _if_cond_24;
    int _for_it_44;
    int _if_cond_25;
    int _for_it_45;
    int tmp_index_622;
    int tmp_index_626;
    int tmp_index_641;
    int tmp_index_643;
    int tmp_index_653;
    int tmp_index_655;
    int tmp_index_665;
    int tmp_index_667;
    int tmp_call_13;
    int _for_it_46;
    int tmp_parfor_0;
    int i_startidx_in_var_91_0;
    int i_endidx_in_var_92_0;
    int tmp_arg_17;
    int _for_it_47;
    int _if_cond_28;
    int _for_it_52;
    int tmp_index_881;
    int tmp_index_883;
    int tmp_index_893;
    int tmp_index_895;
    int _for_it_53;
    int tmp_index_905;
    int tmp_index_909;
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
    int _for_it_48;
    int tmp_index_679;
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
    int _for_it_49;
    int i_startidx_in_var_103_0_0;
    int i_endidx_in_var_104_0_0;
    int _for_it_3_0;
    int _for_it_4_0;
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
    int _for_it_5_0;
    int i_startidx_var_120_0;
    int i_endidx_var_121_0;
    int i_startidx_in_var_91_3;
    int i_endidx_in_var_92_3;
    int _for_it_6;
    int _for_it_7;
    int tmp_index_178;
    int tmp_index_180;
    int tmp_index_190;
    int tmp_index_192;
    int tmp_index_202;
    int tmp_index_204;
    int tmp_index_214;
    int tmp_index_216;
    int _for_it_8;
    int _for_it_9;
    int _for_it_10;
    int _for_it_13;
    int _for_it_14;
    int _for_it_15;


    {
        int* v_global_data_nrdmax;
        v_global_data_nrdmax = (int*)(&(global_data->nrdmax)[0]);
        int* v_global_data_nflatlev;
        v_global_data_nflatlev = (int*)(&(global_data->nflatlev)[0]);

        {
            int global_data_0_in_nrdmax_0 = v_global_data_nrdmax[0];
            int nrdmax_jg_out;

            ///////////////////
            // Tasklet code (T_l419_c419)
            nrdmax_jg_out = global_data_0_in_nrdmax_0;
            ///////////////////

            nrdmax_jg = nrdmax_jg_out;
        }
        {
            int global_data_0_in_nflatlev_0 = v_global_data_nflatlev[0];
            int nflatlev_jg_out;

            ///////////////////
            // Tasklet code (T_l420_c420)
            nflatlev_jg_out = global_data_0_in_nflatlev_0;
            ///////////////////

            nflatlev_jg = nflatlev_jg_out;
        }
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

    }
    i_startblk_var_118_0 = v_v_ptr_patch_var_106_verts_start_block[(2 - __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5)];

    {


    }
    i_endblk_var_119_0 = v_v_ptr_patch_var_106_verts_end_block[((- __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5) - 5)];

    for (_for_it_3_0 = i_startblk_var_118_0; (_for_it_3_0 <= i_endblk_var_119_0); _for_it_3_0 = (_for_it_3_0 + 1)) {
        {


        }
        i_startidx_in_var_103_0_0 = v_v_p_patch_var_94_verts_start_index[(2 - __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5)];
        {


        }
        i_endidx_in_var_104_0_0 = v_v_p_patch_var_94_verts_end_index[((- __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5) - 5)];
        if (((_for_it_3_0 == i_startblk_var_118_0) == 1)) {

            i_startidx_var_120_0 = i_startidx_in_var_103_0_0;
            {


            }
            i_endidx_var_121_0 = global_data_var_93_nproma_8[0];
            if (((_for_it_3_0 == i_endblk_var_119_0) == 1)) {

                i_endidx_var_121_0 = i_endidx_in_var_104_0_0;

            }
        } else {
            if (((_for_it_3_0 == i_endblk_var_119_0) == 1)) {

                i_startidx_var_120_0 = 1;
                i_endidx_var_121_0 = i_endidx_in_var_104_0_0;

            } else {

                i_startidx_var_120_0 = 1;
                {


                }
                i_endidx_var_121_0 = global_data_var_93_nproma_8[0];

            }
        }
        for (_for_it_4_0 = 1; (_for_it_4_0 <= 90); _for_it_4_0 = (_for_it_4_0 + 1)) {
            for (_for_it_5_0 = i_startidx_var_120_0; (_for_it_5_0 <= i_endidx_var_121_0); _for_it_5_0 = (_for_it_5_0 + 1)) {
                {


                }
                tmp_index_92_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_94_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_104_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_106_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_116_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_118_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_128_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_130_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_140_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_142_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_152_0 = (v_v_ptr_patch_var_106_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_154_0 = (v_v_ptr_patch_var_106_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {
                    double* p_prog_vn_7;
                    p_prog_vn_7 = (double*)(&(p_prog->vn)[0]);
                    t_int_state** ptr_int_0;
                    ptr_int_0 = &p_int;
                    double* v_ptr_int_geofac_rot;
                    v_ptr_int_geofac_rot = (double*)(&((*ptr_int_0)->geofac_rot)[0]);

                    {
                        double ptr_int_0_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (1 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double ptr_int_1_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (2 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double ptr_int_2_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (3 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double ptr_int_3_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (4 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double ptr_int_4_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (5 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double ptr_int_5_in_geofac_rot_0 = v_ptr_int_geofac_rot[(((((__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * __f2dace_SA_geofac_rot_d_1_s_41_p_int_6) * ((- __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6) + _for_it_3_0)) + (__f2dace_SA_geofac_rot_d_0_s_40_p_int_6 * (6 - __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6))) - __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6) + _for_it_5_0)];
                        double vec_e_0_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
                        double vec_e_1_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
                        double vec_e_2_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
                        double vec_e_3_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
                        double vec_e_4_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
                        double vec_e_5_in_0 = p_prog_vn_7[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
                        double rot_vec_out_0;

                        ///////////////////
                        // Tasklet code (T_l296_c296)
                        rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
                        ///////////////////

                        zeta[(((_for_it_5_0 + ((90 * tmp_struct_symbol_8) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_8 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
                    }

                }

            }

        }

    }

    {


    }
    i_startblk_var_146 = v_v_p_patch_edges_start_block[(5 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];

    {


    }
    i_endblk_var_147 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 10)];

    for (_for_it_6 = i_startblk_var_146; (_for_it_6 <= i_endblk_var_147); _for_it_6 = (_for_it_6 + 1)) {
        {


        }
        i_startidx_in_var_91_3 = v_v_p_patch_var_82_edges_start_index[(5 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
        {


        }
        i_endidx_in_var_92_3 = v_v_p_patch_var_82_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 10)];
        if ((_for_it_6 != i_startblk_var_146)) {

            i_startidx_var_148 = 1;

        } else {

            i_startidx_var_148 = max(1, i_startidx_in_var_91_3);

        }
        if ((_for_it_6 != i_endblk_var_147)) {
            {


            }
            i_endidx_var_149 = global_data_var_81_nproma_9[0];

        } else {

            i_endidx_var_149 = i_endidx_in_var_92_3;

        }
        for (_for_it_7 = 1; (_for_it_7 <= 90); _for_it_7 = (_for_it_7 + 1)) {
            for (_for_it_8 = i_startidx_var_148; (_for_it_8 <= i_endidx_var_149); _for_it_8 = (_for_it_8 + 1)) {
                {


                }
                tmp_index_178 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_180 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_190 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_192 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_202 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_204 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {


                }
                tmp_index_214 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                {


                }
                tmp_index_216 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                {
                    double* v_p_int_rbf_vec_coeff_e;
                    v_p_int_rbf_vec_coeff_e = (double*)(&(p_int->rbf_vec_coeff_e)[0]);

                    {
                        double p_int_0_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 1)];
                        double p_int_1_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 2)];
                        double p_int_2_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 3)];
                        double p_int_3_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 4)];
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_180) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_7))) + tmp_index_178)];
                        double p_prog_1_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_192) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_7))) + tmp_index_190)];
                        double p_prog_2_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_204) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_7))) + tmp_index_202)];
                        double p_prog_3_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_216) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_7))) + tmp_index_214)];
                        double p_diag_out_vt_0;

                        ///////////////////
                        // Tasklet code (T_l441_c441)
                        p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
                        ///////////////////

                        v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_292_p_diag_9) + _for_it_7)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_8)] = p_diag_out_vt_0;
                    }

                }

            }

        }
        for (_for_it_9 = 2; (_for_it_9 <= 90); _for_it_9 = (_for_it_9 + 1)) {
            for (_for_it_10 = i_startidx_var_148; (_for_it_10 <= i_endidx_var_149); _for_it_10 = (_for_it_10 + 1)) {
                {
                    double* v_p_metrics_wgtfac_e;
                    v_p_metrics_wgtfac_e = (double*)(&(p_metrics->wgtfac_e)[0]);

                    {
                        double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8) + _for_it_10)];
                        double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[((((__f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_324_p_metrics_8) + _for_it_9)) + ((91 * __f2dace_SA_wgtfac_e_d_0_s_323_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_325_p_metrics_8) + _for_it_6))) - __f2dace_SOA_wgtfac_e_d_0_s_323_p_metrics_8) + _for_it_10)];
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_10)];
                        double p_prog_1_in_vn_0 = v_p_prog_vn[(((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * (((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_9) - 1))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_10)];
                        double p_diag_out_vn_ie_0;

                        ///////////////////
                        // Tasklet code (T_l446_c446)
                        p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                        ///////////////////

                        v_p_diag_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_10)] = p_diag_out_vn_ie_0;
                    }
                    {
                        double p_diag_0_in_vt_0 = v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_292_p_diag_9) + _for_it_9)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_10)];
                        double tmp_call_2_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_2_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                        ///////////////////

                        tmp_call_2 = tmp_call_2_out;
                    }

                }
                {
                    double tmp_call_1;

                    {
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_9)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_10)];
                        double tmp_call_1_out;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        tmp_call_1_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                        ///////////////////

                        tmp_call_1 = tmp_call_1_out;
                    }
                    {
                        double tmp_call_1_0_in = tmp_call_1;
                        double tmp_call_2_0_in = tmp_call_2;
                        double z_kin_hor_e_out_0;

                        ///////////////////
                        // Tasklet code (T_l447_c447)
                        z_kin_hor_e_out_0 = (0.5 * (tmp_call_1_0_in + tmp_call_2_0_in));
                        ///////////////////

                        z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_365) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s_363) + _for_it_10)] = z_kin_hor_e_out_0;
                    }

                }

            }

        }
        for (_for_it_13 = nflatlev_jg; (_for_it_13 <= 90); _for_it_13 = (_for_it_13 + 1)) {
            for (_for_it_14 = i_startidx_var_148; (_for_it_14 <= i_endidx_var_149); _for_it_14 = (_for_it_14 + 1)) {
                {
                    double* v_p_metrics_ddxn_z_full;
                    v_p_metrics_ddxn_z_full = (double*)(&(p_metrics->ddxn_z_full)[0]);
                    double* v_p_metrics_ddxt_z_full;
                    v_p_metrics_ddxt_z_full = (double*)(&(p_metrics->ddxt_z_full)[0]);

                    {
                        double p_diag_0_in_vt_0 = v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_292_p_diag_9) + _for_it_13)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_14)];
                        double p_metrics_0_in_ddxn_z_full_0 = v_p_metrics_ddxn_z_full[((((__f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8 * ((- __f2dace_SOA_ddxn_z_full_d_1_s_309_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxn_z_full_d_0_s_308_p_metrics_8) * ((- __f2dace_SOA_ddxn_z_full_d_2_s_310_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxn_z_full_d_0_s_308_p_metrics_8) + _for_it_14)];
                        double p_metrics_1_in_ddxt_z_full_0 = v_p_metrics_ddxt_z_full[((((__f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8 * ((- __f2dace_SOA_ddxt_z_full_d_1_s_312_p_metrics_8) + _for_it_13)) + ((90 * __f2dace_SA_ddxt_z_full_d_0_s_311_p_metrics_8) * ((- __f2dace_SOA_ddxt_z_full_d_2_s_313_p_metrics_8) + _for_it_6))) - __f2dace_SOA_ddxt_z_full_d_0_s_311_p_metrics_8) + _for_it_14)];
                        double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_13)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_14)];
                        double z_w_concorr_me_out_0;

                        ///////////////////
                        // Tasklet code (T_l459_c459)
                        z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                        ///////////////////

                        z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * ((- __f2dace_OA_z_w_concorr_me_d_2_s_362) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s_360 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_361) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s_360) + _for_it_14)] = z_w_concorr_me_out_0;
                    }

                }

            }

        }
        for (_for_it_15 = i_startidx_var_148; (_for_it_15 <= i_endidx_var_149); _for_it_15 = (_for_it_15 + 1)) {
            {

                {
                    double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_289_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_15)];
                    double p_diag_out_vn_ie_0;

                    ///////////////////
                    // Tasklet code (T_l464_c464)
                    p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                    ///////////////////

                    v_p_diag_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * (1 - __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
                }
                {
                    double p_diag_0_in_vt_0 = v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_292_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_15)];
                    double z_vt_ie_out_0;

                    ///////////////////
                    // Tasklet code (T_l465_c465)
                    z_vt_ie_out_0 = p_diag_0_in_vt_0;
                    ///////////////////

                    z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_366 * __f2dace_A_z_vt_ie_d_1_s_367) * ((- __f2dace_OA_z_vt_ie_d_2_s_368) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_366 * (1 - __f2dace_OA_z_vt_ie_d_1_s_367))) - __f2dace_OA_z_vt_ie_d_0_s_366) + _for_it_15)] = z_vt_ie_out_0;
                }

            }
            {
                double tmp_call_4;
                double tmp_call_3;

                {
                    double p_diag_0_in_vt_0 = v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_292_p_diag_9)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_6))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_15)];
                    double tmp_call_4_out;

                    ///////////////////
                    // Tasklet code (T_l466_c466)
                    tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                    ///////////////////

                    tmp_call_4 = tmp_call_4_out;
                }
                {
                    double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_289_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_15)];
                    double tmp_call_3_out;

                    ///////////////////
                    // Tasklet code (T_l466_c466)
                    tmp_call_3_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                    ///////////////////

                    tmp_call_3 = tmp_call_3_out;
                }
                {
                    double tmp_call_3_0_in = tmp_call_3;
                    double tmp_call_4_0_in = tmp_call_4;
                    double z_kin_hor_e_out_0;

                    ///////////////////
                    // Tasklet code (T_l466_c466)
                    z_kin_hor_e_out_0 = (0.5 * (tmp_call_3_0_in + tmp_call_4_0_in));
                    ///////////////////

                    z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_365) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * (1 - __f2dace_OA_z_kin_hor_e_d_1_s_364))) - __f2dace_OA_z_kin_hor_e_d_0_s_363) + _for_it_15)] = z_kin_hor_e_out_0;
                }

            }
            {
                double* v_p_metrics_wgtfacq_e;
                v_p_metrics_wgtfacq_e = (double*)(&(p_metrics->wgtfacq_e)[0]);

                {
                    double p_metrics_0_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8) + _for_it_15)];
                    double p_metrics_1_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8) + _for_it_15)];
                    double p_metrics_2_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_327_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_328_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_326_p_metrics_8 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_327_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_326_p_metrics_8) + _for_it_15)];
                    double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * (90 - __f2dace_SOA_vn_d_1_s_289_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_15)];
                    double p_prog_1_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * (89 - __f2dace_SOA_vn_d_1_s_289_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_15)];
                    double p_prog_2_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * (88 - __f2dace_SOA_vn_d_1_s_289_p_prog_7)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_6))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_15)];
                    double p_diag_out_vn_ie_0;

                    ///////////////////
                    // Tasklet code (T_l467_c467)
                    p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                    ///////////////////

                    v_p_diag_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * (91 - __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_6))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
                }

            }

        }

    }

    {


    }
    i_startblk_var_146 = v_v_p_patch_edges_start_block[(7 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];

    {


    }
    i_endblk_var_147 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 9)];

    {


    }
    i_startblk_var_146 = v_v_p_patch_cells_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_var_147 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 5)];

    {


    }
    i_startblk_2 = v_v_p_patch_cells_start_block[(5 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_2 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];

    for (_for_it_22 = i_startblk_var_146; (_for_it_22 <= i_endblk_var_147); _for_it_22 = (_for_it_22 + 1)) {
        {


        }
        i_startidx_in_var_79_1 = v_v_p_patch_var_70_cells_start_index[(4 - __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2)];
        {


        }
        i_endidx_in_var_80_1 = v_v_p_patch_var_70_cells_end_index[((- __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2) - 5)];
        if (((_for_it_22 == i_startblk_var_146) == 1)) {

            i_startidx_var_148 = max(1, i_startidx_in_var_79_1);
            {


            }
            i_endidx_var_149 = global_data_var_69_nproma_12[0];
            if (((_for_it_22 == i_endblk_var_147) == 1)) {

                i_endidx_var_149 = i_endidx_in_var_80_1;

            }
        } else {
            if (((_for_it_22 == i_endblk_var_147) == 1)) {

                i_startidx_var_148 = 1;
                i_endidx_var_149 = i_endidx_in_var_80_1;

            } else {

                i_startidx_var_148 = 1;
                {


                }
                i_endidx_var_149 = global_data_var_69_nproma_12[0];

            }
        }
        for (_for_it_23 = 1; (_for_it_23 <= 90); _for_it_23 = (_for_it_23 + 1)) {
            for (_for_it_24 = i_startidx_var_148; (_for_it_24 <= i_endidx_var_149); _for_it_24 = (_for_it_24 + 1)) {
                {


                }
                tmp_index_407 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
                {


                }
                tmp_index_409 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);
                {


                }
                tmp_index_419 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
                {


                }
                tmp_index_421 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);
                {


                }
                tmp_index_431 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_0_s_363);
                {


                }
                tmp_index_433 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_24)] - __f2dace_OA_z_kin_hor_e_d_2_s_365);
                {

                    {
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_24)];
                        double z_kin_hor_e_0_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_409) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_407)];
                        double z_kin_hor_e_1_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_421) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_419)];
                        double z_kin_hor_e_2_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * tmp_index_433) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_23))) + tmp_index_431)];
                        double z_ekinh_out_0;

                        ///////////////////
                        // Tasklet code (T_l515_c515)
                        z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_kin_hor_e_2_in_0));
                        ///////////////////

                        z_ekinh[(((_for_it_24 + ((90 * tmp_struct_symbol_10) * (_for_it_22 - 1))) + (tmp_struct_symbol_10 * (_for_it_23 - 1))) - 1)] = z_ekinh_out_0;
                    }

                }

            }

        }
        for (_for_it_25 = nflatlev_jg; (_for_it_25 <= 90); _for_it_25 = (_for_it_25 + 1)) {
            for (_for_it_26 = i_startidx_var_148; (_for_it_26 <= i_endidx_var_149); _for_it_26 = (_for_it_26 + 1)) {
                {


                }
                tmp_index_445 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s_360);
                {


                }
                tmp_index_447 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s_362);
                {


                }
                tmp_index_457 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s_360);
                {


                }
                tmp_index_459 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s_362);
                {


                }
                tmp_index_469 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_0_s_360);
                {


                }
                tmp_index_471 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_26)] - __f2dace_OA_z_w_concorr_me_d_2_s_362);
                {

                    {
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_26)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_26)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_26)];
                        double z_w_concorr_me_0_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * tmp_index_447) + (__f2dace_A_z_w_concorr_me_d_0_s_360 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_361) + _for_it_25))) + tmp_index_445)];
                        double z_w_concorr_me_1_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * tmp_index_459) + (__f2dace_A_z_w_concorr_me_d_0_s_360 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_361) + _for_it_25))) + tmp_index_457)];
                        double z_w_concorr_me_2_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_360 * __f2dace_A_z_w_concorr_me_d_1_s_361) * tmp_index_471) + (__f2dace_A_z_w_concorr_me_d_0_s_360 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_361) + _for_it_25))) + tmp_index_469)];
                        double z_w_concorr_mc_out_0;

                        ///////////////////
                        // Tasklet code (T_l521_c521)
                        z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_w_concorr_me_2_in_0));
                        ///////////////////

                        z_w_concorr_mc[((_for_it_26 + (tmp_struct_symbol_0 * (_for_it_25 - 1))) - 1)] = z_w_concorr_mc_out_0;
                    }

                }

            }

        }
        for (_for_it_27 = (nflatlev_jg + 1); (_for_it_27 <= 90); _for_it_27 = (_for_it_27 + 1)) {
            for (_for_it_28 = i_startidx_var_148; (_for_it_28 <= i_endidx_var_149); _for_it_28 = (_for_it_28 + 1)) {
                {
                    double* v_p_metrics_wgtfac_c;
                    v_p_metrics_wgtfac_c = (double*)(&(p_metrics->wgtfac_c)[0]);

                    {
                        double p_metrics_0_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8) + _for_it_28)];
                        double p_metrics_1_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[((((__f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_321_p_metrics_8) + _for_it_27)) + ((91 * __f2dace_SA_wgtfac_c_d_0_s_320_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_322_p_metrics_8) + _for_it_22))) - __f2dace_SOA_wgtfac_c_d_0_s_320_p_metrics_8) + _for_it_28)];
                        double z_w_concorr_mc_0_in_0 = z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 1))) - 1)];
                        double z_w_concorr_mc_1_in_0 = z_w_concorr_mc[((_for_it_28 + (tmp_struct_symbol_0 * (_for_it_27 - 2))) - 1)];
                        double p_diag_out_w_concorr_c_0;

                        ///////////////////
                        // Tasklet code (T_l526_c526)
                        p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                        ///////////////////

                        v_p_diag_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9) + _for_it_27)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9) + _for_it_28)] = p_diag_out_w_concorr_c_0;
                    }

                }

            }

        }
        for (_for_it_29 = 1; (_for_it_29 <= 90); _for_it_29 = (_for_it_29 + 1)) {
            for (_for_it_30 = i_startidx_var_148; (_for_it_30 <= i_endidx_var_149); _for_it_30 = (_for_it_30 + 1)) {
                {

                    {
                        double p_prog_0_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_29)) + ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_30)];
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
        for (_for_it_31 = i_startidx_var_148; (_for_it_31 <= i_endidx_var_149); _for_it_31 = (_for_it_31 + 1)) {
            {

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
        for (_for_it_32 = 90; (_for_it_32 >= (nflatlev_jg + 1)); _for_it_32 = (_for_it_32 + -1)) {
            for (_for_it_33 = i_startidx_var_148; (_for_it_33 <= i_endidx_var_149); _for_it_33 = (_for_it_33 + 1)) {
                {

                    {
                        double p_diag_0_in_w_concorr_c_0 = v_p_diag_w_concorr_c[((((__f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_298_p_diag_9) + _for_it_32)) + ((91 * __f2dace_SA_w_concorr_c_d_0_s_297_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_299_p_diag_9) + _for_it_22))) - __f2dace_SOA_w_concorr_c_d_0_s_297_p_diag_9) + _for_it_33)];
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
        tmp_arg_9 = (nrdmax_jg - 2);
        for (_for_it_34 = max(3, tmp_arg_9); (_for_it_34 <= (90 - 3)); _for_it_34 = (_for_it_34 + 1)) {
            {

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
        tmp_arg_10 = (nrdmax_jg - 2);
        {

            {
                double maxvcfl_out;

                ///////////////////
                // Tasklet code (T_l546_c546)
                maxvcfl_out = 0;
                ///////////////////

                maxvcfl = maxvcfl_out;
            }

        }
        for (_for_it_35 = max(3, tmp_arg_10); (_for_it_35 <= (90 - 3)); _for_it_35 = (_for_it_35 + 1)) {

            clip_count = 0;
            for (_for_it_36 = i_startidx_var_148; (_for_it_36 <= i_endidx_var_149); _for_it_36 = (_for_it_36 + 1)) {
                {
                    double tmp_call_7;

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_36 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)];
                        double tmp_call_7_out;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        tmp_call_7_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        tmp_call_7 = tmp_call_7_out;
                    }
                    {
                        double cfl_w_limit_0_in = cfl_w_limit;
                        double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8) + _for_it_36)];
                        double tmp_call_7_0_in = tmp_call_7;
                        int cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        cfl_clipping_out_0 = (tmp_call_7_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        cfl_clipping[((_for_it_36 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)] = cfl_clipping_out_0;
                    }
                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[((_for_it_36 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];
                        int _if_cond_16_out;

                        ///////////////////
                        // Tasklet code (T_l551_c551)
                        _if_cond_16_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_16 = _if_cond_16_out;
                    }

                }
                if ((_if_cond_16 == 1)) {

                    clip_count = (clip_count + 1);

                }

            }
            if (((clip_count == 0) == 1)) {
                continue;
            }
            for (_for_it_37 = i_startidx_var_148; (_for_it_37 <= i_endidx_var_149); _for_it_37 = (_for_it_37 + 1)) {

                _if_cond_18 = cfl_clipping[((_for_it_37 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];
                if ((_if_cond_18 == 1)) {
                    {
                        double tmp_call_8;

                        {
                            int levmask_out_0;

                            ///////////////////
                            // Tasklet code (T_l556_c556)
                            levmask_out_0 = 1;
                            ///////////////////

                            levmask[((_for_it_22 + (tmp_struct_symbol_13 * (_for_it_35 - 1))) - 1)] = levmask_out_0;
                        }
                        {
                            double dtime_0_in = dtime;
                            double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8) + _for_it_37)];
                            double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)];
                            double vcfl_out;

                            ///////////////////
                            // Tasklet code (T_l557_c557)
                            vcfl_out = ((z_w_con_c_0_in_0 * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0);
                            ///////////////////

                            vcfl = vcfl_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            double tmp_call_8_out;

                            ///////////////////
                            // Tasklet code (T_l558_c558)
                            tmp_call_8_out = abs(vcfl_0_in);
                            ///////////////////

                            tmp_call_8 = tmp_call_8_out;
                        }
                        {
                            double maxvcfl_0_in = maxvcfl;
                            double tmp_call_8_0_in = tmp_call_8;
                            double maxvcfl_out;

                            ///////////////////
                            // Tasklet code (T_l558_c558)
                            maxvcfl_out = max(maxvcfl_0_in, tmp_call_8_0_in);
                            ///////////////////

                            maxvcfl = maxvcfl_out;
                        }

                    }
                    _if_cond_19 = (vcfl < -0.85);
                    if ((_if_cond_19 == 1)) {
                        {

                            {
                                double dtime_0_in = dtime;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8) + _for_it_37)];
                                double z_w_con_c_out_0;

                                ///////////////////
                                // Tasklet code (T_l560_c560)
                                z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                                ///////////////////

                                z_w_con_c[((_for_it_37 + (tmp_struct_symbol_1 * (_for_it_35 - 1))) - 1)] = z_w_con_c_out_0;
                            }

                        }
                    } else {

                        _if_cond_20 = (vcfl > 0.85);
                        if ((_if_cond_20 == 1)) {
                            {

                                {
                                    double dtime_0_in = dtime;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8) + _for_it_35)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8) + _for_it_37)];
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

            }

        }
        for (_for_it_38 = 1; (_for_it_38 <= 90); _for_it_38 = (_for_it_38 + 1)) {
            for (_for_it_39 = i_startidx_var_148; (_for_it_39 <= i_endidx_var_149); _for_it_39 = (_for_it_39 + 1)) {
                {

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
        {

            {
                double maxvcfl_0_in = maxvcfl;
                double vcflmax_out_0;

                ///////////////////
                // Tasklet code (T_l572_c572)
                vcflmax_out_0 = maxvcfl_0_in;
                ///////////////////

                vcflmax[(_for_it_22 - 1)] = vcflmax_out_0;
            }

        }
        continue;
        if ((((_for_it_22 < i_startblk_2) || (_for_it_22 > i_endblk_2)) == 1)) {
            continue;
        }
        {


        }
        i_startidx_in_var_79_0 = v_v_p_patch_var_70_cells_start_index[(5 - __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2)];
        {


        }
        i_endidx_in_var_80_0 = v_v_p_patch_var_70_cells_end_index[((- __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2) - 4)];
        if (((_for_it_22 == i_startblk_2) == 1)) {

            i_startidx_2 = max(1, i_startidx_in_var_79_0);
            {


            }
            i_endidx_2 = global_data_var_69_nproma_13[0];
            if (((_for_it_22 == i_endblk_2) == 1)) {

                i_endidx_2 = i_endidx_in_var_80_0;

            }
        } else {
            if (((_for_it_22 == i_endblk_2) == 1)) {

                i_startidx_2 = 1;
                i_endidx_2 = i_endidx_in_var_80_0;

            } else {

                i_startidx_2 = 1;
                {


                }
                i_endidx_2 = global_data_var_69_nproma_13[0];

            }
        }
        for (_for_it_40 = 2; (_for_it_40 <= 90); _for_it_40 = (_for_it_40 + 1)) {
            for (_for_it_41 = i_startidx_2; (_for_it_41 <= i_endidx_2); _for_it_41 = (_for_it_41 + 1)) {

                tmp_index_540 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9);
                {
                    double* v_p_metrics_coeff1_dwdz;
                    v_p_metrics_coeff1_dwdz = (double*)(&(p_metrics->coeff1_dwdz)[0]);
                    double* v_p_metrics_coeff2_dwdz;
                    v_p_metrics_coeff2_dwdz = (double*)(&(p_metrics->coeff2_dwdz)[0]);

                    {
                        double p_metrics_0_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[((((__f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8) + _for_it_41)];
                        double p_metrics_1_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[((((__f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8) + _for_it_41)];
                        double p_metrics_2_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[((((__f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_336_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff2_dwdz_d_0_s_335_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_337_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff2_dwdz_d_0_s_335_p_metrics_8) + _for_it_41)];
                        double p_metrics_3_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[((((__f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_333_p_metrics_8) + _for_it_40)) + ((90 * __f2dace_SA_coeff1_dwdz_d_0_s_332_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_334_p_metrics_8) + _for_it_22))) - __f2dace_SOA_coeff1_dwdz_d_0_s_332_p_metrics_8) + _for_it_41)];
                        double p_prog_0_in_w_0 = v_p_prog_w[(((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22)) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40) - 1))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double p_prog_1_in_w_0 = v_p_prog_w[(((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22)) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40) + 1))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double p_prog_2_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_40)) + ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_41)];
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_41 + (tmp_struct_symbol_1 * (_for_it_40 - 1))) - 1)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l578_c578)
                        p_diag_out_ddt_w_adv_pc_0 = (- (z_w_con_c_0_in_0 * (((p_prog_0_in_w_0 * p_metrics_0_in_coeff1_dwdz_0) - (p_prog_1_in_w_0 * p_metrics_1_in_coeff2_dwdz_0)) + (p_prog_2_in_w_0 * (p_metrics_2_in_coeff2_dwdz_0 - p_metrics_3_in_coeff1_dwdz_0)))));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * tmp_index_540) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_40))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_41)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        for (_for_it_42 = 2; (_for_it_42 <= 90); _for_it_42 = (_for_it_42 + 1)) {
            for (_for_it_43 = i_startidx_2; (_for_it_43 <= i_endidx_2); _for_it_43 = (_for_it_43 + 1)) {

                tmp_index_567 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9);
                tmp_index_571 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9);
                {


                }
                tmp_index_581 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
                {


                }
                tmp_index_583 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);
                {


                }
                tmp_index_593 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
                {


                }
                tmp_index_595 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);
                {


                }
                tmp_index_605 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_43)] - 1);
                {


                }
                tmp_index_607 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_43)] - 1);
                {
                    double *z_v_grad_w;
                    z_v_grad_w = new double DACE_ALIGN(64)[(((90 * tmp_struct_symbol_4) * (tmp_struct_symbol_5 - 1)) + (90 * tmp_struct_symbol_4))];

                    {
                        double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * tmp_index_571) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_42))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_43)];
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_22)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_43)];
                        double z_v_grad_w_0_in_0 = z_v_grad_w[((tmp_index_581 + ((90 * tmp_index_583) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
                        double z_v_grad_w_1_in_0 = z_v_grad_w[((tmp_index_593 + ((90 * tmp_index_595) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
                        double z_v_grad_w_2_in_0 = z_v_grad_w[((tmp_index_605 + ((90 * tmp_index_607) * tmp_struct_symbol_4)) + (tmp_struct_symbol_4 * (_for_it_42 - 1)))];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l583_c583)
                        p_diag_out_ddt_w_adv_pc_0 = (((p_diag_0_in_ddt_w_adv_pc_0 + (p_int_0_in_e_bln_c_s_0 * z_v_grad_w_0_in_0)) + (p_int_1_in_e_bln_c_s_0 * z_v_grad_w_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_v_grad_w_2_in_0));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * tmp_index_567) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_42))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_43)] = p_diag_out_ddt_w_adv_pc_0;
                    }
                    delete[] z_v_grad_w;

                }

            }

        }
        tmp_arg_12 = (nrdmax_jg - 2);
        for (_for_it_44 = max(3, tmp_arg_12); (_for_it_44 <= (90 - 3)); _for_it_44 = (_for_it_44 + 1)) {

            _if_cond_24 = levmask[((_for_it_22 + (tmp_struct_symbol_13 * (_for_it_44 - 1))) - 1)];
            if ((_if_cond_24 == 1)) {
                for (_for_it_45 = i_startidx_2; (_for_it_45 <= i_endidx_2); _for_it_45 = (_for_it_45 + 1)) {
                    {


                    }
                    _if_cond_25 = (cfl_clipping[((_for_it_45 + (tmp_struct_symbol_14 * (_for_it_44 - 1))) - 1)] && v_v_v_p_patch_cells_decomp_info_owner_mask[(((__f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3 * ((- __f2dace_SOA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3) + _for_it_22)) - __f2dace_SOA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3) + _for_it_45)]);
                    if ((_if_cond_25 == 1)) {

                        tmp_index_622 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9);
                        tmp_index_626 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_307_p_diag_9);
                        {

                            {
                                double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_45 + (tmp_struct_symbol_1 * (_for_it_44 - 1))) - 1)];
                                double tmp_call_11_out;

                                ///////////////////
                                // Tasklet code (T_l591_c591)
                                tmp_call_11_out = abs(z_w_con_c_0_in_0);
                                ///////////////////

                                tmp_call_11 = tmp_call_11_out;
                            }

                        }
                        tmp_index_641 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (1 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
                        {
                            double tmp_call_10;
                            double tmp_arg_13;
                            double tmp_arg_14;

                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double dtime_0_in = dtime;
                                double dtime_1_in = dtime;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[((((__f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_318_p_metrics_8) + _for_it_44)) + ((91 * __f2dace_SA_ddqz_z_half_d_0_s_317_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_319_p_metrics_8) + _for_it_22))) - __f2dace_SOA_ddqz_z_half_d_0_s_317_p_metrics_8) + _for_it_45)];
                                double tmp_call_11_0_in = tmp_call_11;
                                double tmp_arg_14_out;

                                ///////////////////
                                // Tasklet code (T_l591_c591)
                                tmp_arg_14_out = (((tmp_call_11_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0) - (cfl_w_limit_0_in * dtime_1_in));
                                ///////////////////

                                tmp_arg_14 = tmp_arg_14_out;
                            }
                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double dtime_0_in = dtime;
                                double tmp_arg_13_out;

                                ///////////////////
                                // Tasklet code (T_l591_c591)
                                tmp_arg_13_out = (0.85 - (cfl_w_limit_0_in * dtime_0_in));
                                ///////////////////

                                tmp_arg_13 = tmp_arg_13_out;
                            }
                            {
                                double tmp_arg_13_0_in = tmp_arg_13;
                                double tmp_arg_14_0_in = tmp_arg_14;
                                double tmp_call_10_out;

                                ///////////////////
                                // Tasklet code (T_l591_c591)
                                tmp_call_10_out = min(tmp_arg_13_0_in, tmp_arg_14_0_in);
                                ///////////////////

                                tmp_call_10 = tmp_call_10_out;
                            }
                            {
                                double scalfac_exdiff_0_in = scalfac_exdiff;
                                double tmp_call_10_0_in = tmp_call_10;
                                double difcoef_out;

                                ///////////////////
                                // Tasklet code (T_l591_c591)
                                difcoef_out = (scalfac_exdiff_0_in * tmp_call_10_0_in);
                                ///////////////////

                                difcoef = difcoef_out;
                            }

                        }
                        tmp_index_643 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (1 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
                        {


                        }
                        tmp_index_653 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (2 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
                        {


                        }
                        tmp_index_655 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (2 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
                        {


                        }
                        tmp_index_665 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (3 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_0_s_285_p_prog_7);
                        {


                        }
                        tmp_index_667 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (3 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_22))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_45)] - __f2dace_SOA_w_d_2_s_287_p_prog_7);
                        {
                            double* v_p_int_geofac_n2s;
                            v_p_int_geofac_n2s = (double*)(&(p_int->geofac_n2s)[0]);
                            double* v_v_p_patch_cells_area;
                            v_v_p_patch_cells_area = (double*)(&((*v_p_patch_cells)->area)[0]);

                            {
                                double difcoef_0_in = difcoef;
                                double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * tmp_index_626) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_44))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_45)];
                                double p_int_0_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_22)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (1 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_45)];
                                double p_int_1_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_22)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (2 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_45)];
                                double p_int_2_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_22)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (3 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_45)];
                                double p_int_3_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_22)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (4 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_45)];
                                double p_patch_0_in_cells_area_0 = v_v_p_patch_cells_area[(((__f2dace_SA_area_d_0_s_158_cells_p_patch_2 * ((- __f2dace_SOA_area_d_1_s_159_cells_p_patch_2) + _for_it_22)) - __f2dace_SOA_area_d_0_s_158_cells_p_patch_2) + _for_it_45)];
                                double p_prog_0_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_44)) + ((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_287_p_prog_7) + _for_it_22))) - __f2dace_SOA_w_d_0_s_285_p_prog_7) + _for_it_45)];
                                double p_prog_1_in_w_0 = v_p_prog_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_643) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_44))) + tmp_index_641)];
                                double p_prog_2_in_w_0 = v_p_prog_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_655) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_44))) + tmp_index_653)];
                                double p_prog_3_in_w_0 = v_p_prog_w[((((91 * __f2dace_SA_w_d_0_s_285_p_prog_7) * tmp_index_667) + (__f2dace_SA_w_d_0_s_285_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_286_p_prog_7) + _for_it_44))) + tmp_index_665)];
                                double p_diag_out_ddt_w_adv_pc_0;

                                ///////////////////
                                // Tasklet code (T_l592_c592)
                                p_diag_out_ddt_w_adv_pc_0 = (p_diag_0_in_ddt_w_adv_pc_0 + ((difcoef_0_in * p_patch_0_in_cells_area_0) * ((((p_prog_0_in_w_0 * p_int_0_in_geofac_n2s_0) + (p_prog_1_in_w_0 * p_int_1_in_geofac_n2s_0)) + (p_prog_2_in_w_0 * p_int_2_in_geofac_n2s_0)) + (p_prog_3_in_w_0 * p_int_3_in_geofac_n2s_0))));
                                ///////////////////

                                v_p_diag_ddt_w_adv_pc[(((((((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_306_p_diag_9) * tmp_index_622) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_305_p_diag_9) + _for_it_44))) + ((91 * __f2dace_SA_ddt_w_adv_pc_d_0_s_304_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_306_p_diag_9) + _for_it_22))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_304_p_diag_9) + _for_it_45)] = p_diag_out_ddt_w_adv_pc_0;
                            }

                        }
                    }

                }
            }

        }

    }
    tmp_arg_15 = (nrdmax_jg - 2);

    for (_for_it_46 = max(3, tmp_arg_15); (_for_it_46 <= (90 - 3)); _for_it_46 = (_for_it_46 + 1)) {

        tmp_call_13 = 0;
        for (tmp_parfor_0 = i_startblk_var_146; (tmp_parfor_0 <= i_endblk_var_147); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
            if ((levmask[((tmp_parfor_0 + (tmp_struct_symbol_13 * (_for_it_46 - 1))) - 1)] == 1)) {

                tmp_call_13 = 1;

            }

        }
        {

            {
                int levelmask_out_0;

                ///////////////////
                // Tasklet code (T_l600_c600)
                levelmask_out_0 = tmp_call_13;
                ///////////////////

                levelmask[(_for_it_46 - 1)] = levelmask_out_0;
            }

        }

    }

    {


    }
    i_startblk_var_146 = v_v_p_patch_edges_start_block[(10 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];

    {


    }
    i_endblk_var_147 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 8)];

    for (_for_it_47 = i_startblk_var_146; (_for_it_47 <= i_endblk_var_147); _for_it_47 = (_for_it_47 + 1)) {
        {


        }
        i_startidx_in_var_91_0 = v_v_p_patch_var_82_edges_start_index[(10 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
        {


        }
        i_endidx_in_var_92_0 = v_v_p_patch_var_82_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 8)];
        if ((_for_it_47 != i_startblk_var_146)) {

            i_startidx_var_148 = 1;

        } else {

            i_startidx_var_148 = max(1, i_startidx_in_var_91_0);

        }
        if ((_for_it_47 != i_endblk_var_147)) {
            {


            }
            i_endidx_var_149 = global_data_var_81_nproma_14[0];

        } else {

            i_endidx_var_149 = i_endidx_in_var_92_0;

        }
        for (_for_it_48 = 1; (_for_it_48 <= 90); _for_it_48 = (_for_it_48 + 1)) {
            for (_for_it_49 = i_startidx_var_148; (_for_it_49 <= i_endidx_var_149); _for_it_49 = (_for_it_49 + 1)) {

                tmp_index_679 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9);
                {


                }
                tmp_index_698 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_700 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_710 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_712 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_724 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_726 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_733 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_735 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_745 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_747 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_757 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_49)] - 1);
                {


                }
                tmp_index_759 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_49)] - 1);
                {
                    double* v_p_metrics_coeff_gradekin;
                    v_p_metrics_coeff_gradekin = (double*)(&(p_metrics->coeff_gradekin)[0]);
                    double* v_v_p_patch_edges_f_e;
                    v_v_p_patch_edges_f_e = (double*)(&((*v_p_patch_edges)->f_e)[0]);

                    {
                        double p_diag_0_in_vt_0 = v_p_diag_vt[((((__f2dace_SA_vt_d_0_s_291_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_292_p_diag_9) + _for_it_48)) + ((90 * __f2dace_SA_vt_d_0_s_291_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_293_p_diag_9) + _for_it_47))) - __f2dace_SOA_vt_d_0_s_291_p_diag_9) + _for_it_49)];
                        double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[((((__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_48)) + ((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_47))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_49)];
                        double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[(((((91 * __f2dace_SA_vn_ie_d_0_s_294_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_296_p_diag_9) + _for_it_47)) + (__f2dace_SA_vn_ie_d_0_s_294_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_295_p_diag_9) + _for_it_48) + 1))) - __f2dace_SOA_vn_ie_d_0_s_294_p_diag_9) + _for_it_49)];
                        double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_49)];
                        double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_49)];
                        double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
                        double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
                        double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
                        double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_331_p_metrics_8) + _for_it_47)) + (__f2dace_SA_coeff_gradekin_d_0_s_329_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_330_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_329_p_metrics_8) + _for_it_49)];
                        double p_metrics_4_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8) + _for_it_48)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8) + _for_it_49)];
                        double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4) + _for_it_49)];
                        double z_ekinh_0_in_0 = z_ekinh[((tmp_index_698 + ((90 * tmp_index_700) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
                        double z_ekinh_1_in_0 = z_ekinh[((tmp_index_710 + ((90 * tmp_index_712) * tmp_struct_symbol_10)) + (tmp_struct_symbol_10 * (_for_it_48 - 1)))];
                        double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_363 * __f2dace_A_z_kin_hor_e_d_1_s_364) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_365) + _for_it_47)) + (__f2dace_A_z_kin_hor_e_d_0_s_363 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_364) + _for_it_48))) - __f2dace_OA_z_kin_hor_e_d_0_s_363) + _for_it_49)];
                        double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_745 + ((90 * tmp_index_747) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
                        double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_757 + ((90 * tmp_index_759) * tmp_struct_symbol_2)) + (tmp_struct_symbol_2 * (_for_it_48 - 1)))];
                        double zeta_0_in_0 = zeta[((tmp_index_724 + ((90 * tmp_index_726) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
                        double zeta_1_in_0 = zeta[((tmp_index_733 + ((90 * tmp_index_735) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_48 - 1)))];
                        double p_diag_out_ddt_vn_apc_pc_0;

                        ///////////////////
                        // Tasklet code (T_l611_c611)
                        p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
                        ///////////////////

                        v_p_diag_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * tmp_index_679) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9) + _for_it_48))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) + _for_it_49)] = p_diag_out_ddt_vn_apc_pc_0;
                    }

                }

            }

        }
        tmp_arg_17 = (nrdmax_jg - 2);
        for (_for_it_52 = max(3, tmp_arg_17); (_for_it_52 <= (90 - 4)); _for_it_52 = (_for_it_52 + 1)) {

            _if_cond_28 = (levelmask[(_for_it_52 - 1)] || levelmask[_for_it_52]);
            if ((_if_cond_28 == 1)) {
                for (_for_it_53 = i_startidx_var_148; (_for_it_53 <= i_endidx_var_149); _for_it_53 = (_for_it_53 + 1)) {
                    {


                    }
                    tmp_index_881 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_53)] - 1);
                    {


                    }
                    tmp_index_883 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_53)] - 1);
                    {


                    }
                    tmp_index_893 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_53)] - 1);
                    {


                    }
                    tmp_index_895 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_53)] - 1);
                    {
                        double tmp_call_15;

                        {
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_53)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_47)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_53)];
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
                            double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8) + _for_it_53)];
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
                        tmp_index_905 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9);
                        tmp_index_909 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_303_p_diag_9);
                        {


                        }
                        tmp_index_927 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                        {
                            double tmp_call_16;
                            double tmp_arg_18;
                            double tmp_arg_19;

                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double dtime_0_in = dtime;
                                double dtime_1_in = dtime;
                                double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[((((__f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_315_p_metrics_8) + _for_it_52)) + ((90 * __f2dace_SA_ddqz_z_full_e_d_0_s_314_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_316_p_metrics_8) + _for_it_47))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_314_p_metrics_8) + _for_it_53)];
                                double tmp_call_17_0_in = tmp_call_17;
                                double tmp_arg_19_out;

                                ///////////////////
                                // Tasklet code (T_l642_c642)
                                tmp_arg_19_out = (((tmp_call_17_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
                                ///////////////////

                                tmp_arg_19 = tmp_arg_19_out;
                            }
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

                        }
                        tmp_index_929 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                        {


                        }
                        tmp_index_939 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                        {


                        }
                        tmp_index_941 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                        {


                        }
                        tmp_index_951 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                        {


                        }
                        tmp_index_953 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                        {


                        }
                        tmp_index_963 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_0_s_288_p_prog_7);
                        {


                        }
                        tmp_index_965 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_53)] - __f2dace_SOA_vn_d_2_s_290_p_prog_7);
                        {


                        }
                        tmp_index_976 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_53)] - 1);
                        {


                        }
                        tmp_index_978 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_53)] - 1);
                        {


                        }
                        tmp_index_985 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_53)] - 1);
                        {


                        }
                        tmp_index_987 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_47))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_53)] - 1);
                        {
                            double* v_p_int_geofac_grdiv;
                            v_p_int_geofac_grdiv = (double*)(&(p_int->geofac_grdiv)[0]);
                            double* v_v_p_patch_edges_inv_primal_edge_length;
                            v_v_p_patch_edges_inv_primal_edge_length = (double*)(&((*v_p_patch_edges)->inv_primal_edge_length)[0]);
                            double* v_v_p_patch_edges_tangent_orientation;
                            v_v_p_patch_edges_tangent_orientation = (double*)(&((*v_p_patch_edges)->tangent_orientation)[0]);
                            double* v_v_p_patch_edges_area_edge;
                            v_v_p_patch_edges_area_edge = (double*)(&((*v_p_patch_edges)->area_edge)[0]);

                            {
                                double difcoef_0_in = difcoef;
                                double p_diag_0_in_ddt_vn_apc_pc_0 = v_p_diag_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * tmp_index_909) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) + _for_it_53)];
                                double p_int_0_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (1 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_53)];
                                double p_int_1_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (2 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_53)];
                                double p_int_2_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (3 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_53)];
                                double p_int_3_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (4 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_53)];
                                double p_int_4_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_47)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (5 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_53)];
                                double p_patch_0_in_edges_area_edge_0 = v_v_p_patch_edges_area_edge[(((__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * ((- __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4) + _for_it_53)];
                                double p_patch_1_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4) + _for_it_53)];
                                double p_patch_2_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) + _for_it_47)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4) + _for_it_53)];
                                double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_52)) + ((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_290_p_prog_7) + _for_it_47))) - __f2dace_SOA_vn_d_0_s_288_p_prog_7) + _for_it_53)];
                                double p_prog_1_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_929) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_52))) + tmp_index_927)];
                                double p_prog_2_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_941) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_52))) + tmp_index_939)];
                                double p_prog_3_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_953) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_52))) + tmp_index_951)];
                                double p_prog_4_in_vn_0 = v_p_prog_vn[((((90 * __f2dace_SA_vn_d_0_s_288_p_prog_7) * tmp_index_965) + (__f2dace_SA_vn_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_289_p_prog_7) + _for_it_52))) + tmp_index_963)];
                                double zeta_0_in_0 = zeta[((tmp_index_976 + ((90 * tmp_index_978) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                                double zeta_1_in_0 = zeta[((tmp_index_985 + ((90 * tmp_index_987) * tmp_struct_symbol_8)) + (tmp_struct_symbol_8 * (_for_it_52 - 1)))];
                                double p_diag_out_ddt_vn_apc_pc_0;

                                ///////////////////
                                // Tasklet code (T_l643_c643)
                                p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                                ///////////////////

                                v_p_diag_ddt_vn_apc_pc[(((((((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) * tmp_index_905) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_301_p_diag_9) + _for_it_52))) + ((90 * __f2dace_SA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_302_p_diag_9) + _for_it_47))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_300_p_diag_9) + _for_it_53)] = p_diag_out_ddt_vn_apc_pc_0;
                            }

                        }
                    }

                }
            }

        }

    }

    {


    }
    i_startblk_var_146 = v_v_p_patch_cells_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_var_147 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];
    tmp_call_18 = -1.7976931348623157e+308;

    for (tmp_parfor_0 = i_startblk_var_146; (tmp_parfor_0 <= i_endblk_var_147); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        if ((vcflmax[(tmp_parfor_0 - 1)] > tmp_call_18)) {

            tmp_call_18 = vcflmax[(tmp_parfor_0 - 1)];

        }

    }

    {
        double max_vcfl_dyn_var_152;
        double* v_p_diag_max_vcfl_dyn;
        v_p_diag_max_vcfl_dyn = (double*)(&(p_diag->max_vcfl_dyn));

        {
            double max_vcfl_dyn_var_152_out;

            ///////////////////
            // Tasklet code (T_l652_c652)
            max_vcfl_dyn_var_152_out = max(0.0, tmp_call_18);
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

            v_p_diag_max_vcfl_dyn[0] = p_diag_out_max_vcfl_dyn;
        }

    }

    delete[] z_w_concorr_mc;
    delete[] z_w_con_c;
    delete[] z_w_con_c_full;
    delete[] zeta;
    delete[] z_ekinh;
    delete[] vcflmax;
    delete[] levmask;
    delete[] levelmask;
    delete[] cfl_clipping;
}

DACE_EXPORTED void __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_363, __f2dace_A_z_kin_hor_e_d_1_s_364, __f2dace_A_z_vt_ie_d_0_s_366, __f2dace_A_z_vt_ie_d_1_s_367, __f2dace_A_z_w_concorr_me_d_0_s_360, __f2dace_A_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_kin_hor_e_d_0_s_363, __f2dace_OA_z_kin_hor_e_d_1_s_364, __f2dace_OA_z_kin_hor_e_d_2_s_365, __f2dace_OA_z_vt_ie_d_0_s_366, __f2dace_OA_z_vt_ie_d_1_s_367, __f2dace_OA_z_vt_ie_d_2_s_368, __f2dace_OA_z_w_concorr_me_d_0_s_360, __f2dace_OA_z_w_concorr_me_d_1_s_361, __f2dace_OA_z_w_concorr_me_d_2_s_362, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}

DACE_EXPORTED velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_363, int __f2dace_A_z_kin_hor_e_d_1_s_364, int __f2dace_A_z_vt_ie_d_0_s_366, int __f2dace_A_z_vt_ie_d_1_s_367, int __f2dace_A_z_w_concorr_me_d_0_s_360, int __f2dace_A_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_kin_hor_e_d_0_s_363, int __f2dace_OA_z_kin_hor_e_d_1_s_364, int __f2dace_OA_z_kin_hor_e_d_2_s_365, int __f2dace_OA_z_vt_ie_d_0_s_366, int __f2dace_OA_z_vt_ie_d_1_s_367, int __f2dace_OA_z_vt_ie_d_2_s_368, int __f2dace_OA_z_w_concorr_me_d_0_s_360, int __f2dace_OA_z_w_concorr_me_d_1_s_361, int __f2dace_OA_z_w_concorr_me_d_2_s_362, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state = new velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t;


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

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *__state)
{
    int __err = 0;
    delete __state;
    return __err;
}
