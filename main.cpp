#include <ilcplex/ilocplex.h>
#include <filesystem>
#include <chrono>

const std::string path_to_test_file = "Test files/1800 nodes/S = 4.0/1800_100_5_4_65.txt";
const std::string path_to_results_file = "output.txt";
// const std::string path_to_test_directory = "Test files/1800 nodes/S = 4.0";

/* Struct represents parameters of the problem model. */
struct ModelParameters {
	public:
		ModelParameters(const IloInt &i, const IloInt &j, const IloInt &t, const IloNum &s, const IloInt &p)
			:I(i), J(j), T(t), S(s), p(p)
		{}
	
		std::string csv_format() const {
			std::stringstream buffer;

			buffer << I << ", ";
			buffer << J << ", ";
			buffer << T << ", ";
			buffer << S << ", ";
			buffer << p;

			return buffer.str();
		}

	private:
		IloInt I;
		IloInt J;
		IloInt T;
		IloNum S;
		IloInt p;
};

/* Struct represents CPLEX results relevant to the seminar paper. */
struct CplexResults {
	public:
		CplexResults(const IloAlgorithm::Status &s, const IloNum &ov, const double &t, const IloInt &ni, const IloInt &nn, const IloNum &mrg, const IloNum &g)
			:status(s), objective_value(ov), time(t), num_iterations(ni), num_nodes(nn), mip_relative_gap(mrg), gap(g)
		{}

		std::string csv_format() const {
			std::stringstream buffer;

			buffer << std::fixed;

			buffer << std::setprecision(3);
			buffer << status << ", ";
			buffer << objective_value << ", ";
			buffer << time << ", ";
			buffer << num_iterations << ", ";
			buffer << num_nodes << ", ";

			if (status == IloAlgorithm::Status::Optimal) {
				buffer << "-";
			} else {
				buffer << std::setprecision(4);
				buffer << gap;
			}

			return buffer.str();
		}

	private:
		IloAlgorithm::Status status;
		IloNum objective_value;
		double time;
		IloInt num_iterations;
		IloInt num_nodes;
		IloNum mip_relative_gap;
		IloNum gap;
};

/* Struct represents all relevant info for a single test instance (parameters + CPLEX results). */
struct InstanceInfo {
	public:
		InstanceInfo(const ModelParameters &mp, const CplexResults &cr)
			:model_parameters(mp), cplex_results(cr)
		{}

		std::string csv_format() const {
			return model_parameters.csv_format() + ", " + cplex_results.csv_format();
		}
	private:
		ModelParameters model_parameters;
		CplexResults cplex_results;
};

/* Function test all instance files in the directory specified by directory_path, recursively. It writes all the results in the file specified by output_path. */
void test_instances_in_directory(const std::filesystem::path &directory_path, const std::filesystem::path &output_path);

/* Function tests a single instance in the file specified by input_path and writes the results to the file specified by output_path. */
void test_instance(const std::filesystem::path &input_path, const std::filesystem::path &output_path);

/* Function runs the CPLEX optimizer for the test instance in the file specified by the given path and returns the relevant results/information. */
InstanceInfo run_cplex(const std::filesystem::path &input_path);

/* Function prints instance results/information to the file specified by given path. */
void print_results_to_file(const std::filesystem::path &output_path, const InstanceInfo &results);

/* Main function. */
int main() {
    test_instance(path_to_test_file, path_to_results_file);

    return 0;
}

void test_instances_in_directory(const std::filesystem::path &directory_path, const std::filesystem::path &output_path) {
	if (!(std::filesystem::exists(directory_path) && std::filesystem::is_directory(directory_path))) {
		std::cerr << "Invalid directory path or not a directory." << std::endl;
		return;
	}

	for (const auto &file : std::filesystem::directory_iterator(directory_path)) {
		if (std::filesystem::is_directory(file.path())) {
			test_instances_in_directory(file.path(), output_path);
		} else {
			test_instance(file.path(), output_path);
		}
	}
}

void test_instance(const std::filesystem::path &input_path, const std::filesystem::path &output_path) {
	std::cout << "Testing instance from file " << input_path.filename().string() << std::endl;

	try {
		InstanceInfo results = run_cplex(input_path);
		print_results_to_file(output_path, results);
	} catch(std::exception &e) {
		std::cerr << "Error occured while testing instance!" << std::endl;
	}
}

InstanceInfo run_cplex(const std::filesystem::path &input_path) {
	IloEnv env;

	IloModel model(env);

	IloInt I, J, T, p;
	IloNum S;
	
	std::ifstream data(input_path);
	data >> I;
	data >> J;
	data >> T;
	data >> S;
	data >> p;

	ModelParameters model_parameters(I, J, T, S, p);

	IloArray<IloNumArray> A(env, I);
	for (int i = 0; i < I; i++) {
		A[i] = IloNumArray(env, T);
	}
	
	IloArray<IloNumArray> C(env, I);
	for (int i = 0; i < I; i++) {
		C[i] = IloNumArray(env, I);
	}

	for (int i = 0; i < I; i++) {
		for (int j = 0; j < T; j++) {
			data >> A[i][j];
		}
	}

	for (int i = 0; i < I; i++) {
		for (int j = 0; j < I; j++) {
			data >> C[i][j];
		}
	}

	IloArray<IloNumVarArray> x(env, J);
	for (int i = 0; i < J; i++) {
		x[i] = IloNumVarArray(env, T, 0, 1, ILOBOOL);
	}

	IloArray<IloNumVarArray> y(env, I);
	for (int i = 0; i < I; i++) {
		y[i] = IloNumVarArray(env, T, 0, 1, ILOFLOAT);
	}

	IloExpr fo(env);
	for (int t = 0; t < T; t++) {
		for (int i = 0; i < I; i++) {
			fo += A[i][t] * y[i][t];
		}
	}

	model.add(IloMaximize(env, fo));

	IloExpr Expr(env);
	for (int t = 0; t < T; t++) {
		for (int j = 0; j < J; j++) {
			Expr += x[j][t];
		}
	}
	
	model.add(Expr == p);
	Expr.end();		
	Expr = IloExpr(env);

	IloExpr Expr2(env);
	for (int i = 0; i < I; i++) {
		for (int t = 0; t < T; t++) {
			for (int j = 0; j < J; j++) {
				if (C[i][j] <= S) {
					Expr2 += x[j][t];
				}
			}
			Expr2 = Expr2 - y[i][t];
			model.add(Expr2 >= 0);
			Expr2.end();
			Expr2 = IloExpr(env);
		}
	}

	IloCplex cplex(env);
	cplex.setOut(env.getNullStream());
	cplex.setParam(IloCplex::Param::TimeLimit, 7200);
	cplex.setParam(IloCplex::HeurFreq, -1);
	cplex.extract(model);
	
	auto start = std::chrono::high_resolution_clock::now();
	if (!cplex.solve()) {
		env.error() << "Nije moguce resiti :-(" << std::endl;
		throw(-1);
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	CplexResults cplex_results (
		cplex.getStatus(),
		cplex.getObjValue(),
		duration.count() / 1000.0,
		cplex.getNiterations(),
		cplex.getNnodes(),
		cplex.getMIPRelativeGap(),
		cplex.getMIPRelativeGap() * 100
	);

	return InstanceInfo(model_parameters, cplex_results);
}

void print_results_to_file(const std::filesystem::path &output_path, const InstanceInfo &results) {
	std::ofstream output_file(output_path, std::ios::app);

	output_file << results.csv_format() << std::endl;
}