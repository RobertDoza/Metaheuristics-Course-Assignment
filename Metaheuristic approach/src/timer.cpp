#include <stdexcept>

#include "timer.hpp"

Timer global_timer;

Timer::Timer()
    :_started(false)
{}

void Timer::start() {
    if (_started) {
        throw std::runtime_error("Timer already started!");
    }

    _start_time = std::chrono::steady_clock::now();
    _started = true;
}

double Timer::elapsed_seconds() const {
    if (!_started) {
        throw std::runtime_error("Timer not started yet!");
    }

    return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - _start_time).count();
}
