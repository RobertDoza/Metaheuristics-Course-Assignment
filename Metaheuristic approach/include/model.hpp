#pragma once

#include <vector>

#include "solution.hpp"

struct ModelParameters {
	int i;
	int j;
	int t;
	double s;
	int p;
	std::vector<std::vector<double>> population_matrix;
	std::vector<std::vector<double>> distance_matrix;
};

class Model {
	public:
		static Model& get_model();
		static void create_model(const std::string&);
		static Solution generate_solution();
		
		double calculate_fitness(const Solution&) const;
		std::string to_string() const;
	private:
		static Model model;
		static bool created;
		
		Model();
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		void set_parameters(const ModelParameters&);
		
		int _i;
		int _j;
		int _t;
		double _s;
		int _p;
		std::vector<std::vector<double>> _population_matrix;
		std::vector<std::vector<double>> _distance_matrix;
};
