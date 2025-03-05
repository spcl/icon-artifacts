import dace
import shutil
import os

from dace.transformation.interstate import LoopToMap
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups


# Mapping of SDFG -> headerfile
header_dict = {
    "add_aerosol_optics": "serdeae.h",
    "calc_surface_spectral": None,
    "cloud_optics_fn_438": "serdeco.h",
    "crop_cloud_fraction": "serdeccf.h",
    "gas_optics": "serdego.h",
    "get_albedos": "serde_get_albedos.h",
    "solver_mcica_lw": "serdesl.h",
    "solver_mcica_sw": "serdess.h",
}

# Mapping of SDFG -> main file
main_dict = {
    "add_aerosol_optics": "main_add_aerosol_optics.cc",
    "calc_surface_spectral": "main_calc_surface_spectral.cc",
    "cloud_optics_fn_438": "main_cloud_optics.cc",
    "crop_cloud_fraction": "main_crop_cloud_fraction.cc",
    "gas_optics": "main_gas_optics.cc",
    "get_albedos": "main_get_albedos.cc",
    "solver_mcica_lw": "main_solver_mcica_lw.cc",
    "solver_mcica_sw": "main_solver_mcica_sw.cc",
}


# load the sdfg
sdfg = dace.SDFG.from_file("sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz") # ++ (segfault after S2CG)
# sdfg = dace.SDFG.from_file("sdfgs/calc_surface_spectral_simplified_dbg22.sdfgz") # x header missing
# sdfg = dace.SDFG.from_file("sdfgs/cloud_optics_fn_438_simplified_dbg22.sdfgz") # failed assertion
# sdfg = dace.SDFG.from_file("sdfgs/crop_cloud_fraction_simplified_dbg22.sdfgz") # +++
# sdfg = dace.SDFG.from_file("sdfgs/gas_optics_simplified_dbg22.sdfgz") # x SDFG compilation killed
# sdfg = dace.SDFG.from_file("sdfgs/get_albedos_simplified_dbg22.sdfgz") # x header missing
# sdfg = dace.SDFG.from_file("sdfgs/solver_mcica_lw_simplified_dbg22.sdfgz") # unsorted double linked list corrupted
# sdfg = dace.SDFG.from_file("sdfgs/solver_mcica_sw_simplified_dbg22.sdfgz") # bad array new length


# # How many loops before?
# loop_cnt = 0
# for node, state in sdfg.all_nodes_recursive():
#     if isinstance(state, dace.sdfg.state.LoopRegion):
#         loop_cnt += 1

# print(f"loops BEFORE loop2map: {loop_cnt}")

# # apply loop2map transformation
# # num_apps=sdfg.apply_transformations_repeated(LoopToMap)

num_apps = StructToContainerGroups().apply_pass(sdfg, {})


# print(f"Applied {num_apps} LoopToMap transformations")

# # How many loops after?
# loop_cnt = 0
# for node, state in sdfg.all_nodes_recursive():
#     if isinstance(state, dace.sdfg.state.LoopRegion):
#         loop_cnt += 1

# print(f"loops AFTER loop2map: {loop_cnt}")

# sdfg.save("containergrouped.sdfg")

# exit(0)

################################################################################
# Run the altered SDFG


# compile the sdfg
sdfg.compile()


# get build location and dace location
build_loc = sdfg.build_folder
sdfg_name = sdfg.name
dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

# copy main_cpp_files/main_solver_mcica_lw.cc to .dacecache/solver_mcica_lw/src/cpu/main_solver_mcica_lw.cc
main_name = main_dict[sdfg_name]
shutil.copy(
    f"main_cpp_files/{main_name}", f"{build_loc}/src/cpu/{main_name}"
)

# change the line "constexpr char ROOT[] ="
# to contain "/home/xdb/icon-artifacts/inputs/solver_mcica_lw/"
with open(f"{build_loc}/src/cpu/{main_name}", "r") as file:
    lines = file.readlines()
with open(f"{build_loc}/src/cpu/{main_name}", "w") as file:
    for line in lines:
        if line.startswith("constexpr char ROOT[] ="):
            file.write(
                f'constexpr char ROOT[] = "/home/primrose/Work/IconGrounds/icon-artifacts/inputs/{sdfg_name}/";\n'
            )
        else:
            file.write(line)

# copy headers/serdesl.h to .dacecache/solver_mcica_lw/include/serdesl.h
header_name = header_dict[sdfg_name]
shutil.copy(f"headers/{header_name}", f"{build_loc}/include/{header_name}")
# compile c++ solver_mcica_lw.cpp main_solver_mcica_lw.cc -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++17 -O0 -ggdb
os.system(
    f"clang++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/{main_name} -I {build_loc}/include -I {dace_include} -std=c++17 -O0 -ggdb -o {sdfg_name}"
)

os.system(
    f"valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./{sdfg_name}"
)