import dace
import os
import shutil
from pathlib import Path
import typing
import re

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


def modify_files_in_directory(directory):
    pattern = re.compile(r'^(\s*)int tmp_struct_symbol')

    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            if file_path.endswith(('.c', '.h', '.cpp', '.cu')):  # Adjust extensions as needed
                modify_file(file_path, pattern)

def modify_file(file_path, pattern):
    with open(file_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    modified = False
    new_lines = []
    for line in lines:
        if pattern.match(line):
            line = pattern.sub(r'\1static int tmp_struct_symbol', line)
            modified = True
        new_lines.append(line)

    if modified:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.writelines(new_lines)
        # print(f"Modified: {file_path}")

import re

def _insert_measure_time(filename, path, hash):
    with open(filename, 'r') as f:
        lines = f.readlines()

    pattern = re.compile(r"nrdmax_jg =")
    pattern2 = re.compile(r"p_diag_out_max_vcfl_dyn =") # Final tasklet
    pattern3 = re.compile(r"__state->report.reset")
    new_lines = []

    for line in lines:
        if not pattern3.search(line):
            new_lines.append(line)
        else:
            new_lines.append(f'//' + line)
        if pattern.search(line) or pattern2.search(line):
            #if pattern.search(line):
            #    new_lines.append(f'__state->report.init("{path}", "{hash}");\n')
            new_lines.append('measure_time("Kernels"); // Measure time\n')
            if pattern2.search(line):
                new_lines.append(f'__state->report.save("{path}", "{hash}");\n')
    with open(filename, 'w') as f:
        f.writelines(new_lines)

def fix_out_val_0_call(filepath):
    with open(filepath, 'r') as file:
        lines = file.readlines()

    with open(filepath, 'w') as file:
        for line in lines:
            if "out_val_0, &cfl_clipping" in line:
                line = line.replace("out_val_0, &cfl_clipping", "out_val_0[_for_it_35], &cfl_clipping")
            file.write(line)
            
def _process_folder(directory, sdfg: dace.SDFG, instrument: bool = False):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".cu"):
                filepath = os.path.join(root, file)
                # print(filepath)
                if instrument:
                    try:
                        os.mkdir(os.path.join(os.path.abspath(root), "../../../perf"))
                    except FileExistsError:
                        pass
                    _insert_measure_time(filepath,  os.path.join(os.path.abspath(root), "../../../perf"), sdfg.hash_sdfg())

def insert_measure_time_calls(path, sdfg:dace.SDFG, instrument: bool = False):
    # this file is at utils/../.dacecache
    if path is None:
        script_dir = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".dacecache")
    else:
        script_dir = path
    _process_folder(script_dir, sdfg, instrument)

def compile_if_propagated_sdfgs(sdfgs: typing.List[dace.SDFG], gpu: bool = False, release: bool = False, instrument: bool = False, generate_code: bool = True):
    sources = set()
    sources.add("src/reductions.cpp")
    sources.add("src/timer.cpp")
    if gpu:
        sources.add("src/reductions_kernel.cu")
    headers = set()
    headers.add("-Iinclude")
    from dace.codegen import codegen, compiler
    for sdfg in sdfgs:
        sdfg_name = sdfg.name
        build_loc = sdfg.build_folder
        if generate_code:
            try:
                # Fill in scope entry/exit connectors
                sdfg.fill_scope_connectors()

                # Generate code for the program by traversing the SDFG state by state
                program_objects = codegen.generate_code(sdfg, validate=False)
            except Exception:
                fpath = os.path.join("_dacegraphs", "failing.sdfgz")
                sdfg.save(fpath, compress=True)
                print(f"Failing SDFG saved for inspection in {os.path.abspath(fpath)}")
                raise

            # Generate the program folder and write the source files
            compiler.generate_program_folder(sdfg, program_objects, sdfg.build_folder)
            
            modify_files_in_directory(build_loc)
            insert_measure_time_calls(build_loc, sdfg, instrument)
            fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp")
        if gpu:
            _replace_cpp_with_cu(build_loc)
            with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
                file.write('#include "reductions_device.cuh"\n#define __REDUCE_DEVICE__\n' + main_cu_code)
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "w") as file:
                file.write('#include "reductions_kernel.cuh"\n#include "reductions_cpu.h"\n#include "timer.h"\n' + main_cu_code)
            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cu")
            sources.add(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu")
        else:
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "w") as file:
                file.write('#include "reductions_cpu.h"\n#include "timer.h"\n' + main_cu_code)
            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cpp")

    if not gpu:
        sources.add("main.cc")
    else:
        sources.add("main_gpu.cu")

    if gpu:
        if release:
            flags = " -std=c++20 -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-g -Xcompiler=-O3 -lineinfo -Xcompiler=-faligned-new -Xcompiler=-fopenmp --expt-relaxed-constexpr -arch=native"
        else:
            flags = " -std=c++20 -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-faligned-new --expt-relaxed-constexpr -arch=native -O0 -Xcompiler=-O0 -lineinfo -G -g -Xcompiler=-g --fmad=false --prec-div=true --prec-sqrt=true --ftz=false"
    else:
        if release:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -fopenmp -faligned-new -O3 -g "
        else:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas -faligned-new -O0 -g -ggdb "

    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"
    if gpu:
        exit_code = os.system(
            f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_gpu"
        )
    else:
        exit_code = os.system(
            f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_cpu"
        )

    # check if compilation was successful
    if exit_code != 0:
        print("Compilation failed")
        exit(1)

