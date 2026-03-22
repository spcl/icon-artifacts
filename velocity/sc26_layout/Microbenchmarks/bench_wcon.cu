#include <cuda_runtime.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Problem dimensions
const int NPROMA_1 = 81920;
const int NLEV_1   = 90;

const int NPROMA_2 = 90;
const int NLEV_2   = 81920;

// Number of warm‑up and timed runs
const int WARMUP = 5;
const int RUNS   = 20;

// Block sizes for the two layouts
const int BLOCK_X_A = 256;  // nproma dimension (fast)
const int BLOCK_Y_A = 1;    // nlev dimension (slow)

const int BLOCK_X_B = 96;   // nlev dimension (fast)
const int BLOCK_Y_B = 4;    // nproma dimension (slow)

// ------------------------------------------------------------------------
// Layout A: nproma (fast) × nlev (slow)   (Fortran column‑major)
// Index in flat array: idx = jc + jk * nproma
// ------------------------------------------------------------------------

// Separate kernel 1: copy first nlev levels
__global__ void kernel1_layoutA(double* __restrict__ w, double* __restrict__ z,
                                int nproma, int nlev) {
    int jc = blockIdx.x * blockDim.x + threadIdx.x;
    int jk = blockIdx.y;                         // one jk per block row
    if (jc < nproma && jk < nlev) {
        z[jc + jk * nproma] = w[jc + jk * nproma];
    }
}

// Separate kernel 2: set level nlev+1 to zero
__global__ void kernel2_layoutA(double* __restrict__ w, double* __restrict__ z, int nproma, int nlev) {
    int jc = blockIdx.x * blockDim.x + threadIdx.x;
    if (jc < nproma) {
        z[jc + nlev * nproma] = 0.0;
    }
}

// Fused kernel: copy first nlev levels and set the (nlev+1)-th to zero
__global__ void fused_layoutA(double* __restrict__ w, double* __restrict__ z,
                              int nproma, int nlev) {
    int jc = blockIdx.x * blockDim.x + threadIdx.x;
    int jk = blockIdx.y;                         // goes from 0 to nlev
    if (jc < nproma) {
        int idx = jc + jk * nproma;
        if (jk == nlev) {
            z[idx] = 0.0;
        } else {
            z[idx] = w[jc + jk * nproma];
        }
    }
}

// ------------------------------------------------------------------------
// Layout B: nlev (fast) × nproma (slow)   (C‑like row‑major)
// Index in flat array: idx = jk + jc * nlev
// ------------------------------------------------------------------------

// Separate kernel 1
__global__ void kernel1_layoutB(double* __restrict__ w, double* __restrict__ z,
                                int nproma, int nlev) {
    int jk = blockIdx.x * blockDim.x + threadIdx.x;
    int jc = blockIdx.y * blockDim.y + threadIdx.y;
    if (jk < nlev && jc < nproma) {
        z[jk + jc * nlev] = w[jk + jc * nlev];
    }
}

// Separate kernel 2: set last level (jk == nlev) for each column
__global__ void kernel2_layoutB(double* __restrict__ w, double* __restrict__ z, int nproma, int nlev) {
    int jc = blockIdx.y * blockDim.y + threadIdx.y;   // only y dimension used
    if (jc < nproma && threadIdx.x == 0 && blockIdx.x == 0) {
        // Only one thread per column writes the extra element
        z[jc * (nlev + 1) + nlev] = 0.0;
    }
}

// Fused kernel
__global__ void fused_layoutB(double* __restrict__ w, double* __restrict__ z,
                              int nproma, int nlev) {
    int jk = blockIdx.x * blockDim.x + threadIdx.x;
    int jc = blockIdx.y * blockDim.y + threadIdx.y;
    if (jk < nlev + 1 && jc < nproma) {
        int idx = jk + jc * (nlev + 1);
        if (jk == nlev) {
            z[idx] = 0.0;
        } else {
            int w_idx = jk + jc * nlev;
            z[idx] = w[w_idx];
        }
    }
}

// ------------------------------------------------------------------------
// Helper: compute median of a vector of floats
// ------------------------------------------------------------------------
float median(std::vector<float>& times) {
    std::sort(times.begin(), times.end());
    size_t n = times.size();
    if (n % 2 == 0)
        return (times[n/2 - 1] + times[n/2]) / 2.0f;
    else
        return times[n/2];
}

