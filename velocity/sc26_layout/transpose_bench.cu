// transpose_bench.cu
//
// 3D tensor transpose benchmark: A[81920, 90, 2] -> B[90, 81920, 2]
// Permutation: [1, 0, 2]
//
// The last dimension (size 2) remains contiguous in both input and output,
// so we treat it as a 2D transpose of (81920, 90) "fat" elements, where
// each element is a float2 (8 bytes). This gives coalesced 8-byte accesses.
//
// Compile:
//   nvcc -O3 transpose_bench.cu -lcutensor -o transpose_bench
//
// Run:
//   ./transpose_bench

#include <cstdio>
#include <cstdlib>
#include <cuda_runtime.h>
#include <cutensor.h>
#include <vector>
#include <functional>

// --------------------------------------------------------------------------
//  Error checking
// --------------------------------------------------------------------------
#define CUDA_CHECK(x)                                                       \
    do {                                                                     \
        cudaError_t err = (x);                                               \
        if (err != cudaSuccess) {                                            \
            fprintf(stderr, "CUDA error %s:%d: %s\n", __FILE__, __LINE__,    \
                    cudaGetErrorString(err));                                 \
            exit(1);                                                         \
        }                                                                    \
    } while (0)

#define CUTENSOR_CHECK(x)                                                   \
    do {                                                                     \
        cutensorStatus_t err = (x);                                          \
        if (err != CUTENSOR_STATUS_SUCCESS) {                                \
            fprintf(stderr, "cuTENSOR error %s:%d: %s\n", __FILE__,          \
                    __LINE__, cutensorGetErrorString(err));                   \
            exit(1);                                                         \
        }                                                                    \
    } while (0)

// --------------------------------------------------------------------------
//  Dimensions
// --------------------------------------------------------------------------
constexpr int D0 = 81920;  // rows (input dim 0)
constexpr int D1 = 90;     // cols (input dim 1)
constexpr int D2 = 2;      // innermost (stays contiguous)
constexpr size_t NELEMS = (size_t)D0 * D1 * D2;
constexpr size_t NBYTES = NELEMS * sizeof(float);

// --------------------------------------------------------------------------
//  Custom transpose kernel
// --------------------------------------------------------------------------
// Treats A as A_2d[D0][D1] of float2 elements (since D2=2 and float2 = 8B).
// Transposes to B_2d[D1][D0] of float2 with shared-memory tiling.

constexpr int TILE = 32;

__global__ void transpose_102(const float2* __restrict__ A,
                              float2* __restrict__ B,
                              int M, int N)
{
    // M = D0 = 81920 (rows), N = D1 = 90 (cols)
    // A is M x N of float2, B is N x M of float2
    //
    // +1 padding avoids shared memory bank conflicts on column access.
    __shared__ float2 tile[TILE][TILE + 1];

    // --- Coalesced READ from A[row][col] ---
    int col = blockIdx.x * TILE + threadIdx.x;
    int row = blockIdx.y * TILE + threadIdx.y;

    if (row < M && col < N)
        tile[threadIdx.y][threadIdx.x] = A[row * N + col];

    __syncthreads();

    // --- Coalesced WRITE to B[col'][row'] ---
    // Swap block indices so threadIdx.x is again the contiguous dimension
    col = blockIdx.y * TILE + threadIdx.x;
    row = blockIdx.x * TILE + threadIdx.y;

    if (row < N && col < M)
        B[row * M + col] = tile[threadIdx.x][threadIdx.y];
}

// --------------------------------------------------------------------------
//  cuTENSOR v2 permute
// --------------------------------------------------------------------------
void cutensor_permute(cutensorHandle_t handle,
                      const float* d_A, float* d_B,
                      cudaStream_t stream)
{
    // A[D0, D1, D2] -> B[D1, D0, D2]  via perm [1, 0, 2]
    const int32_t modesA[] = {0, 1, 2};
    const int32_t modesB[] = {1, 0, 2};
    const int64_t extentA[] = {D0, D1, D2};
    const int64_t extentB[] = {D1, D0, D2};
    // Row-major strides
    const int64_t stridesA[] = {D1 * D2, D2, 1};
    const int64_t stridesB[] = {D0 * D2, D2, 1};

    cutensorTensorDescriptor_t descA, descB;
    CUTENSOR_CHECK(cutensorCreateTensorDescriptor(
        handle, &descA, 3, extentA, stridesA, CUTENSOR_R_32F, 256));
    CUTENSOR_CHECK(cutensorCreateTensorDescriptor(
        handle, &descB, 3, extentB, stridesB, CUTENSOR_R_32F, 256));

    cutensorOperationDescriptor_t opDesc;
    CUTENSOR_CHECK(cutensorCreatePermutation(
        handle, &opDesc,
        descA, modesA, CUTENSOR_OP_IDENTITY,
        descB, modesB,
        CUTENSOR_COMPUTE_DESC_32F));

    cutensorPlanPreference_t planPref;
    CUTENSOR_CHECK(cutensorCreatePlanPreference(
        handle, &planPref, CUTENSOR_ALGO_DEFAULT, CUTENSOR_JIT_MODE_NONE));

    cutensorPlan_t plan;
    CUTENSOR_CHECK(cutensorCreatePlan(handle, &plan, opDesc, planPref, 0));

    float alpha = 1.0f;

    CUTENSOR_CHECK(cutensorPermute(
        handle, plan, (const void*)&alpha, d_A, d_B, stream));

    cutensorDestroyPlan(plan);
    cutensorDestroyPlanPreference(planPref);
    cutensorDestroyOperationDescriptor(opDesc);
    cutensorDestroyTensorDescriptor(descB);
    cutensorDestroyTensorDescriptor(descA);
}

