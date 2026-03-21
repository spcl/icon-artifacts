#!/bin/bash
#SBATCH --job-name=velocity_gpu_perm_sweep
#SBATCH --nodes=1
#SBATCH --partition=mi300
#SBATCH --exclusive
#SBATCH --time=07:00:00
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=192
#SBATCH --output=permutations_stage4_beverin_output.txt
#SBATCH --error=permutations_stage4_beverin_error.txt

export _RELEASE=1
export GENCODE_NUMBER=90
export OMP_NUM_THREADS=96
export OMP_PROC_BIND=true
export OMP_PLACES=cores
export OMP_DISPLAY_ENV=TRUE
export __HIP_PLATFORM_AMD__=1
export HIP_PLATFORM_AMD=1
export _STAGE=4

mkdir -p beverin_permutations_${_STAGE:-4}

export ROCM_HOME=/opt/rocm
export HIP_PATH=$ROCM_HOME
export HIPCC=$ROCM_HOME/bin/hipcc
export PATH=$ROCM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$ROCM_HOME/lib:$ROCM_HOME/lib64:$LD_LIBRARY_PATH
export CPATH=$ROCM_HOME/include:$CPATH
export LIBRARY_PATH=$ROCM_HOME/lib:$ROCM_HOME/lib64:$LIBRARY_PATH
export CFLAGS="-I$ROCM_HOME/include"
export LDFLAGS="-L$ROCM_HOME/lib -L$ROCM_HOME/lib64"
export CUPY_INSTALL_USE_HIP=1
export HCC_AMDGPU_TARGET=gfx942

spack load python@3.13.8
export CFLAGS="-I$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))") ${CFLAGS}"
export C_INCLUDE_PATH="$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))"):${C_INCLUDE_PATH}"

export HCC_AMDGPU_TARGET=gfx942
export CUPY_HIPCC_GENERATE_CODE=--offload-arch=gfx942

#START_DIR=$(pwd)
#DACE_DIR=$(python3 -c "import dace; import os; print(os.path.dirname(os.path.dirname(dace.__file__)))")
#echo "dace found at: $DACE_DIR"
#cd "$DACE_DIR"
#git fetch origin
#git checkout f2dace/staging
#cd "$START_DIR"

# --- Configuration ---
# Override via: sbatch --export=CONFIGS="c102_e012_b012,c102_e201_b201" run_sweep.sh
CONFIGS="${CONFIGS:-}"          # empty = all 71
REPS="${REPS:-50}"

# --- Build arguments ---
ARGS="--reps ${REPS}"

if [ -n "$CONFIGS" ]; then
    ARGS="$ARGS --configs $CONFIGS"
fi


echo "=== Permutation sweep ==="
echo "CONFIGS:    ${CONFIGS:-all}"
echo "REPS:       $REPS"
echo "NCU:        $NCU"
echo "UNPERMUTED: $UNPERMUTED"
echo "========================="

# Run unpermuted one
python run_permutations.py --configs "c102_e102_b102" --unpermuted --reps ${REPS}
python run_permutations.py --reps ${REPS}

