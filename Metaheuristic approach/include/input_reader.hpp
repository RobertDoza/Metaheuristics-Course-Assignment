#pragma once

#include <string>
#include <vector>

class InputReader {
	public:
		static void read_input(const std::string&);
	private:
		static void read_matrix(std::ifstream&, std::vector<std::vector<double>>&);
};
