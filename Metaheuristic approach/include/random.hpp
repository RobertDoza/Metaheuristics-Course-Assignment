#pragma once

#include <random>
#include <unordered_set>

class RandomGenerator {
	public:
		static void set_seed(unsigned);
		static unsigned get_seed();
		
		static int get_random_number(int);

		static std::vector<unsigned> pick_k_elements(const std::vector<unsigned>&, const unsigned);
		static unsigned pick_random(const std::vector<unsigned>&);
	private:
		std::mt19937 _generator;
		unsigned _seed;
		
		RandomGenerator();
		
		RandomGenerator(const RandomGenerator&) = delete;
		RandomGenerator& operator=(const RandomGenerator&) = delete;
		
		static RandomGenerator& get_instance();
};