// --------------------------------------------------------------------------
//  cuTENSOR permute with pre-built plan (avoids plan creation overhead)
// --------------------------------------------------------------------------
struct CuTensorPermutePlan {
    cutensorPlan_t plan;

    CuTensorPermutePlan(cutensorHandle_t handle) {
        const int32_t modesA[] = {0, 1, 2};
        const int32_t modesB[] = {1, 0, 2};
        const int64_t extentA[] = {D0, D1, D2};
        const int64_t extentB[] = {D1, D0, D2};
        const int64_t stridesA[] = {D1 * D2, D2, 1};
        const int64_t stridesB[] = {D0 * D2, D2, 1};

        cutensorTensorDescriptor_t descA, descB;
        CUTENSOR_CHECK(cutensorCreateTensorDescriptor(
            handle, &descA, 3, extentA, stridesA, CUTENSOR_R_32F, 256));
        CUTENSOR_CHECK(cutensorCreateTensorDescriptor(
            handle, &descB, 3, extentB, stridesB, CUTENSOR_R_32F, 256));

        cutensorOperationDescriptor_t opDesc;
        CUTENSOR_CHECK(cutensorCreatePermutation(
            handle, &opDesc,
            descA, modesA, CUTENSOR_OP_IDENTITY,
            descB, modesB,
            CUTENSOR_COMPUTE_DESC_32F));

        cutensorPlanPreference_t planPref;
        CUTENSOR_CHECK(cutensorCreatePlanPreference(
            handle, &planPref, CUTENSOR_ALGO_DEFAULT, CUTENSOR_JIT_MODE_NONE));

        CUTENSOR_CHECK(cutensorCreatePlan(handle, &plan, opDesc, planPref, 0));

        cutensorDestroyPlanPreference(planPref);
        cutensorDestroyOperationDescriptor(opDesc);
        cutensorDestroyTensorDescriptor(descB);
        cutensorDestroyTensorDescriptor(descA);
    }

    void execute(cutensorHandle_t handle,
                 const float* d_A, float* d_B,
                 cudaStream_t stream) {
        float alpha = 1.0f;
        CUTENSOR_CHECK(cutensorPermute(
            handle, plan, (const void*)&alpha, d_A, d_B, stream));
    }

    ~CuTensorPermutePlan() {
        cutensorDestroyPlan(plan);
    }
};

// --------------------------------------------------------------------------
//  Validation
// --------------------------------------------------------------------------
bool validate(const float* h_A, const float* h_B)
{
    // B[d1][d0][d2] == A[d0][d1][d2]
    for (int d0 = 0; d0 < D0; d0++) {
        for (int d1 = 0; d1 < D1; d1++) {
            for (int d2 = 0; d2 < D2; d2++) {
                float expected = h_A[(size_t)d0 * D1 * D2 + d1 * D2 + d2];
                float got      = h_B[(size_t)d1 * D0 * D2 + d0 * D2 + d2];
                if (expected != got) {
                    fprintf(stderr, "Mismatch at [%d,%d,%d]: expected %f got %f\n",
                            d0, d1, d2, expected, got);
                    return false;
                }
            }
        }
    }
    return true;
}

// --------------------------------------------------------------------------
//  Timing helper
// --------------------------------------------------------------------------
float benchmark_ms(std::function<void()> fn, int warmup, int reps)
{
    for (int i = 0; i < warmup; i++) fn();
    CUDA_CHECK(cudaDeviceSynchronize());

    cudaEvent_t start, stop;
    CUDA_CHECK(cudaEventCreate(&start));
    CUDA_CHECK(cudaEventCreate(&stop));

    CUDA_CHECK(cudaEventRecord(start));
    for (int i = 0; i < reps; i++) fn();
    CUDA_CHECK(cudaEventRecord(stop));
    CUDA_CHECK(cudaEventSynchronize(stop));

    float ms = 0;
    CUDA_CHECK(cudaEventElapsedTime(&ms, start, stop));

    CUDA_CHECK(cudaEventDestroy(start));
    CUDA_CHECK(cudaEventDestroy(stop));

    return ms / reps;
}

