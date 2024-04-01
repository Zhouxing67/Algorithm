#include"Insertion.h"
#include "sort_test_util.h"

int main()
{
    int randow_[10000] = { 0 };
    generateRandomArray(randow_, 1, 99999);
    Insertion::insort(randow_, 10000);
    cout << isSorted(randow_);
}
