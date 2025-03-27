#pragma once

__device__ double reduce_maxZ_device(const double *d_in, int size);
double reduce_maxZ_device(const double d_in, int size);
__device__ int reduce_sum_device(const int *d_in, int size);
int reduce_sum_device(const int d_in, int size);
__device__ double reduce_scan_device(const int *d_in, int size);
double reduce_scan_device(const int d_in, int size);
double reduce_maxZ_gpu(const double *d_in, int size);
int reduce_sum_gpu(const int *d_in, int size);
double reduce_scan_gpu(const int *d_in, int size);