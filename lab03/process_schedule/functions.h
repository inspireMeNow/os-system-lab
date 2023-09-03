#include "high_priority.h"
#include "fcfs.h"
#include "sjf.h"
#include "sync_exclusive.h"

void process_schedule()
{
    std::cout << "请输入要使用的功能（按0退出）" << std::endl;
    std::cout << "1.生产者与消费者问题" << std::endl;
    std::cout << "2.进程调度" << std::endl;
    int choice;
    std::cin >> choice;
    while (choice < 0 || choice > 2)
    {
        fflush(stdin);
        std::cout << "输入错误，请重新输入！" << std::endl;
        std::cin >> choice;
    }
    if (choice == 1)
    {
        sync_exclusive();
    }
    if (choice == 2)
    {
        std::cout << "请输入进程数" << std::endl;
        int n;
        std::cin >> n;
        std::cout << "请输入要使用的算法（按0退出）" << std::endl;
        std::cout << "1.先来先服务" << std::endl;
        std::cout << "2.短作业优先" << std::endl;
        std::cout << "3.高优先级优先" << std::endl;
        int temp_choice;
        std::cin >> temp_choice;
        while (temp_choice < 0 || temp_choice > 3)
        {
            fflush(stdin);
            std::cout << "输入错误，请重新输入！" << std::endl;
            std::cin >> temp_choice;
        }
        std::vector<PCB> pcb;
        PCB p;
        std::cout << "请输入进程名、到达时间、服务时间" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cin >> p.id >> p.arrive_time >> p.serve_time;
            p.priority = 50 - p.serve_time;
            p.need_time = p.serve_time;
            pcb.push_back(p);
        }
        switch (temp_choice)
        {
        case 1:
            pcb = FCFS(pcb);
            print_pcb_status(pcb, temp_choice);
            break;
        case 2:
            pcb = SJF(pcb);
            print_pcb_status(pcb, temp_choice);
            break;
        case 3:
            pcb = high_priority_schedule(pcb);
            print_pcb_status(pcb, temp_choice);
        default:
            break;
        }
    }
}