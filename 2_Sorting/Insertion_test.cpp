#include"Insertion.h"
#include "sort_test_util.h"
#include "../time_record.h"

int main()
{
    int* randow_ = new int[DEAFAULT_LEN];
    generateRandomArray(randow_, 1, 99999);

    //test
    {
        time_recorder recorder;
        Insertion::insort(randow_, DEAFAULT_LEN);
    }


    cout << (isSorted(randow_) ? "true" : "false") << endl;
    delete[] randow_;
}
