#include "StringGenerator.h"
#include <algorithm>

const std::string StringGenerator::alphabet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#%:;^&*()-";

StringGenerator::StringGenerator(unsigned seed)
        : eng(seed),
          dist_len(10, 200),
          dist_char(0, static_cast<int>(alphabet.size()) - 1)
{}

std::vector<std::string> StringGenerator::randomStrings(std::size_t N) {
    std::vector<std::string> a; a.reserve(N);
    for (std::size_t i = 0; i < N; ++i)
        a.push_back(randomString());
    return a;
}

std::vector<std::string> StringGenerator::reversed(const std::vector<std::string>& base) {
    auto a = base;
    std::sort(a.begin(), a.end(), std::greater<std::string>());
    return a;
}

std::vector<std::string> StringGenerator::nearlySorted(const std::vector<std::string>& base,
                                                       std::size_t swaps) {
    auto a = base;
    std::sort(a.begin(), a.end());
    std::uniform_int_distribution<std::size_t> dist_pos(0, a.size() - 1);
    for (std::size_t i = 0; i < swaps; ++i) {
        auto x = dist_pos(eng), y = dist_pos(eng);
        std::swap(a[x], a[y]);
    }
    return a;
}

std::vector<std::string> StringGenerator::withCommonPrefix(std::size_t N,
                                                           std::size_t prefixLen) {
    std::string P; P.reserve(prefixLen);
    for (std::size_t i = 0; i < prefixLen; ++i)
        P.push_back(alphabet[dist_char(eng)]);
    auto a = randomStrings(N);
    for (auto &s : a) s = P + s;
    return a;
}

std::string StringGenerator::randomString() {
    int L = dist_len(eng);
    std::string s; s.reserve(L);
    for (int i = 0; i < L; ++i)
        s.push_back(alphabet[dist_char(eng)]);
    return s;
}
