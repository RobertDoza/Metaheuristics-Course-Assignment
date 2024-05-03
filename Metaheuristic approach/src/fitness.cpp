#include "fitness.hpp"

bool Model::created = false;
Model Model::model;

Model& Model::get_model() {
	if (!created) {
		throw std::logic_error("Model not created");
	}
	return model;
}

double Model::calculate_fitness(const Solution&) const {
	// TODO
	return 3.14;
}

Model::Model() {}

Model::Model(int i, int j, int t, double s, int p, const std::vector<std::vector<double>>& pop, const std::vector<std::vector<double>>& dist)
	:_i(i), _j(j), _t(t), _s(s), _p(p), _population_matrix(pop), _distance_matrix(dist)
{}
