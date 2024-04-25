#pragma once

#include <vector>
#include <ostream>

class Solution {
	public:
		Solution(int, int, int);
		std::string to_string() const;
		
		void flip(int, int);
		std::vector<Solution> get_neighbors() const;
	private:
		const int _j;
		const int _t;
		std::vector<bool> _vector;
		
		void set_value(int, bool);
};

std::ostream& operator<< (std::ostream&, const Solution&);
