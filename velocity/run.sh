#!/bin/bash
#SBATCH --job-name=velten        # Optional: set a job name
#SBATCH --nodes=1                # Request 1 node
#SBATCH --partition=amda100      # Use the amda100 partition
#SBATCH --time=04:00:00          # Set the wall time limit
#SBATCH --output=slurm-%j.out    # Save output to slurm-jobid.out
#SBATCH --error=slurm-%j.err

NPROMA_VALUES=(20480)
RELEASE_MODES=(TRUE)

spack load nvhpc@25.1
export _TILE=0
export _REDUCE_BITWIDTH_TRANSFORMATION=1
export _USE_NVHPC=TRUE
export _USE_CUDA_EVENTS=FALSE

for _RELEASE in "${RELEASE_MODES[@]}"; do
  for _NPROMA in "${NPROMA_VALUES[@]}"; do
    rm -rf *.got *.want
    rm -f velocity_gpu.stage*
    rm *.csv

    export RELEASE=${_RELEASE}
    export NPROMA=${_NPROMA}
    export _RELEASE=${_RELEASE}
    export _NPROMA=${_NPROMA}

    LOG_SUFFIX="${RELEASE,,}_nproma${NPROMA}_split"  # ${RELEASE,,} makes lowercase
    LOG_FILE="gpu_log_stage8_${LOG_SUFFIX}.log"
    ERR_FILE="gpu_log_stage8_${LOG_SUFFIX}.err"
    LOG_DIFF_FILE="gpu_log_stage8_${LOG_SUFFIX}_diff.log"
    ERR_DIFF_FILE="gpu_log_stage8_${LOG_SUFFIX}_diff.err"

    echo "===> Running with RELEASE=$RELEASE and NPROMA=$NPROMA"
    echo "===> Log file: $LOG_FILE"
    echo "===> Error file: $ERR_FILE"

    python -m utils.stages.compile_gpu_stage8 --optimize --compile

    ./velocity_gpu.stage8 2>"$ERR_FILE" 1>"$LOG_FILE"
    python utils/compare_got_and_want.py 2>"$ERR_DIFF_FILE" 1>"$LOG_DIFF_FILE"

    rm -rf *.got *.want
    #rm -f velocity_gpu.stage*
    rm *.csv
  done
done

rm -rf *.got *.want
#rm -f velocity_gpu.stage*
rm *.csv