clang-format -i struct_defs.h || exit 1
clang-format -i cloudsc-simplified-codegen/src/cpu/cloudsc_driver.cpp || exit 1
clang-format -i cloudsc-simplified-loop2map-codegen/src/cpu/cloudsc_driver.cpp || exit 1

(cd cloudsc-simplified-codegen/build && make clean && make) || exit 1
(cd cloudsc-simplified-loop2map-codegen/build && make clean && make) || exit 1
