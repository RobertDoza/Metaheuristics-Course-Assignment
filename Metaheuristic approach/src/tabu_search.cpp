#include <iostream>
#include <limits>

#include "tabu_search.hpp"
#include "model.hpp"
#include "tabu_list.hpp"
#include "neighbor_iterator.hpp"
#include "timer.hpp"
#include "parameters.hpp"

#define TS_LOG

const double negative_infinity = - std::numeric_limits<double>::infinity();

TabuSearchResult TabuSearcher::tabu_search() {
	TabuSearcher& tabu_searcher = get();
	tabu_searcher.start();
	return {tabu_searcher._best_solution, tabu_searcher._best_fitness, tabu_searcher._timeout_reached};
}

TabuSearcher::TabuSearcher()
	:_best_solution(Model::generate_empty_solution()), _best_fitness(negative_infinity), _iteration_counter(0), _timeout_reached(false)
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
	// std::cout << _best_solution << std::endl;
	std::cout << "obj: " << _best_fitness << std::endl;
	std::cout << std::endl;
	#endif

	// TabuList::clear();
	MovementTabuList::clear();
	_iteration_counter = 0;
	unsigned iteration_of_last_improvement;
	unsigned iterations_since_last_improvement = 0;

	while (!stopping_condition_met()) {
        if (global_timer.expired()) {
            _timeout_reached = true;
            break;
        }

		_iteration_counter++;

		#ifdef TS_LOG
		std::cout << "Iteration: " << _iteration_counter << std::endl;
		// std::cout << "Current solution: ";
		// std::cout << current_solution;
		std::cout << std::endl;
		#endif

		std::optional<LocalSearchResult> local_search_result = get_local_best_solution(current_solution, Model::calculate_fitness(current_solution));

		#ifdef TS_LOG
		std::cout << std::endl;
		#endif

		Solution local_best_solution = Model::generate_empty_solution();
		Movement movement_to_local_best;

		if (local_search_result.has_value()) {
			auto result = local_search_result.value();
			local_best_solution = result.solution;
			movement_to_local_best = result.movement;
		} else {
			local_best_solution = Model::generate_random_solution();
			// TODO: movement_to_local_best = ...
			#ifdef TS_LOG
			std::cout << "No local best found. Generating random solution..." << std::endl;
			#endif
		}

		double fitness = Model::calculate_fitness(local_best_solution);

		#ifdef TS_LOG
		// std::cout << "Local best solution: ";
		// std::cout << local_best_solution;
		// std::cout << std::endl;
		// std::cout << "Obj: " << fitness << std::endl;
		#endif

		if (fitness > _best_fitness) {
			_best_solution = local_best_solution;
			_best_fitness = fitness;
			iteration_of_last_improvement = _iteration_counter;
			iterations_since_last_improvement = 0;
			#ifdef TS_LOG
			std::cout << "Found improvement!" << " (" << std::to_string(fitness) << ")" << std::endl;
			#endif
		} else {
			iterations_since_last_improvement++;
		}

		// TabuList::add(local_best_solution);
		MovementTabuList::add(movement_to_local_best);

		#ifdef TS_LOG
		// std::cout << "Tabu list: " << TabuList::to_string() << std::endl;
		// std::cout << "(Movement) tabu list: ";
		std::cout << MovementTabuList::fullness_bar();
		// std::cout << MovementTabuList::to_string();
		std::cout << std::endl;
		#endif

		// TODO: update tabu list

		current_solution = local_best_solution;

		#ifdef TS_LOG
		std::cout << std::endl;
		#endif

		if (iterations_since_last_improvement >= meta_parameters.max_iter_without_improvement) {
			#ifdef TS_LOG
			std::cout << "Iterations since improvement reached " << std::to_string(meta_parameters.max_iter_without_improvement) << " - shaking..." << std::endl;
			#endif
			// current_solution.move_k_facilities(30);
			current_solution = Model::generate_random_solution();
			iterations_since_last_improvement = 0;
		}
	}

	#ifdef TS_LOG
	std::cout << std::endl;
	std::cout << "Last improvement in iteration: " << iteration_of_last_improvement << std::endl;
	#endif
}

bool TabuSearcher::stopping_condition_met() const {
	if (_iteration_counter == meta_parameters.max_iterations) {
		return true;
	}
	
	return false;
}

std::optional<LocalSearchResult> TabuSearcher::get_local_best_solution(const Solution& solution, double solution_fitness) {
	#ifdef TS_LOG
	// std::cout << "Local search - start" << std::endl;
	#endif

	Solution local_best_solution = solution;
	double local_best_fitness = solution_fitness;
	Movement movement_to_local_best;
	bool found_improvement = false;

    int p1 = meta_parameters.ls_active_nodes;
    int p2 = meta_parameters.ls_inactive_nodes;
	auto neighbor_iterator = N3NeighborIterator(solution, p1, p2);
    unsigned neighbor_counter = 0;

    while (true) {
		std::optional<NeighborIterationResult> next = neighbor_iterator.get_next();

		if (!next.has_value()) {
			break;
		}

		auto [neighbor, movement_to_neighbor] = next.value();
		neighbor_counter++;

		#ifdef TS_LOG
		std::cout << "\rNeighbor: " << std::to_string(neighbor_counter);// << std::endl;
		// std::cout << movement_to_neighbor << std::endl;
		// std::cout << neighbor << std::endl;
		#endif

		double fitness = Model::calculate_fitness(neighbor);

        bool tabu = MovementTabuList::contains(movement_to_neighbor);
        bool aspirational = fitness > meta_parameters.aspiration_multiplier * _best_fitness;

        if (tabu && !aspirational) {
            continue;
        }

		if (fitness > local_best_fitness) {
			local_best_solution = neighbor;
			local_best_fitness = fitness;
			movement_to_local_best = movement_to_neighbor;
			found_improvement = true;

            if (meta_parameters.local_search_type == MetaParameters::LocalSearchType::FirstImprovement) {
                break;
            }
		}
	}

	#ifdef TS_LOG
	// std::cout << "Local search - end" << std::endl;
	#endif

	if (found_improvement) {
		return LocalSearchResult{local_best_solution, movement_to_local_best};
	}
	
	return std::nullopt;
}
