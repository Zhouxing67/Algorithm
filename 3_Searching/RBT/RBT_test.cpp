#include <iostream>
#include "RBT.h" // 假设你的红黑树类定义在 RBT.h 文件中
#include <cassert>
using namespace alg4::search;
int main()
{
    // 创建一个红黑树对象
    RBT<int, std::string> rbt;

    // 测试插入功能
    rbt.update(1, "One");
    rbt.update(2, "Two");
    rbt.update(3, "Three");
    rbt.update(4, "Four");
    rbt.update(5, "Five");
    rbt.update(6, "Six");
    rbt.update(7, "Seven");
    rbt.update(8, "Eight");

    // 测试查找功能
    assert(*rbt.find(1) == "One");
    assert(*rbt.find(2) == "Two");
    assert(*rbt.find(3) == "Three");
    assert(*rbt.find(4) == "Four");
    assert(*rbt.find(5) == "Five");

    // 测试大小功能
    assert(rbt.size() == 8);

    // 测试更新功能
    rbt.update(2, "New Two");
    assert(*rbt.find(2) == "New Two");

    // 测试删除功能


    // 测试空树情况
    RBT<int, std::string> emptyRBT;
    assert(emptyRBT.find(1) == nullptr);
    assert(emptyRBT.size() == 0);

    std::cout << "All tests passed!" << std::endl;

    return 0;
}