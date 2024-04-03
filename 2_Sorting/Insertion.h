#ifndef INSERTION_H_INCLUDED
#define INSERTION_H_INCLUDED
#include "../base_include.h"
class Insertion {
    //class 默认private
public:
    static void insort(int nums[], int len)
    {
        for (int i = 1; i < len; i++) {
            int j = i, val = nums[i];
            for (; j > 0 && val < nums[j - 1]; j--)
                nums[j] = nums[j - 1];
            nums[j] = val;
        }
    }
};


#endif // INSERTION_H_INCLUDED
