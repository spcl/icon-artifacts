#!/bin/bash

# ------------------------------------------------------------
# Configuration: edit these paths to match your actual folders
# ------------------------------------------------------------

# Stage 4 (CPU) and Stage 6 (GPU) results
BEVERIN_STAGE4="beverin_permutations_4"   # CPU
DAINT_STAGE4="daint_permutations_4"       # CPU
BEVERIN_STAGE6="beverin_permutations_6"   # GPU
DAINT_STAGE6="daint_permutations_6"       # GPU

# Stage 5 (CPU?) and Stage 8 (GPU?) results
BEVERIN_STAGE5="beverin_full_permutations_5"   # CPU
DAINT_STAGE5="daint_full_permutations_5"       # CPU
BEVERIN_STAGE8="beverin_full_permutations_8"   # GPU
DAINT_STAGE8="daint_full_permutations_8"       # GPU

# Titles (used in plots)
TITLE_BEVERIN_CPU="AMD Zen 4 96 Core"
TITLE_DAINT_CPU="Grace"
TITLE_BEVERIN_GPU="AMD MI300A"
TITLE_DAINT_GPU="NVIDIA GH200"

# Output directory for PNG files (will be created if missing)
OUTDIR="plots"
mkdir -p "$OUTDIR"

# Python script name (assumed to be in current directory)
PY_SCRIPT="plot_permutations.py"   # Change if needed

# ------------------------------------------------------------
# Helper: run the Python script with given arguments and move outputs
# ------------------------------------------------------------
run_and_move() {
    local suffix="$1"   # suffix for output filenames
    shift
    # Run the Python script
    python3 "$PY_SCRIPT" "$@"
    # Move the generated PNG files to OUTDIR with suffix
    for step in step7 step9 combined; do
        if [ -f "violin_plot_${step}.png" ]; then
            mv "violin_plot_${step}.png" "$OUTDIR/violin_plot_${step}_${suffix}.png"
            echo "Moved violin_plot_${step}.png -> $OUTDIR/violin_plot_${step}_${suffix}.png"
        fi
    done
    mv "violin_plot.png" "$OUTDIR/violin_plot_def_${suffix}.png"
}

# ----------------------------------------------------------------------
# Group 1: Stage 4 (CPU) and Stage 6 (GPU)
# ----------------------------------------------------------------------
echo "========== Group 1: Stage 4 (CPU) & Stage 6 (GPU) =========="

# 1) Individual plots (each folder alone)
run_and_move "beverin_stage4" --gpu "$BEVERIN_STAGE4" --gpu-title "$TITLE_BEVERIN_CPU"
run_and_move "daint_stage4"   --gpu "$DAINT_STAGE4"   --gpu-title "$TITLE_DAINT_CPU"
run_and_move "beverin_stage6" --gpu "$BEVERIN_STAGE6" --gpu-title "$TITLE_BEVERIN_GPU"
run_and_move "daint_stage6"   --gpu "$DAINT_STAGE6"   --gpu-title "$TITLE_DAINT_GPU"

# 2) Combined all four
run_and_move "stage4_6_all" \
    --cpu   "$BEVERIN_STAGE4"  --cpu-title "$TITLE_BEVERIN_CPU" \
    --cpu2  "$DAINT_STAGE4"    --cpu2-title "$TITLE_DAINT_CPU" \
    --gpu   "$BEVERIN_STAGE6"  --gpu-title "$TITLE_BEVERIN_GPU" \
    --gpu2  "$DAINT_STAGE6"    --gpu2-title "$TITLE_DAINT_GPU"

# ----------------------------------------------------------------------
# Group 2: Stage 5 (CPU) and Stage 8 (GPU)
# ----------------------------------------------------------------------
echo "========== Group 2: Stage 5 (CPU) & Stage 8 (GPU) =========="

# 1) Individual plots
run_and_move "beverin_stage5" --gpu "$BEVERIN_STAGE5" --gpu-title "$TITLE_BEVERIN_CPU"
run_and_move "daint_stage5"   --gpu "$DAINT_STAGE5"   --gpu-title "$TITLE_DAINT_CPU"
run_and_move "beverin_stage8" --gpu "$BEVERIN_STAGE8" --gpu-title "$TITLE_BEVERIN_GPU"
run_and_move "daint_stage8"   --gpu "$DAINT_STAGE8"   --gpu-title "$TITLE_DAINT_GPU"

# 2) Combined all four
run_and_move "stage5_cpu_only" \
    --gpu   "$BEVERIN_STAGE5"  --gpu-title "$TITLE_BEVERIN_CPU" \
    --gpu2  "$DAINT_STAGE5"    --gpu2-title "$TITLE_DAINT_CPU"

run_and_move "stage8_gpu_only" \
    --gpu   "$BEVERIN_STAGE8"  --gpu-title "$TITLE_BEVERIN_GPU" \
    --gpu2  "$DAINT_STAGE8"    --gpu2-title "$TITLE_DAINT_GPU"

run_and_move "stage5_8_all" \
    --cpu   "$BEVERIN_STAGE5"  --cpu-title "$TITLE_BEVERIN_CPU" \
    --cpu2  "$DAINT_STAGE5"    --cpu2-title "$TITLE_DAINT_CPU" \
    --gpu   "$BEVERIN_STAGE8"  --gpu-title "$TITLE_BEVERIN_GPU" \
    --gpu2  "$DAINT_STAGE8"    --gpu2-title "$TITLE_DAINT_GPU"

echo "All done. Plots saved in $OUTDIR/"