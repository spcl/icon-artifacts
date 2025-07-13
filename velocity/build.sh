#!/bin/bash
RELEASE_MODES=(FALSE TRUE)

for _R in "${RELEASE_MODES[@]}"; do
    for _BL in {0, 1}; do
        export _USE_CUDA_EVENTS=0
        export _RELEASE=${_R}
        export RELEASE=${_R}
        export _TILE=0
        export _REDUCE_BITWIDTH_TRANSFORMATION=1
        export _STANDALONE_HEADERS=1
        export _BUILD_LIB_FOR_SOLVE_NH=${BL}
        for STAGE in {1..9}; do
            python -m utils.stages.compile_gpu_stage${STAGE} --optimize --compile
        done
    done
done