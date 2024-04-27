#ifndef COUNTSORT_INCLUDE_H
#define COUNTSORT_INCLUDE_H
#include <stddef.h>
#include <cstring>
namespace alg4::str
{
    class CountSort {
    public:
        static void sort(unsigned int arr[], size_t len)
        {
            size_t count_size = max(arr, len) + 2;
            unsigned int* count = new unsigned int[count_size] {0};
            unsigned int* aux = new unsigned int[len];

           // memset(count, 0, sizeof(unsigned int) * (count_size));
            //注意这里是arr[i] + 1;
            for (size_t i = 0; i < len; i++)
                count[arr[i] + 1]++;
            for (size_t i = 1; i < count_size; i++)
                count[i] += count[i - 1];
            //现在count[i] 表示值为i的元素在有序序列的位置
            for (size_t i = 0; i < len; i++)
                aux[count[arr[i]]++] = arr[i];
            for (size_t i = 0; i < len; i++)
                arr[i] = aux[i];

           //count[103] = 1;越界访问
            delete[] count;
            delete[] aux;
        }
    private:

        static unsigned int max(unsigned int arr[], size_t len)
        {

            unsigned int res = arr[0];
            for (size_t i = 1; i < len; i++)
                res = arr[i] > res ? arr[i] : res;
            return res;
        }
    };
}
#endif