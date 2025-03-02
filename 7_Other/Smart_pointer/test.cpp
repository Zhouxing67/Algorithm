#include"shareptr.h"
#include "uniqueptr.h"
#include<iostream>
#include<vector>

template <typename ValueType>
struct customDeleter
{
    void operator()(ValueType *ptr) const

    {
        std::cout << "Custom deleter called" << std::endl;
        delete ptr;
    }
};

int main()
{
    /*
    shareptr<int> sh(new int(1));
    std::cout << *sh <<std::endl;
    shareptr<int, customDeleter<int>> sh1(new int(3), customDeleter<int>());

    uniqueptr<int> unq(new int(1));
    ++*unq;
    std::cout << *unq << std::endl;

    uniqueptr<int, customDeleter<int>> unq1(new int(2), customDeleter<int>());

    uniqueptr<int> unq2;
    unq2 = std::move(unq);
    std::cout << *unq2 << std::endl;*/

    std::vector<shareptr<int>> vet(10, shareptr<int>(new int(3)));
    for (auto i = 0; i < 10;i++)
    {
        //std::cout << *vet[i] << std::endl;
        vet[i].displayTimes();
    }

}