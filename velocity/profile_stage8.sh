#!/bin/bash
#SBATCH --job-name=velocity_gpu3
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=04:30:00
#SBATCH --output=stage8_out.txt
#SBATCH --error=stage8_err.txt

pyenv activate dace_py_12
spack load gcc@14
spack load cuda@12.9

export _RELEASE=1
export _PROFILE=0
export GENCODE_ARCH="arch=compute_90a,code=sm_90a"

export _PERMUTE_DIMS=0; export _PROFILE=0; python -m utils.stages.compile_gpu_stage8
export _PERMUTE_DIMS=1; export _PROFILE=0; python -m utils.stages.compile_gpu_stage8

echo "Running unpermuted executable..."
./velocity_gpu.stage8_standalone_release_unpermuted --reps=20 > gpu_unpermuted_stage8.txt 2>&1


echo "Running permuted executable..."
./velocity_gpu.stage8_standalone_release_dim_permuted --reps=20 > gpu_permuted_stage8.txt 2>&1

echo "All runs finished."

ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage8_ln_perm \
  ./velocity_gpu.stage8_standalone_release_dim_permuted 9 --reps=2


echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage8_ln_unperm \
  ./velocity_gpu.stage8_standalone_release_unpermuted 9 --reps=2

echo "All runs finished."

export _PERMUTE_DIMS=0; export _PROFILE=1; python -m utils.stages.compile_gpu_stage8
export _PERMUTE_DIMS=1; export _PROFILE=1; python -m utils.stages.compile_gpu_stage8

export CUDA_LAUNCH_BLOCKING=1

echo "Running unpermuted executable..."
./velocity_gpu.stage8_standalone_release_unpermuted --reps=20 > gpu_unpermuted_profile_stage8.txt 2>&1


echo "Running permuted executable..."
./velocity_gpu.stage8_standalone_release_dim_permuted --reps=20 > gpu_permuted_profile_stage8.txt 2>&1

export CUDA_LAUNCH_BLOCKING=0
