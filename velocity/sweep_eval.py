"""
Takes in a log file.
Creates copy of log file with _eval suffix.
Removes any line that does not start with "=== Running for " or "Timer ".

Now the log file should look like this:
=== Running for x_c=2, y_c=4, x_bs=256, y_bs=1, y_unroll=2 ===
Timer velocity_no_nproma_if_prop_lvn_only_0_istep_1 took 3514 us
Timer velocity_no_nproma_if_prop_lvn_only_0_istep_2 took 1316 us
Timer velocity_no_nproma_if_prop_lvn_only_1_istep_1 took 1365 us
...
=== Running for x_c=1, y_c=1, x_bs=128, y_bs=2, y_unroll=1 ===
Timer velocity_no_nproma_if_prop_lvn_only_0_istep_1 took 4293 us
Timer velocity_no_nproma_if_prop_lvn_only_0_istep_2 took 1732 us
Timer velocity_no_nproma_if_prop_lvn_only_1_istep_1 took 1892 us
...

Should take the median of the timings for each configuration and print it out.
"""

import sys
import os
import statistics
import re

def process_log_file(input_file):
    # Step 1: Read lines and create filtered copy
    output_file = os.path.splitext(input_file)[0] + "_eval.log"
    with open(input_file, 'r') as f_in, open(output_file, 'w') as f_out:
        for line in f_in:
            if line.startswith("=== Running for ") or line.startswith("Timer ") or line.startswith("=== Done for "):
                f_out.write(line)

    # Step 2: Parse filtered file to collect timings
    results = {}
    current_config = None

    with open(output_file, 'r') as f:
        for line in f:
            if line.startswith("=== Running for "):
                current_config = line.strip()
                results[current_config] = []
            elif line.startswith("Timer ") and current_config:
                match = re.search(r'took (\d+) us', line)
                if match:
                    time_us = int(match.group(1))
                    results[current_config].append(time_us)

    # Step 3: Print median timings for each configuration
    with open(output_file, 'a') as f:
      f.write("\n=== Median timings === \n")
      for config, times in results.items():
          if times:
              median_time = statistics.median(times)
              line = f"{config}: median = {median_time:.2f} us\n"
              print(line.strip())
              f.write(line)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python eval_log.py <log_file>")
    else:
        process_log_file(sys.argv[1])
