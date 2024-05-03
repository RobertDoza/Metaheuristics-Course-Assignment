#include <iostream>

#include "solution.hpp"
#include "tabu_search.hpp"
#include "model.hpp"

int main() {
	Model::create_model("assets/example.txt");
	
	std::cout << Model::get_model().to_string() << std::endl;

	Solution s = Model::generate_solution();
	
	std::cout << s << std::endl;
}
