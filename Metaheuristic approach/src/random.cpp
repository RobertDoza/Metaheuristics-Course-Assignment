#include <stdexcept>
#include <algorithm>

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

std::vector<unsigned> RandomGenerator::pick_k_elements(const std::vector<unsigned>& vector, const unsigned k) {
	if (vector.empty()) {
		throw std::out_of_range("Input vector is empty!");
	}

	if (k > vector.size()) {
		throw std::invalid_argument("Trying to pick more elements than available in vector!");
	}

	std::vector<unsigned> picked_elements;

	std::vector<unsigned> copy(vector);
	std::shuffle(copy.begin(), copy.end(), get_instance()._generator);

	picked_elements.insert(picked_elements.end(), copy.begin(), copy.begin() + k);

    return picked_elements;
}

unsigned RandomGenerator::pick_random(const std::vector<unsigned>& vector) {
	if (vector.empty()) {
		throw std::out_of_range("Trying to pick a random element from an empty vector!");
	}

	std::uniform_int_distribution<std::size_t> distribution(0, vector.size() - 1);
	return vector[distribution(get_instance()._generator)];
}

RandomGenerator::RandomGenerator()
	:_generator(std::random_device{}())
{}

RandomGenerator& RandomGenerator::get_instance() {
	static RandomGenerator generator;
	return generator;
}

