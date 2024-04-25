#include <iostream>

#include "solution.hpp"
#include "tabu_search.hpp"

int main() {
	Solution s(3, 4, 5);
	
	std::cout << s << std::endl;
	
	// TabuSearch::tabu_search(s);
	
	s.flip(2, 3);
	
	std::cout << s << std::endl;
}
