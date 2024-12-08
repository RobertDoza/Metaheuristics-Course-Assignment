#pragma once

#include <optional>

#include "solution.hpp"

class NeighborIterator {
    public:
        virtual std::optional<Solution> get_next() = 0;
    protected:
        NeighborIterator(const Solution&);
    private:
        virtual void _advance_to_next() = 0;
    protected:
        const Solution _original_solution;
        bool _has_next;
};

class N1NeighborIterator : public NeighborIterator {
    public:
        N1NeighborIterator(const Solution&);
        std::optional<Solution> get_next() override;
    private:
        void _advance_to_next() override;
    private:
        unsigned _i;
        unsigned _j;
};

class N2NeighborIterator : public NeighborIterator {
    public:
        N2NeighborIterator(const Solution&);
        std::optional<Solution> get_next() override;
    private:
        void _advance_to_next() override;
    private:
        std::size_t _position;
        std::size_t _to_turn_off;
        std::size_t _to_turn_on;
};
