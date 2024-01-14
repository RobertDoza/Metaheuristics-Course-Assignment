#include <iostream>

#include "generate.hpp"

int main() {
	// Example of a test instance
	ModelInstance instance(
		//I  J  T   S   p
		{ 6, 5, 4, 3.2, 1 }
	);

	generate_cpp_test_instance(instance, "Output");

	return 0;
}
