import os
import numpy as np


def compare_got_and_want():
    # Precision for double precision floating point numbers
    abs_tol = np.finfo(np.float64).eps
    rel_tol = np.finfo(np.float64).eps

    # Get list of .got and .want files
    got_files = [f for f in os.listdir() if f.endswith(".got")]
    want_files = [f.replace(".got", ".want") for f in got_files]
    assert len(got_files) == len(
        [f for f in os.listdir() if f.endswith(".want")]
    ), "Number of .got and .want files do not match"

    # Compare each .got file with its corresponding .want file
    found_diff_all = False
    for got, want in zip(got_files, want_files):
        found_diff = False
        max_rel_diff = 0
        max_abs_diff = 0
        with open(got, "r") as got_file, open(want, "r") as want_file:
            got_lines = got_file.readlines()
            want_lines = want_file.readlines()

            if len(got_lines) != len(want_lines):
                print(f"{got} and {want} have different number of lines ❌")
                found_diff = True
                continue

            # lines containing text should be identical, lines containing numbers should be close
            for got_line, want_line in zip(got_lines, want_lines):
                # Are the lines floating point numbers?
                try:
                    got_num = float(got_line)
                    want_num = float(want_line)

                    abs_diff = abs(got_num - want_num)
                    rel_diff = 0
                    if want_num != 0:
                        rel_diff = abs_diff / abs(want_num)
                    max_rel_diff = max(max_rel_diff, rel_diff)
                    max_abs_diff = max(max_abs_diff, abs_diff)

                    if abs_diff > abs_tol or rel_diff > rel_tol:
                        print(f"{got} and {want} have numerical differences ❌")
                        found_diff = True
                        break

                except ValueError:
                    # If not, they should be identical
                    if got_line != want_line:
                        print(f"{got} and {want} have different text ❌")
                        found_diff = True
                        break
        if not found_diff:
            print(f"{got} and {want} are OK ✅")
        print(f"  Rel: {max_rel_diff}, Abs: {max_abs_diff}")
        found_diff_all = found_diff_all or found_diff

    if not found_diff_all:
        print("No numerical differences found ✅")
    else:
        print("Numerical differences found ❌")

if __name__ == "__main__":
    compare_got_and_want()