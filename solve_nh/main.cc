#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#include "solve_nh_parts.h"

#include "corrector_post_serde.h"
#include "corrector_pre_serde.h"
#include "predictor_post_serde.h"
#include "predictor_pre_serde.h"

#include "utils.h"
using namespace standalone_utils;
namespace predictor_pre {
GENERATE_ALL_SERIALIZATION_HELPERS()
} // namespace predictor_pre
namespace predictor_post {
GENERATE_ALL_SERIALIZATION_HELPERS()
} // namespace predictor_post
namespace corrector_pre {
GENERATE_ALL_SERIALIZATION_HELPERS()
} // namespace corrector_pre
namespace corrector_post {
GENERATE_ALL_SERIALIZATION_HELPERS()
} // namespace corrector_post

#include "macro.h"

#include "flags.h"

int main(int argc, char *argv[]) {
  const flags::args args(argc, argv);

  const auto root =
      args.get<std::string>("data", "/Users/pmz/Downloads/dycore-data/");
  const std::filesystem::path ROOT{root};
  acerr() << "Will be reading data from: " << ROOT << std::endl;
  const std::filesystem::path DUMP =
      std::filesystem::current_path() / "gotwant" / ROOT.filename();
  std::error_code ec;
  if (!std::filesystem::create_directories(DUMP, ec) && ec) {
    acerr() << "Failed to create directory: " << ec.message() << std::endl;
  }
  acerr() << "Will be writing got and want files to: " << DUMP << std::endl;

  std::vector<int> ns;
  for (const auto ts : args.positional()) {
    ns.push_back(std::stoi(std::string(ts)));
  }
  if (ns.empty()) {
    ns = {20};
  }

  const int rep = 1;

  for (int n : ns) {
    // PREDICTOR PRE
    {
      acerr() << "Reading data for " << n << "..." << std::endl;

      std::vector<std::jthread> pool;
      SPAWN_ALL_READERS(prepre, predictor_pre);
      pool.clear();
      UNWRAP_ALL_DATA_PAIRS();

      acerr() << "All data read..." << std::endl;

      auto *h = __dace_init_solve_nh_predictor_pre(
          bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      __program_solve_nh_predictor_pre(
          h, bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      int err = __dace_exit_solve_nh_predictor_pre(h);
      if (err != 0) {
        acerr() << "Error in __dace_exit_solve_nh_predictor_pre: " << err
                << std::endl;
        return err;
      }
      acout() << "Step " << n << " done." << std::endl;

      SPAWN_ALL_WRITERS(prepre, predictor_pre);
      pool.clear();
    }

    // PREDICTOR POST
    {
      acerr() << "Reading data for " << n << "..." << std::endl;

      std::vector<std::jthread> pool;
      SPAWN_ALL_READERS(prepost, predictor_post);
      pool.clear();
      UNWRAP_ALL_DATA_PAIRS();

      acerr() << "All data read..." << std::endl;

      auto *h = __dace_init_solve_nh_predictor_post(
          bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      __program_solve_nh_predictor_post(
          h, bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      int err = __dace_exit_solve_nh_predictor_post(h);
      if (err != 0) {
        acerr() << "Error in __dace_exit_solve_nh_predictor_post: " << err
                << std::endl;
        return err;
      }
      acout() << "Step " << n << " done." << std::endl;

      SPAWN_ALL_WRITERS(prepost, predictor_post);
      pool.clear();
    }

    // CORRECTOR PRE
    {
      acerr() << "Reading data for " << n << "..." << std::endl;

      std::vector<std::jthread> pool;
      SPAWN_ALL_READERS(corpre, corrector_pre);
      pool.clear();
      UNWRAP_ALL_DATA_PAIRS();

      acerr() << "All data read..." << std::endl;

      auto *h = __dace_init_solve_nh_corrector_pre(
          bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      __program_solve_nh_corrector_pre(
          h, bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      int err = __dace_exit_solve_nh_corrector_pre(h);
      if (err != 0) {
        acerr() << "Error in __dace_exit_solve_nh_corrector_pre: " << err
                << std::endl;
        return err;
      }
      acout() << "Step " << n << " done." << std::endl;

      SPAWN_ALL_WRITERS(corpre, corrector_pre);
      pool.clear();
    }

    // CORRECTOR POST
    {
      acerr() << "Reading data for " << n << "..." << std::endl;

      std::vector<std::jthread> pool;
      SPAWN_ALL_READERS(corpost, corrector_post);
      pool.clear();
      UNWRAP_ALL_DATA_PAIRS();

      acerr() << "All data read..." << std::endl;

      auto *h = __dace_init_solve_nh_corrector_post(
          bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      __program_solve_nh_corrector_post(
          h, bdy_divdamp_in, enh_divdamp_fac_in, &global_data_in, &p_int_in,
          &p_nh_in, &p_nh_prog_nnow_in, &p_nh_prog_nnew_in, &p_patch_in, &prep_adv_in, scal_divdamp_in, z_alpha_in,
          z_beta_in, z_contr_w_fl_l_in, z_dexner_dz_c_in, z_dwdz_dd_in,
          z_exner_ex_pr_in, z_exner_expl_in, z_exner_ic_in, z_flxdiv_mass_in,
          z_flxdiv_theta_in, z_grad_rth_in, z_graddiv2_vn_in, z_graddiv_vn_in,
          z_gradh_exner_in, z_hydro_corr_in, z_kin_hor_e_in, z_mflx_top_in,
          z_q_in, z_raylfac_in, z_rho_e_in, z_rho_expl_in, z_rho_v_in,
          z_rth_pr_in, z_th_ddz_exner_c_in, z_theta_v_e_in, z_theta_v_fl_e_in,
          z_theta_v_pr_ic_in, z_theta_v_v_in, z_vn_avg_in, z_vt_ie_in,
          z_w_concorr_mc_in, z_w_concorr_me_in, z_w_expl_in,
          true /*__f2dace_OPTIONAL_lacc*/, alin_in, aqdr_in, bqdr_in, df32_in,
          df42_in, distv_bary_1_in, distv_bary_2_in, dt_linintp_ubc_in,
          dt_linintp_ubc_nnew_in, dt_linintp_ubc_nnow_in, dt_shift_in,
          dthalf_in, dtime_in, dz32_in, dz42_in, dzlin_in, dzqdr_in,
          i_endblk_in, i_endidx_in, i_startblk_in, i_startidx_in,
          idyn_timestep_in, ishift_in, istep_in, jb_in, jc_in, je_in, jg_in,
          jk_in, jk_start_in, jks_in, jstep_in, l_child_vertnest_in, l_init_in,
          l_recompute_in, l_vert_nested_in, lacc_in, lclean_mflx_in,
          lprep_adv_in, lsave_mflx_in, lvn_only_in, lvn_pos_in, nblks_gradp_in,
          nlen_gradp_in, nlev_in, nlevp1_in, nnew_in, nnow_in, nproma_gradp_in,
          npromz_gradp_in, nshift_in, nshift_total_in, ntl1_in, ntl2_in,
          nvar_in, r_dtimensubsteps_in, r_nsubsteps_in, rl_end_in, rl_start_in,
          scal_divdamp_o2_in, wgt_nnew_rth_in, wgt_nnew_vel_in, wgt_nnow_rth_in,
          wgt_nnow_vel_in, z_a_in, z_b_in, z_c_in, z_d_vn_dmp_in, z_d_vn_iau_in,
          z_ddt_vn_apc_in, z_ddt_vn_cor_in, z_ddt_vn_dyn_in, z_ddt_vn_pgr_in,
          z_ddt_vn_ray_in, z_g_in, z_gamma_in, z_ntdistv_bary_1_in,
          z_ntdistv_bary_2_in, z_rho_tavg_in, z_rho_tavg_m1_in, z_theta1_in,
          z_theta2_in, z_theta_tavg_in, z_theta_tavg_m1_in, z_theta_v_pr_mc_in,
          z_theta_v_pr_mc_m1_in, z_w_backtraj_in, zf_in);
      int err = __dace_exit_solve_nh_corrector_post(h);
      if (err != 0) {
        acerr() << "Error in __dace_exit_solve_nh_corrector_post: " << err
                << std::endl;
        return err;
      }
      acout() << "Step " << n << " done." << std::endl;

      SPAWN_ALL_WRITERS(corpost, corrector_post);
      pool.clear();
    }
  }
  return EXIT_SUCCESS;
}