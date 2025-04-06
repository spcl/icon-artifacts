#pragma once

void reduce_maxZ_to_address_gpu(const double *d_in, double* d_out, int size);
void reduce_sum_to_address_gpu(const int *d_in, int* d_out, int size);

double reduce_maxZ_to_scalar_gpu(const double *d_in, int size);
int reduce_sum_to_scalar_gpu(const int *d_in, int size);

int reduce_scan_gpu(const int *d_in, int size);
