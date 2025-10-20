#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"
#include "parameters.hpp"

constexpr const unsigned max_iterations = 200;
constexpr const unsigned movement_tabu_list_size = 20;
constexpr const unsigned max_iter_without_improvement = 50;
constexpr const double local_search_parameter_multiplier_1 = 0.125;
constexpr const double local_search_parameter_multiplier_2 = 0.037;

void test_tabu_search(const std::string&);

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <path>" << std::endl;
		return 1;
	}

	std::string instance_filepath = argv[1];
	test_tabu_search(instance_filepath);

	return 0;
}

void test_tabu_search(const std::string& instance_filepath) {
	// std::cout << instance_filepath << std::endl;

    // TODO: remove magic number (seed)
	RandomGenerator::set_seed(123);
	Model::create_model(instance_filepath);

    int p = Model::get_parameters().target_num_sites;
    int t = Model::get_parameters().num_time_periods;
    int j = Model::get_parameters().num_eligible_sites;
    meta_parameters = MetaParameters{
        max_iterations,
        movement_tabu_list_size,
        max_iter_without_improvement,
        local_search_parameter_multiplier_1,
        local_search_parameter_multiplier_2,
        (unsigned) (p * local_search_parameter_multiplier_1),
        (unsigned) ((j * t - p) * local_search_parameter_multiplier_2)
    };
	
    // TODO: remove magic number (timeout (seconds))
    global_timer.start(600);
	auto [result, fitness, timeout_reached] = TabuSearcher::tabu_search();

	std::cout << "MAX ITER: " << meta_parameters.max_iterations << std::endl;
	std::cout << "MOV TL size: " << meta_parameters.movement_tabu_list_size << std::endl;
	std::cout << "Best solution: " << result << std::endl;
	std::cout << "Obj: " << fitness << std::endl;
    std::cout << "Timeout reached: " << (timeout_reached ? "yes" : "no") << std::endl;
}
