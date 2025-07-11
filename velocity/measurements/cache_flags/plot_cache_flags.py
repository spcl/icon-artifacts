import matplotlib.pyplot as plt
import numpy as np

# Data from your table
cache_types = ['l1l2', 'l2only']
medians = [302.000, 306.000]
means = [304.024, 308.695]

# Confidence intervals
median_ci_low = [302.000, 306.000]
median_ci_high = [303.000, 307.000]
mean_ci_low = [303.544, 307.810]
mean_ci_high = [304.644, 309.956]

# Calculate error bars
median_errors = [
    [medians[i] - median_ci_low[i] for i in range(len(medians))],
    [median_ci_high[i] - medians[i] for i in range(len(medians))]
]

mean_errors = [
    [means[i] - mean_ci_low[i] for i in range(len(means))],
    [mean_ci_high[i] - means[i] for i in range(len(means))]
]

# Create the plot
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

# Plot 1: Median comparison
x_pos = np.arange(len(cache_types))
bars1 = ax1.bar(x_pos, medians, yerr=median_errors, capsize=5,
                color=['skyblue', 'lightcoral'], alpha=0.7,
                error_kw={'elinewidth': 2, 'capthick': 2})
ax1.set_xlabel('Cache Type')
ax1.set_ylabel('Runtime (μs)')
ax1.set_title('Median Runtime Comparison\n(99% Confidence Intervals)')
ax1.set_xticks(x_pos)
ax1.set_xticklabels(cache_types)
ax1.grid(True, alpha=0.3)

# Add value labels on bars
for i, (bar, median) in enumerate(zip(bars1, medians)):
    height = bar.get_height()
    ax1.text(bar.get_x() + bar.get_width()/2., height + 0.5,
             f'{median:.1f}μs', ha='center', va='bottom', fontweight='bold')

# Plot 2: Mean comparison
bars2 = ax2.bar(x_pos, means, yerr=mean_errors, capsize=5,
                color=['lightgreen', 'orange'], alpha=0.7,
                error_kw={'elinewidth': 2, 'capthick': 2})
ax2.set_xlabel('Cache Type')
ax2.set_ylabel('Runtime (μs)')
ax2.set_title('Mean Runtime Comparison\n(99% Confidence Intervals)')
ax2.set_xticks(x_pos)
ax2.set_xticklabels(cache_types)
ax2.grid(True, alpha=0.3)

# Add value labels on bars
for i, (bar, mean) in enumerate(zip(bars2, means)):
    height = bar.get_height()
    ax2.text(bar.get_x() + bar.get_width()/2., height + 0.5,
             f'{mean:.1f}μs', ha='center', va='bottom', fontweight='bold')

plt.tight_layout()
plt.show()

# Alternative: Combined plot
fig2, ax = plt.subplots(figsize=(10, 6))

x = np.arange(len(cache_types))
width = 0.35

# Plot both median and mean side by side
bars1 = ax.bar(x - width/2, medians, width, yerr=median_errors,
               label='Median', capsize=5, color='skyblue', alpha=0.7)
bars2 = ax.bar(x + width/2, means, width, yerr=mean_errors,
               label='Mean', capsize=5, color='lightcoral', alpha=0.7)

ax.set_xlabel('Cache Type')
ax.set_ylabel('Runtime (μs)')
ax.set_title('CUDA Cache Performance Comparison\n(99% Confidence Intervals)')
ax.set_xticks(x)
ax.set_xticklabels(cache_types)
ax.legend()
ax.grid(True, alpha=0.3)

# Add value labels
for bars in [bars1, bars2]:
    for bar in bars:
        height = bar.get_height()
        ax.text(bar.get_x() + bar.get_width()/2., height + 0.3,
                f'{height:.1f}', ha='center', va='bottom', fontsize=9)

plt.tight_layout()
plt.ylim(270, 325)  # Set y-limits for better visibility
plt.savefig('cache_performance_comparison.png', dpi=300)
plt.ylim(0, 325)  # Set y-limits for better visibility
plt.savefig('cache_performance_comparison_2.png', dpi=300)
# Print summary
print("Performance Summary:")
print(f"l1l2 cache is {((medians[1] - medians[0]) / medians[0] * 100):.1f}% faster (median)")
print(f"l1l2 cache is {((means[1] - means[0]) / means[0] * 100):.1f}% faster (mean)")
print(f"Absolute difference: {medians[1] - medians[0]:.1f}μs (median), {means[1] - means[0]:.1f}μs (mean)")