#include <functional>
using std::function;

int add(int a, int b);

double add(double a, double b);

std::function<int(int, int)> f(static_cast<int(*)(int, int)>(add));

int (*func_ptr)(int, int) = add;
std::function<int(int, int)> f(func_ptr);