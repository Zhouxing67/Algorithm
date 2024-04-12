#ifndef HEAPSORT_H_INCLUDED
#define HEAPSORT_H_INCLUDED
#include"../base_include.h"
#include"../alg4def.h"

/*
堆排序
1.构建有序堆(最大堆)
2.不断取出maxVal,在重新有序化即可
3.直到堆中不存在新元素

note:有序化API
swim 上浮
sink 下沉
*/

//e.g.   1....n序号的数组进行排序
namespace alg4::sort
{
    class HeapSort {
    public:
        template<typename T>
        static void heap_sort(T nums[], size_t size, comparableFunc<T> comp = std::less<T>())
        {
            //堆有序
            for (size_t k = size / 2; k >= 1; k--)
                sink(nums, k, size, comp);
            while (size > 1) {
                //最大值放在数组后面保存
                swap(nums, 1, size--);
                //保证堆有序
                sink(nums, 1, size, comp);
            }
        }
    private:
        //父节点k 不断下沉  直到k大于两个子节点
        template<typename T>
        static void sink(T nums[], size_t k, size_t size, comparableFunc<T> comp)
        {
            while (2 * k <= size) {
                //k的子节点2k 2k+1中val较大值为j
                size_t j = 2 * k;
                if (j < size && compare(nums, j, j + 1, comp))
                    j++;
                if (!compare(nums, k, j, comp))
                    break;
                swap(nums, k, j);
                k = j;
            }
        }

        //helper function
        //由于数组由0开始作为需要标记
        template<typename T>
        static void swap(T nums[], size_t i, size_t j)
        {
            std::swap(nums[i - 1], nums[j - 1]);
        }

        template<typename T>
        static bool compare(T nums[], size_t i, size_t j, comparableFunc<T> comp)
        {
            return comp(nums[i - 1], nums[j - 1]);
        }
    };
}


#endif 
