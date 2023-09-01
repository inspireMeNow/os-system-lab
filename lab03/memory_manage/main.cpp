#include "fifo.h"
#include "lru.h"

int main()
{
    init_inst();
    int total_page = init_page();
    std::cout << "请输入要使用的算法（按0退出）" << std::endl;
    std::cout << "1.FIFO" << std::endl;
    std::cout << "2.LRU" << std::endl;
    int choice;
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        FIFO();
        break;
    case 2:
        LRU();
        break;
    default:
        break;
    }

    return 0;
}