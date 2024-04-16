#include <cassert>
#include "BST.h"

using namespace alg4::search;

int main()
{
    // 创建二叉搜索树
    BST<int, int> bst;

    // 插入一些键值对
    bst.update(5, 50);
    bst.update(3, 30);
    bst.update(7, 70);
    bst.update(2, 20);
    bst.update(4, 40);
    bst.update(6, 60);
    bst.update(8, 80);

    assert(bst.size() == 7);

    // 测试查找功能
    assert(*bst.find(5) == 50);
    assert(*bst.find(2) == 20);
    assert(bst.find(10) == nullptr); // 不存在的键

    bst.update(5, 40);
    bst.update(2, 10);
    assert(*bst.find(5) == 40);
    assert(*bst.find(2) == 10);

    //测试删除功能
    bst.deleteKey(5);
    assert(bst.find(5) == nullptr);
    assert(bst.size() == 6);
    // 测试最小值功能
    assert(*bst.min() == 2);

    // 测试floor功能
    assert(*bst.floor(3) == 3);
    assert(*bst.floor(9) == 8);

    // 测试select功能
    assert(*bst.select(3) == 6); // 第三小的键是5

    // 测试rank功能
    assert(bst.rank(7) == 4); // 键值7的排名是5

    // 测试删除最小值功能
    bst.deleteMin();
    assert(*bst.min() == 3); // 最小值现在是3

    // 测试清空二叉搜索树
    return 0;
}
