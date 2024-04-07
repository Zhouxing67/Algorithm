#include <iostream>
#include "LinkList.h"

using namespace alg4;
int main()
{
    alg4::LinkList<int> myList;

    // 插入元素
    myList.insert(1, 0);
    myList.insert(2, 1);
    myList.insert(3, 2);
    myList.append(4);

    for (int i = 0; i < myList.len(); i++)
    {
        std::cout << myList[i] << ' ';
    }
    std::cout << std::endl;

    // 删除元素
    myList.remove(1);

    // 访问元素
    std::cout << "第一个元素：" << myList[0] << std::endl;
    std::cout << "第二个元素：" << myList[1] << std::endl;
    std::cout << "第三个元素：" << myList.at(2) << std::endl;
}
