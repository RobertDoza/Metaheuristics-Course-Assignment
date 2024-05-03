#pragma once

#include <vector>

#include "solution.hpp"

class Model {
	public:
		static Model& get_model();
		double calculate_fitness(const Solution&) const;
	private:
		static Model model;
		static bool created;
		
		Model();
		Model(int, int, int, double, int, const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		
		int _i;
		int _j;
		int _t;
		double _s;
		int _p;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _distance_matrix;
};
