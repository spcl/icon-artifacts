#include <cuda_runtime.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>

////////////////////////////////////////////////////
// We are running on host, but the data is on device
////////////////////////////////////////////////////

// max zero reduction interface
void reduce_maxZ_to_address_gpu(const double *__restrict__ d_in, double*__restrict__ d_out, int size, cudaStream_t stream)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Max(nullptr, temp_storage_bytes, d_in, d_out, size, stream);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Max(d_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }

}

double reduce_maxZ_to_scalar_gpu(const double *__restrict__ d_in, int size, cudaStream_t stream)
{

  thrust::device_ptr<const double> d_ptr = thrust::device_pointer_cast(d_in);
  double maxval = thrust::reduce(thrust::cuda::par.on(stream), d_ptr, d_ptr + size, 0.0, thrust::maximum<double>());

  return maxval;
}

// sum reduction interface
void reduce_sum_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, cudaStream_t stream)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Sum(nullptr, temp_storage_bytes, d_in, d_out, size, stream);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Sum(d_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }
}

int reduce_sum_to_scalar_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream)
{
  thrust::device_ptr<const int> d_ptr = thrust::device_pointer_cast(d_in);
  int sumval = thrust::reduce(thrust::cuda::par.on(stream), d_ptr, d_ptr + size, 0, thrust::plus<int>());
  return sumval;
}

// scan reduction interface
int reduce_scan_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream)
{
  return (reduce_sum_to_scalar_gpu(d_in, size, stream) > 0)? 1 : 0;
}

// scan reduction interface
int reduce_scan_gpu(int d_in, int size, cudaStream_t stream)
{
  return (d_in > 0)? 1 : 0;
}

#include <cstdio>

__device__ __forceinline__ int shared_data_reduce_sum_v2(int* __restrict__ shared_data)
{
    constexpr uint NUM_THREADS = 1024;
    constexpr uint NUM_WARPS{NUM_THREADS / 32};
    int sum{0};
#pragma unroll
    for (uint i{0}; i < NUM_WARPS; ++i)
    {
        sum += shared_data[i];
    }
    return sum;
}

__device__ __forceinline__ int warp_reduce_sum(int val)
{
    constexpr unsigned int FULL_MASK{0xffffffff};
#pragma unroll
    for (uint offset{16}; offset > 0; offset /= 2)
    {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val;
}

__device__ __forceinline__ int block_reduce_sum_v2(int const* __restrict__ input_data,
                                    int* __restrict__ shared_data,
                                    int num_elements)
{
    constexpr uint NUM_THREADS = 1024;
    constexpr uint NUM_WARPS{NUM_THREADS / 32};
    uint const num_elements_per_thread{(num_elements + NUM_THREADS - 1) / NUM_THREADS};
    uint const thread_idx{threadIdx.x};
    int sum{0};
    for (uint i{0}; i < num_elements_per_thread; ++i)
    {
        uint const offset{thread_idx + i * NUM_THREADS};
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
    int const block_sum{shared_data_reduce_sum_v2(shared_data)};
    return block_sum;
}


__global__ void batched_reduce_sum_v2(int* __restrict__ output_data,
                                      int const* __restrict__ input_data,
                                      int num_elements_per_batch)
{
    constexpr uint NUM_THREADS = 1024;
    constexpr uint NUM_WARPS{NUM_THREADS / 32};
    uint const block_idx{blockIdx.x};
    uint const thread_idx{threadIdx.x};
    __shared__ int shared_data[NUM_WARPS];
    int const block_sum{block_reduce_sum_v2(
        input_data + block_idx * num_elements_per_batch, shared_data,
        num_elements_per_batch)};
    if (thread_idx == 0)
    {
        output_data[block_idx] = block_sum;
    }
}

void reduce_segmented_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, int batch_size, cudaStream_t stream)
{
    void *batched_reduce_sum_v2_args[] = {
        (void *)&d_out,
        (void *)&d_in,
        (void *)&size
    };
    constexpr uint NUM_WARPS{1024 / 32};

    cudaError_t err = cudaLaunchKernel(
        (void*)batched_reduce_sum_v2,
        dim3(batch_size, 1, 1),
        dim3(1024, 1, 1),
        (void**)batched_reduce_sum_v2_args,
        0,
        stream
    );
    //if (err != cudaSuccess) {
    //    printf("1CUDA error: %s\n", cudaGetErrorString(err));
    //}
    //DACE_KERNEL_LAUNCH_CHECK(err, "batched_reduce_sum_v2", batch_size, 1, 1, NUM_THREADS, 1, 1);
    //batched_reduce_sum_v2<NUM_THREADS><<<batch_size, NUM_THREADS>>>(d_out, d_in, size);
}