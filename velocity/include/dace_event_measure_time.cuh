#pragma once
#include <iostream>

#if __HIP_PLATFORM_AMD__ == 1
#include <hip/hip_runtime.h>
#define gpuEvent_t               hipEvent_t
#define gpuEventCreate           hipEventCreate
#define gpuEventRecord           hipEventRecord
#define gpuEventSynchronize      hipEventSynchronize
#define gpuEventElapsedTime      hipEventElapsedTime
#define gpuEventDestroy          hipEventDestroy
#define gpuDeviceSynchronize     hipDeviceSynchronize
#else
#include <cuda_runtime.h>
#define gpuEvent_t               cudaEvent_t
#define gpuEventCreate           cudaEventCreate
#define gpuEventRecord           cudaEventRecord
#define gpuEventSynchronize      cudaEventSynchronize
#define gpuEventElapsedTime      cudaEventElapsedTime
#define gpuEventDestroy          cudaEventDestroy
#define gpuDeviceSynchronize     cudaDeviceSynchronize
#endif

static void dace_event_measure_time(const char *tag = nullptr)
{
    static int timer_call_count = 0;
    static gpuEvent_t start_event = nullptr;

    if (timer_call_count % 2 == 1) {
        gpuEvent_t stop_event;
        gpuEventCreate(&stop_event);
        gpuEventRecord(stop_event);
        gpuEventSynchronize(stop_event);
        float ms = 0.0f;
        gpuEventElapsedTime(&ms, start_event, stop_event);
        std::cout << "Timer " << tag << " took "
                  << static_cast<unsigned long int>(ms * 1000.0f)
                  << " us" << std::endl;
        gpuEventDestroy(stop_event);
        gpuEventDestroy(start_event);
        start_event = nullptr;
    } else {
        gpuDeviceSynchronize();
        gpuEventCreate(&start_event);
        gpuEventRecord(start_event);
    }
    timer_call_count++;
}