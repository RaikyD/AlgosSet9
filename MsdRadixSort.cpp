#include <iostream>
#include <vector>
#include <string>
#include "MsdRadixSort.h"

void msdRadixSort(std::vector<std::string> &a,
                  std::vector<std::string> &aux,
                  std::size_t lo,
                  std::size_t hi,
                  std::size_t d) {
    if (hi <= lo + 1) {
        return;
    }
    const std::size_t R = 256;

    std::vector<std::size_t> count(R + 2, 0);
    for (std::size_t i = lo; i < hi; ++i) {
        int c = charAt(a[i], d);
        count[c + 1]++;
    }

    for (std::size_t r = 0; r <= R; ++r) {
        count[r + 1] += count[r];
    }
    for (std::size_t i = lo; i < hi; ++i) {
        int c = charAt(a[i], d);
        aux[count[c]++] = a[i];
    }
    for (std::size_t i = lo; i < hi; ++i) {
        a[i] = aux[i - lo];
    }
    for (std::size_t r = 0; r <= R; ++r) {
        msdRadixSort(a, aux, lo + count[r], lo + count[r + 1], d + 1);
    }
}
