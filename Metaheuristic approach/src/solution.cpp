#include <sstream>

#include "solution.hpp"

Solution::Solution(int j, int t)
	:_j(j), _t(t), _vector(j*t)
{}

std::string Solution::to_string() const {
	std::stringstream buffer;
	
	buffer << "|";
	for (int i = 1; i <= _t; i++) {
		buffer << " ";
		for (int j = 1; j <= _j; j++) {
			buffer << _vector[i * _j + j] << " ";
		}
		buffer << "|";
	}
	
	return buffer.str();
}

std::vector<Solution> Solution::get_neighbors() const {
	std::vector<Solution> neighbors = {};
	
	// TODO
	
	return neighbors;
}

void Solution::flip(int i, int j) {
	_vector[i] = !_vector[i];
	_vector[j] = !_vector[j];
}

std::ostream& operator<< (std::ostream& out, const Solution& s) {
	out << s.to_string();
	
	return out;
}
