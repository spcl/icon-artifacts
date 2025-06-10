#!/bin/bash



NPROMA_VALUES=(20480 32)
RELEASE_MODES=(FALSE TRUE)

for _RELEASE in "${RELEASE_MODES[@]}"; do
  for _NPROMA in "${NPROMA_VALUES[@]}"; do
    rm -rf *.got *.want
    rm -f velocity_gpu.stage*
    rm *.csv

    export RELEASE=${_RELEASE}
    export NPROMA=${_NPROMA}

    LOG_SUFFIX="${RELEASE,,}_nproma${NPROMA}_split"  # ${RELEASE,,} makes lowercase
    LOG_FILE="gpu_log_stage7_${LOG_SUFFIX}.log"
    ERR_FILE="gpu_log_stage7_${LOG_SUFFIX}.err"
    LOG_DIFF_FILE="gpu_log_stage7_${LOG_SUFFIX}_diff.log"
    ERR_DIFF_FILE="gpu_log_stage7_${LOG_SUFFIX}_diff.err"

    echo "===> Running with RELEASE=$RELEASE and NPROMA=$NPROMA"
    echo "===> Log file: $LOG_FILE"
    echo "===> Error file: $ERR_FILE"

    for STAGE in {1..6}; do
      python -m utils.stages.compile_gpu_stage${STAGE} --optimize --no-compile
    done

    python -m utils.stages.compile_gpu_stage7 --optimize --compile

    ./velocity_gpu.stage7 2>"$ERR_FILE" 1>"$LOG_FILE"
    python utils/compare_got_and_want.py 2>"$ERR_DIFF_FILE" 1>"$LOG_DIFF_FILE"

    rm -rf *.got *.want
    rm -f velocity_gpu.stage*
    rm *.csv
  done
done

rm -rf *.got *.want
rm -f velocity_gpu.stage*
rm *.csv