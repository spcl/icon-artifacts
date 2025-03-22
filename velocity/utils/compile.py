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


def compile(sdfg: dace.SDFG, gpu: bool = False):
    # get build location and dace location
    build_loc = sdfg.build_folder
    sdfg_name = sdfg.name
    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"

    # remove the .dacecache folder
    shutil.rmtree(build_loc, ignore_errors=True)

    # Generate code
    # TODO: Find a way to generate code with .dacecache
    try:
        sdfg.compile()
    except Exception as e:
        pass

    # Prepend reduction library to .dacecache/<name>/src/cpu/<name>.cpp
    with open(f"src/reductions.cpp", "r") as file:
        reduction_code = file.read()
    with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "r") as file:
        main_cpp_code = file.read()
    with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "w") as file:
        file.write(reduction_code + main_cpp_code)

    if gpu:
        # Prepend reduction library to .dacecache/<name>/src/cuda/<name>_cuda.cu
        with open(f"src/reductions.cu", "r") as file:
            reduction_code = file.read()
        with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
            main_cpp_code = file.read()
        with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
            file.write(reduction_code + main_cpp_code)

    # compile the SDFG
    sdfg._regenerate_code = False
    sdfg.compile()

    if gpu:
        # copy main_cpp_file to .dacecache/<name>/src/cpu/
        shutil.copy(f"main_gpu.cc", f"{build_loc}/src/cpu/main.cu")
    else:
        # copy main_cpp_file to .dacecache/<name>/src/cpu/
        shutil.copy(f"main.cc", f"{build_loc}/src/cpu/main.cc")

    # copy header to .dacecache/<name>/include/
    shutil.copy(f"include/serde_velocity.h", f"{build_loc}/include/serde_velocity.h")

    if gpu:
        # To avoid link issues fastly for CUDA libs and have cuda compiler definition
        _replace_cpp_with_cu(build_loc)

    if gpu:
        # compile nvcc <SDFG cpp file> <SDFG cuda file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=native -O0 -w
        exit_code = os.system(
            f"nvcc {build_loc}/src/cpu/{sdfg_name}.cu {build_loc}/src/cuda/{sdfg_name}_cuda.cu {build_loc}/src/cpu/main.cu -I {build_loc}/include -I {dace_include} -Xcompiler=-faligned-new --expt-relaxed-constexpr -std=c++20 -arch=sm_80 -O0 -Xcompiler=-O0 -Xcompiler=-fopenmp -lineinfo -w -o {sdfg_name}"
        )
    else:
        # compile c++ <SDFG cpp file> <main file> -I../../include -I/<pathtodace>/dace/runtime/include/ -std=c++20 -O0 -ggdb
        exit_code = os.system(
            f"c++ {build_loc}/src/cpu/{sdfg_name}.cpp {build_loc}/src/cpu/main.cc -I {build_loc}/include -I {dace_include} -std=c++20 -O0 -ggdb -o {sdfg_name}"
        )

    # check if compilation was successful
    if exit_code != 0:
        print("Compilation failed")
        exit(1)
