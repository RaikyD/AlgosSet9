#ifndef SET9_STRINGSORTTESTER_H
#define SET9_STRINGSORTTESTER_H

#include <vector>
#include <string>
#include <functional>
#include <cstdint>

extern std::uint64_t charComparisons;

struct CountingComparator {
    bool operator()(const std::string& a, const std::string& b) const;
};

class StringSortTester {
public:
    using SortFunc = std::function<void(
            std::vector<std::string>::iterator,
            std::vector<std::string>::iterator,
            const CountingComparator&)>;

    void runAllTests(const std::vector<std::size_t>& sizes,
                     const std::vector<std::vector<std::string>>& dataSets,
                     const std::vector<std::string>& labels,
                     const std::vector<std::pair<std::string, SortFunc>>& algorithms,
                     int trials = 5);
};

#endif // SET9_STRINGSORTTESTER_H
