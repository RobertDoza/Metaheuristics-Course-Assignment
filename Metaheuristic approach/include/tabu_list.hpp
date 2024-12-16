#pragma once

#include <deque>

#include "solution.hpp"
#include "movement.hpp"

#define TABU_LIST_SIZE 10
#define MOV_TL_SIZE 15

struct TabuListEntry {
    Solution solution;
    std::size_t order;
};

class TabuList {
    public:
        static void add(const Solution&);
        static bool contains(const Solution&);
        static void clear();
        static void remove(const Solution&);
        static std::string to_string();
    private:
        static TabuList& get();
        TabuList();
        TabuList(const TabuList&) = delete;
        TabuList& operator=(const TabuList&) = delete;
        void _add(const Solution&);
        bool _contains(const Solution&);
        void _clear();
        void _remove(const Solution&);
        std::string _to_string() const;
    private:
        std::size_t _size;
        std::size_t _counter;
        std::deque<TabuListEntry> _entries;
};

class MovementTabuList {
    public:
        static void add(const Movement&);
        static bool contains(const Movement&);
        static void clear();
        static void remove(const Movement&);
        static std::string to_string();
    private:
        static MovementTabuList& _get();
        MovementTabuList();
        MovementTabuList(const MovementTabuList&) = delete;
        MovementTabuList& operator=(const MovementTabuList&) = delete;
        void _add(const Movement&);
        bool _contains(const Movement&);
        void _clear();
        void _remove(const Movement&);
        std::string _to_string() const;
    private:
        std::size_t _size;
        std::deque<Movement> _entries;
};
