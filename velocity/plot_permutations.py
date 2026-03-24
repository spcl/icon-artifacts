import re, glob, os, argparse
import numpy as np
import matplotlib.pyplot as plt

pattern = re.compile(r"\[Timer\] Elapsed time: ([\d.]+) ms")
baseline_key = "unpermuted"


def load_folder(folder, step=None):
    """step=None -> all, step=7 -> only _step7, step=9 -> only _step9
       Files without a _stepN suffix are always included."""
    raw: dict[str, list[float]] = {}
    for f in glob.glob(os.path.join(folder, "*.txt")):
        basename = os.path.basename(f).replace(".txt", "")
        has_step = re.search(r"_step\d+$", basename)
        if step is not None and has_step:
            if not basename.endswith(f"_step{step}"):
                continue
        name = re.sub(r"_step\d+$", "", basename)
        with open(f) as fh:
            times = [float(m.group(1)) for line in fh if (m := pattern.search(line))]
        if not times:
            continue
        raw.setdefault(name, []).extend(times)
    violin_data, star_points = {}, {}
    for name, times in raw.items():
        if name == baseline_key or name.endswith("shuffled"):
            violin_data[name] = times
        else:
            if len(times) >= 4:
                violin_data[name] = times
            else:
                star_points[name] = np.median(times)
    return violin_data, star_points

def plot_panel(ax, violin_data, star_points, title, label_order, show_xticklabels=True):
    baseline_median = (
        np.median(violin_data[baseline_key]) if baseline_key in violin_data else None
    )

    configs = [l for l in label_order if l in violin_data]
    star_keys = [l for l in label_order if l in star_points]

    if configs:
        vp = ax.violinplot(
            [violin_data[cfg] for cfg in configs],
            positions=[label_order.index(c) + 1 for c in configs],
            showmeans=True,
        )
        for body, cfg in zip(vp["bodies"], configs):
            color = "green" if cfg == baseline_key else "blue"
            body.set_facecolor(color)
            body.set_edgecolor(color)
            body.set_alpha(0.7)

    for cfg in star_keys:
        val = star_points[cfg]
        x = label_order.index(cfg) + 1
        ax.plot(x, val, marker="*", markersize=10, color="orange")

    text_positions = []
    for cfg in configs:
        if cfg == baseline_key:
            continue
        med = np.median(violin_data[cfg])
        speedup = baseline_median / med if baseline_median else 1
        x = label_order.index(cfg) + 1
        text_positions.append((x, med * 1.1, speedup))

    for cfg in star_keys:
        val = star_points[cfg]
        speedup = baseline_median / val if baseline_median else 1
        x = label_order.index(cfg) + 1
        text_positions.append((x, val * 1.1, speedup))

    if text_positions:
        target = text_positions[0]
        ax.text(target[0], target[1], f"{target[2]:.2f}x", ha="center", va="bottom", fontsize=8)

    ax.set_xticks(range(1, len(label_order) + 1))
    if show_xticklabels:
        ax.set_xticklabels(label_order, rotation=90, ha="center", fontsize=7)
    else:
        ax.set_xticklabels([])
    ax.set_xlim(0.5, len(label_order) + 0.5)
    ax.set_ylim(bottom=0)
    ax.set_ylabel("Time (ms)")
    ax.set_title(title)
    ax.grid(True, axis="both", linestyle="--", alpha=0.5)


def all_keys(vd, sp):
    return set(vd.keys()) | set(sp.keys())


# ---- Argument parsing ----
def none_or_str(value):
    return None if value.lower() == "none" else value


parser = argparse.ArgumentParser(
    description="Violin plot for permuted/shuffled timing results.",
    formatter_class=argparse.RawTextHelpFormatter,
)
parser.add_argument("--cpu",  default=None, metavar="DIR", type=none_or_str,
                    help="Folder with CPU results (vendor 1)")
parser.add_argument("--gpu",  default=None, metavar="DIR", type=none_or_str,
                    help="Folder with GPU results (vendor 1)")
parser.add_argument("--cpu2", default=None, metavar="DIR", type=none_or_str,
                    help="Folder with CPU results (vendor 2)")
parser.add_argument("--gpu2", default=None, metavar="DIR", type=none_or_str,
                    help="Folder with GPU results (vendor 2)")
