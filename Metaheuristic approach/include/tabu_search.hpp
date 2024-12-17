#pragma once

#include <optional>

#include "solution.hpp"
#include "movement.hpp"

struct TabuSearchResult {
	Solution solution;
	double fitness;
};

struct LocalSearchResult {
	Solution solution;
	Movement movement;
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
		bool stopping_condition_met() const;
		std::optional<LocalSearchResult> get_local_best_solution(const Solution&);
	private:
		Solution _best_solution;
		double _best_fitness;
		unsigned _iteration_counter;
};
