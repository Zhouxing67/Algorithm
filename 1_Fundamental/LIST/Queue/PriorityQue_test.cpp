#include <iostream>
#include "PriorityQue.h"  // 
#include <random>
#include <ctime>

int main()
{
    std::mt19937 mt(time(0));
    static std::uniform_int_distribution<int> dis(1, 30);
    // 创建一个最大堆的优先队列，元素类型为整数
    static alg4::list::PriortyQue<int> pq(10, std::less<int>());  // 10表示队列的最大容量

    // 向队列中添加元素
    for (int i = 0; i < 10;i++)
    {
        auto val = dis(mt);
        pq.push(val);
        std::cout << val << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < 10; i++) {// 输出队列的大小和队首元素
       // std::cout << "Queue size: " << pq.size() << std::endl;
        std::cout << "Front element: " << pq.front() << std::endl;
        // 弹出队首元素
        pq.pop();
    }



    return 0;
}
