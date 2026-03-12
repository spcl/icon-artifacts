#!/bin/bash
#SBATCH --job-name=velocity_gpu2
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=01:00:00
#SBATCH --output=job_output_v2.txt
#SBATCH --error=job_error_v2.txt

spack load gcc@14
spack load cuda

export _RELEASE=1
export GENCODE_NUMBER=90a

#python -m utils.stages.compile_gpu_stage8
#export _PERMUTE_DIMS=1
#python -m utils.stages.compile_gpu_stage8

export CUDA_LAUNCH_BLOCKING=0

nsys profile --trace=nvtx,cuda,osrt,nvtx --cuda-memory-usage=true -o stage8_permuted_nsys ./velocity_gpu.stage8_standalone_release_dim_permuted 9 --reps=10 > gpu_permuted_stage8_nsys.txt 2>&1

nsys profile --trace=nvtx,cuda,osrt,nvtx --cuda-memory-usage=true -o stage8_unpermuted_nsys ./velocity_gpu.stage8_standalone_release_unpermuted 9 --reps=10 > gpu_unpermuted_stage8_nsys.txt 2>&1