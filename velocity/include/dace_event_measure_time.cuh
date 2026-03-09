#pragma once

#include <iostream>
#include <cuda_runtime.h>

static void dace_event_measure_time(const char *tag = nullptr)
{
  static int timer_call_count = 0;
  static cudaEvent_t start_event = nullptr;

  if (timer_call_count % 2 == 1)
  {
    cudaEvent_t stop_event;
    cudaEventCreate(&stop_event);
    cudaEventRecord(stop_event);
    cudaEventSynchronize(stop_event);

    float ms = 0.0f;
    cudaEventElapsedTime(&ms, start_event, stop_event);
    std::cout << "Timer " << tag << " took " << static_cast<unsigned long int>(ms * 1000.0f) << " us" << std::endl;

    cudaEventDestroy(stop_event);
    cudaEventDestroy(start_event);
    start_event = nullptr;
  } else {
    cudaDeviceSynchronize();
    cudaEventCreate(&start_event);
    cudaEventRecord(start_event);
  }

  timer_call_count++;
}