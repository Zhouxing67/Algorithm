#include <semaphore>

//using std::counting_semaphore;
using std::binary_semaphore;

int bowel = 3;
const int n = 5; //哲学家人数
int chopstics[n] = { 1 };

binary_semaphore mutex{ 1 };


void eat() {}
void get_resource(int i);
void release_resource(int i);
void philosopher(int i)
{
    while (1) {
        get_resource(i);

        eat();

        release_resource(i);
    }

}
//原子地获取所有资源
//具体的：进程查询所有的资源是否足够，如果足够将取得这份资源并返回，否则开始下一次查询
void get_resource(int i)
{
    bool enough = 0;
    while (1) {
        mutex.acquire();
        if (bowel && chopstics[i] && chopstics[(i - 1 + n) % n]) {
            //获取所有资源
            //拿一个碗
            bowel--;
            //取左筷子，右筷子
            chopstics[i]--;
            chopstics[(i - 1 + n) % n]--;
            mutex.acquire();
            return;
        }
        mutex.release(1);
    }
}
//原子地释放所有资源
void release_resource(int i)
{
    mutex.acquire();
    //放回一个碗
    bowel++;
    //放回左右筷子
    chopstics[i]++;
    chopstics[(i - 1 + n) % n]++;
    mutex.release(1);
}