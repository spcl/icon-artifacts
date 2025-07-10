
#ifndef __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__
#define __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__

#include <dace/dace.h>


struct t_grid_edges {
    int __f2dace_SA_end_block_d_0_s_69 = {};
int __f2dace_SA_end_index_d_0_s_67 = {};
int __f2dace_SA_quad_blk_d_0_s_63 = {};
int __f2dace_SA_quad_blk_d_1_s_64 = {};
int __f2dace_SA_quad_blk_d_2_s_65 = {};
int __f2dace_SA_quad_idx_d_0_s_60 = {};
int __f2dace_SA_quad_idx_d_1_s_61 = {};
int __f2dace_SA_quad_idx_d_2_s_62 = {};
int __f2dace_SA_start_block_d_0_s_68 = {};
int __f2dace_SA_start_index_d_0_s_66 = {};
int __f2dace_SOA_end_block_d_0_s_69 = {};
int __f2dace_SOA_end_index_d_0_s_67 = {};
int __f2dace_SOA_quad_blk_d_0_s_63 = {};
int __f2dace_SOA_quad_blk_d_1_s_64 = {};
int __f2dace_SOA_quad_blk_d_2_s_65 = {};
int __f2dace_SOA_quad_idx_d_0_s_60 = {};
int __f2dace_SOA_quad_idx_d_1_s_61 = {};
int __f2dace_SOA_quad_idx_d_2_s_62 = {};
int __f2dace_SOA_start_block_d_0_s_68 = {};
int __f2dace_SOA_start_index_d_0_s_66 = {};
int* end_block = {};
int* end_index = {};
int* quad_blk = {};
int* quad_idx = {};
int* start_block = {};
int* start_index = {};
};


struct t_int_state {
    int __f2dace_SA_e_bln_c_s_d_0_s_15 = {};
int __f2dace_SA_e_bln_c_s_d_1_s_16 = {};
int __f2dace_SA_e_bln_c_s_d_2_s_17 = {};
int __f2dace_SA_e_flx_avg_d_0_s_18 = {};
int __f2dace_SA_e_flx_avg_d_1_s_19 = {};
int __f2dace_SA_e_flx_avg_d_2_s_20 = {};
int __f2dace_SA_geofac_div_d_0_s_24 = {};
int __f2dace_SA_geofac_div_d_1_s_25 = {};
int __f2dace_SA_geofac_div_d_2_s_26 = {};
int __f2dace_SA_geofac_grdiv_d_0_s_27 = {};
int __f2dace_SA_geofac_grdiv_d_1_s_28 = {};
int __f2dace_SA_geofac_grdiv_d_2_s_29 = {};
int __f2dace_SA_rbf_vec_coeff_e_d_0_s_21 = {};
int __f2dace_SA_rbf_vec_coeff_e_d_1_s_22 = {};
int __f2dace_SA_rbf_vec_coeff_e_d_2_s_23 = {};
int __f2dace_SOA_e_bln_c_s_d_0_s_15 = {};
int __f2dace_SOA_e_bln_c_s_d_1_s_16 = {};
int __f2dace_SOA_e_bln_c_s_d_2_s_17 = {};
int __f2dace_SOA_e_flx_avg_d_0_s_18 = {};
int __f2dace_SOA_e_flx_avg_d_1_s_19 = {};
int __f2dace_SOA_e_flx_avg_d_2_s_20 = {};
int __f2dace_SOA_geofac_div_d_0_s_24 = {};
int __f2dace_SOA_geofac_div_d_1_s_25 = {};
int __f2dace_SOA_geofac_div_d_2_s_26 = {};
int __f2dace_SOA_geofac_grdiv_d_0_s_27 = {};
int __f2dace_SOA_geofac_grdiv_d_1_s_28 = {};
int __f2dace_SOA_geofac_grdiv_d_2_s_29 = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_21 = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_22 = {};
int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_23 = {};
double* e_bln_c_s = {};
double* e_flx_avg = {};
double* geofac_div = {};
double* geofac_grdiv = {};
double* rbf_vec_coeff_e = {};
};


