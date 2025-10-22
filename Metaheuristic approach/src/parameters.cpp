#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "parameters.hpp"

MetaParameters meta_parameters;

MetaParameters load_meta_parameters(const std::string& filename) {
    MetaParameters parameters;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open meta parameters file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "max_iterations") {
            iss >> parameters.max_iterations;
        } else if (key == "movement_tabu_list_size") {
            iss >> parameters.movement_tabu_list_size;
        } else if (key == "max_iter_without_improvement") {
            iss >> parameters.max_iter_without_improvement;
        } else if (key == "local_search_parameter_multiplier_1") {
            iss >> parameters.local_search_parameter_multiplier_1;
        } else if (key == "local_search_parameter_multiplier_2") {
            iss >> parameters.local_search_parameter_multiplier_2;
        } else if (key == "aspiration_multiplier") {
            iss >> parameters.aspiration_multiplier;
        } else if (key == "local_search_type") {
            std::string type;
            iss >> type;
            if (type == "FirstImprovement") {
                parameters.local_search_type = MetaParameters::LocalSearchType::FirstImprovement;
            } else if (type == "BestImprovement") {
                parameters.local_search_type = MetaParameters::LocalSearchType::BestImprovement;
            }
            else throw std::runtime_error("Invalid local_search_type in meta_parameters.txt");
        } else {
            throw std::runtime_error("Unknown parameter: " + key);
        }
    }

    return parameters;
}

