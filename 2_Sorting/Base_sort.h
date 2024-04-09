#ifndef SORT_BASE_INCLUDE_H
#define SORT_BASE_INCLUDE_H
namespace alg4
{
    template<typename T>
    using comparableFunc = std::function<bool(T, T)>;

    template<typename T>
    using sortFunc = std::function<void(T[], size_t, comparableFunc<T>)>;

    template<typename T>
    using RangeType = std::pair<T, T>;
}
#endif