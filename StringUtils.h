#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <cstddef>

inline int charAt(const std::string &s, std::size_t d) {
    return (d < s.size()) ? static_cast<unsigned char>(s[d]) : -1;
}

#endif