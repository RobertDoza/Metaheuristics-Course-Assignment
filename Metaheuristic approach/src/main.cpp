#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <path>" << std::endl;
		return 1;
	}

	std::string filepath = argv[1];

	std::cout << filepath << std::endl;

	RandomGenerator::set_seed(123);
	Model::create_model(filepath);
	
	TabuSearch::tabu_search();

	return 0;
}
