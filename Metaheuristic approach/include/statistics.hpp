#pragma once

#include <limits>
#include <optional>

#include "solution.hpp"
#include "model.hpp"

struct Statistics {
    std::optional<Solution> best_solution;
    double best_fitness;
    double best_time;
    double total_time;
    std::size_t fitness_evaluation_count;
    std::size_t iteration_of_last_improvement;
};

extern Statistics global_statistics;

