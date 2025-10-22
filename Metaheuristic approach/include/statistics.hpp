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
    std::size_t num_iterations;
    std::size_t num_evals;
};

extern Statistics global_statistics;

