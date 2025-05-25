// File: StringGenerator.h
#ifndef SET9_STRINGGENERATOR_H
#define SET9_STRINGGENERATOR_H

#include <vector>
#include <string>
#include <random>

class StringGenerator {
public:
    explicit StringGenerator(unsigned seed = std::random_device{}());
    std::vector<std::string> randomStrings(std::size_t N);
    std::vector<std::string> reversed(const std::vector<std::string>& base);
    std::vector<std::string> nearlySorted(const std::vector<std::string>& base, std::size_t swaps = 100);
    std::vector<std::string> withCommonPrefix(std::size_t N, std::size_t prefixLen);

private:
    std::string randomString();
    std::mt19937 eng;
    std::uniform_int_distribution<int> dist_len;
    std::uniform_int_distribution<int> dist_char;
    static const std::string alphabet;
};

#endif // SET9_STRINGGENERATOR_H
