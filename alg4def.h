#ifndef SORT_BASE_INCLUDE_H
#define SORT_BASE_INCLUDE_H
#include <functional>
#include <cstddef>
namespace alg4
{
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
    template<typename T>
    using comparableFunc = std::function<bool(T, T)>;

    template<typename T>
    using sortFunc = std::function<void(T[], size_t, comparableFunc<T>)>;

    // using size_t = unsigned long long;
    using std::size_t;

    using pos_t = long long;

}
#endif