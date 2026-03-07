#include <cstdio>
#include <cuda_runtime.h>

__global__ void empty_kernel() {}

int main() {
    const int warmup = 100;
    const int iters  = 10000;

    // warmup
    for (int i = 0; i < warmup; i++)
        empty_kernel<<<1, 1>>>();
    cudaDeviceSynchronize();

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start);
    for (int i = 0; i < iters; i++)
        empty_kernel<<<1, 1>>>();
    cudaEventRecord(stop);
    cudaEventSynchronize(stop);

    float ms = 0;
    cudaEventElapsedTime(&ms, start, stop);

    printf("Iterations: %d\n", iters);
    printf("Total:      %.3f ms\n", ms);
    printf("Per launch: %.3f us (%.3f ms)\n", (ms / iters) * 1000.0f, (ms / iters));

    cudaEventDestroy(start);
    cudaEventDestroy(stop);
    return 0;
}