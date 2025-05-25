#include "StringSortTester.h"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <string>

std::uint64_t charComparisons = 0;

bool CountingComparator::operator()(const std::string& a, const std::string& b) const {
    std::size_t n = std::min(a.size(), b.size());
    for (std::size_t i = 0; i < n; ++i) {
        ++charComparisons;
        if (a[i] != b[i]) return a[i] < b[i];
    }
    ++charComparisons;
    return a.size() < b.size();
}

void StringSortTester::runAllTests(const std::vector<std::size_t>& sizes,
                                   const std::vector<std::vector<std::string>>& dataSets,
                                   const std::vector<std::string>& labels,
                                   const std::vector<std::pair<std::string, SortFunc>>& algorithms,
                                   int trials)
{
    auto now = std::chrono::system_clock::now();
    auto ms_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()).count();
    std::string filename = "results_" + std::to_string(ms_since_epoch) + ".csv";

    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Error: cannot open file " << filename << " for writing\n";
        return;
    }

    std::cout << "Writing results to " << filename << "\n";
    ofs << "Type,N,Algorithm,Time_ms,CharCmp\n";

    for (std::size_t di = 0; di < dataSets.size(); ++di) {
        std::cout << "\n=== Data: " << labels[di] << " ===\n";
        for (auto N : sizes) {
            std::cout << "N=" << N;
            std::vector<std::string> arr(dataSets[di].begin(), dataSets[di].begin() + N);
            for (auto& alg : algorithms) {
                double totalTime = 0;
                std::uint64_t totalComps = 0;
                for (int t = 0; t < trials; ++t) {
                    auto a = arr;
                    charComparisons = 0;
                    auto start = std::chrono::high_resolution_clock::now();
                    alg.second(a.begin(), a.end(), CountingComparator());
                    auto end = std::chrono::high_resolution_clock::now();
                    totalTime += std::chrono::duration<double, std::milli>(end - start).count();
                    totalComps += charComparisons;
                }
                double avgTime  = totalTime / trials;
                double avgComps = static_cast<double>(totalComps) / trials;

                std::cout << "\n  [" << alg.first << "] "
                          << "time=" << avgTime << "ms "
                          << "charCmp=" << avgComps;

                ofs
                        << labels[di] << ','
                        << N         << ','
                        << alg.first << ','
                        << avgTime   << ','
                        << avgComps  << '\n';
            }
            std::cout << "\n";
        }
    }

    ofs.close();
}
