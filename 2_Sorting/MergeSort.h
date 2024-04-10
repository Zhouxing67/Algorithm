#ifndef MERGE_SORT_INCLUDE_H
#define MERGE_SORT_INCLUDE_H
#include "Base_sort.h"

namespace alg4
{
    class MergeSort {
    private:
        template<typename T>
        static void merge(T nums[], T temp[], size_t l, size_t mid, size_t r, comparableFunc<T> comp)
        {
            for (size_t i = l; i <= r; i++)
                temp[i] = nums[i];
            size_t j = l, k = mid + 1;

            for (size_t i = l; i <= r; i++) {
                if (j > mid)
                    nums[i] = temp[k++];
                else if (k > r)
                    nums[i] = temp[j++];
                else if (comp(temp[j], temp[k]))
                    nums[i] = temp[j++];
                else
                    nums[i] = temp[k++];
            }
        }
        template<typename T>
        static void sort(T nums[], T temp[], size_t l, size_t r, comparableFunc<T> comp)
        {
            if (l >= r)
                return;
            size_t mid = l + (r - l) / 2;

            sort<T>(nums, temp, l, mid, comp);
            sort<T>(nums, temp, mid + 1, r, comp);

            merge<T>(nums, temp, l, mid, r, comp);
        }

    public:
        template<typename T>
        static void merge_sort(T nums[], size_t size, comparableFunc<T> comp = std::less<T>())
        {
            T* temp = new T[size];
            sort<T>(nums, temp, 0, size - 1, comp);
            delete temp;
        }

    };
}
#endif