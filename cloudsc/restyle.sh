set -x

clang-format -i struct_defs.h || exit 1
clang-format -i cloudsc_driver_ffi.cc || exit 1
clang-format -i cloudsc-simplified-codegen/include/cloudsc_driver.h || exit 1
clang-format -i cloudsc-simplified-loop2map-codegen/include/cloudsc_driver.h || exit 1
clang-format -i cloudsc-simplified-codegen/src/cpu/cloudsc_driver.cpp || exit 1
clang-format -i cloudsc-simplified-loop2map-codegen/src/cpu/cloudsc_driver.cpp || exit 1
clang-format -i cloudsc-partial3/include/cloudsc_driver.h || exit 1
clang-format -i cloudsc-partial3/src/cpu/cloudsc_driver.cpp || exit 1
