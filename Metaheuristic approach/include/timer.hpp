#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void start();
    double elapsed_seconds() const;
private:
    std::chrono::steady_clock::time_point _start_time;
    bool _started;
};

extern Timer global_timer;

