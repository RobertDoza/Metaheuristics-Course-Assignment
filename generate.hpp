#ifndef GENERATE_HPP
#define GENERATE_HPP

#include <utility>
#include <vector>
#include <cmath>
#include <ostream>

/* Struct represents parameters of the problem model. */
struct ModelParameters {
	unsigned i;
	unsigned j;
	unsigned t;
	double s;
	unsigned p;
};

/* Struct represents the parameters used when generating a test instance. */
struct GenerationParameters {
	double dist_min_value;
	double dist_max_value;
	
	double pop_min_value;
	double pop_max_value;
};

/* Default parameters used when generating test instances. */
constexpr GenerationParameters default_generation_parameters = {0.0, 30.0, 0.0, 100.0};

/* Default output destination directory when generating test instances. */
constexpr std::string_view default_output_directory = "Output";

/* Class represents an instance of the problem model. */
class ModelInstance {
	public:
		/* Main constructor for the class. */
		ModelInstance(const ModelParameters&, const GenerationParameters& = default_generation_parameters);
		
		/* Function returns a string representation of the instance useful for testing via CPLEX IDE. */
		std::string to_cplex_string() const;
		
		/* Getter function returns the model parameters. */
		ModelParameters get_model_parameters() const;
		
		/* Overload of the << operator. Suitable when testing via the C++ implementation. */
		friend std::ostream& operator << (std::ostream&, const ModelInstance&);
	private:
		/* Number of nodes/locations (I). */
		unsigned _num_nodes;
		
		/* Number of potential facility locations (J). */
		unsigned _num_facilities;
		
		/* Number of time periods (T). */
		unsigned _num_periods;
		
		/* The coverage radius (S). */
		double _coverage_radius;
		
		/* Total number of facilities to be located across all time periods (s). */
		unsigned _total_facilities;
		
		/* Matrix of populations/demands of nodes in each time period. */
		std::vector<std::vector<double>> _population_matrix;
		
		/* Matrix of distances between each pair of locations. */
		std::vector<std::vector<double>> _distance_matrix;
		
		/* Function returns a string representation of the instance useful for testing via the C++ implementation. */
		std::string to_string() const;
		
		/* Function initializes the population matrix. */
		void initialize_populations(const double&, const double&);
		
		/* Function initializes the distance matrix. */
		void initialize_distances(const double&, const double&);
};

/* Function reads model parameters written in the file specified by the given path, and generates test instances in the current directory. */
void generate_test_instances(const std::string&, const GenerationParameters& = default_generation_parameters);

/* Function reads model parameters from a file and stores them in a vector. */
std::vector<ModelParameters> read_parameters_from_file(const std::string&);

/* Function creates a test instance file suitable for testing via the C++ project implementation. */
void generate_cpp_test_instance(const ModelInstance&, const std::string& = std::string(default_output_directory));

/* Function creates a test instance file suitable for testing via the CPLEX IDE. */
void generate_cplex_test_instance(const ModelInstance&, const std::string& = std::string(default_output_directory));

/* Function creates a fitting name for the test instance with given parameters, without the extension. */
std::string format_filename(const ModelParameters&);

/* Function creates a fitting name for the .txt test instance with given parameters. */
std::string format_cpp_instance_filename(const ModelParameters&);

/* Function creates a fitting name for the .dat test instance with given parameters. */
std::string format_cplex_instance_filename(const ModelParameters&);

/* Function calculates the Euclidean distance between two points in a plane. */
double euclidean_distance(const std::pair<double, double>&, const std::pair<double, double>&);

/* Function calculates the locations as points in a Euclidean plane. */
std::vector<std::pair<double, double>> calculate_locations(const int&, const double&, const double&);

#endif
