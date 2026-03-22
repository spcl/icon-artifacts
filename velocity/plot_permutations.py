import re, glob, os, sys, argparse
import numpy as np
import matplotlib.pyplot as plt

pattern = re.compile(r"\[Timer\] Elapsed time: ([\d.]+) ms")

def place_text(ax, positions):
    """positions: list of (x, y, label) sorted by x. Nudges y to avoid overlaps."""
    placed = []
    for x, y, label in sorted(positions, key=lambda p: p[0]):
        y_clear = y
        for px, py, _ in placed:
            if abs(px - x) < 0.6:  # same x-neighborhood
                if abs(y_clear - py) < 1.2:  # overlap threshold (tune to your ms scale)
                    y_clear = py + 1.2
        placed.append((x, y_clear, label))
        ax.text(x, y_clear, label, ha="center", va="bottom", fontsize=8)

def load_folder(folder):
    violin_data = {}
    star_points = {}
    for f in glob.glob(os.path.join(folder, "*.txt")):
        name = os.path.basename(f).replace(".txt", "")
        with open(f) as fh:
            times = [float(m.group(1)) for line in fh if (m := pattern.search(line))]
        if not times:
            continue
        if name == "unpermuted" or name.endswith("shuffled"):
            violin_data[name] = times
        else:
            star_points[name] = np.median(times)
    return violin_data, star_points

def plot_panel(ax, violin_data, star_points, title, label_order=None):
    baseline_key = "unpermuted"
    baseline_median = (
        np.median(violin_data[baseline_key]) if baseline_key in violin_data else None
    )

    if label_order is None:
        other_violin = {k: v for k, v in violin_data.items() if k != baseline_key}
        sorted_other = sorted(other_violin, key=lambda k: np.median(other_violin[k]))
        sorted_stars = sorted(star_points.items(), key=lambda x: x[1])
        label_order = (
            ([baseline_key] if baseline_key in violin_data else [])
            + sorted_other
            + [k for k, _ in sorted_stars]
        )

    configs = [l for l in label_order if l in violin_data]
    star_keys = [l for l in label_order if l in star_points]

    vals = [violin_data[cfg] for cfg in configs]
    if vals:
        vp = ax.violinplot([violin_data[cfg] for cfg in configs],
                           positions=[label_order.index(c) + 1 for c in configs],
                           showmeans=True)
        for body, cfg in zip(vp["bodies"], configs):
            color = "green" if cfg == baseline_key else "blue"
            body.set_facecolor(color); body.set_edgecolor(color); body.set_alpha(0.7)

    # --- collect all speedup annotations ---
    text_positions = []

    for cfg in configs:
        med = np.median(violin_data[cfg])
        speedup = baseline_median / med if baseline_median else 1
        x = label_order.index(cfg) + 1
        if speedup > 1:
            text_positions.append((x, med * 1.1, speedup))

    for cfg in star_keys:
        val = star_points[cfg]
        speedup = baseline_median / val if baseline_median else 1
        x = label_order.index(cfg) + 1
        if speedup > 1:
            text_positions.append((x, val * 1.1, speedup))

    if text_positions:
        best = text_positions[0]
        ax.text(best[0], best[1], f"{best[2]:.2f}x", ha="center", va="bottom", fontsize=8)

    ax.set_xticks(range(1, len(label_order) + 1))
    ax.set_xticklabels(label_order, rotation=90, ha="center", fontsize=7)
    ax.set_ylabel("Time (ms)")
    ax.set_title(title)
    ax.grid(True, axis="both", linestyle="--", alpha=0.5)




# ---- Argument parsing ----
parser = argparse.ArgumentParser(
    description="Violin plot for permuted/shuffled timing results.",
    formatter_class=argparse.RawTextHelpFormatter,
)
parser.add_argument("--cpu",  default="beverin_permutations_4", metavar="DIR",
                    help="Folder with CPU results (vendor 1)")
parser.add_argument("--gpu",  default="beverin_permutations_6", metavar="DIR",
                    help="Folder with GPU results (vendor 1)")
parser.add_argument("--cpu2", default=None, metavar="DIR",
                    help="Folder with CPU results (vendor 2)")
parser.add_argument("--gpu2", default=None, metavar="DIR",
                    help="Folder with GPU results (vendor 2)")
args = parser.parse_args()

# Build ordered panel list: cpu1, gpu1, cpu2, gpu2
panels = []
if args.cpu:
    panels.append((args.cpu,  "CPU"))
if args.gpu:
    panels.append((args.gpu,  "GPU"))
if args.cpu2:
    panels.append((args.cpu2, "CPU (Vendor 2)"))
if args.gpu2:
    panels.append((args.gpu2, "GPU (Vendor 2)"))

if not panels:
    parser.error("Provide at least one of --cpu, --gpu, --cpu2, --gpu2.")

# ---- Build figure ----
# Load all data first
panel_data = [(folder, title, *load_folder(folder)) for folder, title in panels]

# Derive global label order from GPU vendor 1 (first --gpu panel)
gpu1 = next(((vd, sp) for f, t, vd, sp in panel_data if t == "GPU"), None)
if gpu1:
    vd, sp = gpu1
    baseline_key = "unpermuted"
    other_violin = {k: v for k, v in vd.items() if k != baseline_key}
    sorted_other = sorted(other_violin, key=lambda k: np.median(other_violin[k]))
    sorted_stars = sorted(sp.items(), key=lambda x: x[1])
    global_order = (
        ([baseline_key] if baseline_key in vd else [])
        + sorted_other
        + [k for k, _ in sorted_stars]
    )
else:
    global_order = None  # fallback: each panel sorts itself

n = len(panels)
fig, axes = plt.subplots(n, 1, figsize=(10, 5 * n))
if n == 1:
    axes = [axes]

for ax, (folder, title, violin_data, star_points) in zip(axes, panel_data):
    if not violin_data and not star_points:
        ax.set_title(f"{title}  [no data found in {folder}]"); continue
    plot_panel(ax, violin_data, star_points, title, label_order=global_order)

fig.tight_layout()
fig.savefig("violin_plot.png", dpi=200)
print("Saved violin_plot.png")