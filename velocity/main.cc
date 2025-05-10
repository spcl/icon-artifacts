#include <filesystem>
#include <fstream>
#include <future>
#include <iostream>
#include <string>
#include <thread>

#include "serde.h"
#include "velocity_tendencies.h"

std::ifstream open_ifstream(const std::filesystem::path& ROOT,
                            const std::string& name, int timestep) {
  const std::filesystem::path datapath =
      ROOT / (name + "." + std::to_string(timestep) + ".data");
  if (!std::filesystem::exists(datapath)) {
    std::cerr << "Cannot find: " << datapath << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Reading from: " << datapath << std::endl;
  return {datapath};
}

template <typename T>
std::enable_if_t<std::is_pointer_v<T>, T> read(
    const std::filesystem::path& ROOT, const std::string& name, int timestep) {
  auto data = open_ifstream(ROOT, name, timestep);
  using Pointee = std::remove_pointer_t<T>;
  auto [m, arr] = serde::read_array<Pointee>(data);
  return arr;
}

template <typename T>
std::enable_if_t<std::is_class_v<T> || std::is_arithmetic_v<T>, T> read(
    const std::filesystem::path& ROOT, const std::string& name, int timestep) {
  auto data = open_ifstream(ROOT, name, timestep);
  T t{};
  serde::deserialize(&t, data);
  return t;
}

template <>
global_data_type read<global_data_type>(const std::filesystem::path& ROOT,
                                        const std::string& name, int timestep) {
  auto data = open_ifstream(ROOT, name, timestep);
  global_data_type t{};
  serde::deserialize_global_data(&t, data);
  return t;
}

template <typename T>
std::pair<T, T> t0_t1_pair(const std::filesystem::path& ROOT,
                           const std::string& name, int timestep) {
  auto t0 = read<T>(ROOT, name + ".t0", timestep);
  auto t1 = read<T>(ROOT, name + ".t1", timestep);
  return {t0, t1};
}

template <typename T>
std::enable_if_t<std::is_pointer_v<T>, void> got_want_pair(
    T got, T want, const std::string& name, int timestep) {
  {
    std::ofstream data(name + "_" + std::to_string(timestep) + ".got");
    data << serde::serialize_array(got) << std::endl;
  }
  {
    std::ofstream data(name + "_" + std::to_string(timestep) + ".want");
    data << serde::serialize_array(want) << std::endl;
  }
}

std::ofstream open_ofstream(const std::string& name, int timestep,
                            const std::string& suffix) {
  const std::filesystem::path datapath(name + "_" + std::to_string(timestep) +
                                       "." + suffix);
  std::cout << "Writing to: " << datapath << std::endl;
  return {datapath};
}

template <typename T>
std::enable_if_t<std::is_class_v<T> || std::is_arithmetic_v<T>, void>
got_want_pair(const T& got, const T& want, const std::string& name,
              int timestep) {
  open_ofstream(name, timestep, "got") << serde::serialize(&got) << std::endl;
  open_ofstream(name, timestep, "want") << serde::serialize(&want) << std::endl;
}

template <>
void got_want_pair(const global_data_type& got, const global_data_type& want,
                   const std::string& name, int timestep) {
  open_ofstream(name, timestep, "got")
      << serde::serialize_global_data(&got) << std::endl;
  open_ofstream(name, timestep, "want")
      << serde::serialize_global_data(&want) << std::endl;
}

template <typename F>
auto spawn(std::vector<std::jthread>& pool, F&& f) {
  using R = std::invoke_result_t<F>;

  std::promise<R> prom;
  std::future<R> fut = prom.get_future();

  pool.emplace_back([p = std::move(prom), func = std::forward<F>(f)]() mutable {
    try {
      p.set_value(func());
    } catch (...) {
      p.set_exception(std::current_exception());
    }
  });
  return fut;
}

int main(int argc, char* argv[]) {
  const std::filesystem::path ROOT{"data_nproma32"};
  std::vector<int> ns = {1, 2, 7, 9, 43, 93, 463, 519, 1140, 1814, 2593, 5701};
  int n1 = -1;
  int rep = 1;

  if (argc == 2) {
    n1 = std::atoi(argv[1]);
  }
  std::cout << "Running: " << n1 << std::endl;
  if (n1 > 0) {
    ns = {n1};
  }

  for (int n : ns) {
    std::cerr << "Reading data for " << n << "..." << std::endl;

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

    auto [global_data, global_data_want] = fut_global_data.get();
    auto [p_diag, p_diag_want] = fut_p_diag.get();
    auto p_int = fut_p_int.get();
    auto [p_metrics, p_metrics_want] = fut_p_metrics.get();
    auto p_patch = fut_p_patch.get();
    auto [p_prog, p_prog_want] = fut_p_prog.get();
    auto [z_kin_hor_e, z_kin_hor_e_want] = fut_z_kin_hor_e.get();
    auto [z_vt_ie, z_vt_ie_want] = fut_z_vt_ie.get();
    auto [z_w_concorr_me, z_w_concorr_me_want] = fut_z_w_concorr.get();
    int istep = fut_istep.get();
    int ldeepatmo = fut_ldeepatmo.get();
    int lvn_only = fut_lvn_only.get();
    int ntnd = fut_ntnd.get();
    double dt_linintp_ubc = fut_dt_linintp.get();
    double dtime = fut_dtime.get();

    std::cerr << "All data read..." << std::endl;

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
    std::cout << "Step " << n
              << " variables, extra_diffu: " << global_data.lextra_diffu
              << ", istep: ";
    std::cout << istep << ", lvn_only: " << lvn_only
              << ", ldeepatmo: " << ldeepatmo << std::endl;

    if (lvn_only == 1 && istep == 1) {
      auto* h_1_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
          &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
          /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
          /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
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
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2),
          dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
          h_1_1, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
          /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
          /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
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
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2),
          dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      int err =
          __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(h_1_1);

    } else if (lvn_only == 0 && istep == 1) {
      auto* h_0_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
          &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
          /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
          /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
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
          serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2),
          dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      for (int j = 0; j < rep; j++) {
        __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
            h_0_1, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
            z_kin_hor_e, z_vt_ie, z_w_concorr_me,
            /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
            serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
            /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
            serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
            /*__f2dace_A_z_vt_ie_d_0_s_160=*/
            serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
            /*__f2dace_A_z_vt_ie_d_1_s_161=*/
            serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
            /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
            serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(0),
            /*__f2dace_A_z_w_concorr_me_d_1_s_155=*/
            serde::ARRAY_META_DICT()->at(z_w_concorr_me).size.at(1),
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
            serde::ARRAY_META_DICT()->at(z_w_concorr_me).lbound.at(2),
            dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      }
      int err =
          __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(h_0_1);

    } else if (lvn_only == 1 && istep == 2) {
      auto* h_1_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
          &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
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
          dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
          h_1_2, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),

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
          dt_linintp_ubc, dtime, istep, ldeepatmo, lvn_only, ntnd);
      int err =
          __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(h_1_2);

    } else if (lvn_only == 0 && istep == 2) {
      auto* h_0_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
          &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
          z_kin_hor_e, z_vt_ie, z_w_concorr_me,
          /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
          /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
          serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
          /*__f2dace_A_z_vt_ie_d_0_s_160=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
          /*__f2dace_A_z_vt_ie_d_1_s_161=*/
          serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
          /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
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
          serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(2), dt_linintp_ubc,
          dtime, istep, ldeepatmo, lvn_only, ntnd);
      for (int j = 0; j < rep; j++) {
        __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
            h_0_2, &global_data, &p_diag, &p_int, &p_metrics, &p_patch, &p_prog,
            z_kin_hor_e, z_vt_ie, z_w_concorr_me,
            /*__f2dace_A_z_kin_hor_e_d_0_s_157=*/
            serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(0),
            /*__f2dace_A_z_kin_hor_e_d_1_s_158=*/
            serde::ARRAY_META_DICT()->at(z_kin_hor_e).size.at(1),
            /*__f2dace_A_z_vt_ie_d_0_s_160=*/
            serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(0),
            /*__f2dace_A_z_vt_ie_d_1_s_161=*/
            serde::ARRAY_META_DICT()->at(z_vt_ie).size.at(1),
            /*__f2dace_A_z_w_concorr_me_d_0_s_154=*/
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
            serde::ARRAY_META_DICT()->at(z_vt_ie).lbound.at(2), dt_linintp_ubc,
            dtime, istep, ldeepatmo, lvn_only, ntnd);
      }
      int err =
          __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(h_0_2);

    } else {
      throw std::runtime_error("Law of Logic and Mathematics violated");
    }
    std::cout << "Step " << n << " done." << std::endl;

    pool.clear();
    pool.emplace_back([&] {
      got_want_pair<global_data_type>(global_data, global_data_want,
                                      "global_data", n);
    });
    pool.emplace_back(
        [&] { got_want_pair<t_nh_diag>(p_diag, p_diag_want, "p_diag", n); });
    pool.emplace_back([&] {
      got_want_pair<t_nh_metrics>(p_metrics, p_metrics_want, "p_metrics", n);
    });
    pool.emplace_back(
        [&] { got_want_pair<t_nh_prog>(p_prog, p_prog_want, "p_prog", n); });
    pool.emplace_back([&] {
      got_want_pair<double*>(z_kin_hor_e, z_kin_hor_e_want, "z_kin_hor_e", n);
    });
    pool.emplace_back(
        [&] { got_want_pair<double*>(z_vt_ie, z_vt_ie_want, "z_vt_ie", n); });
    pool.emplace_back([&] {
      got_want_pair<double*>(z_w_concorr_me, z_w_concorr_me_want,
                             "z_w_concorr_me", n);
    });
  }
  return EXIT_SUCCESS;
}
