#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"
#include "parameters.hpp"

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
	
	auto [result, fitness] = TabuSearcher::tabu_search();

	std::cout << "MAX ITER: " << meta_parameters.max_iterations << std::endl;
	std::cout << "MAX ITER without improvement: " << meta_parameters.max_iter_without_improvement << std::endl;
	std::cout << "MOV TL size: " << meta_parameters.movement_tabu_list_size << std::endl;
    std::cout << "Number of active nodes in LS: " << meta_parameters.ls_active_nodes << std::endl;
    std::cout << "Number of inactive nodes in LS: " << meta_parameters.ls_inactive_nodes << std::endl;

	std::cout << "Best solution: " << result << std::endl;
	std::cout << "Obj: " << std::to_string(fitness) << std::endl;
}