struct t_nh_diag {
    int __f2dace_SA_ddt_exner_phy_d_0_s_255 = {};
int __f2dace_SA_ddt_exner_phy_d_1_s_256 = {};
int __f2dace_SA_ddt_exner_phy_d_2_s_257 = {};
int __f2dace_SA_ddt_w_adv_pc_d_0_s_267 = {};
int __f2dace_SA_ddt_w_adv_pc_d_1_s_268 = {};
int __f2dace_SA_ddt_w_adv_pc_d_2_s_269 = {};
int __f2dace_SA_ddt_w_adv_pc_d_3_s_270 = {};
int __f2dace_SA_exner_dyn_incr_d_0_s_258 = {};
int __f2dace_SA_exner_dyn_incr_d_1_s_259 = {};
int __f2dace_SA_exner_dyn_incr_d_2_s_260 = {};
int __f2dace_SA_exner_incr_d_0_s_246 = {};
int __f2dace_SA_exner_incr_d_1_s_247 = {};
int __f2dace_SA_exner_incr_d_2_s_248 = {};
int __f2dace_SA_exner_pr_d_0_s_207 = {};
int __f2dace_SA_exner_pr_d_1_s_208 = {};
int __f2dace_SA_exner_pr_d_2_s_209 = {};
int __f2dace_SA_grf_bdy_mflx_d_0_s_225 = {};
int __f2dace_SA_grf_bdy_mflx_d_1_s_226 = {};
int __f2dace_SA_grf_bdy_mflx_d_2_s_227 = {};
int __f2dace_SA_grf_tend_rho_d_0_s_222 = {};
int __f2dace_SA_grf_tend_rho_d_1_s_223 = {};
int __f2dace_SA_grf_tend_rho_d_2_s_224 = {};
int __f2dace_SA_grf_tend_thv_d_0_s_228 = {};
int __f2dace_SA_grf_tend_thv_d_1_s_229 = {};
int __f2dace_SA_grf_tend_thv_d_2_s_230 = {};
int __f2dace_SA_grf_tend_w_d_0_s_219 = {};
int __f2dace_SA_grf_tend_w_d_1_s_220 = {};
int __f2dace_SA_grf_tend_w_d_2_s_221 = {};
int __f2dace_SA_mass_fl_e_d_0_s_210 = {};
int __f2dace_SA_mass_fl_e_d_1_s_211 = {};
int __f2dace_SA_mass_fl_e_d_2_s_212 = {};
int __f2dace_SA_mflx_ic_ubc_d_0_s_243 = {};
int __f2dace_SA_mflx_ic_ubc_d_1_s_244 = {};
int __f2dace_SA_mflx_ic_ubc_d_2_s_245 = {};
int __f2dace_SA_rho_ic_d_0_s_213 = {};
int __f2dace_SA_rho_ic_d_1_s_214 = {};
int __f2dace_SA_rho_ic_d_2_s_215 = {};
int __f2dace_SA_rho_ic_ubc_d_0_s_240 = {};
int __f2dace_SA_rho_ic_ubc_d_1_s_241 = {};
int __f2dace_SA_rho_ic_ubc_d_2_s_242 = {};
int __f2dace_SA_rho_incr_d_0_s_249 = {};
int __f2dace_SA_rho_incr_d_1_s_250 = {};
int __f2dace_SA_rho_incr_d_2_s_251 = {};
int __f2dace_SA_theta_v_ic_d_0_s_216 = {};
int __f2dace_SA_theta_v_ic_d_1_s_217 = {};
int __f2dace_SA_theta_v_ic_d_2_s_218 = {};
int __f2dace_SA_theta_v_ic_ubc_d_0_s_237 = {};
int __f2dace_SA_theta_v_ic_ubc_d_1_s_238 = {};
int __f2dace_SA_theta_v_ic_ubc_d_2_s_239 = {};
int __f2dace_SA_vn_ie_d_0_s_261 = {};
int __f2dace_SA_vn_ie_d_1_s_262 = {};
int __f2dace_SA_vn_ie_d_2_s_263 = {};
int __f2dace_SA_vn_ie_ubc_d_0_s_231 = {};
int __f2dace_SA_vn_ie_ubc_d_1_s_232 = {};
int __f2dace_SA_vn_ie_ubc_d_2_s_233 = {};
int __f2dace_SA_vt_d_0_s_252 = {};
int __f2dace_SA_vt_d_1_s_253 = {};
int __f2dace_SA_vt_d_2_s_254 = {};
int __f2dace_SA_w_concorr_c_d_0_s_264 = {};
int __f2dace_SA_w_concorr_c_d_1_s_265 = {};
int __f2dace_SA_w_concorr_c_d_2_s_266 = {};
int __f2dace_SA_w_ubc_d_0_s_234 = {};
int __f2dace_SA_w_ubc_d_1_s_235 = {};
int __f2dace_SA_w_ubc_d_2_s_236 = {};
int __f2dace_SOA_ddt_exner_phy_d_0_s_255 = {};
int __f2dace_SOA_ddt_exner_phy_d_1_s_256 = {};
int __f2dace_SOA_ddt_exner_phy_d_2_s_257 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_0_s_267 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_1_s_268 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_2_s_269 = {};
int __f2dace_SOA_ddt_w_adv_pc_d_3_s_270 = {};
int __f2dace_SOA_exner_dyn_incr_d_0_s_258 = {};
int __f2dace_SOA_exner_dyn_incr_d_1_s_259 = {};
int __f2dace_SOA_exner_dyn_incr_d_2_s_260 = {};
int __f2dace_SOA_exner_incr_d_0_s_246 = {};
int __f2dace_SOA_exner_incr_d_1_s_247 = {};
int __f2dace_SOA_exner_incr_d_2_s_248 = {};
int __f2dace_SOA_exner_pr_d_0_s_207 = {};
int __f2dace_SOA_exner_pr_d_1_s_208 = {};
int __f2dace_SOA_exner_pr_d_2_s_209 = {};
int __f2dace_SOA_grf_bdy_mflx_d_0_s_225 = {};
int __f2dace_SOA_grf_bdy_mflx_d_1_s_226 = {};
int __f2dace_SOA_grf_bdy_mflx_d_2_s_227 = {};
int __f2dace_SOA_grf_tend_rho_d_0_s_222 = {};
int __f2dace_SOA_grf_tend_rho_d_1_s_223 = {};
int __f2dace_SOA_grf_tend_rho_d_2_s_224 = {};
int __f2dace_SOA_grf_tend_thv_d_0_s_228 = {};
int __f2dace_SOA_grf_tend_thv_d_1_s_229 = {};
int __f2dace_SOA_grf_tend_thv_d_2_s_230 = {};
int __f2dace_SOA_grf_tend_w_d_0_s_219 = {};
int __f2dace_SOA_grf_tend_w_d_1_s_220 = {};
int __f2dace_SOA_grf_tend_w_d_2_s_221 = {};
int __f2dace_SOA_mass_fl_e_d_0_s_210 = {};
int __f2dace_SOA_mass_fl_e_d_1_s_211 = {};
int __f2dace_SOA_mass_fl_e_d_2_s_212 = {};
int __f2dace_SOA_mflx_ic_ubc_d_0_s_243 = {};
int __f2dace_SOA_mflx_ic_ubc_d_1_s_244 = {};
int __f2dace_SOA_mflx_ic_ubc_d_2_s_245 = {};
int __f2dace_SOA_rho_ic_d_0_s_213 = {};
int __f2dace_SOA_rho_ic_d_1_s_214 = {};
int __f2dace_SOA_rho_ic_d_2_s_215 = {};
int __f2dace_SOA_rho_ic_ubc_d_0_s_240 = {};
int __f2dace_SOA_rho_ic_ubc_d_1_s_241 = {};
int __f2dace_SOA_rho_ic_ubc_d_2_s_242 = {};
int __f2dace_SOA_rho_incr_d_0_s_249 = {};
int __f2dace_SOA_rho_incr_d_1_s_250 = {};
int __f2dace_SOA_rho_incr_d_2_s_251 = {};
int __f2dace_SOA_theta_v_ic_d_0_s_216 = {};
int __f2dace_SOA_theta_v_ic_d_1_s_217 = {};
int __f2dace_SOA_theta_v_ic_d_2_s_218 = {};
int __f2dace_SOA_theta_v_ic_ubc_d_0_s_237 = {};
int __f2dace_SOA_theta_v_ic_ubc_d_1_s_238 = {};
int __f2dace_SOA_theta_v_ic_ubc_d_2_s_239 = {};
int __f2dace_SOA_vn_ie_d_0_s_261 = {};
int __f2dace_SOA_vn_ie_d_1_s_262 = {};
int __f2dace_SOA_vn_ie_d_2_s_263 = {};
int __f2dace_SOA_vn_ie_ubc_d_0_s_231 = {};
int __f2dace_SOA_vn_ie_ubc_d_1_s_232 = {};
int __f2dace_SOA_vn_ie_ubc_d_2_s_233 = {};
int __f2dace_SOA_vt_d_0_s_252 = {};
int __f2dace_SOA_vt_d_1_s_253 = {};
int __f2dace_SOA_vt_d_2_s_254 = {};
int __f2dace_SOA_w_concorr_c_d_0_s_264 = {};
int __f2dace_SOA_w_concorr_c_d_1_s_265 = {};
int __f2dace_SOA_w_concorr_c_d_2_s_266 = {};
int __f2dace_SOA_w_ubc_d_0_s_234 = {};
int __f2dace_SOA_w_ubc_d_1_s_235 = {};
int __f2dace_SOA_w_ubc_d_2_s_236 = {};
double* ddt_exner_phy = {};
double* ddt_w_adv_pc = {};
double* exner_dyn_incr = {};
double* exner_incr = {};
double* exner_pr = {};
double* grf_bdy_mflx = {};
double* grf_tend_rho = {};
double* grf_tend_thv = {};
double* grf_tend_w = {};
double* mass_fl_e = {};
double* mflx_ic_ubc = {};
double* rho_ic = {};
double* rho_ic_ubc = {};
double* rho_incr = {};
double* theta_v_ic = {};
double* theta_v_ic_ubc = {};
double* vn_ie = {};
double* vn_ie_ubc = {};
double* vt = {};
double* w_concorr_c = {};
double* w_ubc = {};
};


