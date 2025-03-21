#include <cuda_runtime.h>

////////////////////////
// Device functions
////////////////////////


// max zero reduction interface
__device__ double reduce_maxZ_gpu(const double *d_in, int size) {
  double max_val = 0;
  for (int i = 0; i < size; i++)
    max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
  return max_val;
}

// sum reduction interface
__device__ int reduce_sum_gpu(const int *d_in, int size) {
  int sum = 0.0;
  for (int i = 0; i < size; i++)
    sum += d_in[i];
  return sum;
}

// scan reduction interface
__device__ double reduce_scan_gpu(const int *d_in, int size)
{
  return (double)(reduce_sum_gpu(d_in, size) > 0);
}
