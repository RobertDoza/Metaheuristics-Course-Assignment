#include "neighbor_iterator.hpp"

NeighborIterator::NeighborIterator(const Solution& solution)
    :_original_solution(solution)
{}

N1NeighborIterator::N1NeighborIterator(const Solution& solution)
    :NeighborIterator(solution), _i(0), _j(0)
{}

std::optional<Solution> N1NeighborIterator::get_next() {
    _advance_to_next();

    if (!_has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_i, false);
    neighbor.set_value(_j, true);

    return neighbor;
}

void N1NeighborIterator::_advance_to_next() {
    while (true) {
        _j++;
        if (_j >= _original_solution._vector.size()) {
            _j = 0;
            _i++;
            if (_i >= _original_solution._vector.size()) {
                _has_next = false;
                return;
            }
        }

        if (_original_solution._vector[_i] == true && _original_solution._vector[_j] == false) {
            _has_next = true;
            return;
        }
    }
}

N2NeighborIterator::N2NeighborIterator(const Solution& solution)
    :NeighborIterator(solution), _position(0)
{}

std::optional<Solution> N2NeighborIterator::get_next() {
    _advance_to_next();

    if (!_has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_to_turn_off, false);
    neighbor.set_value(_to_turn_on, true);

    return neighbor;
}

void N2NeighborIterator::_advance_to_next() {
    enum class Side {
        Left,
        Right
    };

    static Side next_side = Side::Left;
    std::size_t solution_length = _original_solution._vector.size();

    if (next_side == Side::Right) {
        next_side = Side::Left;
        
        std::size_t pos_right = _position == solution_length - 1 ? 0 : _position + 1;

        if (_original_solution._vector[_position] == true && _original_solution._vector[pos_right] == false) {
            _to_turn_off = _position;
            _to_turn_on = pos_right;
            _has_next = true;
            return;
        }
    }

    while (true) {
        _position++;

        if (_position >= solution_length) {
            _has_next = false;
            return;
        }

        if (_original_solution._vector[_position] == false) {
            continue;
        }
        
        next_side = Side::Right;
        std::size_t pos_left = _position == 0 ? solution_length - 1 : _position - 1;
        
        if (_original_solution._vector[pos_left] == false) {
            _to_turn_off = _position;
            _to_turn_on = pos_left;
            _has_next = true;
        } else {
            _advance_to_next();
        }
        return;
    }
}
