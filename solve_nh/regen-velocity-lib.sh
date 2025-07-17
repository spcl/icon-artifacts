#!/usr/bin/env bash
set -xeuo pipefail

#
# This script regenerates the main executable with injected velocity kernels.
# It involves three main stages:
# 1. Fetching CUDA source files for velocity kernels from a specific git branch.
# 2. Patching these files to be compatible with a standard C++ compiler (removing CUDA specifics).
# 3. Compiling the patched files, the main DaCe-generated code, and a main wrapper to create a single executable.
#

# --- Configuration ---
# Source git branch for velocity kernels
GIT_SOURCE_BRANCH="origin/new_sched_solve_nh"
# Base path for the velocity kernel source files within the git repository
VELOCITY_SRC_BASE_PATH="velocity/codegen"
# Workspace directory to store fetched and patched files
WORKSPACE_DIR="velocity_workspace"
# Root of the DaCe installation. Can be overridden by setting the environment variable.
DACEROOT=${DACEROOT:-/Users/pmz/gitspace/dace/}

# --- Compiler Setup ---
# Select compiler based on the operating system
if [[ "$(uname)" == "Darwin" ]]; then
  CC="clang++"
else
  CC="g++"
fi

# Compiler-specific error limit flag
ERRLIM=()
if [[ "$CC" == "clang++" ]]; then
  ERRLIM+=(-ferror-limit=1)
else
  ERRLIM+=(-fmax-errors=1)
fi

# Warning flags
WARNING_FLAGS=(
  -g -Wall -Wextra
  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
  -Wno-unused-but-set-variable -Wno-unused-but-set-parameter -Wno-sign-compare
)
[[ "$CC" == "clang++" ]] && WARNING_FLAGS+=(
  -Wno-parentheses-equality -Wno-constant-logical-operand
)

# Optimization and standard flags
OPTIMIZATION_FLAGS=(-O0 -march=native -fno-strict-aliasing -fno-omit-frame-pointer -fno-fast-math -ffp-contract=off)
STANDARD_FLAGS=(-std=c++20 -fPIC -fopenmp)

# Combine all
COMPILER_FLAGS=(
  "${ERRLIM[@]}"
  "${WARNING_FLAGS[@]}"
  "${OPTIMIZATION_FLAGS[@]}"
  "${STANDARD_FLAGS[@]}"
)

# --- Helper Functions ---

# Portable sed -i across Linux and macOS
# Sets the sed_inplace_opt variable with the correct option for in-place editing
get_sed_inplace_opt() {
  if [[ $(uname) == "Darwin" ]]; then
    sed_inplace_opt=('-i' '')
  else
    sed_inplace_opt=('-i')
  fi
}

# --- Main Logic ---

# Stage 1: Fetch source files from Git
fetch_sources() {
  # The stage id is passed as the first argument to this function
  local stage_id="$1"

  printf "%s" "--- Stage 1: Fetching source files from Git ---"
  mkdir -p "$WORKSPACE_DIR"

  # Use two indexed arrays for portability, as associative arrays (`declare -A`) are not supported in older bash versions (e.g., on macOS).
  local dest_files=("velocity_1.cc" "velocity_2.cc" "velocity_3.cc" "velocity_4.cc" "velocity_1.h" "velocity_2.h" "velocity_3.h" "velocity_4.h")
  local src_paths=(
    "velocity_no_nproma_if_prop_lvn_only_0_istep_1/src/cpu/velocity_no_nproma_if_prop_lvn_only_0_istep_1.cu"
    "velocity_no_nproma_if_prop_lvn_only_1_istep_1/src/cpu/velocity_no_nproma_if_prop_lvn_only_1_istep_1.cu"
    "velocity_no_nproma_if_prop_lvn_only_0_istep_2/src/cpu/velocity_no_nproma_if_prop_lvn_only_0_istep_2.cu"
    "velocity_no_nproma_if_prop_lvn_only_1_istep_2/src/cpu/velocity_no_nproma_if_prop_lvn_only_1_istep_2.cu"
    "velocity_no_nproma_if_prop_lvn_only_0_istep_1/include/velocity_no_nproma_if_prop_lvn_only_0_istep_1.h"
    "velocity_no_nproma_if_prop_lvn_only_1_istep_1/include/velocity_no_nproma_if_prop_lvn_only_1_istep_1.h"
    "velocity_no_nproma_if_prop_lvn_only_0_istep_2/include/velocity_no_nproma_if_prop_lvn_only_0_istep_2.h"
    "velocity_no_nproma_if_prop_lvn_only_1_istep_2/include/velocity_no_nproma_if_prop_lvn_only_1_istep_2.h"
  )

  for i in "${!dest_files[@]}"; do
    local dest_file="${dest_files[$i]}"
    local src_path="${src_paths[$i]}"
    echo "Fetching $src_path..."
    git show "$GIT_SOURCE_BRANCH:$VELOCITY_SRC_BASE_PATH/stage${stage_id}/${src_path}" > "$WORKSPACE_DIR/$dest_file"
  done

  # Fetch other necessary files
  echo "Fetching supporting files..."
  git show "$GIT_SOURCE_BRANCH:velocity/include/reductions_cpu.h" > "$WORKSPACE_DIR/reductions_cpu.h"
  git show "$GIT_SOURCE_BRANCH:velocity/include/reductions_kernel.cuh" > "$WORKSPACE_DIR/reductions_kernel.h"
  git show "$GIT_SOURCE_BRANCH:velocity/include/timer.h" > "$WORKSPACE_DIR/timer.h"
  git show "$GIT_SOURCE_BRANCH:velocity/src/reductions.cpp" > "$WORKSPACE_DIR/reductions.cc"
  git show "$GIT_SOURCE_BRANCH:velocity/src/reductions_kernel.cu" > "$WORKSPACE_DIR/reductions_kernel.cc"
  git show "$GIT_SOURCE_BRANCH:velocity/src/timer.cpp" > "$WORKSPACE_DIR/timer.cc"
  echo "Done fetching files."
}

