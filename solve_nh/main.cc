#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

// #include "predictor_pre_serde.h"
#include "predictor_post_serde.h"
//#include "corrector_pre_serde.h"
//#include "corrector_post_serde.h"
namespace serde = ::predictor_post;

#include "utils.h"
using namespace standalone_utils;

#include "macro.h"

#include "flags.h"

int main(int argc, char* argv[]) {
  const flags::args args(argc, argv);

  const auto root = args.get<std::string>("data", "/Users/pmz/Downloads/dycore-data/");
  const std::filesystem::path ROOT{root};
  acerr() << "Will be reading data from: " << ROOT << std::endl;
  const std::filesystem::path DUMP = std::filesystem::current_path() / "gotwant" / ROOT.filename();
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
    acerr() << "Reading data for " << n << "..." << std::endl;

    std::vector<std::jthread> pool;
    SPAWN_ALL_DIAGS(prepost);
    pool.clear();
    UNWRAP_ALL_DIAGS;

    acerr() << "All data read..." << std::endl;

    // if (ldeepatmo != 0) {
    //   throw std::runtime_error("ldeepatmo is not 0");
    // }
    // if (global_data.lextra_diffu != 1) {
    //   throw std::runtime_error("lextra_diffu is not 1");
    // }
    // if (istep != 1 && istep != 2) {
    //   throw std::runtime_error("istep not 1 or 2");
    // }
    // if (lvn_only != 0 && lvn_only != 1) {
    //   throw std::runtime_error("lvn_only not 0 or 1");
    // }
    // acout() << "Step " << n
    //         << " variables, extra_diffu: " << global_data.lextra_diffu
    //         << ", istep: ";
    // acout() << istep << ", lvn_only: " << lvn_only
    //         << ", ldeepatmo: " << ldeepatmo << std::endl;

    // if (lvn_only == 1 && istep == 1) {
    //   auto* h_1_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    //       &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //       /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //       /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //       /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //       /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2),
    //       /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(0),
    //       /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(1),
    //       /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(2),
    //       dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
    //       h_1_1, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //       /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //       /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //       /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //       /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2),
    //       /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(0),
    //       /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(1),
    //       /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(2),
    //       dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   int err =
    //       __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(h_1_1);

    // } else if (lvn_only == 0 && istep == 1) {
    //   auto* h_0_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    //       &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //       /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //       /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //       /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //       /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2),
    //       /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(0),
    //       /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(1),
    //       /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(2),
    //       dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   for (int j = 0; j < rep; j++) {
    //     __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
    //         h_0_1, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //         z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //         /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //         /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //         /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //         /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //         /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //         serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //         /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //         serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //         /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //         /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //         /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //         /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //         /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //         /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2),
    //         /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
    //         serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(0),
    //         /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
    //         serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(1),
    //         /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
    //         serde::ARRAY_META_DICT_AT(z_w_concorr_me).lbound.at(2),
    //         dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   }
    //   int err =
    //       __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(h_0_1);

    // } else if (lvn_only == 1 && istep == 2) {
    //   auto* h_1_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    //       &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //       /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(2),
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2), dt_linintp_ubc,
    //       dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
    //       h_1_2, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),

    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(0),
    //       /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(1),
    //       serde::ARRAY_META_DICT_AT(z_w_concorr_me).size.at(2),
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2), dt_linintp_ubc,
    //       dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   int err =
    //       __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(h_1_2);

    // } else if (lvn_only == 0 && istep == 2) {
    //   auto* h_0_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    //       &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //       z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //       /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //       /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //       /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //       /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //       /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //       /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //       /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //       /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //       serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //       /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //       /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //       /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //       serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2), dt_linintp_ubc,
    //       dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   for (int j = 0; j < rep; j++) {
    //     __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
    //         h_0_2, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
    //         z_kin_hor_e, z_vt_ie, z_w_concorr_me,
    //         /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(0),
    //         /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).size.at(1),
    //         /*__f2dace_A_z_vt_ie_d_0_s_160=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(0),
    //         /*__f2dace_A_z_vt_ie_d_1_s_161=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).size.at(1),
    //         /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
    //         /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(0),
    //         /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(1),
    //         /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
    //         serde::ARRAY_META_DICT_AT(z_kin_hor_e).lbound.at(2),
    //         /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(0),
    //         /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(1),
    //         /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
    //         serde::ARRAY_META_DICT_AT(z_vt_ie).lbound.at(2), dt_linintp_ubc,
    //         dtime, istep, ldeepatmo, lvn_only, ntnd);
    //   }
    //   int err =
    //       __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(h_0_2);

    // } else {
    //   throw std::runtime_error("Law of Logic and Mathematics violated");
    // }
    // acout() << "Step " << n << " done." << std::endl;

    // pool.emplace_back([&] {
    //   got_want_pair<global_data_type>(global_data, global_data_want,
    //                                   "global_data", n, DUMP);
    // });
    // pool.emplace_back(
    //     [&] { got_want_pair<t_nh_diag>(p_diag, p_diag_want, "p_diag", n, DUMP); });
    // pool.emplace_back([&] {
    //   got_want_pair<t_nh_metrics>(p_metrics, p_metrics_want, "p_metrics", n, DUMP);
    // });
    // pool.emplace_back(
    //     [&] { got_want_pair<t_nh_prog>(p_prog, p_prog_want, "p_prog", n, DUMP); });
    // pool.emplace_back([&] {
    //   got_want_pair<double*>(z_kin_hor_e, z_kin_hor_e_want, "z_kin_hor_e", n, DUMP);
    // });
    // pool.emplace_back(
    //     [&] { got_want_pair<double*>(z_vt_ie, z_vt_ie_want, "z_vt_ie", n, DUMP); });
    // pool.emplace_back([&] {
    //   got_want_pair<double*>(z_w_concorr_me, z_w_concorr_me_want,
    //                          "z_w_concorr_me", n, DUMP);
    // });
    pool.clear();
  }
  return EXIT_SUCCESS;
}