struct t_nh_ref {
    int __f2dace_SA_w_ref_d_0_s_271 = {};
int __f2dace_SA_w_ref_d_1_s_272 = {};
int __f2dace_SA_w_ref_d_2_s_273 = {};
int __f2dace_SOA_w_ref_d_0_s_271 = {};
int __f2dace_SOA_w_ref_d_1_s_272 = {};
int __f2dace_SOA_w_ref_d_2_s_273 = {};
double* w_ref = {};
};


struct t_nh_metrics {
    int __f2dace_SA_bdy_mflx_e_blk_d_0_s_310 = {};
int __f2dace_SA_bdy_mflx_e_idx_d_0_s_309 = {};
int __f2dace_SA_ddqz_z_full_e_d_0_s_285 = {};
int __f2dace_SA_ddqz_z_full_e_d_1_s_286 = {};
int __f2dace_SA_ddqz_z_full_e_d_2_s_287 = {};
int __f2dace_SA_ddqz_z_half_d_0_s_288 = {};
int __f2dace_SA_ddqz_z_half_d_1_s_289 = {};
int __f2dace_SA_ddqz_z_half_d_2_s_290 = {};
int __f2dace_SA_ddxn_z_full_d_0_s_279 = {};
int __f2dace_SA_ddxn_z_full_d_1_s_280 = {};
int __f2dace_SA_ddxn_z_full_d_2_s_281 = {};
int __f2dace_SA_ddxt_z_full_d_0_s_282 = {};
int __f2dace_SA_ddxt_z_full_d_1_s_283 = {};
int __f2dace_SA_ddxt_z_full_d_2_s_284 = {};
int __f2dace_SA_deepatmo_divh_mc_d_0_s_311 = {};
int __f2dace_SA_deepatmo_divzl_mc_d_0_s_313 = {};
int __f2dace_SA_deepatmo_divzu_mc_d_0_s_312 = {};
int __f2dace_SA_exner_ref_mc_d_0_s_306 = {};
int __f2dace_SA_exner_ref_mc_d_1_s_307 = {};
int __f2dace_SA_exner_ref_mc_d_2_s_308 = {};
int __f2dace_SA_inv_ddqz_z_full_d_0_s_291 = {};
int __f2dace_SA_inv_ddqz_z_full_d_1_s_292 = {};
int __f2dace_SA_inv_ddqz_z_full_d_2_s_293 = {};
int __f2dace_SA_rayleigh_w_d_0_s_274 = {};
int __f2dace_SA_vwind_expl_wgt_d_0_s_275 = {};
int __f2dace_SA_vwind_expl_wgt_d_1_s_276 = {};
int __f2dace_SA_vwind_impl_wgt_d_0_s_277 = {};
int __f2dace_SA_vwind_impl_wgt_d_1_s_278 = {};
int __f2dace_SA_wgtfac_c_d_0_s_294 = {};
int __f2dace_SA_wgtfac_c_d_1_s_295 = {};
int __f2dace_SA_wgtfac_c_d_2_s_296 = {};
int __f2dace_SA_wgtfac_e_d_0_s_297 = {};
int __f2dace_SA_wgtfac_e_d_1_s_298 = {};
int __f2dace_SA_wgtfac_e_d_2_s_299 = {};
int __f2dace_SA_wgtfacq_c_d_0_s_300 = {};
int __f2dace_SA_wgtfacq_c_d_1_s_301 = {};
int __f2dace_SA_wgtfacq_c_d_2_s_302 = {};
int __f2dace_SA_wgtfacq_e_d_0_s_303 = {};
int __f2dace_SA_wgtfacq_e_d_1_s_304 = {};
int __f2dace_SA_wgtfacq_e_d_2_s_305 = {};
int __f2dace_SOA_bdy_mflx_e_blk_d_0_s_310 = {};
int __f2dace_SOA_bdy_mflx_e_idx_d_0_s_309 = {};
int __f2dace_SOA_ddqz_z_full_e_d_0_s_285 = {};
int __f2dace_SOA_ddqz_z_full_e_d_1_s_286 = {};
int __f2dace_SOA_ddqz_z_full_e_d_2_s_287 = {};
int __f2dace_SOA_ddqz_z_half_d_0_s_288 = {};
int __f2dace_SOA_ddqz_z_half_d_1_s_289 = {};
int __f2dace_SOA_ddqz_z_half_d_2_s_290 = {};
int __f2dace_SOA_ddxn_z_full_d_0_s_279 = {};
int __f2dace_SOA_ddxn_z_full_d_1_s_280 = {};
int __f2dace_SOA_ddxn_z_full_d_2_s_281 = {};
int __f2dace_SOA_ddxt_z_full_d_0_s_282 = {};
int __f2dace_SOA_ddxt_z_full_d_1_s_283 = {};
int __f2dace_SOA_ddxt_z_full_d_2_s_284 = {};
int __f2dace_SOA_deepatmo_divh_mc_d_0_s_311 = {};
int __f2dace_SOA_deepatmo_divzl_mc_d_0_s_313 = {};
int __f2dace_SOA_deepatmo_divzu_mc_d_0_s_312 = {};
int __f2dace_SOA_exner_ref_mc_d_0_s_306 = {};
int __f2dace_SOA_exner_ref_mc_d_1_s_307 = {};
int __f2dace_SOA_exner_ref_mc_d_2_s_308 = {};
int __f2dace_SOA_inv_ddqz_z_full_d_0_s_291 = {};
int __f2dace_SOA_inv_ddqz_z_full_d_1_s_292 = {};
int __f2dace_SOA_inv_ddqz_z_full_d_2_s_293 = {};
int __f2dace_SOA_rayleigh_w_d_0_s_274 = {};
int __f2dace_SOA_vwind_expl_wgt_d_0_s_275 = {};
int __f2dace_SOA_vwind_expl_wgt_d_1_s_276 = {};
int __f2dace_SOA_vwind_impl_wgt_d_0_s_277 = {};
int __f2dace_SOA_vwind_impl_wgt_d_1_s_278 = {};
int __f2dace_SOA_wgtfac_c_d_0_s_294 = {};
int __f2dace_SOA_wgtfac_c_d_1_s_295 = {};
int __f2dace_SOA_wgtfac_c_d_2_s_296 = {};
int __f2dace_SOA_wgtfac_e_d_0_s_297 = {};
int __f2dace_SOA_wgtfac_e_d_1_s_298 = {};
int __f2dace_SOA_wgtfac_e_d_2_s_299 = {};
int __f2dace_SOA_wgtfacq_c_d_0_s_300 = {};
int __f2dace_SOA_wgtfacq_c_d_1_s_301 = {};
int __f2dace_SOA_wgtfacq_c_d_2_s_302 = {};
int __f2dace_SOA_wgtfacq_e_d_0_s_303 = {};
int __f2dace_SOA_wgtfacq_e_d_1_s_304 = {};
int __f2dace_SOA_wgtfacq_e_d_2_s_305 = {};
int* bdy_mflx_e_blk = {};
int bdy_mflx_e_dim = {};
int* bdy_mflx_e_idx = {};
double* ddqz_z_full_e = {};
double* ddqz_z_half = {};
double* ddxn_z_full = {};
double* ddxt_z_full = {};
double* deepatmo_divh_mc = {};
double* deepatmo_divzl_mc = {};
double* deepatmo_divzu_mc = {};
double* exner_ref_mc = {};
double* inv_ddqz_z_full = {};
double* rayleigh_w = {};
double* vwind_expl_wgt = {};
double* vwind_impl_wgt = {};
double* wgtfac_c = {};
double* wgtfac_e = {};
double* wgtfacq_c = {};
double* wgtfacq_e = {};
};


