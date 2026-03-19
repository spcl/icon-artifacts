#!/bin/bash
#SBATCH --job-name=velocity_gpu_profile
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=02:30:00
#SBATCH --output=job_output.txt
#SBATCH --error=job_error.txt

spack load gcc/76jw6nu
spack load cuda@12.9

export _RELEASE=1
export GENCODE_NUMBER=90


python -m utils.stages.compile_gpu_stage6


#echo "Running permuted executable..."
./velocity_gpu.stage6_standalone_release_permuted_single_map >> gpu_permuted_stage6.txt 2>&1

echo "Profiling permuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  --clock-control none \
  -f \
  -o stage6_ln_perm \
  ./velocity_gpu.stage6_standalone_release_permuted_single_map 9 --reps=3 \
  > gpu_permuted_ncu.txt 2>&1


#echo "Running unpermuted executable..."
./velocity_gpu.stage6_standalone_release_unpermuted >> gpu_unpermuted_stage6.txt 2>&1
sleep 1

echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  --clock-control none \
  -f \
  -o stage6_ln_unperm \
  ./velocity_gpu.stage6_standalone_release_unpermuted 9 --reps=3 \
  > gpu_unpermuted_ncu.txt 2>&1

echo "All runs finished."