#ifndef INSERTION_H_INCLUDED
#define INSERTION_H_INCLUDED
#include "../base_include.h"
#include "Base_sort.h"
namespace alg4
{
    class Insertion {
        //class 默认private
    public:
        template<typename T>
        static void insert_sort(T nums[], size_t len, comparableFunc<T> comp = std::less<T>())
        {
            for (size_t i = 1; i < len; i++) {
                size_t j = i;
                T val = nums[i];
                for (; j >= 1 && comp(val, nums[j - 1]); j--)
                    nums[j] = nums[j - 1];
                nums[j] = val;
            }
        }

        template<typename T>
        static void shell_sort(T nums[], size_t len, comparableFunc<T> comp = std::less<T>())
        {
            int step = 1;
            while (step < len / 3)
                step = step * 3 + 1;

            while (step > 0) {
                for (size_t i = 1; i < len; i++) {
                    T val = nums[i];
                    size_t j = i;
                    for (; j >= step && comp(val, nums[j - step]); j -= step)
                        nums[j] = nums[j - step];
                    nums[j] = val;
                }
                step /= 3;
            }

        }
    };
}

#endif // INSERTION_H_INCLUDED
