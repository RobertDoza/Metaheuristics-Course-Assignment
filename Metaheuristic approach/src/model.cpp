#include <sstream>
#include <unordered_set>

#include "model.hpp"
#include "input_reader.hpp"
#include "utils.hpp"

bool Model::_created = false;
Model Model::_model;

std::string ModelParameters::to_string() const {
    std::stringstream buffer;
	
	buffer << "Parameters:\n";
	buffer << "I = " << num_demand_nodes << ", ";
	buffer << "J = " << num_eligible_sites << ", ";
	buffer << "T = " << num_time_periods << ", ";
	buffer << "S = " << coverage_radius << ", ";
	buffer << "p = " << target_num_sites << "\n";
	
	buffer << "Population matrix:\n";
	buffer << matrix_to_string(population_matrix);
	
	buffer << "\n";
	
	buffer << "Distance matrix:\n";
	buffer << matrix_to_string(distance_matrix);
	
	return buffer.str();
}

void Model::create_model(const std::string& filename) {
	ModelParameters parameters = InputReader::read_input(filename);
	
	_model._set_parameters(parameters);
	
	_created = true;
}

Solution Model::generate_random_solution() {
	Model& model = _get_model();
	return Solution(model._parameters.num_eligible_sites, model._parameters.num_time_periods, model._parameters.target_num_sites);
}

Solution Model::generate_empty_solution() {
	Model& model = _get_model();
    return Solution(model._parameters.num_eligible_sites, model._parameters.num_time_periods);
}

double Model::calculate_fitness(const Solution& solution) {
	return _get_model()._calculate_fitness(solution);
}

std::string Model::to_string() {
    return _get_model()._to_string();
}

int Model::get_target_num_sites() {
    return _get_model()._parameters.target_num_sites;
}

Model& Model::_get_model() {
	if (!_created) {
		throw std::logic_error("Model not created");
	}
	return _model;
}

Model::Model() {}

void Model::_set_parameters(const ModelParameters& params) {
	_parameters = params;
}

double Model::_calculate_fitness(const Solution& s) const {
	double sum = 0.0;
	
	auto nodes_per_period = s.get_nodes_per_period();
	
	int t = 0;
	for (const auto& period : nodes_per_period) {
        for (int i = 0; i < _parameters.num_demand_nodes; i++) {
            for (const int node : period) {
                if (_parameters.distance_matrix[node][i] < _parameters.coverage_radius ) {
                    sum += _parameters.population_matrix[i][t];
                    break;
                }
            }
        }

		t++;
	}
	
	return sum;
}

std::string Model::_to_string() const {
	return _parameters.to_string();
}
