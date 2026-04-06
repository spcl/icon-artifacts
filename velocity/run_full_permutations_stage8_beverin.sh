#!/bin/bash
#SBATCH --job-name=s8_p_full
#SBATCH --nodes=1
#SBATCH --partition=mi300
#SBATCH --exclusive
#SBATCH --time=18:00:00
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=192
#SBATCH --output=permutations_stage8_beverin_output.txt
#SBATCH --error=permutations_stage8_beverin_error.txt

export _RELEASE=1
export GENCODE_NUMBER=90
export OMP_NUM_THREADS=96
export OMP_PROC_BIND=spread
export OMP_PLACES=cores
export OMP_DISPLAY_ENV=TRUE
export __HIP_PLATFORM_AMD__=1
export HIP_PLATFORM_AMD=1
export BEVERIN=1
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
export CUPY_HIPCC_GENERATE_CODE=--offload-arch=gfx942
export _STAGE=8
export RM_TIMERS=1
export _TBLOCK_DIMS="32,4,1"


export LLVM_HOME=/opt/rocm/llvm/
export PATH=$LLVM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$LLVM_HOME/lib:$LLVM_HOME/lib64:$LD_LIBRARY_PATH
export CPATH=$LLVM_HOME/include:$CPATH
export LIBRARY_PATH=$LLVM_HOME/lib:$LLVM_HOME/lib64:$LIBRARY_PATH

spack load python@3.13.8
export CFLAGS="-I$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))") ${CFLAGS}"
export C_INCLUDE_PATH="$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))"):${C_INCLUDE_PATH}"


#START_DIR=$(pwd)
#DACE_DIR=$(python3 -c "import dace; import os; print(os.path.dirname(os.path.dirname(dace.__file__)))")
#echo "dace found at: $DACE_DIR"
#cd "$DACE_DIR"
#git fetch origin
#git checkout f2dace/staging
#cd "$START_DIR"
mkdir -p beverin_full_permutations_${_STAGE:-8}

# --- Configuration ---
CONFIGS="${CONFIGS:-}"          # empty = all
REPS="${REPS:-100}"

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

export _REDUCE_BITWIDTH_TRANSFORMATION=0
export _SUFFIX="full_"
export V2=0
# Run unpermuted one
python run_stage8_permutations.py --configs="nlev_first" --reps ${REPS}
python run_stage8_permutations.py --configs="index_only" --reps ${REPS}
python run_stage8_permutations.py --unpermuted --reps ${REPS}
python run_stage8_permutations.py --reps ${REPS}

