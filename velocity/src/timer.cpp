#include <iostream>
#include <chrono>

void measure_time(const char *tag = nullptr)
{
  static int timer_call_count = 0;
  static std::chrono::high_resolution_clock::time_point timer_last_time = std::chrono::high_resolution_clock::now();

  if (timer_call_count % 2 == 1)
  {
    auto now = std::chrono::high_resolution_clock::now();
    unsigned long int start = std::chrono::duration_cast<std::chrono::microseconds>(timer_last_time.time_since_epoch()).count();
    unsigned long int end = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    std::cout << "Timer " << tag << " took " << (end - start) << " us" << std::endl;
  } else {
    timer_last_time = std::chrono::high_resolution_clock::now();
  }

  timer_call_count++;
}
