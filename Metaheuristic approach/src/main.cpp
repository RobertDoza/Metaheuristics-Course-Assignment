#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"
#include "tabu_list.hpp"
#include "timer.hpp"

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
	
    // TODO: remove magic number (timeout (seconds))
    global_timer.start(600);
	auto [result, fitness, timeout_reached] = TabuSearcher::tabu_search();

	std::cout << "MAX ITER: " << MAX_ITER << std::endl;
	std::cout << "MOV TL size: " << MOV_TL_SIZE << std::endl;
	std::cout << "Best solution: " << result << std::endl;
	std::cout << "Obj: " << fitness << std::endl;
    std::cout << "Timeout reached: " << (timeout_reached ? "yes" : "no") << std::endl;
}
