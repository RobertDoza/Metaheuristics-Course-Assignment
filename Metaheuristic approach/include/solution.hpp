#pragma once

#include <vector>
#include <ostream>

class Solution {
	public:
		Solution(int, int);
		std::string to_string() const;
		
		std::vector<Solution> get_neighbors() const;
	private:
		const int _j;
		const int _t;
		std::vector<bool> _vector;
};

std::ostream& operator<< (std::ostream&, const Solution&);
