#!/usr/bin/env python3
"""
Plot violin comparison of ICON velocity kernel timings.

Usage:
    python plot_timers.py <permuted_log> <unpermuted_log> [-o output.png]

Parses timer lines like:
    Timer velocity_no_nproma_if_prop_lvn_only_0_istep_2 took 924 us

Groups every 10 consecutive timer lines per config into (first, remaining 9).
Produces 2 subplots: first-run warmup vs steady-state (remaining 9).
"""

import argparse
import re
from collections import defaultdict
from pathlib import Path

import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import numpy as np

TIMER_RE = re.compile(
    r"Timer\s+(velocity_no_nproma_if_prop_lvn_only_(\d+)_istep_(\d+))\s+took\s+(\d+)\s+us"
)

CONFIGS = [
    ("lvn_only=0, istep=1", "0", "1"),
    ("lvn_only=0, istep=2", "0", "2"),
    ("lvn_only=1, istep=1", "1", "1"),
    ("lvn_only=1, istep=2", "1", "2"),
]


def parse_log(path: str) -> dict[str, list[list[int]]]:
    """
    Returns {config_key: [[10 timings], [10 timings], ...]}
    where config_key is e.g. "0_2" for lvn_only=0, istep=2.
    Each inner list is one step's 10 repetitions.
    """
    raw: dict[str, list[int]] = defaultdict(list)
    with open(path) as f:
        for line in f:
            m = TIMER_RE.search(line)
            if m:
                lvn, istep, us = m.group(2), m.group(3), int(m.group(4))
                raw[f"{lvn}_{istep}"].append(us)

    grouped: dict[str, list[list[int]]] = {}
    for key, vals in raw.items():
        # chunk into groups of 10
        chunks = [vals[i : i + 10] for i in range(0, len(vals), 10)]
        # drop incomplete trailing chunk
        grouped[key] = [c for c in chunks if len(c) == 10]
    return grouped


def split_first_rest(
    grouped: dict[str, list[list[int]]]
) -> tuple[dict[str, list[int]], dict[str, list[int]]]:
    """Split each config into first-run values and remaining-9 values."""
    firsts: dict[str, list[int]] = defaultdict(list)
    rests: dict[str, list[int]] = defaultdict(list)
    for key, chunks in grouped.items():
        for chunk in chunks:
            firsts[key].append(chunk[0])
            rests[key].extend(chunk[1:])
    return firsts, rests


def make_violin(ax, data_pairs, labels, colors, title):
    """
    data_pairs: list of (values_permuted, values_unpermuted) per config present.
    labels: config labels corresponding to data_pairs.
    """
    positions = []
    all_data = []
    tick_positions = []
    tick_labels = []
    color_list = []

    pos = 1
    for i, (perm, unperm) in enumerate(data_pairs):
        # permuted
        all_data.append(perm)
        positions.append(pos)
        color_list.append(colors[0])
        # unpermuted
        all_data.append(unperm)
        positions.append(pos + 1)
        color_list.append(colors[1])

        tick_positions.append(pos + 0.5)
        tick_labels.append(labels[i])
        pos += 3  # gap between configs

    if not all_data:
        ax.set_title(title)
        ax.text(0.5, 0.5, "No data", ha="center", va="center", transform=ax.transAxes)
        return

    parts = ax.violinplot(all_data, positions=positions, showmedians=True, showextrema=True)

    for idx, body in enumerate(parts["bodies"]):
        body.set_facecolor(color_list[idx])
        body.set_alpha(0.7)

    for key in ("cbars", "cmins", "cmaxes", "cmedians"):
        if key in parts:
            parts[key].set_color("black")

    ax.set_xticks(tick_positions)
    ax.set_xticklabels(tick_labels, fontsize=9)
    ax.set_ylabel("Time (µs)")
    ax.set_title(title)
    ax.yaxis.set_minor_locator(ticker.AutoMinorLocator())
    ax.grid(axis="y", alpha=0.3)


def main():
    parser = argparse.ArgumentParser(description="Compare permuted vs unpermuted ICON velocity timings")
    parser.add_argument("permuted", help="Path to permuted log file")
    parser.add_argument("unpermuted", help="Path to unpermuted log file")
    parser.add_argument("-o", "--output", default="velocity_violin.png", help="Output plot path")
    args = parser.parse_args()

    g_perm = parse_log(args.permuted)
    g_unperm = parse_log(args.unpermuted)

    f_perm, r_perm = split_first_rest(g_perm)
    f_unperm, r_unperm = split_first_rest(g_unperm)

    # Determine which configs are present in at least one file
    all_keys = sorted(set(list(g_perm.keys()) + list(g_unperm.keys())))

    config_labels = []
    first_pairs = []
    rest_pairs = []
    for key in all_keys:
        lvn, istep = key.split("_")
        label = f"lvn_only={lvn}\nistep={istep}"
        config_labels.append(label)
        first_pairs.append((f_perm.get(key, []), f_unperm.get(key, [])))
        rest_pairs.append((r_perm.get(key, []), r_unperm.get(key, [])))

    colors = ["#4C72B0", "#DD8452"]  # blue=permuted, orange=unpermuted

    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(10, 4), sharey=False)

    make_violin(ax1, first_pairs, config_labels, colors, "First run (After copy kernel)")
    make_violin(ax2, rest_pairs, config_labels, colors, "Remaining 9 runs")

    # Legend
    from matplotlib.patches import Patch

    legend_elements = [
        Patch(facecolor=colors[0], alpha=0.7, label=Path(args.permuted).stem),
        Patch(facecolor=colors[1], alpha=0.7, label=Path(args.unpermuted).stem),
    ]
    fig.legend(handles=legend_elements, loc="lower center", ncol=2, fontsize=12, frameon=True,
               bbox_to_anchor=(0.5, -0.02))
 
    perm_name = Path(args.permuted).stem
    unperm_name = Path(args.unpermuted).stem
    fig.suptitle(f"Velocity kernel: {perm_name} vs {unperm_name}", fontsize=13, y=1.02)
    fig.tight_layout(rect=[0, 0.06, 1, 1])
    fig.savefig(args.output, dpi=180, bbox_inches="tight")
    print(f"Saved to {args.output}")

    # Print summary statistics
    print("\n--- Summary (median ± IQR in µs) ---")
    for key in all_keys:
        lvn, istep = key.split("_")
        print(f"\n  lvn_only={lvn}, istep={istep}:")
        for label, f_d, r_d in [
            (Path(args.permuted).stem, f_perm, r_perm),
            (Path(args.unpermuted).stem, f_unperm, r_unperm),
        ]:
            fv = np.array(f_d.get(key, []))
            rv = np.array(r_d.get(key, []))
            if len(fv):
                print(f"    {label:30s}  first: {np.median(fv):.0f} ({np.percentile(fv,25):.0f}-{np.percentile(fv,75):.0f})  "
                      f"rest: {np.median(rv):.0f} ({np.percentile(rv,25):.0f}-{np.percentile(rv,75):.0f})")
            else:
                print(f"    {label:30s}  (no data)")


if __name__ == "__main__":
    main()