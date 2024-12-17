#include "neighbor_iterator.hpp"
#include "random.hpp"

NeighborIterator::NeighborIterator(const Solution& solution)
    :_original_solution(solution)
{}

N1NeighborIterator::N1NeighborIterator(const Solution& solution)
    :NeighborIterator(solution), _i(0), _j(0)
{}

std::optional<NeighborIterationResult> N1NeighborIterator::get_next() {
    _advance_to_next();

    if (!_has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_i, false);
    neighbor.set_value(_j, true);

    return NeighborIterationResult{neighbor, Movement{_i, _j}};
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

std::optional<NeighborIterationResult> N2NeighborIterator::get_next() {
    _advance_to_next();

    if (!_has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_to_turn_off, false);
    neighbor.set_value(_to_turn_on, true);

    return NeighborIterationResult{neighbor, Movement{_to_turn_off, _to_turn_on}};
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

N3NeighborIterator::N3NeighborIterator(const Solution& solution)
    :NeighborIterator(solution)
{}

N3NeighborIterator::N3NeighborIterator(const Solution& solution, const std::size_t size_active, const std::size_t size_inactive)
    :NeighborIterator(solution),
    _active_node_indices(RandomGenerator::pick_k_elements(solution.get_active_node_indices(), size_active)),
    _inactive_node_indices(RandomGenerator::pick_k_elements(solution.get_inactive_node_indices(), size_inactive)),
    _i(0), _j(0), _active_node_index(0), _inactive_node_index(0)
{}

std::optional<NeighborIterationResult> N3NeighborIterator::get_next() {
    _advance_to_next();

    if (!_has_next) {
        return std::nullopt;
    }

    Solution neighbor = _original_solution;
    neighbor.set_value(_active_node_index, false);
    neighbor.set_value(_inactive_node_index, true);

    return NeighborIterationResult{neighbor, Movement{_active_node_index, _inactive_node_index}};
}

void N3NeighborIterator::_advance_to_next() {
    while (true) {
        if (_j >= _inactive_node_indices.size()) {
            _j = 0;
            _i++;
            if (_i >= _active_node_indices.size()) {
                _has_next = false;
                return;
            }
        }

        _active_node_index = _active_node_indices[_i];
        _inactive_node_index = _inactive_node_indices[_j];
        
        _j++;

        if (_original_solution._vector[_active_node_index] == true && _original_solution._vector[_inactive_node_index] == false) {
            _has_next = true;
            return;
        }
    }
}
