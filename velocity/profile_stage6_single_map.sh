#!/bin/bash
#SBATCH --job-name=velocity_gpu2
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=02:00:00
#SBATCH --output=stage6_out.txt
#SBATCH --error=stage6_err.txt

pyenv activate dace_py_12
spack load gcc@14
spack load cuda@12.9

export _RELEASE=1
export _PROFILE=0
export GENCODE_ARCH="arch=compute_90a,code=sm_90a"
export CUDA_LAUNCH_BLOCKING=1

python -m utils.stages.compile_gpu_stage6

echo "Running permuted executable..."
./velocity_gpu.stage6_standalone_release_permuted_single_map --reps=20 > gpu_permuted_profile_stage6.txt 2>&1

echo "Running unpermuted executable..."
./velocity_gpu.stage6_standalone_release_unpermuted --reps=20 > gpu_unpermuted_profile_stage6.txt 2>&1

echo "All runs finished."

echo "Profiling permuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_perm \
  ./velocity_gpu.stage6_standalone_release_permuted_single_map 9 --reps=4


echo "Profiling unpermuted executable with Nsight Compute..."
ncu \
  --set full \
  --import-source yes \
  -f \
  -o stage6_ln_unperm \
  ./velocity_gpu.stage6_standalone_release_unpermuted 9 --reps=4

echo "All runs finished."