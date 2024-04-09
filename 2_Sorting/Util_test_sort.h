#ifndef SORT_TEST_UTIL
#define SORT_TEST_UTIL

#include <cstddef>
#include <stdexcept>
#include <random>
#include <ctime>
#include "../time_record.h"
#include "Base_sort.h"
using std::size_t;

namespace alg4
{
    const size_t DEAFAULT_LEN = 1000000;
    const RangeType<int> DEAFAULT_INT_RANGE{ -999999, 999999};
    const RangeType<double> DEAFAULT_double_RANGE{ -999999.0, 999999.0 };
    const RangeType<float> DEAFAULT_FLOAT_RANGE{ -9999.0f, 9999.0f };
    const RangeType<char> DEAFAULT_CHAR_RANGE{ -128, 127 };

    class sort_util {
    public:
        
        template<typename T>
        static bool isSorted(const T arr[], size_t size = DEAFAULT_LEN)
        {
            for (size_t i = 1; i < size; ++i) {
                if (arr[i] < arr[i - 1]) {
                    return false;
                }
            }
            return true;
        }
        // 生成指定范围的随机数组
        template<typename T>
        static void generateRandomArray(T arr[], RangeType<T> range, size_t size = DEAFAULT_LEN)
        {
            T minVal = range.first, maxVal = range.second;
            for (size_t i = 0; i < size; ++i) {
                static std::mt19937 generator(time(0));
                static std::uniform_int_distribution<T> distribution(minVal, maxVal);
                arr[i] = distribution(generator);
            }
        }

        template<typename T>
        static void sort_test(T arr[], RangeType<T> range, sortFunc<T> sort, size_t size = DEAFAULT_LEN, comparableFunc<T> comp = std::less<int>())
        {
            generateRandomArray(arr, range, size);
            {
                time_recorder recorder;
                sort(arr, size, comp);
            }
            bool issorted = isSorted(arr, size);
            std::cout << "Issorted :" << (issorted ? "true" : "false") << std::endl;
        }
    };
}


#endif