#!/bin/bash
#SBATCH --job-name=s8_p_low
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=16:00:00
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=288
#SBATCH --output=lowering_permutations_stage8_output.txt
#SBATCH --error=lowering_permutations_stage8_error.txt

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
export RM_TIMERS=1
export _TBLOCK_DIMS="32,16,1"

export _STAGE=8
mkdir -p permutations_${_STAGE:-8}

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

export _REDUCE_BITWIDTH_TRANSFORMATION=1
export _SUFFIX="lowered_full_"
export V2=0
# Run unpermuted one
python run_stage8_permutations.py --unpermuted --reps ${REPS}
python run_stage8_permutations.py --configs="nlev_first" --reps ${REPS}
python run_stage8_permutations.py --configs="index_only" --reps ${REPS}
#python run_stage8_permutations.py --reps ${REPS}

