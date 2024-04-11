#ifndef SIMPLE_SORT_INCLUDE_H
#define SIMPLE_SORT_INCLUDE_H
#include "Base_sort.h"
namespace alg4::sort
{
    class SimpleSort {
    public:
        template<typename T>
        static void bubble_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            for (size_t i = 0; i < size - 1; i++) {
                bool isswaped = false;
                for (size_t j = 0; j < size - i - 1; j++) {
                    if (comp(nums[j + 1], nums[j]))
                    {
                        std::swap(nums[j], nums[j + 1]);
                        isswaped = true;
                    }
                }
                if (!isswaped)
                    return;
            }
        }

        template<typename T>
        static void insert_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            for (size_t i = 1; i < size; i++) {
                size_t j = i;
                T val = nums[i];
                for (; j >= 1 && comp(val, nums[j - 1]); j--)
                    nums[j] = nums[j - 1];
                nums[j] = val;
            }
        }

        template<typename T>
        static void shell_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            int step = 1;
            while (step < size / 3)
                step = step * 3 + 1;

            while (step > 0) {
                for (size_t i = 1; i < size; i++) {
                    T val = nums[i];
                    size_t j = i;
                    for (; j >= step && comp(val, nums[j - step]); j -= step)
                        nums[j] = nums[j - step];
                    nums[j] = val;
                }
                step /= 3;
            }

        }

        template<typename T>
        static void select_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            for (size_t i = 0; i < size; i++) {
                size_t min = i;
                for (int j = i + 1; j < size; j++)
                    min = comp(nums[j], nums[min]) ? j : min;
                std::swap(nums[i], nums[min]);
            }
        }
    };
}

#endif