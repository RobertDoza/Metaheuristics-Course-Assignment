#pragma once

#include <deque>

#include "solution.hpp"

#define TABU_LIST_SIZE 10

struct TabuListEntry {
    Solution solution;
    std::size_t order;
};

class TabuList {
    public:
        static void clear();
        static void add(const Solution&);
        static std::string to_string();
    private:
        static TabuList& get();
        TabuList();
        TabuList(const TabuList&) = delete;
        TabuList& operator=(const TabuList&) = delete;
        void _add(const Solution&);
        void _clear();
        std::string _to_string() const;
    private:
        std::size_t _size;
        std::size_t _counter;
        std::deque<TabuListEntry> _entries;
};
