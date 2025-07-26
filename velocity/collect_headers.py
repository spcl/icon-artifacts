import re

def extract_function_declarations(header_paths):
    matches = []
    keywords = ("__dace_exit_", "__dace_init_", "__program_")

    for path in header_paths:
        try:
            with open(path, 'r') as f:
                for line in f:
                    stripped = line.strip()
                    if any(k in stripped for k in keywords) and stripped.endswith(';'):
                        matches.append(stripped)
        except Exception as e:
            print(f"Error reading {path}: {e}")

    return matches

# Example usage:
if __name__ == "__main__":
    headers = [
        "codegen/stage9/velocity_no_nproma_if_prop_lvn_only_0_istep_1/include/velocity_no_nproma_if_prop_lvn_only_0_istep_1.h",
        "codegen/stage9/velocity_no_nproma_if_prop_lvn_only_0_istep_2/include/velocity_no_nproma_if_prop_lvn_only_0_istep_2.h",
        "codegen/stage9/velocity_no_nproma_if_prop_lvn_only_1_istep_1/include/velocity_no_nproma_if_prop_lvn_only_1_istep_1.h",
        "codegen/stage9/velocity_no_nproma_if_prop_lvn_only_1_istep_2/include/velocity_no_nproma_if_prop_lvn_only_1_istep_2.h"
    ]

    functions = extract_function_declarations(headers)

    print("Extracted Function Declarations:\n")
    for func in functions:
        print(func)

    with open("velocity_header.h", "w") as output_file:
        for func in functions:
            output_file.write(func + "\n\n")
