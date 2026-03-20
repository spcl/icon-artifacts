#pragma once

#include <iostream>
#include <chrono>

#if __HIP_PLATFORM_AMD__ == 1
#include <hip/hip_runtime.h>
#define gpuMalloc        hipMalloc
#define gpuMemset        hipMemset
#define gpuDeviceSynchronize hipDeviceSynchronize
#define LAUNCH_KERNEL(kernel, grid, block, ...) \
    hipLaunchKernelGGL(kernel, grid, block, 0, 0, __VA_ARGS__)
#else
#include <cuda_runtime.h>
#define gpuMalloc        cudaMalloc
#define gpuMemset        cudaMemset
#define gpuDeviceSynchronize cudaDeviceSynchronize
#define LAUNCH_KERNEL(kernel, grid, block, ...) \
    kernel<<<grid, block>>>(__VA_ARGS__)
#endif

static double* flush_buffer = nullptr;
static double* block_sums   = nullptr;
static const size_t FLUSH_SIZE  = 268435456;   // 256 MB > L2 of any current GPU
static const size_t CHUNK_SIZE  = 256 * 1024 / sizeof(double); // 256 KB per block (in doubles)
static const size_t NUM_CHUNKS  = FLUSH_SIZE / (CHUNK_SIZE * sizeof(double));
static const int    BLOCK_SIZE  = 256;         // threads per block

// Kernel to flush both L1 and L2 caches by reading a large buffer.
// buffer     : device memory (size at least L2_SIZE)
// chunk_size : number of elements per block (must be > L1 size per SM)
// num_chunks : total blocks launched
// block_sums : output array (size num_chunks) - used only to force the reads
static __global__ void flush_caches_kernel(const double* buffer, size_t chunk_size,
                                           size_t num_chunks, double* block_sums)
{
    size_t block_id = blockIdx.x;
    if (block_id >= num_chunks) return;

    size_t start = block_id * chunk_size;
    double sum = 0.0;

    for (size_t i = start + threadIdx.x; i < start + chunk_size; i += blockDim.x) {
        sum += buffer[i];
    }

    __shared__ double shared[256];
    shared[threadIdx.x] = sum;
    __syncthreads();

    for (int s = blockDim.x / 2; s > 0; s >>= 1) {
        if (threadIdx.x < s) {
            shared[threadIdx.x] += shared[threadIdx.x + s];
        }
        __syncthreads();
    }

    if (threadIdx.x == 0) {
        block_sums[block_id] = shared[0];
    }
}

static void flush_all_caches()
{
    if (!flush_buffer) {
        gpuMalloc(&flush_buffer, FLUSH_SIZE);
        gpuMalloc(&block_sums, NUM_CHUNKS * sizeof(double));
    }

    gpuMemset(flush_buffer, 0, FLUSH_SIZE);
    gpuDeviceSynchronize();

    LAUNCH_KERNEL(flush_caches_kernel, NUM_CHUNKS, BLOCK_SIZE,
                  flush_buffer, CHUNK_SIZE, NUM_CHUNKS, block_sums);
    gpuDeviceSynchronize();
}

static void dace_measure_time(const char *tag = nullptr)
{
    static int timer_call_count = 0;
    static std::chrono::high_resolution_clock::time_point timer_last_time =
        std::chrono::high_resolution_clock::now();

    if (timer_call_count % 2 == 1) {
        auto now = std::chrono::high_resolution_clock::now();
        unsigned long int start =
            std::chrono::duration_cast<std::chrono::microseconds>(
                timer_last_time.time_since_epoch()).count();
        unsigned long int end =
            std::chrono::duration_cast<std::chrono::microseconds>(
                now.time_since_epoch()).count();
        std::cout << "Timer " << tag << " took " << (end - start) << " us" << std::endl;
    } else {
        flush_all_caches();
        timer_last_time = std::chrono::high_resolution_clock::now();
    }
    timer_call_count++;
}