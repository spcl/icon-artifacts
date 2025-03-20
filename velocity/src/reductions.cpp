#include <omp.h>

// max reduction interface
double reduce_max(const double *d_in, int size)
{
  double max_val = d_in[0];
#pragma omp parallel for reduction(max : max_val)
  for (int i = 1; i < size; i++)
  {
    if (d_in[i] > max_val)
    {
      max_val = d_in[i];
    }
  }
  return max_val;
}

// sum reduction interface
int reduce_sum(const int *d_in, int size)
{
  int sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; i++)
  {
    sum += d_in[i];
  }
  return sum;
}

// scan reduction interface
double reduce_scan(const int *d_in, int size)
{
  return (double)(reduce_sum(d_in, size) > 0);
}
