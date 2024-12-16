#pragma once

#include <string>
#include <ostream>

struct Movement {
    unsigned long deactivated_facility;
    unsigned long activated_facility;

    bool operator==(const Movement&) const;

    std::string to_string() const;
};

std::ostream& operator<<(std::ostream&, const Movement&);
