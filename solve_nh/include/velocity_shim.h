#pragma once

#if defined(GPU)

#include "velocity_shim_gpu.h"

#else

#include "velocity_shim_cpu.h"

#endif