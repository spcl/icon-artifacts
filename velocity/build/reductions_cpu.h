#pragma once

void reduce_maxZ_to_address_cpu(const double *d_in, double* d_out, int size);
void reduce_sum_to_address_cpu(const int *d_in, int* d_out, int size);

double reduce_maxZ_to_scalar_cpu(const double *d_in, int size);
int reduce_sum_to_scalar_cpu(const int *d_in, int size);

int reduce_scan_cpu(const int *d_in, int size);
int reduce_scan_cpu(const int d_in, int size);