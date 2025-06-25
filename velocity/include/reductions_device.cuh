#pragma once
#include <cstdint>

#define __REDUCE_DEVICE__

__device__ __inline__ double reduce_maxZ_to_scalar_device(const double * __restrict__ d_in, int size)
{
    double max_val = 0.0;
    #pragma unroll
    for (int i = 0; i < size; i++){
        max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
    return max_val;
}

__device__ __inline__ void reduce_maxZ_to_address_device(const double * __restrict__ d_in, double * __restrict__ d_out, int size)
{
    d_out[0] = reduce_maxZ_to_scalar_device(d_in, size);
}

// sum reduction interface
__device__ __inline__ int reduce_sum_to_scalar_device(const int * __restrict__ d_in, int size)
{
    int sum = 0;
    #pragma unroll
    for (int i = 0; i < size; i++){
        sum += d_in[i];
    }
    return sum;
}


__device__ __inline__ uint8_t reduce_sum_to_scalar_device(const uint8_t * __restrict__ d_in, int size)
{
    uint8_t sum = 0;
    #pragma unroll
    for (int i = 0; i < size; i++){
        sum += d_in[i];
    }
    return sum;
}


__device__ __inline__ int strided_reduce_sum_to_scalar_device(const int * __restrict__ d_in, int size, int stride)
{
    int sum = 0;
    #pragma unroll
    for (int i = 0; i < size; i+=stride){
        sum += d_in[i];
    }
    return sum;
}

__device__ __inline__ void reduce_sum_to_address_device(const int * __restrict__ d_in, int* __restrict__ d_out, int size)
{
    d_out[0] = reduce_sum_to_scalar_device(d_in, size);
}

__device__ __inline__ void strided_reduce_sum_to_address_device(const int * __restrict__ d_in, int* __restrict__ d_out, int size, int stride)
{
    d_out[0] = strided_reduce_sum_to_scalar_device(d_in, size, stride);
}


// scan reduction interface
__device__ __inline__ int reduce_scan_device(const int * __restrict__ d_in, int size)
{
    return (reduce_sum_to_scalar_device(d_in, size) > 0) ? 1 : 0;
}

__device__ __inline__ int reduce_scan_device(int d_in, int size)
{
    return (d_in > 0) ? 1 : 0;
}

__device__ __inline__ uint8_t reduce_scan_device(const uint8_t * __restrict__ d_in, int size)
{
    return (reduce_sum_to_scalar_device(d_in, size) > 0) ? 1 : 0;
}

__device__ __inline__ uint8_t reduce_scan_device(uint8_t d_in, int size)
{
    return (d_in > 0) ? 1 : 0;
}