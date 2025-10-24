#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"
#include "parameters.hpp"
#include "statistics.hpp"

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cout << "Usage: " << argv[0] << " <instance_path> <parameters_path> <seed>" << std::endl;
		return 1;
	}

	std::string instance_filepath = argv[1];
    std::string parameters_filepath = argv[2];
    unsigned seed = std::stoul(argv[3]);

    RandomGenerator::set_seed(seed);
	Model::create_model(instance_filepath);

    load_meta_parameters(parameters_filepath);
	
    global_timer.start();
	auto [result, fitness] = TabuSearcher::tabu_search();
    global_statistics.total_time = global_timer.elapsed_seconds();

    global_statistics.best_solution = result;
    global_statistics.best_fitness = fitness;

    std::cout << meta_parameters << std::endl;

    std::cout << std::endl;

    std::cout << global_statistics << std::endl;

	return 0;
}

