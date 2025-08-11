#!/bin/bash

# Number of repetitions (e.g., 24 for 24 hours)
NUM_REPEATS=18

for ((i=1; i<=NUM_REPEATS; i++)); do
    echo "[$(date)] Submitting job $i of $NUM_REPEATS..."
    sbatch submit_sweep.sh
    # Wait for job to finish before submitting the next one
    while squeue -u $USER | grep -q "sweep_job"; do
        # Check every 15 minutes
        sleep 900
    done
done
