#include <iostream>

#include "solution.hpp"
#include "tabu_search.hpp"
#include "input_reader.hpp"

int main() {
	/*
	Solution s(3, 4, 5);
	
	std::cout << s << std::endl;
	
	int i = 0;
	for (const auto& n : s.get_neighbors()) {
		std::cout << ++i << ") ";
		std::cout << n << std::endl;
	}
	*/
	
	InputReader::read_input("assets/6_5_4_3.2_1.txt");
}
