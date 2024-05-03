#pragma once

#include <string>
#include <vector>

struct ModelParameters {
	int i;
	int j;
	int t;
	double s;
	int p;
	std::vector<std::vector<double>> population_matrix;
	std::vector<std::vector<double>> distance_matrix;
};

class InputReader {
	public:
		static ModelParameters read_input(const std::string&);
	private:
		static int read_int(std::ifstream&);
		static double read_double(std::ifstream& in);
		static void read_matrix(std::ifstream&, std::vector<std::vector<double>>&);
};
