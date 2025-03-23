set +x

c++ src/cpu/solve_nh.cpp main.cc -I/Users/pmz/gitspace/tmpdace/dace/dace/runtime/include/ -Iinclude/ -Wno-parentheses-equality -std=c++20 -fPIC -fsanitize=address -fsanitize=undefined -g -O0
