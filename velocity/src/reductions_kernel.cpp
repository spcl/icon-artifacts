#if __HIP_PLATFORM_AMD__ == 1

#include "hip/hip_runtime.h"
#include <hip/hip_runtime.h>
#include <hipcub/hipcub.hpp>
#define GPU_PREFIX(name) hip##name
#define gpuStream_t hipStream_t
#define gpuMalloc hipMalloc
#define gpuFree hipFree
#define DEVICE_REDUCE hipcub::DeviceReduce
#define LAUNCH_KERNEL(kernel, grid, block, stream, ...) \
    hipLaunchKernelGGL(kernel, grid, block, 0, stream, __VA_ARGS__)

#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>
#include <cstdint>

////////////////////////////////////////////////////
// Max reduction
////////////////////////////////////////////////////

static void* maxZ_temp_storage = nullptr;

void reduce_maxZ_to_address_gpu(const double *__restrict__ d_in,
                                double *__restrict__ d_out,
                                int size,
                                gpuStream_t stream)
{
    static size_t temp_storage_bytes = 0;
    static int last_size = -1;

    if (size > last_size) {
        if (maxZ_temp_storage != nullptr) {
            gpuFree(maxZ_temp_storage);
            maxZ_temp_storage = nullptr;
        }
        temp_storage_bytes = 0;
        DEVICE_REDUCE::Max(nullptr, temp_storage_bytes, d_in, d_out, size, stream);
        if (temp_storage_bytes != 0) {
            gpuMalloc(&maxZ_temp_storage, temp_storage_bytes);
        }
        last_size = size;
    }

    DEVICE_REDUCE::Max(maxZ_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);
}

void cleanup_reduce_maxZ_gpu()
{
    if (maxZ_temp_storage != nullptr) {
        gpuFree(maxZ_temp_storage);
        maxZ_temp_storage = nullptr;
    }
}

double reduce_maxZ_to_scalar_gpu(const double *__restrict__ d_in, int size, gpuStream_t stream)
{
    thrust::device_ptr<const double> d_ptr = thrust::device_pointer_cast(d_in);
    return thrust::reduce(d_ptr, d_ptr + size, 0.0, thrust::maximum<double>());
}

////////////////////////////////////////////////////
// Sum reduction
////////////////////////////////////////////////////

static void* sum_temp_storage = nullptr;

void reduce_sum_to_address_gpu(const double *__restrict__ d_in,
                               double *__restrict__ d_out,
                               int size,
                               gpuStream_t stream)
{
    static size_t temp_storage_bytes = 0;
    static int last_size = -1;

    if (sum_temp_storage == nullptr || size != last_size) {
        if (sum_temp_storage != nullptr) {
            gpuFree(sum_temp_storage);
            sum_temp_storage = nullptr;
        }
        temp_storage_bytes = 0;
        DEVICE_REDUCE::Sum(nullptr, temp_storage_bytes, d_in, d_out, size, stream);
        if (temp_storage_bytes != 0) {
            gpuMalloc(&sum_temp_storage, temp_storage_bytes);
        }
        last_size = size;
    }

    DEVICE_REDUCE::Sum(sum_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);
}

void cleanup_reduce_sum_gpu()
{
    if (sum_temp_storage != nullptr) {
        gpuFree(sum_temp_storage);
        sum_temp_storage = nullptr;
    }
}

int reduce_sum_to_scalar_gpu(const int *__restrict__ d_in, int size, gpuStream_t stream)
{
    thrust::device_ptr<const int> d_ptr = thrust::device_pointer_cast(d_in);
    return thrust::reduce(d_ptr, d_ptr + size, 0, thrust::plus<int>());
}

////////////////////////////////////////////////////
// Scan reduction (any-positive check)
////////////////////////////////////////////////////

int reduce_scan_gpu(const int *__restrict__ d_in, int size, gpuStream_t stream)
{
    return (reduce_sum_to_scalar_gpu(d_in, size, stream) > 0) ? 1 : 0;
}

int reduce_scan_gpu(int d_in, int size, gpuStream_t stream)
{
    return (d_in > 0) ? 1 : 0;
}

////////////////////////////////////////////////////
// Dimensional scan kernels — int
////////////////////////////////////////////////////

__global__ void kernel_reduce_scan_last_dim(const int *__restrict__ arr,
                                            int *__restrict__ out,
                                            int start, int end, int D, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    int acc = 0;
    for (int d = start; d < end; d++) {
        acc = arr[i + d * N] > 0 ? 1 : acc;
    }
    out[i] = acc;
}

__global__ void kernel_reduce_scan_first_dim(const int *__restrict__ arr,
                                             int *__restrict__ out,
                                             int start, int end, int D, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    int acc = 0;
    for (int d = start; d < end; d++) {
        acc = arr[d + i * D] > 0 ? 1 : acc;
    }
    out[i] = acc;
}

void reduce_scan_last_dim(const int *arr, int *out,
                          int start, int end, int D, int N)
{
    LAUNCH_KERNEL(kernel_reduce_scan_last_dim, 1, 96, 0, arr, out, start, end, D, N);
}

void reduce_scan_first_dim(const int *arr, int *out,
                           int start, int end, int D, int N)
{
    LAUNCH_KERNEL(kernel_reduce_scan_first_dim, 1, 96, 0, arr, out, start, end, D, N);
}

////////////////////////////////////////////////////
// Dimensional scan kernels — uint8_t
////////////////////////////////////////////////////

__global__ void kernel_reduce_scan_last_dim(const uint8_t *__restrict__ arr,
                                            uint8_t *__restrict__ out,
                                            int start, int end, int D, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    uint8_t acc = 0;
    for (int d = start; d < end; d++) {
        acc = arr[i + d * N] > 0 ? 1 : acc;
    }
    out[i] = acc;
}

__global__ void kernel_reduce_scan_first_dim(const uint8_t *__restrict__ arr,
                                             uint8_t *__restrict__ out,
                                             int start, int end, int D, int N)
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if (i >= N) return;

    uint8_t acc = 0;
    for (int d = start; d < end; d++) {
        acc = arr[d + i * D] > 0 ? 1 : acc;
    }
    out[i] = acc;
}

void reduce_scan_last_dim(const uint8_t *arr, uint8_t *out,
                          int start, int end, int D, int N)
{
    LAUNCH_KERNEL(kernel_reduce_scan_last_dim, 1, 96, 0, arr, out, start, end, D, N);
}

void reduce_scan_first_dim(const uint8_t *arr, uint8_t *out,
                           int start, int end, int D, int N)
{
    LAUNCH_KERNEL(kernel_reduce_scan_first_dim, 1, 96, 0, arr, out, start, end, D, N);
}

#endif