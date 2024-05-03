#include "utils.hpp"

#include <sstream>

template<typename T>
std::string matrix_to_string(const std::vector<std::vector<T>>& matrix) {
	std::stringstream buffer;
	
	for (size_t i = 0; i < matrix.size(); i++) {
		for (const T& elem : matrix[i]) {
			buffer << elem << "\t";
		}
		
		if (i != matrix.size() - 1) {
			buffer << "\n";
		}
	}
	
	return buffer.str();
}

template std::string matrix_to_string<double>(const std::vector<std::vector<double>>& matrix);
