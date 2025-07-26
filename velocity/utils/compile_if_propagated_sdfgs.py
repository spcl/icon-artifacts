import dace
import os
import shutil
from pathlib import Path
import typing
import re

from dace.sdfg import infer_types
from utils.config import fix_out_val_0, rm_syncs
from utils.prune_names import prune_names, compare_structs

use_cuda_events = os.getenv('_USE_CUDA_EVENTS', '0').lower() in ('1', 'true', 'yes')

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
    return
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

def set_default_stream(file_path: str):
    src = "__state->gpu_context->streams[0]"
    dst = "nullptr"
    with open(file_path, "r") as f:
        code = f.read()

    code = code.replace(src, dst)

    with open(file_path, "w") as f:
        f.write(code)


def repl_in_file(file_path: str, src:str, dst:str):
    with open(file_path, "r") as f:
        code = f.read()

    code = code.replace(src, dst)

    with open(file_path, "w") as f:
        f.write(code)


def repl_in_file_per_line_with_cond(file_path: str, src: str, dst: str, condition: callable):
    with open(file_path, "r") as f:
        lines = f.readlines()

    for i, line in enumerate(lines):
        if condition(line):
            line = line.replace(src, dst) if condition(line) else line
        lines[i] = line

    with open(file_path, "w") as f:
        f.writelines(lines)


