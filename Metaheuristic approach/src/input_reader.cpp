#include <fstream>

#include "input_reader.hpp"

ModelParameters InputReader::read_input(const std::string& filename) {
	std::ifstream in(filename);
	
	if (!in.is_open()) {
		throw std::runtime_error("Unable to open file");
	}
	
	std::size_t i, j, t, p;
	double s;
	
	i = read_size_t(in);
	j = read_size_t(in);
	t = read_size_t(in);
	s = read_double(in);
	p = read_size_t(in);
	
	std::vector<std::vector<double>> population_matrix(i, std::vector<double>(t));
	std::vector<std::vector<double>> distance_matrix(i, std::vector<double>(i));
	
	read_matrix(in, population_matrix);
	read_matrix(in, distance_matrix);
	
	return ModelParameters{i, j, t, s, p, population_matrix, distance_matrix};
}

std::size_t InputReader::read_size_t(std::ifstream& in) {
    std::string token;
    if (!(in >> token)) {
        throw std::runtime_error("Error reading size_t value");
    }

    try {
        std::size_t position;
        unsigned long value = std::stoul(token, &position);

        if (position != token.length()) {
            throw std::runtime_error("Not a valid size_t value");
        }

        return static_cast<std::size_t>(value);
    } catch (const std::invalid_argument&) {
        throw std::runtime_error("Invalid size_t format");
    } catch (const std::out_of_range&) {
        throw std::runtime_error("size_t value out of range");
    }
}

double InputReader::read_double(std::ifstream& in) {
	std::string token;
	if (!(in >> token)) {
		throw std::runtime_error("Error reading double");
	}

	try {
		std::size_t position;
		double value = std::stod(token, &position);
		
		if (position != token.length()) {
			throw std::runtime_error("Not a double");
		}
		
		return value;
	} catch (const std::invalid_argument& e) {
		throw std::runtime_error("Invalid double format");
	} catch (const std::out_of_range& e) {
		throw std::runtime_error("Double out of range");
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
