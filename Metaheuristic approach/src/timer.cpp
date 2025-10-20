#include <stdexcept>

#include "timer.hpp"

Timer global_timer;

Timer::Timer()
    :_started(false)
{}

void Timer::start(std::size_t num_seconds) {
    if (_started) {
        throw std::runtime_error("Timer already started!");
    }

    _start_time = std::chrono::steady_clock::now();
    _time_limit = std::chrono::seconds(num_seconds);
    _started = true;
}

bool Timer::expired() const {
    if (!_started) {
        throw std::runtime_error("Timer not started yet!");
    }
    return std::chrono::steady_clock::now() - _start_time >= _time_limit;
}

