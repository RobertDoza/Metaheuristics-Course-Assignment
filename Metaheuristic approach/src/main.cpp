#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"
#include "parameters.hpp"
#include "statistics.hpp"

void test_tabu_search(const std::string&, unsigned);

int main(int argc, char** argv) {
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " <path> <seed>" << std::endl;
		return 1;
	}

	std::string instance_filepath = argv[1];
    unsigned seed = std::stoul(argv[2]);
	test_tabu_search(instance_filepath, seed);

	return 0;
}

void test_tabu_search(const std::string& instance_filepath, unsigned seed) {
	// std::cout << instance_filepath << std::endl;

	RandomGenerator::set_seed(seed);
	Model::create_model(instance_filepath);

    meta_parameters = load_meta_parameters("meta_parameters.txt");
    int p = Model::get_parameters().target_num_sites;
    int t = Model::get_parameters().num_time_periods;
    int j = Model::get_parameters().num_eligible_sites;
    meta_parameters.ls_active_nodes = (unsigned) (p * meta_parameters.local_search_parameter_multiplier_1);
    meta_parameters.ls_inactive_nodes = (unsigned) ((j * t - p) * meta_parameters.local_search_parameter_multiplier_2);
	
    global_timer.start();
	auto [result, fitness] = TabuSearcher::tabu_search();
    global_statistics.total_time = global_timer.elapsed_seconds();

    global_statistics.best_solution = result;
    global_statistics.best_fitness = fitness;

    std::cout << meta_parameters << std::endl;

    std::cout << std::endl;

    std::cout << global_statistics << std::endl;
}

