#include "device_manage/functions.h"
#include "file_manage/functions.h"
#include "memory_manage/functions.h"
#include "process_schedule/functions.h"

int main()
{
    int n = 1;
    while (n != 0)
    {
        while (n < 0 || n > 4)
        {
            std::cout << "输入错误，请重新输入" << std::endl;
            std::cin >> n;
        }
        std::cout << "模拟操作系统" << std::endl;
        std::cout << "1、进程管理" << std::endl;
        std::cout << "2、设备管理" << std::endl;
        std::cout << "3、文件管理" << std::endl;
        std::cout << "4、存储管理" << std::endl;
        std::cout << "请输入要使用的功能（按0退出）" << std::endl;
        std::cin >> n;
        switch (n)
        {
        case 1:
            process_schedule();
            break;
        case 2:
            device_manage();
            break;
        case 3:
            file_manage();
            break;
        case 4:
            memory_manage();
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }
    return 0;
}