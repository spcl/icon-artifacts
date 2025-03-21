#include <omp.h>

// max zero reduction interface
double reduce_maxZ(const double *d_in, int size)
{
  double max_val = 0;
#pragma omp parallel for reduction(max : max_val)
  for (int i = 0; i < size; i++)
    max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
  return max_val;
}

// sum reduction interface
int reduce_sum(const int *d_in, int size)
{
  int sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; i++)
    sum += d_in[i];
  return sum;
}

// scan reduction interface
double reduce_scan(const int *d_in, int size)
{
  return (double)(reduce_sum(d_in, size) > 0);
}
