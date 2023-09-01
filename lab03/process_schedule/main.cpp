#include "high_priority.h"
#include "fcfs.h"
#include "sjf.h"

int main()
{
    std::cout << "请输入进程数" << std::endl;
    int n;
    std::cin >> n;
    std::cout << "请输入要使用的算法（按0退出）" << std::endl;
    std::cout << "1.先来先服务" << std::endl;
    std::cout << "2.短作业优先" << std::endl;
    std::cout << "3.高优先级优先" << std::endl;
    int choice;
    std::cin >> choice;
    std::vector<PCB> pcb;
    PCB p;
    switch (choice)
    {
    case 1:
        std::cout << "请输入进程名、到达时间、服务时间" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cin >> p.id >> p.arrive_time >> p.serve_time;
            pcb.push_back(p);
        }
        pcb = FCFS(pcb);
        break;
    case 2:
        std::cout << "请输入进程名、到达时间、服务时间" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cin >> p.id >> p.arrive_time >> p.serve_time;
            pcb.push_back(p);
        }
        pcb = SJF(pcb);
        break;
    case 3:
        std::cout << "请输入进程名、服务时间" << std::endl;
        for (int i = 0; i < n; i++)
        {
            std::cin >> p.id >> p.serve_time;
            pcb.push_back(p);
        }
        pcb = high_priority_schedule(pcb);
    default:
        break;
    }
    print_pcb_status(pcb, 3);

    return 0;
}