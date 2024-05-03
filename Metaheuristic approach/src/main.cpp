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
	
	auto result = s.get_nodes_per_period();
	
	for (const auto& row : result) {
		for (int n : row) {
			std::cout << n << " ";
		}
		std::cout << "\n";
	}
}
