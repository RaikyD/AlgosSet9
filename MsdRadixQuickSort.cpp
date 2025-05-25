#include "MsdRadixQuickSort.h"
#include "StringUtils.h"
#include "StringSortTester.h"

#include <vector>
#include <string>
#include <cstddef>

static void quick3(std::vector<std::string>& a, int lo, int hi, std::size_t d) {
    if (lo >= hi) return;
    int lt = lo, gt = hi;
    int v = charAt(a[lo], d);
    int i = lo + 1;
    while (i <= gt) {
        int t = charAt(a[i], d);
        ++charComparisons;
        if (t < v) {
            std::swap(a[lt++], a[i++]);
        } else {
            ++charComparisons;
            if (t > v) {
                std::swap(a[i], a[gt--]);
            } else {
                ++charComparisons;
                ++i;
            }
        }
    }
    quick3(a, lo, lt - 1, d);
    if (v >= 0) quick3(a, lt, gt, d + 1);
    quick3(a, gt + 1, hi, d);
}

void msdRadixQuick(std::vector<std::string> &a,
                   std::vector<std::string> &aux,
                   std::size_t lo,
                   std::size_t hi,
                   std::size_t d) {
    const std::size_t threshold = 74;
    if (hi <= lo + 1) return;
    if (hi - lo < threshold) {
        quick3(a, static_cast<int>(lo), static_cast<int>(hi) - 1, d);
        return;
    }
    const std::size_t R = 256;
    std::vector<std::size_t> count(R + 2, 0);
    for (std::size_t i = lo; i < hi; ++i)
        ++count[charAt(a[i], d) + 1];
    for (std::size_t r = 0; r <= R; ++r)
        count[r + 1] += count[r];
    for (std::size_t i = lo; i < hi; ++i)
        aux[count[charAt(a[i], d)]++] = std::move(a[i]);
    for (std::size_t i = lo; i < hi; ++i)
        a[i] = std::move(aux[i - lo]);
    std::size_t start = lo;
    for (std::size_t r = 0; r <= R; ++r) {
        std::size_t end = lo + count[r];
        if (start < end)
            msdRadixQuick(a, aux, start, end, d + 1);
        start = end;
    }
}
