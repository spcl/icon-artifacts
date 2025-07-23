#!/usr/bin/env bash
set -xeuo pipefail


# --- Configuration ---
# Source git branch for the precompiled libraries
GIT_SOURCE_BRANCH="origin/new_sched_solve_nh"
# Base path for the precompiled libraries within the git repository
VELOCITY_SHARED_LIB_ROOT="velocity/shared_libs"
MACHINE="local"
LIB_MODE="solve_nh_integration"
BUILD_MODE="debug" # Options: debug, release

# For stages 0-3, we will fetch the same VT shared library file built at stage 1.
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_0.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_1.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_2.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/9/libvelocity.so" > "libvelocity_3.so"
