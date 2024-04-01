#ifndef SORT_TEST_UTIL
#define SORT_TEST_UTIL
#include <cstddef>
#include <stdexcept>
#include <random>
#include <ctime>
using std::size_t;

const size_t DEAFAULT_LEN = 10000;


template<typename T>
bool isSorted(const T arr[], size_t size = DEAFAULT_LEN)
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
void generateRandomArray(T arr[], T minVal, T maxVal, size_t size = DEAFAULT_LEN)
{
    for (size_t i = 0; i < size; ++i) {
        static std::mt19937 generator(time(0));
        static std::uniform_int_distribution<int> distribution(minVal, maxVal);
        arr[i] = distribution(generator);
    }
}


#endif