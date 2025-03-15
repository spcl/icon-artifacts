#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "serde_velocity.h"
#include "velocity_tendencies.h"

int main() {
  const std::filesystem::path ROOT{"data"};
  const int max_n = 5;

  for (int n = 1; n <= max_n; ++n) {
    std::cerr << "Reading data for " << n << "..." << std::endl;

    global_data_type global_data;
    {
      std::ifstream data(ROOT / ("global_data_t0." + std::to_string(n) + ".data"));
      serde::deserialize_global_data(&global_data, data);
    }
    global_data_type global_data_want;
    {
      std::ifstream data(ROOT / ("global_data_t1." + std::to_string(n) + ".data"));
      serde::deserialize_global_data(&global_data_want, data);
    }

    t_nh_diag p_diag;
    {
      std::ifstream data(ROOT / ("p_diag_t0." + std::to_string(n) + ".data"));
      serde::deserialize(&p_diag, data);
    }
    t_nh_diag p_diag_want;
    {
      std::ifstream data(ROOT / ("p_diag_t1." + std::to_string(n) + ".data"));
      serde::deserialize(&p_diag_want, data);
    }

    t_int_state p_int;
    {
      std::ifstream data(ROOT / ("p_int." + std::to_string(n) + ".data"));
      serde::deserialize(&p_int, data);
    }

    t_nh_metrics p_metrics;
    {
      std::ifstream data(ROOT / ("p_metrics_t0." + std::to_string(n) + ".data"));
      serde::deserialize(&p_metrics, data);
    }
    t_nh_metrics p_metrics_want;
    {
      std::ifstream data(ROOT / ("p_metrics_t1." + std::to_string(n) + ".data"));
      serde::deserialize(&p_metrics_want, data);
    }

    t_patch p_patch;
    {
      std::ifstream data(ROOT / ("p_patch." + std::to_string(n) + ".data"));
      serde::deserialize(&p_patch, data);
    }

    t_nh_prog p_prog;
    {
      std::ifstream data(ROOT / ("p_prog_t0." + std::to_string(n) + ".data"));
      serde::deserialize(&p_prog, data);
    }
    t_nh_prog p_prog_want;
    {
      std::ifstream data(ROOT / ("p_prog_t1." + std::to_string(n) + ".data"));
      serde::deserialize(&p_prog_want, data);
    }

    double *z_kin_hor_e = nullptr;
    {
      std::ifstream data(ROOT / ("z_kin_hor_e_t0." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_kin_hor_e = arr;
    }
    double *z_kin_hor_e_want = nullptr;
    {
      std::ifstream data(ROOT / ("z_kin_hor_e_t1." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_kin_hor_e_want = arr;
    }

    double *z_vt_ie = nullptr;
    {
      std::ifstream data(ROOT / ("z_vt_ie_t0." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_vt_ie = arr;
    }
    double *z_vt_ie_want = nullptr;
    {
      std::ifstream data(ROOT / ("z_vt_ie_t1." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_vt_ie_want = arr;
    }

    double *z_w_concorr_me = nullptr;
    {
      std::ifstream data(ROOT / ("z_w_concorr_me_t0." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_w_concorr_me = arr;
    }
    double *z_w_concorr_me_want = nullptr;
    {
      std::ifstream data(ROOT / ("z_w_concorr_me_t1." + std::to_string(n) + ".data"));
      auto [m, arr] = serde::read_array<double>(data);
      z_w_concorr_me_want = arr;
    }

    int istep, ldeepatmo, lvn_only, ntnd;
    {
      std::ifstream data(ROOT / ("istep." + std::to_string(n) + ".data"));
      serde::deserialize(&istep, data);
    }
    {
      std::ifstream data(ROOT / ("ldeepatmo." + std::to_string(n) + ".data"));
      serde::deserialize(&ldeepatmo, data);
    }
    {
      std::ifstream data(ROOT / ("lvn_only." + std::to_string(n) + ".data"));
      serde::deserialize(&lvn_only, data);
    }
    {
      std::ifstream data(ROOT / ("ntnd." + std::to_string(n) + ".data"));
      serde::deserialize(&ntnd, data);
    }
    double dt_linintp_ubc, dtime;
    {
      std::ifstream data(ROOT / ("dt_linintp_ubc." + std::to_string(n) + ".data"));
      serde::deserialize(&dt_linintp_ubc, data);
    }
    {
      std::ifstream data(ROOT / ("dtime." + std::to_string(n) + ".data"));
      serde::deserialize(&dtime, data);
    }

    std::cerr << "All data read..." << std::endl;

    auto *h = __dace_init_velocity_tendencies(
        &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog, z_kin_hor_e,
        z_vt_ie, z_w_concorr_me,
        /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
        /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(2),
        /*__f2dace_A_z_vt_ie_d_0_s_160=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
        /*__f2dace_A_z_vt_ie_d_1_s_161=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(2),
        /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
        /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(2),
        /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(0),
        /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(1),
        /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(2),
        /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(0),
        /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(1),
        /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(2),
        /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(0),
        /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(1),
        /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2), dt_linintp_ubc,
        dtime, istep, ldeepatmo, lvn_only, ntnd);
    __program_velocity_tendencies(
        h, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
        z_kin_hor_e, z_vt_ie, z_w_concorr_me,
        /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
        /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(2),
        /*__f2dace_A_z_vt_ie_d_0_s_160=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
        /*__f2dace_A_z_vt_ie_d_1_s_161=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
        serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(2),
        /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
        /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(2),
        /*__f2dace_OA_z_kin_hor_e_d_0_s_157=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(0),
        /*__f2dace_OA_z_kin_hor_e_d_1_s_158=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(1),
        /*__f2dace_OA_z_kin_hor_e_d_2_s_159=*/
        serde::ARRAY_META_DICT()->at(z_kin_hor_e).lbound.at(2),
        /*__f2dace_OA_z_vt_ie_d_0_s_160=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(0),
        /*__f2dace_OA_z_vt_ie_d_1_s_161=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(1),
        /*__f2dace_OA_z_vt_ie_d_2_s_162=*/
        serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(2),
        /*__f2dace_OA_z_w_concorr_me_d_0_s_154=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(0),
        /*__f2dace_OA_z_w_concorr_me_d_1_s_155=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(1),
        /*__f2dace_OA_z_w_concorr_me_d_2_s_156=*/
        serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2), dt_linintp_ubc,
        dtime, istep, ldeepatmo, lvn_only, ntnd);

    __dace_exit_velocity_tendencies(h);

    {
      std::ofstream data("global_data_" + std::to_string(n) + ".got");
      data << serde::serialize_global_data(&global_data) << std::endl;
    }
    {
      std::ofstream data("global_data_" + std::to_string(n) + ".want");
      data << serde::serialize_global_data(&global_data_want) << std::endl;
    }
    {
      std::ofstream data("p_diag_" + std::to_string(n) + ".got");
      data << serde::serialize(&p_diag) << std::endl;
    }
    {
      std::ofstream data("p_diag_" + std::to_string(n) + ".want");
      data << serde::serialize(&p_diag_want) << std::endl;
    }
    {
      std::ofstream data("p_metrics_" + std::to_string(n) + ".got");
      data << serde::serialize(&p_metrics) << std::endl;
    }
    {
      std::ofstream data("p_metrics_" + std::to_string(n) + ".want");
      data << serde::serialize(&p_metrics_want) << std::endl;
    }
    {
      std::ofstream data("p_prog_" + std::to_string(n) + ".got");
      data << serde::serialize(&p_prog) << std::endl;
    }
    {
      std::ofstream data("p_prog_" + std::to_string(n) + ".want");
      data << serde::serialize(&p_prog_want) << std::endl;
    }
    {
      std::ofstream data("z_kin_hor_e_" + std::to_string(n) + ".got");
      data << serde::serialize_array(z_kin_hor_e) << std::endl;
    }
    {
      std::ofstream data("z_kin_hor_e_" + std::to_string(n) + ".want");
      data << serde::serialize_array(z_kin_hor_e_want) << std::endl;
    }
    {
      std::ofstream data("z_vt_ie_" + std::to_string(n) + ".got");
      data << serde::serialize_array(z_vt_ie) << std::endl;
    }
    {
      std::ofstream data("z_vt_ie_" + std::to_string(n) + ".want");
      data << serde::serialize_array(z_vt_ie_want) << std::endl;
    }
    {
      std::ofstream data("z_w_concorr_me_" + std::to_string(n) + ".got");
      data << serde::serialize_array(z_w_concorr_me) << std::endl;
    }
    {
      std::ofstream data("z_w_concorr_me_" + std::to_string(n) + ".want");
      data << serde::serialize_array(z_w_concorr_me_want) << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
