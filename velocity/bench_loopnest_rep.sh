#!/bin/bash
#SBATCH --job-name=velocity_gpu_profile
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --output=job_output.txt
#SBATCH --error=job_error.txt

spack load gcc/76jw6nu
spack load cuda@12.9

export _RELEASE=1
export GENCODE_NUMBER=90
export _PROFILE=0

python -m utils.stages.compile_gpu_stage6

for i in {1..10}; do
    echo "=== Iteration $i (permuted) ===" >> gpu_permuted_stage6.txt
    sleep 10
    ./velocity_gpu.stage6_standalone_release_permuted_single_map >> gpu_permuted_stage6.txt 2>&1

    echo "=== Iteration $i (unpermuted) ===" >> gpu_unpermuted_stage6.txt
    sleep 10
    ./velocity_gpu.stage6_standalone_release_unpermuted >> gpu_unpermuted_stage6.txt 2>&1

    sleep 10
done