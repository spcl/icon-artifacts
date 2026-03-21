import re, glob, os, sys
import numpy as np
import matplotlib.pyplot as plt

folder = sys.argv[1] if len(sys.argv) > 1 else "."
pattern = re.compile(r"\[Timer\] Elapsed time: ([\d.]+) ms")

data = {}
for f in glob.glob(os.path.join(folder, "*.txt")):
    name = os.path.basename(f).replace(".txt", "")
    with open(f) as fh:
        times = [float(m.group(1)) for line in fh if (m := pattern.search(line))]
    if not times:
        continue
    if name == "unpermuted":
        cfg = "unpermuted"
        data[cfg] = times
    else:
        data[name] = times

configs = sorted(data.keys())
vals = [data[cfg] for cfg in configs]
colors = ["green" if cfg == "unpermuted" else "blue" for cfg in configs]

baseline_median = np.median(data["unpermuted"]) if "unpermuted" in data else None

fig, ax = plt.subplots()
vp = ax.violinplot(vals, showmeans=True)
for body, c in zip(vp["bodies"], colors):
    body.set_facecolor(c)
    body.set_edgecolor(c)
    body.set_alpha(0.7)

# Speedup annotations
if baseline_median is not None:
    for i, cfg in enumerate(configs):
        med = np.median(data[cfg])
        speedup = baseline_median / med
        ax.text(i + 1, min(med * 1.2, med + 0.15), f"{speedup:.2f}x", ha="center", va="bottom", fontsize=8)

ax.set_xticks(range(1, len(configs) + 1))
ax.set_xticklabels(configs, rotation=90, ha="center", fontsize=7)
ax.set_ylabel("Time (ms)")
ax.grid(True, axis="both", linestyle="--", alpha=0.5)
fig.tight_layout()
fig.savefig("violin_plot.png", dpi=200)