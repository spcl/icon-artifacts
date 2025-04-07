#pragma once

void reduce_maxZ_to_address_gpu(const double *d_in, double* d_out, int size);
void reduce_sum_to_address_gpu(const int *d_in, int* d_out, int size);

double reduce_maxZ_to_scalar_gpu(const double *d_in, int size);
int reduce_sum_to_scalar_gpu(const int *d_in, int size);

int reduce_scan_gpu(int d_in, int size);
int reduce_scan_gpu(const int *d_in, int size);


template <size_t NUM_WARPS>
__device__ int shared_data_reduce_sum_v2(int shared_data[NUM_WARPS])
{
    int sum{0};
#pragma unroll
    for (size_t i{0}; i < NUM_WARPS; ++i)
    {
        sum += shared_data[i];
    }
    return sum;
}

__device__ int warp_reduce_sum(int val)
{
    constexpr unsigned int FULL_MASK{0xffffffff};
#pragma unroll
    for (size_t offset{16}; offset > 0; offset /= 2)
    {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val;
}

template <size_t NUM_THREADS, size_t NUM_WARPS = NUM_THREADS / 32>
__device__ int block_reduce_sum_v2(int const* __restrict__ input_data,
                                    int shared_data[NUM_WARPS],
                                    size_t num_elements)
{
    size_t const num_elements_per_thread{(num_elements + NUM_THREADS - 1) / NUM_THREADS};
    size_t const thread_idx{threadIdx.x};
    int sum{0};
    for (size_t i{0}; i < num_elements_per_thread; ++i)
    {
        size_t const offset{thread_idx + i * NUM_THREADS};
        if (offset < num_elements)
        {
            sum += input_data[offset];
        }
    }
    sum = warp_reduce_sum(sum);
    if (threadIdx.x % 32 == 0)
    {
        shared_data[threadIdx.x / 32] = sum;
    }
    __syncthreads();
    int const block_sum{shared_data_reduce_sum_v2<NUM_WARPS>(shared_data)};
    return block_sum;
}

template <size_t NUM_THREADS>
__global__ void batched_reduce_sum_v2(int* __restrict__ output_data,
                                      int const* __restrict__ input_data,
                                      size_t num_elements_per_batch)
{
    constexpr size_t NUM_WARPS{NUM_THREADS / 32};
    size_t const block_idx{blockIdx.x};
    size_t const thread_idx{threadIdx.x};
    __shared__ int shared_data[NUM_WARPS];
    int const block_sum{block_reduce_sum_v2<NUM_THREADS, NUM_WARPS>(
        input_data + block_idx * num_elements_per_batch, shared_data,
        num_elements_per_batch)};
    if (thread_idx == 0)
    {
        output_data[block_idx] = block_sum;
    }
}

template <size_t NUM_THREADS>
void reduce_segmented_to_address_gpu(const int *d_in, int* d_out, int size, int size2, cudaStream_t stream)
{
    batched_reduce_sum_v2<NUM_THREADS><<<size2, NUM_THREADS, 0, stream>>>(d_out, d_in, size);
}
