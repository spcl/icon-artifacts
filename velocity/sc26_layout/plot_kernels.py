#!/usr/bin/env python3
"""
Parse kernel timing logs and plot violin plots (separate CPU / GPU panels).

Usage:
    python plot_kernels.py \
        --cpu-unpermuted r02b05_ln/cpu_unpermuted.txt \
        --cpu-permuted r02b05_ln/cpu_permuted.txt \
        --gpu-unpermuted r02b05_ln/gpu_unpermuted_profile_stage6.txt \
        --gpu-permuted r02b05_ln/gpu_permuted_profile_stage6.txt \
        --launch-overhead r02b05_ln/launch_overhead.txt \
        --title "R02B05" \
        --warmup 2

    python plot_kernels.py \
        --cpu-unpermuted r02b06_ln/cpu_unpermuted.txt \
        --cpu-permuted r02b06_ln/cpu_permuted.txt \
        --gpu-unpermuted r02b06_ln/gpu_unpermuted_profile_stage6.txt \
        --gpu-permuted r02b06_ln/gpu_permuted_profile_stage6.txt \
        --launch-overhead r02b06_ln/launch_overhead.txt \
        --title "R02B06" \
        --warmup 10

    python sc26_layout/plot_kernels.py \
        --cpu-unpermuted r02b05_ln/cpu_unpermuted.txt \
        --cpu-permuted r02b05_ln/cpu_permuted.txt \
        --gpu-unpermuted gpu_unpermuted_stage6_v2.txt \
        --gpu-permuted gpu_permuted_stage6_v2.txt \
        --title "R02B06" \
        --launch-overhead r02b06_ln/launch_overhead.txt \
        --warmup 2

python sc26_layout/plot_kernels.py \
    --cpu-unpermuted cpu_unpermuted_stage4.txt \
    --cpu-permuted cpu_permuted_stage4.txt \
    --gpu-unpermuted gpu_unpermuted_stage6.txt \
    --gpu-permuted gpu_permuted_stage6.txt \
    --title "R02B06" \
    --launch-overhead r02b06_ln/launch_overhead.txt \
    --warmup 2
"""

import re
import argparse
import numpy as np
import matplotlib.pyplot as plt


def parse_elapsed_times(filepath):
    """Extract all 'Elapsed time: X ms' values from a timer log."""
    times = []
    with open(filepath) as f:
        for line in f:
            m = re.search(r"Elapsed time:\s+([\d.eE+-]+)\s*ms", line)
            if m:
                times.append(float(m.group(1)))
    return np.array(times)


def parse_launch_overhead(filepath):
    """Extract per-launch overhead in ms from the launch overhead file."""
    with open(filepath) as f:
        for line in f:
            m = re.search(r"Per launch:.*\(([\d.eE+-]+)\s*ms\)", line)
            if m:
                return float(m.group(1))
            m = re.search(r"Per launch:\s+([\d.eE+-]+)\s*us", line)
            if m:
                return float(m.group(1)) / 1000.0
    raise ValueError(f"Could not parse launch overhead from {filepath}")


def violin_panel(ax, data_list, labels, colors, title):
    """Draw a violin plot with jittered dots on a given axes."""
    positions = list(range(1, len(data_list) + 1))

    parts = ax.violinplot(data_list, positions=positions,
                          showmedians=True, showextrema=False)

    for i, pc in enumerate(parts["bodies"]):
        pc.set_facecolor(colors[i])
        pc.set_edgecolor("black")
        pc.set_alpha(0.7)

    parts["cmedians"].set_color("black")

    rng = np.random.default_rng(42)
    for i, (pos, d) in enumerate(zip(positions, data_list)):
        jitter = rng.uniform(-0.15, 0.15, size=len(d))
        ax.scatter(pos + jitter, d, s=8, alpha=0.3, color=colors[i], zorder=3)

    ax.set_xticks(positions)
    ax.set_xticklabels(labels)
    ax.set_ylim(bottom=0)
    ax.set_ylabel("Elapsed time [ms]")
    ax.set_title(title)
    ax.grid(axis="y", alpha=0.3)

    for lbl, d in zip(labels, data_list):
        print(f"  {title} / {lbl}: median={np.median(d):.4f} ms, "
              f"mean={np.mean(d):.4f} ms, n={len(d)}")


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--cpu-unpermuted", required=True)
    parser.add_argument("--cpu-permuted", required=True)
    parser.add_argument("--gpu-unpermuted", required=True)
    parser.add_argument("--gpu-permuted", required=True)
    parser.add_argument("--launch-overhead", required=True)
    parser.add_argument("--warmup", type=int, default=5)
    parser.add_argument("--title", type=str, default="R02B05")
    parser.add_argument("-o", "--output", default="kernel_violin.pdf")
    args = parser.parse_args()

    W = args.warmup

    cpu_unperm = parse_elapsed_times(args.cpu_unpermuted)[W:]
    cpu_perm   = parse_elapsed_times(args.cpu_permuted)[W:]
    gpu_unperm = parse_elapsed_times(args.gpu_unpermuted)[W:]
    gpu_perm   = parse_elapsed_times(args.gpu_permuted)[W:]
    #overhead   = parse_launch_overhead(args.launch_overhead)

    print(f"Samples after {W} warmup:  "
          #f"CPU unperm={len(cpu_unperm)}, CPU perm={len(cpu_perm)}, "
          f"GPU unperm={len(gpu_unperm)}, GPU perm={len(gpu_perm)}")
    #print(f"Launch overhead: {overhead:.6f} ms\n")

    # --- Two panels side by side ---
    fig, (ax_cpu, ax_gpu) = plt.subplots(1, 2, figsize=(10, 5))

    # CPU panel
    violin_panel(
        ax_cpu,
        [cpu_unperm, cpu_perm],
        ["Unpermuted", "Permuted"],
        ["#4C72B0", "#DD8452"],
        f"CPU kernel runtime ({args.title})",
    )

    # GPU panel: raw + overhead-subtracted
    violin_panel(
        ax_gpu,
        [gpu_unperm, gpu_perm],
        ["Unperm", "Perm"],
        ["#4C72B0", "#DD8452"],
        f"GPU kernel runtime ({args.title})",
    )

    fig.tight_layout()
    fig.savefig(args.output, dpi=150, bbox_inches="tight")
    print(f"\nSaved to {args.output}")
    plt.show()


if __name__ == "__main__":
    main()