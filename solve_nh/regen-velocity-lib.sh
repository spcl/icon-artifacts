#!/usr/bin/env bash
set -xeuo pipefail


# --- Configuration ---
# Source git branch for the precompiled libraries
GIT_SOURCE_BRANCH="origin/libs"
# Base path for the precompiled libraries within the git repository
VELOCITY_SRC_BASE_PATH="libraries"

VT_STAGE_1_AULT_SO="libvelocity_gpu_stage1_x86_a100_cpu_input_solve_nh_integration_release.so"

for N in 0 1 2; do
  SO_NAME="libvelocity_gpu_stage1_x86_a100_cpu_input_solve_nh_integration_release.so"
  OUTPUT_SO="libvelocity_${N}.so"
  echo "Fetching $SO_NAME from git for $OUTPUT_SO..."
  git show "$GIT_SOURCE_BRANCH:$VELOCITY_SRC_BASE_PATH/$SO_NAME" > "$OUTPUT_SO"
  echo "Saved as $OUTPUT_SO"
done
