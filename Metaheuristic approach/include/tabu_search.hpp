#pragma once

#include "solution.hpp"

class TabuSearch {
	public:
		static Solution tabu_search();
	private:
		static Solution get_local_best_solution(const Solution&);
		static bool stopping_condition_met();
};
