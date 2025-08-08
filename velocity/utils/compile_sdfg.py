import dace
import os
import shutil
from pathlib import Path


# Replace cpp with cu
def _replace_cpp_with_cu(directory):
    directory = Path(directory)  # Convert to Path object
    for file in directory.rglob("*.cpp"):  # Find all .cpp files
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")
    for file in directory.rglob("*.cc"):
        new_name = file.with_suffix(".cu")  # Change the suffix to .cu
        file.rename(new_name)  # Rename the file
        print(f"Renamed: {file} -> {new_name}")


# Generate code
# Copied and adjusted from dace/dace/sdfg/sdfg.py:compile
def _generate_code(sdfg: dace.SDFG, validate: bool = True):
    # Importing these outside creates an import loop
    from dace.codegen import codegen, compiler
    import copy
    import warnings

    build_folder = sdfg.build_folder

    ############################
    # DaCe Compilation Process #

    # Clone SDFG as the other modules may modify its contents
    sdfg = copy.deepcopy(sdfg)
    # Fix the build folder name on the copied SDFG to avoid it changing
    # if the codegen modifies the SDFG (thereby changing its hash)
    sdfg.build_folder = build_folder

    # Ensure external nested SDFGs are loaded.
    for _ in sdfg.all_sdfgs_recursive(load_ext=True):
        pass

    # Rename SDFG to avoid runtime issues with clashing names
    index = 0
    while sdfg.is_loaded():
        sdfg.name = f"{sdfg.name}_{index}"
        index += 1
    if sdfg.name != sdfg.name:
        warnings.warn(
            f"SDFG '{sdfg.name}' is already loaded by another object, recompiling under a different "
            f"name '{sdfg.name}'."
        )

    try:
        # Fill in scope entry/exit connectors
        sdfg.fill_scope_connectors()

        # Generate code for the program by traversing the SDFG state by state
        program_objects = codegen.generate_code(sdfg, validate=validate)
    except Exception:
        fpath = os.path.join("_dacegraphs", "failing.sdfgz")
        sdfg.save(fpath, compress=True)
        print(f"Failing SDFG saved for inspection in {os.path.abspath(fpath)}")
        raise

    # Generate the program folder and write the source files
    compiler.generate_program_folder(sdfg, program_objects, build_folder)


def _pre_injection(sdfg: dace.SDFG, gpu: bool = False, release: bool = False):
    build_loc = sdfg.build_folder
    shutil.rmtree(build_loc, ignore_errors=True)  # remove the .dacecache folder
    _generate_code(sdfg)  # Generate code
    os.makedirs(f"{build_loc}/perf", exist_ok=True)  # Create perf folder


def _injection(sdfg: dace.SDFG, gpu: bool = False, release: bool = False):
    # get build location and dace location
    build_loc = sdfg.build_folder
    sdfg_name = sdfg.name

    # Prepend reduction library to .dacecache/<name>/src/cuda/<name>_cuda.cu
    if gpu:
        with open(f"src/reductions.cu", "r") as file:
            reduction_code = file.read()
        with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
            main_cpp_code = file.read()
        with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
            file.write(reduction_code + main_cpp_code)

    # Prepend reduction library to .dacecache/<name>/src/cpu/<name>.cpp
    with open(f"src/reductions.cpp", "r") as file:
        reduction_code = file.read()
    with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "r") as file:
        main_cpp_code = file.read()
    with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "w") as file:
        file.write(reduction_code + main_cpp_code)

    # Copy main file to .dacecache/<name>/src/
    if gpu:
        shutil.copy(f"main_gpu.cc", f"{build_loc}/src/cpu/main.cc")
    else:
        shutil.copy(f"main.cc", f"{build_loc}/src/cpu/main.cc")

    # Replace const std::filesystem::path ROOT{"data"}; in main.cc with data_<sdfg tag> and replace "veloctiy_tendencies" with "<sdfg name>"
    tag = sdfg_name.split("_")[-1]
    assert tag != "", "SDFG name must end with a tag"
    assert os.path.exists(f"data_{tag}"), f"data_{tag} folder does not exist"
    with open(f"{build_loc}/src/cpu/main.cc", "r") as file:
        lines = file.readlines()
    with open(f"{build_loc}/src/cpu/main.cc", "w") as file:
        for line in lines:
            if "const std::filesystem::path ROOT{" in line:
                file.write(f'const std::filesystem::path ROOT{{"data_{tag}"}};\n')
            elif "velocity_tendencies" in line:
                file.write(line.replace("velocity_tendencies", sdfg_name))
            else:
                file.write(line)

    # copy header to .dacecache/<name>/include/
    assert os.path.exists(
        f"include/serde_velocity_{tag}.h"
    ), f"serde_velocity_{tag}.h does not exist"
    shutil.copy(
        f"include/serde_velocity_{tag}.h", f"{build_loc}/include/serde_velocity.h"
    )

    # Replace "veloctiy_tendencies" with "<sdfg name>"
    with open(f"{build_loc}/include/serde_velocity.h", "r") as file:
        lines = file.readlines()
    with open(f"{build_loc}/include/serde_velocity.h", "w") as file:
        for line in lines:
            if "velocity_tendencies" in line:
                file.write(line.replace("velocity_tendencies", sdfg_name))
            else:
                file.write(line)

    # To avoid link issues fastly for CUDA libs and have cuda compiler definition
    if gpu:
        _replace_cpp_with_cu(build_loc)


def _post_injection(sdfg: dace.SDFG, gpu: bool = False, release: bool = False):
    # get build location and dace location
    build_loc = sdfg.build_folder
    sdfg_name = sdfg.name
    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

    if gpu:
        if release:
            flags = " -std=c++20 -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-g -Xcompiler=-O3 -lineinfo -Xcompiler=-faligned-new --expt-relaxed-constexpr -arch=native"
        else:
            flags = " -std=c++20 -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-faligned-new --expt-relaxed-constexpr -arch=native -O0 -Xcompiler=-O0 -lineinfo -G -g -Xcompiler=-g --fmad=false --prec-div=true --prec-sqrt=true --ftz=false"
    else:
        if release:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -faligned-new -O3 -g "
        else:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas -faligned-new -O0 -g -ggdb "

    if gpu:
        exit_code = os.system(
            f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu {build_loc}/src/cpu/main.cu -I {build_loc}/include -I {dace_include} {flags} -o {sdfg_name}"
        )
    else:
        exit_code = os.system(
            f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/main.cc -I {build_loc}/include -I {dace_include} {flags} -o {sdfg_name}"
        )

    # check if compilation was successful
    if exit_code != 0:
        print("Compilation failed")
        exit(1)


def compile_sdfg(sdfg: dace.SDFG, gpu: bool = False, release: bool = False):
    _pre_injection(sdfg, gpu=gpu, release=release)
    _injection(sdfg, gpu=gpu, release=release)
    _post_injection(sdfg, gpu=gpu, release=release)
