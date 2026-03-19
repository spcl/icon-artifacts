#!/bin/bash
#SBATCH --job-name=velocity_gpu2
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=05:30:00
#SBATCH --output=job_output_v2.txt
#SBATCH --error=job_error_v2.txt


spack load gcc/76jw6nu
spack load cuda@12.9

export _RELEASE=1
export GENCODE_NUMBER=90

export _PERMUTE_DIMS=0 
export _PROFILE=0
python -m utils.stages.compile_gpu_stage8

export _PERMUTE_DIMS=1
export _PROFILE=0
python -m utils.stages.compile_gpu_stage8


echo "Running unpermuted executable..."
./velocity_gpu.stage8_standalone_release_unpermuted 9 > gpu_unpermuted_stage8.txt 2>&1

echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  --clock-control none \
  -f \
  -o stage8_dim_unperm \
  ./velocity_gpu.stage8_standalone_release_unpermuted 9 --reps=3 \
  > gpu_unpermuted_stage8_ncu.txt 2>&1

echo "Running permuted executable..."
./velocity_gpu.stage8_standalone_release_dim_permuted 9 > gpu_permuted_stage8.txt 2>&1

echo "Profiling permuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  --clock-control none \
  -f \
  -o stage8_dim_perm \
  ./velocity_gpu.stage8_standalone_release_dim_permuted 9 --reps=3 \
  > gpu_permuted_stage8_ncu.txt 2>&1

echo "All runs finished."