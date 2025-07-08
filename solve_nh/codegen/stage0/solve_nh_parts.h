#include <dace/dace.h>

namespace corrector_post {
#ifndef __DACE_CODEGEN_SOLVE_NH_CORRECTOR_POST__
#define __DACE_CODEGEN_SOLVE_NH_CORRECTOR_POST__

struct global_data_type {
  int grf_intmethod_e = {};
  double iau_wgt_dyn = {};
  int is_iau_active = {};
  int itime_scheme = {};
  int *kstart_dd3d = {};
  int *kstart_moist = {};
  int l_limited_area = {};
  int *ndyn_substeps_var = {};
  int *nflatlev = {};
  int nproma = {};
  int *nrdmax = {};
  int rayleigh_type = {};
  int timer_solve_nh_edgecomp = {};
  int timer_solve_nh_vimpl = {};
  int timers_level = {};
};

struct t_grid_edges {
  int __f2dace_SA_end_block_d_0_s_67 = {};
  int __f2dace_SA_end_index_d_0_s_65 = {};
  int __f2dace_SA_quad_blk_d_0_s_59 = {};
  int __f2dace_SA_quad_blk_d_1_s_60 = {};
  int __f2dace_SA_quad_blk_d_2_s_61 = {};
  int __f2dace_SA_quad_idx_d_0_s_56 = {};
  int __f2dace_SA_quad_idx_d_1_s_57 = {};
  int __f2dace_SA_quad_idx_d_2_s_58 = {};
  int __f2dace_SA_refin_ctrl_d_0_s_62 = {};
  int __f2dace_SA_refin_ctrl_d_1_s_63 = {};
  int __f2dace_SA_start_block_d_0_s_66 = {};
  int __f2dace_SA_start_index_d_0_s_64 = {};
  int __f2dace_SOA_end_block_d_0_s_67 = {};
  int __f2dace_SOA_end_index_d_0_s_65 = {};
  int __f2dace_SOA_quad_blk_d_0_s_59 = {};
  int __f2dace_SOA_quad_blk_d_1_s_60 = {};
  int __f2dace_SOA_quad_blk_d_2_s_61 = {};
  int __f2dace_SOA_quad_idx_d_0_s_56 = {};
  int __f2dace_SOA_quad_idx_d_1_s_57 = {};
  int __f2dace_SOA_quad_idx_d_2_s_58 = {};
  int __f2dace_SOA_refin_ctrl_d_0_s_62 = {};
  int __f2dace_SOA_refin_ctrl_d_1_s_63 = {};
  int __f2dace_SOA_start_block_d_0_s_66 = {};
  int __f2dace_SOA_start_index_d_0_s_64 = {};
  int *end_block = {};
  int *end_index = {};
  int *quad_blk = {};
  int *quad_idx = {};
  int *refin_ctrl = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_nh_diag {
  int __f2dace_SA_ddt_exner_phy_d_0_s_235 = {};
  int __f2dace_SA_ddt_exner_phy_d_1_s_236 = {};
  int __f2dace_SA_ddt_exner_phy_d_2_s_237 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_0_s_247 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_1_s_248 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_2_s_249 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_3_s_250 = {};
  int __f2dace_SA_exner_dyn_incr_d_0_s_238 = {};
  int __f2dace_SA_exner_dyn_incr_d_1_s_239 = {};
  int __f2dace_SA_exner_dyn_incr_d_2_s_240 = {};
  int __f2dace_SA_exner_incr_d_0_s_226 = {};
  int __f2dace_SA_exner_incr_d_1_s_227 = {};
  int __f2dace_SA_exner_incr_d_2_s_228 = {};
  int __f2dace_SA_exner_pr_d_0_s_193 = {};
  int __f2dace_SA_exner_pr_d_1_s_194 = {};
  int __f2dace_SA_exner_pr_d_2_s_195 = {};
  int __f2dace_SA_grf_bdy_mflx_d_0_s_205 = {};
  int __f2dace_SA_grf_bdy_mflx_d_1_s_206 = {};
  int __f2dace_SA_grf_bdy_mflx_d_2_s_207 = {};
  int __f2dace_SA_mass_fl_e_d_0_s_196 = {};
  int __f2dace_SA_mass_fl_e_d_1_s_197 = {};
  int __f2dace_SA_mass_fl_e_d_2_s_198 = {};
  int __f2dace_SA_mass_fl_e_sv_d_0_s_244 = {};
  int __f2dace_SA_mass_fl_e_sv_d_1_s_245 = {};
  int __f2dace_SA_mass_fl_e_sv_d_2_s_246 = {};
  int __f2dace_SA_mflx_ic_int_d_0_s_220 = {};
  int __f2dace_SA_mflx_ic_int_d_1_s_221 = {};
  int __f2dace_SA_mflx_ic_int_d_2_s_222 = {};
  int __f2dace_SA_mflx_ic_ubc_d_0_s_223 = {};
  int __f2dace_SA_mflx_ic_ubc_d_1_s_224 = {};
  int __f2dace_SA_mflx_ic_ubc_d_2_s_225 = {};
  int __f2dace_SA_rho_ic_d_0_s_199 = {};
  int __f2dace_SA_rho_ic_d_1_s_200 = {};
  int __f2dace_SA_rho_ic_d_2_s_201 = {};
  int __f2dace_SA_rho_ic_int_d_0_s_217 = {};
  int __f2dace_SA_rho_ic_int_d_1_s_218 = {};
  int __f2dace_SA_rho_ic_int_d_2_s_219 = {};
  int __f2dace_SA_rho_incr_d_0_s_229 = {};
  int __f2dace_SA_rho_incr_d_1_s_230 = {};
  int __f2dace_SA_rho_incr_d_2_s_231 = {};
  int __f2dace_SA_theta_v_ic_d_0_s_202 = {};
  int __f2dace_SA_theta_v_ic_d_1_s_203 = {};
  int __f2dace_SA_theta_v_ic_d_2_s_204 = {};
  int __f2dace_SA_theta_v_ic_int_d_0_s_214 = {};
  int __f2dace_SA_theta_v_ic_int_d_1_s_215 = {};
  int __f2dace_SA_theta_v_ic_int_d_2_s_216 = {};
  int __f2dace_SA_vt_d_0_s_232 = {};
  int __f2dace_SA_vt_d_1_s_233 = {};
  int __f2dace_SA_vt_d_2_s_234 = {};
  int __f2dace_SA_w_concorr_c_d_0_s_241 = {};
  int __f2dace_SA_w_concorr_c_d_1_s_242 = {};
  int __f2dace_SA_w_concorr_c_d_2_s_243 = {};
  int __f2dace_SA_w_int_d_0_s_208 = {};
  int __f2dace_SA_w_int_d_1_s_209 = {};
  int __f2dace_SA_w_int_d_2_s_210 = {};
  int __f2dace_SA_w_ubc_d_0_s_211 = {};
  int __f2dace_SA_w_ubc_d_1_s_212 = {};
  int __f2dace_SA_w_ubc_d_2_s_213 = {};
  int __f2dace_SOA_ddt_exner_phy_d_0_s_235 = {};
  int __f2dace_SOA_ddt_exner_phy_d_1_s_236 = {};
  int __f2dace_SOA_ddt_exner_phy_d_2_s_237 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_0_s_247 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_1_s_248 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_2_s_249 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_3_s_250 = {};
  int __f2dace_SOA_exner_dyn_incr_d_0_s_238 = {};
  int __f2dace_SOA_exner_dyn_incr_d_1_s_239 = {};
  int __f2dace_SOA_exner_dyn_incr_d_2_s_240 = {};
  int __f2dace_SOA_exner_incr_d_0_s_226 = {};
  int __f2dace_SOA_exner_incr_d_1_s_227 = {};
  int __f2dace_SOA_exner_incr_d_2_s_228 = {};
  int __f2dace_SOA_exner_pr_d_0_s_193 = {};
  int __f2dace_SOA_exner_pr_d_1_s_194 = {};
  int __f2dace_SOA_exner_pr_d_2_s_195 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_0_s_205 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_1_s_206 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_2_s_207 = {};
  int __f2dace_SOA_mass_fl_e_d_0_s_196 = {};
  int __f2dace_SOA_mass_fl_e_d_1_s_197 = {};
  int __f2dace_SOA_mass_fl_e_d_2_s_198 = {};
  int __f2dace_SOA_mass_fl_e_sv_d_0_s_244 = {};
  int __f2dace_SOA_mass_fl_e_sv_d_1_s_245 = {};
  int __f2dace_SOA_mass_fl_e_sv_d_2_s_246 = {};
  int __f2dace_SOA_mflx_ic_int_d_0_s_220 = {};
  int __f2dace_SOA_mflx_ic_int_d_1_s_221 = {};
  int __f2dace_SOA_mflx_ic_int_d_2_s_222 = {};
  int __f2dace_SOA_mflx_ic_ubc_d_0_s_223 = {};
  int __f2dace_SOA_mflx_ic_ubc_d_1_s_224 = {};
  int __f2dace_SOA_mflx_ic_ubc_d_2_s_225 = {};
  int __f2dace_SOA_rho_ic_d_0_s_199 = {};
  int __f2dace_SOA_rho_ic_d_1_s_200 = {};
  int __f2dace_SOA_rho_ic_d_2_s_201 = {};
  int __f2dace_SOA_rho_ic_int_d_0_s_217 = {};
  int __f2dace_SOA_rho_ic_int_d_1_s_218 = {};
  int __f2dace_SOA_rho_ic_int_d_2_s_219 = {};
  int __f2dace_SOA_rho_incr_d_0_s_229 = {};
  int __f2dace_SOA_rho_incr_d_1_s_230 = {};
  int __f2dace_SOA_rho_incr_d_2_s_231 = {};
  int __f2dace_SOA_theta_v_ic_d_0_s_202 = {};
  int __f2dace_SOA_theta_v_ic_d_1_s_203 = {};
  int __f2dace_SOA_theta_v_ic_d_2_s_204 = {};
  int __f2dace_SOA_theta_v_ic_int_d_0_s_214 = {};
  int __f2dace_SOA_theta_v_ic_int_d_1_s_215 = {};
  int __f2dace_SOA_theta_v_ic_int_d_2_s_216 = {};
  int __f2dace_SOA_vt_d_0_s_232 = {};
  int __f2dace_SOA_vt_d_1_s_233 = {};
  int __f2dace_SOA_vt_d_2_s_234 = {};
  int __f2dace_SOA_w_concorr_c_d_0_s_241 = {};
  int __f2dace_SOA_w_concorr_c_d_1_s_242 = {};
  int __f2dace_SOA_w_concorr_c_d_2_s_243 = {};
  int __f2dace_SOA_w_int_d_0_s_208 = {};
  int __f2dace_SOA_w_int_d_1_s_209 = {};
  int __f2dace_SOA_w_int_d_2_s_210 = {};
  int __f2dace_SOA_w_ubc_d_0_s_211 = {};
  int __f2dace_SOA_w_ubc_d_1_s_212 = {};
  int __f2dace_SOA_w_ubc_d_2_s_213 = {};
  double *ddt_exner_phy = {};
  double *ddt_w_adv_pc = {};
  double *exner_dyn_incr = {};
  double *exner_incr = {};
  double *exner_pr = {};
  double *grf_bdy_mflx = {};
  double *mass_fl_e = {};
  double *mass_fl_e_sv = {};
  double *mflx_ic_int = {};
  double *mflx_ic_ubc = {};
  double *rho_ic = {};
  double *rho_ic_int = {};
  double *rho_incr = {};
  double *theta_v_ic = {};
  double *theta_v_ic_int = {};
  double *vt = {};
  double *w_concorr_c = {};
  double *w_int = {};
  double *w_ubc = {};
};

struct t_nh_ref {
  int __f2dace_SA_w_ref_d_0_s_251 = {};
  int __f2dace_SA_w_ref_d_1_s_252 = {};
  int __f2dace_SA_w_ref_d_2_s_253 = {};
  int __f2dace_SOA_w_ref_d_0_s_251 = {};
  int __f2dace_SOA_w_ref_d_1_s_252 = {};
  int __f2dace_SOA_w_ref_d_2_s_253 = {};
  double *w_ref = {};
};

struct t_nh_metrics {
  int __f2dace_SA_bdy_mflx_e_blk_d_0_s_284 = {};
  int __f2dace_SA_bdy_mflx_e_idx_d_0_s_283 = {};
  int __f2dace_SA_ddqz_z_full_e_d_0_s_265 = {};
  int __f2dace_SA_ddqz_z_full_e_d_1_s_266 = {};
  int __f2dace_SA_ddqz_z_full_e_d_2_s_267 = {};
  int __f2dace_SA_ddqz_z_half_d_0_s_268 = {};
  int __f2dace_SA_ddqz_z_half_d_1_s_269 = {};
  int __f2dace_SA_ddqz_z_half_d_2_s_270 = {};
  int __f2dace_SA_ddxn_z_full_d_0_s_259 = {};
  int __f2dace_SA_ddxn_z_full_d_1_s_260 = {};
  int __f2dace_SA_ddxn_z_full_d_2_s_261 = {};
  int __f2dace_SA_ddxt_z_full_d_0_s_262 = {};
  int __f2dace_SA_ddxt_z_full_d_1_s_263 = {};
  int __f2dace_SA_ddxt_z_full_d_2_s_264 = {};
  int __f2dace_SA_deepatmo_divh_mc_d_0_s_285 = {};
  int __f2dace_SA_deepatmo_divzl_mc_d_0_s_287 = {};
  int __f2dace_SA_deepatmo_divzu_mc_d_0_s_286 = {};
  int __f2dace_SA_exner_ref_mc_d_0_s_280 = {};
  int __f2dace_SA_exner_ref_mc_d_1_s_281 = {};
  int __f2dace_SA_exner_ref_mc_d_2_s_282 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_0_s_271 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_1_s_272 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_2_s_273 = {};
  int __f2dace_SA_rayleigh_w_d_0_s_254 = {};
  int __f2dace_SA_vwind_expl_wgt_d_0_s_255 = {};
  int __f2dace_SA_vwind_expl_wgt_d_1_s_256 = {};
  int __f2dace_SA_vwind_impl_wgt_d_0_s_257 = {};
  int __f2dace_SA_vwind_impl_wgt_d_1_s_258 = {};
  int __f2dace_SA_wgtfac_c_d_0_s_274 = {};
  int __f2dace_SA_wgtfac_c_d_1_s_275 = {};
  int __f2dace_SA_wgtfac_c_d_2_s_276 = {};
  int __f2dace_SA_wgtfacq_c_d_0_s_277 = {};
  int __f2dace_SA_wgtfacq_c_d_1_s_278 = {};
  int __f2dace_SA_wgtfacq_c_d_2_s_279 = {};
  int __f2dace_SOA_bdy_mflx_e_blk_d_0_s_284 = {};
  int __f2dace_SOA_bdy_mflx_e_idx_d_0_s_283 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_0_s_265 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_1_s_266 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_2_s_267 = {};
  int __f2dace_SOA_ddqz_z_half_d_0_s_268 = {};
  int __f2dace_SOA_ddqz_z_half_d_1_s_269 = {};
  int __f2dace_SOA_ddqz_z_half_d_2_s_270 = {};
  int __f2dace_SOA_ddxn_z_full_d_0_s_259 = {};
  int __f2dace_SOA_ddxn_z_full_d_1_s_260 = {};
  int __f2dace_SOA_ddxn_z_full_d_2_s_261 = {};
  int __f2dace_SOA_ddxt_z_full_d_0_s_262 = {};
  int __f2dace_SOA_ddxt_z_full_d_1_s_263 = {};
  int __f2dace_SOA_ddxt_z_full_d_2_s_264 = {};
  int __f2dace_SOA_deepatmo_divh_mc_d_0_s_285 = {};
  int __f2dace_SOA_deepatmo_divzl_mc_d_0_s_287 = {};
  int __f2dace_SOA_deepatmo_divzu_mc_d_0_s_286 = {};
  int __f2dace_SOA_exner_ref_mc_d_0_s_280 = {};
  int __f2dace_SOA_exner_ref_mc_d_1_s_281 = {};
  int __f2dace_SOA_exner_ref_mc_d_2_s_282 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_0_s_271 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_1_s_272 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_2_s_273 = {};
  int __f2dace_SOA_rayleigh_w_d_0_s_254 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_0_s_255 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_1_s_256 = {};
  int __f2dace_SOA_vwind_impl_wgt_d_0_s_257 = {};
  int __f2dace_SOA_vwind_impl_wgt_d_1_s_258 = {};
  int __f2dace_SOA_wgtfac_c_d_0_s_274 = {};
  int __f2dace_SOA_wgtfac_c_d_1_s_275 = {};
  int __f2dace_SOA_wgtfac_c_d_2_s_276 = {};
  int __f2dace_SOA_wgtfacq_c_d_0_s_277 = {};
  int __f2dace_SOA_wgtfacq_c_d_1_s_278 = {};
  int __f2dace_SOA_wgtfacq_c_d_2_s_279 = {};
  int *bdy_mflx_e_blk = {};
  int bdy_mflx_e_dim = {};
  int *bdy_mflx_e_idx = {};
  double *ddqz_z_full_e = {};
  double *ddqz_z_half = {};
  double *ddxn_z_full = {};
  double *ddxt_z_full = {};
  double *deepatmo_divh_mc = {};
  double *deepatmo_divzl_mc = {};
  double *deepatmo_divzu_mc = {};
  double *exner_ref_mc = {};
  double *inv_ddqz_z_full = {};
  double *rayleigh_w = {};
  double *vwind_expl_wgt = {};
  double *vwind_impl_wgt = {};
  double *wgtfac_c = {};
  double *wgtfacq_c = {};
};

struct t_nh_state {
  t_nh_diag *diag = {};
  t_nh_metrics *metrics = {};
  t_nh_ref *ref = {};
};

struct t_grid_cells {
  int __f2dace_SA_edge_blk_d_0_s_49 = {};
  int __f2dace_SA_edge_blk_d_1_s_50 = {};
  int __f2dace_SA_edge_blk_d_2_s_51 = {};
  int __f2dace_SA_edge_idx_d_0_s_46 = {};
  int __f2dace_SA_edge_idx_d_1_s_47 = {};
  int __f2dace_SA_edge_idx_d_2_s_48 = {};
  int __f2dace_SA_end_block_d_0_s_55 = {};
  int __f2dace_SA_end_index_d_0_s_53 = {};
  int __f2dace_SA_start_block_d_0_s_54 = {};
  int __f2dace_SA_start_index_d_0_s_52 = {};
  int __f2dace_SOA_edge_blk_d_0_s_49 = {};
  int __f2dace_SOA_edge_blk_d_1_s_50 = {};
  int __f2dace_SOA_edge_blk_d_2_s_51 = {};
  int __f2dace_SOA_edge_idx_d_0_s_46 = {};
  int __f2dace_SOA_edge_idx_d_1_s_47 = {};
  int __f2dace_SOA_edge_idx_d_2_s_48 = {};
  int __f2dace_SOA_end_block_d_0_s_55 = {};
  int __f2dace_SOA_end_index_d_0_s_53 = {};
  int __f2dace_SOA_start_block_d_0_s_54 = {};
  int __f2dace_SOA_start_index_d_0_s_52 = {};
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_block = {};
  int *end_index = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_nh_prog {
  int __f2dace_SA_exner_d_0_s_187 = {};
  int __f2dace_SA_exner_d_1_s_188 = {};
  int __f2dace_SA_exner_d_2_s_189 = {};
  int __f2dace_SA_rho_d_0_s_184 = {};
  int __f2dace_SA_rho_d_1_s_185 = {};
  int __f2dace_SA_rho_d_2_s_186 = {};
  int __f2dace_SA_theta_v_d_0_s_190 = {};
  int __f2dace_SA_theta_v_d_1_s_191 = {};
  int __f2dace_SA_theta_v_d_2_s_192 = {};
  int __f2dace_SA_vn_d_0_s_181 = {};
  int __f2dace_SA_vn_d_1_s_182 = {};
  int __f2dace_SA_vn_d_2_s_183 = {};
  int __f2dace_SA_w_d_0_s_178 = {};
  int __f2dace_SA_w_d_1_s_179 = {};
  int __f2dace_SA_w_d_2_s_180 = {};
  int __f2dace_SOA_exner_d_0_s_187 = {};
  int __f2dace_SOA_exner_d_1_s_188 = {};
  int __f2dace_SOA_exner_d_2_s_189 = {};
  int __f2dace_SOA_rho_d_0_s_184 = {};
  int __f2dace_SOA_rho_d_1_s_185 = {};
  int __f2dace_SOA_rho_d_2_s_186 = {};
  int __f2dace_SOA_theta_v_d_0_s_190 = {};
  int __f2dace_SOA_theta_v_d_1_s_191 = {};
  int __f2dace_SOA_theta_v_d_2_s_192 = {};
  int __f2dace_SOA_vn_d_0_s_181 = {};
  int __f2dace_SOA_vn_d_1_s_182 = {};
  int __f2dace_SOA_vn_d_2_s_183 = {};
  int __f2dace_SOA_w_d_0_s_178 = {};
  int __f2dace_SOA_w_d_1_s_179 = {};
  int __f2dace_SOA_w_d_2_s_180 = {};
  double *exner = {};
  double *rho = {};
  double *theta_v = {};
  double *vn = {};
  double *w = {};
};

struct t_int_state {
  int __f2dace_SA_e_bln_c_s_d_0_s_12 = {};
  int __f2dace_SA_e_bln_c_s_d_1_s_13 = {};
  int __f2dace_SA_e_bln_c_s_d_2_s_14 = {};
  int __f2dace_SA_e_flx_avg_d_0_s_15 = {};
  int __f2dace_SA_e_flx_avg_d_1_s_16 = {};
  int __f2dace_SA_e_flx_avg_d_2_s_17 = {};
  int __f2dace_SA_geofac_div_d_0_s_21 = {};
  int __f2dace_SA_geofac_div_d_1_s_22 = {};
  int __f2dace_SA_geofac_div_d_2_s_23 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_0_s_18 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_1_s_19 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_2_s_20 = {};
  int __f2dace_SOA_e_bln_c_s_d_0_s_12 = {};
  int __f2dace_SOA_e_bln_c_s_d_1_s_13 = {};
  int __f2dace_SOA_e_bln_c_s_d_2_s_14 = {};
  int __f2dace_SOA_e_flx_avg_d_0_s_15 = {};
  int __f2dace_SOA_e_flx_avg_d_1_s_16 = {};
  int __f2dace_SOA_e_flx_avg_d_2_s_17 = {};
  int __f2dace_SOA_geofac_div_d_0_s_21 = {};
  int __f2dace_SOA_geofac_div_d_1_s_22 = {};
  int __f2dace_SOA_geofac_div_d_2_s_23 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_18 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_19 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_20 = {};
  double *e_bln_c_s = {};
  double *e_flx_avg = {};
  double *geofac_div = {};
  double *rbf_vec_coeff_e = {};
};

struct t_prepare_adv {
  int __f2dace_SA_mass_flx_ic_d_0_s_303 = {};
  int __f2dace_SA_mass_flx_ic_d_1_s_304 = {};
  int __f2dace_SA_mass_flx_ic_d_2_s_305 = {};
  int __f2dace_SA_mass_flx_me_d_0_s_300 = {};
  int __f2dace_SA_mass_flx_me_d_1_s_301 = {};
  int __f2dace_SA_mass_flx_me_d_2_s_302 = {};
  int __f2dace_SA_vn_traj_d_0_s_309 = {};
  int __f2dace_SA_vn_traj_d_1_s_310 = {};
  int __f2dace_SA_vn_traj_d_2_s_311 = {};
  int __f2dace_SA_vol_flx_ic_d_0_s_306 = {};
  int __f2dace_SA_vol_flx_ic_d_1_s_307 = {};
  int __f2dace_SA_vol_flx_ic_d_2_s_308 = {};
  int __f2dace_SOA_mass_flx_ic_d_0_s_303 = {};
  int __f2dace_SOA_mass_flx_ic_d_1_s_304 = {};
  int __f2dace_SOA_mass_flx_ic_d_2_s_305 = {};
  int __f2dace_SOA_mass_flx_me_d_0_s_300 = {};
  int __f2dace_SOA_mass_flx_me_d_1_s_301 = {};
  int __f2dace_SOA_mass_flx_me_d_2_s_302 = {};
  int __f2dace_SOA_vn_traj_d_0_s_309 = {};
  int __f2dace_SOA_vn_traj_d_1_s_310 = {};
  int __f2dace_SOA_vn_traj_d_2_s_311 = {};
  int __f2dace_SOA_vol_flx_ic_d_0_s_306 = {};
  int __f2dace_SOA_vol_flx_ic_d_1_s_307 = {};
  int __f2dace_SOA_vol_flx_ic_d_2_s_308 = {};
  double *mass_flx_ic = {};
  double *mass_flx_me = {};
  double *vn_traj = {};
  double *vol_flx_ic = {};
};

struct t_patch {
  t_grid_cells *cells = {};
  t_grid_edges *edges = {};
  int id = {};
  int nblks_c = {};
  int nblks_e = {};
  int nblks_v = {};
  int nlev = {};
  int nlevp1 = {};
};

struct solve_nh_corrector_post_state_t; // Forward declaration.

DACE_EXPORTED solve_nh_corrector_post_state_t *
__dace_init_solve_nh_corrector_post(
    double *bdy_divdamp, double *enh_divdamp_fac, global_data_type *global_data,
    t_int_state *p_int, t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew,
    t_nh_prog *p_nh_prog_nnow, t_patch *p_patch, t_prepare_adv *prep_adv,
    double *scal_divdamp, double *z_alpha, double *z_beta,
    double *z_contr_w_fl_l, double *z_dexner_dz_c, double *z_dwdz_dd,
    double *z_exner_ex_pr, double *z_exner_expl, double *z_exner_ic,
    double *z_flxdiv_mass, double *z_flxdiv_theta, double *z_grad_rth,
    double *z_graddiv2_vn, double *z_graddiv_vn, double *z_gradh_exner,
    double *z_hydro_corr, double *z_kin_hor_e, double *z_mflx_top, double *z_q,
    double *z_raylfac, double *z_rho_e, double *z_rho_expl, double *z_rho_v,
    double *z_rth_pr, double *z_th_ddz_exner_c, double *z_theta_v_e,
    double *z_theta_v_fl_e, double *z_theta_v_pr_ic, double *z_theta_v_v,
    double *z_vn_avg, double *z_vt_ie, double *z_w_concorr_mc,
    double *z_w_concorr_me, double *z_w_expl, int __f2dace_OPTIONAL_lacc,
    double alin, double aqdr, double bqdr, double df32, double df42,
    double distv_bary_1, double distv_bary_2, double dt_linintp_ubc,
    double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift,
    double dthalf, double dtime, double dz32, double dz42, double dzlin,
    double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx,
    int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg,
    int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init,
    int l_recompute, int l_vert_nested, int lacc, int lclean_mflx,
    int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp,
    int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp,
    int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2,
    int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end,
    int rl_start, double scal_divdamp_o2, double wgt_nnew_rth,
    double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a,
    double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau,
    double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn,
    double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma,
    double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg,
    double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);
DACE_EXPORTED int
__dace_exit_solve_nh_corrector_post(solve_nh_corrector_post_state_t *__state);
DACE_EXPORTED void __program_solve_nh_corrector_post(
    solve_nh_corrector_post_state_t *__state, double *bdy_divdamp,
    double *enh_divdamp_fac, global_data_type *global_data, t_int_state *p_int,
    t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew, t_nh_prog *p_nh_prog_nnow,
    t_patch *p_patch, t_prepare_adv *prep_adv, double *scal_divdamp,
    double *z_alpha, double *z_beta, double *z_contr_w_fl_l,
    double *z_dexner_dz_c, double *z_dwdz_dd, double *z_exner_ex_pr,
    double *z_exner_expl, double *z_exner_ic, double *z_flxdiv_mass,
    double *z_flxdiv_theta, double *z_grad_rth, double *z_graddiv2_vn,
    double *z_graddiv_vn, double *z_gradh_exner, double *z_hydro_corr,
    double *z_kin_hor_e, double *z_mflx_top, double *z_q, double *z_raylfac,
    double *z_rho_e, double *z_rho_expl, double *z_rho_v, double *z_rth_pr,
    double *z_th_ddz_exner_c, double *z_theta_v_e, double *z_theta_v_fl_e,
    double *z_theta_v_pr_ic, double *z_theta_v_v, double *z_vn_avg,
    double *z_vt_ie, double *z_w_concorr_mc, double *z_w_concorr_me,
    double *z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr,
    double bqdr, double df32, double df42, double distv_bary_1,
    double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew,
    double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime,
    double dz32, double dz42, double dzlin, double dzqdr, int i_endblk,
    int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift,
    int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks,
    int jstep, int l_child_vertnest, int l_init, int l_recompute,
    int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx,
    int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev,
    int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp,
    int nshift, int nshift_total, int ntl1, int ntl2, int nvar,
    double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start,
    double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel,
    double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b,
    double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc,
    double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr,
    double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1,
    double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1,
    double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);

#endif // __DACE_CODEGEN_SOLVE_NH_CORRECTOR_POST__
} // namespace corrector_post
#include <dace/dace.h>

namespace corrector_pre {
#ifndef __DACE_CODEGEN_SOLVE_NH_CORRECTOR_PRE__
#define __DACE_CODEGEN_SOLVE_NH_CORRECTOR_PRE__

struct global_data_type {
  double divdamp_fac = {};
  double divdamp_fac_o2 = {};
  int divdamp_order = {};
  int divdamp_type = {};
  int i_am_accel_node = {};
  double iau_wgt_dyn = {};
  int is_iau_active = {};
  int itime_scheme = {};
  int *kstart_dd3d = {};
  int l_limited_area = {};
  int ldeepatmo = {};
  int lextra_diffu = {};
  int lvert_nest = {};
  int *nflatlev = {};
  int nproma = {};
  int *nrdmax = {};
  int rayleigh_type = {};
  int timer_intp = {};
  int timer_solve_nh_cellcomp = {};
  int timer_solve_nh_veltend = {};
  int timer_solve_nh_vnupd = {};
  int timers_level = {};
};

struct t_grid_edges {
  int __f2dace_SA_area_edge_d_0_s_186 = {};
  int __f2dace_SA_area_edge_d_1_s_187 = {};
  int __f2dace_SA_cell_blk_d_0_s_165 = {};
  int __f2dace_SA_cell_blk_d_1_s_166 = {};
  int __f2dace_SA_cell_blk_d_2_s_167 = {};
  int __f2dace_SA_cell_idx_d_0_s_162 = {};
  int __f2dace_SA_cell_idx_d_1_s_163 = {};
  int __f2dace_SA_cell_idx_d_2_s_164 = {};
  int __f2dace_SA_end_block_d_0_s_197 = {};
  int __f2dace_SA_end_index_d_0_s_195 = {};
  int __f2dace_SA_f_e_d_0_s_188 = {};
  int __f2dace_SA_f_e_d_1_s_189 = {};
  int __f2dace_SA_fn_e_d_0_s_190 = {};
  int __f2dace_SA_fn_e_d_1_s_191 = {};
  int __f2dace_SA_ft_e_d_0_s_192 = {};
  int __f2dace_SA_ft_e_d_1_s_193 = {};
  int __f2dace_SA_inv_dual_edge_length_d_0_s_184 = {};
  int __f2dace_SA_inv_dual_edge_length_d_1_s_185 = {};
  int __f2dace_SA_inv_primal_edge_length_d_0_s_182 = {};
  int __f2dace_SA_inv_primal_edge_length_d_1_s_183 = {};
  int __f2dace_SA_quad_blk_d_0_s_179 = {};
  int __f2dace_SA_quad_blk_d_1_s_180 = {};
  int __f2dace_SA_quad_blk_d_2_s_181 = {};
  int __f2dace_SA_quad_idx_d_0_s_176 = {};
  int __f2dace_SA_quad_idx_d_1_s_177 = {};
  int __f2dace_SA_quad_idx_d_2_s_178 = {};
  int __f2dace_SA_start_block_d_0_s_196 = {};
  int __f2dace_SA_start_index_d_0_s_194 = {};
  int __f2dace_SA_tangent_orientation_d_0_s_174 = {};
  int __f2dace_SA_tangent_orientation_d_1_s_175 = {};
  int __f2dace_SA_vertex_blk_d_0_s_171 = {};
  int __f2dace_SA_vertex_blk_d_1_s_172 = {};
  int __f2dace_SA_vertex_blk_d_2_s_173 = {};
  int __f2dace_SA_vertex_idx_d_0_s_168 = {};
  int __f2dace_SA_vertex_idx_d_1_s_169 = {};
  int __f2dace_SA_vertex_idx_d_2_s_170 = {};
  int __f2dace_SOA_area_edge_d_0_s_186 = {};
  int __f2dace_SOA_area_edge_d_1_s_187 = {};
  int __f2dace_SOA_cell_blk_d_0_s_165 = {};
  int __f2dace_SOA_cell_blk_d_1_s_166 = {};
  int __f2dace_SOA_cell_blk_d_2_s_167 = {};
  int __f2dace_SOA_cell_idx_d_0_s_162 = {};
  int __f2dace_SOA_cell_idx_d_1_s_163 = {};
  int __f2dace_SOA_cell_idx_d_2_s_164 = {};
  int __f2dace_SOA_end_block_d_0_s_197 = {};
  int __f2dace_SOA_end_index_d_0_s_195 = {};
  int __f2dace_SOA_f_e_d_0_s_188 = {};
  int __f2dace_SOA_f_e_d_1_s_189 = {};
  int __f2dace_SOA_fn_e_d_0_s_190 = {};
  int __f2dace_SOA_fn_e_d_1_s_191 = {};
  int __f2dace_SOA_ft_e_d_0_s_192 = {};
  int __f2dace_SOA_ft_e_d_1_s_193 = {};
  int __f2dace_SOA_inv_dual_edge_length_d_0_s_184 = {};
  int __f2dace_SOA_inv_dual_edge_length_d_1_s_185 = {};
  int __f2dace_SOA_inv_primal_edge_length_d_0_s_182 = {};
  int __f2dace_SOA_inv_primal_edge_length_d_1_s_183 = {};
  int __f2dace_SOA_quad_blk_d_0_s_179 = {};
  int __f2dace_SOA_quad_blk_d_1_s_180 = {};
  int __f2dace_SOA_quad_blk_d_2_s_181 = {};
  int __f2dace_SOA_quad_idx_d_0_s_176 = {};
  int __f2dace_SOA_quad_idx_d_1_s_177 = {};
  int __f2dace_SOA_quad_idx_d_2_s_178 = {};
  int __f2dace_SOA_start_block_d_0_s_196 = {};
  int __f2dace_SOA_start_index_d_0_s_194 = {};
  int __f2dace_SOA_tangent_orientation_d_0_s_174 = {};
  int __f2dace_SOA_tangent_orientation_d_1_s_175 = {};
  int __f2dace_SOA_vertex_blk_d_0_s_171 = {};
  int __f2dace_SOA_vertex_blk_d_1_s_172 = {};
  int __f2dace_SOA_vertex_blk_d_2_s_173 = {};
  int __f2dace_SOA_vertex_idx_d_0_s_168 = {};
  int __f2dace_SOA_vertex_idx_d_1_s_169 = {};
  int __f2dace_SOA_vertex_idx_d_2_s_170 = {};
  double *area_edge = {};
  int *cell_blk = {};
  int *cell_idx = {};
  int *end_block = {};
  int *end_index = {};
  double *f_e = {};
  double *fn_e = {};
  double *ft_e = {};
  double *inv_dual_edge_length = {};
  double *inv_primal_edge_length = {};
  int *quad_blk = {};
  int *quad_idx = {};
  int *start_block = {};
  int *start_index = {};
  double *tangent_orientation = {};
  int *vertex_blk = {};
  int *vertex_idx = {};
};

struct t_grid_vertices {
  int __f2dace_SA_cell_blk_d_0_s_201 = {};
  int __f2dace_SA_cell_blk_d_1_s_202 = {};
  int __f2dace_SA_cell_blk_d_2_s_203 = {};
  int __f2dace_SA_cell_idx_d_0_s_198 = {};
  int __f2dace_SA_cell_idx_d_1_s_199 = {};
  int __f2dace_SA_cell_idx_d_2_s_200 = {};
  int __f2dace_SA_edge_blk_d_0_s_207 = {};
  int __f2dace_SA_edge_blk_d_1_s_208 = {};
  int __f2dace_SA_edge_blk_d_2_s_209 = {};
  int __f2dace_SA_edge_idx_d_0_s_204 = {};
  int __f2dace_SA_edge_idx_d_1_s_205 = {};
  int __f2dace_SA_edge_idx_d_2_s_206 = {};
  int __f2dace_SA_end_block_d_0_s_213 = {};
  int __f2dace_SA_end_index_d_0_s_211 = {};
  int __f2dace_SA_start_block_d_0_s_212 = {};
  int __f2dace_SA_start_index_d_0_s_210 = {};
  int __f2dace_SOA_cell_blk_d_0_s_201 = {};
  int __f2dace_SOA_cell_blk_d_1_s_202 = {};
  int __f2dace_SOA_cell_blk_d_2_s_203 = {};
  int __f2dace_SOA_cell_idx_d_0_s_198 = {};
  int __f2dace_SOA_cell_idx_d_1_s_199 = {};
  int __f2dace_SOA_cell_idx_d_2_s_200 = {};
  int __f2dace_SOA_edge_blk_d_0_s_207 = {};
  int __f2dace_SOA_edge_blk_d_1_s_208 = {};
  int __f2dace_SOA_edge_blk_d_2_s_209 = {};
  int __f2dace_SOA_edge_idx_d_0_s_204 = {};
  int __f2dace_SOA_edge_idx_d_1_s_205 = {};
  int __f2dace_SOA_edge_idx_d_2_s_206 = {};
  int __f2dace_SOA_end_block_d_0_s_213 = {};
  int __f2dace_SOA_end_index_d_0_s_211 = {};
  int __f2dace_SOA_start_block_d_0_s_212 = {};
  int __f2dace_SOA_start_index_d_0_s_210 = {};
  int *cell_blk = {};
  int *cell_idx = {};
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_block = {};
  int *end_index = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_nh_prog {
  int __f2dace_SA_rho_d_0_s_360 = {};
  int __f2dace_SA_rho_d_1_s_361 = {};
  int __f2dace_SA_rho_d_2_s_362 = {};
  int __f2dace_SA_theta_v_d_0_s_363 = {};
  int __f2dace_SA_theta_v_d_1_s_364 = {};
  int __f2dace_SA_theta_v_d_2_s_365 = {};
  int __f2dace_SA_vn_d_0_s_357 = {};
  int __f2dace_SA_vn_d_1_s_358 = {};
  int __f2dace_SA_vn_d_2_s_359 = {};
  int __f2dace_SA_w_d_0_s_354 = {};
  int __f2dace_SA_w_d_1_s_355 = {};
  int __f2dace_SA_w_d_2_s_356 = {};
  int __f2dace_SOA_rho_d_0_s_360 = {};
  int __f2dace_SOA_rho_d_1_s_361 = {};
  int __f2dace_SOA_rho_d_2_s_362 = {};
  int __f2dace_SOA_theta_v_d_0_s_363 = {};
  int __f2dace_SOA_theta_v_d_1_s_364 = {};
  int __f2dace_SOA_theta_v_d_2_s_365 = {};
  int __f2dace_SOA_vn_d_0_s_357 = {};
  int __f2dace_SOA_vn_d_1_s_358 = {};
  int __f2dace_SOA_vn_d_2_s_359 = {};
  int __f2dace_SOA_w_d_0_s_354 = {};
  int __f2dace_SOA_w_d_1_s_355 = {};
  int __f2dace_SOA_w_d_2_s_356 = {};
  double *rho = {};
  double *theta_v = {};
  double *vn = {};
  double *w = {};
};

struct t_nh_diag {
  int __f2dace_SA_ddt_vn_adv_d_0_s_408 = {};
  int __f2dace_SA_ddt_vn_adv_d_1_s_409 = {};
  int __f2dace_SA_ddt_vn_adv_d_2_s_410 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_0_s_390 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_1_s_391 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_2_s_392 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_3_s_393 = {};
  int __f2dace_SA_ddt_vn_cor_d_0_s_411 = {};
  int __f2dace_SA_ddt_vn_cor_d_1_s_412 = {};
  int __f2dace_SA_ddt_vn_cor_d_2_s_413 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_0_s_394 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_1_s_395 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_2_s_396 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_3_s_397 = {};
  int __f2dace_SA_ddt_vn_dmp_d_0_s_405 = {};
  int __f2dace_SA_ddt_vn_dmp_d_1_s_406 = {};
  int __f2dace_SA_ddt_vn_dmp_d_2_s_407 = {};
  int __f2dace_SA_ddt_vn_dyn_d_0_s_402 = {};
  int __f2dace_SA_ddt_vn_dyn_d_1_s_403 = {};
  int __f2dace_SA_ddt_vn_dyn_d_2_s_404 = {};
  int __f2dace_SA_ddt_vn_iau_d_0_s_420 = {};
  int __f2dace_SA_ddt_vn_iau_d_1_s_421 = {};
  int __f2dace_SA_ddt_vn_iau_d_2_s_422 = {};
  int __f2dace_SA_ddt_vn_pgr_d_0_s_414 = {};
  int __f2dace_SA_ddt_vn_pgr_d_1_s_415 = {};
  int __f2dace_SA_ddt_vn_pgr_d_2_s_416 = {};
  int __f2dace_SA_ddt_vn_phd_d_0_s_417 = {};
  int __f2dace_SA_ddt_vn_phd_d_1_s_418 = {};
  int __f2dace_SA_ddt_vn_phd_d_2_s_419 = {};
  int __f2dace_SA_ddt_vn_phy_d_0_s_381 = {};
  int __f2dace_SA_ddt_vn_phy_d_1_s_382 = {};
  int __f2dace_SA_ddt_vn_phy_d_2_s_383 = {};
  int __f2dace_SA_ddt_vn_ray_d_0_s_423 = {};
  int __f2dace_SA_ddt_vn_ray_d_1_s_424 = {};
  int __f2dace_SA_ddt_vn_ray_d_2_s_425 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_0_s_398 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_1_s_399 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_2_s_400 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_3_s_401 = {};
  int __f2dace_SA_exner_pr_d_0_s_366 = {};
  int __f2dace_SA_exner_pr_d_1_s_367 = {};
  int __f2dace_SA_exner_pr_d_2_s_368 = {};
  int __f2dace_SA_rho_ic_d_0_s_369 = {};
  int __f2dace_SA_rho_ic_d_1_s_370 = {};
  int __f2dace_SA_rho_ic_d_2_s_371 = {};
  int __f2dace_SA_theta_v_ic_d_0_s_372 = {};
  int __f2dace_SA_theta_v_ic_d_1_s_373 = {};
  int __f2dace_SA_theta_v_ic_d_2_s_374 = {};
  int __f2dace_SA_vn_ie_d_0_s_384 = {};
  int __f2dace_SA_vn_ie_d_1_s_385 = {};
  int __f2dace_SA_vn_ie_d_2_s_386 = {};
  int __f2dace_SA_vn_incr_d_0_s_375 = {};
  int __f2dace_SA_vn_incr_d_1_s_376 = {};
  int __f2dace_SA_vn_incr_d_2_s_377 = {};
  int __f2dace_SA_vt_d_0_s_378 = {};
  int __f2dace_SA_vt_d_1_s_379 = {};
  int __f2dace_SA_vt_d_2_s_380 = {};
  int __f2dace_SA_w_concorr_c_d_0_s_387 = {};
  int __f2dace_SA_w_concorr_c_d_1_s_388 = {};
  int __f2dace_SA_w_concorr_c_d_2_s_389 = {};
  int __f2dace_SOA_ddt_vn_adv_d_0_s_408 = {};
  int __f2dace_SOA_ddt_vn_adv_d_1_s_409 = {};
  int __f2dace_SOA_ddt_vn_adv_d_2_s_410 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_390 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_391 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_392 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_393 = {};
  int __f2dace_SOA_ddt_vn_cor_d_0_s_411 = {};
  int __f2dace_SOA_ddt_vn_cor_d_1_s_412 = {};
  int __f2dace_SOA_ddt_vn_cor_d_2_s_413 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_0_s_394 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_1_s_395 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_2_s_396 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_3_s_397 = {};
  int __f2dace_SOA_ddt_vn_dmp_d_0_s_405 = {};
  int __f2dace_SOA_ddt_vn_dmp_d_1_s_406 = {};
  int __f2dace_SOA_ddt_vn_dmp_d_2_s_407 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_0_s_402 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_1_s_403 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_2_s_404 = {};
  int __f2dace_SOA_ddt_vn_iau_d_0_s_420 = {};
  int __f2dace_SOA_ddt_vn_iau_d_1_s_421 = {};
  int __f2dace_SOA_ddt_vn_iau_d_2_s_422 = {};
  int __f2dace_SOA_ddt_vn_pgr_d_0_s_414 = {};
  int __f2dace_SOA_ddt_vn_pgr_d_1_s_415 = {};
  int __f2dace_SOA_ddt_vn_pgr_d_2_s_416 = {};
  int __f2dace_SOA_ddt_vn_phd_d_0_s_417 = {};
  int __f2dace_SOA_ddt_vn_phd_d_1_s_418 = {};
  int __f2dace_SOA_ddt_vn_phd_d_2_s_419 = {};
  int __f2dace_SOA_ddt_vn_phy_d_0_s_381 = {};
  int __f2dace_SOA_ddt_vn_phy_d_1_s_382 = {};
  int __f2dace_SOA_ddt_vn_phy_d_2_s_383 = {};
  int __f2dace_SOA_ddt_vn_ray_d_0_s_423 = {};
  int __f2dace_SOA_ddt_vn_ray_d_1_s_424 = {};
  int __f2dace_SOA_ddt_vn_ray_d_2_s_425 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_0_s_398 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_1_s_399 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_2_s_400 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_3_s_401 = {};
  int __f2dace_SOA_exner_pr_d_0_s_366 = {};
  int __f2dace_SOA_exner_pr_d_1_s_367 = {};
  int __f2dace_SOA_exner_pr_d_2_s_368 = {};
  int __f2dace_SOA_rho_ic_d_0_s_369 = {};
  int __f2dace_SOA_rho_ic_d_1_s_370 = {};
  int __f2dace_SOA_rho_ic_d_2_s_371 = {};
  int __f2dace_SOA_theta_v_ic_d_0_s_372 = {};
  int __f2dace_SOA_theta_v_ic_d_1_s_373 = {};
  int __f2dace_SOA_theta_v_ic_d_2_s_374 = {};
  int __f2dace_SOA_vn_ie_d_0_s_384 = {};
  int __f2dace_SOA_vn_ie_d_1_s_385 = {};
  int __f2dace_SOA_vn_ie_d_2_s_386 = {};
  int __f2dace_SOA_vn_incr_d_0_s_375 = {};
  int __f2dace_SOA_vn_incr_d_1_s_376 = {};
  int __f2dace_SOA_vn_incr_d_2_s_377 = {};
  int __f2dace_SOA_vt_d_0_s_378 = {};
  int __f2dace_SOA_vt_d_1_s_379 = {};
  int __f2dace_SOA_vt_d_2_s_380 = {};
  int __f2dace_SOA_w_concorr_c_d_0_s_387 = {};
  int __f2dace_SOA_w_concorr_c_d_1_s_388 = {};
  int __f2dace_SOA_w_concorr_c_d_2_s_389 = {};
  double *ddt_vn_adv = {};
  int ddt_vn_adv_is_associated = {};
  double *ddt_vn_apc_pc = {};
  double *ddt_vn_cor = {};
  int ddt_vn_cor_is_associated = {};
  double *ddt_vn_cor_pc = {};
  double *ddt_vn_dmp = {};
  int ddt_vn_dmp_is_associated = {};
  double *ddt_vn_dyn = {};
  int ddt_vn_dyn_is_associated = {};
  double *ddt_vn_iau = {};
  int ddt_vn_iau_is_associated = {};
  double *ddt_vn_pgr = {};
  int ddt_vn_pgr_is_associated = {};
  double *ddt_vn_phd = {};
  int ddt_vn_phd_is_associated = {};
  double *ddt_vn_phy = {};
  double *ddt_vn_ray = {};
  int ddt_vn_ray_is_associated = {};
  double *ddt_w_adv_pc = {};
  double *exner_pr = {};
  double max_vcfl_dyn = {};
  double *rho_ic = {};
  double *theta_v_ic = {};
  double *vn_ie = {};
  double *vn_incr = {};
  double *vt = {};
  double *w_concorr_c = {};
};

struct t_nh_ref {
  int __f2dace_SA_vn_ref_d_0_s_426 = {};
  int __f2dace_SA_vn_ref_d_1_s_427 = {};
  int __f2dace_SA_vn_ref_d_2_s_428 = {};
  int __f2dace_SOA_vn_ref_d_0_s_426 = {};
  int __f2dace_SOA_vn_ref_d_1_s_427 = {};
  int __f2dace_SOA_vn_ref_d_2_s_428 = {};
  double *vn_ref = {};
};

struct t_nh_metrics {
  int __f2dace_SA_coeff1_dwdz_d_0_s_447 = {};
  int __f2dace_SA_coeff1_dwdz_d_1_s_448 = {};
  int __f2dace_SA_coeff1_dwdz_d_2_s_449 = {};
  int __f2dace_SA_coeff2_dwdz_d_0_s_450 = {};
  int __f2dace_SA_coeff2_dwdz_d_1_s_451 = {};
  int __f2dace_SA_coeff2_dwdz_d_2_s_452 = {};
  int __f2dace_SA_coeff_gradekin_d_0_s_444 = {};
  int __f2dace_SA_coeff_gradekin_d_1_s_445 = {};
  int __f2dace_SA_coeff_gradekin_d_2_s_446 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_0_s_456 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_1_s_457 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_2_s_458 = {};
  int __f2dace_SA_ddqz_z_full_e_d_0_s_435 = {};
  int __f2dace_SA_ddqz_z_full_e_d_1_s_436 = {};
  int __f2dace_SA_ddqz_z_full_e_d_2_s_437 = {};
  int __f2dace_SA_ddqz_z_half_d_0_s_438 = {};
  int __f2dace_SA_ddqz_z_half_d_1_s_439 = {};
  int __f2dace_SA_ddqz_z_half_d_2_s_440 = {};
  int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_461 = {};
  int __f2dace_SA_deepatmo_gradh_mc_d_0_s_459 = {};
  int __f2dace_SA_deepatmo_invr_ifc_d_0_s_462 = {};
  int __f2dace_SA_deepatmo_invr_mc_d_0_s_460 = {};
  int __f2dace_SA_hmask_dd3d_d_0_s_431 = {};
  int __f2dace_SA_hmask_dd3d_d_1_s_432 = {};
  int __f2dace_SA_rayleigh_vn_d_0_s_429 = {};
  int __f2dace_SA_scalfac_dd3d_d_0_s_430 = {};
  int __f2dace_SA_theta_ref_mc_d_0_s_453 = {};
  int __f2dace_SA_theta_ref_mc_d_1_s_454 = {};
  int __f2dace_SA_theta_ref_mc_d_2_s_455 = {};
  int __f2dace_SA_vwind_expl_wgt_d_0_s_433 = {};
  int __f2dace_SA_vwind_expl_wgt_d_1_s_434 = {};
  int __f2dace_SA_wgtfac_c_d_0_s_441 = {};
  int __f2dace_SA_wgtfac_c_d_1_s_442 = {};
  int __f2dace_SA_wgtfac_c_d_2_s_443 = {};
  int __f2dace_SOA_coeff1_dwdz_d_0_s_447 = {};
  int __f2dace_SOA_coeff1_dwdz_d_1_s_448 = {};
  int __f2dace_SOA_coeff1_dwdz_d_2_s_449 = {};
  int __f2dace_SOA_coeff2_dwdz_d_0_s_450 = {};
  int __f2dace_SOA_coeff2_dwdz_d_1_s_451 = {};
  int __f2dace_SOA_coeff2_dwdz_d_2_s_452 = {};
  int __f2dace_SOA_coeff_gradekin_d_0_s_444 = {};
  int __f2dace_SOA_coeff_gradekin_d_1_s_445 = {};
  int __f2dace_SOA_coeff_gradekin_d_2_s_446 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_0_s_456 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_1_s_457 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_2_s_458 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_0_s_435 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_1_s_436 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_2_s_437 = {};
  int __f2dace_SOA_ddqz_z_half_d_0_s_438 = {};
  int __f2dace_SOA_ddqz_z_half_d_1_s_439 = {};
  int __f2dace_SOA_ddqz_z_half_d_2_s_440 = {};
  int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_461 = {};
  int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_459 = {};
  int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_462 = {};
  int __f2dace_SOA_deepatmo_invr_mc_d_0_s_460 = {};
  int __f2dace_SOA_hmask_dd3d_d_0_s_431 = {};
  int __f2dace_SOA_hmask_dd3d_d_1_s_432 = {};
  int __f2dace_SOA_rayleigh_vn_d_0_s_429 = {};
  int __f2dace_SOA_scalfac_dd3d_d_0_s_430 = {};
  int __f2dace_SOA_theta_ref_mc_d_0_s_453 = {};
  int __f2dace_SOA_theta_ref_mc_d_1_s_454 = {};
  int __f2dace_SOA_theta_ref_mc_d_2_s_455 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_0_s_433 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_1_s_434 = {};
  int __f2dace_SOA_wgtfac_c_d_0_s_441 = {};
  int __f2dace_SOA_wgtfac_c_d_1_s_442 = {};
  int __f2dace_SOA_wgtfac_c_d_2_s_443 = {};
  double *coeff1_dwdz = {};
  double *coeff2_dwdz = {};
  double *coeff_gradekin = {};
  double *d_exner_dz_ref_ic = {};
  double *ddqz_z_full_e = {};
  double *ddqz_z_half = {};
  double *deepatmo_gradh_ifc = {};
  double *deepatmo_gradh_mc = {};
  double *deepatmo_invr_ifc = {};
  double *deepatmo_invr_mc = {};
  double *hmask_dd3d = {};
  double *rayleigh_vn = {};
  double *scalfac_dd3d = {};
  double *theta_ref_mc = {};
  double *vwind_expl_wgt = {};
  double *wgtfac_c = {};
};

struct t_nh_state {
  int __f2dace_SA_prog_d_0_s_463 = {};
  int __f2dace_SOA_prog_d_0_s_463 = {};
  t_nh_diag *diag = {};
  t_nh_metrics *metrics = {};
  t_nh_prog **prog = {};
  t_nh_ref *ref = {};
};

struct t_grid_domain_decomp_info {
  int __f2dace_SA_owner_mask_d_0_s_32 = {};
  int __f2dace_SA_owner_mask_d_1_s_33 = {};
  int __f2dace_SOA_owner_mask_d_0_s_32 = {};
  int __f2dace_SOA_owner_mask_d_1_s_33 = {};
  int *owner_mask = {};
};

struct t_grid_cells {
  int __f2dace_SA_area_d_0_s_156 = {};
  int __f2dace_SA_area_d_1_s_157 = {};
  int __f2dace_SA_edge_blk_d_0_s_153 = {};
  int __f2dace_SA_edge_blk_d_1_s_154 = {};
  int __f2dace_SA_edge_blk_d_2_s_155 = {};
  int __f2dace_SA_edge_idx_d_0_s_150 = {};
  int __f2dace_SA_edge_idx_d_1_s_151 = {};
  int __f2dace_SA_edge_idx_d_2_s_152 = {};
  int __f2dace_SA_end_block_d_0_s_161 = {};
  int __f2dace_SA_end_index_d_0_s_159 = {};
  int __f2dace_SA_neighbor_blk_d_0_s_147 = {};
  int __f2dace_SA_neighbor_blk_d_1_s_148 = {};
  int __f2dace_SA_neighbor_blk_d_2_s_149 = {};
  int __f2dace_SA_neighbor_idx_d_0_s_144 = {};
  int __f2dace_SA_neighbor_idx_d_1_s_145 = {};
  int __f2dace_SA_neighbor_idx_d_2_s_146 = {};
  int __f2dace_SA_start_block_d_0_s_160 = {};
  int __f2dace_SA_start_index_d_0_s_158 = {};
  int __f2dace_SOA_area_d_0_s_156 = {};
  int __f2dace_SOA_area_d_1_s_157 = {};
  int __f2dace_SOA_edge_blk_d_0_s_153 = {};
  int __f2dace_SOA_edge_blk_d_1_s_154 = {};
  int __f2dace_SOA_edge_blk_d_2_s_155 = {};
  int __f2dace_SOA_edge_idx_d_0_s_150 = {};
  int __f2dace_SOA_edge_idx_d_1_s_151 = {};
  int __f2dace_SOA_edge_idx_d_2_s_152 = {};
  int __f2dace_SOA_end_block_d_0_s_161 = {};
  int __f2dace_SOA_end_index_d_0_s_159 = {};
  int __f2dace_SOA_neighbor_blk_d_0_s_147 = {};
  int __f2dace_SOA_neighbor_blk_d_1_s_148 = {};
  int __f2dace_SOA_neighbor_blk_d_2_s_149 = {};
  int __f2dace_SOA_neighbor_idx_d_0_s_144 = {};
  int __f2dace_SOA_neighbor_idx_d_1_s_145 = {};
  int __f2dace_SOA_neighbor_idx_d_2_s_146 = {};
  int __f2dace_SOA_start_block_d_0_s_160 = {};
  int __f2dace_SOA_start_index_d_0_s_158 = {};
  double *area = {};
  t_grid_domain_decomp_info *decomp_info = {};
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_block = {};
  int *end_index = {};
  int *neighbor_blk = {};
  int *neighbor_idx = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_int_state {
  int __f2dace_SA_c_lin_e_d_0_s_54 = {};
  int __f2dace_SA_c_lin_e_d_1_s_55 = {};
  int __f2dace_SA_c_lin_e_d_2_s_56 = {};
  int __f2dace_SA_cells_aw_verts_d_0_s_60 = {};
  int __f2dace_SA_cells_aw_verts_d_1_s_61 = {};
  int __f2dace_SA_cells_aw_verts_d_2_s_62 = {};
  int __f2dace_SA_e_bln_c_s_d_0_s_57 = {};
  int __f2dace_SA_e_bln_c_s_d_1_s_58 = {};
  int __f2dace_SA_e_bln_c_s_d_2_s_59 = {};
  int __f2dace_SA_geofac_grdiv_d_0_s_63 = {};
  int __f2dace_SA_geofac_grdiv_d_1_s_64 = {};
  int __f2dace_SA_geofac_grdiv_d_2_s_65 = {};
  int __f2dace_SA_geofac_n2s_d_0_s_69 = {};
  int __f2dace_SA_geofac_n2s_d_1_s_70 = {};
  int __f2dace_SA_geofac_n2s_d_2_s_71 = {};
  int __f2dace_SA_geofac_rot_d_0_s_66 = {};
  int __f2dace_SA_geofac_rot_d_1_s_67 = {};
  int __f2dace_SA_geofac_rot_d_2_s_68 = {};
  int __f2dace_SA_nudgecoeff_e_d_0_s_72 = {};
  int __f2dace_SA_nudgecoeff_e_d_1_s_73 = {};
  int __f2dace_SOA_c_lin_e_d_0_s_54 = {};
  int __f2dace_SOA_c_lin_e_d_1_s_55 = {};
  int __f2dace_SOA_c_lin_e_d_2_s_56 = {};
  int __f2dace_SOA_cells_aw_verts_d_0_s_60 = {};
  int __f2dace_SOA_cells_aw_verts_d_1_s_61 = {};
  int __f2dace_SOA_cells_aw_verts_d_2_s_62 = {};
  int __f2dace_SOA_e_bln_c_s_d_0_s_57 = {};
  int __f2dace_SOA_e_bln_c_s_d_1_s_58 = {};
  int __f2dace_SOA_e_bln_c_s_d_2_s_59 = {};
  int __f2dace_SOA_geofac_grdiv_d_0_s_63 = {};
  int __f2dace_SOA_geofac_grdiv_d_1_s_64 = {};
  int __f2dace_SOA_geofac_grdiv_d_2_s_65 = {};
  int __f2dace_SOA_geofac_n2s_d_0_s_69 = {};
  int __f2dace_SOA_geofac_n2s_d_1_s_70 = {};
  int __f2dace_SOA_geofac_n2s_d_2_s_71 = {};
  int __f2dace_SOA_geofac_rot_d_0_s_66 = {};
  int __f2dace_SOA_geofac_rot_d_1_s_67 = {};
  int __f2dace_SOA_geofac_rot_d_2_s_68 = {};
  int __f2dace_SOA_nudgecoeff_e_d_0_s_72 = {};
  int __f2dace_SOA_nudgecoeff_e_d_1_s_73 = {};
  double *c_lin_e = {};
  double *cells_aw_verts = {};
  double *e_bln_c_s = {};
  double *geofac_grdiv = {};
  double *geofac_n2s = {};
  double *geofac_rot = {};
  double *nudgecoeff_e = {};
};

struct t_prepare_adv {};

struct t_patch {
  t_grid_cells *cells = {};
  t_grid_edges *edges = {};
  int id = {};
  int nblks_c = {};
  int nblks_e = {};
  int nblks_v = {};
  int nlev = {};
  int nlevp1 = {};
  int nshift = {};
  t_grid_vertices *verts = {};
};

struct solve_nh_corrector_pre_state_t; // Forward declaration.

DACE_EXPORTED solve_nh_corrector_pre_state_t *
__dace_init_solve_nh_corrector_pre(
    double *bdy_divdamp, double *enh_divdamp_fac, global_data_type *global_data,
    t_int_state *p_int, t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew,
    t_nh_prog *p_nh_prog_nnow, t_patch *p_patch, t_prepare_adv *prep_adv,
    double *scal_divdamp, double *z_alpha, double *z_beta,
    double *z_contr_w_fl_l, double *z_dexner_dz_c, double *z_dwdz_dd,
    double *z_exner_ex_pr, double *z_exner_expl, double *z_exner_ic,
    double *z_flxdiv_mass, double *z_flxdiv_theta, double *z_grad_rth,
    double *z_graddiv2_vn, double *z_graddiv_vn, double *z_gradh_exner,
    double *z_hydro_corr, double *z_kin_hor_e, double *z_mflx_top, double *z_q,
    double *z_raylfac, double *z_rho_e, double *z_rho_expl, double *z_rho_v,
    double *z_rth_pr, double *z_th_ddz_exner_c, double *z_theta_v_e,
    double *z_theta_v_fl_e, double *z_theta_v_pr_ic, double *z_theta_v_v,
    double *z_vn_avg, double *z_vt_ie, double *z_w_concorr_mc,
    double *z_w_concorr_me, double *z_w_expl, int __f2dace_OPTIONAL_lacc,
    double alin, double aqdr, double bqdr, double df32, double df42,
    double distv_bary_1, double distv_bary_2, double dt_linintp_ubc,
    double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift,
    double dthalf, double dtime, double dz32, double dz42, double dzlin,
    double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx,
    int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg,
    int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init,
    int l_recompute, int l_vert_nested, int lacc, int lclean_mflx,
    int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp,
    int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp,
    int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2,
    int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end,
    int rl_start, double scal_divdamp_o2, double wgt_nnew_rth,
    double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a,
    double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau,
    double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn,
    double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma,
    double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg,
    double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);
DACE_EXPORTED int
__dace_exit_solve_nh_corrector_pre(solve_nh_corrector_pre_state_t *__state);
DACE_EXPORTED void __program_solve_nh_corrector_pre(
    solve_nh_corrector_pre_state_t *__state, double *bdy_divdamp,
    double *enh_divdamp_fac, global_data_type *global_data, t_int_state *p_int,
    t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew, t_nh_prog *p_nh_prog_nnow,
    t_patch *p_patch, t_prepare_adv *prep_adv, double *scal_divdamp,
    double *z_alpha, double *z_beta, double *z_contr_w_fl_l,
    double *z_dexner_dz_c, double *z_dwdz_dd, double *z_exner_ex_pr,
    double *z_exner_expl, double *z_exner_ic, double *z_flxdiv_mass,
    double *z_flxdiv_theta, double *z_grad_rth, double *z_graddiv2_vn,
    double *z_graddiv_vn, double *z_gradh_exner, double *z_hydro_corr,
    double *z_kin_hor_e, double *z_mflx_top, double *z_q, double *z_raylfac,
    double *z_rho_e, double *z_rho_expl, double *z_rho_v, double *z_rth_pr,
    double *z_th_ddz_exner_c, double *z_theta_v_e, double *z_theta_v_fl_e,
    double *z_theta_v_pr_ic, double *z_theta_v_v, double *z_vn_avg,
    double *z_vt_ie, double *z_w_concorr_mc, double *z_w_concorr_me,
    double *z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr,
    double bqdr, double df32, double df42, double distv_bary_1,
    double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew,
    double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime,
    double dz32, double dz42, double dzlin, double dzqdr, int i_endblk,
    int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift,
    int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks,
    int jstep, int l_child_vertnest, int l_init, int l_recompute,
    int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx,
    int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev,
    int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp,
    int nshift, int nshift_total, int ntl1, int ntl2, int nvar,
    double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start,
    double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel,
    double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b,
    double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc,
    double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr,
    double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1,
    double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1,
    double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);

#endif // __DACE_CODEGEN_SOLVE_NH_CORRECTOR_PRE__
} // namespace corrector_pre
#include <dace/dace.h>

namespace predictor_post {
#ifndef __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__
#define __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__

struct global_data_type {
  int divdamp_type = {};
  int grf_intmethod_e = {};
  double iau_wgt_dyn = {};
  int is_iau_active = {};
  int *kstart_dd3d = {};
  int *kstart_moist = {};
  int l_limited_area = {};
  int *ndyn_substeps_var = {};
  int *nflatlev = {};
  int nproma = {};
  int *nrdmax = {};
  int rayleigh_type = {};
  int timer_solve_nh_edgecomp = {};
  int timer_solve_nh_vimpl = {};
  int timers_level = {};
};

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
  int *end_block = {};
  int *end_index = {};
  int *quad_blk = {};
  int *quad_idx = {};
  int *start_block = {};
  int *start_index = {};
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
  double *ddt_exner_phy = {};
  double *ddt_w_adv_pc = {};
  double *exner_dyn_incr = {};
  double *exner_incr = {};
  double *exner_pr = {};
  double *grf_bdy_mflx = {};
  double *grf_tend_rho = {};
  double *grf_tend_thv = {};
  double *grf_tend_w = {};
  double *mass_fl_e = {};
  double *mflx_ic_ubc = {};
  double *rho_ic = {};
  double *rho_ic_ubc = {};
  double *rho_incr = {};
  double *theta_v_ic = {};
  double *theta_v_ic_ubc = {};
  double *vn_ie = {};
  double *vn_ie_ubc = {};
  double *vt = {};
  double *w_concorr_c = {};
  double *w_ubc = {};
};

struct t_nh_ref {
  int __f2dace_SA_w_ref_d_0_s_271 = {};
  int __f2dace_SA_w_ref_d_1_s_272 = {};
  int __f2dace_SA_w_ref_d_2_s_273 = {};
  int __f2dace_SOA_w_ref_d_0_s_271 = {};
  int __f2dace_SOA_w_ref_d_1_s_272 = {};
  int __f2dace_SOA_w_ref_d_2_s_273 = {};
  double *w_ref = {};
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
  int *bdy_mflx_e_blk = {};
  int bdy_mflx_e_dim = {};
  int *bdy_mflx_e_idx = {};
  double *ddqz_z_full_e = {};
  double *ddqz_z_half = {};
  double *ddxn_z_full = {};
  double *ddxt_z_full = {};
  double *deepatmo_divh_mc = {};
  double *deepatmo_divzl_mc = {};
  double *deepatmo_divzu_mc = {};
  double *exner_ref_mc = {};
  double *inv_ddqz_z_full = {};
  double *rayleigh_w = {};
  double *vwind_expl_wgt = {};
  double *vwind_impl_wgt = {};
  double *wgtfac_c = {};
  double *wgtfac_e = {};
  double *wgtfacq_c = {};
  double *wgtfacq_e = {};
};

struct t_nh_state {
  t_nh_diag *diag = {};
  t_nh_metrics *metrics = {};
  t_nh_ref *ref = {};
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
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_block = {};
  int *end_index = {};
  int *start_block = {};
  int *start_index = {};
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
  double *exner = {};
  double *rho = {};
  double *theta_v = {};
  double *vn = {};
  double *w = {};
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
  double *e_bln_c_s = {};
  double *e_flx_avg = {};
  double *geofac_div = {};
  double *geofac_grdiv = {};
  double *rbf_vec_coeff_e = {};
};

struct t_prepare_adv {};

struct t_patch {
  t_grid_cells *cells = {};
  t_grid_edges *edges = {};
  int id = {};
  int nblks_c = {};
  int nblks_e = {};
  int nblks_v = {};
  int nlev = {};
  int nlevp1 = {};
};

struct solve_nh_predictor_post_state_t; // Forward declaration.

DACE_EXPORTED solve_nh_predictor_post_state_t *
__dace_init_solve_nh_predictor_post(
    double *bdy_divdamp, double *enh_divdamp_fac, global_data_type *global_data,
    t_int_state *p_int, t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew,
    t_nh_prog *p_nh_prog_nnow, t_patch *p_patch, t_prepare_adv *prep_adv,
    double *scal_divdamp, double *z_alpha, double *z_beta,
    double *z_contr_w_fl_l, double *z_dexner_dz_c, double *z_dwdz_dd,
    double *z_exner_ex_pr, double *z_exner_expl, double *z_exner_ic,
    double *z_flxdiv_mass, double *z_flxdiv_theta, double *z_grad_rth,
    double *z_graddiv2_vn, double *z_graddiv_vn, double *z_gradh_exner,
    double *z_hydro_corr, double *z_kin_hor_e, double *z_mflx_top, double *z_q,
    double *z_raylfac, double *z_rho_e, double *z_rho_expl, double *z_rho_v,
    double *z_rth_pr, double *z_th_ddz_exner_c, double *z_theta_v_e,
    double *z_theta_v_fl_e, double *z_theta_v_pr_ic, double *z_theta_v_v,
    double *z_vn_avg, double *z_vt_ie, double *z_w_concorr_mc,
    double *z_w_concorr_me, double *z_w_expl, int __f2dace_OPTIONAL_lacc,
    double alin, double aqdr, double bqdr, double df32, double df42,
    double distv_bary_1, double distv_bary_2, double dt_linintp_ubc,
    double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift,
    double dthalf, double dtime, double dz32, double dz42, double dzlin,
    double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx,
    int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg,
    int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init,
    int l_recompute, int l_vert_nested, int lacc, int lclean_mflx,
    int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp,
    int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp,
    int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2,
    int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end,
    int rl_start, double scal_divdamp_o2, double wgt_nnew_rth,
    double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a,
    double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau,
    double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn,
    double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma,
    double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg,
    double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);
DACE_EXPORTED int
__dace_exit_solve_nh_predictor_post(solve_nh_predictor_post_state_t *__state);
DACE_EXPORTED void __program_solve_nh_predictor_post(
    solve_nh_predictor_post_state_t *__state, double *bdy_divdamp,
    double *enh_divdamp_fac, global_data_type *global_data, t_int_state *p_int,
    t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew, t_nh_prog *p_nh_prog_nnow,
    t_patch *p_patch, t_prepare_adv *prep_adv, double *scal_divdamp,
    double *z_alpha, double *z_beta, double *z_contr_w_fl_l,
    double *z_dexner_dz_c, double *z_dwdz_dd, double *z_exner_ex_pr,
    double *z_exner_expl, double *z_exner_ic, double *z_flxdiv_mass,
    double *z_flxdiv_theta, double *z_grad_rth, double *z_graddiv2_vn,
    double *z_graddiv_vn, double *z_gradh_exner, double *z_hydro_corr,
    double *z_kin_hor_e, double *z_mflx_top, double *z_q, double *z_raylfac,
    double *z_rho_e, double *z_rho_expl, double *z_rho_v, double *z_rth_pr,
    double *z_th_ddz_exner_c, double *z_theta_v_e, double *z_theta_v_fl_e,
    double *z_theta_v_pr_ic, double *z_theta_v_v, double *z_vn_avg,
    double *z_vt_ie, double *z_w_concorr_mc, double *z_w_concorr_me,
    double *z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr,
    double bqdr, double df32, double df42, double distv_bary_1,
    double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew,
    double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime,
    double dz32, double dz42, double dzlin, double dzqdr, int i_endblk,
    int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift,
    int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks,
    int jstep, int l_child_vertnest, int l_init, int l_recompute,
    int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx,
    int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev,
    int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp,
    int nshift, int nshift_total, int ntl1, int ntl2, int nvar,
    double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start,
    double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel,
    double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b,
    double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc,
    double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr,
    double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1,
    double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1,
    double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);

#endif // __DACE_CODEGEN_SOLVE_NH_PREDICTOR_POST__
} // namespace predictor_post
#include <dace/dace.h>

namespace predictor_pre {
#ifndef __DACE_CODEGEN_SOLVE_NH_PREDICTOR_PRE__
#define __DACE_CODEGEN_SOLVE_NH_PREDICTOR_PRE__

struct global_data_type {
  int grf_intmethod_e = {};
  int i_am_accel_node = {};
  int iadv_rhotheta = {};
  double iau_wgt_dyn = {};
  int igradp_method = {};
  int is_iau_active = {};
  int itime_scheme = {};
  int *kstart_dd3d = {};
  int l_limited_area = {};
  int ldeepatmo = {};
  int lextra_diffu = {};
  int lvert_nest = {};
  int *nflat_gradp = {};
  int *nflatlev = {};
  int nproma = {};
  int *nrdmax = {};
  int rayleigh_type = {};
  int timer_intp = {};
  int timer_solve_nh_cellcomp = {};
  int timer_solve_nh_veltend = {};
  int timer_solve_nh_vnupd = {};
  int timers_level = {};
};

struct t_tangent_vectors {
  double v1 = {};
  double v2 = {};
};

struct t_grid_edges {
  int __f2dace_SA_area_edge_d_0_s_254 = {};
  int __f2dace_SA_area_edge_d_1_s_255 = {};
  int __f2dace_SA_cell_blk_d_0_s_227 = {};
  int __f2dace_SA_cell_blk_d_1_s_228 = {};
  int __f2dace_SA_cell_blk_d_2_s_229 = {};
  int __f2dace_SA_cell_idx_d_0_s_224 = {};
  int __f2dace_SA_cell_idx_d_1_s_225 = {};
  int __f2dace_SA_cell_idx_d_2_s_226 = {};
  int __f2dace_SA_dual_normal_cell_d_0_s_247 = {};
  int __f2dace_SA_dual_normal_cell_d_1_s_248 = {};
  int __f2dace_SA_dual_normal_cell_d_2_s_249 = {};
  int __f2dace_SA_end_block_d_0_s_265 = {};
  int __f2dace_SA_end_index_d_0_s_263 = {};
  int __f2dace_SA_f_e_d_0_s_256 = {};
  int __f2dace_SA_f_e_d_1_s_257 = {};
  int __f2dace_SA_fn_e_d_0_s_258 = {};
  int __f2dace_SA_fn_e_d_1_s_259 = {};
  int __f2dace_SA_ft_e_d_0_s_260 = {};
  int __f2dace_SA_ft_e_d_1_s_261 = {};
  int __f2dace_SA_inv_dual_edge_length_d_0_s_252 = {};
  int __f2dace_SA_inv_dual_edge_length_d_1_s_253 = {};
  int __f2dace_SA_inv_primal_edge_length_d_0_s_250 = {};
  int __f2dace_SA_inv_primal_edge_length_d_1_s_251 = {};
  int __f2dace_SA_primal_normal_cell_d_0_s_244 = {};
  int __f2dace_SA_primal_normal_cell_d_1_s_245 = {};
  int __f2dace_SA_primal_normal_cell_d_2_s_246 = {};
  int __f2dace_SA_quad_blk_d_0_s_241 = {};
  int __f2dace_SA_quad_blk_d_1_s_242 = {};
  int __f2dace_SA_quad_blk_d_2_s_243 = {};
  int __f2dace_SA_quad_idx_d_0_s_238 = {};
  int __f2dace_SA_quad_idx_d_1_s_239 = {};
  int __f2dace_SA_quad_idx_d_2_s_240 = {};
  int __f2dace_SA_start_block_d_0_s_264 = {};
  int __f2dace_SA_start_index_d_0_s_262 = {};
  int __f2dace_SA_tangent_orientation_d_0_s_236 = {};
  int __f2dace_SA_tangent_orientation_d_1_s_237 = {};
  int __f2dace_SA_vertex_blk_d_0_s_233 = {};
  int __f2dace_SA_vertex_blk_d_1_s_234 = {};
  int __f2dace_SA_vertex_blk_d_2_s_235 = {};
  int __f2dace_SA_vertex_idx_d_0_s_230 = {};
  int __f2dace_SA_vertex_idx_d_1_s_231 = {};
  int __f2dace_SA_vertex_idx_d_2_s_232 = {};
  int __f2dace_SOA_area_edge_d_0_s_254 = {};
  int __f2dace_SOA_area_edge_d_1_s_255 = {};
  int __f2dace_SOA_cell_blk_d_0_s_227 = {};
  int __f2dace_SOA_cell_blk_d_1_s_228 = {};
  int __f2dace_SOA_cell_blk_d_2_s_229 = {};
  int __f2dace_SOA_cell_idx_d_0_s_224 = {};
  int __f2dace_SOA_cell_idx_d_1_s_225 = {};
  int __f2dace_SOA_cell_idx_d_2_s_226 = {};
  int __f2dace_SOA_dual_normal_cell_d_0_s_247 = {};
  int __f2dace_SOA_dual_normal_cell_d_1_s_248 = {};
  int __f2dace_SOA_dual_normal_cell_d_2_s_249 = {};
  int __f2dace_SOA_end_block_d_0_s_265 = {};
  int __f2dace_SOA_end_index_d_0_s_263 = {};
  int __f2dace_SOA_f_e_d_0_s_256 = {};
  int __f2dace_SOA_f_e_d_1_s_257 = {};
  int __f2dace_SOA_fn_e_d_0_s_258 = {};
  int __f2dace_SOA_fn_e_d_1_s_259 = {};
  int __f2dace_SOA_ft_e_d_0_s_260 = {};
  int __f2dace_SOA_ft_e_d_1_s_261 = {};
  int __f2dace_SOA_inv_dual_edge_length_d_0_s_252 = {};
  int __f2dace_SOA_inv_dual_edge_length_d_1_s_253 = {};
  int __f2dace_SOA_inv_primal_edge_length_d_0_s_250 = {};
  int __f2dace_SOA_inv_primal_edge_length_d_1_s_251 = {};
  int __f2dace_SOA_primal_normal_cell_d_0_s_244 = {};
  int __f2dace_SOA_primal_normal_cell_d_1_s_245 = {};
  int __f2dace_SOA_primal_normal_cell_d_2_s_246 = {};
  int __f2dace_SOA_quad_blk_d_0_s_241 = {};
  int __f2dace_SOA_quad_blk_d_1_s_242 = {};
  int __f2dace_SOA_quad_blk_d_2_s_243 = {};
  int __f2dace_SOA_quad_idx_d_0_s_238 = {};
  int __f2dace_SOA_quad_idx_d_1_s_239 = {};
  int __f2dace_SOA_quad_idx_d_2_s_240 = {};
  int __f2dace_SOA_start_block_d_0_s_264 = {};
  int __f2dace_SOA_start_index_d_0_s_262 = {};
  int __f2dace_SOA_tangent_orientation_d_0_s_236 = {};
  int __f2dace_SOA_tangent_orientation_d_1_s_237 = {};
  int __f2dace_SOA_vertex_blk_d_0_s_233 = {};
  int __f2dace_SOA_vertex_blk_d_1_s_234 = {};
  int __f2dace_SOA_vertex_blk_d_2_s_235 = {};
  int __f2dace_SOA_vertex_idx_d_0_s_230 = {};
  int __f2dace_SOA_vertex_idx_d_1_s_231 = {};
  int __f2dace_SOA_vertex_idx_d_2_s_232 = {};
  double *area_edge = {};
  int *cell_blk = {};
  int *cell_idx = {};
  t_tangent_vectors **dual_normal_cell = {};
  int *end_block = {};
  int *end_index = {};
  double *f_e = {};
  double *fn_e = {};
  double *ft_e = {};
  double *inv_dual_edge_length = {};
  double *inv_primal_edge_length = {};
  t_tangent_vectors **primal_normal_cell = {};
  int *quad_blk = {};
  int *quad_idx = {};
  int *start_block = {};
  int *start_index = {};
  double *tangent_orientation = {};
  int *vertex_blk = {};
  int *vertex_idx = {};
};

struct t_grid_vertices {
  int __f2dace_SA_cell_blk_d_0_s_269 = {};
  int __f2dace_SA_cell_blk_d_1_s_270 = {};
  int __f2dace_SA_cell_blk_d_2_s_271 = {};
  int __f2dace_SA_cell_idx_d_0_s_266 = {};
  int __f2dace_SA_cell_idx_d_1_s_267 = {};
  int __f2dace_SA_cell_idx_d_2_s_268 = {};
  int __f2dace_SA_edge_blk_d_0_s_275 = {};
  int __f2dace_SA_edge_blk_d_1_s_276 = {};
  int __f2dace_SA_edge_blk_d_2_s_277 = {};
  int __f2dace_SA_edge_idx_d_0_s_272 = {};
  int __f2dace_SA_edge_idx_d_1_s_273 = {};
  int __f2dace_SA_edge_idx_d_2_s_274 = {};
  int __f2dace_SA_end_block_d_0_s_281 = {};
  int __f2dace_SA_end_index_d_0_s_279 = {};
  int __f2dace_SA_start_block_d_0_s_280 = {};
  int __f2dace_SA_start_index_d_0_s_278 = {};
  int __f2dace_SOA_cell_blk_d_0_s_269 = {};
  int __f2dace_SOA_cell_blk_d_1_s_270 = {};
  int __f2dace_SOA_cell_blk_d_2_s_271 = {};
  int __f2dace_SOA_cell_idx_d_0_s_266 = {};
  int __f2dace_SOA_cell_idx_d_1_s_267 = {};
  int __f2dace_SOA_cell_idx_d_2_s_268 = {};
  int __f2dace_SOA_edge_blk_d_0_s_275 = {};
  int __f2dace_SOA_edge_blk_d_1_s_276 = {};
  int __f2dace_SOA_edge_blk_d_2_s_277 = {};
  int __f2dace_SOA_edge_idx_d_0_s_272 = {};
  int __f2dace_SOA_edge_idx_d_1_s_273 = {};
  int __f2dace_SOA_edge_idx_d_2_s_274 = {};
  int __f2dace_SOA_end_block_d_0_s_281 = {};
  int __f2dace_SOA_end_index_d_0_s_279 = {};
  int __f2dace_SOA_start_block_d_0_s_280 = {};
  int __f2dace_SOA_start_index_d_0_s_278 = {};
  int *cell_blk = {};
  int *cell_idx = {};
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_block = {};
  int *end_index = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_nh_diag {
  int __f2dace_SA_ddt_vn_apc_pc_d_0_s_569 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_1_s_570 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_2_s_571 = {};
  int __f2dace_SA_ddt_vn_apc_pc_d_3_s_572 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_0_s_573 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_1_s_574 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_2_s_575 = {};
  int __f2dace_SA_ddt_vn_cor_pc_d_3_s_576 = {};
  int __f2dace_SA_ddt_vn_dyn_d_0_s_581 = {};
  int __f2dace_SA_ddt_vn_dyn_d_1_s_582 = {};
  int __f2dace_SA_ddt_vn_dyn_d_2_s_583 = {};
  int __f2dace_SA_ddt_vn_grf_d_0_s_584 = {};
  int __f2dace_SA_ddt_vn_grf_d_1_s_585 = {};
  int __f2dace_SA_ddt_vn_grf_d_2_s_586 = {};
  int __f2dace_SA_ddt_vn_phy_d_0_s_560 = {};
  int __f2dace_SA_ddt_vn_phy_d_1_s_561 = {};
  int __f2dace_SA_ddt_vn_phy_d_2_s_562 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_0_s_577 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_1_s_578 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_2_s_579 = {};
  int __f2dace_SA_ddt_w_adv_pc_d_3_s_580 = {};
  int __f2dace_SA_exner_pr_d_0_s_530 = {};
  int __f2dace_SA_exner_pr_d_1_s_531 = {};
  int __f2dace_SA_exner_pr_d_2_s_532 = {};
  int __f2dace_SA_grf_bdy_mflx_d_0_s_545 = {};
  int __f2dace_SA_grf_bdy_mflx_d_1_s_546 = {};
  int __f2dace_SA_grf_bdy_mflx_d_2_s_547 = {};
  int __f2dace_SA_grf_tend_mflx_d_0_s_542 = {};
  int __f2dace_SA_grf_tend_mflx_d_1_s_543 = {};
  int __f2dace_SA_grf_tend_mflx_d_2_s_544 = {};
  int __f2dace_SA_grf_tend_vn_d_0_s_539 = {};
  int __f2dace_SA_grf_tend_vn_d_1_s_540 = {};
  int __f2dace_SA_grf_tend_vn_d_2_s_541 = {};
  int __f2dace_SA_rho_ic_d_0_s_533 = {};
  int __f2dace_SA_rho_ic_d_1_s_534 = {};
  int __f2dace_SA_rho_ic_d_2_s_535 = {};
  int __f2dace_SA_theta_v_ic_d_0_s_536 = {};
  int __f2dace_SA_theta_v_ic_d_1_s_537 = {};
  int __f2dace_SA_theta_v_ic_d_2_s_538 = {};
  int __f2dace_SA_vn_ie_d_0_s_563 = {};
  int __f2dace_SA_vn_ie_d_1_s_564 = {};
  int __f2dace_SA_vn_ie_d_2_s_565 = {};
  int __f2dace_SA_vn_ie_int_d_0_s_548 = {};
  int __f2dace_SA_vn_ie_int_d_1_s_549 = {};
  int __f2dace_SA_vn_ie_int_d_2_s_550 = {};
  int __f2dace_SA_vn_ie_ubc_d_0_s_551 = {};
  int __f2dace_SA_vn_ie_ubc_d_1_s_552 = {};
  int __f2dace_SA_vn_ie_ubc_d_2_s_553 = {};
  int __f2dace_SA_vn_incr_d_0_s_554 = {};
  int __f2dace_SA_vn_incr_d_1_s_555 = {};
  int __f2dace_SA_vn_incr_d_2_s_556 = {};
  int __f2dace_SA_vt_d_0_s_557 = {};
  int __f2dace_SA_vt_d_1_s_558 = {};
  int __f2dace_SA_vt_d_2_s_559 = {};
  int __f2dace_SA_w_concorr_c_d_0_s_566 = {};
  int __f2dace_SA_w_concorr_c_d_1_s_567 = {};
  int __f2dace_SA_w_concorr_c_d_2_s_568 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_0_s_569 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_1_s_570 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_2_s_571 = {};
  int __f2dace_SOA_ddt_vn_apc_pc_d_3_s_572 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_0_s_573 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_1_s_574 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_2_s_575 = {};
  int __f2dace_SOA_ddt_vn_cor_pc_d_3_s_576 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_0_s_581 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_1_s_582 = {};
  int __f2dace_SOA_ddt_vn_dyn_d_2_s_583 = {};
  int __f2dace_SOA_ddt_vn_grf_d_0_s_584 = {};
  int __f2dace_SOA_ddt_vn_grf_d_1_s_585 = {};
  int __f2dace_SOA_ddt_vn_grf_d_2_s_586 = {};
  int __f2dace_SOA_ddt_vn_phy_d_0_s_560 = {};
  int __f2dace_SOA_ddt_vn_phy_d_1_s_561 = {};
  int __f2dace_SOA_ddt_vn_phy_d_2_s_562 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_0_s_577 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_1_s_578 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_2_s_579 = {};
  int __f2dace_SOA_ddt_w_adv_pc_d_3_s_580 = {};
  int __f2dace_SOA_exner_pr_d_0_s_530 = {};
  int __f2dace_SOA_exner_pr_d_1_s_531 = {};
  int __f2dace_SOA_exner_pr_d_2_s_532 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_0_s_545 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_1_s_546 = {};
  int __f2dace_SOA_grf_bdy_mflx_d_2_s_547 = {};
  int __f2dace_SOA_grf_tend_mflx_d_0_s_542 = {};
  int __f2dace_SOA_grf_tend_mflx_d_1_s_543 = {};
  int __f2dace_SOA_grf_tend_mflx_d_2_s_544 = {};
  int __f2dace_SOA_grf_tend_vn_d_0_s_539 = {};
  int __f2dace_SOA_grf_tend_vn_d_1_s_540 = {};
  int __f2dace_SOA_grf_tend_vn_d_2_s_541 = {};
  int __f2dace_SOA_rho_ic_d_0_s_533 = {};
  int __f2dace_SOA_rho_ic_d_1_s_534 = {};
  int __f2dace_SOA_rho_ic_d_2_s_535 = {};
  int __f2dace_SOA_theta_v_ic_d_0_s_536 = {};
  int __f2dace_SOA_theta_v_ic_d_1_s_537 = {};
  int __f2dace_SOA_theta_v_ic_d_2_s_538 = {};
  int __f2dace_SOA_vn_ie_d_0_s_563 = {};
  int __f2dace_SOA_vn_ie_d_1_s_564 = {};
  int __f2dace_SOA_vn_ie_d_2_s_565 = {};
  int __f2dace_SOA_vn_ie_int_d_0_s_548 = {};
  int __f2dace_SOA_vn_ie_int_d_1_s_549 = {};
  int __f2dace_SOA_vn_ie_int_d_2_s_550 = {};
  int __f2dace_SOA_vn_ie_ubc_d_0_s_551 = {};
  int __f2dace_SOA_vn_ie_ubc_d_1_s_552 = {};
  int __f2dace_SOA_vn_ie_ubc_d_2_s_553 = {};
  int __f2dace_SOA_vn_incr_d_0_s_554 = {};
  int __f2dace_SOA_vn_incr_d_1_s_555 = {};
  int __f2dace_SOA_vn_incr_d_2_s_556 = {};
  int __f2dace_SOA_vt_d_0_s_557 = {};
  int __f2dace_SOA_vt_d_1_s_558 = {};
  int __f2dace_SOA_vt_d_2_s_559 = {};
  int __f2dace_SOA_w_concorr_c_d_0_s_566 = {};
  int __f2dace_SOA_w_concorr_c_d_1_s_567 = {};
  int __f2dace_SOA_w_concorr_c_d_2_s_568 = {};
  int ddt_vn_adv_is_associated = {};
  double *ddt_vn_apc_pc = {};
  int ddt_vn_cor_is_associated = {};
  double *ddt_vn_cor_pc = {};
  double *ddt_vn_dyn = {};
  int ddt_vn_dyn_is_associated = {};
  double *ddt_vn_grf = {};
  int ddt_vn_grf_is_associated = {};
  double *ddt_vn_phy = {};
  double *ddt_w_adv_pc = {};
  double *exner_pr = {};
  double *grf_bdy_mflx = {};
  double *grf_tend_mflx = {};
  double *grf_tend_vn = {};
  double max_vcfl_dyn = {};
  double *rho_ic = {};
  double *theta_v_ic = {};
  double *vn_ie = {};
  double *vn_ie_int = {};
  double *vn_ie_ubc = {};
  double *vn_incr = {};
  double *vt = {};
  double *w_concorr_c = {};
};

struct t_nh_ref {
  int __f2dace_SA_vn_ref_d_0_s_587 = {};
  int __f2dace_SA_vn_ref_d_1_s_588 = {};
  int __f2dace_SA_vn_ref_d_2_s_589 = {};
  int __f2dace_SOA_vn_ref_d_0_s_587 = {};
  int __f2dace_SOA_vn_ref_d_1_s_588 = {};
  int __f2dace_SOA_vn_ref_d_2_s_589 = {};
  double *vn_ref = {};
};

struct t_nh_metrics {
  int __f2dace_SA_bdy_mflx_e_blk_d_0_s_679 = {};
  int __f2dace_SA_bdy_mflx_e_idx_d_0_s_678 = {};
  int __f2dace_SA_coeff1_dwdz_d_0_s_626 = {};
  int __f2dace_SA_coeff1_dwdz_d_1_s_627 = {};
  int __f2dace_SA_coeff1_dwdz_d_2_s_628 = {};
  int __f2dace_SA_coeff2_dwdz_d_0_s_629 = {};
  int __f2dace_SA_coeff2_dwdz_d_1_s_630 = {};
  int __f2dace_SA_coeff2_dwdz_d_2_s_631 = {};
  int __f2dace_SA_coeff_gradekin_d_0_s_623 = {};
  int __f2dace_SA_coeff_gradekin_d_1_s_624 = {};
  int __f2dace_SA_coeff_gradekin_d_2_s_625 = {};
  int __f2dace_SA_coeff_gradp_d_0_s_636 = {};
  int __f2dace_SA_coeff_gradp_d_1_s_637 = {};
  int __f2dace_SA_coeff_gradp_d_2_s_638 = {};
  int __f2dace_SA_coeff_gradp_d_3_s_639 = {};
  int __f2dace_SA_d2dexdz2_fac1_mc_d_0_s_664 = {};
  int __f2dace_SA_d2dexdz2_fac1_mc_d_1_s_665 = {};
  int __f2dace_SA_d2dexdz2_fac1_mc_d_2_s_666 = {};
  int __f2dace_SA_d2dexdz2_fac2_mc_d_0_s_667 = {};
  int __f2dace_SA_d2dexdz2_fac2_mc_d_1_s_668 = {};
  int __f2dace_SA_d2dexdz2_fac2_mc_d_2_s_669 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_0_s_661 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_1_s_662 = {};
  int __f2dace_SA_d_exner_dz_ref_ic_d_2_s_663 = {};
  int __f2dace_SA_ddqz_z_full_e_d_0_s_599 = {};
  int __f2dace_SA_ddqz_z_full_e_d_1_s_600 = {};
  int __f2dace_SA_ddqz_z_full_e_d_2_s_601 = {};
  int __f2dace_SA_ddqz_z_half_d_0_s_602 = {};
  int __f2dace_SA_ddqz_z_half_d_1_s_603 = {};
  int __f2dace_SA_ddqz_z_half_d_2_s_604 = {};
  int __f2dace_SA_ddxn_z_full_d_0_s_593 = {};
  int __f2dace_SA_ddxn_z_full_d_1_s_594 = {};
  int __f2dace_SA_ddxn_z_full_d_2_s_595 = {};
  int __f2dace_SA_ddxt_z_full_d_0_s_596 = {};
  int __f2dace_SA_ddxt_z_full_d_1_s_597 = {};
  int __f2dace_SA_ddxt_z_full_d_2_s_598 = {};
  int __f2dace_SA_deepatmo_gradh_ifc_d_0_s_682 = {};
  int __f2dace_SA_deepatmo_gradh_mc_d_0_s_680 = {};
  int __f2dace_SA_deepatmo_invr_ifc_d_0_s_683 = {};
  int __f2dace_SA_deepatmo_invr_mc_d_0_s_681 = {};
  int __f2dace_SA_exner_exfac_d_0_s_640 = {};
  int __f2dace_SA_exner_exfac_d_1_s_641 = {};
  int __f2dace_SA_exner_exfac_d_2_s_642 = {};
  int __f2dace_SA_exner_ref_mc_d_0_s_652 = {};
  int __f2dace_SA_exner_ref_mc_d_1_s_653 = {};
  int __f2dace_SA_exner_ref_mc_d_2_s_654 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_0_s_605 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_1_s_606 = {};
  int __f2dace_SA_inv_ddqz_z_full_d_2_s_607 = {};
  int __f2dace_SA_pg_edgeblk_d_0_s_676 = {};
  int __f2dace_SA_pg_edgeidx_d_0_s_675 = {};
  int __f2dace_SA_pg_exdist_d_0_s_670 = {};
  int __f2dace_SA_pg_vertidx_d_0_s_677 = {};
  int __f2dace_SA_rayleigh_vn_d_0_s_590 = {};
  int __f2dace_SA_rho_ref_mc_d_0_s_655 = {};
  int __f2dace_SA_rho_ref_mc_d_1_s_656 = {};
  int __f2dace_SA_rho_ref_mc_d_2_s_657 = {};
  int __f2dace_SA_rho_ref_me_d_0_s_658 = {};
  int __f2dace_SA_rho_ref_me_d_1_s_659 = {};
  int __f2dace_SA_rho_ref_me_d_2_s_660 = {};
  int __f2dace_SA_theta_ref_ic_d_0_s_649 = {};
  int __f2dace_SA_theta_ref_ic_d_1_s_650 = {};
  int __f2dace_SA_theta_ref_ic_d_2_s_651 = {};
  int __f2dace_SA_theta_ref_mc_d_0_s_643 = {};
  int __f2dace_SA_theta_ref_mc_d_1_s_644 = {};
  int __f2dace_SA_theta_ref_mc_d_2_s_645 = {};
  int __f2dace_SA_theta_ref_me_d_0_s_646 = {};
  int __f2dace_SA_theta_ref_me_d_1_s_647 = {};
  int __f2dace_SA_theta_ref_me_d_2_s_648 = {};
  int __f2dace_SA_vertidx_gradp_d_0_s_671 = {};
  int __f2dace_SA_vertidx_gradp_d_1_s_672 = {};
  int __f2dace_SA_vertidx_gradp_d_2_s_673 = {};
  int __f2dace_SA_vertidx_gradp_d_3_s_674 = {};
  int __f2dace_SA_vwind_expl_wgt_d_0_s_591 = {};
  int __f2dace_SA_vwind_expl_wgt_d_1_s_592 = {};
  int __f2dace_SA_wgtfac_c_d_0_s_608 = {};
  int __f2dace_SA_wgtfac_c_d_1_s_609 = {};
  int __f2dace_SA_wgtfac_c_d_2_s_610 = {};
  int __f2dace_SA_wgtfac_e_d_0_s_611 = {};
  int __f2dace_SA_wgtfac_e_d_1_s_612 = {};
  int __f2dace_SA_wgtfac_e_d_2_s_613 = {};
  int __f2dace_SA_wgtfacq1_c_d_0_s_620 = {};
  int __f2dace_SA_wgtfacq1_c_d_1_s_621 = {};
  int __f2dace_SA_wgtfacq1_c_d_2_s_622 = {};
  int __f2dace_SA_wgtfacq_c_d_0_s_614 = {};
  int __f2dace_SA_wgtfacq_c_d_1_s_615 = {};
  int __f2dace_SA_wgtfacq_c_d_2_s_616 = {};
  int __f2dace_SA_wgtfacq_e_d_0_s_617 = {};
  int __f2dace_SA_wgtfacq_e_d_1_s_618 = {};
  int __f2dace_SA_wgtfacq_e_d_2_s_619 = {};
  int __f2dace_SA_zdiff_gradp_d_0_s_632 = {};
  int __f2dace_SA_zdiff_gradp_d_1_s_633 = {};
  int __f2dace_SA_zdiff_gradp_d_2_s_634 = {};
  int __f2dace_SA_zdiff_gradp_d_3_s_635 = {};
  int __f2dace_SOA_bdy_mflx_e_blk_d_0_s_679 = {};
  int __f2dace_SOA_bdy_mflx_e_idx_d_0_s_678 = {};
  int __f2dace_SOA_coeff1_dwdz_d_0_s_626 = {};
  int __f2dace_SOA_coeff1_dwdz_d_1_s_627 = {};
  int __f2dace_SOA_coeff1_dwdz_d_2_s_628 = {};
  int __f2dace_SOA_coeff2_dwdz_d_0_s_629 = {};
  int __f2dace_SOA_coeff2_dwdz_d_1_s_630 = {};
  int __f2dace_SOA_coeff2_dwdz_d_2_s_631 = {};
  int __f2dace_SOA_coeff_gradekin_d_0_s_623 = {};
  int __f2dace_SOA_coeff_gradekin_d_1_s_624 = {};
  int __f2dace_SOA_coeff_gradekin_d_2_s_625 = {};
  int __f2dace_SOA_coeff_gradp_d_0_s_636 = {};
  int __f2dace_SOA_coeff_gradp_d_1_s_637 = {};
  int __f2dace_SOA_coeff_gradp_d_2_s_638 = {};
  int __f2dace_SOA_coeff_gradp_d_3_s_639 = {};
  int __f2dace_SOA_d2dexdz2_fac1_mc_d_0_s_664 = {};
  int __f2dace_SOA_d2dexdz2_fac1_mc_d_1_s_665 = {};
  int __f2dace_SOA_d2dexdz2_fac1_mc_d_2_s_666 = {};
  int __f2dace_SOA_d2dexdz2_fac2_mc_d_0_s_667 = {};
  int __f2dace_SOA_d2dexdz2_fac2_mc_d_1_s_668 = {};
  int __f2dace_SOA_d2dexdz2_fac2_mc_d_2_s_669 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_0_s_661 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_1_s_662 = {};
  int __f2dace_SOA_d_exner_dz_ref_ic_d_2_s_663 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_0_s_599 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_1_s_600 = {};
  int __f2dace_SOA_ddqz_z_full_e_d_2_s_601 = {};
  int __f2dace_SOA_ddqz_z_half_d_0_s_602 = {};
  int __f2dace_SOA_ddqz_z_half_d_1_s_603 = {};
  int __f2dace_SOA_ddqz_z_half_d_2_s_604 = {};
  int __f2dace_SOA_ddxn_z_full_d_0_s_593 = {};
  int __f2dace_SOA_ddxn_z_full_d_1_s_594 = {};
  int __f2dace_SOA_ddxn_z_full_d_2_s_595 = {};
  int __f2dace_SOA_ddxt_z_full_d_0_s_596 = {};
  int __f2dace_SOA_ddxt_z_full_d_1_s_597 = {};
  int __f2dace_SOA_ddxt_z_full_d_2_s_598 = {};
  int __f2dace_SOA_deepatmo_gradh_ifc_d_0_s_682 = {};
  int __f2dace_SOA_deepatmo_gradh_mc_d_0_s_680 = {};
  int __f2dace_SOA_deepatmo_invr_ifc_d_0_s_683 = {};
  int __f2dace_SOA_deepatmo_invr_mc_d_0_s_681 = {};
  int __f2dace_SOA_exner_exfac_d_0_s_640 = {};
  int __f2dace_SOA_exner_exfac_d_1_s_641 = {};
  int __f2dace_SOA_exner_exfac_d_2_s_642 = {};
  int __f2dace_SOA_exner_ref_mc_d_0_s_652 = {};
  int __f2dace_SOA_exner_ref_mc_d_1_s_653 = {};
  int __f2dace_SOA_exner_ref_mc_d_2_s_654 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_0_s_605 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_1_s_606 = {};
  int __f2dace_SOA_inv_ddqz_z_full_d_2_s_607 = {};
  int __f2dace_SOA_pg_edgeblk_d_0_s_676 = {};
  int __f2dace_SOA_pg_edgeidx_d_0_s_675 = {};
  int __f2dace_SOA_pg_exdist_d_0_s_670 = {};
  int __f2dace_SOA_pg_vertidx_d_0_s_677 = {};
  int __f2dace_SOA_rayleigh_vn_d_0_s_590 = {};
  int __f2dace_SOA_rho_ref_mc_d_0_s_655 = {};
  int __f2dace_SOA_rho_ref_mc_d_1_s_656 = {};
  int __f2dace_SOA_rho_ref_mc_d_2_s_657 = {};
  int __f2dace_SOA_rho_ref_me_d_0_s_658 = {};
  int __f2dace_SOA_rho_ref_me_d_1_s_659 = {};
  int __f2dace_SOA_rho_ref_me_d_2_s_660 = {};
  int __f2dace_SOA_theta_ref_ic_d_0_s_649 = {};
  int __f2dace_SOA_theta_ref_ic_d_1_s_650 = {};
  int __f2dace_SOA_theta_ref_ic_d_2_s_651 = {};
  int __f2dace_SOA_theta_ref_mc_d_0_s_643 = {};
  int __f2dace_SOA_theta_ref_mc_d_1_s_644 = {};
  int __f2dace_SOA_theta_ref_mc_d_2_s_645 = {};
  int __f2dace_SOA_theta_ref_me_d_0_s_646 = {};
  int __f2dace_SOA_theta_ref_me_d_1_s_647 = {};
  int __f2dace_SOA_theta_ref_me_d_2_s_648 = {};
  int __f2dace_SOA_vertidx_gradp_d_0_s_671 = {};
  int __f2dace_SOA_vertidx_gradp_d_1_s_672 = {};
  int __f2dace_SOA_vertidx_gradp_d_2_s_673 = {};
  int __f2dace_SOA_vertidx_gradp_d_3_s_674 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_0_s_591 = {};
  int __f2dace_SOA_vwind_expl_wgt_d_1_s_592 = {};
  int __f2dace_SOA_wgtfac_c_d_0_s_608 = {};
  int __f2dace_SOA_wgtfac_c_d_1_s_609 = {};
  int __f2dace_SOA_wgtfac_c_d_2_s_610 = {};
  int __f2dace_SOA_wgtfac_e_d_0_s_611 = {};
  int __f2dace_SOA_wgtfac_e_d_1_s_612 = {};
  int __f2dace_SOA_wgtfac_e_d_2_s_613 = {};
  int __f2dace_SOA_wgtfacq1_c_d_0_s_620 = {};
  int __f2dace_SOA_wgtfacq1_c_d_1_s_621 = {};
  int __f2dace_SOA_wgtfacq1_c_d_2_s_622 = {};
  int __f2dace_SOA_wgtfacq_c_d_0_s_614 = {};
  int __f2dace_SOA_wgtfacq_c_d_1_s_615 = {};
  int __f2dace_SOA_wgtfacq_c_d_2_s_616 = {};
  int __f2dace_SOA_wgtfacq_e_d_0_s_617 = {};
  int __f2dace_SOA_wgtfacq_e_d_1_s_618 = {};
  int __f2dace_SOA_wgtfacq_e_d_2_s_619 = {};
  int __f2dace_SOA_zdiff_gradp_d_0_s_632 = {};
  int __f2dace_SOA_zdiff_gradp_d_1_s_633 = {};
  int __f2dace_SOA_zdiff_gradp_d_2_s_634 = {};
  int __f2dace_SOA_zdiff_gradp_d_3_s_635 = {};
  int *bdy_mflx_e_blk = {};
  int bdy_mflx_e_dim = {};
  int *bdy_mflx_e_idx = {};
  double *coeff1_dwdz = {};
  double *coeff2_dwdz = {};
  double *coeff_gradekin = {};
  double *coeff_gradp = {};
  double *d2dexdz2_fac1_mc = {};
  double *d2dexdz2_fac2_mc = {};
  double *d_exner_dz_ref_ic = {};
  double *ddqz_z_full_e = {};
  double *ddqz_z_half = {};
  double *ddxn_z_full = {};
  double *ddxt_z_full = {};
  double *deepatmo_gradh_ifc = {};
  double *deepatmo_gradh_mc = {};
  double *deepatmo_invr_ifc = {};
  double *deepatmo_invr_mc = {};
  double *exner_exfac = {};
  double *exner_ref_mc = {};
  double *inv_ddqz_z_full = {};
  int *pg_edgeblk = {};
  int *pg_edgeidx = {};
  double *pg_exdist = {};
  int pg_listdim = {};
  int *pg_vertidx = {};
  double *rayleigh_vn = {};
  double *rho_ref_mc = {};
  double *rho_ref_me = {};
  double *theta_ref_ic = {};
  double *theta_ref_mc = {};
  double *theta_ref_me = {};
  int *vertidx_gradp = {};
  double *vwind_expl_wgt = {};
  double *wgtfac_c = {};
  double *wgtfac_e = {};
  double *wgtfacq1_c = {};
  double *wgtfacq_c = {};
  double *wgtfacq_e = {};
  double *zdiff_gradp = {};
};

struct t_nh_state {
  t_nh_diag *diag = {};
  t_nh_metrics *metrics = {};
  t_nh_ref *ref = {};
};

struct t_grid_domain_decomp_info {
  int __f2dace_SA_owner_mask_d_0_s_62 = {};
  int __f2dace_SA_owner_mask_d_1_s_63 = {};
  int __f2dace_SOA_owner_mask_d_0_s_62 = {};
  int __f2dace_SOA_owner_mask_d_1_s_63 = {};
  int *owner_mask = {};
};

struct t_grid_cells {
  int __f2dace_SA_area_d_0_s_214 = {};
  int __f2dace_SA_area_d_1_s_215 = {};
  int __f2dace_SA_edge_blk_d_0_s_211 = {};
  int __f2dace_SA_edge_blk_d_1_s_212 = {};
  int __f2dace_SA_edge_blk_d_2_s_213 = {};
  int __f2dace_SA_edge_idx_d_0_s_208 = {};
  int __f2dace_SA_edge_idx_d_1_s_209 = {};
  int __f2dace_SA_edge_idx_d_2_s_210 = {};
  int __f2dace_SA_end_blk_d_0_s_221 = {};
  int __f2dace_SA_end_blk_d_1_s_222 = {};
  int __f2dace_SA_end_block_d_0_s_223 = {};
  int __f2dace_SA_end_index_d_0_s_217 = {};
  int __f2dace_SA_neighbor_blk_d_0_s_205 = {};
  int __f2dace_SA_neighbor_blk_d_1_s_206 = {};
  int __f2dace_SA_neighbor_blk_d_2_s_207 = {};
  int __f2dace_SA_neighbor_idx_d_0_s_202 = {};
  int __f2dace_SA_neighbor_idx_d_1_s_203 = {};
  int __f2dace_SA_neighbor_idx_d_2_s_204 = {};
  int __f2dace_SA_start_blk_d_0_s_218 = {};
  int __f2dace_SA_start_blk_d_1_s_219 = {};
  int __f2dace_SA_start_block_d_0_s_220 = {};
  int __f2dace_SA_start_index_d_0_s_216 = {};
  int __f2dace_SOA_area_d_0_s_214 = {};
  int __f2dace_SOA_area_d_1_s_215 = {};
  int __f2dace_SOA_edge_blk_d_0_s_211 = {};
  int __f2dace_SOA_edge_blk_d_1_s_212 = {};
  int __f2dace_SOA_edge_blk_d_2_s_213 = {};
  int __f2dace_SOA_edge_idx_d_0_s_208 = {};
  int __f2dace_SOA_edge_idx_d_1_s_209 = {};
  int __f2dace_SOA_edge_idx_d_2_s_210 = {};
  int __f2dace_SOA_end_blk_d_0_s_221 = {};
  int __f2dace_SOA_end_blk_d_1_s_222 = {};
  int __f2dace_SOA_end_block_d_0_s_223 = {};
  int __f2dace_SOA_end_index_d_0_s_217 = {};
  int __f2dace_SOA_neighbor_blk_d_0_s_205 = {};
  int __f2dace_SOA_neighbor_blk_d_1_s_206 = {};
  int __f2dace_SOA_neighbor_blk_d_2_s_207 = {};
  int __f2dace_SOA_neighbor_idx_d_0_s_202 = {};
  int __f2dace_SOA_neighbor_idx_d_1_s_203 = {};
  int __f2dace_SOA_neighbor_idx_d_2_s_204 = {};
  int __f2dace_SOA_start_blk_d_0_s_218 = {};
  int __f2dace_SOA_start_blk_d_1_s_219 = {};
  int __f2dace_SOA_start_block_d_0_s_220 = {};
  int __f2dace_SOA_start_index_d_0_s_216 = {};
  double *area = {};
  t_grid_domain_decomp_info *decomp_info = {};
  int *edge_blk = {};
  int *edge_idx = {};
  int *end_blk = {};
  int *end_block = {};
  int *end_index = {};
  int *neighbor_blk = {};
  int *neighbor_idx = {};
  int *start_blk = {};
  int *start_block = {};
  int *start_index = {};
};

struct t_nh_prog {
  int __f2dace_SA_exner_d_0_s_524 = {};
  int __f2dace_SA_exner_d_1_s_525 = {};
  int __f2dace_SA_exner_d_2_s_526 = {};
  int __f2dace_SA_rho_d_0_s_521 = {};
  int __f2dace_SA_rho_d_1_s_522 = {};
  int __f2dace_SA_rho_d_2_s_523 = {};
  int __f2dace_SA_theta_v_d_0_s_527 = {};
  int __f2dace_SA_theta_v_d_1_s_528 = {};
  int __f2dace_SA_theta_v_d_2_s_529 = {};
  int __f2dace_SA_vn_d_0_s_518 = {};
  int __f2dace_SA_vn_d_1_s_519 = {};
  int __f2dace_SA_vn_d_2_s_520 = {};
  int __f2dace_SA_w_d_0_s_515 = {};
  int __f2dace_SA_w_d_1_s_516 = {};
  int __f2dace_SA_w_d_2_s_517 = {};
  int __f2dace_SOA_exner_d_0_s_524 = {};
  int __f2dace_SOA_exner_d_1_s_525 = {};
  int __f2dace_SOA_exner_d_2_s_526 = {};
  int __f2dace_SOA_rho_d_0_s_521 = {};
  int __f2dace_SOA_rho_d_1_s_522 = {};
  int __f2dace_SOA_rho_d_2_s_523 = {};
  int __f2dace_SOA_theta_v_d_0_s_527 = {};
  int __f2dace_SOA_theta_v_d_1_s_528 = {};
  int __f2dace_SOA_theta_v_d_2_s_529 = {};
  int __f2dace_SOA_vn_d_0_s_518 = {};
  int __f2dace_SOA_vn_d_1_s_519 = {};
  int __f2dace_SOA_vn_d_2_s_520 = {};
  int __f2dace_SOA_w_d_0_s_515 = {};
  int __f2dace_SOA_w_d_1_s_516 = {};
  int __f2dace_SOA_w_d_2_s_517 = {};
  double *exner = {};
  double *rho = {};
  double *theta_v = {};
  double *vn = {};
  double *w = {};
};

struct t_int_state {
  int __f2dace_SA_c_lin_e_d_0_s_93 = {};
  int __f2dace_SA_c_lin_e_d_1_s_94 = {};
  int __f2dace_SA_c_lin_e_d_2_s_95 = {};
  int __f2dace_SA_cells_aw_verts_d_0_s_99 = {};
  int __f2dace_SA_cells_aw_verts_d_1_s_100 = {};
  int __f2dace_SA_cells_aw_verts_d_2_s_101 = {};
  int __f2dace_SA_e_bln_c_s_d_0_s_96 = {};
  int __f2dace_SA_e_bln_c_s_d_1_s_97 = {};
  int __f2dace_SA_e_bln_c_s_d_2_s_98 = {};
  int __f2dace_SA_geofac_grdiv_d_0_s_105 = {};
  int __f2dace_SA_geofac_grdiv_d_1_s_106 = {};
  int __f2dace_SA_geofac_grdiv_d_2_s_107 = {};
  int __f2dace_SA_geofac_grg_d_0_s_114 = {};
  int __f2dace_SA_geofac_grg_d_1_s_115 = {};
  int __f2dace_SA_geofac_grg_d_2_s_116 = {};
  int __f2dace_SA_geofac_grg_d_3_s_117 = {};
  int __f2dace_SA_geofac_n2s_d_0_s_111 = {};
  int __f2dace_SA_geofac_n2s_d_1_s_112 = {};
  int __f2dace_SA_geofac_n2s_d_2_s_113 = {};
  int __f2dace_SA_geofac_rot_d_0_s_108 = {};
  int __f2dace_SA_geofac_rot_d_1_s_109 = {};
  int __f2dace_SA_geofac_rot_d_2_s_110 = {};
  int __f2dace_SA_pos_on_tplane_e_d_0_s_118 = {};
  int __f2dace_SA_pos_on_tplane_e_d_1_s_119 = {};
  int __f2dace_SA_pos_on_tplane_e_d_2_s_120 = {};
  int __f2dace_SA_pos_on_tplane_e_d_3_s_121 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_0_s_102 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_1_s_103 = {};
  int __f2dace_SA_rbf_vec_coeff_e_d_2_s_104 = {};
  int __f2dace_SOA_c_lin_e_d_0_s_93 = {};
  int __f2dace_SOA_c_lin_e_d_1_s_94 = {};
  int __f2dace_SOA_c_lin_e_d_2_s_95 = {};
  int __f2dace_SOA_cells_aw_verts_d_0_s_99 = {};
  int __f2dace_SOA_cells_aw_verts_d_1_s_100 = {};
  int __f2dace_SOA_cells_aw_verts_d_2_s_101 = {};
  int __f2dace_SOA_e_bln_c_s_d_0_s_96 = {};
  int __f2dace_SOA_e_bln_c_s_d_1_s_97 = {};
  int __f2dace_SOA_e_bln_c_s_d_2_s_98 = {};
  int __f2dace_SOA_geofac_grdiv_d_0_s_105 = {};
  int __f2dace_SOA_geofac_grdiv_d_1_s_106 = {};
  int __f2dace_SOA_geofac_grdiv_d_2_s_107 = {};
  int __f2dace_SOA_geofac_grg_d_0_s_114 = {};
  int __f2dace_SOA_geofac_grg_d_1_s_115 = {};
  int __f2dace_SOA_geofac_grg_d_2_s_116 = {};
  int __f2dace_SOA_geofac_grg_d_3_s_117 = {};
  int __f2dace_SOA_geofac_n2s_d_0_s_111 = {};
  int __f2dace_SOA_geofac_n2s_d_1_s_112 = {};
  int __f2dace_SOA_geofac_n2s_d_2_s_113 = {};
  int __f2dace_SOA_geofac_rot_d_0_s_108 = {};
  int __f2dace_SOA_geofac_rot_d_1_s_109 = {};
  int __f2dace_SOA_geofac_rot_d_2_s_110 = {};
  int __f2dace_SOA_pos_on_tplane_e_d_0_s_118 = {};
  int __f2dace_SOA_pos_on_tplane_e_d_1_s_119 = {};
  int __f2dace_SOA_pos_on_tplane_e_d_2_s_120 = {};
  int __f2dace_SOA_pos_on_tplane_e_d_3_s_121 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_0_s_102 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_1_s_103 = {};
  int __f2dace_SOA_rbf_vec_coeff_e_d_2_s_104 = {};
  double *c_lin_e = {};
  double *cells_aw_verts = {};
  double *e_bln_c_s = {};
  double *geofac_grdiv = {};
  double *geofac_grg = {};
  double *geofac_n2s = {};
  double *geofac_rot = {};
  double *pos_on_tplane_e = {};
  double *rbf_vec_coeff_e = {};
};

struct t_prepare_adv {
  int __f2dace_SA_mass_flx_me_d_0_s_705 = {};
  int __f2dace_SA_mass_flx_me_d_1_s_706 = {};
  int __f2dace_SA_mass_flx_me_d_2_s_707 = {};
  int __f2dace_SOA_mass_flx_me_d_0_s_705 = {};
  int __f2dace_SOA_mass_flx_me_d_1_s_706 = {};
  int __f2dace_SOA_mass_flx_me_d_2_s_707 = {};
  double *mass_flx_me = {};
};

struct t_patch {
  t_grid_cells *cells = {};
  t_grid_edges *edges = {};
  int id = {};
  int n_childdom = {};
  int nblks_c = {};
  int nblks_e = {};
  int nblks_v = {};
  int nlev = {};
  int nlevp1 = {};
  int nshift = {};
  t_grid_vertices *verts = {};
};

struct solve_nh_predictor_pre_state_t; // Forward declaration.

DACE_EXPORTED solve_nh_predictor_pre_state_t *
__dace_init_solve_nh_predictor_pre(
    double *bdy_divdamp, double *enh_divdamp_fac, global_data_type *global_data,
    t_int_state *p_int, t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew,
    t_nh_prog *p_nh_prog_nnow, t_patch *p_patch, t_prepare_adv *prep_adv,
    double *scal_divdamp, double *z_alpha, double *z_beta,
    double *z_contr_w_fl_l, double *z_dexner_dz_c, double *z_dwdz_dd,
    double *z_exner_ex_pr, double *z_exner_expl, double *z_exner_ic,
    double *z_flxdiv_mass, double *z_flxdiv_theta, double *z_grad_rth,
    double *z_graddiv2_vn, double *z_graddiv_vn, double *z_gradh_exner,
    double *z_hydro_corr, double *z_kin_hor_e, double *z_mflx_top, double *z_q,
    double *z_raylfac, double *z_rho_e, double *z_rho_expl, double *z_rho_v,
    double *z_rth_pr, double *z_th_ddz_exner_c, double *z_theta_v_e,
    double *z_theta_v_fl_e, double *z_theta_v_pr_ic, double *z_theta_v_v,
    double *z_vn_avg, double *z_vt_ie, double *z_w_concorr_mc,
    double *z_w_concorr_me, double *z_w_expl, int __f2dace_OPTIONAL_lacc,
    double alin, double aqdr, double bqdr, double df32, double df42,
    double distv_bary_1, double distv_bary_2, double dt_linintp_ubc,
    double dt_linintp_ubc_nnew, double dt_linintp_ubc_nnow, double dt_shift,
    double dthalf, double dtime, double dz32, double dz42, double dzlin,
    double dzqdr, int i_endblk, int i_endidx, int i_startblk, int i_startidx,
    int idyn_timestep, int ishift, int istep, int jb, int jc, int je, int jg,
    int jk, int jk_start, int jks, int jstep, int l_child_vertnest, int l_init,
    int l_recompute, int l_vert_nested, int lacc, int lclean_mflx,
    int lprep_adv, int lsave_mflx, int lvn_only, int lvn_pos, int nblks_gradp,
    int nlen_gradp, int nlev, int nlevp1, int nnew, int nnow, int nproma_gradp,
    int npromz_gradp, int nshift, int nshift_total, int ntl1, int ntl2,
    int nvar, double r_dtimensubsteps, double r_nsubsteps, int rl_end,
    int rl_start, double scal_divdamp_o2, double wgt_nnew_rth,
    double wgt_nnew_vel, double wgt_nnow_rth, double wgt_nnow_vel, double z_a,
    double z_b, double z_c, double z_d_vn_dmp, double z_d_vn_iau,
    double z_ddt_vn_apc, double z_ddt_vn_cor, double z_ddt_vn_dyn,
    double z_ddt_vn_pgr, double z_ddt_vn_ray, double z_g, double z_gamma,
    double z_ntdistv_bary_1, double z_ntdistv_bary_2, double z_rho_tavg,
    double z_rho_tavg_m1, double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);
DACE_EXPORTED int
__dace_exit_solve_nh_predictor_pre(solve_nh_predictor_pre_state_t *__state);
DACE_EXPORTED void __program_solve_nh_predictor_pre(
    solve_nh_predictor_pre_state_t *__state, double *bdy_divdamp,
    double *enh_divdamp_fac, global_data_type *global_data, t_int_state *p_int,
    t_nh_state *p_nh, t_nh_prog *p_nh_prog_nnew, t_nh_prog *p_nh_prog_nnow,
    t_patch *p_patch, t_prepare_adv *prep_adv, double *scal_divdamp,
    double *z_alpha, double *z_beta, double *z_contr_w_fl_l,
    double *z_dexner_dz_c, double *z_dwdz_dd, double *z_exner_ex_pr,
    double *z_exner_expl, double *z_exner_ic, double *z_flxdiv_mass,
    double *z_flxdiv_theta, double *z_grad_rth, double *z_graddiv2_vn,
    double *z_graddiv_vn, double *z_gradh_exner, double *z_hydro_corr,
    double *z_kin_hor_e, double *z_mflx_top, double *z_q, double *z_raylfac,
    double *z_rho_e, double *z_rho_expl, double *z_rho_v, double *z_rth_pr,
    double *z_th_ddz_exner_c, double *z_theta_v_e, double *z_theta_v_fl_e,
    double *z_theta_v_pr_ic, double *z_theta_v_v, double *z_vn_avg,
    double *z_vt_ie, double *z_w_concorr_mc, double *z_w_concorr_me,
    double *z_w_expl, int __f2dace_OPTIONAL_lacc, double alin, double aqdr,
    double bqdr, double df32, double df42, double distv_bary_1,
    double distv_bary_2, double dt_linintp_ubc, double dt_linintp_ubc_nnew,
    double dt_linintp_ubc_nnow, double dt_shift, double dthalf, double dtime,
    double dz32, double dz42, double dzlin, double dzqdr, int i_endblk,
    int i_endidx, int i_startblk, int i_startidx, int idyn_timestep, int ishift,
    int istep, int jb, int jc, int je, int jg, int jk, int jk_start, int jks,
    int jstep, int l_child_vertnest, int l_init, int l_recompute,
    int l_vert_nested, int lacc, int lclean_mflx, int lprep_adv, int lsave_mflx,
    int lvn_only, int lvn_pos, int nblks_gradp, int nlen_gradp, int nlev,
    int nlevp1, int nnew, int nnow, int nproma_gradp, int npromz_gradp,
    int nshift, int nshift_total, int ntl1, int ntl2, int nvar,
    double r_dtimensubsteps, double r_nsubsteps, int rl_end, int rl_start,
    double scal_divdamp_o2, double wgt_nnew_rth, double wgt_nnew_vel,
    double wgt_nnow_rth, double wgt_nnow_vel, double z_a, double z_b,
    double z_c, double z_d_vn_dmp, double z_d_vn_iau, double z_ddt_vn_apc,
    double z_ddt_vn_cor, double z_ddt_vn_dyn, double z_ddt_vn_pgr,
    double z_ddt_vn_ray, double z_g, double z_gamma, double z_ntdistv_bary_1,
    double z_ntdistv_bary_2, double z_rho_tavg, double z_rho_tavg_m1,
    double z_theta1, double z_theta2, double z_theta_tavg,
    double z_theta_tavg_m1, double z_theta_v_pr_mc, double z_theta_v_pr_mc_m1,
    double z_w_backtraj, double zf);

#endif // __DACE_CODEGEN_SOLVE_NH_PREDICTOR_PRE__
} // namespace predictor_pre