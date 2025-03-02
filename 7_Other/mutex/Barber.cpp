#include <semaphore>

using std::binary_semaphore;
using std::counting_semaphore;

int counting = 0; //记录等候的顾客人数
const int n = 10; //一共有n把椅子

binary_semaphore mutex{ 1 }; //用于实现对counting1的互斥访问
counting_semaphore services{ 0 }; //实现同步
counting_semaphore customs{ 0 }; //实现同步

void custom()
{
    mutex.acquire();
    if (counting > n)
    {
        mutex.release();
        return;
    }
    //取号码
    counting++;
    mutex.release();
    customs.release();
    services.acquire();
    //开始被剪头
}

void barber()
{
    while (1)
    {
        mutex.acquire();
        if (counting != 0)
        {
            //叫号
            counting--;
            mutex.release();
            services.release();
            //剪头
        }
        else {
            mutex.release();
            customs.acquire();
        }
    }

}