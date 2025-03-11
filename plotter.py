"""
This script plots CSV files in the following format:
name,time(us)
"""

import pandas as pd
import sys
import os
import matplotlib.pyplot as plt

def plot_csv(file_path):
  # Read the CSV file
  data = pd.read_csv(file_path)
  
  # Check if the required columns are present
  if 'name' not in data.columns or 'time(us)' not in data.columns:
    print("CSV file must contain 'name' and 'time(us)' columns.")
    return
  
  # Scale time to microseconds
  data['time(ms)'] = data['time(us)'] / 1000
  ylabel = 'Time (ms)'
  
  # Compute medians and std deviations
  medians = data.groupby('name').median()['time(ms)']
  std_devs = data.groupby('name').std()['time(ms)']
  names = data['name'].unique()

  # Ensure ordering of names, medians, and std_devs, match
  medians = [medians[name] for name in names]
  std_devs = [std_devs[name] for name in names]
  
  # Plot the data
  plt.figure(figsize=(8, 4))
  plt.bar(names, medians, yerr=std_devs)

  plt.ylabel(ylabel)
  title = os.path.splitext(os.path.basename(file_path))[0]
  title = title.replace("_", " ")
  title = " ".join([word.capitalize() for word in title.split()])
  plt.title(f"{title}")
  plt.savefig('plot.pdf')

if __name__ == "__main__":
  if len(sys.argv) != 2:
    print("Usage: python plotter.py <path_to_csv_file>")
  else:
    plot_csv(sys.argv[1])
