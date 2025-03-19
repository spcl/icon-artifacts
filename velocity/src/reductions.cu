#include <cuda_runtime.h>
#include <dace/dace.h>

// source: https://github.com/MaxKotlan/Cuda-Find-Max-Using-Parallel-Reduction/blob/master/Maximum.cu

// max reduction kernel
__global__ void max_reduction_kernel(double* data, int data_size){
  int idx = blockDim.x * blockIdx.x + threadIdx.x;

  __shared__ float sdata[640];
  if (idx < data_size){
      sdata[threadIdx.x] = data[idx];
      __syncthreads();

      for(int stride=blockDim.x/2; stride > 0; stride /= 2) {
          if (threadIdx.x < stride) {
              float lhs = sdata[threadIdx.x];
              float rhs = sdata[threadIdx.x + stride];
              sdata[threadIdx.x] = lhs < rhs ? rhs : lhs;
          }
          __syncthreads();
      }
  }
  if (idx == 0) data[0] = sdata[0];
}


// max reduction interface
DACE_EXPORTED double reduce_max(double *d_in, int size) {
  // Copy input data to device
  double *d_out;
  cudaMalloc(&d_out, size * sizeof(double));
  cudaMemcpy(d_out, d_in, size * sizeof(double), cudaMemcpyDeviceToDevice);

  // Perform reduction
  max_reduction_kernel<<<1, size>>>(d_out, size);

  // Copy result back to host
  double result;
  cudaMemcpy(&result, d_out, sizeof(double), cudaMemcpyDeviceToHost);
  return result;
}

// sum reduction kernel
__global__ void sum_reduction_kernel(double* data, int data_size){
  int idx = blockDim.x * blockIdx.x + threadIdx.x;

  __shared__ float sdata[640];
  if (idx < data_size){
      sdata[threadIdx.x] = data[idx];
      __syncthreads();

      for(int stride=blockDim.x/2; stride > 0; stride /= 2) {
          if (threadIdx.x < stride) {
              sdata[threadIdx.x] += sdata[threadIdx.x + stride];
          }
          __syncthreads();
      }
  }
  if (idx == 0) data[0] = sdata[0];
}

// sum reduction interface
DACE_EXPORTED int reduce_sum(int *d_in, int size) {
  // Copy input data to device
  double *d_out;
  cudaMalloc(&d_out, size * sizeof(double));
  cudaMemcpy(d_out, d_in, size * sizeof(double), cudaMemcpyDeviceToDevice);

  // Perform reduction
  sum_reduction_kernel<<<1, size>>>(d_out, size);

  // Copy result back to host
  double result;
  cudaMemcpy(&result, d_out, sizeof(double), cudaMemcpyDeviceToHost);
  return result;
}
