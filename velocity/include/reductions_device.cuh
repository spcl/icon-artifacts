#pragma once

#define __REDUCE_DEVICE__

__device__ double reduce_maxZ_device(const double *d_in, int size);
__device__ int reduce_sum_device(const int *d_in, int size);
__device__ double reduce_scan_device(const int *d_in, int size);