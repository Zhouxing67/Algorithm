#ifndef UTIL_SORT_H
#define UTIL_SORT_H

#include <cstddef>
#include <stdexcept>
#include <random>
#include <ctime>
#include "../time_record.h"
#include "../type_def.h"
#include "../color_def.h"
#include <algorithm>

using std::size_t;

namespace alg4::util
{
    const size_t DEAFAULT_LEN = 1000000;

    template<typename T>
    using RangeType = std::pair<T, T>;

    const RangeType<int> DEAFAULT_INT_RANGE{ -999999, 999999 };
    const RangeType<double> DEAFAULT_DOUBLE_RANGE{ -999999.0, 999999.0 };
    const RangeType<float> DEAFAULT_FLOAT_RANGE{ -9999.0f, 9999.0f };
    const RangeType<char> DEAFAULT_CHAR_RANGE{ -128, 127 };

    RangeType<unsigned int> genUintRange(unsigned max) { return { 0, max }; }

    class sort_util {
    public:
    
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
        static void sort_test(T arr[], RangeType<T> range, sortFunc<T> sort, size_t size = DEAFAULT_LEN, comparableFunc<T> comp = std::less<T>())
        {
            static size_t times = 0;
            times++;
            std::cout << "The " << times << " times test     ";

            generateRandomArray(arr, range, size);
            {
                time_recorder recorder;
                sort(arr, size, comp);
            }
            checkisSorted(arr, size);
        }

         template<typename T>
         static void checkArrayisSorted(T* arr, size_t size, comparableFunc<T> comp = std::less<T>())
         {
             bool issorted = std::is_sorted(arr, arr + size, comp);
             if (issorted)
                 std::cout << "Issorted : " << ANSI_COLOR_GREEN << "True" << ANSI_COLOR_RESET << std::endl;
             else
                 std::cout << "Issorted : " << ANSI_COLOR_RED << "False" << ANSI_COLOR_RESET << std::endl;
         }
    };
}


#endif