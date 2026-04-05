#!/bin/bash
#SBATCH --job-name=cc2
#SBATCH --nodes=1
#SBATCH --partition=normal
#SBATCH --exclusive
#SBATCH --time=00:40:00
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=288
#SBATCH --output=full_permutations_stage4_output.txt
#SBATCH --error=full_permutations_stage4_error.txt

spack load gcc/76jw6nu
spack load cuda@12.9
export _RELEASE=1
export GENCODE_NUMBER=90
export OMP_NUM_THREADS=288
export OMP_PROC_BIND=spread
export OMP_PLACES=cores
export OMP_DISPLAY_ENV=TRUE
export __HIP_PLATFORM_AMD__=0
export HIP_PLATFORM_AMD=0
export _TBLOCK_DIMS="32,16,1"

export _STAGE=5
mkdir -p daint_full_permutations_${_STAGE:-5}

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
export V2=1

# Run unpermuted one
# "c102_e021_b012" -> nlev first
python run_stage4_permutations.py --configs="index_only" --reps ${REPS}
python run_stage4_permutations.py --configs="nlev_first" --reps ${REPS}
python run_stage4_permutations.py --unpermuted --reps ${REPS}
python run_stage4_permutations.py --reps ${REPS}

