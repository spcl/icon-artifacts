#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>

#include "serde_solve_nh.h"
#include "solve_nh.h"

const std::filesystem::path ROOT{
    "/Users/pmz/gitspace/icon-dace/experiments/exclaim_ape_R2B09/"};

std::filesystem::path versioned_data(const std::string& name, int version) {
  auto file_name = name + "." + std::to_string(version) + ".data";
  return ROOT / file_name;
}

std::ifstream read_from(const std::filesystem::path &p) {
  std::ifstream fs{p};
  if (!fs.good()) {
    std::cerr << "Cannot open: " << p << std::endl;
    exit(EXIT_FAILURE);
  }
  return fs;
}

int main() {
  const int max_n = 1;

  for (int n = 1; n <= max_n; ++n) {
    std::cerr << "Reading data for " << n << "..." << std::endl;

    global_data_type global_data;
    {
      auto data = read_from(versioned_data("global_data.t0", n));
      serde::deserialize(&global_data, data);
    }
    global_data_type global_data_want;
    {
      auto data = read_from(versioned_data("global_data.t1", n));
      serde::deserialize(&global_data_want, data);
    }
    /*
    std::vector<const global_data_type*> gs{&global_data, &global_data_want};
    std::cerr << serde::serialize_consistent_global_data(gs,
    serde::SerializationType::PLAIN) << std::endl; std::cerr <<
    serde::serialize_consistent_global_data(gs,
    serde::SerializationType::CONST_INJECTION) << std::endl; std::cerr <<
    serde::serialize_consistent_global_data(gs,
    serde::SerializationType::F90_MODULE) << std::endl; return 0;
    */

    t_int_state p_int;
    {
      auto data = read_from(versioned_data("p_int", n));
      serde::deserialize(&p_int, data);
    }

    t_patch p_patch;
    {
      auto data = read_from(versioned_data("p_patch.t0", n));
      serde::deserialize(&p_patch, data);
    }
    t_patch p_patch_want;
    {
      auto data = read_from(versioned_data("p_patch.t1", n));
      serde::deserialize(&p_patch_want, data);
    }

    t_prepare_adv prep_adv;
    {
      auto data = read_from(versioned_data("prep_adv.t0", n));
      serde::deserialize(&prep_adv, data);
    }
    t_prepare_adv prep_adv_want;
    {
      auto data = read_from(versioned_data("prep_adv.t1", n));
      serde::deserialize(&prep_adv_want, data);
    }

    t_nh_state p_nh;
    {
      auto data = read_from(versioned_data("p_nh.t0", n));
      serde::deserialize(&p_nh, data);
    }
    t_nh_state p_nh_want;
    {
      auto data = read_from(versioned_data("p_nh.t1", n));
      serde::deserialize(&p_nh_want, data);
    }

    int jstep, idyn_timestep, l_init, l_recompute, nnew, nnow;
    {
      auto data = read_from(versioned_data("jstep", n));
      serde::deserialize(&jstep, data);
    }
    {
      auto data = read_from(versioned_data("idyn_timestep", n));
      serde::deserialize(&idyn_timestep, data);
    }
    {
      auto data = read_from(versioned_data("l_init", n));
      serde::deserialize(&l_init, data);
    }
    {
      auto data = read_from(versioned_data("l_recompute", n));
      serde::deserialize(&l_recompute, data);
    }
    {
      auto data = read_from(versioned_data("nnew", n));
      serde::deserialize(&nnew, data);
    }
    {
      auto data = read_from(versioned_data("nnow", n));
      serde::deserialize(&nnow, data);
    }
    double lacc, dtime, lclean_mflx, lprep_adv, lsave_mflx;
    {
      auto data = read_from(versioned_data("lacc", n));
      serde::deserialize(&lacc, data);
    }
    {
      auto data = read_from(versioned_data("dtime", n));
      serde::deserialize(&dtime, data);
    }
    {
      auto data = read_from(versioned_data("lclean_mflx", n));
      serde::deserialize(&lclean_mflx, data);
    }
    {
      auto data = read_from(versioned_data("lprep_adv", n));
      serde::deserialize(&lprep_adv, data);
    }
    {
      auto data = read_from(versioned_data("lsave_mflx", n));
      serde::deserialize(&lsave_mflx, data);
    }

    std::cerr << "All data read..." << std::endl;

    auto *h = __dace_init_solve_nh(
        &global_data, &p_int, &p_nh, &p_patch, &prep_adv,
        /*__f2dace_OPTIONAL_lacc=*/0, dtime, idyn_timestep, jstep, l_init,
        l_recompute, lacc, lclean_mflx, lprep_adv, lsave_mflx, nnew, nnow,
        /*tmp_index_1292=*/0, /*tmp_index_1293=*/0);

    __program_solve_nh(h, &global_data, &p_int, &p_nh, &p_patch, &prep_adv,
                       /*__f2dace_OPTIONAL_lacc=*/0, dtime, idyn_timestep,
                       jstep, l_init, l_recompute, lacc, lclean_mflx, lprep_adv,
                       lsave_mflx, nnew, nnow,
                       /*tmp_index_1292=*/0, /*tmp_index_1293=*/0);

    __dace_exit_solve_nh(h);

    {
      std::ofstream data("global_data_" + std::to_string(n) + ".got");
      data << serde::serialize(&global_data) << std::endl;
    }
    {
      std::ofstream data("global_data_" + std::to_string(n) + ".want");
      data << serde::serialize(&global_data_want) << std::endl;
    }

    {
      std::ofstream data("p_patch_" + std::to_string(n) + ".got");
      data << serde::serialize(&p_patch) << std::endl;
    }
    {
      std::ofstream data("p_patch_" + std::to_string(n) + ".want");
      data << serde::serialize(&p_patch_want) << std::endl;
    }

    {
      std::ofstream data("prep_adv_" + std::to_string(n) + ".got");
      data << serde::serialize(&prep_adv) << std::endl;
    }
    {
      std::ofstream data("prep_adv_" + std::to_string(n) + ".want");
      data << serde::serialize(&prep_adv_want) << std::endl;
    }

    {
      std::ofstream data("p_nh_" + std::to_string(n) + ".got");
      data << serde::serialize(&p_nh) << std::endl;
    }
    {
      std::ofstream data("p_nh_" + std::to_string(n) + ".want");
      data << serde::serialize(&p_nh_want) << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
