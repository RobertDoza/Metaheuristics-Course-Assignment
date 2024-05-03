#pragma once

#include <vector>

#include "solution.hpp"

class Model {
	public:
		double calculate_fitness(const Solution&) const;
	private:
		int _i;
		int _j;
		int _t;
		double _s;
		int _p;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _destination_matrix;
};
