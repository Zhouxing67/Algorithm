#ifndef COUNTSORT_H
#define COUNTSORT_H

#include"type_def.h"
namespace alg4::sort
{
    void count_sort(unsigned int arr[], int len, int max)
    {
        unsigned int tmp[max + 1] = { 0 };
        for (int i = 0; i != len; i++)
            tmp[arr[i]]++;
        for (int i = 0, cur = 0; i != max + 1; i++)
        {
            while(tmp[i] != 0)
            {
                arr[cur++] = i;
                tmp[i]--;
            }
        }
    }
}
#endif