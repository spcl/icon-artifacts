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

# --- Main Logic ---

# Compile all parts into a single executable
compile_all() {
  # The stage id is passed as the first argument to this function
  local stage_id="$1"

  printf "%s" "\n--- Stage 1: Compiling ---"

  echo "Compiling DaCe/SDFG parts (using stage: ${stage_id})..."
  python -m "stages.stage_${stage_id}" --compile --mode=static

  echo "Compiling final executable..."
  # Link all parts together into the final executable
  $CC main.cc velocity_*.o reductions.o timer.o solve_nh_parts.o \
    -Iinclude \
    -I"codegen/stage${stage_id}" \
    -I"$WORKSPACE_DIR" \
    -I"$DACEROOT/dace/runtime/include" \
    "${COMPILER_FLAGS[@]}" -o verify_solve_nh_parts
  printf "%s" "Executable verify_solve_nh_parts created."
}

# --- Execution ---
main() {
  # Use the first command-line argument as the stage id, defaulting to "0".
  local stage_to_run=${1:-0}

  compile_all "${stage_to_run}"
  printf "%s" "\nScript finished successfully."
}

main "$@"
