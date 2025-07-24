#!/bin/bash
#SBATCH --job-name=sweep_job
#SBATCH --nodes=1
#SBATCH --partition=debug
#SBATCH --time=00:30:00
#SBATCH --account=g34
#SBATCH --output=logs/sweep_%j.out
#SBATCH --error=logs/sweep_%j.err

python sweep.py