// ------------------------------------------------------------------------
// Benchmark a kernel: run it RUNS times, collect times, print median
// ------------------------------------------------------------------------
void benchmark(const char* name,
               void (*kernel)(double* __restrict__, double* __restrict__, int, int),
               dim3 grid, dim3 block,
               double* __restrict__ d_w, double* __restrict__ d_z, int nproma, int nlev) {
    // Warm‑up
    for (int i = 0; i < WARMUP; ++i) {
        kernel<<<grid, block>>>(d_w, d_z, nproma, nlev);
    }
    cudaDeviceSynchronize();

    std::vector<float> times(RUNS);
    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    for (int r = 0; r < RUNS; ++r) {
        cudaEventRecord(start, 0);
        kernel<<<grid, block>>>(d_w, d_z, nproma, nlev);
        cudaEventRecord(stop, 0);
        cudaEventSynchronize(stop);
        float ms;
        cudaEventElapsedTime(&ms, start, stop);
        times[r] = ms;
    }

    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    float med = median(times);
    printf("%-25s : %8.3f ms\n", name, med);
}


// ------------------------------------------------------------------------
// Main driver: test both layouts and both problem sizes
// ------------------------------------------------------------------------
int main() {
    cudaSetDevice(0);

    // Two problem sizes
    struct Dims { int nproma; int nlev; };
    Dims dims[2] = { {NPROMA_1, NLEV_1}, {NPROMA_2, NLEV_2} };

    for (int d = 0; d < 2; ++d) {
        int nproma = dims[d].nproma;
        int nlev   = dims[d].nlev;

        printf("\n========== Dimensions: nproma = %d, nlev = %d ==========\n", nproma, nlev);

        // -----------------------------------------------------------------
        // Layout A (nproma fast)
        // -----------------------------------------------------------------
        printf("\n--- Layout A (nproma fast) ---\n");

        size_t size_wA = (size_t)nproma * nlev * sizeof(double);
        std::vector<double> h_wA(nproma * nlev);
        std::mt19937 rng(123);
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        for (int i = 0; i < nproma * nlev; ++i)
            h_wA[i] = dist(rng);

        double *d_wA, *d_zA;
        cudaMalloc(&d_wA, size_wA);
        cudaMalloc(&d_zA, (size_t)nproma * (nlev + 1) * sizeof(double));
        cudaMemcpy(d_wA, h_wA.data(), size_wA, cudaMemcpyHostToDevice);

        // Grids for layout A
        dim3 grid1A  ( (nproma + BLOCK_X_A - 1) / BLOCK_X_A, nlev );
        dim3 grid2A  ( (nproma + BLOCK_X_A - 1) / BLOCK_X_A, 1 );
        dim3 gridFusedA ( (nproma + BLOCK_X_A - 1) / BLOCK_X_A, nlev + 1 );
        dim3 blockA ( BLOCK_X_A, BLOCK_Y_A );

        benchmark("kernel1_layoutA", kernel1_layoutA, grid1A, blockA, d_wA, d_zA, nproma, nlev);
        benchmark("kernel2_layoutA", kernel2_layoutA, grid2A, blockA, d_wA, d_zA, nproma, nlev);
        benchmark("fused_layoutA",   fused_layoutA,   gridFusedA, blockA, d_wA, d_zA, nproma, nlev);

        cudaFree(d_wA);
        cudaFree(d_zA);

        // -----------------------------------------------------------------
        // Layout B (nlev fast)
        // -----------------------------------------------------------------
        printf("\n--- Layout B (nlev fast) ---\n");

        size_t size_wB = (size_t)nproma * nlev * sizeof(double);
        std::vector<double> h_wB(nproma * nlev);
        for (int i = 0; i < nproma * nlev; ++i)
            h_wB[i] = dist(rng);

        double *d_wB, *d_zB;
        cudaMalloc(&d_wB, size_wB);
        cudaMalloc(&d_zB, (size_t)nproma * (nlev + 1) * sizeof(double));
        cudaMemcpy(d_wB, h_wB.data(), size_wB, cudaMemcpyHostToDevice);

        // Grids for layout B
        dim3 grid1B  ( (nlev + BLOCK_X_B - 1) / BLOCK_X_B,
                       (nproma + BLOCK_Y_B - 1) / BLOCK_Y_B );
        dim3 grid2B  ( 1, (nproma + BLOCK_Y_B - 1) / BLOCK_Y_B );   // only y dimension used
        dim3 gridFusedB ( (nlev+1 + BLOCK_X_B - 1) / BLOCK_X_B,
                          (nproma + BLOCK_Y_B - 1) / BLOCK_Y_B );
        dim3 blockB ( BLOCK_X_B, BLOCK_Y_B );

        benchmark("kernel1_layoutB", kernel1_layoutB, grid1B, blockB, d_wB, d_zB, nproma, nlev);
        benchmark("kernel2_layoutB", kernel2_layoutB, grid2B, blockB, d_wB, d_zB, nproma, nlev);
        benchmark("fused_layoutB",   fused_layoutB,   gridFusedB, blockB, d_wB, d_zB, nproma, nlev);

        cudaFree(d_wB);
        cudaFree(d_zB);
    }

    return 0;
}