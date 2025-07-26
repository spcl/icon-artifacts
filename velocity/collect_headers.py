import re

def extract_function_declarations(header_paths):
    function_decls = []

    # Regular expression to match function declarations.
    # This assumes simple non-templated functions, not inside a class.
    func_pattern = re.compile(r"""
        ^                                  # Start of line
        [\w:\*\&\s]+?                      # Return type (non-greedy)
        \s+                                # At least one space
        [\w:~]+                            # Function name
        \s*                                # Optional space
        \(                                 # Opening parenthesis
        [^;{}]*                            # Parameters (no semicolon or braces allowed here)
        \)                                 # Closing parenthesis
        \s*                                # Optional space
        (const)?                           # Optional const
        \s*                                # Optional space
        (;|$)                              # Ends with semicolon or EOL (if macro-generated)
        """, re.VERBOSE)

    for path in header_paths:
        try:
            with open(path, 'r') as file:
                for line in file:
                    line = line.strip()
                    if func_pattern.match(line):
                        function_decls.append(line)
        except FileNotFoundError:
            print(f"File not found: {path}")
        except Exception as e:
            print(f"Error reading {path}: {e}")

    return function_decls


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
