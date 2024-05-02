#pragma once

#include <vector>

class FitnessCalculator {
	public:
		double calculate_fitness(); // TODO
	private:
		int _i;
		int _j;
		int _t;
		double _s;
		int _p;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _destination_matrix;
};
