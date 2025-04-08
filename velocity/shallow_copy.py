import re

def _check_flattener_assignment(line):
    tokens = line.split()
    if len(tokens) == 4:
        if (tokens[-1].startswith("__CG_") and
            "=" == tokens[-2] and
            tokens[-3].startswith("__cg_")):
            return True

def _check_deflattener_assignment(line):
    "double *__cg_p_prog__m_w                                 = &__CG_p_prog__m_w[0];"
    tokens = line.split()
    if len(tokens) == 4:
        if (tokens[-1].startswith("&__CG_") and
            "=" == tokens[-2] and
            tokens[-3].startswith("__cg_")):
            return True

setzero_str0_1="""
{
for (int i = 0; i < tmp_struct_symbol_12; i++){
    __state->__0_vcflmax[i] = 0.0;
}

{
cudaStream_t stream = __state->gpu_context->streams[0];
cudaMemsetAsync(__state->__0_gpu_levelmask, 0, 90 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_maxvcfl_arr, 0, (((87 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (87 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_v, 0, (((91 * tmp_struct_symbol_6) * (tmp_struct_symbol_7 - 1)) + (91 * tmp_struct_symbol_6)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_cfl_clipping, 0, (91 * tmp_struct_symbol_14) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c, 0, (91 * tmp_struct_symbol_1) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_levmask, 0, (90 * tmp_struct_symbol_13) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_concorr_mc, 0, (90 * tmp_struct_symbol_0) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_zeta, 0, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c_full, 0, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_out_val_0, 0, 89 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_v_grad_w, 0, (((90 * tmp_struct_symbol_4) * (tmp_struct_symbol_5 - 1)) + (90 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_ekinh, 0, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double), stream);
}
}
"""
setzero_str0_2="""
{
for (int i = 0; i < tmp_struct_symbol_12; i++){
    __state->__0_vcflmax[i] = 0.0;
}

{
cudaStream_t stream = __state->gpu_context->streams[0];
cudaMemsetAsync(__state->__0_gpu_levelmask, 0, 90 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_maxvcfl_arr, 0, (((87 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (87 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_v, 0, (((91 * tmp_struct_symbol_6) * (tmp_struct_symbol_7 - 1)) + (91 * tmp_struct_symbol_6)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_cfl_clipping, 0, (91 * tmp_struct_symbol_14) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c, 0, (91 * tmp_struct_symbol_1) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_levmask, 0, (90 * tmp_struct_symbol_13) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_zeta, 0, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c_full, 0, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_out_val_0, 0, 89 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_v_grad_w, 0, (((90 * tmp_struct_symbol_4) * (tmp_struct_symbol_5 - 1)) + (90 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_ekinh, 0, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double), stream);
}
}
"""
setzero_str1_1="""
{
for (int i = 0; i < tmp_struct_symbol_12; i++){
    __state->__0_vcflmax[i] = 0.0;
}

{
cudaStream_t stream = __state->gpu_context->streams[0];
cudaMemsetAsync(__state->__0_gpu_levelmask, 0, 90 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_maxvcfl_arr, 0, (((87 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (87 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_cfl_clipping, 0, (91 * tmp_struct_symbol_14) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c, 0, (91 * tmp_struct_symbol_1) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_levmask, 0, (90 * tmp_struct_symbol_13) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_concorr_mc, 0, (90 * tmp_struct_symbol_0) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_zeta, 0, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c_full, 0, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_out_val_0, 0, 89 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_ekinh, 0, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double), stream);
}
}
"""
setzero_str1_2="""
{
for (int i = 0; i < tmp_struct_symbol_12; i++){
    __state->__0_vcflmax[i] = 0.0;
}

{
cudaStream_t stream = __state->gpu_context->streams[0];
cudaMemsetAsync(__state->__0_gpu_levelmask, 0, 90 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_maxvcfl_arr, 0, (((87 * tmp_struct_symbol_4) * (tmp_struct_symbol_11 - 1)) + (87 * tmp_struct_symbol_4)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_cfl_clipping, 0, (91 * tmp_struct_symbol_14) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c, 0, (91 * tmp_struct_symbol_1) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_levmask, 0, (90 * tmp_struct_symbol_13) * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_zeta, 0, (((90 * tmp_struct_symbol_8) * (tmp_struct_symbol_9 - 1)) + (90 * tmp_struct_symbol_8)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_z_w_con_c_full, 0, (((90 * tmp_struct_symbol_2) * (tmp_struct_symbol_3 - 1)) + (90 * tmp_struct_symbol_2)) * sizeof(double), stream);
cudaMemsetAsync(__state->__0_gpu_out_val_0, 0, 89 * sizeof(int), stream);
cudaMemsetAsync(__state->__0_gpu_z_ekinh, 0, (((90 * tmp_struct_symbol_10) * (tmp_struct_symbol_11 - 1)) + (90 * tmp_struct_symbol_10)) * sizeof(double), stream);
}
}
"""
setzerodict = {
    "lvn_only_0_istep_1": setzero_str0_1,
    "lvn_only_0_istep_2": setzero_str0_2,
    "lvn_only_1_istep_1": setzero_str1_1,
    "lvn_only_1_istep_2": setzero_str1_2,
}

