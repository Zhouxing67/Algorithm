#include <iostream>
#include "Hash.h"
#include "LinearProbingHash.h"

int main()
{
    // 创建一个哈希表实例
    alg4::search::LinearHash <int, std::string> hashTable;

    // 插入一些键值对
    hashTable.put(1, "One");
    hashTable.put(2, "Two");
    hashTable.put(3, "Three");

    // 测试获取操作
    std::cout << "Value for key 1: " << *hashTable.get(1) << std::endl;
    std::cout << "Value for key 2: " << *hashTable.get(2) << std::endl;
    std::cout << "Value for key 3: " << *hashTable.get(3) << std::endl;

    // 测试删除操作
    hashTable.del(2);
    std::cout << "After deleting key 2, value for key 2: ";
    try {
        std::cout << (hashTable.get(2)  == nullptr ? "no key" : " error")<< std::endl;
    }
    catch (...) {
        std::cout << "Key not found" << std::endl;
    }

    return 0;
}
