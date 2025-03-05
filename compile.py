import copy
import subprocess
import dace
import shutil
import os

from dace.transformation.interstate.loop_to_map import LoopToMap
from dace.transformation.passes.struct_to_container_group import StructToContainerGroups

# Mapping of SDFG -> headerfile
header_dict = {
    "add_aerosol_optics": "serdeae.h",
    #"calc_surface_spectral": None,
    "cloud_optics_fn_438": "serdeco.h",
    "crop_cloud_fraction": "serdeccf.h",
    #"gas_optics": "serdego.h",
    "get_albedos": "serde_get_albedos.h",
    "solver_mcica_lw": "serdesl.h",
    "solver_mcica_sw": "serdess.h",
}

# Mapping of SDFG -> main file
main_dict = {
    "add_aerosol_optics": "main_add_aerosol_optics.cc",
    #"calc_surface_spectral": "main_calc_surface_spectral.cc",
    "cloud_optics_fn_438": "main_cloud_optics.cc",
    "crop_cloud_fraction": "main_crop_cloud_fraction.cc",
    #"gas_optics": "main_gas_optics.cc",
    "get_albedos": "main_get_albedos.cpp",
    "solver_mcica_lw": "main_solver_mcica_lw.cc",
    "solver_mcica_sw": "main_solver_mcica_sw.cc",
}


paths = [
    "sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz",
    #"sdfgs/calc_surface_spectral_simplified_dbg22.sdfgz",
    "sdfgs/cloud_optics_fn_438_simplified_dbg22.sdfgz",
    "sdfgs/crop_cloud_fraction_simplified_dbg22.sdfgz",
    #"sdfgs/gas_optics_simplified_dbg22.sdfgz"
    "sdfgs/get_albedos_simplified_dbg22.sdfgz",
    "sdfgs/solver_mcica_lw_simplified_dbg22.sdfgz",
    "sdfgs/solver_mcica_sw_simplified_dbg22.sdfgz",
]

paths = [
    "sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz",
]

