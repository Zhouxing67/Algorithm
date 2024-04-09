#include"Insertion.h"
#include "Util_test_sort.h"
#include "../time_record.h"

using namespace alg4;
int main()
{
    const int len = 30000;
    int* randow_ = new int[len];
    RangeType<int> range{ 0, 100 };

    sort_util::sort_test(randow_, range, sortFunc<int>(&Insertion::shell_sort<int>), len);

    sort_util::sort_test(randow_, range, sortFunc<int>(&Insertion::insert_sort<int>), len);

    delete[] randow_;
}
