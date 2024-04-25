#include <sstream>
#include <random>
#include <iostream>

#include "solution.hpp"

Solution::Solution(int j, int t, int p)
	:_j(j), _t(t), _vector(j * t)
{
	int N = j * t - 1;
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(0, N);
	
	for (int i = 0; i < p; i++) {
		int random_number = distr(eng);
		std::cout << random_number << std::endl;
		while (_vector[random_number]) {
			random_number = distr(eng);
			std::cout << "--> " << random_number << std::endl;
		}
		
		set_value(random_number, true);
	}
}

std::string Solution::to_string() const {
	std::stringstream buffer;
	
	buffer << "|";
	for (int i = 0; i < _t; i++) {
		buffer << " ";
		for (int j = 0; j < _j; j++) {
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

void Solution::set_value(int i, bool value) {
	if (i < 0 || i > static_cast<int>(_vector.size()) - 1) {
		throw std::out_of_range("Index out of bounds!");
	}
	
	_vector[i] = value;
}

std::ostream& operator<< (std::ostream& out, const Solution& s) {
	out << s.to_string();
	
	return out;
}
