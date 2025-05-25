#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "StringGenerator.h"
#include "StringSortTester.h"
#include "StringMergeSort.h"
#include "StringQuickSort.h"
#include "MsdRadixSort.h"
#include "MsdRadixQuickSort.h"

int main() {
    StringGenerator gen;
    auto baseRandom   = gen.randomStrings(3000);
    auto baseReversed = gen.reversed(baseRandom);
    auto baseNearly   = gen.nearlySorted(baseRandom, 150);

    std::vector<std::vector<std::string>> dataSets = {
            baseRandom,
            baseReversed,
            baseNearly
    };
    std::vector<std::string> labels = {
            "Random",
            "Reversed",
            "NearlySorted"
    };
    std::vector<std::size_t> sizes;
    for (std::size_t n = 100; n <= 3000; n += 100) {
        sizes.push_back(n);
    }

    using SortFunc = StringSortTester::SortFunc;

    SortFunc stdQS = [](auto begin, auto end, auto cmp) {
        std::sort(begin, end, cmp);
    };
    SortFunc stdMS = [](auto begin, auto end, auto cmp) {
        std::stable_sort(begin, end, cmp);
    };
    SortFunc triQS = [](auto begin, auto end, auto ) {
        std::vector<std::string> tmp(begin, end);
        if (!tmp.empty()) {
            quickSort3Way(tmp, 0, static_cast<int>(tmp.size()) - 1, 0);
        }
        std::copy(tmp.begin(), tmp.end(), begin);
    };

    SortFunc strMS = [](auto begin, auto end, auto cmp) {
        std::vector<std::string> tmp(begin, end);
        std::vector<std::string> buf(tmp.size());
        mergeSort(tmp, buf, 0, tmp.size());
        std::copy(tmp.begin(), tmp.end(), begin);
    };
    SortFunc msd   = [](auto begin, auto end, auto cmp) {
        std::vector<std::string> tmp(begin, end);
        std::vector<std::string> aux(tmp.size());
        msdRadixSort(tmp, aux, 0, tmp.size(), 0);
        std::copy(tmp.begin(), tmp.end(), begin);
    };
    SortFunc msd_qs = [](auto begin, auto end, auto cmp) {
        std::vector<std::string> tmp(begin, end);
        std::vector<std::string> aux(tmp.size());
        msdRadixQuick(tmp, aux, 0, tmp.size(), 0);
        std::copy(tmp.begin(), tmp.end(), begin);
    };

    std::vector<std::pair<std::string, SortFunc>> algs = {
            {"StdQuickSort", stdQS},
            {"StdMergeSort", stdMS},
            {"3WayQuickSort", triQS},
            {"StringMergeSort", strMS},
            {"MSDRadixSort", msd},
            {"MSDRadix+Quick", msd_qs}
    };


    StringSortTester tester;
    tester.runAllTests(sizes, dataSets, labels, algs, 5);

    return 0;
}
