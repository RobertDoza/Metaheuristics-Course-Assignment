#include <iostream>
#include <sstream>

#include "statistics.hpp"

Statistics global_statistics;

std::string Statistics::to_string() const {
    std::stringstream buffer;

    buffer << "Best solution: " << global_statistics.best_solution.value() << std::endl;
    buffer << "Best fitness: " << std::to_string(global_statistics.best_fitness) << std::endl;
    buffer << "Best time: " << std::to_string(global_statistics.best_time) << std::endl;
    buffer << "Total time: " << std::to_string(global_statistics.total_time) << std::endl;
    buffer << "Number of evaluations: " << global_statistics.fitness_evaluation_count << std::endl;
    buffer << "Iteration of last improvement: " << global_statistics.iteration_of_last_improvement;

    return buffer.str();
}

std::ostream& operator<<(std::ostream& out, const Statistics& stats) {
    out << stats.to_string();
    return out;
}

