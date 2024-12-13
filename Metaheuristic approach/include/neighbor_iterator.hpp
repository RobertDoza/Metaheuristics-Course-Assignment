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

class N3NeighborIterator : public NeighborIterator {
    public:
        N3NeighborIterator(const Solution&);
        N3NeighborIterator(const Solution&, const std::size_t, const std::size_t);
        std::optional<Solution> get_next() override;
    private:
        void _advance_to_next() override;
    private:
        std::vector<unsigned> _active_node_indices;
        std::vector<unsigned> _inactive_node_indices;
        std::size_t _i;
        std::size_t _j;
        std::size_t _active_node_index;
        std::size_t _inactive_node_index;
};
