#!/bin/bash
#SBATCH --job-name=s4_p1
#SBATCH --nodes=1
#SBATCH --partition=mi300
#SBATCH --exclusive
#SBATCH --time=10:00:00
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=192
#SBATCH --output=sp_permutations_stage4_beverin_output.txt
#SBATCH --error=sp_permutations_stage4_beverin_error.txt

export _RELEASE=1
export GENCODE_NUMBER=90
export OMP_NUM_THREADS=96
export OMP_PROC_BIND=spread
export OMP_PLACES=cores
export OMP_DISPLAY_ENV=TRUE
export __HIP_PLATFORM_AMD__=1
export HIP_PLATFORM_AMD=1
export _STAGE=4
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
export _TBLOCK_DIMS="32,4,1"

export LLVM_HOME=/opt/rocm/llvm/
export PATH=$LLVM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$LLVM_HOME/lib:$LLVM_HOME/lib64:$LD_LIBRARY_PATH
export CPATH=$LLVM_HOME/include:$CPATH
export LIBRARY_PATH=$LLVM_HOME/lib:$LLVM_HOME/lib64:$LIBRARY_PATH
export V2=0
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
export BEVERIN=1
mkdir -p beverin_permutations_${_STAGE:-4}

# --- Configuration ---
# Override via: sbatch --export=CONFIGS="c102_e012_b012,c102_e201_b201" run_sweep.sh
CONFIGS="${CONFIGS:-}"          # empty = all 71
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
export _SUFFIX=""
export V2=0

# Run unpermuted one
python run_cpu_permutations.py --configs "c102_e102_b102" --unpermuted --reps ${REPS}
python run_cpu_permutations.py --configs "c102_e021_b012" --reps ${REPS}
python run_cpu_permutations.py --configs "c102_e201_b102" --reps ${REPS}
#python run_permutations.py --reps ${REPS}

