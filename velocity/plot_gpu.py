#!/usr/bin/env python3
"""
plot_stage8_gpu.py

2×2 violin plot for stage-8 GPU results.
  rows    : step7 (lvn_only=0, istep=1)  /  step9 (lvn_only=1, istep=2)
  columns : Beverin (MI300A)             /  Daint (GH200)

Only "unpermuted" and "nlev_first_shuffled" are plotted.

Y-axis cap heuristic
  - Collect all values in the panel.
  - If max > OUTLIER_FACTOR × p95, cap at p95 × CAP_MARGIN  (outliers present).
  - Otherwise let matplotlib choose its own upper limit, then scale it by
    NATURAL_MARGIN to add a little breathing room.
"""

import re, glob, os, argparse
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Patch

# ── Constants ──────────────────────────────────────────────────────────────────
PATTERN       = re.compile(r"\[Timer\] Elapsed time: ([\d.]+) ms")
BASELINE_KEY  = "unpermuted"
TARGET_KEY    = "nlev_first_shuffled"
KEEP_KEYS     = {BASELINE_KEY, TARGET_KEY}

OUTLIER_FACTOR = 1.5   # if max > factor × p95 → outliers present
CAP_MARGIN     = 1.10  # cap = p95 × this
NATURAL_MARGIN = 1.05  # no outliers → matplotlib top × this

STEP_CONFIG = {
    7: "(lvn\_only=0, istep=1)",   # raw string used in titles
    9: "(lvn\_only=1, istep=2)",
}

VCOL = {
    BASELINE_KEY: "#555555",   # dark grey
    TARGET_KEY:   "#2980b9",   # blue
}
VLAB = {
    BASELINE_KEY: "Unpermuted (baseline)",
    TARGET_KEY:   "nlev\_first\_shuffled",
}

# ── Data loading ───────────────────────────────────────────────────────────────
def load_folder(folder: str, step: int) -> dict[str, list[float]]:
    """Return {name: [times]} keeping only KEEP_KEYS for the given step."""
    raw: dict[str, list[float]] = {}
    for f in glob.glob(os.path.join(folder, "*.txt")):
        basename = os.path.basename(f).replace(".txt", "")
        # Filter by step suffix
        has_step = re.search(r"_step\d+$", basename)
        if has_step and not basename.endswith(f"_step{step}"):
            continue
        name = re.sub(r"_step\d+$", "", basename)
        if name not in KEEP_KEYS:
            continue
        with open(f) as fh:
            times = [float(m.group(1)) for line in fh if (m := PATTERN.search(line))]
        if times:
            raw.setdefault(name, []).extend(times)
    return raw


# ── Y-axis cap ─────────────────────────────────────────────────────────────────
def compute_ylim(ax, all_values: list[float]) -> float | None:
    """
    Returns a cap value if outliers are detected, else None (let mpl decide).
    Caller applies a small natural margin in the None case.
    """
    if not all_values:
        return None
    arr = np.array(all_values)
    p95 = np.percentile(arr, 95)
    vmax = arr.max()
    if vmax > OUTLIER_FACTOR * p95:
        return p95 * CAP_MARGIN
    return None   # no bad outliers


