#!/bin/bash
# Build and run the transpose benchmark
# Assumes CUTENSOR_ROOT is set, or cutensor is in system paths

CUTENSOR_INC=""
CUTENSOR_LIB="-lcutensor"

if [ -n "$CUTENSOR_ROOT" ]; then
    CUTENSOR_INC="-I${CUTENSOR_ROOT}/include"
    CUTENSOR_LIB="-L${CUTENSOR_ROOT}/lib -lcutensor"
fi

set -ex
nvcc -O3 -std=c++17 -arch=sm_86 \
    transpose_bench.cu \
    ${CUTENSOR_INC} \
    ${CUTENSOR_LIB} \
    -o transpose_bench

./transpose_bench