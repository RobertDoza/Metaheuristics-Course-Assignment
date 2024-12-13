#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"

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
	std::cout << instance_filepath << std::endl;

	RandomGenerator::set_seed(123);
	Model::create_model(instance_filepath);
	
	auto [result, fitness] = TabuSearcher::tabu_search();

	std::cout << "Best solution: " << result << std::endl;
	std::cout << "Obj: " << fitness << std::endl;
}