for path in paths:
    # Load SDFG
    sdfg = dace.SDFG.from_file(path)
    def gen_sdfg():

        ################################################################################
        ### Apply Optimizations
        ################################################################################

        # TODO: Add Optimizations here for each SDFG
        #StructToContainerGroups(save_steps=False, verbose=False, simplify=False).apply_pass(sdfg, {})
        StructToContainerGroups(save_steps=False, verbose=False, simplify=False).apply_pass(sdfg, {})
        sdfg.save(f"flat_{sdfg.name}.sdfgz", compress=True)
        sdfg.apply_transformations_repeated(LoopToMap, validate=False)
        sdfg.save(f"map_{sdfg.name}.sdfgz", compress=True)
        sdfg.validate()
        sdfg.apply_gpu_transformations(validate=False, simplify=False)
        sdfg.save("to_gpu.sdfgz", compress=True)

        def fixes(sdfg):
            for state in sdfg.states():
                for n in state.nodes():
                    if isinstance(n, dace.nodes.NestedSDFG):
                        fixes(n.sdfg)
                    if isinstance(n, dace.nodes.AccessNode) and isinstance(sdfg.arrays[n.data], dace.data.View):
                        assert state.in_degree(n) == 1
                        for ie in state.in_edges(n):
                            if isinstance(ie.src, dace.nodes.MapEntry):
                                d = ie.data.data
                                an = state.add_access(d)
                                state.add_edge(an, None, n, "views", copy.deepcopy(ie.data))
                                state.add_edge(ie.src, ie.src_conn, an, None, dace.memlet.Memlet(expr=d))
                                state.remove_edge(ie)
                                print("FF", n, ie.src)

        def fixes2(sdfg):
            for state in sdfg.states():
                for n in state.nodes():
                    if isinstance(n, dace.nodes.NestedSDFG):
                        fixes2(n.sdfg)
                    if isinstance(n, dace.nodes.AccessNode):
                        arr = sdfg.arrays[n.data]
                        if arr.storage == dace.dtypes.StorageType.GPU_Global and state.scope_dict()[n] is None:
                            arr.storage = dace.dtypes.StorageType.CPU_Pinned


        sdfg.simplify(validate=False)
        fixes(sdfg)
        fixes2(sdfg)
        sdfg.save("fixed.sdfgz", compress=True)
        #sdfg.validate()
        #sdfg.save("fixed2.sdfgz", compress=True)

        ################################################################################
        ### Compile the (optimized) SDFG with alterations
        ################################################################################

        # compile the SDFG
        sdfg.generate_code()

    #if path != "sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz":
    #    gen_sdfg()
    gen_sdfg()

    # Source file changes
    # get build location and dace location
    build_loc = sdfg.build_folder
    sdfg_name = sdfg.name
    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

    if path == "sdfgs/add_aerosol_optics_simplified_dbg22.sdfgz":
        file_path = f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu"

        # Read the file
        with open(file_path, "r") as file:
            lines = file.readlines()

        # Remove the specific line
        filtered_lines = [line for line in lines if "int nlev_var_393 = nlev_var_393;" not in line.strip()]
        print("FL", filtered_lines)

        # Write back the modified content
        with open(file_path, "w") as file:
            file.writelines(filtered_lines)


    # copy main_cpp_file to .dacecache/<name>/src/cpu/
    main_name = main_dict[sdfg_name]
    print(main_name)
    shutil.copy(f"main_cpp_files/{main_name}", f"{build_loc}/src/cpu/{main_name}")

    # change the line "constexpr char ROOT[] ="
    # to contain "<path to this script>/inputs/<name>/"
    input_folder = os.path.dirname(os.path.realpath(__file__)) + "/inputs"
    with open(f"{build_loc}/src/cpu/{main_name}", "r") as file:
        lines = file.readlines()
    with open(f"{build_loc}/src/cpu/{main_name}", "w") as file:
        for line in lines:
            if line.startswith("constexpr char ROOT[] ="):
                file.write(f'constexpr char ROOT[] = "{input_folder}/{sdfg_name}/";\n')
            else:
                file.write(line)
    root_dir = f"{build_loc}/src"
    for dirpath, _, filenames in os.walk(root_dir):
        for filename in filenames:
            if filename.endswith(".cpp"):
                old_path = os.path.join(dirpath, filename)
                new_path = os.path.join(dirpath, filename[:-4] + ".cu")  # Replace ".cpp" with ".cu"
                os.rename(old_path, new_path)
                print(f"Renamed: {old_path} -> {new_path}")


    # copy header to .dacecache/<name>/include/
    header_name = header_dict[sdfg_name]
    print("COMPILING:", sdfg_name, header_name, main_name)
    shutil.copy(f"headers/{header_name}", f"{build_loc}/include/{header_name}")

    compile_cmd = [
        "nvcc", f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", f"{build_loc}/src/cpu/{main_name}", f"{build_loc}/src/cpu/{sdfg_name}.cu",
        "-I", f"{build_loc}/include", "-I", f"{dace_include}",
        "-Xcompiler=-fsanitize=address", "-Xcompiler=-faligned-new", "-std=c++17", "-O0", "-Xcompiler=-ggdb", "-Xcompiler=-O0",
        "-o", sdfg_name
    ]
    print(compile_cmd)

    print(f"Running compile command: {' '.join(compile_cmd)}")
    subprocess.run(compile_cmd, check=False)  # This waits for compilation to finish

    print(f"RUNNING {sdfg_name}")
    subprocess.run(f"./{sdfg_name}", shell=True, check=False)  # This waits for execution to finish

    print(f"COMPARING {sdfg_name}")


    got_files = [f for f in os.listdir() if f.endswith(".got")]

    for got_file in got_files:
        want_file = got_file.replace(".got", ".want")

        if os.path.isfile(want_file):
            print(f"Comparing {got_file} with {want_file}...")
            result = subprocess.run(["diff", got_file, want_file])
            if result.stdout:
                with open(got_file + ".out", "w") as f:
                    f.write(result.stdout)
            if result.stderr:
                print(f"Error: {result.stderr}")
                with open(got_file + ".err", "w") as f:
                    f.write(result.stderr)
        else:
            print(f"Warning: No matching .want file for {got_file}")