# Stage 2: Patch fetched files to remove CUDA-specific code
patch_sources() {
  printf "%s" "\n--- Stage 2: Patching source files ---"
  local sed_inplace_opt
  get_sed_inplace_opt

  # Replace CUDA header with standard header
  find "$WORKSPACE_DIR/" -name 'velocity_*.cc' -exec sed "${sed_inplace_opt[@]}" 's|"reductions_kernel.cuh"|"reductions_kernel.h"|g' {} +

  # Remove CUDA-specific includes, keywords, and function calls from reduction kernels
  sed "${sed_inplace_opt[@]}" \
    -e '/#include <cuda_runtime\.h>/d' \
    -e '/#include[[:space:]]*<thrust\/.*>/d' \
    -e '/cudaStream_t/d' \
    -e 's/\(__global__\)/static/g' \
    "$WORKSPACE_DIR/reductions_kernel.h"

  sed "${sed_inplace_opt[@]}" \
    -e 's/\(__device__\)//g' \
    -e 's/\(__forceinline__\)//g' \
    "$WORKSPACE_DIR/reductions_kernel.cc"

  # Run various patches on the velocity sources.
  # Note: The glob is intentionally unquoted to allow shell expansion.
  sed "${sed_inplace_opt[@]}" \
    -e '/#include "\.\.\/\.\.\/include\/hash\.h"/d' \
    -e '/cudaDeviceSynchronize[[:space:]]*(.*);/d' \
    -e '/cleanup_reduce_sum_gpu/d' \
    -e '/cleanup_reduce_maxZ_gpu/d' \
    "$WORKSPACE_DIR"/velocity_*.cc

  # Normalize DaCe-generated symbols
  sed -E "${sed_inplace_opt[@]}" 's/(->__f2dace_.*_d_[0-9]+_s)_[0-9]+/\1/g' "$WORKSPACE_DIR"/velocity_*.cc

  for f in "$WORKSPACE_DIR"/velocity_*.*; do
    # Prepend includes. The `i` command with a backslash and literal newline
    # is the portable way to insert lines across different versions of sed.
    sed "${sed_inplace_opt[@]}" '1s|^|#include <dace/dace.h>\n#include "shared_struct_defs.h"\n|' "$f"

    # Remove `__restrict__` keywords.
    sed "${sed_inplace_opt[@]}" 's/__restrict__ //g' "$f"

    # Filter out the DaCe state structure definition, which is not needed in the final binary
    awk '
    /\/\* DaCe AUTO-GENERATED FILE\. DO NOT MODIFY \*\// { print; skip=1; next }
    /struct velocity_no_nproma_.*_state_t \{/ { skip=0; print; next }
    !skip
    ' "$f" > "$f.tmp" && mv "$f.tmp" "$f"

    # Filter out the DaCe state structure definition, which is not needed in the final binary
    awk '
    /^#define __DACE_CODEGEN_VELOCITY_NO_NPROMA_IF_PROP_LVN_ONLY_[01]_ISTEP_[12]__/ { skip=1; next }
    /struct velocity_no_nproma_.*_state_t/ { skip=0; print; next }
    !skip
    ' "$f" > "$f.tmp" && mv "$f.tmp" "$f"
  done

  echo "Formatting code with clang-format..."
  clang-format -i "$WORKSPACE_DIR"/*.h "$WORKSPACE_DIR"/*.cc

  cat "$WORKSPACE_DIR"/velocity_*.h > include/velocity.h
  rm "$WORKSPACE_DIR"/velocity_*.h

  echo "Done patching files."
}

# Stage 3: Compile velocit library.
compile_velocity() {
  printf "%s" "\n--- Stage 3: Compiling ---"

  echo "Compiling velocity library..."
  # Compile patched velocity sources into object files
  $CC "$WORKSPACE_DIR"/velocity_*.cc "$WORKSPACE_DIR"/reductions.cc "$WORKSPACE_DIR"/timer.cc \
    -Iinclude \
    -I"$WORKSPACE_DIR" \
    -I"$DACEROOT/dace/runtime/include" \
    "${COMPILER_FLAGS[@]}" -c

  # Archive object files into a static library
  ar rcs libvelocity.a velocity_*.o reductions.o timer.o
  echo "libvelocity.a created."
}


# --- Execution ---
main() {
  # Use the first command-line argument as the stage id, defaulting to "1".
  local stage_to_fetch=${1:-1}

  fetch_sources "${stage_to_fetch}"
  patch_sources
  compile_velocity
  printf "%s" "\nScript finished successfully."
}

main "$@"
