#!/bin/bash
#SBATCH --job-name=velocity_gpu_profile_reorder
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=02:30:00
#SBATCH --output=job_output_reorder.txt
#SBATCH --error=job_error_reorder.txt

spack load gcc/76jw6nu
spack load cuda@12.9

export _RELEASE=1
export GENCODE_NUMBER=90


python -m utils.stages.compile_gpu_stage6


#echo "Running unpermuted executable..."
./velocity_gpu.stage6_standalone_release_unpermuted > gpu_unpermuted_stage6_v2.txt 2>&1

echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_unperm_v2 \
  ./velocity_gpu.stage6_standalone_release_unpermuted 9 --reps=3 \
  > gpu_unpermuted_ncu_v2.txt 2>&1


#echo "Running permuted executable..."
./velocity_gpu.stage6_standalone_release_permuted_single_map > gpu_permuted_stage6_v2.txt 2>&1

echo "Profiling permuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_perm_v2 \
  ./velocity_gpu.stage6_v2_standalone_release_permuted_single_map 9 --reps=3 \
  > gpu_permuted_ncu_v2.txt 2>&1

