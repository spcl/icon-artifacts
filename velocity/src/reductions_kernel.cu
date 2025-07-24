#include <cuda_runtime.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>

////////////////////////////////////////////////////
// We are running on host, but the data is on device
////////////////////////////////////////////////////


__device__ __forceinline__ int shared_data_reduce_sum_v2(int* __restrict__ shared_data)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int sum{0};
#pragma unroll
    for (int i{0}; i < NUM_WARPS; ++i)
    {
        sum += shared_data[i];
    }
    return sum;
}

__device__ __forceinline__ double shared_data_reduce_max_v2(double* __restrict__ shared_data)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    double max{-1.0e300}; // Initialize to a very small value
#pragma unroll
    for (int i{0}; i < NUM_WARPS; ++i)
    {
        max = shared_data[i] > max ? shared_data[i] : max;
    }
    return max;
}


__device__ __forceinline__ int warp_reduce_sum(int val)
{
    constexpr unsigned int FULL_MASK{0xffffffff};
#pragma unroll
    for (int offset{16}; offset > 0; offset /= 2)
    {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val;
}

__device__ __forceinline__ double warp_reduce_max(double val)
{
    constexpr unsigned int FULL_MASK{0xffffffff};
    #pragma unroll
    for (int offset{16}; offset > 0; offset /= 2)
    {
        val = max(val, __shfl_down_sync(FULL_MASK, val, offset));
    }
    return val;
}

__device__ __forceinline__ int block_reduce_sum_v2(int const* __restrict__ input_data,
                                    int* __restrict__ shared_data,
                                    int num_elements)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    const int num_elements_per_thread{(num_elements + NUM_THREADS - 1) / NUM_THREADS};
    const int thread_idx{threadIdx.x};
    int sum{0};
    for (int i{0}; i < num_elements_per_thread; ++i)
    {
        int const offset{thread_idx + i * NUM_THREADS};
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

__device__ __forceinline__ double block_reduce_max_v2(double const* __restrict__ input_data,
                                    double* __restrict__ shared_data,
                                    int num_elements)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    const int num_elements_per_thread{(num_elements + NUM_THREADS - 1) / NUM_THREADS};
    const int thread_idx{threadIdx.x};
    double max{-1.0e300}; // Initialize to a very small value
    for (int i{0}; i < num_elements_per_thread; ++i)
    {
        int const offset{thread_idx + i * NUM_THREADS};
        if (offset < num_elements)
        {
            max = input_data[offset]  > max ? input_data[offset] : max;
        }
    }
    max = warp_reduce_max(max);
    if (threadIdx.x % 32 == 0)
    {
        shared_data[threadIdx.x / 32] = max;
    }
    __syncthreads();
    double const block_max{shared_data_reduce_max_v2(shared_data)};
    return block_max;
}


__global__ void batched_reduce_sum_v2(int* __restrict__ output_data,
                                      int const* __restrict__ input_data,
                                      int num_elements_per_batch)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int const block_idx{blockIdx.x};
    int const thread_idx{threadIdx.x};
    __shared__ int shared_data[NUM_WARPS];
    int const block_sum{block_reduce_sum_v2(
        input_data + block_idx * num_elements_per_batch, shared_data,
        num_elements_per_batch)};
    if (thread_idx == 0)
    {
        output_data[block_idx] = block_sum;
    }
}

__global__ void batched_reduce_max_v2(double* __restrict__ output_data,
                                      double const* __restrict__ input_data,
                                      int num_elements_per_batch)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int const block_idx{blockIdx.x};
    int const thread_idx{threadIdx.x};
    __shared__ double shared_data[NUM_WARPS];
    double const block_max{block_reduce_max_v2(
        input_data + block_idx * num_elements_per_batch, shared_data,
        num_elements_per_batch)};
    if (thread_idx == 0)
    {
        output_data[block_idx] = block_max;
    }
}