def add_timers(file_path: str, gpu: bool, stage:int, use_openacc_stream: bool = False):

    with open(file_path, "r") as f:
        code = f.read()

    # Pattern 1: Insert BEFORE `nrdmax_jg = __CG_global_data__m_nrdmax[0];`
    if stage < 7:
        pattern1 = r'^\s*nrdmax_jg\s*=\s*__CG_global_data__m_nrdmax\[0\];\s*$'
    else:
        pattern1 = r'^\s*nflatlev_jg\s*=\s*__CG_global_data__m_nflatlev\[0\];\s*$'
    if gpu is False:
        replacement1 = ' measure_time("Run"); \n\\g<0>'
    else:
        if stage > 5 and stage < 9:
            if use_cuda_events:
                # Stage 6 adds it before cudaStreamSynchronize
                replacement1 = '   cudaStreamSynchronize(__state->gpu_context->streams[0]); //EntryStreamSync\n      cudaEvent_t start1, stop1;\n    cudaEventCreate(&start1);\n    cudaEventCreate(&stop1);\n    cudaEventRecord(start1); \n //measure_time("Run");\n \\g<0>'
            else:
                replacement1 = '   cudaStreamSynchronize(__state->gpu_context->streams[0]); //EntryStreamSync\n      //cudaEvent_t start1, stop1;\n    //cudaEventCreate(&start1);\n    //cudaEventCreate(&stop1);\n    //cudaEventRecord(start1); \n measure_time("Run");\n \\g<0>'
        elif stage == 9:
            if use_openacc_stream:
                # Stage 8 adds it after open acc stream
                replacement1 = '\\g<0>'
            else:
                replacement1 = '   cudaDeviceSynchronize(); //EntryStreamSync\n      //cudaEvent_t start1, stop1;\n    //cudaEventCreate(&start1);\n    //cudaEventCreate(&stop1);\n    //cudaEventRecord(start1); \n measure_time("Run");\n \\g<0>'
        else:
            assert stage <= 5
            if use_cuda_events:
                replacement1 = '   cudaDeviceSynchronize(); //EntryStreamSync\n      cudaEvent_t start1, stop1;\n    cudaEventCreate(&start1);\n    cudaEventCreate(&stop1);\n    cudaEventRecord(start1); \n //measure_time("Run");\n \\g<0>'
            else:
                replacement1 = '   cudaDeviceSynchronize(); //EntryStreamSync\n      //cudaEvent_t start1, stop1;\n    //cudaEventCreate(&start1);\n    //cudaEventCreate(&stop1);\n    //cudaEventRecord(start1); \n measure_time("Run");\n \\g<0>'
    pattern2 = r'^\s*double p_diag_out_max_vcfl_dyn;\s*$'
    if gpu is True:
        if stage > 5 and stage < 9:
            if not use_cuda_events:
                replacement2 = '\\g<0>  //cudaEventRecord(stop1);\n    //cudaEventSynchronize(stop1);\n    //float milliseconds1 = 0;\n    //cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     measure_time("Host Based C++ Timer"); \n  //cudaEventDestroy(start1);\n    //cudaEventDestroy(stop1);\n    //cudaStreamSynchronize(__state->gpu_context->streams[0]); \n  //std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
            else:
                replacement2 = '\\g<0>  cudaEventRecord(stop1);\n    cudaEventSynchronize(stop1);\n    float milliseconds1 = 0;\n    cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     //measure_time("Host Based C++ Timer"); \n  cudaEventDestroy(start1);\n    cudaEventDestroy(stop1);\n    cudaStreamSynchronize(__state->gpu_context->streams[0]); \n  std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
        elif stage == 9:
            if use_openacc_stream:
                replacement2 = '\\g<0>  cudaStreamSynchronize(__state->gpu_context->streams[0]);\n    //cudaEventRecord(stop1);\n    //cudaEventSynchronize(stop1);\n    //float milliseconds1 = 0;\n    //cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     measure_time("Host Based C++ Timer"); \n  //cudaEventDestroy(start1);\n    //cudaEventDestroy(stop1);\n    //cudaDeviceSynchronize(); \n  //std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
            else:
                replacement2 = '\\g<0>  cudaStreamSynchronize(__state->gpu_context->streams[0]);\n    //cudaEventRecord(stop1);\n    //cudaEventSynchronize(stop1);\n    //float milliseconds1 = 0;\n    //cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     measure_time("Host Based C++ Timer"); \n  //cudaEventDestroy(start1);\n    //cudaEventDestroy(stop1);\n    cudaDeviceSynchronize(); \n  //std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
        else:
            if use_cuda_events:
                replacement2 = '\\g<0>  cudaEventRecord(stop1);\n    cudaEventSynchronize(stop1);\n    float milliseconds1 = 0;\n    //cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     //measure_time("Host Based C++ Timer"); \n  cudaEventDestroy(start1);\n    //cudaEventDestroy(stop1);\n    cudaDeviceSynchronize(); \n  std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
            else:
                replacement2 = '\\g<0>  //cudaEventRecord(stop1);\n    //cudaEventSynchronize(stop1);\n    //float milliseconds1 = 0;\n    //cudaEventElapsedTime(&milliseconds1, start1, stop1);\n     measure_time("Host Based C++ Timer"); \n  //cudaEventDestroy(start1);\n    //cudaEventDestroy(stop1);\n    //cudaDeviceSynchronize(); \n  //std::cout << "CUDA Events Based Total time: " << milliseconds1*1000.0 << " us" << std::endl;\n'
    else:
        replacement2 = '\\g<0>  measure_time("Run");\n'
    # Apply replacements
    code = re.sub(pattern1, replacement1, code, flags=re.MULTILINE)
    code = re.sub(pattern2, replacement2, code, flags=re.MULTILINE)

    if gpu is True:
        if stage > 5:
            pattern4 = """dace::CopyNDDynamic<double, 1, false, 1>::template ConstDst<1>::Copy(
            __state->__0_gpu_vcflmax, __state->__0_vcflmax, tmp_struct_symbol_12, 1);"""

            replacement4 = "DACE_GPU_CHECK(cudaMemcpyAsync((void*)__state->__0_vcflmax, (void*)__state->__0_gpu_vcflmax, static_cast<size_t>(tmp_struct_symbol_12) * sizeof(double), cudaMemcpyDeviceToHost, __state->gpu_context->streams[0]));"

            code = code.replace(pattern4, replacement4)

            pattern5 = r'(^\s*double\s*.*\s*in_arr\s*=.*vcflmax.*;)'
            replacement5 = r'cudaStreamSynchronize(__state->gpu_context->streams[0]);//ExitStreamSync\n\1'
            test_line = "double* in_arr = &__state->__0_vcflmax[(replaced_var_6 - 1)];"

            if re.match(pattern5, test_line):
                #print("Pattern matches!")
                pass
            else:
                #print("Pattern doesn't match")
                assert False
            code = re.sub(pattern5, replacement5, code, flags=re.MULTILINE)

    with open(file_path, "w") as f:
        f.write(code)


