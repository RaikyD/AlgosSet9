#include "StringQuickSort.h"
#include "StringUtils.h"
#include "StringSortTester.h"

#include <algorithm>
#include <vector>
#include <string>

void quickSort3Way(std::vector<std::string>& a, int lo, int hi, std::size_t d) {
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
    quickSort3Way(a, lo, lt - 1, d);
    if (v >= 0) quickSort3Way(a, lt, gt, d + 1);
    quickSort3Way(a, gt + 1, hi, d);
}
