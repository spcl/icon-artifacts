#include <cuda_runtime.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>

////////////////////////////////////////////////////
// We are running on host, but the data is on device
////////////////////////////////////////////////////

// max zero reduction interface
double reduce_maxZ_gpu(const double *d_in, int size)
{
  thrust::device_vector<double> data(d_in, d_in + size);
  double const thrust_result = thrust::reduce(thrust::device, data.begin(), data.end(), 0.0, thrust::maximum<double>());
  return thrust_result;
}

// sum reduction interface
int reduce_sum_gpu(const int *d_in, int size)
{
  thrust::device_vector<int> data(d_in, d_in + size);
  int const thrust_result = thrust::reduce(thrust::device, data.begin(), data.end(), 0, thrust::plus<int>());
  return thrust_result;
}

// scan reduction interface
double reduce_scan_gpu(const int *d_in, int size)
{
  return (double)(reduce_sum_gpu(d_in, size) > 0);
}
}