def change_to_openacc_stream(host_file_path: str, dev_file_path: str, gpu: bool):
    assert gpu is True
    stream_decl = """
// This part is generated by the IconGrounds velocity utils.
// It is used to declare the openacc stream for the GPU code.
// START
#include <cuda_runtime.h>
#include <openacc.h>
static cudaStream_t open_acc_stream;
// END
"""
    host_check = "void __program_velocity_no_nproma_if_prop"
    dev_check = "DACE_EXPORTED int __dace_init_cuda_"
    for (file_path, check) in [
        (host_file_path, host_check),
        (dev_file_path, dev_check),
    ]:
        with open(file_path, "r") as f:
            lines = f.readlines()

        modified_lines = [stream_decl]
        i = 0

        def _process_line(line:str) -> str:
            if "__dace_current_stream = __state->gpu_context->streams" in line:
                _l = "cudaStream_t __dace_current_stream = open_acc_stream;\n"
            elif (
                "cudaStreamCreateWithFlags" in line or
                "cudaStreamDestroy" in line or
                "cudaEventCreateWithFlags" in line or
                "cudaEventDestroy" in line or
                "__state->gpu_context->internal_streams[" in line) and (
                    "cudaLaunchKernel" not in line
                ):
                _l = "//" + line
            elif "__state->gpu_context->streams[0]" in line:
                _l = line.replace("__state->gpu_context->streams[0]", "open_acc_stream")
            else:
                _l = line
            return _l

        c = False
        while i < len(lines):
            line = lines[i]

            # Check if line starts with the target function name
            if check in line:
                modified_lines.append(_process_line(line))
                i += 1

                is_host_check = (check == host_check)
                #raise Exception(is_host_check, check, host_check)
                if is_host_check:
                    if "_internal" in line:
                        if check in line and check == host_check and ("{" not in line) and (";" not in line) and ("DACE_EXPORTED" not in line):
                            c = True
                            print(line, check)
                            if i < len(lines) and lines[i].strip() == "{":
                                modified_lines.append(_process_line("{\n"))  # Add the opening brace

                                # Add the stream declarations after the opening brace
                                modified_lines.append("open_acc_stream = (cudaStream_t) acc_get_cuda_stream(1);\n")
                                modified_lines.append("cudaStreamSynchronize(open_acc_stream); //EntryStreamSync\n")
                                if use_cuda_events:
                                    modified_lines.append(
                                        """    cudaEvent_t start1, stop1;\n    cudaEventCreate(&start1);\n    cudaEventCreate(&stop1);\n    cudaEventRecord(start1); \n """
                                    )
                                else:
                                    modified_lines.append('measure_time("Run");\n')

                                i += 1
                            #raise Exception(line, check)
                elif not is_host_check:
                    if check in line and check == dev_check and check != host_check and "{" in line:
                        modified_lines.append("open_acc_stream = (cudaStream_t) acc_get_cuda_stream(1);\n")

            else:
                modified_lines.append(_process_line(line))
                i += 1

        # Write the modified content back to the file
        with open(file_path, "w") as f:
            f.writelines(modified_lines)


