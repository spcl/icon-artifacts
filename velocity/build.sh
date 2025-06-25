#!/bin/bash
for STAGE in {1..7}; do
    python -m utils.stages.compile_gpu_stage${STAGE} --optimize --compile
done
