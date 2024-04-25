#pragma once

#include <random>

class RandomGenerator {
	public:
		static void set_seed(unsigned);
		static unsigned get_seed();
		
		static int get_random_number(int);
	private:
		std::mt19937 _generator;
		unsigned _seed;
		
		RandomGenerator();
		
		RandomGenerator(const RandomGenerator&) = delete;
		RandomGenerator& operator=(const RandomGenerator&) = delete;
		
		static RandomGenerator& get_instance();
};

