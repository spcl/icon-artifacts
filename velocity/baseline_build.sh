set +x

source /scratch/wbenjami/icon-dace/cpu_modules.sh

DACERT_INCDIR=/scratch/pmazumde/gitspace/dace/dace/runtime/include/
VELOCITY_INCDIR=generated_data/codegen/cpu/include/
SERDE_INCDIR=generated_data/

VELOCITY_CC=generated_data/codegen/cpu/src/cpu/velocity_tendencies.cpp

export ASAN_OPTIONS=new_delete_type_mismatch=0

c++ ${VELOCITY_CC} main.cc -o numerically_validate \
-I${DACERT_INCDIR} \
-I${VELOCITY_INCDIR} \
-I${SERDE_INCDIR} \
-Wno-parentheses-equality -std=c++20 -fPIC -fsanitize=address -fsanitize=undefined -g -O0
