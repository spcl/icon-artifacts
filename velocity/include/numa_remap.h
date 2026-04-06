#pragma once

#include <cstddef>
#include <omp.h>

// ---------------------------------------------------------------------------
enum class Distribution { BLOCK_1D, ROW_WISE, COL_WISE };

// ---------------------------------------------------------------------------
// numa_touch — trigger page migration by touching every element from the
// "correct" OMP thread.  With OMP_PROC_BIND=spread + schedule(static),
// each thread's pages migrate to its NUMA node via AutoNUMA.
//
// Array is nlist slices of dim0 × dim1 (C row-major).
//
//   ROW_WISE  (shuffled):   parallel over rows
//   COL_WISE  (unshuffled): parallel over columns
//   BLOCK_1D  (small/flat): parallel over total elements
//
// Call this once before the timed region to warm up placement.
// ---------------------------------------------------------------------------
template <typename T>
void numa_touch(T *arr, size_t dim0, size_t dim1, size_t nlist,
                Distribution dist) {
  const size_t slice = dim0 * dim1;
  const size_t total = nlist * slice;

  switch (dist) {

  case Distribution::ROW_WISE: {
    const size_t nrows = nlist * dim0;
    #pragma omp parallel for schedule(static)
    for (size_t row = 0; row < nrows; ++row) {
      size_t base = row * dim1;
      for (size_t c = 0; c < dim1; ++c)
        arr[base + c] = arr[base + c];
    }
    break;
  }

  case Distribution::COL_WISE: {
    #pragma omp parallel for schedule(static)
    for (size_t c = 0; c < dim1; ++c) {
      for (size_t l = 0; l < nlist; ++l) {
        for (size_t r = 0; r < dim0; ++r) {
          size_t idx = l * slice + r * dim1 + c;
          arr[idx] = arr[idx];
        }
      }
    }
    break;
  }

  case Distribution::BLOCK_1D: {
    #pragma omp parallel for schedule(static)
    for (size_t i = 0; i < total; ++i)
      arr[i] = arr[i];
    break;
  }

  } // switch
}