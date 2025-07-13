#!/bin/bash
RELEASE_MODES=(FALSE TRUE)

for _RELEASE in "${RELEASE_MODES[@]}"; do
    export RELEASE=${_RELEASE}
    export _USE_CUDA_EVENTS=0
    export _RELEASE=${_RELEASE}
    export _TILE=0
    export _REDUCE_BITWIDTH_TRANSFORMATION=1
    export _STANDALONE_HEADERS=1
    for STAGE in {1..9}; do
        python -m utils.stages.compile_gpu_stage${STAGE} --optimize --compile
    done
done