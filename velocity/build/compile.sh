nvcc velocity_no_nproma_if_prop_lvn_only_0_istep_2.cu \
    velocity_no_nproma_if_prop_lvn_only_0_istep_2_cuda.cu \
    timer.cpp \
    reductions_kernel.cu \
    reductions.cpp \
    -I. \
    -I./runtime/include \
    --diag-suppress 68 --diag-suppress 550 --diag-suppress 20208 --diag-suppress 1835 \
    --diag-suppress 177 --diag-suppress 20012 --diag-suppress 1098 \
    -Xcompiler=-Wall -Xcompiler=-Wextra -Xcompiler=-Wno-unused-parameter \
    -Xcompiler=-Wno-unknown-pragmas -Xcompiler=-O3 -Xcompiler=-faligned-new \
    --expt-relaxed-constexpr -arch=native --use_fast_math -O3 \
    -std=c++17 -rdc=true -Xcompiler=-fPIC \
    --compiler-options '-fPIC' --shared  -o libvelocity_gpu.so