#pragma once

#include <vector>

#include "solution.hpp"

struct ModelParameters {
	std::size_t num_demand_nodes;
	std::size_t num_eligible_sites;
	std::size_t num_time_periods;
	double coverage_radius;
	std::size_t target_num_sites;
	std::vector<std::vector<double>> population_matrix;
	std::vector<std::vector<double>> distance_matrix;

	std::string to_string() const;
};

class Model {
	public:
		static void create_model(const std::string&);
		static Solution generate_random_solution();
		static Solution generate_empty_solution();
		static Solution generate_greedy_solution();
		static double calculate_fitness(const Solution&);
		static std::string to_string();
        static ModelParameters get_parameters();
	private:
		static Model& _get_model();
		Model();
		Model(const Model&) = delete;
		Model& operator=(const Model&) = delete;
		void _set_parameters(const ModelParameters&);
		double _calculate_fitness(const Solution&) const;
		std::string _to_string() const;
	private:
		static Model _model;
		static bool _created;
		ModelParameters _parameters;
};
