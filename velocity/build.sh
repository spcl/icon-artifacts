#!/bin/bash
for STAGE in {1..9}; do
    python -m utils.stages.compile_gpu_stage${STAGE} --optimize --compile 1>>build.out 2>>build.err
done
