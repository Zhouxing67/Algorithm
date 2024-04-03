#include <iostream>
#include "LinkList.h"

void compare(const int a)
{
    std::cout << (a == 0) << std::endl;;
}

int main()
{
    mtd::LinkList<int> myList;

    // 插入元素
    myList.insert(1, 0);
    myList.insert(2, 1);
    myList.insert(3, 2);
    myList.append(4);

    //myList.traversal(compare);
    /* std::cout << "链表内容：";
    myList.print();

    // 访问元素
    std::cout << "第一个元素：" << myList[0] << std::endl;
    std::cout << "第二个元素：" << myList[1] << std::endl;
    std::cout << "第三个元素：" << myList.at(2) << std::endl;

    // 删除元素
    myList.remove(1);

    // 打印链表
    std::cout << "删除元素后的链表内容：";
    myList.print();

    // 获取链表长度
    std::cout << "链表长度：" << myList.len() << std::endl; */

}
