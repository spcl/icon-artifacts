#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#include "predictor_pre_serde.h"
//#include "predictor_post_serde.h"
//#include "corrector_pre_serde.h"
//#include "corrector_post_serde.h"
namespace serde = ::predictor_pre;

#include "utils.h"
using namespace standalone_utils;

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

    auto fut_global_data = spawn(pool, [&] {
      return t0_t1_pair<global_data_type>(ROOT, "global_data", n);
    });
    auto fut_p_diag =
        spawn(pool, [&] { return t0_t1_pair<t_nh_diag>(ROOT, "p_diag", n); });
    auto fut_p_int =
        spawn(pool, [&] { return read<t_int_state>(ROOT, "p_int", n); });
    auto fut_p_metrics = spawn(
        pool, [&] { return t0_t1_pair<t_nh_metrics>(ROOT, "p_metrics", n); });
    auto fut_p_patch =
        spawn(pool, [&] { return read<t_patch>(ROOT, "p_patch", n); });
    auto fut_p_prog =
        spawn(pool, [&] { return t0_t1_pair<t_nh_prog>(ROOT, "p_prog", n); });
    auto fut_z_kin_hor_e = spawn(
        pool, [&] { return t0_t1_pair<double*>(ROOT, "z_kin_hor_e", n); });
    auto fut_z_vt_ie =
        spawn(pool, [&] { return t0_t1_pair<double*>(ROOT, "z_vt_ie", n); });
    auto fut_z_w_concorr = spawn(
        pool, [&] { return t0_t1_pair<double*>(ROOT, "z_w_concorr_me", n); });
    auto fut_istep = spawn(pool, [&] { return read<int>(ROOT, "istep", n); });
    auto fut_ldeepatmo =
        spawn(pool, [&] { return read<int>(ROOT, "ldeepatmo", n); });
    auto fut_lvn_only =
        spawn(pool, [&] { return read<int>(ROOT, "lvn_only", n); });
    auto fut_ntnd = spawn(pool, [&] { return read<int>(ROOT, "ntnd", n); });
    auto fut_dt_linintp =
        spawn(pool, [&] { return read<double>(ROOT, "dt_linintp_ubc", n); });
    auto fut_dtime =
        spawn(pool, [&] { return read<double>(ROOT, "dtime", n); });
    pool.clear();

    auto global_data_pair = fut_global_data.get();
    auto& global_data = std::get<0>(global_data_pair);
    auto& global_data_want = std::get<1>(global_data_pair);

    auto p_diag_pair = fut_p_diag.get();
    auto& p_diag = std::get<0>(p_diag_pair);
    auto& p_diag_want = std::get<1>(p_diag_pair);

    auto p_int = fut_p_int.get();

    auto p_metrics_pair = fut_p_metrics.get();
    auto& p_metrics = std::get<0>(p_metrics_pair);
    auto& p_metrics_want = std::get<1>(p_metrics_pair);

    auto p_patch = fut_p_patch.get();

    auto p_prog_pair = fut_p_prog.get();
    auto& p_prog = std::get<0>(p_prog_pair);
    auto& p_prog_want = std::get<1>(p_prog_pair);

    auto z_kin_hor_e_pair = fut_z_kin_hor_e.get();
    auto& z_kin_hor_e = std::get<0>(z_kin_hor_e_pair);
    auto& z_kin_hor_e_want = std::get<1>(z_kin_hor_e_pair);

    auto z_vt_ie_pair = fut_z_vt_ie.get();
    auto& z_vt_ie = std::get<0>(z_vt_ie_pair);
    auto& z_vt_ie_want = std::get<1>(z_vt_ie_pair);

    auto z_w_concorr_me_pair = fut_z_w_concorr.get();
    auto& z_w_concorr_me = std::get<0>(z_w_concorr_me_pair);
    auto& z_w_concorr_me_want = std::get<1>(z_w_concorr_me_pair);
    int istep = fut_istep.get();
    int ldeepatmo = fut_ldeepatmo.get();
    int lvn_only = fut_lvn_only.get();
    int ntnd = fut_ntnd.get();
    double dt_linintp_ubc = fut_dt_linintp.get();
    double dtime = fut_dtime.get();

    acerr() << "All data read..." << std::endl;

    if (ldeepatmo != 0) {
      throw std::runtime_error("ldeepatmo is not 0");
    }
    if (global_data.lextra_diffu != 1) {
      throw std::runtime_error("lextra_diffu is not 1");
    }
    if (istep != 1 && istep != 2) {
      throw std::runtime_error("istep not 1 or 2");
    }
    if (lvn_only != 0 && lvn_only != 1) {
      throw std::runtime_error("lvn_only not 0 or 1");
    }
    acout() << "Step " << n
            << " variables, extra_diffu: " << global_data.lextra_diffu
            << ", istep: ";
    acout() << istep << ", lvn_only: " << lvn_only
            << ", ldeepatmo: " << ldeepatmo << std::endl;

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