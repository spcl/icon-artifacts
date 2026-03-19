#!/usr/bin/env python3
"""
Plot GPU permuted vs unpermuted kernel timings.
Splits each group of 10 repetitions into first run (cold) and remaining 9 (warm).

Usage:
python sc26_layout/plot_stage6_v2.py \
    --gpu-unpermuted gpu_unpermuted_stage6.txt \
    --gpu-permuted gpu_permuted_stage6.txt  \
    --reps-per-group 20 \
    --warmup-groups 0 \
    --title "R02B05" \
    -o gpu_first_rest.pdf

python sc26_layout/plot_stage6_v2.py \
    --gpu-unpermuted cpu_unpermuted_stage4.txt \
    --gpu-permuted cpu_permuted_stage4.txt  \
    --reps-per-group 10 \
    --warmup-groups 0 \
    --title "R02B05" \
    -o cpu_first_rest.pdf
"""

import argparse
import re
from pathlib import Path

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np
from matplotlib.patches import Patch


def parse_elapsed_times(path: str) -> list[float]:
    """Parse elapsed times in ms from a log file.
    Adjust the regex below to match your log format.
    """
    times = []
    # Try multiple common formats
    patterns = [
        #re.compile(r"took\s+([\d.]+)\s*us"),           # "took 924 us" → convert to ms
        #re.compile(r"took\s+([\d.]+)\s*ms"),           # "took 0.924 ms"
        re.compile(r"Elapsed\s+time\s*[:=]\s*([\d.]+)\s*ms"),  # "elapsed time: 0.924"
        #re.compile(r"time[_\s]*(?:ms)?\s*[:=]\s*([\d.]+)"),     # "time_ms: 0.924"
        #re.compile(r"([\d.]+)\s*$"),                   # bare number per line
    ]
    
    with open(path) as f:
        for line in f:
            for i, pat in enumerate(patterns):
                m = pat.search(line)
                if m:
                    val = float(m.group(1))
                    times.append(val)
                    break

    print(times[0:21])
    #raise Exception(times[0:21])
    return times


def split_first_rest(times: list[float], reps: int) -> tuple[list[float], list[float]]:
    """Split a flat list of timings into (first of each group, remaining reps-1)."""
    firsts = []
    rests = []
    for i in range(0, len(times), reps):
        chunk = times[i : i + reps]
        if len(chunk) == reps:
            firsts.append(chunk[0])
            rests.extend(chunk[1:])
    return firsts, rests


def violin_panel(ax, data_list, labels, colors, title):
    """Draw side-by-side violins on a single axes."""
    positions = list(range(1, len(data_list) + 1))

    # Filter out empty datasets
    valid = [(d, p, c) for d, p, c in zip(data_list, positions, colors) if len(d) > 1]
    if not valid:
        ax.set_title(title)
        ax.text(0.5, 0.5, "No data", ha="center", va="center", transform=ax.transAxes)
        return

    vdata = [v[0] for v in valid]
    vpos = [v[1] for v in valid]
    vcol = [v[2] for v in valid]

    parts = ax.violinplot(vdata, positions=vpos, showmedians=True, showextrema=True,
                          widths=0.7)

    for idx, body in enumerate(parts["bodies"]):
        body.set_facecolor(vcol[idx])
        body.set_alpha(0.7)

    for key in ("cbars", "cmins", "cmaxes", "cmedians"):
        if key in parts:
            parts[key].set_color("black")

    ax.set_xticks(positions)
    ax.set_xticklabels(labels, fontsize=10)
    ax.set_ylabel("Time (ms)")
    ax.set_title(title, fontsize=12)
    ax.yaxis.set_minor_locator(ticker.AutoMinorLocator())
    ax.grid(axis="y", alpha=0.3)


def print_summary(label, data):
    arr = np.array(data)
    if len(arr) == 0:
        print(f"    {label:30s}  (no data)")
    else:
        print(f"    {label:30s}  n={len(arr):3d}  "
              f"median={np.median(arr):.3f}  "
              f"IQR=[{np.percentile(arr, 25):.3f}, {np.percentile(arr, 75):.3f}]  "
              f"min={np.min(arr):.3f}  max={np.max(arr):.3f} ms")


