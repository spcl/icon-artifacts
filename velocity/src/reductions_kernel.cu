#include <cuda_runtime.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>

////////////////////////////////////////////////////
// We are running on host, but the data is on device
////////////////////////////////////////////////////

// max zero reduction interface
void reduce_maxZ_to_address_gpu(const double *d_in, double* d_out, int size)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Max(nullptr, temp_storage_bytes, d_in, d_out, size);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Max(d_temp_storage, temp_storage_bytes, d_in, d_out, size);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }

}

double reduce_maxZ_to_scalar_gpu(const double *d_in, int size)
{
  double maxval = thrust::reduce(d_in, d_in + size, 0.0, thrust::maximum<double>());
  return maxval;
}

// sum reduction interface
void reduce_sum_to_address_gpu(const int *d_in, int* d_out, int size)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Sum(nullptr, temp_storage_bytes, d_in, d_out, size);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Sum(d_temp_storage, temp_storage_bytes, d_in, d_out, size);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }
}

int reduce_sum_to_scalar_gpu(const int *d_in, int size)
{
  int maxval = thrust::reduce(d_in, d_in + size, 0, thrust::plus<int>());
  return maxval;
}

// scan reduction interface
int reduce_scan_gpu(const int *d_in, int size)
{
  return (reduce_sum_to_scalar_gpu(d_in, size) > 0)? 1 : 0;
}
