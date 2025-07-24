import dace


"""
#include <cuda_runtime.h>
#include <cstdio>

static cudaEvent_t& get_start_event() {
    static cudaEvent_t start_event;
    static bool initialized = false;
    if (!initialized) {
        cudaEventCreate(&start_event);
        initialized = true;
    }
    return start_event;
}

static cudaEvent_t& get_stop_event() {
    static cudaEvent_t stop_event;
    static bool initialized = false;
    if (!initialized) {
        cudaEventCreate(&stop_event);
        initialized = true;
    }
    return stop_event;
}

static void dace_timer_start() {
    cudaEventRecord(get_start_event());
}

static void dace_timer_stop(const char* label) {
    cudaEventRecord(get_stop_event());
    cudaEventSynchronize(get_stop_event());

    float milliseconds = 0.0f;
    cudaEventElapsedTime(&milliseconds, get_start_event(), get_stop_event());

    printf("[CUDA TIMING] %s: %.5f us\n", label, milliseconds * 1000);
}
"""

def create_profile_sdfg(sdfg: dace.SDFG):
    pass