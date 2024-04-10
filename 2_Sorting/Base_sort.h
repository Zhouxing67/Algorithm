#ifndef SORT_BASE_INCLUDE_H
#define SORT_BASE_INCLUDE_H
#include<functional>
namespace alg4
{
    template<typename T>
    using comparableFunc = std::function<bool(T, T)>;

    template<typename T>
    using sortFunc = std::function<void(T[], size_t, comparableFunc<T>)>;

    // using size_t = unsigned long long;
    using std::size_t;
}
#endif