files = [
    "z_vt_ie",
    "z_kin_hor_e",
    "z_w_concorr_me"
]

import numpy as np
import re

def read_entries_from_file(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()

    entries = []
    reading_entries = False
    for line in lines:
        line = line.strip()
        if line.startswith("# entries"):
            reading_entries = True
            continue
        if reading_entries:
            try:
                entries.append(float(line))
            except ValueError:
                break  # Stop reading if we reach a non-numeric line

    return np.array(entries)

def max_abs_difference(file1, file2):
    entries1 = read_entries_from_file(file1)
    entries2 = read_entries_from_file(file2)

    if entries1.shape != entries2.shape:
        raise ValueError("Entry arrays have different sizes!")

    return np.max(np.abs(entries1 - entries2))

for f in files:
    got_file = f"{f}.got"
    want_file = f"{f}.want"

    print(f"Comparing {got_file} with {want_file}...")
    try:
        difference = max_abs_difference(got_file, want_file)
        print(f"Max absolute difference: {difference}")
    except Exception as e:
        print(f"Error: {e}")