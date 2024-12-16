#include "movement.hpp"

bool Movement::operator==(const Movement &other) const {
    return this->activated_facility == other.activated_facility && this->deactivated_facility == other.deactivated_facility;
}

std::string Movement::to_string() const {
    return std::to_string(deactivated_facility) + " -> " + std::to_string(activated_facility);
}

std::ostream& operator<<(std::ostream& out, const Movement& movement) {
    out << movement.to_string();
    return out;
}
