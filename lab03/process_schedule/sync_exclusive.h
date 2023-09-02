#ifndef SYNC_EXCLUSIVE_H
#define SYNC_EXCLUSIVE_H

#include <unistd.h>
#include <iostream>
#include <thread>

#define MAX 20

#define RUN_TIME 10

int count = 5;

void Producer()
{
    for (int i = 0; i < RUN_TIME; i++)
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
        i++;
    }
}
void Consumer()
{
    for (int i = 0; i < RUN_TIME; i++)
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
        i++;
    }
}
int tStop()
{
    int l = getchar();
    return l;
}
void sync_exclusive()
{
    std::thread t1(Producer);
    std::thread t2(Consumer);
    t1.join();
    t2.join();
}

#endif