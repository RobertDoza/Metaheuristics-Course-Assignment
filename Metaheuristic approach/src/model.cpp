#include "model.hpp"
#include "input_reader.hpp"

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

double Model::calculate_fitness(const Solution&) const {
	// TODO
	return 3.14;
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
