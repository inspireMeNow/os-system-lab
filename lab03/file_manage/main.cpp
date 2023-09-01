#include "compare.h"

int main()
{
    std::cout << "磁盘调度算法\n";
    std::cout << "请输入要使用的算法（按0退出）\n";
    std::cout << "1.先来先服务算法（FCFS）\n";
    std::cout << "2.最短寻道时间优先算法（SSTF）\n";
    std::cout << "3.扫描算法（SCAN）\n";
    std::cout << "4.循环扫描算法（CSCAN）\n";
    std::cout << "5.各类算法的比较\n";
    std::cout << "请输入你的选择的算法（输入 0 离开）\n";
    int choice;
    std::cin >> choice;
    if (choice >= 1 && choice <= 5)
    {
        std::cout << "从" << MAX_DISK_TRACK / 2 << "号磁道开始\n";
        get_disk_track();
    }
    switch (choice)
    {
    case 1:
        FCFS();
        break;
    case 2:
        SSTF();
        break;
    case 3:
        SCAN();
        break;
    case 4:
        CSCAN();
        break;
    case 5:
        COMPARE();
        break;
    default:
        break;
    }
    return 0;
}