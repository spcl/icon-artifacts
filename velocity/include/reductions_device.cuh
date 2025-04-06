#pragma once

#define __REDUCE_DEVICE__

__device__ __inline__ double reduce_maxZ_to_scalar_device(const double *d_in, int size)
{
    double max_val = 0.0;
    for (int i = 0; i < size; i++){
        max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
    return max_val;
}

__device__ __inline__ void reduce_maxZ_to_scalar_device(const double *d_in, double* d_out, int size)
{
    d_out[0] = reduce_maxZ_to_scalar_device(d_in, size);
}

// sum reduction interface
__device__ __inline__ int reduce_sum_to_scalar_device(const int *d_in, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++){
        sum += d_in[i];
    }
    return sum;
}

__device__ __inline__ void reduce_maxZ_to_address_device(const int *d_in, int* d_out, int size)
{
    d_out[0] = reduce_sum_to_scalar_device(d_in, size);
}

// scan reduction interface
__device__ __inline__ int reduce_scan_device(const int *d_in, int size)
{
    return (reduce_sum_to_scalar_device(d_in, size) > 0) ? 1 : 0;
}

__device__ __inline__ double reduce_maxZ_device(const double d_in, int size)
{
    return d_in;
}

// sum reduction interface
__device__ __inline__ int reduce_sum_device(const int d_in, int size)
{
    return d_in;
}

// scan reduction interface
__device__ __inline__ int reduce_scan_device(const int d_in, int size)
{
    return (d_in > 0) ? 1 : 0;
}