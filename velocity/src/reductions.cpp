#include <omp.h>

////////////////////////////////////////////////////
// We are running on host and the data is on host
////////////////////////////////////////////////////

constexpr int PARALLEL_THRESHOLD = 10000; // Tune as needed

// max zero reduction interface
double reduce_maxZ_to_scalar_cpu(const double *d_in, int size)
{
  double max_val = 0.0;
  if (size > PARALLEL_THRESHOLD) {
#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < size; i++) {
      max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
  } else {
    for (int i = 0; i < size; i++) {
      max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
  }
  return max_val;
}

void reduce_maxZ_to_address_cpu(const double *d_in, double* d_out, int size)
{
  double max_val = 0.0;
  if (size > PARALLEL_THRESHOLD) {
#pragma omp parallel for reduction(max : max_val)
    for (int i = 0; i < size; i++) {
      max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
  } else {
    for (int i = 0; i < size; i++) {
      max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
    }
  }
  d_out[0] = max_val;
}

// sum reduction interface
int reduce_sum_to_scalar_cpu(const int *d_in, int size)
{
  int sum = 0;
  if (size > PARALLEL_THRESHOLD) {
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < size; i++) {
      sum += d_in[i];
    }
  } else {
    for (int i = 0; i < size; i++) {
      sum += d_in[i];
    }
  }
  return sum;
}

void reduce_sum_to_address_cpu(const int *d_in, int* d_out, int size)
{
  int sum = 0;
  if (size > PARALLEL_THRESHOLD) {
#pragma omp parallel for reduction(+ : sum)
    for (int i = 0; i < size; i++) {
      sum += d_in[i];
    }
  } else {
    for (int i = 0; i < size; i++) {
      sum += d_in[i];
    }
  }
  d_out[0] = sum;
}


// scan reduction interface
int reduce_scan_cpu(const int *d_in, int size)
{
  return reduce_sum_to_scalar_cpu(d_in, size) > 0 ? 1 : 0;
}

int reduce_scan_cpu(const int d_in, int size)
{
  return d_in > 0 ? 1 : 0;
}
