/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../../include/hash.h"

struct t_nh_prog {
    int __f2dace_SA_vn_d_0_s_291 = {};
    int __f2dace_SA_vn_d_1_s_292 = {};
    int __f2dace_SA_vn_d_2_s_293 = {};
    int __f2dace_SA_w_d_0_s_288 = {};
    int __f2dace_SA_w_d_1_s_289 = {};
    int __f2dace_SA_w_d_2_s_290 = {};
    int __f2dace_SOA_vn_d_0_s_291 = {};
    int __f2dace_SOA_vn_d_1_s_292 = {};
    int __f2dace_SOA_vn_d_2_s_293 = {};
    int __f2dace_SOA_w_d_0_s_288 = {};
    int __f2dace_SOA_w_d_1_s_289 = {};
    int __f2dace_SOA_w_d_2_s_290 = {};
    double* vn = {};
    double* w = {};
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
    int id = {};
    int nblks_c = {};
    int nblks_e = {};
    int nblks_v = {};
    int nlev = {};
    int nlevp1 = {};
    int nshift = {};
    t_grid_vertices* verts = {};
};

struct t_nh_metrics {
    int __f2dace_SA_coeff1_dwdz_d_0_s_338 = {};
    int __f2dace_SA_coeff1_dwdz_d_1_s_339 = {};
    int __f2dace_SA_coeff1_dwdz_d_2_s_340 = {};
    int __f2dace_SA_coeff2_dwdz_d_0_s_341 = {};
    int __f2dace_SA_coeff2_dwdz_d_1_s_342 = {};
    int __f2dace_SA_coeff2_dwdz_d_2_s_343 = {};
    int __f2dace_SA_coeff_gradekin_d_0_s_335 = {};
    int __f2dace_SA_coeff_gradekin_d_1_s_336 = {};
    int __f2dace_SA_coeff_gradekin_d_2_s_337 = {};
    int __f2dace_SA_ddqz_z_full_e_d_0_s_320 = {};
    int __f2dace_SA_ddqz_z_full_e_d_1_s_321 = {};
    int __f2dace_SA_ddqz_z_full_e_d_2_s_322 = {};
    int __f2dace_SA_ddqz_z_half_d_0_s_323 = {};
    int __f2dace_SA_ddqz_z_half_d_1_s_324 = {};
    int __f2dace_SA_ddqz_z_half_d_2_s_325 = {};
    int __f2dace_SA_ddxn_z_full_d_0_s_314 = {};
    int __f2dace_SA_ddxn_z_full_d_1_s_315 = {};
    int __f2dace_SA_ddxn_z_full_d_2_s_316 = {};
    int __f2dace_SA_ddxt_z_full_d_0_s_317 = {};
    int __f2dace_SA_ddxt_z_full_d_1_s_318 = {};
    int __f2dace_SA_ddxt_z_full_d_2_s_319 = {};
    int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_346 = {};
    int __f2dace_SA_deepatmo_gradh_mc_d_0_s_344 = {};
    int __f2dace_SA_deepatmo_invr_ifc_d_0_s_347 = {};
    int __f2dace_SA_deepatmo_invr_mc_d_0_s_345 = {};
    int __f2dace_SA_wgtfac_c_d_0_s_326 = {};
    int __f2dace_SA_wgtfac_c_d_1_s_327 = {};
    int __f2dace_SA_wgtfac_c_d_2_s_328 = {};
    int __f2dace_SA_wgtfac_e_d_0_s_329 = {};
    int __f2dace_SA_wgtfac_e_d_1_s_330 = {};
    int __f2dace_SA_wgtfac_e_d_2_s_331 = {};
    int __f2dace_SA_wgtfacq_e_d_0_s_332 = {};
    int __f2dace_SA_wgtfacq_e_d_1_s_333 = {};
    int __f2dace_SA_wgtfacq_e_d_2_s_334 = {};
    int __f2dace_SOA_coeff1_dwdz_d_0_s_338 = {};
    int __f2dace_SOA_coeff1_dwdz_d_1_s_339 = {};
    int __f2dace_SOA_coeff1_dwdz_d_2_s_340 = {};
    int __f2dace_SOA_coeff2_dwdz_d_0_s_341 = {};
    int __f2dace_SOA_coeff2_dwdz_d_1_s_342 = {};
    int __f2dace_SOA_coeff2_dwdz_d_2_s_343 = {};
    int __f2dace_SOA_coeff_gradekin_d_0_s_335 = {};
    int __f2dace_SOA_coeff_gradekin_d_1_s_336 = {};
    int __f2dace_SOA_coeff_gradekin_d_2_s_337 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_0_s_320 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_1_s_321 = {};
    int __f2dace_SOA_ddqz_z_full_e_d_2_s_322 = {};
    int __f2dace_SOA_ddqz_z_half_d_0_s_323 = {};
    int __f2dace_SOA_ddqz_z_half_d_1_s_324 = {};
    int __f2dace_SOA_ddqz_z_half_d_2_s_325 = {};
    int __f2dace_SOA_ddxn_z_full_d_0_s_314 = {};
    int __f2dace_SOA_ddxn_z_full_d_1_s_315 = {};
    int __f2dace_SOA_ddxn_z_full_d_2_s_316 = {};
    int __f2dace_SOA_ddxt_z_full_d_0_s_317 = {};
    int __f2dace_SOA_ddxt_z_full_d_1_s_318 = {};
    int __f2dace_SOA_ddxt_z_full_d_2_s_319 = {};
    int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_346 = {};
    int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_344 = {};
    int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_347 = {};
    int __f2dace_SOA_deepatmo_invr_mc_d_0_s_345 = {};
    int __f2dace_SOA_wgtfac_c_d_0_s_326 = {};
    int __f2dace_SOA_wgtfac_c_d_1_s_327 = {};
    int __f2dace_SOA_wgtfac_c_d_2_s_328 = {};
    int __f2dace_SOA_wgtfac_e_d_0_s_329 = {};
    int __f2dace_SOA_wgtfac_e_d_1_s_330 = {};
    int __f2dace_SOA_wgtfac_e_d_2_s_331 = {};
    int __f2dace_SOA_wgtfacq_e_d_0_s_332 = {};
    int __f2dace_SOA_wgtfacq_e_d_1_s_333 = {};
    int __f2dace_SOA_wgtfacq_e_d_2_s_334 = {};
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

struct global_data_type {
    int i_am_accel_node = {};
    int lextra_diffu = {};
    int lvert_nest = {};
    int* nflatlev = {};
    int nproma = {};
    int* nrdmax = {};
    int timer_intp = {};
    int timer_solve_nh_veltend = {};
    int timers_level = {};
};

struct t_nh_diag {
    int __f2dace_SA_ddt_vn_apc_pc_d_0_s_306 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_1_s_307 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_2_s_308 = {};
    int __f2dace_SA_ddt_vn_apc_pc_d_3_s_309 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_0_s_310 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_1_s_311 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_2_s_312 = {};
    int __f2dace_SA_ddt_w_adv_pc_d_3_s_313 = {};
    int __f2dace_SA_vn_ie_d_0_s_300 = {};
    int __f2dace_SA_vn_ie_d_1_s_301 = {};
    int __f2dace_SA_vn_ie_d_2_s_302 = {};
    int __f2dace_SA_vn_ie_ubc_d_0_s_294 = {};
    int __f2dace_SA_vn_ie_ubc_d_1_s_295 = {};
    int __f2dace_SA_vn_ie_ubc_d_2_s_296 = {};
    int __f2dace_SA_vt_d_0_s_297 = {};
    int __f2dace_SA_vt_d_1_s_298 = {};
    int __f2dace_SA_vt_d_2_s_299 = {};
    int __f2dace_SA_w_concorr_c_d_0_s_303 = {};
    int __f2dace_SA_w_concorr_c_d_1_s_304 = {};
    int __f2dace_SA_w_concorr_c_d_2_s_305 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308 = {};
    int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_0_s_310 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_1_s_311 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_2_s_312 = {};
    int __f2dace_SOA_ddt_w_adv_pc_d_3_s_313 = {};
    int __f2dace_SOA_vn_ie_d_0_s_300 = {};
    int __f2dace_SOA_vn_ie_d_1_s_301 = {};
    int __f2dace_SOA_vn_ie_d_2_s_302 = {};
    int __f2dace_SOA_vn_ie_ubc_d_0_s_294 = {};
    int __f2dace_SOA_vn_ie_ubc_d_1_s_295 = {};
    int __f2dace_SOA_vn_ie_ubc_d_2_s_296 = {};
    int __f2dace_SOA_vt_d_0_s_297 = {};
    int __f2dace_SOA_vt_d_1_s_298 = {};
    int __f2dace_SOA_vt_d_2_s_299 = {};
    int __f2dace_SOA_w_concorr_c_d_0_s_303 = {};
    int __f2dace_SOA_w_concorr_c_d_1_s_304 = {};
    int __f2dace_SOA_w_concorr_c_d_2_s_305 = {};
    double* ddt_vn_apc_pc = {};
    double* ddt_w_adv_pc = {};
    double max_vcfl_dyn = {};
    double* vn_ie = {};
    double* vn_ie_ubc = {};
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

struct velocity_tendencies_state_t {

};

int tmp_struct_symbol_0;
int tmp_struct_symbol_1;
int tmp_struct_symbol_2;
int tmp_struct_symbol_3;
int tmp_struct_symbol_4;
int tmp_struct_symbol_5;
int tmp_struct_symbol_6;
int tmp_struct_symbol_7;
int tmp_struct_symbol_8;
int tmp_struct_symbol_9;
int tmp_struct_symbol_10;
int tmp_struct_symbol_11;
int tmp_struct_symbol_12;
int tmp_struct_symbol_13;
int tmp_struct_symbol_14;
int tmp_struct_symbol_15;
int tmp_struct_symbol_16;
int tmp_struct_symbol_17;
int tmp_struct_symbol_18;
int tmp_struct_symbol_19;
int tmp_struct_symbol_20;
int tmp_struct_symbol_21;
int tmp_struct_symbol_22;
int tmp_struct_symbol_23;
int tmp_struct_symbol_24;
int __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2;
int __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2;
int __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2;
int __f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2;
int __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2;
int __f2dace_SA_neighbor_idx_d_2_s_148_cells_p_patch_2;
int __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2;
int __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2;
int __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2;
int __f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2;
int __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2;
int __f2dace_SA_neighbor_blk_d_2_s_151_cells_p_patch_2;
int __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2;
int __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2;
int __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2;
int __f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2;
int __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2;
int __f2dace_SA_edge_idx_d_2_s_154_cells_p_patch_2;
int __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2;
int __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2;
int __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2;
int __f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2;
int __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2;
int __f2dace_SA_edge_blk_d_2_s_157_cells_p_patch_2;
int __f2dace_SOA_area_d_0_s_158_cells_p_patch_2;
int __f2dace_SOA_area_d_1_s_159_cells_p_patch_2;
int __f2dace_SA_area_d_0_s_158_cells_p_patch_2;
int __f2dace_SA_area_d_1_s_159_cells_p_patch_2;
int __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2;
int __f2dace_SA_start_index_d_0_s_160_cells_p_patch_2;
int __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2;
int __f2dace_SA_end_index_d_0_s_161_cells_p_patch_2;
int __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2;
int __f2dace_SA_start_block_d_0_s_162_cells_p_patch_2;
int __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2;
int __f2dace_SA_end_block_d_0_s_163_cells_p_patch_2;
int __f2dace_SOA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3;
int __f2dace_SOA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3;
int __f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3;
int __f2dace_SA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3;
int __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4;
int __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4;
int __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4;
int __f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4;
int __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4;
int __f2dace_SA_cell_idx_d_2_s_166_edges_p_patch_4;
int __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4;
int __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4;
int __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4;
int __f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4;
int __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4;
int __f2dace_SA_cell_blk_d_2_s_169_edges_p_patch_4;
int __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4;
int __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4;
int __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4;
int __f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4;
int __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4;
int __f2dace_SA_vertex_idx_d_2_s_172_edges_p_patch_4;
int __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4;
int __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4;
int __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4;
int __f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4;
int __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4;
int __f2dace_SA_vertex_blk_d_2_s_175_edges_p_patch_4;
int __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4;
int __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4;
int __f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4;
int __f2dace_SA_tangent_orientation_d_1_s_177_edges_p_patch_4;
int __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4;
int __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4;
int __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4;
int __f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4;
int __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4;
int __f2dace_SA_quad_idx_d_2_s_180_edges_p_patch_4;
int __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4;
int __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4;
int __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4;
int __f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4;
int __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4;
int __f2dace_SA_quad_blk_d_2_s_183_edges_p_patch_4;
int __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4;
int __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4;
int __f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4;
int __f2dace_SA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4;
int __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4;
int __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4;
int __f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4;
int __f2dace_SA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4;
int __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4;
int __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4;
int __f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4;
int __f2dace_SA_area_edge_d_1_s_189_edges_p_patch_4;
int __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4;
int __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4;
int __f2dace_SA_f_e_d_0_s_190_edges_p_patch_4;
int __f2dace_SA_f_e_d_1_s_191_edges_p_patch_4;
int __f2dace_SOA_fn_e_d_0_s_192_edges_p_patch_4;
int __f2dace_SOA_fn_e_d_1_s_193_edges_p_patch_4;
int __f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4;
int __f2dace_SA_fn_e_d_1_s_193_edges_p_patch_4;
int __f2dace_SOA_ft_e_d_0_s_194_edges_p_patch_4;
int __f2dace_SOA_ft_e_d_1_s_195_edges_p_patch_4;
int __f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4;
int __f2dace_SA_ft_e_d_1_s_195_edges_p_patch_4;
int __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4;
int __f2dace_SA_start_index_d_0_s_196_edges_p_patch_4;
int __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4;
int __f2dace_SA_end_index_d_0_s_197_edges_p_patch_4;
int __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4;
int __f2dace_SA_start_block_d_0_s_198_edges_p_patch_4;
int __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4;
int __f2dace_SA_end_block_d_0_s_199_edges_p_patch_4;
int __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5;
int __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5;
int __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5;
int __f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5;
int __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5;
int __f2dace_SA_cell_idx_d_2_s_202_verts_p_patch_5;
int __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5;
int __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5;
int __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5;
int __f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5;
int __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5;
int __f2dace_SA_cell_blk_d_2_s_205_verts_p_patch_5;
int __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5;
int __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5;
int __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5;
int __f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5;
int __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5;
int __f2dace_SA_edge_idx_d_2_s_208_verts_p_patch_5;
int __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5;
int __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5;
int __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5;
int __f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5;
int __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5;
int __f2dace_SA_edge_blk_d_2_s_211_verts_p_patch_5;
int __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5;
int __f2dace_SA_start_index_d_0_s_212_verts_p_patch_5;
int __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5;
int __f2dace_SA_end_index_d_0_s_213_verts_p_patch_5;
int __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5;
int __f2dace_SA_start_block_d_0_s_214_verts_p_patch_5;
int __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5;
int __f2dace_SA_end_block_d_0_s_215_verts_p_patch_5;
int __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6;
int __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6;
int __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6;
int __f2dace_SA_c_lin_e_d_0_s_25_p_int_6;
int __f2dace_SA_c_lin_e_d_1_s_26_p_int_6;
int __f2dace_SA_c_lin_e_d_2_s_27_p_int_6;
int __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6;
int __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6;
int __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6;
int __f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6;
int __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6;
int __f2dace_SA_e_bln_c_s_d_2_s_30_p_int_6;
int __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6;
int __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6;
int __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6;
int __f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6;
int __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6;
int __f2dace_SA_cells_aw_verts_d_2_s_33_p_int_6;
int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6;
int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6;
int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6;
int __f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6;
int __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6;
int __f2dace_SA_rbf_vec_coeff_e_d_2_s_36_p_int_6;
int __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6;
int __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6;
int __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6;
int __f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6;
int __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6;
int __f2dace_SA_geofac_grdiv_d_2_s_39_p_int_6;
int __f2dace_SOA_geofac_rot_d_0_s_40_p_int_6;
int __f2dace_SOA_geofac_rot_d_1_s_41_p_int_6;
int __f2dace_SOA_geofac_rot_d_2_s_42_p_int_6;
int __f2dace_SA_geofac_rot_d_0_s_40_p_int_6;
int __f2dace_SA_geofac_rot_d_1_s_41_p_int_6;
int __f2dace_SA_geofac_rot_d_2_s_42_p_int_6;
int __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6;
int __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6;
int __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6;
int __f2dace_SA_geofac_n2s_d_0_s_43_p_int_6;
int __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6;
int __f2dace_SA_geofac_n2s_d_2_s_45_p_int_6;
int __f2dace_SOA_w_d_0_s_288_p_prog_7;
int __f2dace_SOA_w_d_1_s_289_p_prog_7;
int __f2dace_SOA_w_d_2_s_290_p_prog_7;
int __f2dace_SA_w_d_0_s_288_p_prog_7;
int __f2dace_SA_w_d_1_s_289_p_prog_7;
int __f2dace_SA_w_d_2_s_290_p_prog_7;
int __f2dace_SOA_vn_d_0_s_291_p_prog_7;
int __f2dace_SOA_vn_d_1_s_292_p_prog_7;
int __f2dace_SOA_vn_d_2_s_293_p_prog_7;
int __f2dace_SA_vn_d_0_s_291_p_prog_7;
int __f2dace_SA_vn_d_1_s_292_p_prog_7;
int __f2dace_SA_vn_d_2_s_293_p_prog_7;
int __f2dace_SOA_ddxn_z_full_d_0_s_314_p_metrics_8;
int __f2dace_SOA_ddxn_z_full_d_1_s_315_p_metrics_8;
int __f2dace_SOA_ddxn_z_full_d_2_s_316_p_metrics_8;
int __f2dace_SA_ddxn_z_full_d_0_s_314_p_metrics_8;
int __f2dace_SA_ddxn_z_full_d_1_s_315_p_metrics_8;
int __f2dace_SA_ddxn_z_full_d_2_s_316_p_metrics_8;
int __f2dace_SOA_ddxt_z_full_d_0_s_317_p_metrics_8;
int __f2dace_SOA_ddxt_z_full_d_1_s_318_p_metrics_8;
int __f2dace_SOA_ddxt_z_full_d_2_s_319_p_metrics_8;
int __f2dace_SA_ddxt_z_full_d_0_s_317_p_metrics_8;
int __f2dace_SA_ddxt_z_full_d_1_s_318_p_metrics_8;
int __f2dace_SA_ddxt_z_full_d_2_s_319_p_metrics_8;
int __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8;
int __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8;
int __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8;
int __f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8;
int __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8;
int __f2dace_SA_ddqz_z_full_e_d_2_s_322_p_metrics_8;
int __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8;
int __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8;
int __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8;
int __f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8;
int __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8;
int __f2dace_SA_ddqz_z_half_d_2_s_325_p_metrics_8;
int __f2dace_SOA_wgtfac_c_d_0_s_326_p_metrics_8;
int __f2dace_SOA_wgtfac_c_d_1_s_327_p_metrics_8;
int __f2dace_SOA_wgtfac_c_d_2_s_328_p_metrics_8;
int __f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8;
int __f2dace_SA_wgtfac_c_d_1_s_327_p_metrics_8;
int __f2dace_SA_wgtfac_c_d_2_s_328_p_metrics_8;
int __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8;
int __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8;
int __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8;
int __f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8;
int __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8;
int __f2dace_SA_wgtfac_e_d_2_s_331_p_metrics_8;
int __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8;
int __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8;
int __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8;
int __f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8;
int __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8;
int __f2dace_SA_wgtfacq_e_d_2_s_334_p_metrics_8;
int __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8;
int __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8;
int __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8;
int __f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8;
int __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8;
int __f2dace_SA_coeff_gradekin_d_2_s_337_p_metrics_8;
int __f2dace_SOA_coeff1_dwdz_d_0_s_338_p_metrics_8;
int __f2dace_SOA_coeff1_dwdz_d_1_s_339_p_metrics_8;
int __f2dace_SOA_coeff1_dwdz_d_2_s_340_p_metrics_8;
int __f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8;
int __f2dace_SA_coeff1_dwdz_d_1_s_339_p_metrics_8;
int __f2dace_SA_coeff1_dwdz_d_2_s_340_p_metrics_8;
int __f2dace_SOA_coeff2_dwdz_d_0_s_341_p_metrics_8;
int __f2dace_SOA_coeff2_dwdz_d_1_s_342_p_metrics_8;
int __f2dace_SOA_coeff2_dwdz_d_2_s_343_p_metrics_8;
int __f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8;
int __f2dace_SA_coeff2_dwdz_d_1_s_342_p_metrics_8;
int __f2dace_SA_coeff2_dwdz_d_2_s_343_p_metrics_8;
int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8;
int __f2dace_SA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8;
int __f2dace_SOA_deepatmo_invr_mc_d_0_s_345_p_metrics_8;
int __f2dace_SA_deepatmo_invr_mc_d_0_s_345_p_metrics_8;
int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_346_p_metrics_8;
int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_346_p_metrics_8;
int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8;
int __f2dace_SA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8;
int __f2dace_SOA_vn_ie_ubc_d_0_s_294_p_diag_9;
int __f2dace_SOA_vn_ie_ubc_d_1_s_295_p_diag_9;
int __f2dace_SOA_vn_ie_ubc_d_2_s_296_p_diag_9;
int __f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9;
int __f2dace_SA_vn_ie_ubc_d_1_s_295_p_diag_9;
int __f2dace_SA_vn_ie_ubc_d_2_s_296_p_diag_9;
int __f2dace_SOA_vt_d_0_s_297_p_diag_9;
int __f2dace_SOA_vt_d_1_s_298_p_diag_9;
int __f2dace_SOA_vt_d_2_s_299_p_diag_9;
int __f2dace_SA_vt_d_0_s_297_p_diag_9;
int __f2dace_SA_vt_d_1_s_298_p_diag_9;
int __f2dace_SA_vt_d_2_s_299_p_diag_9;
int __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9;
int __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9;
int __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9;
int __f2dace_SA_vn_ie_d_0_s_300_p_diag_9;
int __f2dace_SA_vn_ie_d_1_s_301_p_diag_9;
int __f2dace_SA_vn_ie_d_2_s_302_p_diag_9;
int __f2dace_SOA_w_concorr_c_d_0_s_303_p_diag_9;
int __f2dace_SOA_w_concorr_c_d_1_s_304_p_diag_9;
int __f2dace_SOA_w_concorr_c_d_2_s_305_p_diag_9;
int __f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9;
int __f2dace_SA_w_concorr_c_d_1_s_304_p_diag_9;
int __f2dace_SA_w_concorr_c_d_2_s_305_p_diag_9;
int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9;
int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9;
int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9;
int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9;
int __f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9;
int __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9;
int __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9;
int __f2dace_SA_ddt_vn_apc_pc_d_3_s_309_p_diag_9;
int __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9;
int __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9;
int __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9;
int __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9;
int __f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9;
int __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9;
int __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9;
int __f2dace_SA_ddt_w_adv_pc_d_3_s_313_p_diag_9;
void __program_velocity_tendencies_internal(velocity_tendencies_state_t*__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_369, int __f2dace_A_z_kin_hor_e_d_1_s_370, int __f2dace_A_z_vt_ie_d_0_s_372, int __f2dace_A_z_vt_ie_d_1_s_373, int __f2dace_A_z_w_concorr_me_d_0_s_366, int __f2dace_A_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_kin_hor_e_d_0_s_369, int __f2dace_OA_z_kin_hor_e_d_1_s_370, int __f2dace_OA_z_kin_hor_e_d_2_s_371, int __f2dace_OA_z_vt_ie_d_0_s_372, int __f2dace_OA_z_vt_ie_d_1_s_373, int __f2dace_OA_z_vt_ie_d_2_s_374, int __f2dace_OA_z_w_concorr_me_d_0_s_366, int __f2dace_OA_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_w_concorr_me_d_2_s_368, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    double *z_w_concorr_mc;
    z_w_concorr_mc = new double DACE_ALIGN(64)[((tmp_struct_symbol_0 * (tmp_struct_symbol_1 - 1)) + tmp_struct_symbol_0)];
    double *z_w_con_c;
    z_w_con_c = new double DACE_ALIGN(64)[((tmp_struct_symbol_2 * (tmp_struct_symbol_3 - 1)) + tmp_struct_symbol_2)];
    double *z_w_con_c_full;
    z_w_con_c_full = new double DACE_ALIGN(64)[((((tmp_struct_symbol_4 * tmp_struct_symbol_5) * (tmp_struct_symbol_6 - 1)) + (tmp_struct_symbol_4 * (tmp_struct_symbol_5 - 1))) + tmp_struct_symbol_4)];
    double *z_v_grad_w;
    z_v_grad_w = new double DACE_ALIGN(64)[((((tmp_struct_symbol_7 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (tmp_struct_symbol_7 * (tmp_struct_symbol_8 - 1))) + tmp_struct_symbol_7)];
    double *z_w_v;
    z_w_v = new double DACE_ALIGN(64)[((((tmp_struct_symbol_10 * tmp_struct_symbol_11) * (tmp_struct_symbol_12 - 1)) + (tmp_struct_symbol_10 * (tmp_struct_symbol_11 - 1))) + tmp_struct_symbol_10)];
    double *zeta;
    zeta = new double DACE_ALIGN(64)[((((tmp_struct_symbol_13 * tmp_struct_symbol_14) * (tmp_struct_symbol_15 - 1)) + (tmp_struct_symbol_13 * (tmp_struct_symbol_14 - 1))) + tmp_struct_symbol_13)];
    double *z_ekinh;
    z_ekinh = new double DACE_ALIGN(64)[((((tmp_struct_symbol_16 * tmp_struct_symbol_17) * (tmp_struct_symbol_18 - 1)) + (tmp_struct_symbol_16 * (tmp_struct_symbol_17 - 1))) + tmp_struct_symbol_16)];
    int nlev_var_154;
    int nlevp1_var_155;
    int jg;
    double cfl_w_limit;
    double vcfl;
    double maxvcfl;
    double *vcflmax;
    vcflmax = new double DACE_ALIGN(64)[tmp_struct_symbol_19];
    double w_con_e;
    double scalfac_exdiff;
    double difcoef;
    int nrdmax_jg;
    int nflatlev_jg;
    int *levmask;
    levmask = new int DACE_ALIGN(64)[((tmp_struct_symbol_20 * (tmp_struct_symbol_21 - 1)) + tmp_struct_symbol_20)];
    int *levelmask;
    levelmask = new int DACE_ALIGN(64)[tmp_struct_symbol_22];
    int *cfl_clipping;
    cfl_clipping = new int DACE_ALIGN(64)[((tmp_struct_symbol_23 * (tmp_struct_symbol_24 - 1)) + tmp_struct_symbol_23)];
    double tmp_call_2;
    double tmp_call_13;
    double tmp_call_19;
    int _if_cond_9;
    int _if_cond_10;
    int _if_cond_18;
    int _if_cond_25;
    int _if_cond_29;
    double _if_cond_31;
    int* v_global_data_lextra_diffu;
    v_global_data_lextra_diffu = (int*)(&(global_data->lextra_diffu));
    t_grid_edges** v_p_patch_edges;
    v_p_patch_edges = (t_grid_edges**)(&(p_patch->edges));
    t_grid_cells** v_p_patch_cells;
    v_p_patch_cells = (t_grid_cells**)(&(p_patch->cells));
    double* v_p_prog_vn;
    v_p_prog_vn = (double*)(&(p_prog->vn)[0]);
    double* v_p_diag_vt;
    v_p_diag_vt = (double*)(&(p_diag->vt)[0]);
    double* v_p_metrics_wgtfac_e;
    v_p_metrics_wgtfac_e = (double*)(&(p_metrics->wgtfac_e)[0]);
    double* v_p_diag_vn_ie;
    v_p_diag_vn_ie = (double*)(&(p_diag->vn_ie)[0]);
    double* v_p_metrics_wgtfacq_e;
    v_p_metrics_wgtfacq_e = (double*)(&(p_metrics->wgtfacq_e)[0]);
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
    double* v_p_metrics_coeff_gradekin;
    v_p_metrics_coeff_gradekin = (double*)(&(p_metrics->coeff_gradekin)[0]);
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
    double* v_v_p_patch_edges_inv_primal_edge_length;
    v_v_p_patch_edges_inv_primal_edge_length = (double*)(&((*v_p_patch_edges)->inv_primal_edge_length)[0]);
    double* v_v_p_patch_edges_tangent_orientation;
    v_v_p_patch_edges_tangent_orientation = (double*)(&((*v_p_patch_edges)->tangent_orientation)[0]);
    double* v_v_p_patch_edges_ft_e;
    v_v_p_patch_edges_ft_e = (double*)(&((*v_p_patch_edges)->ft_e)[0]);
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
    double* v_v_p_patch_edges_f_e;
    v_v_p_patch_edges_f_e = (double*)(&((*v_p_patch_edges)->f_e)[0]);
    int* v_v_v_p_patch_cells_decomp_info_owner_mask;
    v_v_v_p_patch_cells_decomp_info_owner_mask = (int*)(&((*v_v_p_patch_cells_decomp_info)->owner_mask)[0]);
    global_data_type** global_data_var_83_0;
    global_data_var_83_0 = &global_data;
    int* global_data_var_83_nproma_14;
    global_data_var_83_nproma_14 = (int*)(&((*global_data_var_83_0)->nproma));
    t_patch** p_patch_var_84_3;
    p_patch_var_84_3 = &p_patch;
    t_grid_edges** v_p_patch_var_84_edges;
    v_p_patch_var_84_edges = (t_grid_edges**)(&((*p_patch_var_84_3)->edges));
    int* v_v_p_patch_var_84_edges_start_index;
    v_v_p_patch_var_84_edges_start_index = (int*)(&((*v_p_patch_var_84_edges)->start_index)[0]);
    int* v_v_p_patch_var_84_edges_end_index;
    v_v_p_patch_var_84_edges_end_index = (int*)(&((*v_p_patch_var_84_edges)->end_index)[0]);
    t_patch** p_patch_var_84_0;
    p_patch_var_84_0 = &p_patch;
    global_data_type** global_data_var_71_0;
    global_data_var_71_0 = &global_data;
    int* global_data_var_71_nproma_13;
    global_data_var_71_nproma_13 = (int*)(&((*global_data_var_71_0)->nproma));
    t_patch** p_patch_var_72_1;
    p_patch_var_72_1 = &p_patch;
    t_grid_cells** v_p_patch_var_72_cells;
    v_p_patch_var_72_cells = (t_grid_cells**)(&((*p_patch_var_72_1)->cells));
    int* v_v_p_patch_var_72_cells_start_index;
    v_v_p_patch_var_72_cells_start_index = (int*)(&((*v_p_patch_var_72_cells)->start_index)[0]);
    int* v_v_p_patch_var_72_cells_end_index;
    v_v_p_patch_var_72_cells_end_index = (int*)(&((*v_p_patch_var_72_cells)->end_index)[0]);
    t_patch** p_patch_var_72_0;
    p_patch_var_72_0 = &p_patch;
    global_data_type** global_data_var_71_1;
    global_data_var_71_1 = &global_data;
    int* global_data_var_71_nproma_12;
    global_data_var_71_nproma_12 = (int*)(&((*global_data_var_71_1)->nproma));
    global_data_type** global_data_var_83_1;
    global_data_var_83_1 = &global_data;
    int* global_data_var_83_nproma_11;
    global_data_var_83_nproma_11 = (int*)(&((*global_data_var_83_1)->nproma));
    t_patch** p_patch_var_84_1;
    p_patch_var_84_1 = &p_patch;
    global_data_type** global_data_var_83_2;
    global_data_var_83_2 = &global_data;
    int* global_data_var_83_nproma_10;
    global_data_var_83_nproma_10 = (int*)(&((*global_data_var_83_2)->nproma));
    t_patch** p_patch_var_84_2;
    p_patch_var_84_2 = &p_patch;
    global_data_type** global_data_var_83_3;
    global_data_var_83_3 = &global_data;
    int* global_data_var_83_nproma_9;
    global_data_var_83_nproma_9 = (int*)(&((*global_data_var_83_3)->nproma));
    t_patch** ptr_patch_var_108_0;
    ptr_patch_var_108_0 = &p_patch;
    t_grid_vertices** v_ptr_patch_var_108_verts;
    v_ptr_patch_var_108_verts = (t_grid_vertices**)(&((*ptr_patch_var_108_0)->verts));
    int* v_v_ptr_patch_var_108_verts_start_block;
    v_v_ptr_patch_var_108_verts_start_block = (int*)(&((*v_ptr_patch_var_108_verts)->start_block)[0]);
    int* v_v_ptr_patch_var_108_verts_end_block;
    v_v_ptr_patch_var_108_verts_end_block = (int*)(&((*v_ptr_patch_var_108_verts)->end_block)[0]);
    int* v_v_ptr_patch_var_108_verts_edge_idx;
    v_v_ptr_patch_var_108_verts_edge_idx = (int*)(&((*v_ptr_patch_var_108_verts)->edge_idx)[0]);
    int* v_v_ptr_patch_var_108_verts_edge_blk;
    v_v_ptr_patch_var_108_verts_edge_blk = (int*)(&((*v_ptr_patch_var_108_verts)->edge_blk)[0]);
    global_data_type** global_data_var_107_0;
    global_data_var_107_0 = &global_data;
    global_data_type** global_data_var_95_0;
    global_data_var_95_0 = &(*global_data_var_107_0);
    int* global_data_var_95_nproma_8;
    global_data_var_95_nproma_8 = (int*)(&((*global_data_var_95_0)->nproma));
    t_patch** p_patch_var_96_0;
    p_patch_var_96_0 = &(*ptr_patch_var_108_0);
    t_grid_vertices** v_p_patch_var_96_verts;
    v_p_patch_var_96_verts = (t_grid_vertices**)(&((*p_patch_var_96_0)->verts));
    int* v_v_p_patch_var_96_verts_start_index;
    v_v_p_patch_var_96_verts_start_index = (int*)(&((*v_p_patch_var_96_verts)->start_index)[0]);
    int* v_v_p_patch_var_96_verts_end_index;
    v_v_p_patch_var_96_verts_end_index = (int*)(&((*v_p_patch_var_96_verts)->end_index)[0]);
    t_patch** ptr_patch_var_130_0;
    ptr_patch_var_130_0 = &p_patch;
    t_grid_vertices** v_ptr_patch_var_130_verts;
    v_ptr_patch_var_130_verts = (t_grid_vertices**)(&((*ptr_patch_var_130_0)->verts));
    int* v_v_ptr_patch_var_130_verts_start_block;
    v_v_ptr_patch_var_130_verts_start_block = (int*)(&((*v_ptr_patch_var_130_verts)->start_block)[0]);
    int* v_v_ptr_patch_var_130_verts_end_block;
    v_v_ptr_patch_var_130_verts_end_block = (int*)(&((*v_ptr_patch_var_130_verts)->end_block)[0]);
    int* v_v_ptr_patch_var_130_verts_start_index;
    v_v_ptr_patch_var_130_verts_start_index = (int*)(&((*v_ptr_patch_var_130_verts)->start_index)[0]);
    int* v_v_ptr_patch_var_130_verts_end_index;
    v_v_ptr_patch_var_130_verts_end_index = (int*)(&((*v_ptr_patch_var_130_verts)->end_index)[0]);
    int* v_v_ptr_patch_var_130_verts_cell_idx;
    v_v_ptr_patch_var_130_verts_cell_idx = (int*)(&((*v_ptr_patch_var_130_verts)->cell_idx)[0]);
    int* v_v_ptr_patch_var_130_verts_cell_blk;
    v_v_ptr_patch_var_130_verts_cell_blk = (int*)(&((*v_ptr_patch_var_130_verts)->cell_blk)[0]);
    global_data_type** global_data_var_129_0;
    global_data_var_129_0 = &global_data;
    int* v_global_data_var_129_nproma;
    v_global_data_var_129_nproma = (int*)(&((*global_data_var_129_0)->nproma));
    int tmp_index_162;
    int tmp_index_163;
    int _if_cond_11;
    int i_startblk_var_120_0;
    int i_endblk_var_121_0;
    int _if_cond_12;
    int i_startblk_var_148;
    int i_endblk_var_149;
    int _if_cond_15;
    int _if_cond_16;
    int i_startblk_2;
    int i_endblk_2;
    int tmp_arg_15;
    double tmp_call_20;
    int l_vert_nested;
    int i_startblk_var_142_0;
    int i_endblk_var_143_0;
    int i_startidx_in_var_144_0;
    int i_endidx_in_var_145_0;
    int _for_it_0_0_0;
    int _for_it_1_0_0;
    int tmp_index_12_0_0;
    int tmp_index_48_0_0;
    int tmp_index_72_0_0;
    int tmp_index_62_0_0;
    int tmp_index_24_0_0;
    int tmp_index_60_0_0;
    int tmp_index_74_0_0;
    int tmp_index_26_0_0;
    int tmp_index_38_0_0;
    int tmp_index_36_0_0;
    int tmp_index_50_0_0;
    int tmp_index_14_0_0;
    int _for_it_2_0_0;
    int i_endidx_var_47_0_0;
    int i_startidx_var_46_0_0;
    int i_startidx_in_var_93_3;
    int i_endidx_in_var_94_3;
    int _if_cond_13;
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
    int _for_it_11;
    int _for_it_12;
    int _for_it_13;
    int _for_it_14;
    int tmp_index_293;
    int tmp_index_299;
    int tmp_index_305;
    int tmp_index_311;
    int _for_it_15;
    int tmp_index_338;
    int tmp_index_344;
    int tmp_index_350;
    int tmp_index_356;
    int _for_it_16;
    int i_endidx_var_151;
    int i_startidx_var_150;
    int i_startidx_in_var_93_2;
    int i_endidx_in_var_94_2;
    int _for_it_17;
    int _for_it_18;
    int tmp_index_374;
    int tmp_index_376;
    int tmp_index_383;
    int tmp_index_385;
    int tmp_index_399;
    int tmp_index_401;
    int tmp_index_408;
    int tmp_index_410;
    int _for_it_19;
    int i_startidx_in_var_93_1;
    int i_endidx_in_var_94_1;
    int _for_it_20;
    int _for_it_21;
    int _for_it_22;
    int i_startidx_in_var_81_1;
    int i_endidx_in_var_82_1;
    int _if_cond_17;
    int tmp_arg_9;
    int tmp_arg_10;
    int _if_cond_23;
    int i_startidx_in_var_81_0;
    int i_endidx_in_var_82_0;
    int _for_it_23;
    int _for_it_24;
    int tmp_index_452;
    int tmp_index_454;
    int tmp_index_464;
    int tmp_index_466;
    int tmp_index_476;
    int tmp_index_478;
    int _for_it_25;
    int _for_it_26;
    int tmp_index_490;
    int tmp_index_492;
    int tmp_index_502;
    int tmp_index_504;
    int tmp_index_514;
    int tmp_index_516;
    int _for_it_27;
    int _for_it_28;
    int _for_it_29;
    int _for_it_30;
    int _for_it_31;
    int tmp_index_536;
    int _for_it_32;
    int _for_it_33;
    int _for_it_34;
    int _for_it_35;
    int clip_count;
    int _for_it_36;
    int _for_it_37;
    int _if_cond_20;
    int _for_it_38;
    double _if_cond_21;
    double _if_cond_22;
    int _for_it_39;
    int _for_it_40;
    int _for_it_41;
    int tmp_index_585;
    int _for_it_42;
    int _for_it_43;
    int tmp_index_612;
    int tmp_index_616;
    int tmp_index_626;
    int tmp_index_628;
    int tmp_index_638;
    int tmp_index_640;
    int tmp_index_650;
    int tmp_index_652;
    int _for_it_44;
    int tmp_arg_12;
    int _if_cond_26;
    int _for_it_45;
    int _if_cond_27;
    int _for_it_46;
    int tmp_index_667;
    int tmp_index_671;
    int tmp_index_686;
    int tmp_index_688;
    int tmp_index_698;
    int tmp_index_700;
    int tmp_index_710;
    int tmp_index_712;
    int i_startidx_2;
    int i_endidx_2;
    int tmp_call_15;
    int _for_it_47;
    int tmp_parfor_0;
    int i_startidx_in_var_93_0;
    int i_endidx_in_var_94_0;
    int _if_cond_28;
    int _for_it_48;
    int _for_it_49;
    int tmp_index_724;
    int tmp_index_743;
    int tmp_index_745;
    int tmp_index_755;
    int tmp_index_757;
    int tmp_index_769;
    int tmp_index_771;
    int tmp_index_778;
    int tmp_index_780;
    int tmp_index_790;
    int tmp_index_792;
    int tmp_index_802;
    int tmp_index_804;
    int _for_it_50;
    int _for_it_51;
    int tmp_index_817;
    int tmp_index_836;
    int tmp_index_838;
    int tmp_index_848;
    int tmp_index_850;
    int tmp_index_863;
    int tmp_index_865;
    int tmp_index_872;
    int tmp_index_874;
    int tmp_index_885;
    int tmp_index_887;
    int tmp_index_897;
    int tmp_index_899;
    int _for_it_52;
    int tmp_arg_17;
    int _if_cond_30;
    int _for_it_53;
    int tmp_index_926;
    int tmp_index_928;
    int tmp_index_938;
    int tmp_index_940;
    int _for_it_54;
    int tmp_index_950;
    int tmp_index_954;
    int tmp_index_972;
    int tmp_index_974;
    int tmp_index_984;
    int tmp_index_986;
    int tmp_index_996;
    int tmp_index_998;
    int tmp_index_1008;
    int tmp_index_1010;
    int tmp_index_1021;
    int tmp_index_1023;
    int tmp_index_1030;
    int tmp_index_1032;
    int i_startidx_in_var_105_0_0;
    int i_endidx_in_var_106_0_0;
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
    int i_startidx_var_122_0;
    int i_endidx_var_123_0;


    {
        int* v_global_data_lvert_nest;
        v_global_data_lvert_nest = (int*)(&(global_data->lvert_nest));
        int* v_p_patch_nshift;
        v_p_patch_nshift = (int*)(&(p_patch->nshift));

        {
            int global_data_0_in_lvert_nest = v_global_data_lvert_nest[0];
            int p_patch_0_in_nshift = v_p_patch_nshift[0];
            int _if_cond_9_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_9_out = (global_data_0_in_lvert_nest && (p_patch_0_in_nshift > 0));
            ///////////////////

            _if_cond_9 = _if_cond_9_out;
        }

    }

    if ((_if_cond_9 == 1)) {

        l_vert_nested = 1;

    } else {

        l_vert_nested = 0;

    }

    {
        int* v_p_patch_id;
        v_p_patch_id = (int*)(&(p_patch->id));

        {
            int p_patch_0_in_id = v_p_patch_id[0];
            int jg_out;

            ///////////////////
            // Tasklet code (T_l418_c418)
            jg_out = p_patch_0_in_id;
            ///////////////////

            jg = jg_out;
        }

    }
    tmp_index_162 = (jg - 1);
    tmp_index_163 = (jg - 1);

    {
        int* v_global_data_nrdmax;
        v_global_data_nrdmax = (int*)(&(global_data->nrdmax)[0]);
        int* v_global_data_nflatlev;
        v_global_data_nflatlev = (int*)(&(global_data->nflatlev)[0]);
        int* v_p_patch_nlev;
        v_p_patch_nlev = (int*)(&(p_patch->nlev));
        int* v_p_patch_nlevp1;
        v_p_patch_nlevp1 = (int*)(&(p_patch->nlevp1));

        {
            int global_data_0_in_nrdmax_0 = v_global_data_nrdmax[tmp_index_162];
            int nrdmax_jg_out;

            ///////////////////
            // Tasklet code (T_l419_c419)
            nrdmax_jg_out = global_data_0_in_nrdmax_0;
            ///////////////////

            nrdmax_jg = nrdmax_jg_out;
        }
        {
            int global_data_0_in_nflatlev_0 = v_global_data_nflatlev[tmp_index_163];
            int nflatlev_jg_out;

            ///////////////////
            // Tasklet code (T_l420_c420)
            nflatlev_jg_out = global_data_0_in_nflatlev_0;
            ///////////////////

            nflatlev_jg = nflatlev_jg_out;
        }
        {
            int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
            int _if_cond_10_out;

            ///////////////////
            // Tasklet code (T_l0_c0)
            _if_cond_10_out = global_data_0_in_lextra_diffu;
            ///////////////////

            _if_cond_10 = _if_cond_10_out;
        }
        {
            int p_patch_0_in_nlev = v_p_patch_nlev[0];
            int nlev_var_154_out;

            ///////////////////
            // Tasklet code (T_l421_c421)
            nlev_var_154_out = p_patch_0_in_nlev;
            ///////////////////

            nlev_var_154 = nlev_var_154_out;
        }
        {
            int p_patch_0_in_nlevp1 = v_p_patch_nlevp1[0];
            int nlevp1_var_155_out;

            ///////////////////
            // Tasklet code (T_l422_c422)
            nlevp1_var_155_out = p_patch_0_in_nlevp1;
            ///////////////////

            nlevp1_var_155 = nlevp1_var_155_out;
        }

    }

    if ((_if_cond_10 == 1)) {
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

        }
    } else {
        {

            {
                double dtime_0_in = dtime;
                double cfl_w_limit_out;

                ///////////////////
                // Tasklet code (T_l427_c427)
                cfl_w_limit_out = (0.85 / dtime_0_in);
                ///////////////////

                cfl_w_limit = cfl_w_limit_out;
            }
            {
                double scalfac_exdiff_out;

                ///////////////////
                // Tasklet code (T_l428_c428)
                scalfac_exdiff_out = 0.0;
                ///////////////////

                scalfac_exdiff = scalfac_exdiff_out;
            }

        }
    }
    _if_cond_11 = (1 - lvn_only);

    if ((_if_cond_11 == 1)) {
        {


        }
        i_startblk_var_142_0 = v_v_ptr_patch_var_130_verts_start_block[(2 - __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5)];
        {


        }
        i_endblk_var_143_0 = v_v_ptr_patch_var_130_verts_end_block[((- __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5) - 5)];
        {


        }
        i_startidx_in_var_144_0 = v_v_ptr_patch_var_130_verts_start_index[(2 - __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5)];
        {


        }
        i_endidx_in_var_145_0 = v_v_ptr_patch_var_130_verts_end_index[((- __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5) - 5)];
        for (_for_it_0_0_0 = i_startblk_var_142_0; (_for_it_0_0_0 <= i_endblk_var_143_0); _for_it_0_0_0 = (_for_it_0_0_0 + 1)) {
            if (((_for_it_0_0_0 == i_startblk_var_142_0) == 1)) {
                {


                }
                i_endidx_var_47_0_0 = v_global_data_var_129_nproma[0];
                i_startidx_var_46_0_0 = i_startidx_in_var_144_0;
                if (((_for_it_0_0_0 == i_endblk_var_143_0) == 1)) {

                    i_endidx_var_47_0_0 = i_endidx_in_var_145_0;

                }
            } else {
                if (((_for_it_0_0_0 == i_endblk_var_143_0) == 1)) {

                    i_endidx_var_47_0_0 = i_endidx_in_var_145_0;
                    i_startidx_var_46_0_0 = 1;

                } else {
                    {


                    }
                    i_endidx_var_47_0_0 = v_global_data_var_129_nproma[0];
                    i_startidx_var_46_0_0 = 1;

                }
            }
            for (_for_it_1_0_0 = 1; (_for_it_1_0_0 <= __f2dace_SA_w_d_1_s_289_p_prog_7); _for_it_1_0_0 = (_for_it_1_0_0 + 1)) {
                for (_for_it_2_0_0 = i_startidx_var_46_0_0; (_for_it_2_0_0 <= i_endidx_var_47_0_0); _for_it_2_0_0 = (_for_it_2_0_0 + 1)) {
                    {


                    }
                    tmp_index_12_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (1 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_48_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (4 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_72_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (6 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_62_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (5 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    tmp_index_24_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (2 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_60_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (5 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_74_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (6 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    tmp_index_26_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (2 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    tmp_index_38_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (3 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    tmp_index_36_0_0 = (v_v_ptr_patch_var_130_verts_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * __f2dace_SA_cell_idx_d_1_s_201_verts_p_patch_5) * (3 - __f2dace_SOA_cell_idx_d_2_s_202_verts_p_patch_5)) + (__f2dace_SA_cell_idx_d_0_s_200_verts_p_patch_5 * ((- __f2dace_SOA_cell_idx_d_1_s_201_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_idx_d_0_s_200_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    tmp_index_50_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (4 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    tmp_index_14_0_0 = (v_v_ptr_patch_var_130_verts_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * __f2dace_SA_cell_blk_d_1_s_204_verts_p_patch_5) * (1 - __f2dace_SOA_cell_blk_d_2_s_205_verts_p_patch_5)) + (__f2dace_SA_cell_blk_d_0_s_203_verts_p_patch_5 * ((- __f2dace_SOA_cell_blk_d_1_s_204_verts_p_patch_5) + _for_it_0_0_0))) - __f2dace_SOA_cell_blk_d_0_s_203_verts_p_patch_5) + _for_it_2_0_0)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    {
                        double* p_prog_w_1;
                        p_prog_w_1 = (double*)(&(p_prog->w)[0]);
                        double* p_int_cells_aw_verts_2;
                        p_int_cells_aw_verts_2 = (double*)(&(p_int->cells_aw_verts)[0]);

                        {
                            double c_int_var_33_0_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (1 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double c_int_var_33_1_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (2 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double c_int_var_33_2_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (3 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double c_int_var_33_3_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (4 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double c_int_var_33_4_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (5 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double c_int_var_33_5_in_0 = p_int_cells_aw_verts_2[(((((__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * __f2dace_SA_cells_aw_verts_d_1_s_32_p_int_6) * ((- __f2dace_SOA_cells_aw_verts_d_2_s_33_p_int_6) + _for_it_0_0_0)) + (__f2dace_SA_cells_aw_verts_d_0_s_31_p_int_6 * (6 - __f2dace_SOA_cells_aw_verts_d_1_s_32_p_int_6))) - __f2dace_SOA_cells_aw_verts_d_0_s_31_p_int_6) + _for_it_2_0_0)];
                            double p_cell_in_var_32_0_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_14_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_12_0_0)];
                            double p_cell_in_var_32_1_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_26_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_24_0_0)];
                            double p_cell_in_var_32_2_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_38_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_36_0_0)];
                            double p_cell_in_var_32_3_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_50_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_48_0_0)];
                            double p_cell_in_var_32_4_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_62_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_60_0_0)];
                            double p_cell_in_var_32_5_in_0 = p_prog_w_1[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_74_0_0) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_1_0_0))) + tmp_index_72_0_0)];
                            double p_vert_out_var_34_out_0;

                            ///////////////////
                            // Tasklet code (T_l117_c117)
                            p_vert_out_var_34_out_0 = ((((((c_int_var_33_0_in_0 * p_cell_in_var_32_0_in_0) + (c_int_var_33_1_in_0 * p_cell_in_var_32_1_in_0)) + (c_int_var_33_2_in_0 * p_cell_in_var_32_2_in_0)) + (c_int_var_33_3_in_0 * p_cell_in_var_32_3_in_0)) + (c_int_var_33_4_in_0 * p_cell_in_var_32_4_in_0)) + (c_int_var_33_5_in_0 * p_cell_in_var_32_5_in_0));
                            ///////////////////

                            z_w_v[(((_for_it_2_0_0 + ((tmp_struct_symbol_10 * tmp_struct_symbol_11) * (_for_it_0_0_0 - 1))) + (tmp_struct_symbol_10 * (_for_it_1_0_0 - 1))) - 1)] = p_vert_out_var_34_out_0;
                        }

                    }

                }

            }

        }
    }

