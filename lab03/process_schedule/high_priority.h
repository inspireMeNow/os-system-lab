#ifndef HIGH_PRIORITY_H
#define HIGH_PRIORITY_H
#include "pcb.h"
bool compare_priority(PCB a, PCB b)
{
    return a.priority > b.priority;
}

int find_max_priority(std::vector<PCB> pcb)
{
    int max, index;
    max = pcb[0].priority;
    index = 0;
    for (int i = 0; i < pcb.size(); i++)
    {
        if (pcb[i].serve_time > max)
        {
            max = pcb[i].serve_time;
            index = i;
        }
    }
    return index;
}

std::vector<PCB> high_priority_schedule(std::vector<PCB> pcb) // 高优先级优先
{
    std::vector<PCB> waiting = pcb; // 就绪队列
    std::vector<PCB> running;       // 运行队列
    std::vector<PCB> finishing;     // 完成队列
    for (int i = 0; i < waiting.size(); i++)
    {
        waiting[i].need_time = waiting[i].serve_time;
    }
    int time = 0;
    while (!waiting.empty())
    {
        int index = find_max_priority(waiting);
        running.push_back(waiting[index]);
        running[0].status = "R";
        waiting[index].priority--;
        waiting[index].need_time -= TIME_SLICE;
        time += TIME_SLICE;
        std::cout << "当前时间：" << time << std::endl;
        std::cout << "就绪队列" << std::endl;
        print_pcb(waiting);
        std::cout << std::endl;
        std::cout << "运行队列" << std::endl;
        print_pcb(running);
        std::cout << std::endl;
        std::cout << "完成队列" << std::endl;
        print_pcb(finishing);
        std::cout << "\n"
                  << std::endl;
        running.clear();
        if (waiting[index].need_time <= 0)
        {
            waiting[index].status = "F";
            waiting[index].end_time = time;
            waiting[index].round_time = waiting[index].end_time - waiting[index].arrive_time;
            waiting[index].weight_round_time = (double)waiting[index].round_time / (double)waiting[index].serve_time;
            finishing.push_back(waiting[index]);
            waiting.erase(waiting.begin() + index);
        }
    }

    return finishing;
}

#endif