def fix_levelmask_calls(filepath: str, host : bool, stage: int):
    if stage <= 5:
        with open(filepath, "r") as file:
            lines = file.readlines()
        with open(filepath, "w") as file:
            i = 0
            while i < len(lines):
                line = lines[i]
                if host:
                    p1 = "uint8_t  gpu_levelmask, double *"
                    r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
                    p2 = "gpu_levelmask, &"
                    r2 = "&gpu_levelmask[0], &"
                else:
                    p1 = "uint8_t  gpu_levelmask, double *"
                    r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
                    p2 = "gpu_levelmask, &"
                    r2 = "gpu_levelmask[0], &"
                    #p3 = ", gpu_cfl_clipping, &"
                    #p4 = "(gpu_cfl_clipping, &"
                    p5 = "uint8_t in_arr = gpu_cfl_clipping;"
                    r5 = "uint8_t in_arr = gpu_cfl_clipping[((_for_it_22 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];"
                    p6 = "uint8_t  gpu_cfl_clipping,"
                    r6 = "uint8_t* __restrict__  gpu_cfl_clipping,"
                    line = line.replace(p5, r5).replace(p6, r6)
                line2 = line.replace(p1, r1).replace(p2, r2)
                file.write(line2)
                i += 1
    else:
        with open(filepath, "r") as file:
            lines = file.readlines()
        with open(filepath, "w") as file:
            i = 0
            while i < len(lines):
                line = lines[i]
                if host:
                    p1 = "uint8_t  gpu_levelmask, double *"
                    r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
                    p2 = "__state->__0_gpu_levelmask, &"
                    r2 = "&__state->__0_gpu_levelmask[0], &"
                else:
                    p1 = "uint8_t gpu_levelmask, double *"
                    r1 = "uint8_t* __restrict__  gpu_levelmask, double *"
                    p2 = "&__state->__0_gpu_levelmask, &"
                    r2 = "&__state->__0_gpu_levelmask[0], &"
                    #p3 = ", gpu_cfl_clipping, &"
                    #p4 = "(gpu_cfl_clipping, &"
                    p5 = "uint8_t in_arr = gpu_cfl_clipping;"
                    r5 = "uint8_t in_arr = gpu_cfl_clipping[((_for_it_22 + (tmp_struct_symbol_14 * (_for_it_35 - 1))) - 1)];"
                    p6 = "uint8_t  gpu_cfl_clipping,"
                    r6 = "uint8_t* __restrict__  gpu_cfl_clipping,"
                    line = line.replace(p5, r5).replace(p6, r6)
                p7 = ", &gpu_levelmask,"
                r7 = ", &gpu_levelmask[0],"
                line2 = line.replace(p1, r1).replace(p2, r2).replace(p7, r7)
                file.write(line2)
                i += 1

def add_reduce_clean_up_calls(filepath: str):
    pattern1 = "DACE_EXPORTED int __dace_exit_velocity_no_nproma_if_prop"
    with open(filepath, "r") as file:
        lines = file.readlines()
    with open(filepath, "w") as file:
        i = 0
        while i < len(lines):
            if pattern1 in lines[i]:
                assert i < len(lines)
                assert lines[i+1].strip() == "{"
                line = lines[i]
                file.write(line)
                file.write("{\n")
                file.write("cleanup_reduce_sum_gpu();\n")
                file.write("cleanup_reduce_maxZ_gpu();\n")
                i += 1
            else:
                line = lines[i]
                file.write(line)
            i += 1

def comment_out_syncs(filepath: str, gpu: bool):
    # comment out (prepend //) any line containing cudaStreamSynchronize
    vcflmax_count = 0
    added_one = False
    with open(filepath, "r") as file:
        lines = file.readlines()
    with open(filepath, "w") as file:
        for line in lines:
            if ("cudaStreamSynchronize" in line) or ("EventRecord" in line) or ("StreamWaitEvent" in line):
                if ("stop" in line) or ("start" in line):
                    # or ("ExitStreamSync" in line) or ("EntryStreamSync" in line)
                    line = line
                else:
                    line = "//" + line
            if "tmp_call_18 = -1.7976931348623157e+308;" in line:
                if gpu:
                    line = "DACE_GPU_CHECK(cudaStreamSynchronize(__state->gpu_context->streams[0]));\n" + line
                else:
                    line = "//" + line
            file.write(line)

