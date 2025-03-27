#pragma once

double reduce_maxZ_gpu(const double *d_in, int size);
int reduce_sum_gpu(const int *d_in, int size);
double reduce_scan_gpu(const int *d_in, int size);