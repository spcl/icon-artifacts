#!/bin/bash
#SBATCH --job-name=sweep_job
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --time=0:59:00
#SBATCH --output=logs/sweep_%j.out
#SBATCH --error=logs/sweep_%j.err

python3 sweep.py
# python3 sweep_eval.py logs/tested_params.log