    {


    }
    i_startblk_var_120_0 = v_v_ptr_patch_var_108_verts_start_block[(2 - __f2dace_SOA_start_block_d_0_s_214_verts_p_patch_5)];

    {


    }
    i_endblk_var_121_0 = v_v_ptr_patch_var_108_verts_end_block[((- __f2dace_SOA_end_block_d_0_s_215_verts_p_patch_5) - 5)];

    for (_for_it_3_0 = i_startblk_var_120_0; (_for_it_3_0 <= i_endblk_var_121_0); _for_it_3_0 = (_for_it_3_0 + 1)) {
        {


        }
        i_startidx_in_var_105_0_0 = v_v_p_patch_var_96_verts_start_index[(2 - __f2dace_SOA_start_index_d_0_s_212_verts_p_patch_5)];
        {


        }
        i_endidx_in_var_106_0_0 = v_v_p_patch_var_96_verts_end_index[((- __f2dace_SOA_end_index_d_0_s_213_verts_p_patch_5) - 5)];
        if (((_for_it_3_0 == i_startblk_var_120_0) == 1)) {

            i_startidx_var_122_0 = i_startidx_in_var_105_0_0;
            {


            }
            i_endidx_var_123_0 = global_data_var_95_nproma_8[0];
            if (((_for_it_3_0 == i_endblk_var_121_0) == 1)) {

                i_endidx_var_123_0 = i_endidx_in_var_106_0_0;

            }
        } else {
            if (((_for_it_3_0 == i_endblk_var_121_0) == 1)) {

                i_endidx_var_123_0 = i_endidx_in_var_106_0_0;
                i_startidx_var_122_0 = 1;

            } else {

                i_startidx_var_122_0 = 1;
                {


                }
                i_endidx_var_123_0 = global_data_var_95_nproma_8[0];

            }
        }
        for (_for_it_4_0 = 1; (_for_it_4_0 <= __f2dace_SA_vn_d_1_s_292_p_prog_7); _for_it_4_0 = (_for_it_4_0 + 1)) {
            for (_for_it_5_0 = i_startidx_var_122_0; (_for_it_5_0 <= i_endidx_var_123_0); _for_it_5_0 = (_for_it_5_0 + 1)) {
                {


                }
                tmp_index_92_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (1 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_94_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (1 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                {


                }
                tmp_index_104_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (2 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_106_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (2 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                {


                }
                tmp_index_116_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (3 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_118_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (3 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                {


                }
                tmp_index_128_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (4 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_130_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (4 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                {


                }
                tmp_index_140_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (5 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_142_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (5 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                {


                }
                tmp_index_152_0 = (v_v_ptr_patch_var_108_verts_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * __f2dace_SA_edge_idx_d_1_s_207_verts_p_patch_5) * (6 - __f2dace_SOA_edge_idx_d_2_s_208_verts_p_patch_5)) + (__f2dace_SA_edge_idx_d_0_s_206_verts_p_patch_5 * ((- __f2dace_SOA_edge_idx_d_1_s_207_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_idx_d_0_s_206_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                {


                }
                tmp_index_154_0 = (v_v_ptr_patch_var_108_verts_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * __f2dace_SA_edge_blk_d_1_s_210_verts_p_patch_5) * (6 - __f2dace_SOA_edge_blk_d_2_s_211_verts_p_patch_5)) + (__f2dace_SA_edge_blk_d_0_s_209_verts_p_patch_5 * ((- __f2dace_SOA_edge_blk_d_1_s_210_verts_p_patch_5) + _for_it_3_0))) - __f2dace_SOA_edge_blk_d_0_s_209_verts_p_patch_5) + _for_it_5_0)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
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
                        double vec_e_0_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_94_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_92_0)];
                        double vec_e_1_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_106_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_104_0)];
                        double vec_e_2_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_118_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_116_0)];
                        double vec_e_3_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_130_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_128_0)];
                        double vec_e_4_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_142_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_140_0)];
                        double vec_e_5_in_0 = p_prog_vn_7[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_154_0) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_4_0))) + tmp_index_152_0)];
                        double rot_vec_out_0;

                        ///////////////////
                        // Tasklet code (T_l296_c296)
                        rot_vec_out_0 = ((((((vec_e_0_in_0 * ptr_int_0_in_geofac_rot_0) + (vec_e_1_in_0 * ptr_int_1_in_geofac_rot_0)) + (vec_e_2_in_0 * ptr_int_2_in_geofac_rot_0)) + (vec_e_3_in_0 * ptr_int_3_in_geofac_rot_0)) + (vec_e_4_in_0 * ptr_int_4_in_geofac_rot_0)) + (vec_e_5_in_0 * ptr_int_5_in_geofac_rot_0));
                        ///////////////////

                        zeta[(((_for_it_5_0 + ((tmp_struct_symbol_13 * tmp_struct_symbol_14) * (_for_it_3_0 - 1))) + (tmp_struct_symbol_13 * (_for_it_4_0 - 1))) - 1)] = rot_vec_out_0;
                    }

                }

            }

        }

    }
    _if_cond_12 = (istep == 1);

    if ((_if_cond_12 == 1)) {
        {


        }
        i_startblk_var_148 = v_v_p_patch_edges_start_block[(5 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];
        {


        }
        i_endblk_var_149 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 10)];
        for (_for_it_6 = i_startblk_var_148; (_for_it_6 <= i_endblk_var_149); _for_it_6 = (_for_it_6 + 1)) {
            {


            }
            i_startidx_in_var_93_3 = v_v_p_patch_var_84_edges_start_index[(5 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
            {


            }
            i_endidx_in_var_94_3 = v_v_p_patch_var_84_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 10)];
            if ((_for_it_6 != i_startblk_var_148)) {

                i_startidx_var_150 = 1;

            } else {

                i_startidx_var_150 = max(1, i_startidx_in_var_93_3);

            }
            if ((_for_it_6 != i_endblk_var_149)) {
                {


                }
                i_endidx_var_151 = global_data_var_83_nproma_9[0];

            } else {

                i_endidx_var_151 = i_endidx_in_var_94_3;

            }
            for (_for_it_7 = 1; (_for_it_7 <= nlev_var_154); _for_it_7 = (_for_it_7 + 1)) {
                for (_for_it_8 = i_startidx_var_150; (_for_it_8 <= i_endidx_var_151); _for_it_8 = (_for_it_8 + 1)) {
                    {


                    }
                    tmp_index_178 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                    {


                    }
                    tmp_index_180 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                    {


                    }
                    tmp_index_190 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                    {


                    }
                    tmp_index_192 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                    {


                    }
                    tmp_index_202 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                    {


                    }
                    tmp_index_204 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                    {


                    }
                    tmp_index_214 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                    {


                    }
                    tmp_index_216 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_6))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_8)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                    {
                        double* v_p_int_rbf_vec_coeff_e;
                        v_p_int_rbf_vec_coeff_e = (double*)(&(p_int->rbf_vec_coeff_e)[0]);

                        {
                            double p_int_0_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 1)];
                            double p_int_1_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 2)];
                            double p_int_2_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 3)];
                            double p_int_3_in_rbf_vec_coeff_e_0 = v_p_int_rbf_vec_coeff_e[(((((__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * __f2dace_SA_rbf_vec_coeff_e_d_1_s_35_p_int_6) * ((- __f2dace_SOA_rbf_vec_coeff_e_d_2_s_36_p_int_6) + _for_it_6)) + (__f2dace_SA_rbf_vec_coeff_e_d_0_s_34_p_int_6 * ((- __f2dace_SOA_rbf_vec_coeff_e_d_1_s_35_p_int_6) + _for_it_8))) - __f2dace_SOA_rbf_vec_coeff_e_d_0_s_34_p_int_6) + 4)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_180) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_7))) + tmp_index_178)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_192) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_7))) + tmp_index_190)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_204) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_7))) + tmp_index_202)];
                            double p_prog_3_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_216) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_7))) + tmp_index_214)];
                            double p_diag_out_vt_0;

                            ///////////////////
                            // Tasklet code (T_l441_c441)
                            p_diag_out_vt_0 = ((((p_int_0_in_rbf_vec_coeff_e_0 * p_prog_0_in_vn_0) + (p_int_1_in_rbf_vec_coeff_e_0 * p_prog_1_in_vn_0)) + (p_int_2_in_rbf_vec_coeff_e_0 * p_prog_2_in_vn_0)) + (p_int_3_in_rbf_vec_coeff_e_0 * p_prog_3_in_vn_0));
                            ///////////////////

                            v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_7))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_8)] = p_diag_out_vt_0;
                        }

                    }

                }

            }
            for (_for_it_9 = 2; (_for_it_9 <= nlev_var_154); _for_it_9 = (_for_it_9 + 1)) {
                for (_for_it_10 = i_startidx_var_150; (_for_it_10 <= i_endidx_var_151); _for_it_10 = (_for_it_10 + 1)) {
                    {

                        {
                            double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8) + _for_it_9))) - __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8) + _for_it_10)];
                            double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8) + _for_it_9))) - __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8) + _for_it_10)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_9))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_10)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * (((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_9) - 1))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_10)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l446_c446)
                            p_diag_out_vn_ie_0 = ((p_metrics_0_in_wgtfac_e_0 * p_prog_0_in_vn_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_prog_1_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_9))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_10)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_9))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_10)];
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
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_9))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_10)];
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

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_371) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_9))) - __f2dace_OA_z_kin_hor_e_d_0_s_369) + _for_it_10)] = z_kin_hor_e_out_0;
                        }

                    }

                }

            }
            _if_cond_13 = (1 - lvn_only);
            if ((_if_cond_13 == 1)) {
                for (_for_it_11 = 2; (_for_it_11 <= nlev_var_154); _for_it_11 = (_for_it_11 + 1)) {
                    for (_for_it_12 = i_startidx_var_150; (_for_it_12 <= i_endidx_var_151); _for_it_12 = (_for_it_12 + 1)) {
                        {

                            {
                                double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_11))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_12)];
                                double p_diag_1_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * (((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_11) - 1))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_12)];
                                double p_metrics_0_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8) + _for_it_11))) - __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8) + _for_it_12)];
                                double p_metrics_1_in_wgtfac_e_0 = v_p_metrics_wgtfac_e[(((((__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8) * ((- __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 * ((- __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8) + _for_it_11))) - __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8) + _for_it_12)];
                                double z_vt_ie_out_0;

                                ///////////////////
                                // Tasklet code (T_l453_c453)
                                z_vt_ie_out_0 = ((p_metrics_0_in_wgtfac_e_0 * p_diag_0_in_vt_0) + ((1.0 - p_metrics_1_in_wgtfac_e_0) * p_diag_1_in_vt_0));
                                ///////////////////

                                z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_372 * ((- __f2dace_OA_z_vt_ie_d_1_s_373) + _for_it_11))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_12)] = z_vt_ie_out_0;
                            }

                        }

                    }

                }
            }
            for (_for_it_13 = nflatlev_jg; (_for_it_13 <= nlev_var_154); _for_it_13 = (_for_it_13 + 1)) {
                for (_for_it_14 = i_startidx_var_150; (_for_it_14 <= i_endidx_var_151); _for_it_14 = (_for_it_14 + 1)) {
                    {
                        double* v_p_metrics_ddxn_z_full;
                        v_p_metrics_ddxn_z_full = (double*)(&(p_metrics->ddxn_z_full)[0]);
                        double* v_p_metrics_ddxt_z_full;
                        v_p_metrics_ddxt_z_full = (double*)(&(p_metrics->ddxt_z_full)[0]);

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_13))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_14)];
                            double p_metrics_0_in_ddxn_z_full_0 = v_p_metrics_ddxn_z_full[(((((__f2dace_SA_ddxn_z_full_d_0_s_314_p_metrics_8 * __f2dace_SA_ddxn_z_full_d_1_s_315_p_metrics_8) * ((- __f2dace_SOA_ddxn_z_full_d_2_s_316_p_metrics_8) + _for_it_6)) + (__f2dace_SA_ddxn_z_full_d_0_s_314_p_metrics_8 * ((- __f2dace_SOA_ddxn_z_full_d_1_s_315_p_metrics_8) + _for_it_13))) - __f2dace_SOA_ddxn_z_full_d_0_s_314_p_metrics_8) + _for_it_14)];
                            double p_metrics_1_in_ddxt_z_full_0 = v_p_metrics_ddxt_z_full[(((((__f2dace_SA_ddxt_z_full_d_0_s_317_p_metrics_8 * __f2dace_SA_ddxt_z_full_d_1_s_318_p_metrics_8) * ((- __f2dace_SOA_ddxt_z_full_d_2_s_319_p_metrics_8) + _for_it_6)) + (__f2dace_SA_ddxt_z_full_d_0_s_317_p_metrics_8 * ((- __f2dace_SOA_ddxt_z_full_d_1_s_318_p_metrics_8) + _for_it_13))) - __f2dace_SOA_ddxt_z_full_d_0_s_317_p_metrics_8) + _for_it_14)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_13))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_14)];
                            double z_w_concorr_me_out_0;

                            ///////////////////
                            // Tasklet code (T_l459_c459)
                            z_w_concorr_me_out_0 = ((p_prog_0_in_vn_0 * p_metrics_0_in_ddxn_z_full_0) + (p_diag_0_in_vt_0 * p_metrics_1_in_ddxt_z_full_0));
                            ///////////////////

                            z_w_concorr_me[(((((__f2dace_A_z_w_concorr_me_d_0_s_366 * __f2dace_A_z_w_concorr_me_d_1_s_367) * ((- __f2dace_OA_z_w_concorr_me_d_2_s_368) + _for_it_6)) + (__f2dace_A_z_w_concorr_me_d_0_s_366 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_367) + _for_it_13))) - __f2dace_OA_z_w_concorr_me_d_0_s_366) + _for_it_14)] = z_w_concorr_me_out_0;
                        }

                    }

                }

            }
            if (((1 - l_vert_nested) == 1)) {
                for (_for_it_15 = i_startidx_var_150; (_for_it_15 <= i_endidx_var_151); _for_it_15 = (_for_it_15 + 1)) {
                    {

                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_292_p_prog_7))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_15)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l464_c464)
                            p_diag_out_vn_ie_0 = p_prog_0_in_vn_0;
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * (1 - __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_298_p_diag_9))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_15)];
                            double z_vt_ie_out_0;

                            ///////////////////
                            // Tasklet code (T_l465_c465)
                            z_vt_ie_out_0 = p_diag_0_in_vt_0;
                            ///////////////////

                            z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_372 * (1 - __f2dace_OA_z_vt_ie_d_1_s_373))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_15)] = z_vt_ie_out_0;
                        }

                    }
                    tmp_index_293 = (nlevp1_var_155 - __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9);
                    tmp_index_299 = (nlev_var_154 - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    tmp_index_305 = ((nlev_var_154 - 1) - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    tmp_index_311 = ((nlev_var_154 - 2) - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    {
                        double tmp_call_4;
                        double tmp_call_3;

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_298_p_diag_9))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_15)];
                            double tmp_call_4_out;

                            ///////////////////
                            // Tasklet code (T_l466_c466)
                            tmp_call_4_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                            ///////////////////

                            tmp_call_4 = tmp_call_4_out;
                        }
                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_292_p_prog_7))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_15)];
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

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_371) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * (1 - __f2dace_OA_z_kin_hor_e_d_1_s_370))) - __f2dace_OA_z_kin_hor_e_d_0_s_369) + _for_it_15)] = z_kin_hor_e_out_0;
                        }

                    }
                    {

                        {
                            double p_metrics_0_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_15)];
                            double p_metrics_1_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_15)];
                            double p_metrics_2_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_15)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_299)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_15)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_305)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_15)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_311)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_15)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l467_c467)
                            p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * tmp_index_293)) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_15)] = p_diag_out_vn_ie_0;
                        }

                    }

                }
            } else {
                for (_for_it_16 = i_startidx_var_150; (_for_it_16 <= i_endidx_var_151); _for_it_16 = (_for_it_16 + 1)) {
                    {
                        double* v_p_diag_vn_ie_ubc;
                        v_p_diag_vn_ie_ubc = (double*)(&(p_diag->vn_ie_ubc)[0]);

                        {
                            double dt_linintp_ubc_0_in = dt_linintp_ubc;
                            double p_diag_0_in_vn_ie_ubc_0 = v_p_diag_vn_ie_ubc[(((((__f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9 * __f2dace_SA_vn_ie_ubc_d_1_s_295_p_diag_9) * ((- __f2dace_SOA_vn_ie_ubc_d_2_s_296_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9 * (1 - __f2dace_SOA_vn_ie_ubc_d_1_s_295_p_diag_9))) - __f2dace_SOA_vn_ie_ubc_d_0_s_294_p_diag_9) + _for_it_16)];
                            double p_diag_1_in_vn_ie_ubc_0 = v_p_diag_vn_ie_ubc[(((((__f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9 * __f2dace_SA_vn_ie_ubc_d_1_s_295_p_diag_9) * ((- __f2dace_SOA_vn_ie_ubc_d_2_s_296_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9 * (2 - __f2dace_SOA_vn_ie_ubc_d_1_s_295_p_diag_9))) - __f2dace_SOA_vn_ie_ubc_d_0_s_294_p_diag_9) + _for_it_16)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l471_c471)
                            p_diag_out_vn_ie_0 = (p_diag_0_in_vn_ie_ubc_0 + (dt_linintp_ubc_0_in * p_diag_1_in_vn_ie_ubc_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * (1 - __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_16)] = p_diag_out_vn_ie_0;
                        }
                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_298_p_diag_9))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_16)];
                            double z_vt_ie_out_0;

                            ///////////////////
                            // Tasklet code (T_l472_c472)
                            z_vt_ie_out_0 = p_diag_0_in_vt_0;
                            ///////////////////

                            z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_6)) + (__f2dace_A_z_vt_ie_d_0_s_372 * (1 - __f2dace_OA_z_vt_ie_d_1_s_373))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_16)] = z_vt_ie_out_0;
                        }

                    }
                    tmp_index_338 = (nlevp1_var_155 - __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9);
                    tmp_index_344 = (nlev_var_154 - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    tmp_index_350 = ((nlev_var_154 - 1) - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    tmp_index_356 = ((nlev_var_154 - 2) - __f2dace_SOA_vn_d_1_s_292_p_prog_7);
                    {
                        double tmp_call_6;
                        double tmp_call_5;

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_6)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * (1 - __f2dace_SOA_vt_d_1_s_298_p_diag_9))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_16)];
                            double tmp_call_6_out;

                            ///////////////////
                            // Tasklet code (T_l473_c473)
                            tmp_call_6_out = (dace::math::ipow(p_diag_0_in_vt_0, 2));
                            ///////////////////

                            tmp_call_6 = tmp_call_6_out;
                        }
                        {
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * (1 - __f2dace_SOA_vn_d_1_s_292_p_prog_7))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_16)];
                            double tmp_call_5_out;

                            ///////////////////
                            // Tasklet code (T_l473_c473)
                            tmp_call_5_out = (dace::math::ipow(p_prog_0_in_vn_0, 2));
                            ///////////////////

                            tmp_call_5 = tmp_call_5_out;
                        }
                        {
                            double tmp_call_5_0_in = tmp_call_5;
                            double tmp_call_6_0_in = tmp_call_6;
                            double z_kin_hor_e_out_0;

                            ///////////////////
                            // Tasklet code (T_l473_c473)
                            z_kin_hor_e_out_0 = (0.5 * (tmp_call_5_0_in + tmp_call_6_0_in));
                            ///////////////////

                            z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_371) + _for_it_6)) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * (1 - __f2dace_OA_z_kin_hor_e_d_1_s_370))) - __f2dace_OA_z_kin_hor_e_d_0_s_369) + _for_it_16)] = z_kin_hor_e_out_0;
                        }

                    }
                    {

                        {
                            double p_metrics_0_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (1 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_16)];
                            double p_metrics_1_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (2 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_16)];
                            double p_metrics_2_in_wgtfacq_e_0 = v_p_metrics_wgtfacq_e[(((((__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8) * ((- __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8) + _for_it_6)) + (__f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 * (3 - __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8))) - __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8) + _for_it_16)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_344)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_16)];
                            double p_prog_1_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_350)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_16)];
                            double p_prog_2_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_6)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * tmp_index_356)) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_16)];
                            double p_diag_out_vn_ie_0;

                            ///////////////////
                            // Tasklet code (T_l474_c474)
                            p_diag_out_vn_ie_0 = (((p_metrics_0_in_wgtfacq_e_0 * p_prog_0_in_vn_0) + (p_metrics_1_in_wgtfacq_e_0 * p_prog_1_in_vn_0)) + (p_metrics_2_in_wgtfacq_e_0 * p_prog_2_in_vn_0));
                            ///////////////////

                            v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_6)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * tmp_index_338)) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_16)] = p_diag_out_vn_ie_0;
                        }

                    }

                }
            }

        }
    }

    {


    }
    i_startblk_var_148 = v_v_p_patch_edges_start_block[(7 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];

    {


    }
    i_endblk_var_149 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 9)];
    _if_cond_15 = (1 - lvn_only);

    if ((_if_cond_15 == 1)) {
        for (_for_it_17 = i_startblk_var_148; (_for_it_17 <= i_endblk_var_149); _for_it_17 = (_for_it_17 + 1)) {
            {


            }
            i_startidx_in_var_93_2 = v_v_p_patch_var_84_edges_start_index[(7 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
            {


            }
            i_endidx_in_var_94_2 = v_v_p_patch_var_84_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 9)];
            if ((_for_it_17 != i_startblk_var_148)) {

                i_startidx_var_150 = 1;

            } else {

                i_startidx_var_150 = max(1, i_startidx_in_var_93_2);

            }
            if ((_for_it_17 != i_endblk_var_149)) {
                {


                }
                i_endidx_var_151 = global_data_var_83_nproma_10[0];

            } else {

                i_endidx_var_151 = i_endidx_in_var_94_2;

            }
            for (_for_it_18 = 1; (_for_it_18 <= nlev_var_154); _for_it_18 = (_for_it_18 + 1)) {
                for (_for_it_19 = i_startidx_var_150; (_for_it_19 <= i_endidx_var_151); _for_it_19 = (_for_it_19 + 1)) {
                    {


                    }
                    tmp_index_374 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_19)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    {


                    }
                    tmp_index_376 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_19)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    {


                    }
                    tmp_index_383 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_19)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                    {


                    }
                    tmp_index_385 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_19)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                    {


                    }
                    tmp_index_399 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_19)] - 1);
                    {


                    }
                    tmp_index_401 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_19)] - 1);
                    {


                    }
                    tmp_index_408 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_19)] - 1);
                    {


                    }
                    tmp_index_410 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_17))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_19)] - 1);
                    {
                        double* v_v_p_patch_edges_inv_dual_edge_length;
                        v_v_p_patch_edges_inv_dual_edge_length = (double*)(&((*v_p_patch_edges)->inv_dual_edge_length)[0]);

                        {
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_17)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_18))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_19)];
                            double p_patch_0_in_edges_inv_dual_edge_length_0 = v_v_p_patch_edges_inv_dual_edge_length[(((__f2dace_SA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4 * ((- __f2dace_SOA_inv_dual_edge_length_d_1_s_187_edges_p_patch_4) + _for_it_17)) - __f2dace_SOA_inv_dual_edge_length_d_0_s_186_edges_p_patch_4) + _for_it_19)];
                            double p_patch_1_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) + _for_it_17)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4) + _for_it_19)];
                            double p_patch_2_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4) + _for_it_17)) - __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4) + _for_it_19)];
                            double p_prog_0_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_376) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_18))) + tmp_index_374)];
                            double p_prog_1_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_385) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_18))) + tmp_index_383)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_17)) + (__f2dace_A_z_vt_ie_d_0_s_372 * ((- __f2dace_OA_z_vt_ie_d_1_s_373) + _for_it_18))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_19)];
                            double z_w_v_0_in_0 = z_w_v[((tmp_index_399 + ((tmp_index_401 * tmp_struct_symbol_10) * tmp_struct_symbol_11)) + (tmp_struct_symbol_10 * (_for_it_18 - 1)))];
                            double z_w_v_1_in_0 = z_w_v[((tmp_index_408 + ((tmp_index_410 * tmp_struct_symbol_10) * tmp_struct_symbol_11)) + (tmp_struct_symbol_10 * (_for_it_18 - 1)))];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l488_c488)
                            z_v_grad_w_out_0 = (((p_diag_0_in_vn_ie_0 * p_patch_0_in_edges_inv_dual_edge_length_0) * (p_prog_0_in_w_0 - p_prog_1_in_w_0)) + (((z_vt_ie_0_in_0 * p_patch_1_in_edges_inv_primal_edge_length_0) * p_patch_2_in_edges_tangent_orientation_0) * (z_w_v_0_in_0 - z_w_v_1_in_0)));
                            ///////////////////

                            z_v_grad_w[(((_for_it_19 + ((tmp_struct_symbol_7 * tmp_struct_symbol_8) * (_for_it_17 - 1))) + (tmp_struct_symbol_7 * (_for_it_18 - 1))) - 1)] = z_v_grad_w_out_0;
                        }

                    }

                }

            }

        }
    }
    _if_cond_16 = ((1 - lvn_only) && ldeepatmo);

    if ((_if_cond_16 == 1)) {
        for (_for_it_20 = i_startblk_var_148; (_for_it_20 <= i_endblk_var_149); _for_it_20 = (_for_it_20 + 1)) {
            {


            }
            i_startidx_in_var_93_1 = v_v_p_patch_var_84_edges_start_index[(7 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
            {


            }
            i_endidx_in_var_94_1 = v_v_p_patch_var_84_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 9)];
            if ((_for_it_20 != i_startblk_var_148)) {

                i_startidx_var_150 = 1;

            } else {

                i_startidx_var_150 = max(1, i_startidx_in_var_93_1);

            }
            if ((_for_it_20 != i_endblk_var_149)) {
                {


                }
                i_endidx_var_151 = global_data_var_83_nproma_11[0];

            } else {

                i_endidx_var_151 = i_endidx_in_var_94_1;

            }
            for (_for_it_21 = 1; (_for_it_21 <= nlev_var_154); _for_it_21 = (_for_it_21 + 1)) {
                for (_for_it_22 = i_startidx_var_150; (_for_it_22 <= i_endidx_var_151); _for_it_22 = (_for_it_22 + 1)) {
                    {
                        double* v_p_metrics_deepatmo_gradh_ifc;
                        v_p_metrics_deepatmo_gradh_ifc = (double*)(&(p_metrics->deepatmo_gradh_ifc)[0]);
                        double* v_p_metrics_deepatmo_invr_ifc;
                        v_p_metrics_deepatmo_invr_ifc = (double*)(&(p_metrics->deepatmo_invr_ifc)[0]);
                        double* v_v_p_patch_edges_fn_e;
                        v_v_p_patch_edges_fn_e = (double*)(&((*v_p_patch_edges)->fn_e)[0]);

                        {
                            double p_diag_0_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_20)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_21))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_22)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_20)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_21))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_22)];
                            double p_metrics_0_in_deepatmo_gradh_ifc_0 = v_p_metrics_deepatmo_gradh_ifc[((- __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_346_p_metrics_8) + _for_it_21)];
                            double p_metrics_1_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[((- __f2dace_SOA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8) + _for_it_21)];
                            double p_metrics_2_in_deepatmo_invr_ifc_0 = v_p_metrics_deepatmo_invr_ifc[((- __f2dace_SOA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8) + _for_it_21)];
                            double p_patch_0_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((__f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4 * ((- __f2dace_SOA_ft_e_d_1_s_195_edges_p_patch_4) + _for_it_20)) - __f2dace_SOA_ft_e_d_0_s_194_edges_p_patch_4) + _for_it_22)];
                            double p_patch_1_in_edges_fn_e_0 = v_v_p_patch_edges_fn_e[(((__f2dace_SA_fn_e_d_0_s_192_edges_p_patch_4 * ((- __f2dace_SOA_fn_e_d_1_s_193_edges_p_patch_4) + _for_it_20)) - __f2dace_SOA_fn_e_d_0_s_192_edges_p_patch_4) + _for_it_22)];
                            double z_v_grad_w_0_in_0 = z_v_grad_w[(((_for_it_22 + ((tmp_struct_symbol_7 * tmp_struct_symbol_8) * (_for_it_20 - 1))) + (tmp_struct_symbol_7 * (_for_it_21 - 1))) - 1)];
                            double z_vt_ie_0_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_20)) + (__f2dace_A_z_vt_ie_d_0_s_372 * ((- __f2dace_OA_z_vt_ie_d_1_s_373) + _for_it_21))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_22)];
                            double z_vt_ie_1_in_0 = z_vt_ie[(((((__f2dace_A_z_vt_ie_d_0_s_372 * __f2dace_A_z_vt_ie_d_1_s_373) * ((- __f2dace_OA_z_vt_ie_d_2_s_374) + _for_it_20)) + (__f2dace_A_z_vt_ie_d_0_s_372 * ((- __f2dace_OA_z_vt_ie_d_1_s_373) + _for_it_21))) - __f2dace_OA_z_vt_ie_d_0_s_372) + _for_it_22)];
                            double z_v_grad_w_out_0;

                            ///////////////////
                            // Tasklet code (T_l498_c498)
                            z_v_grad_w_out_0 = (((z_v_grad_w_0_in_0 * p_metrics_0_in_deepatmo_gradh_ifc_0) + (p_diag_0_in_vn_ie_0 * ((p_diag_1_in_vn_ie_0 * p_metrics_1_in_deepatmo_invr_ifc_0) - p_patch_0_in_edges_ft_e_0))) + (z_vt_ie_0_in_0 * ((z_vt_ie_1_in_0 * p_metrics_2_in_deepatmo_invr_ifc_0) + p_patch_1_in_edges_fn_e_0)));
                            ///////////////////

                            z_v_grad_w[(((_for_it_22 + ((tmp_struct_symbol_7 * tmp_struct_symbol_8) * (_for_it_20 - 1))) + (tmp_struct_symbol_7 * (_for_it_21 - 1))) - 1)] = z_v_grad_w_out_0;
                        }

                    }

                }

            }

        }
    }

    {


    }
    i_startblk_var_148 = v_v_p_patch_cells_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_var_149 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 5)];

    {


    }
    i_startblk_2 = v_v_p_patch_cells_start_block[(5 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_2 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];

    for (_for_it_23 = i_startblk_var_148; (_for_it_23 <= i_endblk_var_149); _for_it_23 = (_for_it_23 + 1)) {
        {


        }
        i_startidx_in_var_81_1 = v_v_p_patch_var_72_cells_start_index[(4 - __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2)];
        {


        }
        i_endidx_in_var_82_1 = v_v_p_patch_var_72_cells_end_index[((- __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2) - 5)];
        if (((_for_it_23 == i_startblk_var_148) == 1)) {

            i_startidx_var_150 = max(1, i_startidx_in_var_81_1);
            {


            }
            i_endidx_var_151 = global_data_var_71_nproma_12[0];
            if (((_for_it_23 == i_endblk_var_149) == 1)) {

                i_endidx_var_151 = i_endidx_in_var_82_1;

            }
        } else {
            if (((_for_it_23 == i_endblk_var_149) == 1)) {

                i_startidx_var_150 = 1;
                i_endidx_var_151 = i_endidx_in_var_82_1;

            } else {

                i_startidx_var_150 = 1;
                {


                }
                i_endidx_var_151 = global_data_var_71_nproma_12[0];

            }
        }
        for (_for_it_24 = 1; (_for_it_24 <= nlev_var_154); _for_it_24 = (_for_it_24 + 1)) {
            for (_for_it_25 = i_startidx_var_150; (_for_it_25 <= i_endidx_var_151); _for_it_25 = (_for_it_25 + 1)) {
                {


                }
                tmp_index_452 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_0_s_369);
                {


                }
                tmp_index_454 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_2_s_371);
                {


                }
                tmp_index_464 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_0_s_369);
                {


                }
                tmp_index_466 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_2_s_371);
                {


                }
                tmp_index_476 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_0_s_369);
                {


                }
                tmp_index_478 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_25)] - __f2dace_OA_z_kin_hor_e_d_2_s_371);
                {

                    {
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_25)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_25)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_25)];
                        double z_kin_hor_e_0_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * tmp_index_454) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_24))) + tmp_index_452)];
                        double z_kin_hor_e_1_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * tmp_index_466) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_24))) + tmp_index_464)];
                        double z_kin_hor_e_2_in_0 = z_kin_hor_e[((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * tmp_index_478) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_24))) + tmp_index_476)];
                        double z_ekinh_out_0;

                        ///////////////////
                        // Tasklet code (T_l515_c515)
                        z_ekinh_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_kin_hor_e_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_kin_hor_e_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_kin_hor_e_2_in_0));
                        ///////////////////

                        z_ekinh[(((_for_it_25 + ((tmp_struct_symbol_16 * tmp_struct_symbol_17) * (_for_it_23 - 1))) + (tmp_struct_symbol_16 * (_for_it_24 - 1))) - 1)] = z_ekinh_out_0;
                    }

                }

            }

        }
        _if_cond_17 = (istep == 1);
        if ((_if_cond_17 == 1)) {
            for (_for_it_26 = nflatlev_jg; (_for_it_26 <= nlev_var_154); _for_it_26 = (_for_it_26 + 1)) {
                for (_for_it_27 = i_startidx_var_150; (_for_it_27 <= i_endidx_var_151); _for_it_27 = (_for_it_27 + 1)) {
                    {


                    }
                    tmp_index_490 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_0_s_366);
                    {


                    }
                    tmp_index_492 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_2_s_368);
                    {


                    }
                    tmp_index_502 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_0_s_366);
                    {


                    }
                    tmp_index_504 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_2_s_368);
                    {


                    }
                    tmp_index_514 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_0_s_366);
                    {


                    }
                    tmp_index_516 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_27)] - __f2dace_OA_z_w_concorr_me_d_2_s_368);
                    {

                        {
                            double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_27)];
                            double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_27)];
                            double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_27)];
                            double z_w_concorr_me_0_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_366 * __f2dace_A_z_w_concorr_me_d_1_s_367) * tmp_index_492) + (__f2dace_A_z_w_concorr_me_d_0_s_366 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_367) + _for_it_26))) + tmp_index_490)];
                            double z_w_concorr_me_1_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_366 * __f2dace_A_z_w_concorr_me_d_1_s_367) * tmp_index_504) + (__f2dace_A_z_w_concorr_me_d_0_s_366 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_367) + _for_it_26))) + tmp_index_502)];
                            double z_w_concorr_me_2_in_0 = z_w_concorr_me[((((__f2dace_A_z_w_concorr_me_d_0_s_366 * __f2dace_A_z_w_concorr_me_d_1_s_367) * tmp_index_516) + (__f2dace_A_z_w_concorr_me_d_0_s_366 * ((- __f2dace_OA_z_w_concorr_me_d_1_s_367) + _for_it_26))) + tmp_index_514)];
                            double z_w_concorr_mc_out_0;

                            ///////////////////
                            // Tasklet code (T_l521_c521)
                            z_w_concorr_mc_out_0 = (((p_int_0_in_e_bln_c_s_0 * z_w_concorr_me_0_in_0) + (p_int_1_in_e_bln_c_s_0 * z_w_concorr_me_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_w_concorr_me_2_in_0));
                            ///////////////////

                            z_w_concorr_mc[((_for_it_27 + (tmp_struct_symbol_0 * (_for_it_26 - 1))) - 1)] = z_w_concorr_mc_out_0;
                        }

                    }

                }

            }
            for (_for_it_28 = (nflatlev_jg + 1); (_for_it_28 <= nlev_var_154); _for_it_28 = (_for_it_28 + 1)) {
                for (_for_it_29 = i_startidx_var_150; (_for_it_29 <= i_endidx_var_151); _for_it_29 = (_for_it_29 + 1)) {
                    {
                        double* v_p_metrics_wgtfac_c;
                        v_p_metrics_wgtfac_c = (double*)(&(p_metrics->wgtfac_c)[0]);

                        {
                            double p_metrics_0_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[(((((__f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfac_c_d_1_s_327_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_328_p_metrics_8) + _for_it_23)) + (__f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_327_p_metrics_8) + _for_it_28))) - __f2dace_SOA_wgtfac_c_d_0_s_326_p_metrics_8) + _for_it_29)];
                            double p_metrics_1_in_wgtfac_c_0 = v_p_metrics_wgtfac_c[(((((__f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8 * __f2dace_SA_wgtfac_c_d_1_s_327_p_metrics_8) * ((- __f2dace_SOA_wgtfac_c_d_2_s_328_p_metrics_8) + _for_it_23)) + (__f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8 * ((- __f2dace_SOA_wgtfac_c_d_1_s_327_p_metrics_8) + _for_it_28))) - __f2dace_SOA_wgtfac_c_d_0_s_326_p_metrics_8) + _for_it_29)];
                            double z_w_concorr_mc_0_in_0 = z_w_concorr_mc[((_for_it_29 + (tmp_struct_symbol_0 * (_for_it_28 - 1))) - 1)];
                            double z_w_concorr_mc_1_in_0 = z_w_concorr_mc[((_for_it_29 + (tmp_struct_symbol_0 * (_for_it_28 - 2))) - 1)];
                            double p_diag_out_w_concorr_c_0;

                            ///////////////////
                            // Tasklet code (T_l526_c526)
                            p_diag_out_w_concorr_c_0 = ((p_metrics_0_in_wgtfac_c_0 * z_w_concorr_mc_0_in_0) + ((1.0 - p_metrics_1_in_wgtfac_c_0) * z_w_concorr_mc_1_in_0));
                            ///////////////////

                            v_p_diag_w_concorr_c[(((((__f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9 * __f2dace_SA_w_concorr_c_d_1_s_304_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_305_p_diag_9) + _for_it_23)) + (__f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_304_p_diag_9) + _for_it_28))) - __f2dace_SOA_w_concorr_c_d_0_s_303_p_diag_9) + _for_it_29)] = p_diag_out_w_concorr_c_0;
                        }

                    }

                }

            }
        }
        for (_for_it_30 = 1; (_for_it_30 <= nlev_var_154); _for_it_30 = (_for_it_30 + 1)) {
            for (_for_it_31 = i_startidx_var_150; (_for_it_31 <= i_endidx_var_151); _for_it_31 = (_for_it_31 + 1)) {
                {

                    {
                        double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_290_p_prog_7) + _for_it_23)) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_30))) - __f2dace_SOA_w_d_0_s_288_p_prog_7) + _for_it_31)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l532_c532)
                        z_w_con_c_out_0 = p_prog_0_in_w_0;
                        ///////////////////

                        z_w_con_c[((_for_it_31 + (tmp_struct_symbol_2 * (_for_it_30 - 1))) - 1)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        for (_for_it_32 = i_startidx_var_150; (_for_it_32 <= i_endidx_var_151); _for_it_32 = (_for_it_32 + 1)) {

            tmp_index_536 = (nlevp1_var_155 - 1);
            {

                {
                    double z_w_con_c_out_0;

                    ///////////////////
                    // Tasklet code (T_l536_c536)
                    z_w_con_c_out_0 = 0.0;
                    ///////////////////

                    z_w_con_c[((_for_it_32 + (tmp_index_536 * tmp_struct_symbol_2)) - 1)] = z_w_con_c_out_0;
                }

            }

        }
        for (_for_it_33 = nlev_var_154; (_for_it_33 >= (nflatlev_jg + 1)); _for_it_33 = (_for_it_33 + -1)) {
            for (_for_it_34 = i_startidx_var_150; (_for_it_34 <= i_endidx_var_151); _for_it_34 = (_for_it_34 + 1)) {
                {

                    {
                        double p_diag_0_in_w_concorr_c_0 = v_p_diag_w_concorr_c[(((((__f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9 * __f2dace_SA_w_concorr_c_d_1_s_304_p_diag_9) * ((- __f2dace_SOA_w_concorr_c_d_2_s_305_p_diag_9) + _for_it_23)) + (__f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9 * ((- __f2dace_SOA_w_concorr_c_d_1_s_304_p_diag_9) + _for_it_33))) - __f2dace_SOA_w_concorr_c_d_0_s_303_p_diag_9) + _for_it_34)];
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_34 + (tmp_struct_symbol_2 * (_for_it_33 - 1))) - 1)];
                        double z_w_con_c_out_0;

                        ///////////////////
                        // Tasklet code (T_l540_c540)
                        z_w_con_c_out_0 = (z_w_con_c_0_in_0 - p_diag_0_in_w_concorr_c_0);
                        ///////////////////

                        z_w_con_c[((_for_it_34 + (tmp_struct_symbol_2 * (_for_it_33 - 1))) - 1)] = z_w_con_c_out_0;
                    }

                }

            }

        }
        tmp_arg_9 = (nrdmax_jg - 2);
        for (_for_it_35 = max(3, tmp_arg_9); (_for_it_35 <= (nlev_var_154 - 3)); _for_it_35 = (_for_it_35 + 1)) {
            {

                {
                    int levmask_out_0;

                    ///////////////////
                    // Tasklet code (T_l544_c544)
                    levmask_out_0 = 0;
                    ///////////////////

                    levmask[((_for_it_23 + (tmp_struct_symbol_20 * (_for_it_35 - 1))) - 1)] = levmask_out_0;
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
        for (_for_it_36 = max(3, tmp_arg_10); (_for_it_36 <= (nlev_var_154 - 3)); _for_it_36 = (_for_it_36 + 1)) {

            clip_count = 0;
            for (_for_it_37 = i_startidx_var_150; (_for_it_37 <= i_endidx_var_151); _for_it_37 = (_for_it_37 + 1)) {
                {
                    double tmp_call_9;

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_37 + (tmp_struct_symbol_2 * (_for_it_36 - 1))) - 1)];
                        double tmp_call_9_out;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        tmp_call_9_out = abs(z_w_con_c_0_in_0);
                        ///////////////////

                        tmp_call_9 = tmp_call_9_out;
                    }
                    {
                        double cfl_w_limit_0_in = cfl_w_limit;
                        double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8) + _for_it_37)];
                        double tmp_call_9_0_in = tmp_call_9;
                        int cfl_clipping_out_0;

                        ///////////////////
                        // Tasklet code (T_l550_c550)
                        cfl_clipping_out_0 = (tmp_call_9_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_half_0));
                        ///////////////////

                        cfl_clipping[((_for_it_37 + (tmp_struct_symbol_23 * (_for_it_36 - 1))) - 1)] = cfl_clipping_out_0;
                    }
                    {
                        int cfl_clipping_0_in_0 = cfl_clipping[((_for_it_37 + (tmp_struct_symbol_23 * (_for_it_36 - 1))) - 1)];
                        int _if_cond_18_out;

                        ///////////////////
                        // Tasklet code (T_l551_c551)
                        _if_cond_18_out = cfl_clipping_0_in_0;
                        ///////////////////

                        _if_cond_18 = _if_cond_18_out;
                    }

                }
                if ((_if_cond_18 == 1)) {

                    clip_count = (clip_count + 1);

                }

            }
            if (((clip_count == 0) == 1)) {
                continue;
            }
            for (_for_it_38 = i_startidx_var_150; (_for_it_38 <= i_endidx_var_151); _for_it_38 = (_for_it_38 + 1)) {

                _if_cond_20 = cfl_clipping[((_for_it_38 + (tmp_struct_symbol_23 * (_for_it_36 - 1))) - 1)];
                if ((_if_cond_20 == 1)) {
                    {
                        double tmp_call_10;

                        {
                            int levmask_out_0;

                            ///////////////////
                            // Tasklet code (T_l556_c556)
                            levmask_out_0 = 1;
                            ///////////////////

                            levmask[((_for_it_23 + (tmp_struct_symbol_20 * (_for_it_36 - 1))) - 1)] = levmask_out_0;
                        }
                        {
                            double dtime_0_in = dtime;
                            double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8) + _for_it_38)];
                            double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_38 + (tmp_struct_symbol_2 * (_for_it_36 - 1))) - 1)];
                            double vcfl_out;

                            ///////////////////
                            // Tasklet code (T_l557_c557)
                            vcfl_out = ((z_w_con_c_0_in_0 * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0);
                            ///////////////////

                            vcfl = vcfl_out;
                        }
                        {
                            double vcfl_0_in = vcfl;
                            double tmp_call_10_out;

                            ///////////////////
                            // Tasklet code (T_l558_c558)
                            tmp_call_10_out = abs(vcfl_0_in);
                            ///////////////////

                            tmp_call_10 = tmp_call_10_out;
                        }
                        {
                            double maxvcfl_0_in = maxvcfl;
                            double tmp_call_10_0_in = tmp_call_10;
                            double maxvcfl_out;

                            ///////////////////
                            // Tasklet code (T_l558_c558)
                            maxvcfl_out = max(maxvcfl_0_in, tmp_call_10_0_in);
                            ///////////////////

                            maxvcfl = maxvcfl_out;
                        }

                    }
                    _if_cond_21 = (vcfl < -0.85);
                    if ((_if_cond_21 == 1)) {
                        {

                            {
                                double dtime_0_in = dtime;
                                double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8) + _for_it_38)];
                                double z_w_con_c_out_0;

                                ///////////////////
                                // Tasklet code (T_l560_c560)
                                z_w_con_c_out_0 = (- ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in));
                                ///////////////////

                                z_w_con_c[((_for_it_38 + (tmp_struct_symbol_2 * (_for_it_36 - 1))) - 1)] = z_w_con_c_out_0;
                            }

                        }
                    } else {

                        _if_cond_22 = (vcfl > 0.85);
                        if ((_if_cond_22 == 1)) {
                            {

                                {
                                    double dtime_0_in = dtime;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8) + _for_it_36))) - __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8) + _for_it_38)];
                                    double z_w_con_c_out_0;

                                    ///////////////////
                                    // Tasklet code (T_l562_c562)
                                    z_w_con_c_out_0 = ((0.85 * p_metrics_0_in_ddqz_z_half_0) / dtime_0_in);
                                    ///////////////////

                                    z_w_con_c[((_for_it_38 + (tmp_struct_symbol_2 * (_for_it_36 - 1))) - 1)] = z_w_con_c_out_0;
                                }

                            }
                        }
                    }
                }

            }

        }
        for (_for_it_39 = 1; (_for_it_39 <= nlev_var_154); _for_it_39 = (_for_it_39 + 1)) {
            for (_for_it_40 = i_startidx_var_150; (_for_it_40 <= i_endidx_var_151); _for_it_40 = (_for_it_40 + 1)) {
                {

                    {
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_40 + (tmp_struct_symbol_2 * (_for_it_39 - 1))) - 1)];
                        double z_w_con_c_1_in_0 = z_w_con_c[(((_for_it_39 * tmp_struct_symbol_2) + _for_it_40) - 1)];
                        double z_w_con_c_full_out_0;

                        ///////////////////
                        // Tasklet code (T_l569_c569)
                        z_w_con_c_full_out_0 = (0.5 * (z_w_con_c_0_in_0 + z_w_con_c_1_in_0));
                        ///////////////////

                        z_w_con_c_full[(((_for_it_40 + ((tmp_struct_symbol_4 * tmp_struct_symbol_5) * (_for_it_23 - 1))) + (tmp_struct_symbol_4 * (_for_it_39 - 1))) - 1)] = z_w_con_c_full_out_0;
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

                vcflmax[(_for_it_23 - 1)] = vcflmax_out_0;
            }

        }
        _if_cond_23 = lvn_only;
        if ((_if_cond_23 == 1)) {
            continue;
        }
        if ((((_for_it_23 < i_startblk_2) || (_for_it_23 > i_endblk_2)) == 1)) {
            continue;
        }
        {


        }
        i_startidx_in_var_81_0 = v_v_p_patch_var_72_cells_start_index[(5 - __f2dace_SOA_start_index_d_0_s_160_cells_p_patch_2)];
        {


        }
        i_endidx_in_var_82_0 = v_v_p_patch_var_72_cells_end_index[((- __f2dace_SOA_end_index_d_0_s_161_cells_p_patch_2) - 4)];
        if (((_for_it_23 == i_startblk_2) == 1)) {

            i_startidx_2 = max(1, i_startidx_in_var_81_0);
            {


            }
            i_endidx_2 = global_data_var_71_nproma_13[0];
            if (((_for_it_23 == i_endblk_2) == 1)) {

                i_endidx_2 = i_endidx_in_var_82_0;

            }
        } else {
            if (((_for_it_23 == i_endblk_2) == 1)) {

                i_startidx_2 = 1;
                i_endidx_2 = i_endidx_in_var_82_0;

            } else {

                i_startidx_2 = 1;
                {


                }
                i_endidx_2 = global_data_var_71_nproma_13[0];

            }
        }
        for (_for_it_41 = 2; (_for_it_41 <= nlev_var_154); _for_it_41 = (_for_it_41 + 1)) {
            for (_for_it_42 = i_startidx_2; (_for_it_42 <= i_endidx_2); _for_it_42 = (_for_it_42 + 1)) {

                tmp_index_585 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9);
                {
                    double* v_p_metrics_coeff1_dwdz;
                    v_p_metrics_coeff1_dwdz = (double*)(&(p_metrics->coeff1_dwdz)[0]);
                    double* v_p_metrics_coeff2_dwdz;
                    v_p_metrics_coeff2_dwdz = (double*)(&(p_metrics->coeff2_dwdz)[0]);

                    {
                        double p_metrics_0_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[(((((__f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8 * __f2dace_SA_coeff1_dwdz_d_1_s_339_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_340_p_metrics_8) + _for_it_23)) + (__f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_339_p_metrics_8) + _for_it_41))) - __f2dace_SOA_coeff1_dwdz_d_0_s_338_p_metrics_8) + _for_it_42)];
                        double p_metrics_1_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[(((((__f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8 * __f2dace_SA_coeff2_dwdz_d_1_s_342_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_343_p_metrics_8) + _for_it_23)) + (__f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_342_p_metrics_8) + _for_it_41))) - __f2dace_SOA_coeff2_dwdz_d_0_s_341_p_metrics_8) + _for_it_42)];
                        double p_metrics_2_in_coeff2_dwdz_0 = v_p_metrics_coeff2_dwdz[(((((__f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8 * __f2dace_SA_coeff2_dwdz_d_1_s_342_p_metrics_8) * ((- __f2dace_SOA_coeff2_dwdz_d_2_s_343_p_metrics_8) + _for_it_23)) + (__f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8 * ((- __f2dace_SOA_coeff2_dwdz_d_1_s_342_p_metrics_8) + _for_it_41))) - __f2dace_SOA_coeff2_dwdz_d_0_s_341_p_metrics_8) + _for_it_42)];
                        double p_metrics_3_in_coeff1_dwdz_0 = v_p_metrics_coeff1_dwdz[(((((__f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8 * __f2dace_SA_coeff1_dwdz_d_1_s_339_p_metrics_8) * ((- __f2dace_SOA_coeff1_dwdz_d_2_s_340_p_metrics_8) + _for_it_23)) + (__f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8 * ((- __f2dace_SOA_coeff1_dwdz_d_1_s_339_p_metrics_8) + _for_it_41))) - __f2dace_SOA_coeff1_dwdz_d_0_s_338_p_metrics_8) + _for_it_42)];
                        double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_290_p_prog_7) + _for_it_23)) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_41) - 1))) - __f2dace_SOA_w_d_0_s_288_p_prog_7) + _for_it_42)];
                        double p_prog_1_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_290_p_prog_7) + _for_it_23)) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * (((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_41) + 1))) - __f2dace_SOA_w_d_0_s_288_p_prog_7) + _for_it_42)];
                        double p_prog_2_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_290_p_prog_7) + _for_it_23)) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_41))) - __f2dace_SOA_w_d_0_s_288_p_prog_7) + _for_it_42)];
                        double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_42 + (tmp_struct_symbol_2 * (_for_it_41 - 1))) - 1)];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l578_c578)
                        p_diag_out_ddt_w_adv_pc_0 = (- (z_w_con_c_0_in_0 * (((p_prog_0_in_w_0 * p_metrics_0_in_coeff1_dwdz_0) - (p_prog_1_in_w_0 * p_metrics_1_in_coeff2_dwdz_0)) + (p_prog_2_in_w_0 * (p_metrics_2_in_coeff2_dwdz_0 - p_metrics_3_in_coeff1_dwdz_0)))));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9) * tmp_index_585) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9) + _for_it_41))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9) + _for_it_42)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        for (_for_it_43 = 2; (_for_it_43 <= nlev_var_154); _for_it_43 = (_for_it_43 + 1)) {
            for (_for_it_44 = i_startidx_2; (_for_it_44 <= i_endidx_2); _for_it_44 = (_for_it_44 + 1)) {

                tmp_index_612 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9);
                tmp_index_616 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9);
                {


                }
                tmp_index_626 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (1 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_44)] - 1);
                {


                }
                tmp_index_628 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (1 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_44)] - 1);
                {


                }
                tmp_index_638 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (2 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_44)] - 1);
                {


                }
                tmp_index_640 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (2 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_44)] - 1);
                {


                }
                tmp_index_650 = (v_v_p_patch_cells_edge_idx[(((((__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * __f2dace_SA_edge_idx_d_1_s_153_cells_p_patch_2) * (3 - __f2dace_SOA_edge_idx_d_2_s_154_cells_p_patch_2)) + (__f2dace_SA_edge_idx_d_0_s_152_cells_p_patch_2 * ((- __f2dace_SOA_edge_idx_d_1_s_153_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_idx_d_0_s_152_cells_p_patch_2) + _for_it_44)] - 1);
                {


                }
                tmp_index_652 = (v_v_p_patch_cells_edge_blk[(((((__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * __f2dace_SA_edge_blk_d_1_s_156_cells_p_patch_2) * (3 - __f2dace_SOA_edge_blk_d_2_s_157_cells_p_patch_2)) + (__f2dace_SA_edge_blk_d_0_s_155_cells_p_patch_2 * ((- __f2dace_SOA_edge_blk_d_1_s_156_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_edge_blk_d_0_s_155_cells_p_patch_2) + _for_it_44)] - 1);
                {

                    {
                        double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9) * tmp_index_616) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9) + _for_it_43))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9) + _for_it_44)];
                        double p_int_0_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (1 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_44)];
                        double p_int_1_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (2 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_44)];
                        double p_int_2_in_e_bln_c_s_0 = v_p_int_e_bln_c_s[(((((__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * __f2dace_SA_e_bln_c_s_d_1_s_29_p_int_6) * ((- __f2dace_SOA_e_bln_c_s_d_2_s_30_p_int_6) + _for_it_23)) + (__f2dace_SA_e_bln_c_s_d_0_s_28_p_int_6 * (3 - __f2dace_SOA_e_bln_c_s_d_1_s_29_p_int_6))) - __f2dace_SOA_e_bln_c_s_d_0_s_28_p_int_6) + _for_it_44)];
                        double z_v_grad_w_0_in_0 = z_v_grad_w[((tmp_index_626 + ((tmp_index_628 * tmp_struct_symbol_7) * tmp_struct_symbol_8)) + (tmp_struct_symbol_7 * (_for_it_43 - 1)))];
                        double z_v_grad_w_1_in_0 = z_v_grad_w[((tmp_index_638 + ((tmp_index_640 * tmp_struct_symbol_7) * tmp_struct_symbol_8)) + (tmp_struct_symbol_7 * (_for_it_43 - 1)))];
                        double z_v_grad_w_2_in_0 = z_v_grad_w[((tmp_index_650 + ((tmp_index_652 * tmp_struct_symbol_7) * tmp_struct_symbol_8)) + (tmp_struct_symbol_7 * (_for_it_43 - 1)))];
                        double p_diag_out_ddt_w_adv_pc_0;

                        ///////////////////
                        // Tasklet code (T_l583_c583)
                        p_diag_out_ddt_w_adv_pc_0 = (((p_diag_0_in_ddt_w_adv_pc_0 + (p_int_0_in_e_bln_c_s_0 * z_v_grad_w_0_in_0)) + (p_int_1_in_e_bln_c_s_0 * z_v_grad_w_1_in_0)) + (p_int_2_in_e_bln_c_s_0 * z_v_grad_w_2_in_0));
                        ///////////////////

                        v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9) * tmp_index_612) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9) + _for_it_43))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9) + _for_it_44)] = p_diag_out_ddt_w_adv_pc_0;
                    }

                }

            }

        }
        {

            {
                int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
                int _if_cond_25_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_25_out = global_data_0_in_lextra_diffu;
                ///////////////////

                _if_cond_25 = _if_cond_25_out;
            }

        }
        if ((_if_cond_25 == 1)) {

            tmp_arg_12 = (nrdmax_jg - 2);
            for (_for_it_45 = max(3, tmp_arg_12); (_for_it_45 <= (nlev_var_154 - 3)); _for_it_45 = (_for_it_45 + 1)) {

                _if_cond_26 = levmask[((_for_it_23 + (tmp_struct_symbol_20 * (_for_it_45 - 1))) - 1)];
                if ((_if_cond_26 == 1)) {
                    for (_for_it_46 = i_startidx_2; (_for_it_46 <= i_endidx_2); _for_it_46 = (_for_it_46 + 1)) {
                        {


                        }
                        _if_cond_27 = (cfl_clipping[((_for_it_46 + (tmp_struct_symbol_23 * (_for_it_45 - 1))) - 1)] && v_v_v_p_patch_cells_decomp_info_owner_mask[(((__f2dace_SA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3 * ((- __f2dace_SOA_owner_mask_d_1_s_3_decomp_info_cells_p_patch_3) + _for_it_23)) - __f2dace_SOA_owner_mask_d_0_s_2_decomp_info_cells_p_patch_3) + _for_it_46)]);
                        if ((_if_cond_27 == 1)) {

                            tmp_index_667 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9);
                            tmp_index_671 = (ntnd - __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9);
                            {

                                {
                                    double z_w_con_c_0_in_0 = z_w_con_c[((_for_it_46 + (tmp_struct_symbol_2 * (_for_it_45 - 1))) - 1)];
                                    double tmp_call_13_out;

                                    ///////////////////
                                    // Tasklet code (T_l591_c591)
                                    tmp_call_13_out = abs(z_w_con_c_0_in_0);
                                    ///////////////////

                                    tmp_call_13 = tmp_call_13_out;
                                }

                            }
                            tmp_index_686 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (1 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                            {
                                double tmp_call_12;
                                double tmp_arg_13;
                                double tmp_arg_14;

                                {
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double dtime_0_in = dtime;
                                    double dtime_1_in = dtime;
                                    double p_metrics_0_in_ddqz_z_half_0 = v_p_metrics_ddqz_z_half[(((((__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8) + _for_it_23)) + (__f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8) + _for_it_45))) - __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8) + _for_it_46)];
                                    double tmp_call_13_0_in = tmp_call_13;
                                    double tmp_arg_14_out;

                                    ///////////////////
                                    // Tasklet code (T_l591_c591)
                                    tmp_arg_14_out = (((tmp_call_13_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_half_0) - (cfl_w_limit_0_in * dtime_1_in));
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
                                    double tmp_call_12_out;

                                    ///////////////////
                                    // Tasklet code (T_l591_c591)
                                    tmp_call_12_out = min(tmp_arg_13_0_in, tmp_arg_14_0_in);
                                    ///////////////////

                                    tmp_call_12 = tmp_call_12_out;
                                }
                                {
                                    double scalfac_exdiff_0_in = scalfac_exdiff;
                                    double tmp_call_12_0_in = tmp_call_12;
                                    double difcoef_out;

                                    ///////////////////
                                    // Tasklet code (T_l591_c591)
                                    difcoef_out = (scalfac_exdiff_0_in * tmp_call_12_0_in);
                                    ///////////////////

                                    difcoef = difcoef_out;
                                }

                            }
                            tmp_index_688 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (1 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                            {


                            }
                            tmp_index_698 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (2 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                            {


                            }
                            tmp_index_700 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (2 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                            {


                            }
                            tmp_index_710 = (v_v_p_patch_cells_neighbor_idx[(((((__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * __f2dace_SA_neighbor_idx_d_1_s_147_cells_p_patch_2) * (3 - __f2dace_SOA_neighbor_idx_d_2_s_148_cells_p_patch_2)) + (__f2dace_SA_neighbor_idx_d_0_s_146_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_idx_d_1_s_147_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_idx_d_0_s_146_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_0_s_288_p_prog_7);
                            {


                            }
                            tmp_index_712 = (v_v_p_patch_cells_neighbor_blk[(((((__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * __f2dace_SA_neighbor_blk_d_1_s_150_cells_p_patch_2) * (3 - __f2dace_SOA_neighbor_blk_d_2_s_151_cells_p_patch_2)) + (__f2dace_SA_neighbor_blk_d_0_s_149_cells_p_patch_2 * ((- __f2dace_SOA_neighbor_blk_d_1_s_150_cells_p_patch_2) + _for_it_23))) - __f2dace_SOA_neighbor_blk_d_0_s_149_cells_p_patch_2) + _for_it_46)] - __f2dace_SOA_w_d_2_s_290_p_prog_7);
                            {
                                double* v_p_int_geofac_n2s;
                                v_p_int_geofac_n2s = (double*)(&(p_int->geofac_n2s)[0]);
                                double* v_v_p_patch_cells_area;
                                v_v_p_patch_cells_area = (double*)(&((*v_p_patch_cells)->area)[0]);

                                {
                                    double difcoef_0_in = difcoef;
                                    double p_diag_0_in_ddt_w_adv_pc_0 = v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9) * tmp_index_671) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9) + _for_it_45))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9) + _for_it_46)];
                                    double p_int_0_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_23)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (1 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_46)];
                                    double p_int_1_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_23)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (2 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_46)];
                                    double p_int_2_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_23)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (3 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_46)];
                                    double p_int_3_in_geofac_n2s_0 = v_p_int_geofac_n2s[(((((__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * __f2dace_SA_geofac_n2s_d_1_s_44_p_int_6) * ((- __f2dace_SOA_geofac_n2s_d_2_s_45_p_int_6) + _for_it_23)) + (__f2dace_SA_geofac_n2s_d_0_s_43_p_int_6 * (4 - __f2dace_SOA_geofac_n2s_d_1_s_44_p_int_6))) - __f2dace_SOA_geofac_n2s_d_0_s_43_p_int_6) + _for_it_46)];
                                    double p_patch_0_in_cells_area_0 = v_v_p_patch_cells_area[(((__f2dace_SA_area_d_0_s_158_cells_p_patch_2 * ((- __f2dace_SOA_area_d_1_s_159_cells_p_patch_2) + _for_it_23)) - __f2dace_SOA_area_d_0_s_158_cells_p_patch_2) + _for_it_46)];
                                    double p_prog_0_in_w_0 = v_p_prog_w[(((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * ((- __f2dace_SOA_w_d_2_s_290_p_prog_7) + _for_it_23)) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_45))) - __f2dace_SOA_w_d_0_s_288_p_prog_7) + _for_it_46)];
                                    double p_prog_1_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_688) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_45))) + tmp_index_686)];
                                    double p_prog_2_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_700) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_45))) + tmp_index_698)];
                                    double p_prog_3_in_w_0 = v_p_prog_w[((((__f2dace_SA_w_d_0_s_288_p_prog_7 * __f2dace_SA_w_d_1_s_289_p_prog_7) * tmp_index_712) + (__f2dace_SA_w_d_0_s_288_p_prog_7 * ((- __f2dace_SOA_w_d_1_s_289_p_prog_7) + _for_it_45))) + tmp_index_710)];
                                    double p_diag_out_ddt_w_adv_pc_0;

                                    ///////////////////
                                    // Tasklet code (T_l592_c592)
                                    p_diag_out_ddt_w_adv_pc_0 = (p_diag_0_in_ddt_w_adv_pc_0 + ((difcoef_0_in * p_patch_0_in_cells_area_0) * ((((p_prog_0_in_w_0 * p_int_0_in_geofac_n2s_0) + (p_prog_1_in_w_0 * p_int_1_in_geofac_n2s_0)) + (p_prog_2_in_w_0 * p_int_2_in_geofac_n2s_0)) + (p_prog_3_in_w_0 * p_int_3_in_geofac_n2s_0))));
                                    ///////////////////

                                    v_p_diag_ddt_w_adv_pc[(((((((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9) * tmp_index_667) + ((__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9) * ((- __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9) + _for_it_23))) + (__f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 * ((- __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9) + _for_it_45))) - __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9) + _for_it_46)] = p_diag_out_ddt_w_adv_pc_0;
                                }

                            }
                        }

                    }
                }

            }
        }

    }
    tmp_arg_15 = (nrdmax_jg - 2);

    for (_for_it_47 = max(3, tmp_arg_15); (_for_it_47 <= (nlev_var_154 - 3)); _for_it_47 = (_for_it_47 + 1)) {

        tmp_call_15 = 0;
        for (tmp_parfor_0 = i_startblk_var_148; (tmp_parfor_0 <= i_endblk_var_149); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
            if ((levmask[((tmp_parfor_0 + (tmp_struct_symbol_20 * (_for_it_47 - 1))) - 1)] == 1)) {

                tmp_call_15 = 1;

            }

        }
        {

            {
                int levelmask_out_0;

                ///////////////////
                // Tasklet code (T_l600_c600)
                levelmask_out_0 = tmp_call_15;
                ///////////////////

                levelmask[(_for_it_47 - 1)] = levelmask_out_0;
            }

        }

    }

    {


    }
    i_startblk_var_148 = v_v_p_patch_edges_start_block[(10 - __f2dace_SOA_start_block_d_0_s_198_edges_p_patch_4)];

    {


    }
    i_endblk_var_149 = v_v_p_patch_edges_end_block[((- __f2dace_SOA_end_block_d_0_s_199_edges_p_patch_4) - 8)];

    for (_for_it_48 = i_startblk_var_148; (_for_it_48 <= i_endblk_var_149); _for_it_48 = (_for_it_48 + 1)) {
        {


        }
        i_startidx_in_var_93_0 = v_v_p_patch_var_84_edges_start_index[(10 - __f2dace_SOA_start_index_d_0_s_196_edges_p_patch_4)];
        {


        }
        i_endidx_in_var_94_0 = v_v_p_patch_var_84_edges_end_index[((- __f2dace_SOA_end_index_d_0_s_197_edges_p_patch_4) - 8)];
        if ((_for_it_48 != i_startblk_var_148)) {

            i_startidx_var_150 = 1;

        } else {

            i_startidx_var_150 = max(1, i_startidx_in_var_93_0);

        }
        if ((_for_it_48 != i_endblk_var_149)) {
            {


            }
            i_endidx_var_151 = global_data_var_83_nproma_14[0];

        } else {

            i_endidx_var_151 = i_endidx_in_var_94_0;

        }
        _if_cond_28 = (1 - ldeepatmo);
        if ((_if_cond_28 == 1)) {
            for (_for_it_49 = 1; (_for_it_49 <= nlev_var_154); _for_it_49 = (_for_it_49 + 1)) {
                for (_for_it_50 = i_startidx_var_150; (_for_it_50 <= i_endidx_var_151); _for_it_50 = (_for_it_50 + 1)) {

                    tmp_index_724 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9);
                    {


                    }
                    tmp_index_743 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_745 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_755 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_757 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_769 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_771 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_778 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_780 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_790 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_792 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_802 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_50)] - 1);
                    {


                    }
                    tmp_index_804 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_50)] - 1);
                    {

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_48)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_49))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_50)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_49))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_50)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_49) + 1))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_50)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_50)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_50)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_50)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_50)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_50)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_50)];
                            double p_metrics_4_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8) + _for_it_49))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8) + _for_it_50)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4) + _for_it_50)];
                            double z_ekinh_0_in_0 = z_ekinh[((tmp_index_743 + ((tmp_index_745 * tmp_struct_symbol_16) * tmp_struct_symbol_17)) + (tmp_struct_symbol_16 * (_for_it_49 - 1)))];
                            double z_ekinh_1_in_0 = z_ekinh[((tmp_index_755 + ((tmp_index_757 * tmp_struct_symbol_16) * tmp_struct_symbol_17)) + (tmp_struct_symbol_16 * (_for_it_49 - 1)))];
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_371) + _for_it_48)) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_49))) - __f2dace_OA_z_kin_hor_e_d_0_s_369) + _for_it_50)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_790 + ((tmp_index_792 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_49 - 1)))];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_802 + ((tmp_index_804 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_49 - 1)))];
                            double zeta_0_in_0 = zeta[((tmp_index_769 + ((tmp_index_771 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_49 - 1)))];
                            double zeta_1_in_0 = zeta[((tmp_index_778 + ((tmp_index_780 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_49 - 1)))];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l611_c611)
                            p_diag_out_ddt_vn_apc_pc_0 = (- (((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + (0.5 * (zeta_0_in_0 + zeta_1_in_0))))) + ((((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * (p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0)) / p_metrics_4_in_ddqz_z_full_e_0)));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) * tmp_index_724) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) + _for_it_49))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9) + _for_it_50)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        } else {
            for (_for_it_51 = 1; (_for_it_51 <= nlev_var_154); _for_it_51 = (_for_it_51 + 1)) {
                for (_for_it_52 = i_startidx_var_150; (_for_it_52 <= i_endidx_var_151); _for_it_52 = (_for_it_52 + 1)) {

                    tmp_index_817 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9);
                    {


                    }
                    tmp_index_836 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_838 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_848 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_850 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_863 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_865 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_872 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_874 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_885 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_887 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_897 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_52)] - 1);
                    {


                    }
                    tmp_index_899 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_52)] - 1);
                    {
                        double* v_p_metrics_deepatmo_gradh_mc;
                        v_p_metrics_deepatmo_gradh_mc = (double*)(&(p_metrics->deepatmo_gradh_mc)[0]);
                        double* v_p_metrics_deepatmo_invr_mc;
                        v_p_metrics_deepatmo_invr_mc = (double*)(&(p_metrics->deepatmo_invr_mc)[0]);

                        {
                            double p_diag_0_in_vt_0 = v_p_diag_vt[(((((__f2dace_SA_vt_d_0_s_297_p_diag_9 * __f2dace_SA_vt_d_1_s_298_p_diag_9) * ((- __f2dace_SOA_vt_d_2_s_299_p_diag_9) + _for_it_48)) + (__f2dace_SA_vt_d_0_s_297_p_diag_9 * ((- __f2dace_SOA_vt_d_1_s_298_p_diag_9) + _for_it_51))) - __f2dace_SOA_vt_d_0_s_297_p_diag_9) + _for_it_52)];
                            double p_diag_1_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * ((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_51))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_52)];
                            double p_diag_2_in_vn_ie_0 = v_p_diag_vn_ie[(((((__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * __f2dace_SA_vn_ie_d_1_s_301_p_diag_9) * ((- __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9) + _for_it_48)) + (__f2dace_SA_vn_ie_d_0_s_300_p_diag_9 * (((- __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9) + _for_it_51) + 1))) - __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9) + _for_it_52)];
                            double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_52)];
                            double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_52)];
                            double p_metrics_0_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_52)];
                            double p_metrics_1_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_52)];
                            double p_metrics_2_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (2 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_52)];
                            double p_metrics_3_in_coeff_gradekin_0 = v_p_metrics_coeff_gradekin[(((((__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8) * ((- __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8) + _for_it_48)) + (__f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 * (1 - __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8))) - __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8) + _for_it_52)];
                            double p_metrics_4_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[((- __f2dace_SOA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8) + _for_it_51)];
                            double p_metrics_5_in_deepatmo_gradh_mc_0 = v_p_metrics_deepatmo_gradh_mc[((- __f2dace_SOA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8) + _for_it_51)];
                            double p_metrics_6_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8) + _for_it_51))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8) + _for_it_52)];
                            double p_metrics_7_in_deepatmo_invr_mc_0 = v_p_metrics_deepatmo_invr_mc[((- __f2dace_SOA_deepatmo_invr_mc_d_0_s_345_p_metrics_8) + _for_it_51)];
                            double p_patch_0_in_edges_f_e_0 = v_v_p_patch_edges_f_e[(((__f2dace_SA_f_e_d_0_s_190_edges_p_patch_4 * ((- __f2dace_SOA_f_e_d_1_s_191_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_f_e_d_0_s_190_edges_p_patch_4) + _for_it_52)];
                            double p_patch_1_in_edges_ft_e_0 = v_v_p_patch_edges_ft_e[(((__f2dace_SA_ft_e_d_0_s_194_edges_p_patch_4 * ((- __f2dace_SOA_ft_e_d_1_s_195_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_ft_e_d_0_s_194_edges_p_patch_4) + _for_it_52)];
                            double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_48)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_51))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_52)];
                            double z_ekinh_0_in_0 = z_ekinh[((tmp_index_836 + ((tmp_index_838 * tmp_struct_symbol_16) * tmp_struct_symbol_17)) + (tmp_struct_symbol_16 * (_for_it_51 - 1)))];
                            double z_ekinh_1_in_0 = z_ekinh[((tmp_index_848 + ((tmp_index_850 * tmp_struct_symbol_16) * tmp_struct_symbol_17)) + (tmp_struct_symbol_16 * (_for_it_51 - 1)))];
                            double z_kin_hor_e_0_in_0 = z_kin_hor_e[(((((__f2dace_A_z_kin_hor_e_d_0_s_369 * __f2dace_A_z_kin_hor_e_d_1_s_370) * ((- __f2dace_OA_z_kin_hor_e_d_2_s_371) + _for_it_48)) + (__f2dace_A_z_kin_hor_e_d_0_s_369 * ((- __f2dace_OA_z_kin_hor_e_d_1_s_370) + _for_it_51))) - __f2dace_OA_z_kin_hor_e_d_0_s_369) + _for_it_52)];
                            double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_885 + ((tmp_index_887 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_51 - 1)))];
                            double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_897 + ((tmp_index_899 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_51 - 1)))];
                            double zeta_0_in_0 = zeta[((tmp_index_863 + ((tmp_index_865 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_51 - 1)))];
                            double zeta_1_in_0 = zeta[((tmp_index_872 + ((tmp_index_874 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_51 - 1)))];
                            double p_diag_out_ddt_vn_apc_pc_0;

                            ///////////////////
                            // Tasklet code (T_l624_c624)
                            p_diag_out_ddt_vn_apc_pc_0 = (- ((((((z_kin_hor_e_0_in_0 * (p_metrics_0_in_coeff_gradekin_0 - p_metrics_1_in_coeff_gradekin_0)) + (p_metrics_2_in_coeff_gradekin_0 * z_ekinh_0_in_0)) - (p_metrics_3_in_coeff_gradekin_0 * z_ekinh_1_in_0)) * p_metrics_4_in_deepatmo_gradh_mc_0) + (p_diag_0_in_vt_0 * (p_patch_0_in_edges_f_e_0 + ((0.5 * (zeta_0_in_0 + zeta_1_in_0)) * p_metrics_5_in_deepatmo_gradh_mc_0)))) + (((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0)) * ((((p_diag_1_in_vn_ie_0 - p_diag_2_in_vn_ie_0) / p_metrics_6_in_ddqz_z_full_e_0) + (p_prog_0_in_vn_0 * p_metrics_7_in_deepatmo_invr_mc_0)) - p_patch_1_in_edges_ft_e_0))));
                            ///////////////////

                            v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) * tmp_index_817) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) + _for_it_51))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9) + _for_it_52)] = p_diag_out_ddt_vn_apc_pc_0;
                        }

                    }

                }

            }
        }
        {

            {
                int global_data_0_in_lextra_diffu = v_global_data_lextra_diffu[0];
                int _if_cond_29_out;

                ///////////////////
                // Tasklet code (T_l0_c0)
                _if_cond_29_out = global_data_0_in_lextra_diffu;
                ///////////////////

                _if_cond_29 = _if_cond_29_out;
            }

        }
        if ((_if_cond_29 == 1)) {

            tmp_arg_17 = (nrdmax_jg - 2);
            for (_for_it_53 = max(3, tmp_arg_17); (_for_it_53 <= (nlev_var_154 - 4)); _for_it_53 = (_for_it_53 + 1)) {

                _if_cond_30 = (levelmask[(_for_it_53 - 1)] || levelmask[_for_it_53]);
                if ((_if_cond_30 == 1)) {
                    for (_for_it_54 = i_startidx_var_150; (_for_it_54 <= i_endidx_var_151); _for_it_54 = (_for_it_54 + 1)) {
                        {


                        }
                        tmp_index_926 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (1 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_54)] - 1);
                        {


                        }
                        tmp_index_928 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (1 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_54)] - 1);
                        {


                        }
                        tmp_index_938 = (v_v_p_patch_edges_cell_idx[(((((__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * __f2dace_SA_cell_idx_d_1_s_165_edges_p_patch_4) * (2 - __f2dace_SOA_cell_idx_d_2_s_166_edges_p_patch_4)) + (__f2dace_SA_cell_idx_d_0_s_164_edges_p_patch_4 * ((- __f2dace_SOA_cell_idx_d_1_s_165_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_idx_d_0_s_164_edges_p_patch_4) + _for_it_54)] - 1);
                        {


                        }
                        tmp_index_940 = (v_v_p_patch_edges_cell_blk[(((((__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * __f2dace_SA_cell_blk_d_1_s_168_edges_p_patch_4) * (2 - __f2dace_SOA_cell_blk_d_2_s_169_edges_p_patch_4)) + (__f2dace_SA_cell_blk_d_0_s_167_edges_p_patch_4 * ((- __f2dace_SOA_cell_blk_d_1_s_168_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_cell_blk_d_0_s_167_edges_p_patch_4) + _for_it_54)] - 1);
                        {
                            double tmp_call_17;

                            {
                                double p_int_0_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (1 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_54)];
                                double p_int_1_in_c_lin_e_0 = v_p_int_c_lin_e[(((((__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * __f2dace_SA_c_lin_e_d_1_s_26_p_int_6) * ((- __f2dace_SOA_c_lin_e_d_2_s_27_p_int_6) + _for_it_48)) + (__f2dace_SA_c_lin_e_d_0_s_25_p_int_6 * (2 - __f2dace_SOA_c_lin_e_d_1_s_26_p_int_6))) - __f2dace_SOA_c_lin_e_d_0_s_25_p_int_6) + _for_it_54)];
                                double z_w_con_c_full_0_in_0 = z_w_con_c_full[((tmp_index_926 + ((tmp_index_928 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_53 - 1)))];
                                double z_w_con_c_full_1_in_0 = z_w_con_c_full[((tmp_index_938 + ((tmp_index_940 * tmp_struct_symbol_4) * tmp_struct_symbol_5)) + (tmp_struct_symbol_4 * (_for_it_53 - 1)))];
                                double w_con_e_out;

                                ///////////////////
                                // Tasklet code (T_l640_c640)
                                w_con_e_out = ((p_int_0_in_c_lin_e_0 * z_w_con_c_full_0_in_0) + (p_int_1_in_c_lin_e_0 * z_w_con_c_full_1_in_0));
                                ///////////////////

                                w_con_e = w_con_e_out;
                            }
                            {
                                double w_con_e_0_in = w_con_e;
                                double tmp_call_17_out;

                                ///////////////////
                                // Tasklet code (T_l0_c0)
                                tmp_call_17_out = abs(w_con_e_0_in);
                                ///////////////////

                                tmp_call_17 = tmp_call_17_out;
                            }
                            {
                                double cfl_w_limit_0_in = cfl_w_limit;
                                double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8) + _for_it_53))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8) + _for_it_54)];
                                double tmp_call_17_0_in = tmp_call_17;
                                double _if_cond_31_out;

                                ///////////////////
                                // Tasklet code (T_l0_c0)
                                _if_cond_31_out = (tmp_call_17_0_in > (cfl_w_limit_0_in * p_metrics_0_in_ddqz_z_full_e_0));
                                ///////////////////

                                _if_cond_31 = _if_cond_31_out;
                            }

                        }
                        if ((_if_cond_31 == 1)) {
                            {

                                {
                                    double w_con_e_0_in = w_con_e;
                                    double tmp_call_19_out;

                                    ///////////////////
                                    // Tasklet code (T_l642_c642)
                                    tmp_call_19_out = abs(w_con_e_0_in);
                                    ///////////////////

                                    tmp_call_19 = tmp_call_19_out;
                                }

                            }
                            tmp_index_950 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9);
                            tmp_index_954 = (ntnd - __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9);
                            {


                            }
                            tmp_index_972 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (1 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                            {
                                double tmp_call_18;
                                double tmp_arg_18;
                                double tmp_arg_19;

                                {
                                    double cfl_w_limit_0_in = cfl_w_limit;
                                    double dtime_0_in = dtime;
                                    double dtime_1_in = dtime;
                                    double p_metrics_0_in_ddqz_z_full_e_0 = v_p_metrics_ddqz_z_full_e[(((((__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8) * ((- __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8) + _for_it_48)) + (__f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 * ((- __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8) + _for_it_53))) - __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8) + _for_it_54)];
                                    double tmp_call_19_0_in = tmp_call_19;
                                    double tmp_arg_19_out;

                                    ///////////////////
                                    // Tasklet code (T_l642_c642)
                                    tmp_arg_19_out = (((tmp_call_19_0_in * dtime_0_in) / p_metrics_0_in_ddqz_z_full_e_0) - (cfl_w_limit_0_in * dtime_1_in));
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
                                    double tmp_call_18_out;

                                    ///////////////////
                                    // Tasklet code (T_l642_c642)
                                    tmp_call_18_out = min(tmp_arg_18_0_in, tmp_arg_19_0_in);
                                    ///////////////////

                                    tmp_call_18 = tmp_call_18_out;
                                }
                                {
                                    double scalfac_exdiff_0_in = scalfac_exdiff;
                                    double tmp_call_18_0_in = tmp_call_18;
                                    double difcoef_out;

                                    ///////////////////
                                    // Tasklet code (T_l642_c642)
                                    difcoef_out = (scalfac_exdiff_0_in * tmp_call_18_0_in);
                                    ///////////////////

                                    difcoef = difcoef_out;
                                }

                            }
                            tmp_index_974 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (1 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                            {


                            }
                            tmp_index_984 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (2 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                            {


                            }
                            tmp_index_986 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (2 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                            {


                            }
                            tmp_index_996 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (3 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                            {


                            }
                            tmp_index_998 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (3 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                            {


                            }
                            tmp_index_1008 = (v_v_p_patch_edges_quad_idx[(((((__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * __f2dace_SA_quad_idx_d_1_s_179_edges_p_patch_4) * (4 - __f2dace_SOA_quad_idx_d_2_s_180_edges_p_patch_4)) + (__f2dace_SA_quad_idx_d_0_s_178_edges_p_patch_4 * ((- __f2dace_SOA_quad_idx_d_1_s_179_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_idx_d_0_s_178_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_0_s_291_p_prog_7);
                            {


                            }
                            tmp_index_1010 = (v_v_p_patch_edges_quad_blk[(((((__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * __f2dace_SA_quad_blk_d_1_s_182_edges_p_patch_4) * (4 - __f2dace_SOA_quad_blk_d_2_s_183_edges_p_patch_4)) + (__f2dace_SA_quad_blk_d_0_s_181_edges_p_patch_4 * ((- __f2dace_SOA_quad_blk_d_1_s_182_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_quad_blk_d_0_s_181_edges_p_patch_4) + _for_it_54)] - __f2dace_SOA_vn_d_2_s_293_p_prog_7);
                            {


                            }
                            tmp_index_1021 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_54)] - 1);
                            {


                            }
                            tmp_index_1023 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (2 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_54)] - 1);
                            {


                            }
                            tmp_index_1030 = (v_v_p_patch_edges_vertex_idx[(((((__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * __f2dace_SA_vertex_idx_d_1_s_171_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_idx_d_2_s_172_edges_p_patch_4)) + (__f2dace_SA_vertex_idx_d_0_s_170_edges_p_patch_4 * ((- __f2dace_SOA_vertex_idx_d_1_s_171_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_idx_d_0_s_170_edges_p_patch_4) + _for_it_54)] - 1);
                            {


                            }
                            tmp_index_1032 = (v_v_p_patch_edges_vertex_blk[(((((__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * __f2dace_SA_vertex_blk_d_1_s_174_edges_p_patch_4) * (1 - __f2dace_SOA_vertex_blk_d_2_s_175_edges_p_patch_4)) + (__f2dace_SA_vertex_blk_d_0_s_173_edges_p_patch_4 * ((- __f2dace_SOA_vertex_blk_d_1_s_174_edges_p_patch_4) + _for_it_48))) - __f2dace_SOA_vertex_blk_d_0_s_173_edges_p_patch_4) + _for_it_54)] - 1);
                            {
                                double* v_p_int_geofac_grdiv;
                                v_p_int_geofac_grdiv = (double*)(&(p_int->geofac_grdiv)[0]);
                                double* v_v_p_patch_edges_area_edge;
                                v_v_p_patch_edges_area_edge = (double*)(&((*v_p_patch_edges)->area_edge)[0]);

                                {
                                    double difcoef_0_in = difcoef;
                                    double p_diag_0_in_ddt_vn_apc_pc_0 = v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) * tmp_index_954) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) + _for_it_53))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9) + _for_it_54)];
                                    double p_int_0_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_48)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (1 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_54)];
                                    double p_int_1_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_48)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (2 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_54)];
                                    double p_int_2_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_48)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (3 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_54)];
                                    double p_int_3_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_48)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (4 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_54)];
                                    double p_int_4_in_geofac_grdiv_0 = v_p_int_geofac_grdiv[(((((__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * __f2dace_SA_geofac_grdiv_d_1_s_38_p_int_6) * ((- __f2dace_SOA_geofac_grdiv_d_2_s_39_p_int_6) + _for_it_48)) + (__f2dace_SA_geofac_grdiv_d_0_s_37_p_int_6 * (5 - __f2dace_SOA_geofac_grdiv_d_1_s_38_p_int_6))) - __f2dace_SOA_geofac_grdiv_d_0_s_37_p_int_6) + _for_it_54)];
                                    double p_patch_0_in_edges_area_edge_0 = v_v_p_patch_edges_area_edge[(((__f2dace_SA_area_edge_d_0_s_188_edges_p_patch_4 * ((- __f2dace_SOA_area_edge_d_1_s_189_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_area_edge_d_0_s_188_edges_p_patch_4) + _for_it_54)];
                                    double p_patch_1_in_edges_tangent_orientation_0 = v_v_p_patch_edges_tangent_orientation[(((__f2dace_SA_tangent_orientation_d_0_s_176_edges_p_patch_4 * ((- __f2dace_SOA_tangent_orientation_d_1_s_177_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_tangent_orientation_d_0_s_176_edges_p_patch_4) + _for_it_54)];
                                    double p_patch_2_in_edges_inv_primal_edge_length_0 = v_v_p_patch_edges_inv_primal_edge_length[(((__f2dace_SA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4 * ((- __f2dace_SOA_inv_primal_edge_length_d_1_s_185_edges_p_patch_4) + _for_it_48)) - __f2dace_SOA_inv_primal_edge_length_d_0_s_184_edges_p_patch_4) + _for_it_54)];
                                    double p_prog_0_in_vn_0 = v_p_prog_vn[(((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * ((- __f2dace_SOA_vn_d_2_s_293_p_prog_7) + _for_it_48)) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_53))) - __f2dace_SOA_vn_d_0_s_291_p_prog_7) + _for_it_54)];
                                    double p_prog_1_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_974) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_53))) + tmp_index_972)];
                                    double p_prog_2_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_986) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_53))) + tmp_index_984)];
                                    double p_prog_3_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_998) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_53))) + tmp_index_996)];
                                    double p_prog_4_in_vn_0 = v_p_prog_vn[((((__f2dace_SA_vn_d_0_s_291_p_prog_7 * __f2dace_SA_vn_d_1_s_292_p_prog_7) * tmp_index_1010) + (__f2dace_SA_vn_d_0_s_291_p_prog_7 * ((- __f2dace_SOA_vn_d_1_s_292_p_prog_7) + _for_it_53))) + tmp_index_1008)];
                                    double zeta_0_in_0 = zeta[((tmp_index_1021 + ((tmp_index_1023 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_53 - 1)))];
                                    double zeta_1_in_0 = zeta[((tmp_index_1030 + ((tmp_index_1032 * tmp_struct_symbol_13) * tmp_struct_symbol_14)) + (tmp_struct_symbol_13 * (_for_it_53 - 1)))];
                                    double p_diag_out_ddt_vn_apc_pc_0;

                                    ///////////////////
                                    // Tasklet code (T_l643_c643)
                                    p_diag_out_ddt_vn_apc_pc_0 = (p_diag_0_in_ddt_vn_apc_pc_0 + ((difcoef_0_in * p_patch_0_in_edges_area_edge_0) * ((((((p_int_0_in_geofac_grdiv_0 * p_prog_0_in_vn_0) + (p_int_1_in_geofac_grdiv_0 * p_prog_1_in_vn_0)) + (p_int_2_in_geofac_grdiv_0 * p_prog_2_in_vn_0)) + (p_int_3_in_geofac_grdiv_0 * p_prog_3_in_vn_0)) + (p_int_4_in_geofac_grdiv_0 * p_prog_4_in_vn_0)) + ((p_patch_1_in_edges_tangent_orientation_0 * p_patch_2_in_edges_inv_primal_edge_length_0) * (zeta_0_in_0 - zeta_1_in_0)))));
                                    ///////////////////

                                    v_p_diag_ddt_vn_apc_pc[(((((((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) * tmp_index_950) + ((__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) * ((- __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9) + _for_it_48))) + (__f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 * ((- __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9) + _for_it_53))) - __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9) + _for_it_54)] = p_diag_out_ddt_vn_apc_pc_0;
                                }

                            }
                        }

                    }
                }

            }
        }

    }

    {


    }
    i_startblk_var_148 = v_v_p_patch_cells_start_block[(4 - __f2dace_SOA_start_block_d_0_s_162_cells_p_patch_2)];

    {


    }
    i_endblk_var_149 = v_v_p_patch_cells_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];
    tmp_call_20 = -1.7976931348623157e+308;

    for (tmp_parfor_0 = i_startblk_var_148; (tmp_parfor_0 <= i_endblk_var_149); tmp_parfor_0 = (tmp_parfor_0 + 1)) {
        if ((vcflmax[(tmp_parfor_0 - 1)] > tmp_call_20)) {

            tmp_call_20 = vcflmax[(tmp_parfor_0 - 1)];

        }

    }

    {
        double max_vcfl_dyn_var_156;
        double* v_p_diag_max_vcfl_dyn;
        v_p_diag_max_vcfl_dyn = (double*)(&(p_diag->max_vcfl_dyn));

        {
            double max_vcfl_dyn_var_156_out;

            ///////////////////
            // Tasklet code (T_l652_c652)
            max_vcfl_dyn_var_156_out = max(0.0, tmp_call_20);
            ///////////////////

            max_vcfl_dyn_var_156 = max_vcfl_dyn_var_156_out;
        }
        {
            double max_vcfl_dyn_var_156_0_in = max_vcfl_dyn_var_156;
            double p_diag_out_max_vcfl_dyn;

            ///////////////////
            // Tasklet code (T_l653_c653)
            p_diag_out_max_vcfl_dyn = max_vcfl_dyn_var_156_0_in;
            ///////////////////

            v_p_diag_max_vcfl_dyn[0] = p_diag_out_max_vcfl_dyn;
        }

    }

    delete[] z_w_concorr_mc;
    delete[] z_w_con_c;
    delete[] z_w_con_c_full;
    delete[] z_v_grad_w;
    delete[] z_w_v;
    delete[] zeta;
    delete[] z_ekinh;
    delete[] vcflmax;
    delete[] levmask;
    delete[] levelmask;
    delete[] cfl_clipping;
}

