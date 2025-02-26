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
    std::ifstream data(ROOT / "istartcol.2.data");
    serde::deserialize(&istartcol, data);
  }
  {
    std::ifstream data(ROOT / "iendcol.2.data");
    serde::deserialize(&iendcol, data);
  }
  int ncol, nlev;
  {
    std::ifstream data(ROOT / "ncol.2.data");
    serde::deserialize(&ncol, data);
  }
  {
    std::ifstream data(ROOT / "nlev.2.data");
    serde::deserialize(&nlev, data);
  }
  global_data_type global_data;
  {
    std::ifstream data(ROOT / "global_data.2.data");
    serde::deserialize_global_data(&global_data, data);
  }
  config_type config;
  {
    std::ifstream data(ROOT / "config.2.data");
    serde::deserialize(&config, data);
  }
  single_level_type single_level;
  {
    std::ifstream data(ROOT / "single_level.2.data");
    serde::deserialize(&single_level, data);
  }
  gas_type gas;
  {
    std::ifstream data(ROOT / "gas.2.data");
    serde::deserialize(&gas, data);
  }
  thermodynamics_type thermodynamics;
  {
    std::ifstream data(ROOT / "thermodynamics.2.data");
    serde::deserialize(&thermodynamics, data);
  }
  double* incoming_sw = nullptr;
  {
    std::ifstream data(ROOT / "incoming_sw_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    incoming_sw = arr;
  }
  std::cerr << istartcol << ", " << iendcol << ", " << ncol << ", " << nlev << std::endl;
  double* lw_albedo = nullptr;
  {
    std::ifstream data(ROOT / "lw_albedo.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    lw_albedo = arr;
  }
  double* lw_emission = nullptr;
  {
    std::ifstream data(ROOT / "lw_emission_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    lw_emission = arr;
  }
  std::cerr << istartcol << ", " << iendcol << ", " << ncol << ", " << nlev << std::endl;
  double* od_lw = nullptr;
  {
    std::ifstream data(ROOT / "od_lw_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_lw = arr;
  }
  double* od_sw = nullptr;
  {
    std::ifstream data(ROOT / "od_sw_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    od_sw = arr;
  }
  double* planck_hl = nullptr;
  {
    std::ifstream data(ROOT / "planck_hl_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    planck_hl = arr;
  }
  double* ssa_sw = nullptr;
  {
    std::ifstream data(ROOT / "ssa_sw_t0.2.data");
    auto [m, arr] = serde::read_array<double>(data);
    ssa_sw = arr;
  }

  auto* h = __dace_init_gas_optics(
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

  return EXIT_SUCCESS;
}
