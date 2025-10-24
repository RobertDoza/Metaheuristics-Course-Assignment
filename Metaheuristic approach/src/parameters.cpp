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

std::string MetaParameters::to_string() const {
    std::stringstream buffer;

    buffer << "Max total iterations: " << meta_parameters.max_iterations << std::endl;
	buffer << "Max iterations without improvement: " << meta_parameters.max_iter_without_improvement << std::endl;
	buffer << "Movement tabu list size: " << meta_parameters.movement_tabu_list_size << std::endl;
    buffer << "Number of active nodes in LS: " << meta_parameters.ls_active_nodes << std::endl;
    buffer << "Number of inactive nodes in LS: " << meta_parameters.ls_inactive_nodes;

    return buffer.str();
}

std::ostream& operator<<(std::ostream& out, const MetaParameters& params) {
    out << params.to_string();
    return out;
}

