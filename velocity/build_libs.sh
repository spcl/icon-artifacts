#!/bin/bash

set -xe

# Handle --clean flag
if [[ "$1" == "--clean" ]]; then
    echo "🧹 Cleaning shared_libs directory..."
    rm -rf ./shared_libs
fi

RELEASE_MODES=(FALSE TRUE)
STAGES=(1 9)

HOST=$(hostname)

for _R in "${RELEASE_MODES[@]}"; do
        export _USE_CUDA_EVENTS=0
        export _TILE=0
        export _REDUCE_BITWIDTH_TRANSFORMATION=1
        export _RELEASE=${_R}
        export _BUILD_LIB_FOR_SOLVE_NH=1
        for STAGE in "${STAGES[@]}"; do
            MODE=$( [[ "$_R" == "FALSE" ]] && echo "debug" || echo "release" )
            LIBNAME="libvelocity_gpu_stage${STAGE}_solve_nh_integration_${MODE}.so"
            TARGET_DIR="./shared_libs/${HOST}/solve_nh_integration/${MODE}/${STAGE}"
            FINAL_LIB="${TARGET_DIR}/libvelocity.so"

            if [[ -f "$FINAL_LIB" ]]; then
                echo "⚠️  $FINAL_LIB already exists — skipping compilation and move"
                continue
            fi
            if [[ -f "$LIBNAME" ]]; then
                echo "⚠️  $LIBNAME already exists — skipping compilation"
            else
                python -m utils.stages.compile_gpu_stage${STAGE} --compile
            fi

            if [[ -f "$LIBNAME" ]]; then
                echo "✅ Found $LIBNAME"
                mkdir -p "$TARGET_DIR"
                mv "$LIBNAME" "$FINAL_LIB"
                echo "📦 Moved and renamed to $FINAL_LIB"
            else
                echo "❌ Missing $LIBNAME after compilation attempt"
                exit 1
            fi
        done
done