// --------------------------------------------------------------------------
//  Main
// --------------------------------------------------------------------------
int main()
{
    printf("Tensor transpose benchmark: [%d, %d, %d] -> [%d, %d, %d]\n",
           D0, D1, D2, D1, D0, D2);
    printf("Permutation: [1, 0, 2]\n");
    printf("Data: %.1f MB of float32\n\n", NBYTES / (1024.0 * 1024.0));

    // --- Allocate host ---
    std::vector<float> h_A(NELEMS), h_B(NELEMS);
    srand(42);
    for (size_t i = 0; i < NELEMS; i++)
        h_A[i] = (float)(rand() % 1000) / 10.0f;

    // --- Allocate device ---
    float *d_A, *d_B;
    CUDA_CHECK(cudaMalloc(&d_A, NBYTES));
    CUDA_CHECK(cudaMalloc(&d_B, NBYTES));
    CUDA_CHECK(cudaMemcpy(d_A, h_A.data(), NBYTES, cudaMemcpyHostToDevice));

    cudaStream_t stream;
    CUDA_CHECK(cudaStreamCreate(&stream));

    constexpr int WARMUP = 10;
    constexpr int REPS = 250;

    // =====================================================================
    //  Custom kernel (float2 tiled transpose)
    // =====================================================================
    {
        // Treat as 2D: M=D0, N=D1, elements are float2
        int M = D0, N = D1;
        dim3 block(TILE, TILE);
        dim3 grid((N + TILE - 1) / TILE, (M + TILE - 1) / TILE);

        auto fn = [&]() {
            transpose_102<<<grid, block, 0, stream>>>(
                reinterpret_cast<const float2*>(d_A),
                reinterpret_cast<float2*>(d_B),
                M, N);
        };

        float ms = benchmark_ms(fn, WARMUP, REPS);

        // Validate
        CUDA_CHECK(cudaMemcpy(h_B.data(), d_B, NBYTES, cudaMemcpyDeviceToHost));
        bool ok = validate(h_A.data(), h_B.data());

        double bw = 2.0 * NBYTES / (ms / 1000.0) / 1e9;  // read + write
        printf("Custom kernel:           %8.3f ms  %7.1f GB/s  %s\n",
               ms, bw, ok ? "PASS" : "FAIL");
    }

    // =====================================================================
    //  cuTENSOR (with plan creation each call)
    // =====================================================================
    {
        cutensorHandle_t handle;
        CUTENSOR_CHECK(cutensorCreate(&handle));

        auto fn = [&]() {
            CUDA_CHECK(cudaMemset(d_B, 0, NBYTES));
            cutensor_permute(handle, d_A, d_B, stream);
        };

        float ms = benchmark_ms(fn, WARMUP, REPS);

        CUDA_CHECK(cudaMemcpy(h_B.data(), d_B, NBYTES, cudaMemcpyDeviceToHost));
        bool ok = validate(h_A.data(), h_B.data());

        double bw = 2.0 * NBYTES / (ms / 1000.0) / 1e9;
        printf("cuTENSOR (+ plan each):  %8.3f ms  %7.1f GB/s  %s\n",
               ms, bw, ok ? "PASS" : "FAIL");

        CUTENSOR_CHECK(cutensorDestroy(handle));
    }

    // =====================================================================
    //  cuTENSOR (pre-built plan, kernel-only timing)
    // =====================================================================
    {
        cutensorHandle_t handle;
        CUTENSOR_CHECK(cutensorCreate(&handle));

        CuTensorPermutePlan prebuilt(handle);

        auto fn = [&]() {
            prebuilt.execute(handle, d_A, d_B, stream);
        };

        float ms = benchmark_ms(fn, WARMUP, REPS);

        CUDA_CHECK(cudaMemcpy(h_B.data(), d_B, NBYTES, cudaMemcpyDeviceToHost));
        bool ok = validate(h_A.data(), h_B.data());

        double bw = 2.0 * NBYTES / (ms / 1000.0) / 1e9;
        printf("cuTENSOR (pre-built):    %8.3f ms  %7.1f GB/s  %s\n",
               ms, bw, ok ? "PASS" : "FAIL");

        CUTENSOR_CHECK(cutensorDestroy(handle));
    }

    // --- Cleanup ---
    CUDA_CHECK(cudaStreamDestroy(stream));
    CUDA_CHECK(cudaFree(d_A));
    CUDA_CHECK(cudaFree(d_B));

    return 0;
}
