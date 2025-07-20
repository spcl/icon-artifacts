import re
import dace
from typing import Dict, List

def parse_function_arguments(header_text):
    """
    Parse function header to extract argument types and names, removing __restrict__ qualifiers.
    Can handle multiple functions in the same header.
    Function format:
    <function_name>(
    <arg_type> <arg_name>,
    <arg_type> <arg_name>,
    ...
    );

    Args:
        header_text (str): The function header text

    Returns:
        dict: Dictionary with function names as keys and lists of [arg_type, arg_name] as values
    """
    lines = [line.strip() for line in header_text.strip().split('\n')]
    all_functions = {}

    i = 0
    while i < len(lines):
        line = lines[i]

        # Find function name line (contains opening parenthesis, not comment)
        if '(' in line and not line.startswith("#") and not line.startswith('//'):
            func_line_idx = i

            # Extract function name
            func_line = lines[func_line_idx]
            func_name = func_line.split('(')[0].strip()

            # Process argument lines (after the function name line until we find );)
            arguments = []
            j = func_line_idx + 1

            while j < len(lines):
                arg_line = lines[j].strip()

                # Skip empty lines
                if not arg_line:
                    j += 1
                    continue

                # Stop when we hit the closing );
                if arg_line.endswith(');') or arg_line == ');':
                    # Handle case where last argument is on same line as );
                    if not arg_line.startswith(');'):
                        clean_arg = arg_line.replace(');', '').strip()
                        if clean_arg.endswith(','):
                            clean_arg = clean_arg[:-1].strip()
                        if clean_arg:
                            arguments.append(clean_arg)
                    break

                # Remove trailing comma if present
                if arg_line.endswith(','):
                    arg_line = arg_line[:-1].strip()

                arguments.append(arg_line)
                j += 1

            # Parse each argument to extract type and name
            parsed_args = []
            for arg in arguments:
                if not arg:
                    continue

                # Remove __restrict__ qualifier
                arg = re.sub(r'\b__restrict__\b', '', arg).strip()

                # Clean up multiple spaces
                arg = re.sub(r'\s+', ' ', arg)

                # Split into tokens
                tokens = arg.split()
                if len(tokens) >= 2:
                    # Last token is the argument name
                    arg_name = tokens[-1]
                    # Everything else is the type
                    arg_type = ' '.join(tokens[:-1])
                    if arg_name.startswith("*") or arg_name.startswith("&"):
                        # Handle pointer or reference types
                        ref_or_ptr = arg_name[0]
                        arg_name = arg_name[1:]
                        arg_type += f" {ref_or_ptr}"

                    parsed_args.append([arg_type, arg_name])

            all_functions[func_name] = parsed_args
            i = j + 1  # Continue from after the current function
        else:
            i += 1

    return all_functions


