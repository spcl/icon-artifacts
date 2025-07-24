#pragma once

#include "cuda_runtime.h"

static void dace_wait_device()
{
    cudaDeviceSynchronize();
}
