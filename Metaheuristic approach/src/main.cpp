#include <iostream>

#include "solution.hpp"
#include "tabu_search.hpp"
#include "input_reader.hpp"

int main() {
	auto result = InputReader::read_input("assets/example.txt");
	
	std::cout << "I = " << result.i << "\n";
	std::cout << "J = " << result.j << "\n";
	std::cout << "T = " << result.t << "\n";
	std::cout << "S = " << result.s << "\n";
	std::cout << "p = " << result.p << "\n";
	
	for (const auto& row : result.population_matrix) {
		for (const auto p : row) {
			std::cout << p << "\t";
		}
		std::cout << "\n";
	}
	
	for (const auto& row : result.distance_matrix) {
		for (const auto d : row) {
			std::cout << d << "\t";
		}
		std::cout << "\n";
	}
	
	Solution s(result.j, result.t, result.p);
	
	std::cout << s << std::endl;
}
