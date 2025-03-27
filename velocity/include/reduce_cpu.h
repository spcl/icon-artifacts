#pragma once

double reduce_maxZ_cpu(const double *d_in, int size);
double reduce_maxZ_cpu(const double d_in, int size);
int reduce_sum_cpu(const int *d_in, int size);
int reduce_sum_cpu(const int d_in, int size);
double reduce_scan_cpu(const int *d_in, int size);
double reduce_scan_cpu(const int d_in, int size);