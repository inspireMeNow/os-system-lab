#include "fifo.h"
#include "lru.h"

void memory_manage()
{
    int total_page = init_page();
    std::cout << "请输入要使用的算法（按0退出）" << std::endl;
    std::cout << "1.FIFO" << std::endl;
    std::cout << "2.LRU" << std::endl;
    std::cout << "3.两种算法比较" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        init_inst();
        FIFO();
        break;
    case 2:
        init_inst();
        LRU();
        break;
    case 3:
        init_inst();
        std::cout << "FIFO算法" << std::endl
                  << std::endl;
        FIFO();
        std::cout << "LRU算法" << std::endl
                  << std::endl;
        LRU();
        std::cout << std::endl;
        break;
    default:
        break;
    }
}