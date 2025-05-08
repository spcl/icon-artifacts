import dace
import os
import shutil
from pathlib import Path
import typing
import re

from dace.sdfg import infer_types
from utils.config import fix_out_val_0

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
    pattern = re.compile(r"^(\s*)int tmp_struct_symbol")

    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            if file_path.endswith(
                (".c", ".h", ".cpp", ".cu")
            ):  # Adjust extensions as needed
                modify_file(file_path, pattern)


def modify_file(file_path, pattern):
    with open(file_path, "r", encoding="utf-8") as f:
        lines = f.readlines()

    modified = False
    new_lines = []
    for line in lines:
        if pattern.match(line):
            line = pattern.sub(r"\1static int tmp_struct_symbol", line)
            modified = True
        line = re.sub(
            r'\bint\s+(__(f2dace_[a-zA-Z0-9_]+));',
            r'static int \1;',
            line
        )

        new_lines.append(line)

    if modified:
        with open(file_path, "w", encoding="utf-8") as f:
            f.writelines(new_lines)
        # print(f"Modified: {file_path}")


import re


def _insert_measure_time(filename, path, hash):
    with open(filename, "r") as f:
        lines = f.readlines()

    pattern = re.compile(r"nrdmax_jg =")
    pattern2 = re.compile(r"p_diag_out_max_vcfl_dyn =")  # Final tasklet
    pattern3 = re.compile(r"__state->report.reset")
    new_lines = []

    for line in lines:
        if not pattern3.search(line):
            new_lines.append(line)
        else:
            new_lines.append(f"//" + line)
        if pattern.search(line) or pattern2.search(line):
            # if pattern.search(line):
            #    new_lines.append(f'__state->report.init("{path}", "{hash}");\n')
            new_lines.append('measure_time("Kernels"); // Measure time\n')
            if pattern2.search(line):
                new_lines.append(f'__state->report.save("{path}", "{hash}");\n')
    with open(filename, "w") as f:
        f.writelines(new_lines)


def fix_out_val_0_call(filepath, pattern):
    with open(filepath, "r") as file:
        lines = file.readlines()
    replacement = pattern.replace("out_val_0", "out_val_0[_for_it_35]")
    with open(filepath, "w") as file:
        for line in lines:
            if pattern in line:
                line = line.replace(pattern, replacement)
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
                    _insert_measure_time(
                        filepath,
                        os.path.join(os.path.abspath(root), "../../../perf"),
                        sdfg.hash_sdfg(),
                    )


def insert_measure_time_calls(path, sdfg: dace.SDFG, instrument: bool = False):
    # this file is at utils/../.dacecache
    if path is None:
        script_dir = os.path.join(
            os.path.dirname(os.path.abspath(__file__)), "..", ".dacecache"
        )
    else:
        script_dir = path
    _process_folder(script_dir, sdfg, instrument)

def add_timers(file_path: str, gpu: bool):
    """
    """
    import re

    with open(file_path, "r") as f:
        code = f.read()

    # Pattern 1: Insert BEFORE `nrdmax_jg = __CG_global_data__m_nrdmax[0];`
    # Pattern 1: Insert BEFORE `nrdmax_jg = __CG_global_data__m_nrdmax[0];`
    pattern1 = r'^\s*nrdmax_jg\s*=\s*__CG_global_data__m_nrdmax\[0\];\s*$'
    #replacement1 = '    cudaDeviceSynchronize();\n    measure_time("Run");\n\\g<0>'
    replacement1 = '   measure_time("Run"); \n'
    if gpu:
        replacement1 += '   cudaEvent_t start1, stop1;\n    cudaEventCreate(&start1);\n    cudaEventCreate(&stop1);\n    cudaEventRecord(start1); \n\\g<0>'
    # Pattern 2: Insert AFTER `__CG_p_diag__m_max_vcfl_dyn = p_diag_out_max_vcfl_dyn;`
    pattern2 = r'^(.*i_endblk_var_147 = __CG_p_patch__CG_cells__m_end_block\[\(\(- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2\) - 4\)\];.*)$'
    p2 = "i_endblk_var_147 = __CG_p_patch__CG_cells__m_end_block[((- __f2dace_SOA_end_block_d_0_s_163_cells_p_patch_2) - 4)];"
    escaped_p2 = re.escape(p2)
    #replacement2 = '\\1\n    cudaDeviceSynchronize();\n    measure_time("Run");'
    if gpu:
        replacement2 = '\\g<0>    cudaEventRecord(stop1);\n    cudaEventSynchronize(stop1);\n    float milliseconds1 = 0;\n    cudaEventElapsedTime(&milliseconds1, start1, stop1);\n    std::cout << "Total time: " << milliseconds1 << " ms" << std::endl;\n    cudaEventDestroy(start1);\n    cudaEventDestroy(stop1);\n'
        replacement2 += '  measure_time("Run");\n'
    else:
        replacement2 = '  measure_time("Run");\n'
    # Apply replacements
    code = re.sub(pattern1, replacement1, code, flags=re.MULTILINE)
    code = re.sub(pattern2, replacement2, code, flags=re.MULTILINE)


    with open(file_path, "w") as f:
        f.write(code)

