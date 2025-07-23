#!/bin/bash
RELEASE_MODES=(FALSE)
INTEGRATION_MODES=(1 )

for _R in "${RELEASE_MODES[@]}"; do
    for _BL in "${INTEGRATION_MODES[@]}"; do
        export _USE_CUDA_EVENTS=0
        export _RELEASE=${_R}
        export _TILE=0
        export _REDUCE_BITWIDTH_TRANSFORMATION=1
        export _BUILD_LIB_FOR_SOLVE_NH=${BL}
        python -m utils.stages.compile_gpu_stage9 --compile
    done
done