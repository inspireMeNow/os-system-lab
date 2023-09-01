#include <unistd.h>
#include <iostream>
#include <thread>

#define MAX 20

int count = 5;

void Producer()
{
    while (1)
    {
        if (count >= MAX)
        {
            std::cout << "缓冲区已满！" << std::endl;
            usleep(3000000);
        }
        else
        {
            count++;
            std::cout << "生产了一个产品，当前产品总数为：" << count << std::endl;
            usleep(1300000);
        }
    }
}
void Consumer()
{
    while (1)
    {
        if (count == 0)
        {
            std::cout << "缓冲区为空！" << std::endl;
            usleep(2000000);
        }
        else
        {
            count--;
            std::cout << "取出了一个产品，当前产品总数为：" << count << std::endl;
            usleep(2000000);
        }
    }
}
int tStop()
{
    int l = getchar();
    return l;
}
void Start()
{
    std::thread t1(Producer);
    std::thread t2(Consumer);
    t1.detach();
    t2.detach();
    int isStop = tStop();
    if (isStop == 0)
    {
        return;
    }
}
int main()
{
    Start();
    return 0;
}