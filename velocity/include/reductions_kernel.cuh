#pragma once

double reduce_maxZ_gpu(const double *d_in, int size);
int reduce_sum_gpu(const int *d_in, int size);
int reduce_scan_gpu(const int *d_in, int size);

inline double reduce_maxZ_gpu(const double d_in, int size){
    return d_in;
}

inline int reduce_sum_gpu(const int d_in, int size){
    return d_in;
}

inline int reduce_scan_gpu(const int d_in, int size){
    return (d_in > 0) ? 1 : 0;
}