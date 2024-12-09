#pragma once

#include <vector>
#include <ostream>
#include <map>

class Solution {
	public:
		Solution(int, int);
		Solution(int, int, int);
		Solution(const Solution&);
		Solution& operator= (const Solution&);

		bool operator==(const Solution&) const;
		
		std::string to_string() const;
		
		void flip(int, int);
		std::vector<Solution> get_neighbors() const;
		
		std::map<int, std::vector<int>> get_active_nodes() const;
		std::vector<std::vector<int>> get_nodes_per_period() const;

		friend class TabuSearcher;
		friend class NeighborIterator;
		friend class N1NeighborIterator;
		friend class N2NeighborIterator;
	private:
		const int _j;
		const int _t;
		std::vector<bool> _vector;
		
		void set_value(int, bool);
};

std::ostream& operator<< (std::ostream&, const Solution&);
