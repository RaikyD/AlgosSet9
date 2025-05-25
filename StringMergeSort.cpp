#include "StringMergeSort.h"
#include "StringSortTester.h"

#include <algorithm>
#include <string>
#include <cstddef>

static std::size_t lcp(const std::string &a, const std::string &b) {
    std::size_t n = std::min(a.size(), b.size()), i = 0;
    while (i < n) {
        ++charComparisons;
        if (a[i] != b[i]) break;
        ++i;
    }
    return i;
}


static bool lcpCompare(const std::string &a, const std::string &b) {
    std::size_t len = lcp(a, b);
    if (len == a.size() || len == b.size()) {
        ++charComparisons;
        return a.size() < b.size();
    }
    ++charComparisons;
    return a[len] < b[len];
}

void mergeSort(std::vector<std::string> &a,
               std::vector<std::string> &buf,
               std::size_t left,
               std::size_t right) {
    if (right - left <= 1) return;
    std::size_t mid = left + (right - left) / 2;
    mergeSort(a, buf, left, mid);
    mergeSort(a, buf, mid, right);

    std::size_t i = left, j = mid, k = left;
    while (i < mid && j < right) {
        if (lcpCompare(a[i], a[j])) {
            buf[k++] = std::move(a[i++]);
        } else {
            buf[k++] = std::move(a[j++]);
        }
    }
    while (i < mid) buf[k++] = std::move(a[i++]);
    while (j < right) buf[k++] = std::move(a[j++]);
    for (std::size_t t = left; t < right; ++t) {
        a[t] = std::move(buf[t]);
    }
}
