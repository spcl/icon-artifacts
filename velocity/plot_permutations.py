import glob
import re
import numpy as np
import matplotlib.pyplot as plt

# Regex to extract timing
pattern = re.compile(r"\[Timer\] Elapsed time:\s*([0-9.]+)\s*ms")

data = {}
files = sorted(glob.glob("permutations/*.txt"))

for fname in files:
    if "job_output" in fname or "job_error" in fname:
        continue

    times = []

    with open(fname, "r") as f:
        for line in f:
            m = pattern.search(line)
            if m:
                times.append(float(m.group(1)))

    # Optional: drop first (warmup)
    if len(times) > 1:
        times = times[1:]

    if times:
        key = fname.replace("permutations/", "").replace(".txt", "")
        data[key] = times

# =========================
# 📊 SORT BY MEDIAN
# =========================
sorted_items = sorted(data.items(), key=lambda x: np.median(x[1]))
labels = [k for k, _ in sorted_items]
values = [v for _, v in sorted_items]
medians = np.array([np.median(v) for v in values])

# =========================
# 🎻 VIOLIN PLOT
# =========================
plt.figure(figsize=(16, 7))

plt.violinplot(values, showmeans=True, showmedians=True)

plt.xticks(range(1, len(labels) + 1), labels, rotation=90)
plt.ylabel("Runtime (ms)")
plt.title("Runtime Distribution per Configuration")

# ---- GRID (major + minor) ----
plt.grid(True, which='major', linestyle='-', linewidth=0.6, alpha=0.7)
plt.grid(True, which='minor', linestyle='--', linewidth=0.4, alpha=0.5)
plt.minorticks_on()

plt.tight_layout()
plt.savefig("permutations_stage6_violin.png", dpi=300)
plt.close()

# =========================
# ⚡ SPEEDUP SCATTER (vs unpermuted)
# =========================

# Find baseline
baseline_key = None
for k in data.keys():
    if "unpermuted" in k:
        baseline_key = k
        break

if baseline_key is None:
    raise ValueError("Could not find 'unpermuted' baseline!")

baseline_median = np.median(data[baseline_key])

# Compute medians and speedups
labels = []
speedups = []

for k, v in data.items():
    med = np.median(v)
    sp = baseline_median / med
    labels.append(k)
    speedups.append(sp)

# Sort by speedup (optional but recommended)
sorted_items = sorted(zip(labels, speedups), key=lambda x: x[1], reverse=True)
labels, speedups = zip(*sorted_items)

# ---- Plot ----
plt.figure(figsize=(16, 6))

x = np.arange(len(labels))

plt.scatter(x, speedups, s=120)  # thick dots

plt.xticks(x, labels, rotation=90)
plt.ylabel("Speedup vs Unpermuted (median)")
plt.title("Speedup per Configuration")

# Grid (nice + readable)
plt.grid(True, which='major', linestyle='-', linewidth=0.6, alpha=0.7)
plt.grid(True, which='minor', linestyle='--', linewidth=0.4, alpha=0.5)
plt.minorticks_on()

# Annotate values
for xi, sp in zip(x, speedups):
    plt.text(xi, sp, f"{sp:.2f}x", ha='center', va='bottom', fontsize=8)

plt.tight_layout()
plt.savefig("permutations_stage6_speedup_scatter.png", dpi=300)
plt.close()