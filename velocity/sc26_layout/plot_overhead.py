#!/usr/bin/env python3
import sys
import numpy as np
import matplotlib.pyplot as plt

csv_path = sys.argv[1] if len(sys.argv) > 1 else "launch_times.csv"
data = np.genfromtxt(csv_path, delimiter=",", skip_header=1)
times = data[:, 1]  # time_us column

p50, p95, p99 = np.percentile(times, [50, 95, 99])

fig, axes = plt.subplots(1, 2, figsize=(14, 5))

# histogram
ax = axes[0]
ax.hist(times, bins=100, edgecolor="black", linewidth=0.3, alpha=0.85)
for val, label, color in [(p50, "p50", "green"), (p95, "p95", "orange"), (p99, "p99", "red")]:
    ax.axvline(val, color=color, linestyle="--", linewidth=1.5, label=f"{label} = {val:.2f} µs")
ax.set_xlabel("Launch time (µs)")
ax.set_ylabel("Count")
ax.set_title("Kernel launch overhead distribution")
ax.legend()

# time series
ax = axes[1]
ax.plot(times, linewidth=0.3, alpha=0.7)
ax.axhline(p50, color="green", linestyle="--", linewidth=1, label=f"p50 = {p50:.2f} µs")
ax.axhline(p95, color="orange", linestyle="--", linewidth=1, label=f"p95 = {p95:.2f} µs")
ax.set_xlabel("Iteration")
ax.set_ylabel("Launch time (µs)")
ax.set_title("Per-launch time series")
ax.legend()

plt.tight_layout()
plt.savefig("launch_overhead.png", dpi=150)
plt.savefig("launch_overhead.pdf")
print(f"n={len(times)}  mean={times.mean():.2f}µs  median={np.median(times):.2f}µs  std={times.std():.2f}µs  "
      f"min={times.min():.2f}µs  p50={p50:.2f}µs  p95={p95:.2f}µs  p99={p99:.2f}µs  max={times.max():.2f}µs")

print(f"n={len(times)}  mean={times.mean()/1000.0:.5f}ms  median={np.median(times)/1000.0:.5f}ms  std={times.std()/1000.0:.5f}ms  "
      f"min={times.min()/1000.0:.5f}ms  p50={p50/1000.0:.5f}ms  p95={p95/1000.0:.5f}ms  p99={p99/1000.0:.5f}ms  max={times.max()/1000.0:.5f}ms")

print("Saved launch_overhead.png and launch_overhead.pdf")