DACE_EXPORTED void __program_velocity_tendencies(velocity_tendencies_state_t *__state, global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_369, int __f2dace_A_z_kin_hor_e_d_1_s_370, int __f2dace_A_z_vt_ie_d_0_s_372, int __f2dace_A_z_vt_ie_d_1_s_373, int __f2dace_A_z_w_concorr_me_d_0_s_366, int __f2dace_A_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_kin_hor_e_d_0_s_369, int __f2dace_OA_z_kin_hor_e_d_1_s_370, int __f2dace_OA_z_kin_hor_e_d_2_s_371, int __f2dace_OA_z_vt_ie_d_0_s_372, int __f2dace_OA_z_vt_ie_d_1_s_373, int __f2dace_OA_z_vt_ie_d_2_s_374, int __f2dace_OA_z_w_concorr_me_d_0_s_366, int __f2dace_OA_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_w_concorr_me_d_2_s_368, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    __program_velocity_tendencies_internal(__state, global_data, p_diag, p_int, p_metrics, p_patch, p_prog, z_kin_hor_e, z_vt_ie, z_w_concorr_me, __f2dace_A_z_kin_hor_e_d_0_s_369, __f2dace_A_z_kin_hor_e_d_1_s_370, __f2dace_A_z_vt_ie_d_0_s_372, __f2dace_A_z_vt_ie_d_1_s_373, __f2dace_A_z_w_concorr_me_d_0_s_366, __f2dace_A_z_w_concorr_me_d_1_s_367, __f2dace_OA_z_kin_hor_e_d_0_s_369, __f2dace_OA_z_kin_hor_e_d_1_s_370, __f2dace_OA_z_kin_hor_e_d_2_s_371, __f2dace_OA_z_vt_ie_d_0_s_372, __f2dace_OA_z_vt_ie_d_1_s_373, __f2dace_OA_z_vt_ie_d_2_s_374, __f2dace_OA_z_w_concorr_me_d_0_s_366, __f2dace_OA_z_w_concorr_me_d_1_s_367, __f2dace_OA_z_w_concorr_me_d_2_s_368, dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
}

DACE_EXPORTED velocity_tendencies_state_t *__dace_init_velocity_tendencies(global_data_type* global_data, t_nh_diag* p_diag, t_int_state* p_int, t_nh_metrics* p_metrics, t_patch* p_patch, t_nh_prog* p_prog, double * __restrict__ z_kin_hor_e, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_me, int __f2dace_A_z_kin_hor_e_d_0_s_369, int __f2dace_A_z_kin_hor_e_d_1_s_370, int __f2dace_A_z_vt_ie_d_0_s_372, int __f2dace_A_z_vt_ie_d_1_s_373, int __f2dace_A_z_w_concorr_me_d_0_s_366, int __f2dace_A_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_kin_hor_e_d_0_s_369, int __f2dace_OA_z_kin_hor_e_d_1_s_370, int __f2dace_OA_z_kin_hor_e_d_2_s_371, int __f2dace_OA_z_vt_ie_d_0_s_372, int __f2dace_OA_z_vt_ie_d_1_s_373, int __f2dace_OA_z_vt_ie_d_2_s_374, int __f2dace_OA_z_w_concorr_me_d_0_s_366, int __f2dace_OA_z_w_concorr_me_d_1_s_367, int __f2dace_OA_z_w_concorr_me_d_2_s_368, double dt_linintp_ubc, double dtime, int istep, int ldeepatmo, int lvn_only, int ntnd)
{
    int __result = 0;
    velocity_tendencies_state_t *__state = new velocity_tendencies_state_t;


    tmp_struct_symbol_0=global_data->nproma;
    tmp_struct_symbol_1=p_patch->nlev;
    tmp_struct_symbol_2=global_data->nproma;
    tmp_struct_symbol_3=p_patch->nlevp1;
    tmp_struct_symbol_4=global_data->nproma;
    tmp_struct_symbol_5=p_patch->nlev;
    tmp_struct_symbol_6=p_patch->nblks_c;
    tmp_struct_symbol_7=global_data->nproma;
    tmp_struct_symbol_8=p_patch->nlev;
    tmp_struct_symbol_9=p_patch->nblks_e;
    tmp_struct_symbol_10=global_data->nproma;
    tmp_struct_symbol_11=p_patch->nlevp1;
    tmp_struct_symbol_12=p_patch->nblks_v;
    tmp_struct_symbol_13=global_data->nproma;
    tmp_struct_symbol_14=p_patch->nlev;
    tmp_struct_symbol_15=p_patch->nblks_v;
    tmp_struct_symbol_16=global_data->nproma;
    tmp_struct_symbol_17=p_patch->nlev;
    tmp_struct_symbol_18=p_patch->nblks_c;
    tmp_struct_symbol_19=p_patch->nblks_c;
    tmp_struct_symbol_20=p_patch->nblks_c;
    tmp_struct_symbol_21=p_patch->nlev;
    tmp_struct_symbol_22=p_patch->nlev;
    tmp_struct_symbol_23=global_data->nproma;
    tmp_struct_symbol_24=p_patch->nlevp1;
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
    __f2dace_SOA_w_d_0_s_288_p_prog_7 = p_prog->__f2dace_SOA_w_d_0_s_288;
    __f2dace_SOA_w_d_1_s_289_p_prog_7 = p_prog->__f2dace_SOA_w_d_1_s_289;
    __f2dace_SOA_w_d_2_s_290_p_prog_7 = p_prog->__f2dace_SOA_w_d_2_s_290;
    __f2dace_SA_w_d_0_s_288_p_prog_7 = p_prog->__f2dace_SA_w_d_0_s_288;
    __f2dace_SA_w_d_1_s_289_p_prog_7 = p_prog->__f2dace_SA_w_d_1_s_289;
    __f2dace_SA_w_d_2_s_290_p_prog_7 = p_prog->__f2dace_SA_w_d_2_s_290;
    __f2dace_SOA_vn_d_0_s_291_p_prog_7 = p_prog->__f2dace_SOA_vn_d_0_s_291;
    __f2dace_SOA_vn_d_1_s_292_p_prog_7 = p_prog->__f2dace_SOA_vn_d_1_s_292;
    __f2dace_SOA_vn_d_2_s_293_p_prog_7 = p_prog->__f2dace_SOA_vn_d_2_s_293;
    __f2dace_SA_vn_d_0_s_291_p_prog_7 = p_prog->__f2dace_SA_vn_d_0_s_291;
    __f2dace_SA_vn_d_1_s_292_p_prog_7 = p_prog->__f2dace_SA_vn_d_1_s_292;
    __f2dace_SA_vn_d_2_s_293_p_prog_7 = p_prog->__f2dace_SA_vn_d_2_s_293;
    __f2dace_SOA_ddxn_z_full_d_0_s_314_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_0_s_314;
    __f2dace_SOA_ddxn_z_full_d_1_s_315_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_1_s_315;
    __f2dace_SOA_ddxn_z_full_d_2_s_316_p_metrics_8 = p_metrics->__f2dace_SOA_ddxn_z_full_d_2_s_316;
    __f2dace_SA_ddxn_z_full_d_0_s_314_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_0_s_314;
    __f2dace_SA_ddxn_z_full_d_1_s_315_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_1_s_315;
    __f2dace_SA_ddxn_z_full_d_2_s_316_p_metrics_8 = p_metrics->__f2dace_SA_ddxn_z_full_d_2_s_316;
    __f2dace_SOA_ddxt_z_full_d_0_s_317_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_0_s_317;
    __f2dace_SOA_ddxt_z_full_d_1_s_318_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_1_s_318;
    __f2dace_SOA_ddxt_z_full_d_2_s_319_p_metrics_8 = p_metrics->__f2dace_SOA_ddxt_z_full_d_2_s_319;
    __f2dace_SA_ddxt_z_full_d_0_s_317_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_0_s_317;
    __f2dace_SA_ddxt_z_full_d_1_s_318_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_1_s_318;
    __f2dace_SA_ddxt_z_full_d_2_s_319_p_metrics_8 = p_metrics->__f2dace_SA_ddxt_z_full_d_2_s_319;
    __f2dace_SOA_ddqz_z_full_e_d_0_s_320_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_0_s_320;
    __f2dace_SOA_ddqz_z_full_e_d_1_s_321_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_1_s_321;
    __f2dace_SOA_ddqz_z_full_e_d_2_s_322_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_full_e_d_2_s_322;
    __f2dace_SA_ddqz_z_full_e_d_0_s_320_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_0_s_320;
    __f2dace_SA_ddqz_z_full_e_d_1_s_321_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_1_s_321;
    __f2dace_SA_ddqz_z_full_e_d_2_s_322_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_full_e_d_2_s_322;
    __f2dace_SOA_ddqz_z_half_d_0_s_323_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_0_s_323;
    __f2dace_SOA_ddqz_z_half_d_1_s_324_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_1_s_324;
    __f2dace_SOA_ddqz_z_half_d_2_s_325_p_metrics_8 = p_metrics->__f2dace_SOA_ddqz_z_half_d_2_s_325;
    __f2dace_SA_ddqz_z_half_d_0_s_323_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_0_s_323;
    __f2dace_SA_ddqz_z_half_d_1_s_324_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_1_s_324;
    __f2dace_SA_ddqz_z_half_d_2_s_325_p_metrics_8 = p_metrics->__f2dace_SA_ddqz_z_half_d_2_s_325;
    __f2dace_SOA_wgtfac_c_d_0_s_326_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_0_s_326;
    __f2dace_SOA_wgtfac_c_d_1_s_327_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_1_s_327;
    __f2dace_SOA_wgtfac_c_d_2_s_328_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_c_d_2_s_328;
    __f2dace_SA_wgtfac_c_d_0_s_326_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_0_s_326;
    __f2dace_SA_wgtfac_c_d_1_s_327_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_1_s_327;
    __f2dace_SA_wgtfac_c_d_2_s_328_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_c_d_2_s_328;
    __f2dace_SOA_wgtfac_e_d_0_s_329_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_0_s_329;
    __f2dace_SOA_wgtfac_e_d_1_s_330_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_1_s_330;
    __f2dace_SOA_wgtfac_e_d_2_s_331_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfac_e_d_2_s_331;
    __f2dace_SA_wgtfac_e_d_0_s_329_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_0_s_329;
    __f2dace_SA_wgtfac_e_d_1_s_330_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_1_s_330;
    __f2dace_SA_wgtfac_e_d_2_s_331_p_metrics_8 = p_metrics->__f2dace_SA_wgtfac_e_d_2_s_331;
    __f2dace_SOA_wgtfacq_e_d_0_s_332_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_0_s_332;
    __f2dace_SOA_wgtfacq_e_d_1_s_333_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_1_s_333;
    __f2dace_SOA_wgtfacq_e_d_2_s_334_p_metrics_8 = p_metrics->__f2dace_SOA_wgtfacq_e_d_2_s_334;
    __f2dace_SA_wgtfacq_e_d_0_s_332_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_0_s_332;
    __f2dace_SA_wgtfacq_e_d_1_s_333_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_1_s_333;
    __f2dace_SA_wgtfacq_e_d_2_s_334_p_metrics_8 = p_metrics->__f2dace_SA_wgtfacq_e_d_2_s_334;
    __f2dace_SOA_coeff_gradekin_d_0_s_335_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_0_s_335;
    __f2dace_SOA_coeff_gradekin_d_1_s_336_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_1_s_336;
    __f2dace_SOA_coeff_gradekin_d_2_s_337_p_metrics_8 = p_metrics->__f2dace_SOA_coeff_gradekin_d_2_s_337;
    __f2dace_SA_coeff_gradekin_d_0_s_335_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_0_s_335;
    __f2dace_SA_coeff_gradekin_d_1_s_336_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_1_s_336;
    __f2dace_SA_coeff_gradekin_d_2_s_337_p_metrics_8 = p_metrics->__f2dace_SA_coeff_gradekin_d_2_s_337;
    __f2dace_SOA_coeff1_dwdz_d_0_s_338_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_0_s_338;
    __f2dace_SOA_coeff1_dwdz_d_1_s_339_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_1_s_339;
    __f2dace_SOA_coeff1_dwdz_d_2_s_340_p_metrics_8 = p_metrics->__f2dace_SOA_coeff1_dwdz_d_2_s_340;
    __f2dace_SA_coeff1_dwdz_d_0_s_338_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_0_s_338;
    __f2dace_SA_coeff1_dwdz_d_1_s_339_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_1_s_339;
    __f2dace_SA_coeff1_dwdz_d_2_s_340_p_metrics_8 = p_metrics->__f2dace_SA_coeff1_dwdz_d_2_s_340;
    __f2dace_SOA_coeff2_dwdz_d_0_s_341_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_0_s_341;
    __f2dace_SOA_coeff2_dwdz_d_1_s_342_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_1_s_342;
    __f2dace_SOA_coeff2_dwdz_d_2_s_343_p_metrics_8 = p_metrics->__f2dace_SOA_coeff2_dwdz_d_2_s_343;
    __f2dace_SA_coeff2_dwdz_d_0_s_341_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_0_s_341;
    __f2dace_SA_coeff2_dwdz_d_1_s_342_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_1_s_342;
    __f2dace_SA_coeff2_dwdz_d_2_s_343_p_metrics_8 = p_metrics->__f2dace_SA_coeff2_dwdz_d_2_s_343;
    __f2dace_SOA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_mc_d_0_s_344;
    __f2dace_SA_deepatmo_gradh_mc_d_0_s_344_p_metrics_8 = p_metrics->__f2dace_SA_deepatmo_gradh_mc_d_0_s_344;
    __f2dace_SOA_deepatmo_invr_mc_d_0_s_345_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_mc_d_0_s_345;
    __f2dace_SA_deepatmo_invr_mc_d_0_s_345_p_metrics_8 = p_metrics->__f2dace_SA_deepatmo_invr_mc_d_0_s_345;
    __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_346_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_gradh_ifc_d_0_s_346;
    __f2dace_SA_deepatmo_gradh_ifc_d_0_s_346_p_metrics_8 = p_metrics->__f2dace_SA_deepatmo_gradh_ifc_d_0_s_346;
    __f2dace_SOA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8 = p_metrics->__f2dace_SOA_deepatmo_invr_ifc_d_0_s_347;
    __f2dace_SA_deepatmo_invr_ifc_d_0_s_347_p_metrics_8 = p_metrics->__f2dace_SA_deepatmo_invr_ifc_d_0_s_347;
    __f2dace_SOA_vn_ie_ubc_d_0_s_294_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_ubc_d_0_s_294;
    __f2dace_SOA_vn_ie_ubc_d_1_s_295_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_ubc_d_1_s_295;
    __f2dace_SOA_vn_ie_ubc_d_2_s_296_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_ubc_d_2_s_296;
    __f2dace_SA_vn_ie_ubc_d_0_s_294_p_diag_9 = p_diag->__f2dace_SA_vn_ie_ubc_d_0_s_294;
    __f2dace_SA_vn_ie_ubc_d_1_s_295_p_diag_9 = p_diag->__f2dace_SA_vn_ie_ubc_d_1_s_295;
    __f2dace_SA_vn_ie_ubc_d_2_s_296_p_diag_9 = p_diag->__f2dace_SA_vn_ie_ubc_d_2_s_296;
    __f2dace_SOA_vt_d_0_s_297_p_diag_9 = p_diag->__f2dace_SOA_vt_d_0_s_297;
    __f2dace_SOA_vt_d_1_s_298_p_diag_9 = p_diag->__f2dace_SOA_vt_d_1_s_298;
    __f2dace_SOA_vt_d_2_s_299_p_diag_9 = p_diag->__f2dace_SOA_vt_d_2_s_299;
    __f2dace_SA_vt_d_0_s_297_p_diag_9 = p_diag->__f2dace_SA_vt_d_0_s_297;
    __f2dace_SA_vt_d_1_s_298_p_diag_9 = p_diag->__f2dace_SA_vt_d_1_s_298;
    __f2dace_SA_vt_d_2_s_299_p_diag_9 = p_diag->__f2dace_SA_vt_d_2_s_299;
    __f2dace_SOA_vn_ie_d_0_s_300_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_0_s_300;
    __f2dace_SOA_vn_ie_d_1_s_301_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_1_s_301;
    __f2dace_SOA_vn_ie_d_2_s_302_p_diag_9 = p_diag->__f2dace_SOA_vn_ie_d_2_s_302;
    __f2dace_SA_vn_ie_d_0_s_300_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_0_s_300;
    __f2dace_SA_vn_ie_d_1_s_301_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_1_s_301;
    __f2dace_SA_vn_ie_d_2_s_302_p_diag_9 = p_diag->__f2dace_SA_vn_ie_d_2_s_302;
    __f2dace_SOA_w_concorr_c_d_0_s_303_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_0_s_303;
    __f2dace_SOA_w_concorr_c_d_1_s_304_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_1_s_304;
    __f2dace_SOA_w_concorr_c_d_2_s_305_p_diag_9 = p_diag->__f2dace_SOA_w_concorr_c_d_2_s_305;
    __f2dace_SA_w_concorr_c_d_0_s_303_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_0_s_303;
    __f2dace_SA_w_concorr_c_d_1_s_304_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_1_s_304;
    __f2dace_SA_w_concorr_c_d_2_s_305_p_diag_9 = p_diag->__f2dace_SA_w_concorr_c_d_2_s_305;
    __f2dace_SOA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_0_s_306;
    __f2dace_SOA_ddt_vn_apc_pc_d_1_s_307_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_1_s_307;
    __f2dace_SOA_ddt_vn_apc_pc_d_2_s_308_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_2_s_308;
    __f2dace_SOA_ddt_vn_apc_pc_d_3_s_309_p_diag_9 = p_diag->__f2dace_SOA_ddt_vn_apc_pc_d_3_s_309;
    __f2dace_SA_ddt_vn_apc_pc_d_0_s_306_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_0_s_306;
    __f2dace_SA_ddt_vn_apc_pc_d_1_s_307_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_1_s_307;
    __f2dace_SA_ddt_vn_apc_pc_d_2_s_308_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_2_s_308;
    __f2dace_SA_ddt_vn_apc_pc_d_3_s_309_p_diag_9 = p_diag->__f2dace_SA_ddt_vn_apc_pc_d_3_s_309;
    __f2dace_SOA_ddt_w_adv_pc_d_0_s_310_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_0_s_310;
    __f2dace_SOA_ddt_w_adv_pc_d_1_s_311_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_1_s_311;
    __f2dace_SOA_ddt_w_adv_pc_d_2_s_312_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_2_s_312;
    __f2dace_SOA_ddt_w_adv_pc_d_3_s_313_p_diag_9 = p_diag->__f2dace_SOA_ddt_w_adv_pc_d_3_s_313;
    __f2dace_SA_ddt_w_adv_pc_d_0_s_310_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_0_s_310;
    __f2dace_SA_ddt_w_adv_pc_d_1_s_311_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_1_s_311;
    __f2dace_SA_ddt_w_adv_pc_d_2_s_312_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_2_s_312;
    __f2dace_SA_ddt_w_adv_pc_d_3_s_313_p_diag_9 = p_diag->__f2dace_SA_ddt_w_adv_pc_d_3_s_313;

    if (__result) {
        delete __state;
        return nullptr;
    }
    return __state;
}

DACE_EXPORTED int __dace_exit_velocity_tendencies(velocity_tendencies_state_t *__state)
{
    int __err = 0;
    delete __state;
    return __err;
}
