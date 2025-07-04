from pathlib import Path
from collections import defaultdict
import re
from statistics import mean, median, variance

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
        durations = [int(m.group(1)) for m in re.finditer(r'Timer Host Based C\+\+ Timer took (\d+) us', block)]
        if len(durations) == 0:
            durations = [float(m.group(1)) for m in re.finditer(r'CUDA Events Based Total time: ([\d.]+) us', block)]
        assert len(durations) > 0, f"No durations found for step {step_info[0]}"

        if durations:
            stats = {
                "step": step_info[0],
                "extra_diffu": step_info[1],
                "istep": step_info[2],
                "lvn_only": step_info[3],
                "ldeepatmo": step_info[4],
                "mean": mean(durations),
                "median": median(durations),
                "variance": variance(durations) if len(durations) > 1 else 0.0,
                "count": len(durations),
            }
            results.append(stats)

    return results

# Example usage (to be replaced with actual file path)
# parse_timer_log("/path/to/your/logfile.txt")

import sys

# Accept file path from command-line arguments
def main():
    if len(sys.argv) != 2:
        print("Usage: python script.py <log_file_path>")
        return

    file_path = sys.argv[1]
    results = parse_timer_log_by_step(file_path)
    medians = [stats['median'] for stats in results if not (stats['istep'] == 1 and stats['lvn_only'] == 0)]
    avg_median = sum(medians) / len(medians)
    for stats in results:
        print(f"Mean: {stats['mean']:.2f} µs, Median: {stats['median']:.2f} µs, (timestep: {stats['step']}, istep: {stats['istep']}, lvn Only: {stats['lvn_only']})")
    print(f"Average of medians: {avg_median:.2f} µs (timestep 1 skipped)")


# Uncomment to test directly within script-enabled environments
if __name__ == "__main__":
    main()

