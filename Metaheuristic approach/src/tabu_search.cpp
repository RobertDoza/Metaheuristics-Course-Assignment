#include <iostream>

#include "tabu_search.hpp"

int iter = 0;

bool stopping_condition();

Solution TabuSearch::tabu_search(const Solution& s) {
	// TODO
	(void) s;
	
	std::vector<Solution> tabu_list = {s};

	// initialization
	Solution s_best = s;
	
	// main loop
	while (!stopping_condition()) {
		std::cout << iter << "\n";
		iter++;
	}
	
	return s;
}

bool stopping_condition() {
	if (iter == 10) {
		return true;
	}
	
	return false;
}
