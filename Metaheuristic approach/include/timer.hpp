#pragma once

#include <chrono>

class Timer {
public:
    Timer();
    void start(std::size_t num_seconds);
    bool expired() const;
private:
    std::chrono::steady_clock::time_point _start_time;
    std::chrono::seconds _time_limit;
    bool _started;
};

extern Timer global_timer;