gpu_inputs = ["z_w_concorr_me", "z_vt_ie", "z_kin_hor_e"]

def process_file(input_path, flattener_replacement_path, deflattener_replacement_path, output_path_removed, output_path_cleaned):
    with open(input_path, 'r') as infile:
        lines = infile.readlines()

    with open(flattener_replacement_path, 'r') as repfile1:
        flattener_replacement_lines = repfile1.readlines()
    with open(deflattener_replacement_path, 'r') as repfile2:
        deflattener_replacement_lines = repfile2.readlines()

    cleaned_lines = []
    removed_lines = []

    # Compile all regex patterns
    pattern_cg_alloc = re.compile(r'^\s*__CG\w*\s*=\s*new\b.*;')
    pattern_lower_assign = re.compile(r'^\s*\w+\.lower\(\)\s*=\s*.*;')
    pattern_memcpy_gpu = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaMemcpyAsync\s*\(\s*gpu___CG_.*')
    pattern_malloc_gpu = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaMalloc\s*\(\s*\(void\*\*\)\s*&gpu___CG_.*')
    pattern_delete_cg = re.compile(r'^\s*delete\[\]\s+__CG_.*;')
    pattern_cuda_free = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaFree\s*\(\s*gpu___CG_.*\)\s*\)\s*;')
    pattern_cuda_memcpy2 = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaMemcpyAsync\s*\(\s*__CG_.*\)\s*\)\s*;')
    inside_flatten_block = False
    flatten_inserted = False
    inside_deflatten_block = False
    deflatten_inserted = False

    first_rm_free = True
    for line in lines:
        # Detect and remove flatten block
        if '// Start flatten' in line:
            inside_flatten_block = True
            removed_lines.append(line)
            continue
        elif '// End flatten' in line:
            inside_flatten_block = False
            removed_lines.append(line)
            cleaned_lines.extend(flattener_replacement_lines)
            if "lvn_only_0_istep_1" in input_path:
                setzero_str = setzerodict["lvn_only_0_istep_1"]
            elif "lvn_only_0_istep_2" in input_path:
                setzero_str = setzerodict["lvn_only_0_istep_2"]
            elif "lvn_only_1_istep_1" in input_path:
                setzero_str = setzerodict["lvn_only_1_istep_1"]
            elif "lvn_only_1_istep_2" in input_path:
                setzero_str = setzerodict["lvn_only_1_istep_2"]
            cleaned_lines.extend(setzero_str)
            flatten_inserted = True
            continue

        if '// Start deflatten' in line:
            inside_deflatten_block = True
            removed_lines.append(line)
            continue
        elif '// End deflatten' in line:
            inside_deflatten_block = False
            removed_lines.append(line)
            cleaned_lines.extend(deflattener_replacement_lines)
            deflatten_inserted = True
            continue


        if inside_flatten_block or inside_deflatten_block:
            removed_lines.append(line)
            continue

        specific_remvoes = ["__CG_global_data__m_nproma = __cg_global_data__m_nproma;",
                            "__CG_p_diag__m_max_vcfl_dyn = __cg_p_diag__m_max_vcfl_dyn;"]
        cont = False
        for sr in specific_remvoes:
            if sr in line:
                removed_lines.append(line)
                cont = True
        if cont:
            continue

        if _check_flattener_assignment(line) or _check_deflattener_assignment(line):
            removed_lines.append(line)
            continue

        gpu_inputs = ["z_w_concorr_me", "z_vt_ie", "z_kin_hor_e"]

        # Modify the pattern matching to specifically check for these variables
        pattern_malloc_gpu_ins = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaMalloc\s*\(\s*\(void\*\*\)\s*&gpu_(' + '|'.join(gpu_inputs) + r')\s*.*\);')
        pattern_cuda_free_ins = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaFree\s*\(\s*gpu_(' + '|'.join(gpu_inputs) + r')\)\s*\)\s*;')
        pattern_memcpy_gpu_ins = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaMemcpyAsync\s*\(\s*(gpu_(' + '|'.join(gpu_inputs) + r'))|(' + '|'.join(gpu_inputs) + r')\s*,\s*gpu_(' + '|'.join(gpu_inputs) + r')\s*\)\s*;')
        pattern_cuda_free_ins2 = re.compile(r'^\s*DACE_GPU_CHECK\(\s*cudaFree\s*\(\s*(' + '|'.join(gpu_inputs) + r')\)\s*\)\s*;')

        if pattern_malloc_gpu_ins.search(line):
            for gpuin in gpu_inputs:
                if gpuin in line:
                    cleaned_lines.append(f"gpu_{gpuin} = {gpuin};\n")

        # Match any of the removal patterns

        if (
            pattern_cg_alloc.search(line) or
            pattern_lower_assign.search(line) or
            pattern_memcpy_gpu.search(line) or
            pattern_malloc_gpu.search(line) or
            pattern_delete_cg.search(line) or
            pattern_cuda_free.search(line) or
            pattern_cuda_memcpy2.search(line) or
            pattern_malloc_gpu_ins.search(line) or
            pattern_cuda_free_ins.search(line) or
            pattern_memcpy_gpu_ins.search(line) or
            pattern_cuda_free_ins2.search(line)
        ):
            removed_lines.append(line)
        else:
            donot = False
            for gpuin in gpu_inputs:
                if f"DACE_GPU_CHECK(cudaMemcpyAsync({gpuin}, gpu_{gpuin}" in line:
                    print(f"DACE_GPU_CHECK(cudaMemcpyAsync({gpuin}, gpu_{gpuin}... Warning: {gpuin} is used in a memcpy operation.")
                    removed_lines.append(line)
                    donot = True
                    if first_rm_free:
                        first_rm_free = False
                        cleaned_lines.append("cudaDeviceSynchronize();\n")
                    break

            if not donot:
                cleaned_lines.append(line)



    # Write to output files
    with open(output_path_removed, 'w') as removed_file:
        removed_file.writelines(removed_lines)

    with open(output_path_cleaned, 'w') as cleaned_file:
        cleaned_file.writelines(cleaned_lines)

    if not flatten_inserted:
        print("Warning: No '// Start flatten' block was found.")
    if not deflatten_inserted:
        print("Warning: No '// Start deflatten' block was found.")

