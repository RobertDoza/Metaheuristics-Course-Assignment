#pragma once

#include <optional>

#include "solution.hpp"

class NeighborIterator {
    public:
        NeighborIterator(const Solution&);
        std::optional<Solution> get_next();
    private:
        bool _advance_to_next();
    private:
        const Solution _original_solution;
        unsigned _i;
        unsigned _j;
};