velocity_shim_template = """
#ifndef __VELOCITY_SHIM_H__
#define __VELOCITY_SHIM_H__

#include "shared_struct_defs.h"
#include <dace/dace.h>

#if defined(GPU)

#error "GPU Implementation TODO"

#else

#include "velocity.h"

static velocity_no_nproma_if_prop_lvn_only_1_istep_1_state_t *state_lvn_only_1_istep_1 = nullptr;
static velocity_no_nproma_if_prop_lvn_only_1_istep_2_state_t *state_lvn_only_1_istep_2 = nullptr;
static velocity_no_nproma_if_prop_lvn_only_0_istep_1_state_t *state_lvn_only_0_istep_1 = nullptr;
static velocity_no_nproma_if_prop_lvn_only_0_istep_2_state_t *state_lvn_only_0_istep_2 = nullptr;

static void velocity_tendencies(
    {velocity_tendencies_args}
){{
    static int lvn_only_1_istep_1_call_id = 0;
    static int lvn_only_1_istep_2_call_id = 0;
    static int lvn_only_0_istep_1_call_id = 0;
    static int lvn_only_0_istep_2_call_id = 0;

    if (lvn_only == 1 && istep == 1) {{
        if (lvn_only_1_istep_1_call_id == 0) {{
            state_lvn_only_1_istep_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
                {velocity_lvn_only_1_istep_1_args}
            );
        }}
        lvn_only_1_istep_1_call_id++;
        __program_velocity_no_nproma_if_prop_lvn_only_1_istep_1(
            state_lvn_only_1_istep_1,
            {velocity_lvn_only_1_istep_1_args}
        );
    }} else if (lvn_only == 1 && istep == 2) {{
        if (lvn_only_1_istep_2_call_id == 0) {{
            state_lvn_only_1_istep_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
            {velocity_lvn_only_1_istep_2_args}
            );
        }}
        lvn_only_1_istep_2_call_id++;
        __program_velocity_no_nproma_if_prop_lvn_only_1_istep_2(
            state_lvn_only_1_istep_2,
            {velocity_lvn_only_1_istep_2_args}
        );
    }} else if (lvn_only == 0 && istep == 1) {{
        if (lvn_only_0_istep_1_call_id == 0) {{
            state_lvn_only_0_istep_1 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
            {velocity_lvn_only_0_istep_1_args}
            );
        }}
        lvn_only_0_istep_1_call_id++;
        __program_velocity_no_nproma_if_prop_lvn_only_0_istep_1(
            state_lvn_only_0_istep_1,
            {velocity_lvn_only_0_istep_1_args}
        );
    }} else if (lvn_only == 0 && istep == 2) {{
        if (lvn_only_0_istep_2_call_id == 0) {{
            state_lvn_only_0_istep_2 = __dace_init_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
            {velocity_lvn_only_0_istep_2_args}
            );
        }}
        lvn_only_0_istep_2_call_id++;
        __program_velocity_no_nproma_if_prop_lvn_only_0_istep_2(
            state_lvn_only_0_istep_2,
            {velocity_lvn_only_0_istep_2_args}
        );
    }}
}}

static void exit_velocity_tendencies() {{
    if (state_lvn_only_1_istep_1 != nullptr) {{
        __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_1(state_lvn_only_1_istep_1);
        state_lvn_only_1_istep_1 = nullptr;
    }}
    if (state_lvn_only_1_istep_2 != nullptr) {{
        __dace_exit_velocity_no_nproma_if_prop_lvn_only_1_istep_2(state_lvn_only_1_istep_2);
        state_lvn_only_1_istep_2 = nullptr;
    }}
    if (state_lvn_only_0_istep_1 != nullptr) {{
        __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_1(state_lvn_only_0_istep_1);
        state_lvn_only_0_istep_1 = nullptr;
    }}
    if (state_lvn_only_0_istep_2 != nullptr) {{
        __dace_exit_velocity_no_nproma_if_prop_lvn_only_0_istep_2(state_lvn_only_0_istep_2);
        state_lvn_only_0_istep_2 = nullptr;
    }}
}}

#endif // GPU
#endif // __VELOCITY_SHIM_H__
"""

def _has_velocity_tendencies(sdfg: dace.SDFG) -> bool:
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.Tasklet) and ("velocity_tendencies" in node.name  or "velocity_tendencies" in node.label):
                return True
    return False



def gen_caller():
    pass

