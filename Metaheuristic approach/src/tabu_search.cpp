#include <iostream>
#include <limits>

#include "tabu_search.hpp"
#include "model.hpp"
#include "tabu_list.hpp"
#include "neighbor_iterator.hpp"

#define MAX_ITER 20
// #define TS_LOG

const double negative_infinity = - std::numeric_limits<double>::infinity();

TabuSearchResult TabuSearcher::tabu_search() {
	TabuSearcher& tabu_searcher = get();
	tabu_searcher.start();
	return {tabu_searcher._best_solution, tabu_searcher._best_fitness};
}

TabuSearcher::TabuSearcher()
	:_best_solution(Model::generate_empty_solution()), _best_fitness(negative_infinity)
{}

TabuSearcher& TabuSearcher::get() {
    static TabuSearcher tabu_searcher;
	return tabu_searcher;
}

void TabuSearcher::start() {
	Solution initial_solution = Model::generate_random_solution();
	
	_best_solution = initial_solution;
	_best_fitness = Model::calculate_fitness(_best_solution);
	
	Solution current_solution = initial_solution;

	#ifdef TS_LOG
	std::cout << "Initial solution:" << std::endl;
	std::cout << _best_solution << std::endl;
	std::cout << "obj: " << _best_fitness << std::endl;
	#endif

	TabuList::clear();
	_iteration_counter = 0;

	while (!stopping_condition_met()) {
		#ifdef TS_LOG
		std::cout << "Iteration: " << (_iteration_counter + 1) << std::endl;
		#endif

		std::optional<Solution> local_search_result = get_local_best_solution(current_solution);

		Solution local_best_solution = Model::generate_empty_solution();

		if (local_search_result.has_value()) {
			local_best_solution = local_search_result.value();
		} else {
			// TODO: handle case when local search didn't find any solutions
		}

		double fitness = Model::calculate_fitness(local_best_solution);

		#ifdef TS_LOG
		std::cout << "Local best solution: " << local_best_solution << std::endl;
		std::cout << "Obj: " << fitness << std::endl;
		#endif

		if (fitness > _best_fitness) {
			_best_solution = local_best_solution;
			_best_fitness = fitness;
		}

		TabuList::add(local_best_solution);

		#ifdef TS_LOG
		std::cout << "Tabu list: " << TabuList::to_string() << std::endl;
		#endif

		// TODO: update tabu list

		current_solution = local_best_solution;

		#ifdef TS_LOG
		std::cout << std::endl;
		#endif

		_iteration_counter++;
	}
}

bool TabuSearcher::stopping_condition_met() const {
	if (_iteration_counter == MAX_ITER) {
		return true;
	}
	
	return false;
}

std::optional<Solution> TabuSearcher::get_local_best_solution(const Solution& solution) {
	Solution local_best_solution = Model::generate_empty_solution();
	double local_best_fitness = negative_infinity;
	bool found_improvement = false;

	int counter = 0;
	auto neighbor_iterator = N2NeighborIterator(solution);

	while (true) {
		counter++;

		std::optional<Solution> next = neighbor_iterator.get_next();

		if (!next) {
			break;
		}

		auto neighbor = next.value();

		#ifdef TS_LOG
		std::cout << counter << ")" << neighbor << std::endl;
		#endif

		double fitness = Model::calculate_fitness(neighbor);
		
		if (TabuList::contains(neighbor)) {
			if (fitness > _best_fitness) {
				local_best_solution = neighbor;
				local_best_fitness = fitness;
				found_improvement = true;
				
				TabuList::remove(neighbor);
				
				#ifdef TS_LOG
				std::cout << "Aspiration criterion met!" << std::endl;
				#endif

				continue;
			}

			#ifdef TS_LOG
			std::cout << "Skipping neighbor " /*<< neighbor*/ << std::endl;
			#endif

			continue;
		}

		if (fitness > local_best_fitness) {
			local_best_solution = neighbor;
			local_best_fitness = fitness;
			found_improvement = true;
		}
	}

	if (found_improvement) {
		return local_best_solution;
	}
	
	return std::nullopt;
}
