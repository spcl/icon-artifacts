#!/bin/bash
#SBATCH --job-name=cc
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=288
#SBATCH --time=04:00:00
#SBATCH --output=permutations_stage4_daint_output.txt
#SBATCH --error=permutations_stage4_daint_error.txt

spack load gcc/76jw6nu
spack load cuda@12.9
export _RELEASE=1
export GENCODE_NUMBER=90a
export OMP_NUM_THREADS=288
export OMP_PROC_BIND=spread
export OMP_PLACES=cores
export OMP_DISPLAY_ENV=TRUE
export __HIP_PLATFORM_AMD__=0
export HIP_PLATFORM_AMD=0
export _STAGE=4
export V2=0
mkdir -p permutations_${_STAGE:-4}

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
<<<<<<< HEAD
python run_permutations.py --configs "c102_e102_b102" --reps ${REPS}
python run_permutations.py --configs "c102_e201_b102" --reps ${REPS}
python run_permutations.py --configs "c102_e021_b120" --reps ${REPS}
python run_permutations.py --configs "c102_e021_b021" --reps ${REPS}
python run_permutations.py --configs "c102_e021_b021" --unpermuted --reps ${REPS}
python run_permutations.py --reps ${REPS}
=======
python run_cpu_permutations.py --configs "c102_e201_b102" --reps ${REPS}
python run_cpu_permutations.py --configs "c102_e102_b102" --unpermuted --reps ${REPS}
python run_cpu_permutations.py --reps ${REPS}
>>>>>>> 56bf9d769bc93c4d91fcfee75ead7a2e7077b614

