#!/usr/bin/env python3
"""
plot_gpu.py

2×1 violin plot for stage-8 GPU permutation results.
  rows       : AMD MI300A (Beverin)  /  NVIDIA GH200 (Daint)
  x-elements : 4 violins per panel, grouped in 2 config pairs
               [Original | Cost-Model]   [Original | Cost-Model]
               ←─ lvn_only=0, istep=1 ─→ ←─ lvn_only=1, istep=2 ─→
  color      : orange = Original Layout, blue = Cost-Model Suggested
"""

import re, glob, os, argparse
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.transforms as transforms
from matplotlib.patches import Patch

# ── Constants ──────────────────────────────────────────────────────────────────
PATTERN      = re.compile(r"\[Timer\] Elapsed time: ([\d.]+) ms")
BASELINE_KEY = "unpermuted"
TARGET_KEY   = "nlev_first_shuffled"
KEEP_KEYS    = {BASELINE_KEY, TARGET_KEY}

VCOL = {
    BASELINE_KEY: "#e67e22",   # orange
    TARGET_KEY:   "#2980b9",   # blue
}
VLAB = {
    BASELINE_KEY: "Original Layout",
    TARGET_KEY:   "Cost-Model Suggested",
}

# step → (x-group label, x positions for [baseline, target])
CONFIGS = [
    (7,  "Config. LVN Only=1", 1, 2),   # step, label, pos_base, pos_target
    (9,  "Config. LVN Only=0", 4, 5),
]
GAP_CENTRE = 3   # visual gap between groups — no violin plotted here

# ── Data loading ───────────────────────────────────────────────────────────────
def load_folder(folder: str, step: int) -> dict[str, list[float]]:
    raw: dict[str, list[float]] = {}
    for f in glob.glob(os.path.join(folder, "*.txt")):
        basename = os.path.basename(f).replace(".txt", "")
        has_step = re.search(r"_step\d+$", basename)
        if has_step and not basename.endswith(f"_step{step}"):
            continue
        name = re.sub(r"_step\d+$", "", basename)
        if name not in KEEP_KEYS:
            continue
        with open(f) as fh:
            times = [float(m.group(1))
                     for line in fh if (m := PATTERN.search(line))]
        if times:
            raw.setdefault(name, []).extend(times)
    return raw


# ── Panel plotting ─────────────────────────────────────────────────────────────
def plot_panel(ax, folder: str, platform_title: str) -> None:
    # Collect all data for ylim computation
    all_vals_global = []
    plot_specs = []   # (key, pos, data_array)

    for step, cfg_label, pos_base, pos_target in CONFIGS:
        data = load_folder(folder, step)
        for key, pos in [(BASELINE_KEY, pos_base), (TARGET_KEY, pos_target)]:
            if key in data:
                arr = np.array(data[key])
                all_vals_global.extend(arr.tolist())
                plot_specs.append((key, pos, arr, step))

    if not plot_specs:
        ax.set_title(f"{platform_title}\n[no data]")
        return

    # ── Violins ────────────────────────────────────────────────────────────────
    positions_list = [pos for _, pos, _, _ in plot_specs]
    data_list      = [arr for _, _, arr, _ in plot_specs]
    colors_list    = [VCOL[key] for key, _, _, _ in plot_specs]

    vp = ax.violinplot(
        data_list,
        positions=positions_list,
        showmeans=True,
        showmedians=True,
        showextrema=True,
        widths=0.7,
    )
    for body, color in zip(vp["bodies"], colors_list):
        body.set_facecolor(color)
        body.set_edgecolor("black")
        body.set_alpha(0.75)
    vp["cmeans"].set_color("black")
    vp["cmedians"].set_color("white")
    for part in ("cbars", "cmins", "cmaxes"):
        if part in vp:
            vp[part].set_color("black")
            vp[part].set_linewidth(1.0)

    # ── Y limits: full data range, no forced zero, modest headroom ────────────
    arr_all = np.array(all_vals_global)
    vmin, vmax = arr_all.min(), arr_all.max()
    margin = 0.2 * (vmax - vmin) if vmax > vmin else 1.0
    if "AMD" in platform_title:
        vmin -= 0.8
    else:
        vmin -= 0.05
    ax.set_ylim(bottom=vmin * 0.95 - margin * 0.3, top=vmax + margin * 2.0)
    ylo, yhi = ax.get_ylim()
    y_range  = yhi - ylo
    # Store for post-draw tick unification
    ax._data_ylo = ylo
    ax._data_yhi = yhi

    # ── Per-violin annotations ─────────────────────────────────────────────────
    for key, pos, arr, step in plot_specs:
        med      = np.median(arr)
        arr_max  = arr.max()
        arr_min  = arr.min()
        color    = VCOL[key]

        # Median: above violin top, right-offset, italic
        ax.text(pos - 0.45, arr_max + 0.01 * y_range,
                f"med. {med:.3f} ms",
                ha="left", va="bottom",
                fontsize=9, color=color, fontstyle="italic")

    # ── Speedup annotations per config group ───────────────────────────────────
    for step, cfg_label, pos_base, pos_target in CONFIGS:
        data = load_folder(folder, step)
        if BASELINE_KEY in data and TARGET_KEY in data:
            base_med   = np.median(data[BASELINE_KEY])
            target_med = np.median(data[TARGET_KEY])
            if base_med > 0 and target_med > 0:
                speedup  = base_med / target_med
                gap_ms   = base_med - target_med
                arr_min  = np.array(data[TARGET_KEY]).min()
                sign     = "−" if gap_ms > 0 else "+"
                ax.text(pos_target + 0.04, arr_min - 0.018 * y_range,
                        f"{speedup:.2f}×",
                        ha="left", va="top",
                        fontsize=10, fontweight="bold", fontstyle="italic",
                        color=VCOL[TARGET_KEY])

    # ── Baseline median reference line per config group ────────────────────────
    for step, cfg_label, pos_base, pos_target in CONFIGS:
        data = load_folder(folder, step)
        if BASELINE_KEY in data:
            base_med = np.median(data[BASELINE_KEY])
            ax.hlines(base_med, pos_base - 0.35, pos_target + 0.35,
                      colors=VCOL[BASELINE_KEY], linestyles="--",
                      linewidth=1.8, alpha=0.5)

    # ── X-axis: group labels centred under each pair ───────────────────────────
    ax.set_xticks([])   # no individual ticks
    ax.set_xticks([1.5, 4.5])
    ax.set_xticklabels(["", ""])  # no tick labels, we'll add custom text
    ax.set_xlim(0.5, 5.5)

    for step, cfg_label, pos_base, pos_target in CONFIGS:
        centre = (pos_base + pos_target) / 2
        ax.text(centre, ylo - 0.06 * y_range, cfg_label,
                ha="center", va="top",
                fontsize=9, clip_on=False)

    # Vertical separator between groups
    ax.axvline(x=GAP_CENTRE, color="grey", linestyle=":", linewidth=1.0, alpha=0.5)

    ax.set_ylabel("Time (ms)")
    ax.set_title(platform_title, fontsize=12)
    ax.grid(True, axis="y", linestyle="--", alpha=0.35)


