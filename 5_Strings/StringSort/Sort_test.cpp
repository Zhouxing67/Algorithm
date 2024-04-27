#include"CountSort.h"
#include"Quick3WayString.h"
#include"../../2_Sorting/Util_test_sort.h"
#include"../../alg4def.h"
#include <algorithm>
using namespace alg4::str;
using namespace alg4::util;

int main()
{
    {
        size_t size = 100;
        unsigned int* data = new unsigned int[size];
        sort_util::generateRandomArray(data, genUintRange(size), size);
        CountSort::sort(data, size);
        sort_util::checkArrayisSorted(data, size);
    }
    {
        std::vector<string> data(20, " ");
        data[0] = "apple";
        data[1] = "banana";
        data[2] = "orange";
        data[3] = "grape";
        data[4] = "watermelon";
        data[5] = "pineapple";
        data[6] = "strawberry";
        data[7] = "kiwi";
        data[8] = "blueberry";
        data[9] = "mango";
        data[10] = "peach";
        data[11] = "cherry";
        data[12] = "pear";
        data[13] = "plum";
        data[14] = "apricot";
        data[15] = "lemon";
        data[16] = "lime";
        data[17] = "coconut";
        data[18] = "papaya";
        data[19] = "fig";

        Quick3WayString::quick3WayString_sort(data);
        cout << std::is_sorted(data.begin(), data.begin() + data.size());
    }
}