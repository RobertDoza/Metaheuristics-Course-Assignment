#pragma once

#include "solution.hpp"

class TabuSearch {
	public:
		static Solution tabu_search();
	private:
		static bool stopping_condition_met();
		static Solution get_local_best_solution(const Solution&);
};