struct t_nh_state {
    t_nh_diag* diag = {};
t_nh_metrics* metrics = {};
t_nh_ref* ref = {};
};


struct t_prepare_adv {
    
};


struct t_grid_cells {
    int __f2dace_SA_edge_blk_d_0_s_53 = {};
int __f2dace_SA_edge_blk_d_1_s_54 = {};
int __f2dace_SA_edge_blk_d_2_s_55 = {};
int __f2dace_SA_edge_idx_d_0_s_50 = {};
int __f2dace_SA_edge_idx_d_1_s_51 = {};
int __f2dace_SA_edge_idx_d_2_s_52 = {};
int __f2dace_SA_end_block_d_0_s_59 = {};
int __f2dace_SA_end_index_d_0_s_57 = {};
int __f2dace_SA_start_block_d_0_s_58 = {};
int __f2dace_SA_start_index_d_0_s_56 = {};
int __f2dace_SOA_edge_blk_d_0_s_53 = {};
int __f2dace_SOA_edge_blk_d_1_s_54 = {};
int __f2dace_SOA_edge_blk_d_2_s_55 = {};
int __f2dace_SOA_edge_idx_d_0_s_50 = {};
int __f2dace_SOA_edge_idx_d_1_s_51 = {};
int __f2dace_SOA_edge_idx_d_2_s_52 = {};
int __f2dace_SOA_end_block_d_0_s_59 = {};
int __f2dace_SOA_end_index_d_0_s_57 = {};
int __f2dace_SOA_start_block_d_0_s_58 = {};
int __f2dace_SOA_start_index_d_0_s_56 = {};
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
};


