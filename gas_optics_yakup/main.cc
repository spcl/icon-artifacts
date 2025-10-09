#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "gas_optics.h"
#include "serde.h"

int main() {
  const std::filesystem::path ROOT{"data"};

  int istartcol, iendcol;
  {
    std::ifstream data(ROOT / "istartcol.1.data");
    serde::deserialize(&istartcol, data);
  }
  {
    std::ifstream data(ROOT / "iendcol.1.data");
    serde::deserialize(&iendcol, data);
  }
  int ncol, nlev;
  {
    std::ifstream data(ROOT / "ncol.1.data");
    serde::deserialize(&ncol, data);
  }
  {
    std::ifstream data(ROOT / "nlev.1.data");
    serde::deserialize(&nlev, data);
  }
  global_data_type global_data;
  {
    std::ifstream data(ROOT / "global_data.1.data");
    serde::deserialize_global_data(&global_data, data);
  }
  config_type config;
  {
    std::ifstream data(ROOT / "config.1.data");
    serde::deserialize(&config, data);
  }
  single_level_type single_level;
  {
    std::ifstream data(ROOT / "single_level.1.data");
    serde::deserialize(&single_level, data);
  }
  gas_type gas;
  {
    std::ifstream data(ROOT / "gas.1.data");
    serde::deserialize(&gas, data);
  }
  thermodynamics_type thermodynamics;
  {
    std::ifstream data(ROOT / "thermodynamics.1.data");
    serde::deserialize(&thermodynamics, data);
  }
  double *lw_albedo = nullptr;
  {
    std::ifstream data(ROOT / "lw_albedo.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    lw_albedo = arr;
  }

  double *od_lw = nullptr;
  {
    std::ifstream data(ROOT / "od_lw_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_lw = arr;
  }
  double *od_sw = nullptr;
  {
    std::ifstream data(ROOT / "od_sw_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_sw = arr;
  }
  double *ssa_sw = nullptr;
  {
    std::ifstream data(ROOT / "ssa_sw_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    ssa_sw = arr;
  }
  double *planck_hl = nullptr;
  {
    std::ifstream data(ROOT / "planck_hl_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    planck_hl = arr;
  }
  double *lw_emission = nullptr;
  {
    std::ifstream data(ROOT / "lw_emission_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    lw_emission = arr;
  }
  double *incoming_sw = nullptr;
  {
    std::ifstream data(ROOT / "incoming_sw_t0.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    incoming_sw = arr;
  }

  double *od_lw_want = nullptr;
  {
    std::ifstream data(ROOT / "od_lw_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_lw_want = arr;
  }
  double *od_sw_want = nullptr;
  {
    std::ifstream data(ROOT / "od_sw_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_sw_want = arr;
  }
  double *ssa_sw_want = nullptr;
  {
    std::ifstream data(ROOT / "ssa_sw_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    ssa_sw_want = arr;
  }
  double *planck_hl_want = nullptr;
  {
    std::ifstream data(ROOT / "planck_hl_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    planck_hl_want = arr;
  }
  double *lw_emission_want = nullptr;
  {
    std::ifstream data(ROOT / "lw_emission_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    lw_emission_want = arr;
  }
  double *incoming_sw_want = nullptr;
  {
    std::ifstream data(ROOT / "incoming_sw_t1.1.data");
    auto [m, arr] = serde::read_array<double>(data);
    incoming_sw_want = arr;
  }

  auto *h = __dace_init_gas_optics(
      &config, &gas, &global_data, incoming_sw, lw_albedo, lw_emission, od_lw,
      od_sw, planck_hl, &single_level, ssa_sw, &thermodynamics,
      /*incoming_sw_optional=*/true, /*lw_albedo_optional=*/true,
      /*lw_emission_optional=*/true, /*planck_hl_optional=*/true, iendcol,
      istartcol, ncol, nlev, iendcol, istartcol, ncol, nlev);
  __program_gas_optics(
      h, &config, &gas, &global_data, incoming_sw, lw_albedo, lw_emission,
      od_lw, od_sw, planck_hl, &single_level, ssa_sw, &thermodynamics,
      /*incoming_sw_optional=*/true, /*lw_albedo_optional=*/true,
      /*lw_emission_optional=*/true, /*planck_hl_optional=*/true, iendcol,
      istartcol, ncol, nlev, iendcol, istartcol, ncol, nlev);

  __dace_exit_gas_optics(h);

  {
    std::ofstream data("od_lw.got");
    data << serde::serialize_array(od_lw) << std::endl;
  }
  {
    std::ofstream data("od_lw.want");
    data << serde::serialize_array(od_lw_want) << std::endl;
  }
  {
    std::ofstream data("od_sw.got");
    data << serde::serialize_array(od_sw) << std::endl;
  }
  {
    std::ofstream data("od_sw.want");
    data << serde::serialize_array(od_sw_want) << std::endl;
  }
  {
    std::ofstream data("ssa_sw.got");
    data << serde::serialize_array(ssa_sw) << std::endl;
  }
  {
    std::ofstream data("ssa_sw.want");
    data << serde::serialize_array(ssa_sw_want) << std::endl;
  }
  {
    std::ofstream data("planck_hl.got");
    data << serde::serialize_array(planck_hl) << std::endl;
  }
  {
    std::ofstream data("planck_hl.want");
    data << serde::serialize_array(planck_hl_want) << std::endl;
  }
  {
    std::ofstream data("lw_emission.got");
    data << serde::serialize_array(lw_emission) << std::endl;
  }
  {
    std::ofstream data("lw_emission.want");
    data << serde::serialize_array(lw_emission_want) << std::endl;
  }
  {
    std::ofstream data("incoming_sw.got");
    data << serde::serialize_array(incoming_sw) << std::endl;
  }
  {
    std::ofstream data("incoming_sw.want");
    data << serde::serialize_array(incoming_sw_want) << std::endl;
  }

  return EXIT_SUCCESS;
}
