#include <sstream>
#include <algorithm>

#include "tabu_list.hpp"

void TabuList::add(const Solution& s) {
    get()._add(s);
}

bool TabuList::contains(const Solution& s) {
    return get()._contains(s);
}

void TabuList::clear() {
    get()._clear();
}

void TabuList::remove(const Solution& s) {
    get()._remove(s);
}

std::string TabuList::to_string() {
    return get()._to_string();
}

TabuList& TabuList::get() {
    static TabuList tabu_list;
    return tabu_list;
}

TabuList::TabuList()
    :_size(TABU_LIST_SIZE), _counter(0)
{}

void TabuList::_add(const Solution& s) {
    _entries.push_front({s, _counter});
    _counter = (_counter + 1) % _size;

    if (_entries.size() > _size) {
        _entries.pop_back();
    }
}

bool TabuList::_contains(const Solution& solution) {
    auto it = std::find_if(_entries.begin(), _entries.end(),
        [&solution](const TabuListEntry& entry) {
            return entry.solution == solution;
        });
    return it != _entries.end();
}

void TabuList::_clear() {
    _entries.clear();
}

void TabuList::_remove(const Solution& solution) {
    _entries.erase(std::remove_if(_entries.begin(), _entries.end(),
        [&solution](const TabuListEntry& entry) {
            return entry.solution == solution;
        }),
        _entries.end()
    );
}

std::string TabuList::_to_string() const {
    std::size_t size = _entries.size();

    if (size == 0) {
        return "<empty>";
    }

    std::stringstream buffer;

    buffer << "[\n";

    for (size_t i = 0; i < size - 1; i++) {
        buffer << _entries[i].order << ")" << _entries[i].solution << ",\n";
    }
    buffer <<  _entries[size - 1].order << ")" << _entries[size - 1].solution << "\n";

    // buffer << "]";
    buffer << "]\n";

    buffer << "[";

    size_t i;
    for (i = 0; i < size; i++) {
        buffer << "#";
    }
    for (; i < TABU_LIST_SIZE; i++) {
        buffer << " ";
    }

    buffer << "]";

    return buffer.str();
}