def comment_out_syncs(filepath):
    # comment out (prepend //) any line containing cudaStreamSynchronize
    vcflmax_count = 0
    added_one = False
    with open(filepath, "r") as file:
        lines = file.readlines()
    with open(filepath, "w") as file:
        for line in lines:
            if "vcflmax_out_0 = maxvcfl_0_in;" in line:
                vcflmax_count = 1
            if "cudaStreamSynchronize" in line:
                if vcflmax_count > 0:
                    vcflmax_count -= 1
                    line = "//" + line
                    line += "\ncudaStreamSynchronize(__state->gpu_context->streams[0]);\n"
                    added_one = True
                else:
                  line = "//" + line
            file.write(line)
    assert added_one, f"Couldn't add one necessary sync."

def compile_if_propagated_sdfgs(
    sdfgs: typing.List[dace.SDFG],
    gpu: bool = False,
    release: bool = False,
    instrument: bool = False,
    generate_code: bool = True,
    lib = False,
):
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
                infer_types.infer_connector_types(sdfg)

                # Set default storage/schedule types in SDFG
                infer_types.set_default_schedule_and_storage_types(sdfg, None)

                # Recursively expand library nodes that have not yet been expanded
                sdfg.expand_library_nodes()

                # After expansion, run another pass of connector/type inference
                infer_types.infer_connector_types(sdfg)
                infer_types.set_default_schedule_and_storage_types(sdfg, None)
                sdfg.validate()
                sdfg.save(sdfg.name + "_concretized.sdfgz", compress=True)

                # Generate code for the program by traversing the SDFG state by state
                program_objects = codegen.generate_code(sdfg, validate=True)
            except Exception:
                fpath = os.path.join("_dacegraphs", "failing.sdfgz")
                sdfg.save(fpath, compress=True)
                print(f"Failing SDFG saved for inspection in {os.path.abspath(fpath)}")
                raise

            # Generate the program folder and write the source files
            compiler.generate_program_folder(sdfg, program_objects, sdfg.build_folder)

            modify_files_in_directory(build_loc)
            add_timers(f"{build_loc}/src/cpu/{sdfg_name}.cpp", gpu)
            # insert_measure_time_calls(build_loc, sdfg, instrument)
            if fix_out_val_0:
                  fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &cfl_clipping")
                  fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &maxvcfl_arr")
                  fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &z_w_con_c")
        if gpu:
            _replace_cpp_with_cu(build_loc)
            comment_out_syncs(f"{build_loc}/src/cpu/{sdfg_name}.cu")
            with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
                file.write(
                    '#include "reductions_device.cuh"\n#define __REDUCE_DEVICE__\n'
                    + main_cu_code
                )
            if fix_out_val_0:
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_cfl_clipping")
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_z_w_con_c")
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_maxvcfl_arr")
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_levmask")
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_maxvcfl_arr")
                fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_cfl_clipping")
            sources.add(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu")
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "w") as file:
                file.write(
                    '#include "reductions_kernel.cuh"\n#include "reductions_cpu.h"\n#include "timer.h"\n'
                    + main_cu_code
                )
            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cu")
        else:
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "w") as file:
                file.write(
                    '#include "reductions_cpu.h"\n#include "timer.h"\n' + main_cu_code
                )
            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cpp")

    if not gpu:
        if not lib:
            sources.add("main.cc")
    else:
        if not lib:
            sources.add("main_gpu.cu")

    supress_flags = "--diag-suppress 68 --diag-suppress 550 --diag-suppress 20208 --diag-suppress 1835 --diag-suppress 177 --diag-suppress 20012 --diag-suppress 1098"
    if gpu:
        if release:
            flags = f" {supress_flags} -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-O3 -Xcompiler=-faligned-new --expt-relaxed-constexpr -arch=native --use_fast_math -O3 "
        else:
            flags = f" {supress_flags} -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-faligned-new --expt-relaxed-constexpr -arch=native -O0 -Xcompiler=-O0 -G -g -Xcompiler=-g --fmad=false --prec-div=true --prec-sqrt=true --ftz=false "
        if lib:
            flags += " -DNO_SERDE -std=c++17 -rdc=true -Xcompiler=-fPIC --compiler-options '-fPIC' --shared "
        else:
            flags += " -std=c++20 "
    else:
        if release:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -fopenmp -faligned-new -O3 -g "
        else:
            flags = " -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas -faligned-new -O0 -g -ggdb "

    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"
    if gpu:
        if not lib:
            exit_code = os.system(
                f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_gpu"
            )
        else:
            exit_code = os.system(
                f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o libvelocity_gpu.so"
            )
    else:
        if not lib:
            exit_code = os.system(
                f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_cpu"
            )
        else:
            exit_code = os.system(
                f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o libvelocity_cpu.so"
            )

    # check if compilation was successful
    if exit_code != 0:
        if gpu:
            print(f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_gpu")
        else:
            print(f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_cpu")
        print("Compilation failed")
        exit(1)