def comment_out_allocs_and_frees(filepath: str, name_set: typing.Set[str]):
    with open(filepath, 'r') as file:
        lines = file.readlines()

    modified_lines = []
    lines_to_comment = set()  # Track which line indices to comment out

    for i, line in enumerate(lines):
        line_stripped = line.strip()

        # Skip if line is already commented out
        if line_stripped.startswith('//'):
            continue

        should_comment = False

        for name in name_set:
            # Pattern 1: delete[] name;
            if ('delete[]' in line or 'delete' in line) and name in line and ';' in line:
                should_comment = True
                break

            # Pattern 2: cudaFree(name)
            if 'cudaFree' in line and name in line and '(' in line and ')' in line:
                should_comment = True
                break

            # Pattern 3: cudaMalloc with name
            if 'cudaMalloc' in line and name in line and '(' in line and ')' in line:
                should_comment = True
                break

            # Pattern 4: name = new
            if name in line and '=' in line and 'new' in line and 'DACE_ALIGN' in line:
                should_comment = True
                break

        if should_comment:
            lines_to_comment.add(i)  # Comment current line

    # Build the modified lines
    for i, line in enumerate(lines):
        if i in lines_to_comment:
            # Preserve original indentation and add // comment
            leading_whitespace = line[:len(line) - len(line.lstrip())]
            commented_line = leading_whitespace + '//' + line.lstrip()
            modified_lines.append(commented_line)
        else:
            modified_lines.append(line)

    # Write back to file
    with open(filepath, 'w') as file:
        file.writelines(modified_lines)

def use_solve_nh_struct_definitions(filepath: str):
    struct_names = {
        "global_data_type",
        "t_tangent_vectors",
        "t_grid_edges",
        "t_nh_metrics",
        "t_prepare_adv",
        "t_nh_ref",
        "t_nh_prog",
        "t_nh_diag",
        "t_nh_state",
        "t_grid_domain_decomp_info",
        "t_grid_cells",
        "t_int_state",
        "t_grid_vertices",
        "t_patch",
    }

    """
    Script to remove struct definitions and forward declarations for specified struct names.
    Usage: python struct_cleaner.py <file_path> <struct_name1> <struct_name2> ...
    """

    def filter_structs(content, struct_names):
        """Remove struct definitions and forward declarations for specified struct names."""
        lines = content.split('\n')
        filtered_lines = []
        struct_set = set(struct_names)

        i = 0
        while i < len(lines):
            line = lines[i]
            stripped = line.strip()

            # Check for forward declaration: struct name;
            fwd_match = re.match(r'\s*struct\s+(\w+)\s*;', line)
            if fwd_match and fwd_match.group(1) in struct_set:
                i += 1
                continue

            # Check for struct definition: struct name {
            def_match = re.search(r'\bstruct\s+(\w+)\s*\{', line)
            if def_match and def_match.group(1) in struct_set:
                # Skip until we find };
                i += 1
                while i < len(lines) and lines[i].strip() != '};':
                    i += 1
                i += 1  # Skip the }; line too
                continue

            filtered_lines.append(line)
            i += 1

        return '\n'.join(filtered_lines)


    with open(filepath, 'r') as f:
        content = f.read()

    filtered_content = filter_structs(content, struct_names)

    with open(filepath, 'w') as f:
        f.write('#include "shared_struct_defs.h"\n')
        f.write(filtered_content)


pass_by_copy_to_pass_by_ref_tuples = [
    ("double", "__CG_p_diag__m_max_vcfl_dyn"),
]

def _replace_pass_by_copy_to_pass_by_ref_impl(path, type_name_tuples):
    with open(path, 'r') as f:
        content = f.read()

    for type_name, name in type_name_tuples:
        pattern = rf' {re.escape(type_name)} {re.escape(name)},'
        content = re.sub(pattern, rf'{type_name}& {name},', content)
    for type_name, name in type_name_tuples:
        pattern = rf' {re.escape(type_name)} {re.escape(name)}[)]'
        content = re.sub(pattern, rf'{type_name}& {name})', content)

    with open(path, 'w') as f:
        f.write(content)

