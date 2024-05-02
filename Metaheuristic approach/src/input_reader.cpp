#include "input_reader.hpp"

#include <fstream>
#include <vector>

// TODO: remove me
#include <iostream>

void InputReader::read_input(const std::string& filename) {
	std::ifstream in(filename);
	
	int i, j, t, p;
	double s;
	
	in >> i >> j >> t >> s >> p;
	
	std::cout << "I = " << i << "\n";
	std::cout << "J = " << j << "\n";
	std::cout << "T = " << t << "\n";
	std::cout << "S = " << s << "\n";
	std::cout << "p = " << p << "\n";
	
	std::vector<std::vector<double>> population_matrix(i, std::vector<double>(t));
	std::vector<std::vector<double>> distance_matrix(i, std::vector<double>(i));
	
	for (int _i = 0; _i < i; _i++) {
		for (int _t = 0; _t < t; _t++) {
			in >> population_matrix[_i][_t];
		}
	}
	
	for (int _i = 0; _i < i; _i++) {
		for (int _j = 0; _j < i; _j++) {
			in >> distance_matrix[_i][_j];
		}
	}
	
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