# ── Panel plotting ─────────────────────────────────────────────────────────────
def plot_panel(ax, data: dict[str, list[float]], title: str) -> None:
    plot_order = [k for k in [BASELINE_KEY, TARGET_KEY] if k in data]
    positions  = list(range(1, len(plot_order) + 1))

    # ── Violins ────────────────────────────────────────────────────────────────
    if plot_order:
        vp = ax.violinplot(
            [data[k] for k in plot_order],
            positions=positions,
            showmeans=True,
            showmedians=True,
            showextrema=True,
        )
        for body, key in zip(vp["bodies"], plot_order):
            body.set_facecolor(VCOL[key])
            body.set_edgecolor("black")
            body.set_alpha(0.75)
        vp["cmeans"].set_color("black")
        vp["cmedians"].set_color("white")
        for part in ("cbars", "cmins", "cmaxes"):
            if part in vp:
                vp[part].set_color("black")
                vp[part].set_linewidth(1.0)

    # ── Speedup annotation ─────────────────────────────────────────────────────
    if BASELINE_KEY in data and TARGET_KEY in data:
        base_med   = np.median(data[BASELINE_KEY])
        target_med = np.median(data[TARGET_KEY])
        if base_med > 0:
            speedup = base_med / target_med
            x = plot_order.index(TARGET_KEY) + 1
            y = target_med
            ax.text(x, y * 1.04, f"{speedup:.2f}×",
                    ha="center", va="bottom", fontsize=10, fontweight="bold",
                    color=VCOL[TARGET_KEY])

    # ── Y-axis cap ─────────────────────────────────────────────────────────────
    all_vals = [v for vals in data.values() for v in vals]
    cap = compute_ylim(ax, all_vals)
    if cap is not None:
        ax.set_ylim(bottom=0, top=cap)
    else:
        ax.set_ylim(bottom=0)
        current_top = ax.get_ylim()[1]
        ax.set_ylim(top=current_top * NATURAL_MARGIN)

    # ── Axes decoration ────────────────────────────────────────────────────────
    ax.set_xticks(positions)
    ax.set_xticklabels([VLAB[k] for k in plot_order], fontsize=10)
    ax.set_ylabel("Time (ms)")
    ax.set_title(title, fontsize=11)
    ax.grid(True, axis="y", linestyle="--", alpha=0.4)
    ax.set_xlim(0.5, len(plot_order) + 0.5)


# ── Main ───────────────────────────────────────────────────────────────────────
def none_or_str(v):
    return None if v.lower() == "none" else v

parser = argparse.ArgumentParser(
    description="2×2 violin plot: stage-8 GPU results (Beverin vs Daint, step7 vs step9).",
    formatter_class=argparse.RawTextHelpFormatter,
)
parser.add_argument("--gpu",        default="beverin_full_permutations_8", metavar="DIR", type=none_or_str)
parser.add_argument("--gpu2",       default="daint_full_permutations_8",   metavar="DIR", type=none_or_str)
parser.add_argument("--gpu-title",  default="AMD MI300A",                  metavar="STR")
parser.add_argument("--gpu2-title", default="NVIDIA GH200",                metavar="STR")
parser.add_argument("--out",        default="plots/violin_stage8_gpu.png", metavar="FILE")
args = parser.parse_args()

for attr, path in [("gpu", args.gpu), ("gpu2", args.gpu2)]:
    if not os.path.isdir(path):
        parser.error(f"Folder '{path}' not found (--{attr.replace('_','-')}).")

plt.rcParams.update({
    "font.size": 12, "axes.titlesize": 11, "axes.labelsize": 11,
    "xtick.labelsize": 10, "ytick.labelsize": 10, "legend.fontsize": 10,
})

fig, axes = plt.subplots(2, 2, figsize=(10, 8), sharey="row")
fig.suptitle("Velocity Tendencies — Layout Permutation (Stage 8, GPU)",
             fontsize=14, y=0.98)

STEP_ROW = [(7, 0), (9, 1)]
PLATFORM_COL = [
    (args.gpu,  args.gpu_title,  0),
    (args.gpu2, args.gpu2_title, 1),
]

# Map step → config string (no LaTeX escaping needed for mpl text)
STEP_CFG_LABEL = {
    7: "lvn_only=0, istep=1",
    9: "lvn_only=1, istep=2",
}

for step, row in STEP_ROW:
    for folder, plat_title, col in PLATFORM_COL:
        ax    = axes[row][col]
        data  = load_folder(folder, step)
        title = f"{plat_title}  (step{step}: {STEP_CFG_LABEL[step]})"
        if not data:
            ax.set_title(f"{title}\n[no data]")
            ax.set_visible(True)
            continue
        plot_panel(ax, data, title)

    # Share y-axis label only on left column
    axes[row][1].set_ylabel("")

# ── Legend (shared, bottom centre) ────────────────────────────────────────────
handles = [
    Patch(facecolor=VCOL[BASELINE_KEY], edgecolor="black", label=VLAB[BASELINE_KEY]),
    Patch(facecolor=VCOL[TARGET_KEY],   edgecolor="black", label=VLAB[TARGET_KEY]),
]
fig.legend(handles=handles, loc="lower center",
           bbox_to_anchor=(0.5, 0.0), ncol=2, framealpha=0.9)

fig.tight_layout(rect=[0, 0.05, 1, 0.97])
fig.savefig(args.out, dpi=200, bbox_inches="tight")
plt.close(fig)
print(f"Saved {args.out}")