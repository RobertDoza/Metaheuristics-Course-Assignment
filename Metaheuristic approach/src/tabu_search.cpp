#include <iostream>

#include "tabu_search.hpp"
#include "model.hpp"

int iter = 0;

bool stopping_condition();

Solution TabuSearch::tabu_search() {
	// generate initial solution
	Solution s_best = Model::generate_solution();
	
	// create tabu list
	std::vector<Solution> tabu_list = {s_best};

	// main loop
	while (!stopping_condition()) {
		std::cout << iter << "\n";
		iter++;
	}
	
	return s_best;
}

bool stopping_condition() {
	if (iter == 10) {
		return true;
	}
	
	return false;
}
