#pragma once

#if __HIP_PLATFORM_AMD__ == 1
#include <hip/hip_runtime.h>
#define gpuDeviceSynchronize hipDeviceSynchronize
#else
#include <cuda_runtime.h>
#define gpuDeviceSynchronize cudaDeviceSynchronize
#endif

static void dace_wait_device()
{
    gpuDeviceSynchronize();
}