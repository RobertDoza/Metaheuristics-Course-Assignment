#include "neighbor_iterator.hpp"

NeighborIterator::NeighborIterator(const Solution& solution)
    :_original_solution(solution), _i(0), _j(0)
{}

std::optional<Solution> NeighborIterator::get_next() {
    bool has_next = _advance_to_next();

    if (!has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_i, false);
    neighbor.set_value(_j, true);

    return neighbor;
}

bool NeighborIterator::_advance_to_next() {
    while (true) {
        _j++;
        if (_j >= _original_solution._vector.size()) {
            _j = 0;
            _i++;
            if (_i >= _original_solution._vector.size()) {
                return false;
            }
        }

        if (_original_solution._vector[_i] == true && _original_solution._vector[_j] == false) {
            return true;
        }
    }
}
