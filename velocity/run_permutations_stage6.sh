#!/bin/bash
#SBATCH --job-name=velocity_gpu_perm_sweep
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=04:00:00
#SBATCH --output=permutations/job_output.txt
#SBATCH --error=permutations/job_error.txt

spack load gcc/76jw6nu
spack load cuda@12.9
export _RELEASE=1
export GENCODE_NUMBER=90

mkdir -p permutations_${_STAGE:-6}

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
export _STAGE=6
python run_permutations.py --configs "c102_e102_b102" --unpermuted --reps ${REPS}
python run_permutations.py --reps ${REPS}

