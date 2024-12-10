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
