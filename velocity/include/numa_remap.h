#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <numa.h>
#include <sched.h>
#include <sys/mman.h>
#include <thread>
#include <vector>

// ---------------------------------------------------------------------------
// Allocation primitives
// ---------------------------------------------------------------------------
template <typename T> static T *numa_alloc_unfaulted(size_t count) {
  size_t bytes = count * sizeof(T);
  void *p = mmap(nullptr, bytes, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
  if (p == MAP_FAILED) { perror("mmap"); std::abort(); }
  madvise(p, bytes, MADV_HUGEPAGE);
  return static_cast<T *>(p);
}

template <typename T> static void numa_dealloc(T *p, size_t count) {
  if (p) munmap(p, count * sizeof(T));
}

// ---------------------------------------------------------------------------
enum class Distribution { BLOCK_1D, ROW_WISE, COL_WISE };

// ---------------------------------------------------------------------------
static cpu_set_t pin_to_numa_node(int node) {
  cpu_set_t old;
  CPU_ZERO(&old);
  sched_getaffinity(0, sizeof(old), &old);

  struct bitmask *cpus = numa_allocate_cpumask();
  numa_node_to_cpus(node, cpus);

  cpu_set_t ns;
  CPU_ZERO(&ns);
  for (unsigned c = 0; c < numa_num_possible_cpus(); ++c)
    if (numa_bitmask_isbitset(cpus, c)) CPU_SET(c, &ns);
  numa_free_cpumask(cpus);

  sched_setaffinity(0, sizeof(ns), &ns);
  return old;
}

static void restore_affinity(const cpu_set_t &s) {
  sched_setaffinity(0, sizeof(s), &s);
}

// ---------------------------------------------------------------------------
static std::vector<std::pair<size_t, size_t>>
owned_ranges(int node, int num_nodes, size_t dim0, size_t dim1,
             Distribution dist) {

  std::vector<std::pair<size_t, size_t>> ranges;

  auto block = [](size_t total, int n, int i) -> std::pair<size_t, size_t> {
    size_t chunk = total / n;
    size_t rem   = total % n;
    size_t start = i * chunk + std::min<size_t>(i, rem);
    size_t count = chunk + (static_cast<size_t>(i) < rem ? 1 : 0);
    return {start, count};
  };

  switch (dist) {
  case Distribution::BLOCK_1D: {
    auto [s, c] = block(dim0 * dim1, num_nodes, node);
    if (c) ranges.emplace_back(s, c);
    break;
  }
  case Distribution::ROW_WISE: {
    auto [rs, rc] = block(dim0, num_nodes, node);
    if (rc) ranges.emplace_back(rs * dim1, rc * dim1);
    break;
  }
  case Distribution::COL_WISE: {
    auto [cs, cc] = block(dim1, num_nodes, node);
    if (cc)
      for (size_t r = 0; r < dim0; ++r)
        ranges.emplace_back(r * dim1 + cs, cc);
    break;
  }
  }
  return ranges;
}

// ---------------------------------------------------------------------------
// numa_remap
//
//   Allocates a NUMA-distributed copy of the old array via mmap, copies data
//   with first-touch placement, frees the old array (delete[]), and returns
//   the new pointer.
//
//   Usage:  arr = numa_remap(arr, dim0, dim1, nlist, num_nodes, dist);
// ---------------------------------------------------------------------------
template <typename T>
T* numa_remap(T *old_ptr,
              size_t dim0, size_t dim1, size_t nlist,
              int num_nodes, Distribution dist) {

  const size_t slice  = dim0 * dim1;
  const size_t total  = nlist * slice;
  T           *dst    = numa_alloc_unfaulted<T>(total);

  std::vector<std::thread> threads;
  threads.reserve(num_nodes);

  for (int node = 0; node < num_nodes; ++node) {
    threads.emplace_back([&, node, old_ptr]() {
      cpu_set_t old = pin_to_numa_node(node);

      auto ranges = owned_ranges(node, num_nodes, dim0, dim1, dist);
      for (size_t l = 0; l < nlist; ++l) {
        size_t base = l * slice;
        for (auto &[off, cnt] : ranges) {
          std::memcpy(dst + base + off, old_ptr + base + off, cnt * sizeof(T));
        }
      }

      restore_affinity(old);
    });
  }
  for (auto &t : threads) t.join();

  delete[] old_ptr;
  return dst;
}

// ---------------------------------------------------------------------------
// numa_unmap
//
//   Deallocates an mmap'd array.  Caller sets pointer to nullptr after.
//   Usage:  numa_unmap(arr, dim0, dim1, nlist);  arr = nullptr;
// ---------------------------------------------------------------------------
template <typename T>
void numa_unmap(T *ptr, size_t dim0, size_t dim1, size_t nlist) {
  numa_dealloc(ptr, nlist * dim0 * dim1);
}