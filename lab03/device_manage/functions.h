#include "bankers.h"

void device_manage()
{
    int pid;
    std::cout << "系统可用资源数：" << std::endl;
    for (int i = 0; i < M; i++)
    {
        std::cout << "资源" << i << "：" << AVAILABLE[i] << std::endl;
    }
    std::cout << std::endl;
    print_status();
    std::cout << std::endl;
    std::cout << "请输入要申请资源的进程号（0~4）：" << std::endl;
    std::cin >> pid;
    std::cout << "请输入进程" << pid << "申请的资源数：" << std::endl;
    for (int i = 0; i < M; i++)
    {
        std::cout << "第" << i + 1 << "类资源：";
        std::cin >> REQUEST[i];
    }
    yin_hang_jia(pid);
}