fnames = [
    "velocity_no_nproma_if_prop_lvn_only_0_istep_1",
    "velocity_no_nproma_if_prop_lvn_only_0_istep_2",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_1",
    "velocity_no_nproma_if_prop_lvn_only_1_istep_2",
]

def process_files(
    sdfg_names=[fname for fname in fnames],
):
    for sname in sdfg_names:
        process_file(
            input_path=f'.dacecache/{sname}/src/cpu/{sname}.cu',
            flattener_replacement_path=f'./{sname}_flattener_code.cpp',
            deflattener_replacement_path=f'./{sname}_deflattener_code.cpp',
            output_path_removed=f'{sname}_removed_lines.txt',
            output_path_cleaned=f'.dacecache/{sname}/src/cpu/{sname}.cu'
        )

def combine_files(file_paths, output_path):
    combined_lines = set()

    # Read lines from each file and add them to the set
    for file_path in file_paths:
        with open(file_path, 'r') as file:
            combined_lines.update(file.readlines())

    # Write the combined unique lines to a new file
    with open(output_path, 'w') as output_file:
        output_file.writelines(sorted(combined_lines))

# Example usage: combining 4 files
combine_files(
    file_paths=[fname + "_flattener_code.cpp" for fname in fnames],
    output_path='combined.cpp'
)
process_files(fnames)