static void* maxZ_temp_storage = nullptr;
void reduce_maxZ_to_address_gpu(const double *__restrict__ d_in,
                                 double* __restrict__ d_out,
                                 int size,
                                 cudaStream_t stream)
{
  // Static variables to persist across calls
  static size_t temp_storage_bytes = 0;
  static int last_size = -1;

  // Only allocate once, or if size has changed
  if (maxZ_temp_storage == nullptr || size != last_size) {
    if (maxZ_temp_storage != nullptr) {
      cudaFree(maxZ_temp_storage);
      maxZ_temp_storage = nullptr;
    }
    temp_storage_bytes = 0;
    cub::DeviceReduce::Max(nullptr, temp_storage_bytes, d_in, d_out, size, nullptr);
    if (temp_storage_bytes != 0) {
      cudaMalloc(&maxZ_temp_storage, temp_storage_bytes);
    }
    last_size = size;
  }

  // Call the reduction
  cub::DeviceReduce::Max(maxZ_temp_storage, temp_storage_bytes, d_in, d_out, size, nullptr);
}

// Manual cleanup function to call when done
void cleanup_reduce_maxZ_gpu()
{
  if (maxZ_temp_storage != nullptr) {
    cudaFree(maxZ_temp_storage);
    maxZ_temp_storage = nullptr;
  }
}


// max zero reduction interface
/*
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

  void *batched_reduce_max_v2_args[] = {
      (void *)&d_out,
      (void *)&d_in,
      (void *)&size
  };
  cudaError_t err = cudaLaunchKernel(
      (void*)batched_reduce_max_v2,
      dim3(1, 1, 1),
      dim3(1024, 1, 1),
      (void**)batched_reduce_max_v2_args,
      0,
      stream
  );
}
*/

double reduce_maxZ_to_scalar_gpu(const double *__restrict__ d_in, int size, cudaStream_t stream)
{
  thrust::device_ptr<const double> d_ptr = thrust::device_pointer_cast(d_in);
  double maxval = thrust::reduce(d_ptr, d_ptr + size, 0.0, thrust::maximum<double>());
  return maxval;
}

// sum reduction interface
/*
void reduce_sum_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, cudaStream_t stream)
{
  void *batched_reduce_sum_v2_args[] = {
      (void *)&d_out,
      (void *)&d_in,
      (void *)&size
  };
  cudaError_t err = cudaLaunchKernel(
      (void*)batched_reduce_sum_v2,
      dim3(1, 1, 1),
      dim3(1024, 1, 1),
      (void**)batched_reduce_sum_v2_args,
      0,
      stream
  );
}
*/

static void* sum_temp_storage = nullptr;
void reduce_sum_to_address_gpu(const double *__restrict__ d_in,
                                 double* __restrict__ d_out,
                                 int size,
                                 cudaStream_t stream)
{
  // Static variables to persist across calls
  static size_t temp_storage_bytes = 0;
  static int last_size = -1;

  // Only allocate once, or if size has changed
  if (sum_temp_storage == nullptr || size != last_size) {
    if (sum_temp_storage != nullptr) {
      cudaFree(sum_temp_storage);
      sum_temp_storage = nullptr;
    }
    temp_storage_bytes = 0;
    cub::DeviceReduce::Max(nullptr, temp_storage_bytes, d_in, d_out, size, nullptr);
    if (temp_storage_bytes != 0) {
      cudaMalloc(&sum_temp_storage, temp_storage_bytes);
    }
    last_size = size;
  }

  // Call the reduction
  cub::DeviceReduce::Max(sum_temp_storage, temp_storage_bytes, d_in, d_out, size, nullptr);
}

// Manual cleanup function to call when done
void cleanup_reduce_sum_gpu()
{
  if (sum_temp_storage != nullptr) {
    cudaFree(sum_temp_storage);
    sum_temp_storage = nullptr;
  }
}


int reduce_sum_to_scalar_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream)
{
  thrust::device_ptr<const int> d_ptr = thrust::device_pointer_cast(d_in);
  int sumval = thrust::reduce(d_ptr, d_ptr + size, 0, thrust::plus<int>());
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


void reduce_segmented_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, int batch_size, cudaStream_t stream)
{
    void *batched_reduce_sum_v2_args[] = {
        (void *)&d_out,
        (void *)&d_in,
        (void *)&size
    };
    constexpr int NUM_WARPS{1024 / 32};

    cudaError_t err = cudaLaunchKernel(
        (void*)batched_reduce_sum_v2,
        dim3(batch_size, 1, 1),
        dim3(1024, 1, 1),
        (void**)batched_reduce_sum_v2_args,
        0,
        nullptr
    );
}