parser.add_argument("--cpu-title",  default="AMD Zen 3 (96 Cores)", type=none_or_str, metavar="STR")
parser.add_argument("--gpu-title",  default="AMD MI300A",            type=none_or_str, metavar="STR")
parser.add_argument("--cpu2-title", default="Grace CPU",             type=none_or_str, metavar="STR")
parser.add_argument("--gpu2-title", default="GH200 HBM3",            type=none_or_str, metavar="STR")
args = parser.parse_args()

panels = []
for folder, title in [
    (args.cpu,  args.cpu_title),
    (args.gpu,  args.gpu_title),
    (args.cpu2, args.cpu2_title),
    (args.gpu2, args.gpu2_title),
]:
    if folder and os.path.isdir(folder):
        panels.append((folder, title))
    elif folder:
        print(f"Warning: folder '{folder}' not found, skipping.")

if not panels:
    parser.error("Provide at least one of --cpu, --gpu, --cpu2, --gpu2.")

has_two_vendors = bool(args.cpu2 or args.gpu2)

# ---- Loop over step variants ----
for step_label, step_filter in [("step7", 7), ("step9", 9), ("combined", None)]:

    panel_data = [(folder, title, *load_folder(folder, step=step_filter)) for folder, title in panels]

    # ---- Intersection of configs across all panels ----
    common_keys = None
    for _, _, vd, sp in panel_data:
        keys = all_keys(vd, sp)
        common_keys = keys if common_keys is None else common_keys & keys

    if not common_keys:
        print(f"Warning: no common configs for {step_label}, skipping.")
        continue

    # ---- Global label order from GPU1 panel (or first panel) ----
    gpu1_entry = next(((vd, sp) for _, t, vd, sp in panel_data if t == args.gpu_title), None)
    gpu1_vd, gpu1_sp = gpu1_entry if gpu1_entry else (panel_data[0][2], panel_data[0][3])

    other_violin = {k: v for k, v in gpu1_vd.items() if k != baseline_key and k in common_keys}
    sorted_other = sorted(other_violin, key=lambda k: np.median(other_violin[k]))
    common_stars = {k: v for k, v in gpu1_sp.items() if k in common_keys}
    sorted_stars = sorted(common_stars.items(), key=lambda x: x[1])

    global_order = (
        ([baseline_key] if baseline_key in common_keys else [])
        + sorted_other
        + [k for k, _ in sorted_stars]
    )

    # ---- Layout ----
    if has_two_vendors:
        fig, axes = plt.subplots(2, 2, figsize=(16, 10))
        col0 = [(args.cpu_title,  args.cpu),  (args.gpu_title,  args.gpu)]
        col1 = [(args.cpu2_title, args.cpu2), (args.gpu2_title, args.gpu2)]
        data_map = {folder: (vd, sp) for folder, _, vd, sp in panel_data}

        for col_idx, col_panels in enumerate([col0, col1]):
            for row_idx, (title, folder) in enumerate(col_panels):
                ax = axes[row_idx][col_idx]
                vd, sp = data_map.get(folder, ({}, {}))
                vd_f = {k: v for k, v in vd.items() if k in common_keys}
                sp_f = {k: v for k, v in sp.items() if k in common_keys}
                show_labels = (row_idx == 1)
                if not vd_f and not sp_f:
                    ax.set_title(f"{title}  [no data]")
                    continue
                plot_panel(ax, vd_f, sp_f, f"{title} ({step_label})", global_order,
                           show_xticklabels=show_labels)

        for col_idx in range(2):
            axes[0][col_idx].sharex(axes[1][col_idx])
            plt.setp(axes[0][col_idx].get_xticklabels(), visible=False)

    else:
        n = len(panel_data)
        fig, axes_flat = plt.subplots(n, 1, figsize=(10, 5 * n))
        if n == 1:
            axes_flat = [axes_flat]
        for i, (folder, title, vd, sp) in enumerate(panel_data):
            ax = axes_flat[i]
            vd_f = {k: v for k, v in vd.items() if k in common_keys}
            sp_f = {k: v for k, v in sp.items() if k in common_keys}
            show_labels = (i == n - 1)
            if not vd_f and not sp_f:
                ax.set_title(f"{title}  [no data]")
                continue
            plot_panel(ax, vd_f, sp_f, f"{title} ({step_label})", global_order,
                       show_xticklabels=show_labels)

    fig.tight_layout()
    out = f"violin_plot_{step_label}.png"
    fig.savefig(out, dpi=200)
    plt.close(fig)
    print(f"Saved {out}")