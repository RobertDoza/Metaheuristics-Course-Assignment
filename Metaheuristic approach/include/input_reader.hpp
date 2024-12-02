#pragma once

#include <string>
#include <vector>

#include "model.hpp"

class InputReader {
	public:
		static ModelParameters read_input(const std::string&);
	private:
		static int read_int(std::ifstream&);
		static double read_double(std::ifstream&);
		static void read_matrix(std::ifstream&, std::vector<std::vector<double>>&);
};
