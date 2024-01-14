#include <random>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>

#include "generate.hpp"

constexpr int precision = 5;

void generate_test_instances(const std::string &path, const GenerationParameters &generation_parameters) {
	std::vector<ModelParameters> parameters = read_parameters_from_file(path);
	
	std::cout << "                    \tI\tJ\tT\tS\tp\n";
	for (const ModelParameters &model_parameters : parameters) {
		std::cout
			<< "generating instance:\t"
			<< model_parameters.i << "\t"
			<< model_parameters.j << "\t"
			<< model_parameters.t << "\t"
			<< model_parameters.s << "\t"
			<< model_parameters.p << "\n";
		
		ModelInstance instance(model_parameters, generation_parameters);
		
		generate_cpp_test_instance(instance);
		generate_cplex_test_instance(instance);
	}
}

std::vector<ModelParameters> read_parameters_from_file(const std::string &path) {
	std::ifstream file(path);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error reading from file!");
	}
	
	std::vector<ModelParameters> parameters = {};
	
	ModelParameters mp;
	while (file >> mp.i >> mp.j >> mp.t >> mp.s >> mp.p) {		
		parameters.push_back(mp);
	}
	
	file.close();
	
	return parameters;
}

void generate_cpp_test_instance(const ModelInstance &instance, const std::string &output_dir) {
	std::string filename = format_cpp_instance_filename(instance.get_model_parameters());
	std::string path = output_dir + "/" + filename;
	
	std::ofstream file(path);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file!");
	}
	
	file << instance;
	
	file.close();
}

void generate_cplex_test_instance(const ModelInstance &instance, const std::string &output_dir) {
	std::string filename = format_cplex_instance_filename(instance.get_model_parameters());
	std::string path = output_dir + "/" + filename;
	
	std::ofstream file(path);
	
	if (!file.is_open()) {
		throw std::runtime_error("Error opening file!");
	}
	
	file << instance.to_cplex_string();
	
	file.close();
}

std::string format_filename(const ModelParameters &parameters) {
	std::stringstream buffer;
	
	buffer << parameters.i;
	buffer << "_";
	buffer << parameters.j;
	buffer << "_";
	buffer << parameters.t;
	buffer << "_";
	buffer << parameters.s;
	buffer << "_";
	buffer << parameters.p;
	
	return buffer.str();
}

std::string format_cpp_instance_filename(const ModelParameters &parameters) {
	return format_filename(parameters) + ".txt";
}

std::string format_cplex_instance_filename(const ModelParameters &parameters) {
	return format_filename(parameters) + ".dat";
}

double euclidean_distance(const std::pair<double, double> &point1, const std::pair<double, double> &point2) {
	double x1 = point1.first;
	double y1 = point1.second;
	double x2 = point2.first;
	double y2 = point2.second;

	double distance = std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
	
	return distance;
}

std::vector<std::pair<double, double>> calculate_locations(const int &num_nodes, const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	std::vector<std::pair<double, double>> locations;
	
	for (int i = 0; i < num_nodes; i++) {
		double x = distribution(engine);
		double y = distribution(engine);
		locations.push_back({x, y});
	}
	
	return locations;
}

ModelInstance::ModelInstance(const ModelParameters &p, const GenerationParameters &g)
	:_num_nodes(p.i), _num_facilities(p.j), _num_periods(p.t), _coverage_radius(p.s), _total_facilities(p.p),
	_population_matrix(p.i, std::vector<double>(p.t)), _distance_matrix(p.i, std::vector<double>(p.i))
{
	initialize_populations(g.pop_min_value, g.pop_max_value);
	initialize_distances(g.dist_min_value, g.dist_max_value);
}

std::ostream& operator << (std::ostream &o, const ModelInstance &i) {
	o << i.to_string();
	
	return o;
}

std::string ModelInstance::to_string() const {
	std::stringstream buffer;
	
	buffer << _num_nodes << " ";
	buffer << _num_facilities << " ";
	buffer << _num_periods << " ";
	buffer << _coverage_radius << " ";
	buffer << _total_facilities << "\n";
	
	buffer << std::setprecision(precision) << std::fixed;
	
	for (const std::vector<double> &row : _population_matrix) {
		for (const double &value : row) {
			buffer << value << " ";
		}
		buffer << "\n";
	}
	
	for (const std::vector<double> &row : _distance_matrix) {
		for (const double &value : row) {
			buffer << value << " ";
		}
		buffer << "\n";
	}
	
	return buffer.str();
}

std::string ModelInstance::to_cplex_string() const {
	std::stringstream buffer;
	
	buffer << "I = " << _num_nodes << ";\n";
	buffer << "J = " << _num_facilities << ";\n";
	buffer << "T = " << _num_periods << ";\n";
	buffer << "S = " << _coverage_radius << ";\n";
	buffer << "p = " << _total_facilities << ";\n";
	
	buffer << std::setprecision(precision) << std::fixed;
	
	bool add_comma, add_inner_comma;
	
	add_comma = false;
	buffer << "pop = [";
	for (const std::vector<double> &row : _population_matrix) {
		if (add_comma) {
			buffer << ",";
		}
		
		add_inner_comma = false;
		buffer << "\n\t[";
		for (const double &value : row) {
			if (add_inner_comma) {
				buffer << ", ";
			}
			
			buffer << value;
			
			add_inner_comma = true;
		}
		buffer << "]";
		
		add_comma = true;
	}
	buffer << "\n];\n";
	
	add_comma = false;
	buffer << "dist = [";
	for (const std::vector<double> &row : _distance_matrix) {
		if (add_comma) {
			buffer << ",";
		}
		
		add_inner_comma = false;
		buffer << "\n\t[";
		for (const double &value : row) {
			if (add_inner_comma) {
				buffer << ", ";
			}
			
			buffer << value;
			
			add_inner_comma = true;
		}
		buffer << "]";
		
		add_comma = true;
	}
	buffer << "\n];\n";
	
	return buffer.str();
}

ModelParameters ModelInstance::get_model_parameters() const {
	return {_num_nodes, _num_facilities, _num_periods, _coverage_radius, _total_facilities};
}

void ModelInstance::initialize_populations(const double &min_value, const double &max_value) {
	std::random_device rd;
	
	std::default_random_engine engine(rd());
	
	std::uniform_real_distribution<double> distribution(min_value, max_value);
	
	for (unsigned i = 0; i < _num_nodes; i++) {
		for (unsigned j = 0; j < _num_periods; j++) {
			_population_matrix[i][j] = distribution(engine);
		}
	}
}

void ModelInstance::initialize_distances(const double &min_value, const double &max_value) {
	std::vector<std::pair<double, double>> locations = calculate_locations(_num_nodes, min_value, max_value);
	
	int size = locations.size();
	
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			double distance = euclidean_distance(locations[i], locations[j]);
			_distance_matrix[i][j] = _distance_matrix[j][i] = distance;
		}
	}
}
