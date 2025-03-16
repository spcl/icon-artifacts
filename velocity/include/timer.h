#pragma once

#include <iostream>
#include <chrono>

void measure_time(const std::string& message = "") {
    static int call_count = 0;
    static std::chrono::high_resolution_clock::time_point last_time = std::chrono::high_resolution_clock::now();

    call_count++;
    if (call_count % 2 == 0) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = now - last_time;
        std::cout << "Elapsed time: " << elapsed.count() << " seconds";
        if (!message.empty()) {
            std::cout << " - " << message;
        }
        std::cout << std::endl;
    }
    last_time = std::chrono::high_resolution_clock::now();
}