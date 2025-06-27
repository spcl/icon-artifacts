#!/bin/bash

# Default coarsening and block size options
X_COARSENINGS=${X_COARSENINGS:-"1 2 4"}
Y_COARSENINGS=${Y_COARSENINGS:-"1 2 4"}
X_BLOCK_SIZES=${X_BLOCK_SIZES:-"32 64 128 256"}
Y_BLOCK_SIZES=${Y_BLOCK_SIZES:-"1 2 4 8"}
VALID_PRODUCTS=${VALID_PRODUCTS:-"256 512"}
export RELEASE=TRUE

# Loop over all valid parameter combinations
for x_c in $X_COARSENINGS; do
  for y_c in $Y_COARSENINGS; do
    for x_bs in $X_BLOCK_SIZES; do
      for y_bs in $Y_BLOCK_SIZES; do

        total=$((x_bs * y_bs))
        if [[ " $VALID_PRODUCTS " == *" $total "* ]]; then
          echo "=== Running for x_c=$x_c, y_c=$y_c, x_bs=$x_bs, y_bs=$y_bs ==="

          # Export the current config to be picked up by Python
          export X_COARSENING=$x_c
          export Y_COARSENING=$y_c
          export X_BLOCK_SIZE=$x_bs
          export Y_BLOCK_SIZE=$y_bs

          # Compile and optimize kernel
          python -m utils.stages.compile_gpu_stage7 --optimize --compile
          if [ $? -ne 0 ]; then
            echo "❌ Compilation failed for this config"
            continue
          fi

          # Run the velocity executable
          ./velocity_gpu.stage7 7
          if [ $? -ne 0 ]; then
            echo "❌ Execution failed for this config"
          fi
        fi

      done
    done
  done
done