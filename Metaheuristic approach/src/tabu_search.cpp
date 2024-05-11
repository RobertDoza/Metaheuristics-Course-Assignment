#include <iostream>
#include <limits>

#include "tabu_search.hpp"
#include "model.hpp"

const double negative_infinity = - std::numeric_limits<double>::infinity();

int iter = 0;

bool stopping_condition();

Solution TabuSearch::tabu_search() {
	// generate initial solution
	Solution s_best = Model::generate_solution();
	Solution s_best_candidate = s_best;
	
	// TODO: remove
	std::cout << s_best << std::endl;
	
	// create tabu list
	std::vector<Solution> tabu_list = {s_best};

	// main loop
	while (!stopping_condition()) {
		// TODO: remove me
		std::cout << iter << "\n";
		iter++;
		
		auto neighborhood = s_best_candidate.get_neighbors();
		
		double best_candidate_fitness = negative_infinity;
		std::cout << best_candidate_fitness << "\n";
		
		auto counter = 0;
		for (const auto& candidate : neighborhood) {
			std::cout << ++counter << ")\t";
			std::cout << candidate << std::endl;
			
			double candidate_fitness = Model::get_model().calculate_fitness(candidate);
			if (candidate_fitness > best_candidate_fitness) {
				// TODO: s_best_candidate = candidate;
				best_candidate_fitness = candidate_fitness;
			}
		}
	}
	
	return s_best;
}

bool stopping_condition() {
	if (iter == 1) {
		return true;
	}
	
	return false;
}