def main():
    parser = argparse.ArgumentParser(
        description="Plot GPU permuted vs unpermuted: first run vs remaining"
    )
    parser.add_argument("--gpu-unpermuted", required=True, help="Path to unpermuted GPU log")
    parser.add_argument("--gpu-permuted", required=True, help="Path to permuted GPU log")
    parser.add_argument("--reps-per-group", type=int, default=10,
                        help="Number of repetitions per measurement group (default: 20)")
    parser.add_argument("--warmup-groups", type=int, default=0,
                        help="Number of initial groups to discard entirely (default: 0)")
    parser.add_argument("--title", type=str, default="R02B05")
    parser.add_argument("-o", "--output", default="gpu_first_rest.pdf")
    args = parser.parse_args()

    R = args.reps_per_group
    W = args.warmup_groups

    # Parse all times
    gpu_unperm_all = parse_elapsed_times(args.gpu_unpermuted)
    gpu_perm_all = parse_elapsed_times(args.gpu_permuted)

    # Drop warmup groups
    gpu_unperm_all = gpu_unperm_all[W * R:]
    gpu_perm_all = gpu_perm_all[W * R:]

    print(f"Total samples: unperm={len(gpu_unperm_all)}, perm={len(gpu_perm_all)}")
    print(f"Reps per group: {R}, warmup groups dropped: {W}")

    # Split into first / rest
    unperm_first, unperm_rest = split_first_rest(gpu_unperm_all, R)
    print(unperm_first[0:5])
    print(unperm_rest[0:5])
    perm_first, perm_rest = split_first_rest(gpu_perm_all, R)
    print(perm_first[0:5])
    print(perm_rest[0:5])
    print(f"Groups: unperm={len(unperm_first)}, perm={len(perm_first)}")

    # --- Two panels: first run vs remaining ---
    colors = ["#4C72B0", "#DD8452"]  # blue=unpermuted, orange=permuted

    fig, (ax_first, ax_rest) = plt.subplots(1, 2, figsize=(10, 5))

    violin_panel(
        ax_first,
        [unperm_first, perm_first],
        ["Unpermuted", "Permuted"],
        colors,
        f"First run per group ({args.title})",
    )

    violin_panel(
        ax_rest,
        [unperm_rest, perm_rest],
        ["Unpermuted", "Permuted"],
        colors,
        f"Remaining {R - 1} runs ({args.title})",
    )

    legend_elements = [
        Patch(facecolor=colors[0], alpha=0.7, label=Path(args.gpu_unpermuted).stem),
        Patch(facecolor=colors[1], alpha=0.7, label=Path(args.gpu_permuted).stem),
    ]
    fig.legend(handles=legend_elements, loc="lower center", ncol=2, fontsize=11,
               frameon=True, bbox_to_anchor=(0.5, -0.02))

    fig.suptitle(f"GPU velocity kernel: {args.title}", fontsize=13, y=1.02)
    fig.tight_layout(rect=[0, 0.06, 1, 1])
    fig.savefig(args.output, dpi=150, bbox_inches="tight")
    print(f"\nSaved to {args.output}")

    # --- Summary ---
    print(f"\n{'--- Summary (ms) ---':=<60}")
    print("  First run (cold):")
    print_summary("Unpermuted", unperm_first)
    print_summary("Permuted", perm_first)
    print(f"\n  Remaining {R - 1} runs (warm):")
    print_summary("Unpermuted", unperm_rest)
    print_summary("Permuted", perm_rest)

    if len(unperm_rest) and len(perm_rest):
        speedup = np.median(unperm_rest) / np.median(perm_rest)
        print(f"\n  Speedup (warm median): {speedup:.2f}x "
              f"({'permuted faster' if speedup > 1 else 'unpermuted faster'})")


if __name__ == "__main__":
    main()