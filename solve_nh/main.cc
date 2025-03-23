#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "serde_solve_nh.h"
#include "solve_nh.h"

int main() {
  const std::filesystem::path ROOT{
      "/Users/pmz/gitspace/icon-dace/experiments/exclaim_ape_R2B09/"};
  const int max_n = 5;

  for (int n = 1; n <= max_n; ++n) {
    std::cerr << "Reading data for " << n << "..." << std::endl;

    global_data_type global_data;
    {
      std::ifstream data(ROOT /
                         ("global_data.t0." + std::to_string(n) + ".data"));
      serde::deserialize_global_data(&global_data, data);
    }
    global_data_type global_data_want;
    {
      std::ifstream data(ROOT /
                         ("global_data.t1." + std::to_string(n) + ".data"));
      serde::deserialize_global_data(&global_data_want, data);
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
      std::ifstream data(ROOT / ("p_int." + std::to_string(n) + ".data"));
      serde::deserialize(&p_int, data);
    }

    t_patch p_patch;
    {
      std::ifstream data(ROOT / ("p_patch.t0." + std::to_string(n) + ".data"));
      serde::deserialize(&p_patch, data);
    }
    t_patch p_patch_want;
    {
      std::ifstream data(ROOT / ("p_patch.t1." + std::to_string(n) + ".data"));
      serde::deserialize(&p_patch_want, data);
    }

    t_prepare_adv prep_adv;
    {
      std::ifstream data(ROOT / ("prep_adv.t0." + std::to_string(n) + ".data"));
      serde::deserialize(&prep_adv, data);
    }
    t_prepare_adv prep_adv_want;
    {
      std::ifstream data(ROOT / ("prep_adv.t1." + std::to_string(n) + ".data"));
      serde::deserialize(&prep_adv_want, data);
    }

    t_nh_state p_nh;
    {
      std::ifstream data(ROOT / ("p_nh.t0." + std::to_string(n) + ".data"));
      serde::deserialize(&p_nh, data);
    }
    t_nh_state p_nh_want;
    {
      std::ifstream data(ROOT / ("p_nh.t1." + std::to_string(n) + ".data"));
      serde::deserialize(&p_nh_want, data);
    }

    int jstep, idyn_timestep, l_init, l_recompute, nnew, nnow;
    {
      std::ifstream data(ROOT / ("jstep." + std::to_string(n) + ".data"));
      serde::deserialize(&jstep, data);
    }
    {
      std::ifstream data(ROOT /
                         ("idyn_timestep." + std::to_string(n) + ".data"));
      serde::deserialize(&idyn_timestep, data);
    }
    {
      std::ifstream data(ROOT / ("l_init." + std::to_string(n) + ".data"));
      serde::deserialize(&l_init, data);
    }
    {
      std::ifstream data(ROOT / ("l_recompute." + std::to_string(n) + ".data"));
      serde::deserialize(&l_recompute, data);
    }
    {
      std::ifstream data(ROOT / ("nnew." + std::to_string(n) + ".data"));
      serde::deserialize(&nnew, data);
    }
    {
      std::ifstream data(ROOT / ("nnow." + std::to_string(n) + ".data"));
      serde::deserialize(&nnow, data);
    }
    double lacc, dtime, lclean_mflx, lprep_adv, lsave_mflx;
    {
      std::ifstream data(ROOT / ("lacc." + std::to_string(n) + ".data"));
      serde::deserialize(&lacc, data);
    }
    {
      std::ifstream data(ROOT / ("dtime." + std::to_string(n) + ".data"));
      serde::deserialize(&dtime, data);
    }
    {
      std::ifstream data(ROOT / ("lclean_mflx." + std::to_string(n) + ".data"));
      serde::deserialize(&lclean_mflx, data);
    }
    {
      std::ifstream data(ROOT / ("lprep_adv." + std::to_string(n) + ".data"));
      serde::deserialize(&lprep_adv, data);
    }
    {
      std::ifstream data(ROOT / ("lsave_mflx." + std::to_string(n) + ".data"));
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
      data << serde::serialize_global_data(&global_data) << std::endl;
    }
    {
      std::ofstream data("global_data_" + std::to_string(n) + ".want");
      data << serde::serialize_global_data(&global_data_want) << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