struct global_data_type {
    int divdamp_type = {};
int grf_intmethod_e = {};
double iau_wgt_dyn = {};
int is_iau_active = {};
int* kstart_dd3d = {};
int* kstart_moist = {};
int l_limited_area = {};
int* ndyn_substeps_var = {};
int* nflatlev = {};
int nproma = {};
int* nrdmax = {};
int rayleigh_type = {};
int timer_solve_nh_edgecomp = {};
int timer_solve_nh_vimpl = {};
int timers_level = {};
};


struct t_nh_prog {
    int __f2dace_SA_exner_d_0_s_201 = {};
int __f2dace_SA_exner_d_1_s_202 = {};
int __f2dace_SA_exner_d_2_s_203 = {};
int __f2dace_SA_rho_d_0_s_198 = {};
int __f2dace_SA_rho_d_1_s_199 = {};
int __f2dace_SA_rho_d_2_s_200 = {};
int __f2dace_SA_theta_v_d_0_s_204 = {};
int __f2dace_SA_theta_v_d_1_s_205 = {};
int __f2dace_SA_theta_v_d_2_s_206 = {};
int __f2dace_SA_vn_d_0_s_195 = {};
int __f2dace_SA_vn_d_1_s_196 = {};
int __f2dace_SA_vn_d_2_s_197 = {};
int __f2dace_SA_w_d_0_s_192 = {};
int __f2dace_SA_w_d_1_s_193 = {};
int __f2dace_SA_w_d_2_s_194 = {};
int __f2dace_SOA_exner_d_0_s_201 = {};
int __f2dace_SOA_exner_d_1_s_202 = {};
int __f2dace_SOA_exner_d_2_s_203 = {};
int __f2dace_SOA_rho_d_0_s_198 = {};
int __f2dace_SOA_rho_d_1_s_199 = {};
int __f2dace_SOA_rho_d_2_s_200 = {};
int __f2dace_SOA_theta_v_d_0_s_204 = {};
int __f2dace_SOA_theta_v_d_1_s_205 = {};
int __f2dace_SOA_theta_v_d_2_s_206 = {};
int __f2dace_SOA_vn_d_0_s_195 = {};
int __f2dace_SOA_vn_d_1_s_196 = {};
int __f2dace_SOA_vn_d_2_s_197 = {};
int __f2dace_SOA_w_d_0_s_192 = {};
int __f2dace_SOA_w_d_1_s_193 = {};
int __f2dace_SOA_w_d_2_s_194 = {};
double* exner = {};
double* rho = {};
double* theta_v = {};
double* vn = {};
double* w = {};
};




