#include <sstream>

#include "tabu_list.hpp"

void TabuList::clear() {
    get()._clear();
}

void TabuList::add(const Solution& s) {
    get()._add(s);
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

void TabuList::_clear() {
    _entries.clear();
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

    buffer << "]";

    return buffer.str();
}
