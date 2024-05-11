#include <sstream>
#include <iostream>

#include "solution.hpp"
#include "random.hpp"

Solution::Solution(int j, int t, int p)
	:_j(j), _t(t), _vector(j * t)
{
	int n = j * t - 1;
	
	for (int i = 0; i < p; i++) {
		int random_number = RandomGenerator::get_random_number(n);
		
		// TODO: remove me
		// std::cout << random_number << std::endl;
		
		while (_vector[random_number]) {
			random_number = RandomGenerator::get_random_number(n);
			/// std::cout << "--> " << random_number << std::endl;
		}
		
		set_value(random_number, true);
	}
}

Solution::Solution(const Solution& other)
	:_j(other._j), _t(other._t), _vector(other._vector)
{}

Solution& Solution::operator= (const Solution& other) {
	if (this != &other) {
		_vector = other._vector;
	}
	
	return *this;
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
	
	for (unsigned i = 0; i < _vector.size(); i++) {
		if (_vector[i]) {
			for (unsigned j = 0; j < _vector.size(); j++) {
				if (!_vector[j] && i != j) {
					Solution neighbor = *this;
					neighbor.set_value(i, false);
					neighbor.set_value(j, true);
					neighbors.push_back(neighbor);
				}
			}
		}
	}
	
	return neighbors;
}

std::map<int, std::vector<int>> Solution::get_active_nodes() const {
	std::map<int, std::vector<int>> active_nodes = {};

	for (int t = 0; t < _t; t++) {
		for (int j = 0; j < _j; j++) {
			if (_vector[t * _j + j]) {
				active_nodes[j].push_back(t);
			}
		}
	}
	
	return active_nodes;
}

std::vector<std::vector<int>> Solution::get_nodes_per_period() const {
	std::vector<std::vector<int>> result;
	
	for (int t = 0; t < _t; t++) {
		std::vector<int> nodes;
		
		for (int j = 0; j < _j; j++) {
			if (_vector[t * _j + j]) {
				nodes.push_back(j);
			}
		}
		
		result.push_back(nodes);
	}
	
	return result;
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
