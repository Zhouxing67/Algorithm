#ifndef DELETE
#define DELETE
#include <iostream>
template <typename ValueType>
struct DefaultDeleter
{
    void operator()(ValueType *ptr) const
    {
        std::cout << "Default deleter called" << std::endl;
        delete ptr;
    }
};
#endif