set +x

c++ src/cpu/velocity_tendencies.cpp main.cc -I/Users/pmz/gitspace/tmpdace/dace/dace/runtime/include/ -Iinclude/ -Wno-parentheses-equality -std=c++17 -fPIC -fsanitize=address -fsanitize=undefined -g -O0
