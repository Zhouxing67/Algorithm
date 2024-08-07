#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include"type_def.h"
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
            //循环不变量：
            //(lt <= k < i) nums[k] == pivot
            //(j >= gt + 1) nums[j] > pivot
            //nums[i], nums[gt]与pivot的大小关系未知
            while (i <= gt) {
                if (comp(nums[i], pivot))
                    std::swap(nums[lt++], nums[i++]);
                else if (comp(pivot, nums[i]))
                    std::swap(nums[i], nums[gt--]);
                else
                    i++;
            }
            //循环结束后，gt < i
            //得到  nums[lo...lt-1] < pivot=nums[lt...gt] < nums[gt+1...hi]
            q3sort(nums, lo, lt - 1, comp);
            q3sort(nums, gt + 1, hi, comp);
        }
        //partition的意义：
        //1.一次划分操作将确定一个元素在序列里的位置。同时可以将区间分为不相交的两个部分
        //2. 对于一次划分的返回结果j: i < j < k, 则nums[i] < nums[j] == pivot < nums[K];
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
            std::swap(nums[j], nums[lo]);
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
        static void quick3way_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            q3sort(nums, 0, size - 1, comp);
        }

        template<typename T>
        static void quick_sort(T nums[], const size_t size, comparableFunc<T> comp = std::less<T>())
        {
            qsort(nums, 0, size - 1, comp);
        }
    };
}


#endif // QUICK3WAY_H_INCLUDED
