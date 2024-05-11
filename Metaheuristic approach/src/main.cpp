#include <iostream>

#include "random.hpp"
#include "model.hpp"
#include "tabu_search.hpp"

int main() {
	RandomGenerator::set_seed(123);
	Model::create_model("assets/example.txt");
	
	TabuSearch::tabu_search();
}
