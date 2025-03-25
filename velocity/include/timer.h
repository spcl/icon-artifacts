#include <iostream>
#include <chrono>

int timer_call_count = 0;
std::chrono::high_resolution_clock::time_point timer_last_time = std::chrono::high_resolution_clock::now();

void measure_time(velocity_tendencies_state_t *__state = nullptr, const char *tag = nullptr)
{
  if (timer_call_count % 2 == 1)
  {
    auto now = std::chrono::high_resolution_clock::now();
    unsigned long int start = std::chrono::duration_cast<std::chrono::microseconds>(timer_last_time.time_since_epoch()).count();
    unsigned long int end = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    __state->report.add_completion(tag, "Timer", start, end, 0, 0, 0);
  }

  timer_last_time = std::chrono::high_resolution_clock::now();
  timer_call_count++;
}

void timer_1s_check(velocity_tendencies_state_t *__state = nullptr)
{
  auto begin = std::chrono::high_resolution_clock::now();

  // Sleep for 1 second
  std::this_thread::sleep_for(std::chrono::seconds(1));

  auto now = std::chrono::high_resolution_clock::now();
  unsigned long int start = std::chrono::duration_cast<std::chrono::microseconds>(begin.time_since_epoch()).count();
  unsigned long int end = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
  __state->report.add_completion("timer 1s check", "Timer", start, end, 0, 0, 0);
}
