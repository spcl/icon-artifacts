#pragma once

#include <cstddef>
#include <cstdio>
#include <numaif.h>
#include <unistd.h>

// ---------------------------------------------------------------------------
enum class Distribution { BLOCK_1D, ROW_WISE, COL_WISE };

static constexpr int NUMA_NODES = 4;

// ---------------------------------------------------------------------------
// mbind a byte range to a NUMA node, moving existing pages.
// ---------------------------------------------------------------------------
static void bind_and_move(void *addr, size_t bytes, int node) {
  if (bytes == 0) return;
  const size_t PAGE = sysconf(_SC_PAGESIZE);
  uintptr_t s = reinterpret_cast<uintptr_t>(addr) & ~(PAGE - 1);
  uintptr_t e = (reinterpret_cast<uintptr_t>(addr) + bytes + PAGE - 1) & ~(PAGE - 1);
  if (e <= s) return;

  unsigned long nodemask = 1UL << node;
  if (mbind(reinterpret_cast<void *>(s), e - s,
            MPOL_BIND, &nodemask, sizeof(nodemask) * 8,
            MPOL_MF_MOVE) != 0)
    perror("mbind");
}

// ---------------------------------------------------------------------------
// Block-decompose `total` into `n` chunks, return (start, count) for chunk `i`.
// ---------------------------------------------------------------------------
static inline void block_range(size_t total, int n, int i,
                               size_t &start, size_t &count) {
  size_t chunk = total / n;
  size_t rem   = total % n;
  start = i * chunk + ((size_t)i < rem ? i : rem);
  count = chunk + ((size_t)i < rem ? 1 : 0);
}

// ---------------------------------------------------------------------------
// numa_touch — move pages of an existing new[]-allocated array across 4 NUMA
// nodes using mbind(MPOL_MF_MOVE).  Works with numa_balancing=0.
//
// Array: nlist slices of dim0 × dim1 (C row-major, dim1 contiguous).
//
//   ROW_WISE  (shuffled):   dim0 rows split across 4 nodes, per slice
//   COL_WISE  (unshuffled): dim1 columns split across 4 nodes, per slice
//   BLOCK_1D  (small/flat): total elements split across 4 nodes
// ---------------------------------------------------------------------------
template <typename T>
void numa_touch(T *arr, size_t dim0, size_t dim1, size_t nlist,
                Distribution dist) {
  const size_t slice = dim0 * dim1;
  const size_t total = nlist * slice;

  switch (dist) {

  case Distribution::ROW_WISE: {
    // Split rows across nodes. Each node owns a contiguous row chunk
    // within every slice → contiguous byte range per (node, slice).
    for (int nd = 0; nd < NUMA_NODES; ++nd) {
      size_t rstart, rcount;
      block_range(dim0, NUMA_NODES, nd, rstart, rcount);
      if (rcount == 0) continue;
      for (size_t l = 0; l < nlist; ++l) {
        T *base = arr + l * slice + rstart * dim1;
        bind_and_move(base, rcount * dim1 * sizeof(T), nd);
      }
    }
    break;
  }

  case Distribution::COL_WISE: {
    // Split columns across nodes. Within each row of each slice,
    // each node owns a contiguous column sub-range.
    for (int nd = 0; nd < NUMA_NODES; ++nd) {
      size_t cstart, ccount;
      block_range(dim1, NUMA_NODES, nd, cstart, ccount);
      if (ccount == 0) continue;
      for (size_t l = 0; l < nlist; ++l) {
        for (size_t r = 0; r < dim0; ++r) {
          T *base = arr + l * slice + r * dim1 + cstart;
          bind_and_move(base, ccount * sizeof(T), nd);
        }
      }
    }
    break;
  }

  case Distribution::BLOCK_1D: {
    // Flat split of total elements across nodes.
    for (int nd = 0; nd < NUMA_NODES; ++nd) {
      size_t estart, ecount;
      block_range(total, NUMA_NODES, nd, estart, ecount);
      if (ecount == 0) continue;
      bind_and_move(arr + estart, ecount * sizeof(T), nd);
    }
    break;
  }

  } // switch
}