def replace_pass_by_copy_to_pass_by_ref(path: str):
    """
    Replace pass-by-copy parameters with pass-by-reference in the given file.
    This is used to avoid unnecessary copies of large data structures.
    """
    _replace_pass_by_copy_to_pass_by_ref_impl(path, pass_by_copy_to_pass_by_ref_tuples)

def compile_if_propagated_sdfgs(
    sdfgs: typing.List[dace.SDFG],
    gpu: bool,
    release: bool,
    generate_code: bool,
    lib: bool,
    main_name: None | str,
    stage: int,
    debuginfo: bool,
    allocation_names_to_comment_out: set | None,
    use_openacc_stream: bool,
):
    compare_structs(sdfgs)

    use_nvhpc = os.getenv('_USE_NVHPC', '0').lower() in ('1', 'true', 'yes')
    dace.Config.set('compiler', 'cuda', 'max_concurrent_streams', value="1")
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
                """
                for node, graph in sdfg.all_nodes_recursive():
                    if "vcflmax" in graph.sdfg.arrays:
                        graph.sdfg.arrays["vcflmax"].storage = dace.dtypes.StorageType.CPU_Heap
                        assert graph.sdfg.arrays["vcflmax"].storage == dace.dtypes.StorageType.CPU_Heap
                    if "gpu_vcflmax" in graph.sdfg.arrays:
                        graph.sdfg.arrays["gpu_vcflmax"].storage = dace.dtypes.StorageType.GPU_Global
                        assert graph.sdfg.arrays["gpu_vcflmax"].storage == dace.dtypes.StorageType.GPU_Global
                """
                # Set the LibNode schedules back to GPU if input/output is GPU global
                """
                from utils.reductions import LibNode
                b = False
                for node, graph in sdfg.all_nodes_recursive():
                    if isinstance(node, LibNode) or isinstance(node, dace.nodes.LibraryNode) or isinstance(node, dace.nodes.Tasklet) or isinstance(node, dace.nodes.CodeNode):
                        in_array_names = [e.src.data for e in graph.in_edges(node) if isinstance(e.src, dace.nodes.AccessNode)]
                        out_array_names = [e.dst.data for e in graph.out_edges(node) if isinstance(e.dst, dace.nodes.AccessNode)]
                        arrays = set()
                        for in_name in in_array_names:
                            arrays.add(graph.sdfg.arrays[in_name])
                        for out_name in out_array_names:
                            arrays.add(graph.sdfg.arrays[out_name])
                        real_arrays = set([array for array in arrays if isinstance(array, dace.data.Array)])
                        all_gpu = all(
                            (isinstance(array, dace.data.Array) and array.storage == dace.dtypes.StorageType.GPU_Global) for array in real_arrays
                        )
                        if all_gpu:
                            b = True
                            node.schedule = dace.dtypes.ScheduleType.GPU_Device
                assert b, "No GPU LibNode found in SDFG"
                """
                sdfg.save(sdfg.name + "_concretized.sdfgz", compress=True)
                #sdfg.validate() # Schedule problem here

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
            #add_timers(f"{build_loc}/src/cpu/{sdfg_name}.cpp", gpu, stage)
            # insert_measure_time_calls(build_loc, sdfg, instrument)
            #if fix_out_val_0:
            #      fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &cfl_clipping")
            #      fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &maxvcfl_arr")
            #      fix_out_val_0_call(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "out_val_0, &z_w_con_c")
        if gpu:
            _replace_cpp_with_cu(build_loc)
            if stage > 5 and rm_syncs:
                comment_out_syncs(f"{build_loc}/src/cpu/{sdfg_name}.cu", gpu)
            #assert allocation_names_to_comment_out is not None, "Allocation names to comment out must be provided for GPU code generation"
            #assert use_openacc_stream is True
            if allocation_names_to_comment_out is not None:
                assert stage == 9, "Allocation names to comment out are only supported in stage 9"
                comment_out_allocs_and_frees(f"{build_loc}/src/cpu/{sdfg_name}.cu", allocation_names_to_comment_out)
            if use_openacc_stream:
                assert stage == 9, "OpenACC stream is only supported in stage 9"
                assert gpu is True, "OpenACC stream is only supported for GPU code"
                change_to_openacc_stream(
                    f"{build_loc}/src/cpu/{sdfg_name}.cu",
                    f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu",
                    gpu
                )
            add_reduce_clean_up_calls(f"{build_loc}/src/cpu/{sdfg_name}.cu")
            #This fix is needed for uint8_t
            fix_levelmask_calls(f"{build_loc}/src/cpu/{sdfg_name}.cu", True, stage)
            if stage > 5:
                fix_levelmask_calls(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", False, stage)

            if stage > 5:
                with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "r") as file:
                    main_cu_code = file.read()
                with open(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "w") as file:
                    file.write(
                        '#include "reductions_device.cuh"\n#define __REDUCE_DEVICE__\n'
                        + main_cu_code
                    )
                repl_in_file(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu", "const const", "const")
                repl_in_file(f"{build_loc}/src/cpu/{sdfg_name}.cu", "const const", "const")
                repl_in_file_per_line_with_cond(
                    f"{build_loc}/src/cpu/{sdfg_name}.cu",
                    "double __CG_p_diag__m_max_vcfl_dyn",
                    "double &__CG_p_diag__m_max_vcfl_dyn",
                    condition=lambda line: "double __CG_p_diag__m_max_vcfl_dyn" in line and "__CG_p_diag__m_max_vcfl_dyn;" not in line
                )
                repl_in_file_per_line_with_cond(
                    f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu",
                    "double __CG_p_diag__m_max_vcfl_dyn",
                    "double &__CG_p_diag__m_max_vcfl_dyn",
                    condition=lambda line: "double __CG_p_diag__m_max_vcfl_dyn" in line and "__CG_p_diag__m_max_vcfl_dyn;" not in line
                )
            #if fix_out_val_0:
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_cfl_clipping")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_z_w_con_c")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_maxvcfl_arr")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_levmask")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_maxvcfl_arr")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "gpu_out_val_0, &gpu_cfl_clipping")
            #    fix_out_val_0_call(f"{build_loc}/src/cuda/{sdfg.name}_cuda.cu", "out_val_0, &gpu_levmask")
            if stage > 5:
                sources.add(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu")
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cu", "w") as file:
                file.write(
                    '#include "reductions_kernel.cuh"\n#include "reductions_cpu.h"\n#include "timer.h"\n'
                    + main_cu_code
                )

            if stage == 8 or stage == 9:
                set_default_stream(f"{build_loc}/src/cpu/{sdfg_name}.cu")
                set_default_stream(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu")

            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cu")
        else:
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "r") as file:
                main_cu_code = file.read()
            with open(f"{build_loc}/src/cpu/{sdfg_name}.cpp", "w") as file:
                file.write(
                    '#include "reductions_cpu.h"\n#include "timer.h"\n' + main_cu_code
                )
            sources.add(f"{build_loc}/src/cpu/{sdfg.name}.cpp")

        _build_for_integration = os.getenv('_BUILD_LIB_FOR_SOLVE_NH', '0').lower() in ('1', 'true', 'yes')
        if _build_for_integration:
            if stage == 1 or stage == 9:
                if not gpu:
                    use_solve_nh_struct_definitions(f"{build_loc}/src/cpu/{sdfg_name}.cpp")
                else:
                    if stage == 1:
                        use_solve_nh_struct_definitions(f"{build_loc}/src/cpu/{sdfg_name}.cu")
                    else:
                        use_solve_nh_struct_definitions(f"{build_loc}/src/cpu/{sdfg_name}.cu")
                        use_solve_nh_struct_definitions(f"{build_loc}/src/cuda/{sdfg_name}_cuda.cu")
            if not gpu:
                replace_pass_by_copy_to_pass_by_ref(f"{build_loc}/src/cpu/{sdfg_name}.cpp")
                replace_pass_by_copy_to_pass_by_ref(f"{build_loc}/include/{sdfg_name}.h")
            else:
                replace_pass_by_copy_to_pass_by_ref(f"{build_loc}/src/cpu/{sdfg_name}.cu")
                replace_pass_by_copy_to_pass_by_ref(f"{build_loc}/include/{sdfg_name}.h")


    if main_name is not None:
        sources.add(f"{main_name}")
    else:
        if not gpu:
            if not lib:
                sources.add("main.cc")
        else:
            if not lib:
                sources.add("main_gpu.cu")

    nvhpc_flags = "-ccbin=nvc++" if use_nvhpc else ""


    supress_flags = "--diag-suppress 68 --diag-suppress 550 --diag-suppress 20208 --diag-suppress 1835 --diag-suppress 177 --diag-suppress 20012 --diag-suppress 1098"
    no_nvhpc_flags = "-Wconversion -Wno-sign-conversion -Wfloat-conversion -Wno-unknown-pragmas -faligned-new" if not use_nvhpc else ""
    no_nvhpc_flags_gpu = "-Xcompiler=-Wconversion -Xcompiler=-Wsign-conversion -Xcompiler=-Wfloat-conversion -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-faligned-new" if not use_nvhpc else ""
    if gpu:
        debuginfo_flags = "-lineinfo" if debuginfo else ""
    else:
        debuginfo_flags = "-g" if debuginfo else ""
    nvhpc_flags += "  " if use_nvhpc else ""

    cuda_arch = os.getenv('_CUDA_ARCH', 'native')
    if gpu:
        if release:
            flags = f" {nvhpc_flags} {supress_flags} {no_nvhpc_flags_gpu} -DNDEBUG -Xcompiler=-DNDEBUG -Xcompiler=-Wall -Xcompiler=-Wextra  -Xcompiler=-O3 --expt-relaxed-constexpr -arch={cuda_arch} --use_fast_math -O3 {debuginfo_flags} --ftz=true --prec-div=false --prec-sqrt=false --fmad=true -Xptxas=-O3 -Xptxas=-v -Xcompiler=-march=native -Xcompiler=-mtune=native --restrict -Xcompiler=-fopenmp --relocatable-device-code=true -rdc=true -dlto -DNDEBUG"
        else:
            flags = f" {supress_flags} {no_nvhpc_flags_gpu} -DNDEBUG -Xcompiler=-Wall -Xcompiler=-Wextra --expt-relaxed-constexpr -arch={cuda_arch} -O0 -Xcompiler=-O0 -G {debuginfo_flags} --fmad=false --prec-div=true --prec-sqrt=true --ftz=false "
        if lib:
            flags += " -DNO_SERDE -std=c++17 -rdc=true -Xcompiler=-fPIC --compiler-options '-fPIC' --shared "
        else:
            flags += " -std=c++20 "
    else:
        if release:
            flags = f" {no_nvhpc_flags} {debuginfo_flags} -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -fopenmp -O3 -DNDEBUG"
        else:
            flags = f" {no_nvhpc_flags} -std=c++20 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unknown-pragmas -O0 -ggdb {debuginfo_flags} "

    dace_include = os.path.dirname(dace.__file__) + "/runtime/include/"
    if gpu:
        if not lib:
            compile_cmd = f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_gpu"
        else:
            compile_cmd = f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o libvelocity_gpu.so"
    else:
        if not lib:
            compile_cmd = f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_cpu"
        else:
            compile_cmd = f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o libvelocity_cpu.so"

    print(f"Compiling: {compile_cmd}")
    exit_code = os.system(compile_cmd)

    # check if compilation was successful
    if exit_code != 0:
        if gpu:
            print(f"nvcc {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_gpu")
        else:
            print(f"c++ {' '.join(sources)} -I{build_loc}/include -I{dace_include} {' '.join(headers)} {flags} -o velocity_cpu")
        print("Compilation failed")
        exit(1)
