#!/usr/bin/env bash
set -xeuo pipefail

# --- Default configuration ---
GIT_SOURCE_BRANCH="origin/new_sched_solve_nh"
VELOCITY_SHARED_LIB_ROOT="velocity/shared_libs"
MACHINE="ault23.cscs.ch"
BUILD_MODE="debug"  # Options: debug, release
LIB_MODE="solve_nh_integration"

# --- Parse arguments ---
while [[ $# -gt 0 ]]; do
    case "$1" in
        --machine)
            MACHINE="$2"
            shift 2
            ;;
        --mode)
            BUILD_MODE="$2"
            shift 2
            ;;
        --help|-h)
            echo "Usage: $0 [--machine MACHINE] [--mode MODE]"
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            echo "Usage: $0 [--machine MACHINE] [--mode MODE]"
            exit 1
            ;;
    esac
done

# --- Fetch shared libraries ---
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_0.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_1.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/1/libvelocity.so" > "libvelocity_2.so"
git show "${GIT_SOURCE_BRANCH}:${VELOCITY_SHARED_LIB_ROOT}/${MACHINE}/${LIB_MODE}/${BUILD_MODE}/9/libvelocity.so" > "libvelocity_3.so"
