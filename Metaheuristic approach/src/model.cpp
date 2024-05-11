#include <sstream>

#include "model.hpp"
#include "input_reader.hpp"
#include "utils.hpp"

bool Model::created = false;
Model Model::model;

Model& Model::get_model() {
	if (!created) {
		throw std::logic_error("Model not created");
	}
	return model;
}

void Model::create_model(const std::string& filename) {
	ModelParameters parameters = InputReader::read_input(filename);
	
	model.set_parameters(parameters);
	
	created = true;
}

Solution Model::generate_solution() {
	Model& model = get_model();
	return Solution(model._j, model._t, model._p);
}

#include <iostream> // TODO remove me
#include <unordered_set>

double Model::calculate_fitness(const Solution& s) const {
	double sum = 0.0;
	
	auto nodes_per_period = s.get_nodes_per_period();
	
	int t = 0;
	for (const auto& period : nodes_per_period) {
		std::unordered_set<int> covered_nodes;
		
		for (const int node : period) {
			std::cout << node << " ";
			
			for (int i = 0; i < _i; i++) {
				if (_distance_matrix[node][i] < _s) {
					covered_nodes.insert(i);
				}
			}
		}
		std::cout << "\n\t";
		for (const int covered_node : covered_nodes) {
			std::cout << "a_{" << covered_node << t << "} ";
			double value = _population_matrix[covered_node][t];
			std::cout << "(" << value << ") ";
			sum += value;
		}
		
		std::cout << "\n";
		t++;
	}
	
	return sum;
}

std::string Model::to_string() const {
	std::stringstream buffer;
	
	buffer << "Parameters:\n";
	buffer << "I = " << _i << ", ";
	buffer << "J = " << _j << ", ";
	buffer << "T = " << _t << ", ";
	buffer << "S = " << _s << ", ";
	buffer << "p = " << _p << "\n";
	
	buffer << "Population matrix:\n";
	buffer << matrix_to_string(_population_matrix);
	
	buffer << "\n";
	
	buffer << "Distance matrix:\n";
	buffer << matrix_to_string(_distance_matrix);
	
	return buffer.str();
}

Model::Model() {}

void Model::set_parameters(const ModelParameters& params) {
	_i = params.i;
	_j = params.j;
	_t = params.t;
	_s = params.s;
	_p = params.p;
	_population_matrix = params.population_matrix;
	_distance_matrix = params.distance_matrix;
}
