#include "random.hpp"

void RandomGenerator::set_seed(unsigned seed) {
	get_instance()._seed = seed;
	get_instance()._generator.seed(seed);
}

unsigned RandomGenerator::get_seed() {
	return get_instance()._seed;
}

int RandomGenerator::get_random_number(int n) {
	std::uniform_int_distribution<int> distribution(0, n - 1);
	
	return distribution(get_instance()._generator);
}

RandomGenerator::RandomGenerator()
	:_generator(std::random_device{}())
{}

RandomGenerator& RandomGenerator::get_instance() {
	static RandomGenerator generator;
	return generator;
}

