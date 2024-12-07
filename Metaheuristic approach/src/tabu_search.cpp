#include <iostream>
#include <limits>

#include "tabu_search.hpp"
#include "model.hpp"
#include "tabu_list.hpp"
#include "neighbor_iterator.hpp"

#define MAX_ITER 20

const double negative_infinity = - std::numeric_limits<double>::infinity();

int iter = 0;

Solution TabuSearch::tabu_search() {
	// generate initial solution
	Solution initial_solution = Model::generate_solution();
	
	Solution best_solution = initial_solution;
	double f_best = Model::calculate_fitness(best_solution);
	
	Solution current_solution = initial_solution;

	std::cout << "Initial solution:" << std::endl;
	std::cout << best_solution << std::endl;
	std::cout << "obj: " << f_best << std::endl;

	TabuList::clear();

	while (!stopping_condition_met()) {
		std::cout << "Iteration: " << (iter+1) << std::endl;

		Solution local_best_solution = get_local_best_solution(current_solution);

		double f = Model::calculate_fitness(local_best_solution);

		std::cout << "Local best solution: " << local_best_solution << std::endl;
		std::cout << "Obj: " << f << std::endl;

		if (f > f_best) {
			best_solution = local_best_solution;
			f_best = f;
		}

		TabuList::add(local_best_solution);

		std::cout << "Tabu list: " << TabuList::to_string() << std::endl;

		// TODO: update tabu list

		current_solution = local_best_solution;

		std::cout << std::endl;

		iter++;
	}
	
	return best_solution;
}

bool TabuSearch::stopping_condition_met() {
	if (iter == MAX_ITER) {
		return true;
	}
	
	return false;
}

Solution TabuSearch::get_local_best_solution(const Solution& solution) {
	Solution local_best_solution = solution;
	double f_local_best = Model::calculate_fitness(local_best_solution);

	int counter = 0;
	auto neighbor_iterator = NeighborIterator(solution);

	while (true) {
		counter++;

		std::optional<Solution> next = neighbor_iterator.get_next();

		if (!next) {
			break;
		}

		auto neighbor = next.value();

		std::cout << counter << ")" << neighbor << std::endl;

		double fitness = Model::calculate_fitness(neighbor);

		if (fitness > f_local_best) {
			local_best_solution = neighbor;
			f_local_best = fitness;
		}
	}

	return local_best_solution;
}
