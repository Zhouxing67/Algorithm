#include "Allocator.h"
#include <cinttypes>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
using mtd::Allocator;
int main()
{
    std::vector<int, Allocator<int>> v(0);

    for (size_t i = 0; i < 30; i++)
    {
        sleep(1);
        v.push_back(i);
        //auto n = v.get_allocator().get_alloc_count_();
        //std::cout << "Cost:" <<  n << std::endl;
    }
}