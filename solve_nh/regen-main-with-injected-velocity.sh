set -x

mkdir -p velocity_workspace

git show origin/new_sched:velocity/codegen/stage5/velocity_no_nproma_if_prop_lvn_only_0_istep_1/src/cpu/velocity_no_nproma_if_prop_lvn_only_0_istep_1.cu > velocity_workspace/velocity_1.cc
git show origin/new_sched:velocity/codegen/stage5/velocity_no_nproma_if_prop_lvn_only_1_istep_1/src/cpu/velocity_no_nproma_if_prop_lvn_only_1_istep_1.cu > velocity_workspace/velocity_2.cc
git show origin/new_sched:velocity/codegen/stage5/velocity_no_nproma_if_prop_lvn_only_0_istep_2/src/cpu/velocity_no_nproma_if_prop_lvn_only_0_istep_2.cu > velocity_workspace/velocity_3.cc
git show origin/new_sched:velocity/codegen/stage5/velocity_no_nproma_if_prop_lvn_only_1_istep_2/src/cpu/velocity_no_nproma_if_prop_lvn_only_1_istep_2.cu > velocity_workspace/velocity_4.cc

git show origin/new_sched:velocity/include/reductions_cpu.h > velocity_workspace/reductions_cpu.h
git show origin/new_sched:velocity/include/reductions_kernel.cuh > velocity_workspace/reductions_kernel.h
git show origin/new_sched:velocity/include/timer.h > velocity_workspace/timer.h
git show origin/new_sched:velocity/src/reductions.cpp > velocity_workspace/reductions.cc
git show origin/new_sched:velocity/src/reductions_kernel.cu > velocity_workspace/reductions_kernel.cc
git show origin/new_sched:velocity/src/timer.cpp > velocity_workspace/timer.cc

find velocity_workspace/ -name 'velocity_*.cc' -exec sed -i '' 's|"reductions_kernel\.cuh"|"reductions_kernel.h"|g' {} +
sed -i '' '/#include <cuda_runtime\.h>/d' velocity_workspace/reductions_kernel.h velocity_workspace/reductions_kernel.cc
sed -i '' '/#include[[:space:]]*<thrust\/.*>/d' velocity_workspace/reductions_kernel.cc
sed -i '' '/cudaStream_t/d' velocity_workspace/reductions_kernel.h
sed -i '' 's/\(__global__\)/static/g' velocity_workspace/reductions_kernel.h
sed -i '' 's/\(__device__\)//g' velocity_workspace/reductions_kernel.cc
sed -i '' 's/\(__forceinline__\)//g' velocity_workspace/reductions_kernel.cc
sed -i '' '/#include "\.\.\/\.\.\/include\/hash\.h"/d' velocity_workspace/velocity_*.cc
sed -i '' '/cudaDeviceSynchronize[[:space:]]*(.*);/d' velocity_workspace/velocity_*.cc
sed -i '' '/cleanup_reduce_sum_gpu/d' velocity_workspace/velocity_*.cc
sed -i '' '/cleanup_reduce_maxZ_gpu/d' velocity_workspace/velocity_*.cc
sed -E -i '' 's/(->__f2dace_.*_d_[0-9]+_s)_[0-9]+/\1/g' velocity_workspace/velocity_*.cc

for f in velocity_workspace/velocity_*.cc; do
  sed -i '' '1s|^|#include <dace/dace.h>\n#include "shared_struct_defs.h"\n|' "$f"
  awk '
  /\/\* DaCe AUTO-GENERATED FILE\. DO NOT MODIFY \*\// { print; skip=1; next }
  /struct velocity_no_nproma_.*_state_t \{/ { skip=0; print; next }
  !skip
  ' "$f" > "$f.tmp" && mv "$f.tmp" "$f"
done

clang-format -i velocity_workspace/*.h velocity_workspace*.cc

clang++ velocity_workspace/velocity_*.cc velocity_workspace/reductions.cc velocity_workspace/timer.cc \
  -I/Users/pmz/gitspace/dace/dace/runtime/include \
  -Iinclude \
  -Ivelocity_workspace \
  -ferror-limit=1 -g -Wall -Wall -Wextra \
  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable \
  -Wno-unused-but-set-parameter -Wno-sign-compare -Wno-parentheses-equality -Wno-constant-logical-operand \
  -O3 -march=native -fno-strict-aliasing -fno-omit-frame-pointer \
  -std=c++23 -fPIC -fopenmp -c
ar rcs libvelocity.a velocity_*.o reductions.o timer.o

python -m stages.stage_0 --compile --mode=static

clang++ main.cc libvelocity.a libverify_solve_nh_parts.a \
  -Iinclude \
  -Icodegen/stage0 \
  -I/Users/pmz/gitspace/dace/dace/runtime/include \
  -ferror-limit=1 -g -Wall -Wall -Wextra \
  -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable \
  -Wno-unused-but-set-parameter -Wno-sign-compare -Wno-parentheses-equality -Wno-constant-logical-operand \
  -O3 -march=native -fno-strict-aliasing -fno-omit-frame-pointer \
  -std=c++23 -fPIC -fopenmp -o verify_solve_nh_parts