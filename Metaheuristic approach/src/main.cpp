#include <iostream>

#include "solution.hpp"
#include "tabu_search.hpp"
#include "model.hpp"
#include "random.hpp"

int main() {
	RandomGenerator::set_seed(123);
	
	Model::create_model("assets/example.txt");
	
	std::cout << Model::get_model().to_string() << std::endl;

	Solution s = Model::generate_solution();
	
	std::cout << s << std::endl;
	
	double fitness = Model::get_model().calculate_fitness(s);
	
	std::cout << "fitness: " << fitness << "\n";
}
