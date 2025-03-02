#include"CountSort.h"
#include "Util_test_sort.h"
using namespace alg4::sort;
using namespace alg4::util;
using namespace alg4;

int main()
{
    unsigned int max = 999;
    size_t len = 100000;
    auto range = genUintRange(max);
    unsigned int* data = new unsigned int[len];

    sort_util::generateRandomArray(data, range,len);
    count_sort(data, len, max);
    auto cmp = [](unsigned  int l, unsigned  int r) {return l < r; };

    sort_util::checkArrayisSorted(data, len);

}