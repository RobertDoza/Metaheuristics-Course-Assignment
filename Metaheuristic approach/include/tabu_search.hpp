#pragma once

#include "solution.hpp"

struct TabuSearchResult {
	Solution solution;
	double fitness;
};

class TabuSearcher {
	public:
		static TabuSearchResult tabu_search();
	private:
		TabuSearcher();
		TabuSearcher(const TabuSearcher&) = delete;
		TabuSearcher& operator=(const TabuSearcher&) = delete;

		static TabuSearcher& get();

		void start();
		static bool stopping_condition_met();
		Solution get_local_best_solution(const Solution&);
	private:
		Solution _best_solution;
		double _best_fitness;
};