# ── CLI ────────────────────────────────────────────────────────────────────────
def none_or_str(v):
    return None if v.lower() == "none" else v

parser = argparse.ArgumentParser(
    description="2×1 violin: stage-8 GPU layout comparison.",
    formatter_class=argparse.RawTextHelpFormatter,
)
parser.add_argument("--gpu",        default="beverin_full_permutations_8", type=none_or_str)
parser.add_argument("--gpu2",       default="daint_full_permutations_8",   type=none_or_str)
parser.add_argument("--gpu-title",  default="AMD MI300A",                  type=none_or_str)
parser.add_argument("--gpu2-title", default="NVIDIA GH200",                type=none_or_str)
parser.add_argument("--out",        default="plots/violin_stage8_gpu.png")
args = parser.parse_args()

for attr, path in [("gpu", args.gpu), ("gpu2", args.gpu2)]:
    if not os.path.isdir(path):
        parser.error(f"Folder '{path}' not found (--{attr.replace('_','-')}).")

# ── rcParams ───────────────────────────────────────────────────────────────────
plt.rcParams.update({
    "font.size":       12,
    "axes.titlesize":  12,
    "axes.labelsize":  11,
    "xtick.labelsize": 10,
    "ytick.labelsize": 10,
    "legend.fontsize": 10,
})

fig, axes = plt.subplots(
    2, 1,
    figsize=(8*0.8, 6*0.8),
    gridspec_kw={"hspace": 0.27},
)

fig.suptitle("Memory Layout Impact on GPU Impl. Velocity Tendencies",
             fontsize=13, y=0.97)

plot_panel(axes[0], args.gpu,  args.gpu_title)
plot_panel(axes[1], args.gpu2, args.gpu2_title)

# ── Unified tick count across both panels ──────────────────────────────────────
from matplotlib.ticker import MaxNLocator
N_TICKS = 6   # at least 6 ticks on both panels
for ax in axes:
    locator = MaxNLocator(nbins=N_TICKS, min_n_ticks=N_TICKS, steps=[1, 2, 2.5, 5, 10])
    locator.set_axis(ax.yaxis)
    ticks = locator.tick_values(ax._data_ylo, ax._data_yhi)
    # Enforce minimum: if fewer than 6 returned, force nbins higher
    if len(ticks) < N_TICKS:
        locator = MaxNLocator(nbins=N_TICKS + 2, min_n_ticks=N_TICKS,
                              steps=[1, 2, 2.5, 5, 10])
        locator.set_axis(ax.yaxis)
        ticks = locator.tick_values(ax._data_ylo, ax._data_yhi)
    ax.set_yticks(ticks)
    ax.set_ylim(ax._data_ylo, ax._data_yhi)

# ── Legend ─────────────────────────────────────────────────────────────────────
handles = [
    Patch(facecolor=VCOL[BASELINE_KEY], edgecolor="black", label=VLAB[BASELINE_KEY]),
    Patch(facecolor=VCOL[TARGET_KEY],   edgecolor="black", label=VLAB[TARGET_KEY]),
]
fig.legend(handles=handles, loc="lower center",
           bbox_to_anchor=(0.5, -0.01), ncol=2, framealpha=0.9)

fig.tight_layout(rect=[0, 0.05, 1, 0.5])
os.makedirs(os.path.dirname(args.out) if os.path.dirname(args.out) else ".", exist_ok=True)
fig.savefig(args.out, dpi=200, bbox_inches="tight")
fig.savefig(args.out.replace(".png", ".pdf"), dpi=200, bbox_inches="tight")
plt.close(fig)
print(f"Saved {args.out}")