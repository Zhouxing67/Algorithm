#ifndef QUICK3WAY_H_INCLUDED
#define QUICK3WAY_H_INCLUDED
#include"Base_sort.h"
/*
三向快速排序
每次递归将 小数组首元素相同的元素放在相邻位置

优点:
对于大量重复的元素的数组排序 优于传统快排
*/

namespace alg4::sort
{
    class QuickSort {
    private:
        template<typename T>
        static void q3sort(T nums[], pos_t lo, pos_t hi, comparableFunc<T> comp)
        {
            if (lo >= hi)
                return;
            size_t lt = lo, gt = hi, i = lo + 1;

            T pivot = nums[lo];
            while (i <= gt) {
                if (comp(nums[i], pivot))
                    std::swap(nums[lt++], nums[i++]);
                else if (comp(pivot, nums[i]))
                    std::swap(nums[i], nums[gt--]);
                else
                    i++;
            }
            //得到  nums[lo..lt-1] < pivot=nums[lt..gt] < nums[gt+1...hi]
            q3sort(nums, lo, lt - 1, comp);
            q3sort(nums, gt + 1, hi, comp);
        }

        template<typename T>
        static pos_t partition(T nums[], pos_t lo, pos_t hi, comparableFunc<T> comp)
        {
            T pivot = nums[lo];
            pos_t i = lo, j = hi + 1;
            while (i < j) {
                //循环条件：nums[i] < pivot，同时 i <= hi
                while (++i <= hi && comp(nums[i], pivot));
                //循环条件：nums[j] > pivot，同时 j >= lo
                while (--j >= lo && comp(pivot, nums[j]));

                if (i < j)
                    std::swap(nums[i], nums[j]);
            }
            //循环结束后i == j吗
            std::swap(nums[j], pivot);
            return j;
        }

        template<typename T>
        static void qsort(T nums[], pos_t lo, pos_t hi, comparableFunc<T> comp)
        {
            if (lo >= hi)
                return;
            pos_t j = partition(nums, lo, hi, comp);
            
            qsort(nums, lo, j - 1, comp);
            qsort(nums, j + 1, hi, comp);
        }

    public:
        template<typename T>
        static void q3sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            q3sort(nums, 0, size - 1, comp);
        }

        template<typename T>
        static void qsort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            qsort(nums, 0, size - 1, comp);
        }
    };
}


#endif // QUICK3WAY_H_INCLUDED