struct solve_nh_predictor_post_state_t;  // Forward declaration.

DACE_EXPORTED solve_nh_predictor_post_state_t *__dace_init_solve_nh_predictor_post(double * __restrict__ bdy_divdamp, double * __restrict__ enh_divdamp_fac, global_data_type* global_data, t_int_state* p_int, t_nh_state* p_nh, t_nh_prog* p_nh_prog_nnew, t_nh_prog* p_nh_prog_nnow, t_patch* p_patch, t_prepare_adv* prep_adv, double * __restrict__ scal_divdamp, double * __restrict__ z_alpha, double * __restrict__ z_beta, double * __restrict__ z_contr_w_fl_l, double * __restrict__ z_dexner_dz_c, double * __restrict__ z_dwdz_dd, double * __restrict__ z_exner_ex_pr, double * __restrict__ z_exner_expl, double * __restrict__ z_exner_ic, double * __restrict__ z_flxdiv_mass, double * __restrict__ z_flxdiv_theta, double * __restrict__ z_grad_rth, double * __restrict__ z_graddiv2_vn, double * __restrict__ z_graddiv_vn, double * __restrict__ z_gradh_exner, double * __restrict__ z_hydro_corr, double * __restrict__ z_kin_hor_e, double * __restrict__ z_mflx_top, double * __restrict__ z_q, double * __restrict__ z_raylfac, double * __restrict__ z_rho_e, double * __restrict__ z_rho_expl, double * __restrict__ z_rho_v, double * __restrict__ z_rth_pr, double * __restrict__ z_th_ddz_exner_c, double * __restrict__ z_theta_v_e, double * __restrict__ z_theta_v_fl_e, double * __restrict__ z_theta_v_pr_ic, double * __restrict__ z_theta_v_v, double * __restrict__ z_vn_avg, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_mc, double * __restrict__ z_w_concorr_me, double * __restrict__ z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr, double bqdr, double df32, double df42, double distv_bary_1, double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime, double dz32, double dz42, double dzlin, double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init, int l_recompute, int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2, int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start, double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg, double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1, double z_w_backtraj, double zf);
DACE_EXPORTED int __dace_exit_solve_nh_predictor_post(solve_nh_predictor_post_state_t *__state);
DACE_EXPORTED void __program_solve_nh_predictor_post(solve_nh_predictor_post_state_t *__state, double * __restrict__ bdy_divdamp, double * __restrict__ enh_divdamp_fac, global_data_type* global_data, t_int_state* p_int, t_nh_state* p_nh, t_nh_prog* p_nh_prog_nnew, t_nh_prog* p_nh_prog_nnow, t_patch* p_patch, t_prepare_adv* prep_adv, double * __restrict__ scal_divdamp, double * __restrict__ z_alpha, double * __restrict__ z_beta, double * __restrict__ z_contr_w_fl_l, double * __restrict__ z_dexner_dz_c, double * __restrict__ z_dwdz_dd, double * __restrict__ z_exner_ex_pr, double * __restrict__ z_exner_expl, double * __restrict__ z_exner_ic, double * __restrict__ z_flxdiv_mass, double * __restrict__ z_flxdiv_theta, double * __restrict__ z_grad_rth, double * __restrict__ z_graddiv2_vn, double * __restrict__ z_graddiv_vn, double * __restrict__ z_gradh_exner, double * __restrict__ z_hydro_corr, double * __restrict__ z_kin_hor_e, double * __restrict__ z_mflx_top, double * __restrict__ z_q, double * __restrict__ z_raylfac, double * __restrict__ z_rho_e, double * __restrict__ z_rho_expl, double * __restrict__ z_rho_v, double * __restrict__ z_rth_pr, double * __restrict__ z_th_ddz_exner_c, double * __restrict__ z_theta_v_e, double * __restrict__ z_theta_v_fl_e, double * __restrict__ z_theta_v_pr_ic, double * __restrict__ z_theta_v_v, double * __restrict__ z_vn_avg, double * __restrict__ z_vt_ie, double * __restrict__ z_w_concorr_mc, double * __restrict__ z_w_concorr_me, double * __restrict__ z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr, double bqdr, double df32, double df42, double distv_bary_1, double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime, double dz32, double dz42, double dzlin, double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init, int l_recompute, int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2, int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start, double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg, double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1, double z_w_backtraj, double zf);

#endif // __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__
