#!/bin/bash

# Number of repetitions (e.g., 24 for 24 hours)
NUM_REPEATS=24

for ((i=1; i<=NUM_REPEATS; i++)); do
    echo "[$(date)] Submitting job $i of $NUM_REPEATS..."
    sbatch run_sweep.sh
    sleep 3600  # Wait for 1 hour
done
