import re
import sys
import matplotlib.pyplot as plt
import math

if len(sys.argv) != 2:
    print(f"Usage: python {sys.argv[0]} <filename>")
    sys.exit(1)

filename = sys.argv[1]

# Data containers
configs = []
percent_nz_count = []
percent_nz_rows = []
percent_nz_cols = []

with open(filename, 'r') as f:
    lines = f.readlines()

i = 0
while i < len(lines):
    line = lines[i]
    match = re.match(r'\s*Called istep=(\d+), lvn_only=(\d+)', line)
    if match:
        istep = int(match.group(1))
        lvn_only = int(match.group(2))
        configs.append(f"istep={istep}, lvn={lvn_only}")

        # Look for next 3 relevant lines
        count_line = lines[i+2].strip()
        row_line = lines[i+3].strip()
        col_line = lines[i+4].strip()

        # Extract numbers
        nz_count, total_count = map(int, re.findall(r'\d+', count_line))
        nz_rows, total_rows = map(int, re.findall(r'\d+', row_line))
        nz_cols, total_cols = map(int, re.findall(r'\d+', col_line))

        # Compute percentages
        percent_nz_count.append(nz_count / total_count)
        percent_nz_rows.append(nz_rows / total_rows)
        percent_nz_cols.append(nz_cols / total_cols)

        i += 5
    else:
        i += 1

# Plotting
x = range(len(configs))
width = 0.25

for y, name in [(percent_nz_count, "nnz_vals"), (percent_nz_rows, "nnz_rows"), (percent_nz_cols, "nnz_cols")]:
    plt.figure(figsize=(25, 6))
    plt.bar([p - width for p in x], y, width, label=name)
    #plt.bar(x, percent_nz_rows, width, label="Non-zero rows")
    #plt.bar([p + width for p in x], percent_nz_cols, width, label="Non-zero cols")
    max_val = max(y)
    ymax = math.ceil(max_val * 5) / 5.0  # Rounds up to nearest multiple of 0.2
    plt.ylim(0.0, ymax + 0.05)  # Add a small margin above the max value
    plt.xticks(ticks=[], labels=[], fontsize=18)
    plt.yticks(fontsize=18)
    plt.ylabel("Fraction (0.0 to 1.0)")
    plt.title("CFL Clipping Sparsity Statistics", fontsize=18)
    plt.legend(loc='lower center', bbox_to_anchor=(0.5, -0.25), fontsize=18, ncol=1)
    plt.tight_layout()
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.savefig(f"cfl_clipping_{name}_sparsity.png", dpi=300)
