#include <omp.h>

////////////////////////////////////////////////////
// We are running on host and the data is on host
////////////////////////////////////////////////////

// max zero reduction interface
double reduce_maxZ_cpu(const double *d_in, int size)
{
  double max_val = 0;
#pragma omp parallel for reduction(max : max_val)
  for (int i = 0; i < size; i++)
    max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
  return max_val;
}

double reduce_maxZ_cpu(const double d_in, int size)
{
  return (d_in > 0) ? d_in : 0;
}

// sum reduction interface
int reduce_sum_cpu(const int *d_in, int size)
{
  int sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; i++)
    sum += d_in[i];
  return sum;
}

int reduce_sum_cpu(const int d_in, int size)
{
  return d_in;
}

// scan reduction interface
double reduce_scan_cpu(const int *d_in, int size)
{
  return (double)(reduce_sum_cpu(d_in, size) > 0);
}

double reduce_scan_cpu(const int d_in, int size)
{
  return (double)(reduce_sum_cpu(d_in, size) > 0);
}
