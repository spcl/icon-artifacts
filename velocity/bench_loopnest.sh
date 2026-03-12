#!/bin/bash
#SBATCH --job-name=velocity_gpu_profile
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=02:30:00
#SBATCH --output=job_output.txt
#SBATCH --error=job_error.txt

spack load gcc@14
spack load cuda

export _RELEASE=1
export GENCODE_NUMBER=90

#python -m utils.stages.compile_gpu_stage6


#echo "Running permuted executable..."
#./velocity_gpu.stage6_standalone_release_permuted_single_map 9 > gpu_permuted.txt 2>&1

echo "Profiling permuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_perm \
  ./velocity_gpu.stage6_standalone_release_permuted_single_map 9 \
  > gpu_permuted_ncu.txt 2>&1


#echo "Running unpermuted executable..."
#./velocity_gpu.stage6_standalone_release_unpermuted 9 > gpu_unpermuted.txt 2>&1

echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_unperm \
  ./velocity_gpu.stage6_standalone_release_unpermuted 9 \
  > gpu_unpermuted_ncu.txt 2>&1

echo "All runs finished."