def _generate_velocity_shim(velocity_header: str, velocity_shim_output: str,
                            sdfgs: List[dace.SDFG], typed_inputs):
    results = parse_function_arguments(velocity_header)
    velocity_tendencies_args = list()
    velocity_lvn_only_1_istep_1_args = list()
    velocity_lvn_only_1_istep_2_args = list()
    velocity_lvn_only_0_istep_1_args = list()
    velocity_lvn_only_0_istep_2_args = list()
    name_mapping = dict()

    # For all functions ensure all variables except the state is available.
    # If input argument is scalar (pass-by-copy, or pass-by-ref), the input can be either a scalar or a symbol
    # If input is a pass-by-ptr, then it has to be an array

    starts_with_repl_rules = [
        ("__CG_p_diag", "__CG_p_nh__CG_diag"),
        ("__CG_p_metrics", "__CG_p_nh__CG_metrics"),
        ("__CG_p_prog__m_vn", "__CG_p_nh_prog_nnew__m_vn"),
        ("__CG_p_prog__m_w", "__CG_p_nh_prog_nnew__m_w"),
    ]

    struct_names_to_skip = [
        "p_diag",
        "p_metrics",
        "p_prog"
    ]

    struct_name_mapping = {
        "p_diag": "in_p_nh->diag",
        "p_metrics": "in_p_nh->metrics",
        "p_prog": "in_p_nh_prog_nnew",
    }

    symbol_mapping = {
        "__f2dace_A_z_kin_hor_e_d_0_s" : "in_global_data->nproma",
        "__f2dace_A_z_kin_hor_e_d_1_s" : "in_p_patch->nlev",
        "__f2dace_A_z_kin_hor_e_d_2_s" : "in_p_patch->nblks_e",
        "__f2dace_A_z_vt_ie_d_0_s" : "in_global_data->nproma",
        "__f2dace_A_z_vt_ie_d_1_s" : "in_p_patch->nlev",
        "__f2dace_A_z_vt_ie_d_2_s" : "in_p_patch->nblks_e",
        "__f2dace_A_z_w_concorr_me_d_0_s" : "in_global_data->nproma",
        "__f2dace_A_z_w_concorr_me_d_1_s" : "in_p_patch->nlev",
        "__f2dace_A_z_w_concorr_me_d_2_s" : "in_p_patch->nblks_e",
        "__f2dace_OA_z_kin_hor_e_d_0_s" : "1",
        "__f2dace_OA_z_kin_hor_e_d_1_s" : "1",
        "__f2dace_OA_z_kin_hor_e_d_2_s" : "1",
        "__f2dace_OA_z_vt_ie_d_0_s" : "1",
        "__f2dace_OA_z_vt_ie_d_1_s" : "1",
        "__f2dace_OA_z_vt_ie_d_2_s" : "1",
        "__f2dace_OA_z_w_concorr_me_d_0_s" : "1",
        "__f2dace_OA_z_w_concorr_me_d_1_s" : "1",
        "__f2dace_OA_z_w_concorr_me_d_2_s" : "1",
        "ldeepatmo": "in_global_data->ldeepatmo",
        "dt_linintp_ubc": "in_dt_linintp_ubc",
        "dtime": "in_dtime",
    }

    symbols_to_skip = {
        "lvn_only",
        "istep",
        "ntnd",
    }

    unioned_arg_types_and_names = list()
    for func_name, args in results.items():
        for arg_type, arg_name in args:
            if "__staet" in arg_name:
                continue
            if (arg_type, arg_name) not in unioned_arg_types_and_names:
                unioned_arg_types_and_names.append((arg_type, arg_name))

    for sdfg in sdfgs:
        if not _has_velocity_tendencies(sdfg):
            continue
        for arg_type, arg_name in unioned_arg_types_and_names:
            if arg_name in struct_names_to_skip:
                name_mapping[arg_name] = struct_name_mapping[arg_name]
                continue
            if arg_name in symbol_mapping:
                name_mapping[arg_name] = symbol_mapping[arg_name]
                continue
            if arg_name in symbols_to_skip:
                continue
            if "__state" in arg_name:
                continue
            if "*" in arg_type:
                # Array
                original_name = arg_name
                exhausted = False
                while (arg_name not in sdfg.arrays) and (not exhausted):
                    for start, repl in starts_with_repl_rules:
                        #print(start, repl, original_name, arg_name)
                        if original_name.startswith(start):
                            arg_name = arg_name.replace(start, repl)
                            #print(f"  Replacing {original_name} with {arg_name} in SDFG {sdfg.name}")
                    exhausted = True

                assert arg_name in sdfg.arrays, f"Array {arg_name} not found in SDFG {sdfg.name}"

                if original_name in name_mapping:
                    assert name_mapping[original_name] == "in_" + arg_name, \
                        f"Array {original_name} mapped to {name_mapping[original_name]} but found {arg_name} in SDFG {sdfg.name}"
                else:
                    name_mapping[original_name] = "in_" + arg_name


            else:
                original_name = arg_name
                exhausted = False
                while (arg_name not in sdfg.arrays) and (not exhausted):
                    for start, repl in starts_with_repl_rules:
                        #print(start, repl, original_name, arg_name)
                        if original_name.startswith(start):
                            arg_name = arg_name.replace(start, repl)
                            #print(f"  Replacing {original_name} with {arg_name} in SDFG {sdfg.name}")
                    exhausted = True

                # Scalar / Symbol
                assert arg_name in sdfg.symbols or (arg_name in sdfg.arrays and isinstance(sdfg.arrays[arg_name], dace.data.Scalar)), f"Scalar/Symbol {arg_name} not found in SDFG {sdfg.name}"

                assert arg_name not in sdfg.symbols
                name_mapping[original_name] = "in_" + arg_name


    # Now we know we can use the args as they are
    print("Velocity Tendencies Function Arguments That Are Arrays and Scalars:")
    for key, val in name_mapping.items():
        print(f"  {key} (Velocity Tendencies Function Name) -> {val} (SDFG Name)")

    print("Symbols To Manually Fix:")
    for key in symbols_to_skip:
        print(f"  {key} (Manual) -> ?")

    print("Args in Order of Velocity Tendencies:")

    print("AS DICT:")
    print("name_mapping = {")
    for key, val in name_mapping.items():
        print(f"  '{key}': '{val}',")
    print("}")

    velocity_tendencies_args_list = []
    for arg_type, arg_name in unioned_arg_types_and_names:
        if "_state" in arg_name:
            continue  # Skip state arguments
        velocity_tendencies_args_list.append(f"{arg_type} {arg_name}")
    velocity_tendencies_args_str = ",\n        ".join(velocity_tendencies_args_list)

    call_args_ll = []
    for fun_name in ["lvn_only_1_istep_1",
                     "lvn_only_1_istep_2",
                     "lvn_only_0_istep_1",
                     "lvn_only_0_istep_2"]:
        key, val = None, None
        for _key, _val in result.items():
            if fun_name in _key and "_program" in _key:
                key, val = _key, _val
                break
        assert key is not None and val is not None, f"Function {fun_name} not found in results"
        call_str = ",\n            ".join(v[1] for v in val)
        call_args_ll.append(call_str)

    sstr = velocity_shim_template.format(
        velocity_tendencies_args=velocity_tendencies_args_str,
        velocity_lvn_only_1_istep_1_args=call_args_ll[0],
        velocity_lvn_only_1_istep_2_args=call_args_ll[1],
        velocity_lvn_only_0_istep_1_args=call_args_ll[2],
        velocity_lvn_only_0_istep_2_args=call_args_ll[3]
    )

    with open(velocity_shim_output, 'w') as f:
        f.write(sstr)


# Example usage
if __name__ == "__main__":
    header_path = 'include/velocity.h'
    header_shim_path = 'include/velocity_shim.h'
    with open(header_path, 'r') as f:
        header = f.read()
    result = parse_function_arguments(header)
    print("Parsed result:")
    for func_name, args in result.items():
        print(f"Function: {func_name}")
        for arg_type, arg_name in args:
            print(f"  {arg_type} -> {arg_name}")

    sdfg_paths = [
        "codegen/gpu_solve_nh_corrector_post_stage1.sdfgz",
        "codegen/gpu_solve_nh_corrector_pre_stage1.sdfgz",
        "codegen/gpu_solve_nh_predictor_pre_stage1.sdfgz",
        "codegen/gpu_solve_nh_predictor_post_stage1.sdfgz",
    ]
    sdfgs = [dace.SDFG.from_file(path) for path in sdfg_paths]

    _generate_velocity_shim(header, header_shim_path, sdfgs, result)
