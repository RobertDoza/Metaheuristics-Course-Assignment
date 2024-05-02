#include "input_reader.hpp"

#include <fstream>
#include <vector>

// TODO: remove me
#include <iostream>

void InputReader::read_input(const std::string& filename) {
	std::ifstream in(filename);
	
	if (!in.is_open()) {
		throw std::runtime_error("Unable to open file");
	}
	
	int i, j, t, p;
	double s;
	
	if (!(in >> i >> j >> t >> s >> p)) {
		throw std::runtime_error("Invalid format in the header");
	}
	
	if (i <= 0 || j <= 0 || t <= 0 || s <= 0.0 || p <= 0) {
		throw std::runtime_error("Invalid values in the header");
	}
	
	std::cout << "I = " << i << "\n";
	std::cout << "J = " << j << "\n";
	std::cout << "T = " << t << "\n";
	std::cout << "S = " << s << "\n";
	std::cout << "p = " << p << "\n";
	
	std::vector<std::vector<double>> population_matrix(i, std::vector<double>(t));
	std::vector<std::vector<double>> distance_matrix(i, std::vector<double>(i));
	
	read_matrix(in, population_matrix);
	read_matrix(in, distance_matrix);
	
	for (int _i = 0; _i < i; _i++) {
		for (int _t = 0; _t < t; _t++) {
			std::cout << population_matrix[_i][_t] << " ";
		}
		std::cout << "\n";
	}
	
	for (int _i = 0; _i < i; _i++) {
		for (int _j = 0; _j < i; _j++) {
			std::cout << distance_matrix[_i][_j] << " ";
		}
		std::cout << "\n";
	}
}

void InputReader::read_matrix(std::ifstream& in, std::vector<std::vector<double>>& matrix) {
	for (size_t i = 0; i < matrix.size(); i++) {
		for (size_t j = 0; j < matrix[i].size(); j++) {
			if (!(in >> matrix[i][j])) {
				throw std::runtime_error("Error reading matrix values");
			}
		}
	}
}
