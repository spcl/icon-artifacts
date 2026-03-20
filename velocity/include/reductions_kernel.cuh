#pragma once

#include <cuda_runtime.h>
#include <cstdint> 

void reduce_maxZ_to_address_gpu(const double *__restrict__ d_in, double* __restrict__ d_out, int size, cudaStream_t stream);
void reduce_sum_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, cudaStream_t stream);

double reduce_maxZ_to_scalar_gpu(const double *__restrict__ d_in, int size, cudaStream_t stream);
int reduce_sum_to_scalar_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream);

int reduce_scan_gpu(int d_in, int size, cudaStream_t stream);
int reduce_scan_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream);

void cleanup_reduce_sum_gpu();
void cleanup_reduce_maxZ_gpu();

void reduce_scan_first_dim(const uint8_t* __restrict__ arr,
                                  uint8_t* __restrict__ out,
                                  int start, int end, int D, int N);
void reduce_scan_last_dim(const uint8_t* __restrict__ arr,
                                 uint8_t* __restrict__ out,
                                 int start, int end, int D, int N);

void reduce_scan_first_dim(const int* __restrict__ arr,
                                  int* __restrict__ out,
                                  int start, int end, int D, int N);
void reduce_scan_last_dim(const int* __restrict__ arr,
                                 int* __restrict__ out,
                                 int start, int end, int D, int N);