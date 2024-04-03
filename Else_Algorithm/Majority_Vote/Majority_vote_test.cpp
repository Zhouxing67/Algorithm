#include <iostream>
#include <vector>
#include "Majority.h"

int main()
{
    std::vector<int> data = { 1, 2, 2, 2, 3, 2, 3, 3, 3 }; // 示例数据
    int n = 2; // 要找出的主要元素个数

    alg4::Majority majorityFinder(data, n);

    const int* majority = majorityFinder.get_majority();

    std::cout << "找到的主要元素为：";
    for (int i = 0; i < n; i++) {
        std::cout << majority[i] << " ";
    }

    return 0;
}
