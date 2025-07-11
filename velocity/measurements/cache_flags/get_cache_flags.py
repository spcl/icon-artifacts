from pathlib import Path
from collections import defaultdict
import re
from statistics import mean, median, variance
import subprocess
from scipy.stats import bootstrap
import numpy as np

# Function to parse the file and compute stats

def parse_timer_log_by_step(file_path):
    content = Path(file_path).read_text()

    # Match all step config lines and their positions
    config_matches = list(re.finditer(
        r"Step (\d+) variables, extra_diffu: (\d+), istep: (\d+), lvn_only: (\d+), ldeepatmo: (\d+)", content))

    results = []

    for i, match in enumerate(config_matches):
        step_info = tuple(int(g) for g in match.groups())
        start = match.end()
        end = config_matches[i + 1].start() if i + 1 < len(config_matches) else len(content)

        block = content[start:end]
        durations = [float(m.group(1)) for m in re.finditer(r'Timer Host Based C\+\+ Timer took (\d+) us', block)]
        if len(durations) == 0:
            durations = [float(m.group(1)) for m in re.finditer(r'CUDA Events Based Total time: ([\d.]+) us', block)]
        assert len(durations) > 0, f"No durations found for step {step_info[0]}"

        if durations:
            print(f"Step {step_info[0]}: {len(durations)} durations found")
            if not (step_info[2] == 1 and step_info[3] == 0):
                results += durations

    print(len(results), "total durations found across all steps")

    return results


def get_median_runtime(path: str):
    results = parse_timer_log_by_step(path)

    median = np.median(results)
    mean = np.mean(results)

    # Compute 95% confidence interval for the median using scipy
    median_ci = bootstrap(np.array(results).reshape(1, -1), np.median, confidence_level=0.99,
                          n_resamples=5000, method='percentile').confidence_interval

    # 95% CI for the mean
    stddev = np.std(results, ddof=1)
    mean_ci = bootstrap(np.array(results).reshape(1, -1), np.mean, confidence_level=0.99,
                          n_resamples=5000, method='percentile').confidence_interval


    # Debug print per step

    print(f"Median Runtime: {median:.2f} us (timestep 1 skipped)")
    print(f"Mean Runtime: {mean:.2f} us (timestep 1 skipped)")

    # Convert to milliseconds
    return median, mean, (median_ci.low, median_ci.high), (mean_ci.low, mean_ci.high)


CACHE_TYPES = ["l1l2", "l2only"] #, "default"

# Simulate or run external script here
def run_external_script():
    # Replace the below with the actual script path and args
    subprocess.run(["./run.sh"], check=True)

cache_to_flag_dict = {
    'l1l2': '"-Xptxas -dlcm=ca"',
    'l2only': '"-Xptxas -dlcm=cg"',
    #'default': '""'
}

def main():
    #run_external_script()

    results = []
    for cache_type in CACHE_TYPES:
        log_file = f"gpu_log_stage8_true_nproma20480_{cache_type}.log"
        median, mean, median_ci, mean_ci = get_median_runtime(log_file)
        if median is not None:
            print(f"{cache_type}: median runtime = {median:.3f} us"
                f" (99% CI: {median_ci[0]:.3f}–{median_ci[1]:.3f} us)")
        if mean is not None:
            print(f"{cache_type}: mean runtime = {mean:.3f} us"
                f" (99% CI: {mean_ci[0]:.3f}–{mean_ci[1]:.3f} us)")
        results.append((cache_type, median, mean, median_ci, mean_ci))

    # Sort by median runtime (low to high), filtering out None
    sorted_results = sorted([r for r in results if r[1] is not None], key=lambda x: x[1])
    print("\nCache types sorted by median runtime (low to high):")
    for cache_type, median, mean, median_ci, mean_ci in sorted_results:
        print(f"{cache_type}: {median:.3f} us (99% CI: {median_ci[0]:.3f}–{median_ci[1]:.3f} us)")

    print(f"To use {sorted_results[0][0]}, export: {cache_to_flag_dict[sorted_results[0][0]]}")
    print(f"export _CUDA_CACHE_FLAGS={cache_to_flag_dict[sorted_results[0][0]]}")

    sorted_results = sorted([r for r in results if r[2] is not None], key=lambda x: x[2])
    print("\nCache types sorted by mean runtime (low to high):")
    for cache_type, median, mean, median_ci, mean_ci in sorted_results:
        print(f"{cache_type}: {mean:.3f} us (99% CI: {mean_ci[0]:.3f}–{mean_ci[1]:.3f} us)")

    print(f"To use {sorted_results[0][0]}, export: {cache_to_flag_dict[sorted_results[0][0]]}")
    print(f"export _CUDA_CACHE_FLAGS={cache_to_flag_dict[sorted_results[0][0]]}")


if __name__ == "__main__":
    main()