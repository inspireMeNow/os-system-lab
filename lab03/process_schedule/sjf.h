#ifndef SJF_H
#define SJF_H
#include "pcb.h"
bool compare_serve_arrive_time(PCB a, PCB b)
{
    if (a.arrive_time == b.arrive_time)
    {
        return a.serve_time < b.serve_time;
    }
    else
    {
        return a.arrive_time < b.arrive_time;
    }
}

int find_min_servetime(std::vector<PCB> pcb)
{
    int min, index;
    min = pcb[0].serve_time;
    index = 0;
    for (int i = 0; i < pcb.size(); i++)
    {
        if (pcb[i].serve_time < min)
        {
            min = pcb[i].serve_time;
            index = i;
        }
    }
    return index;
}

std::vector<PCB> SJF(std::vector<PCB> pcb) // SJF算法
{
    std::sort(pcb.begin(), pcb.end(), compare_serve_arrive_time);
    std::vector<PCB> temp = pcb;
    int time = 0;
    std::vector<PCB> temp2; // 已到达的进程
    while (!temp.empty())
    {
        temp2.clear();
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i].arrive_time <= time)
            {
                temp2.push_back(temp[i]);
            }
        }
        if (temp2.empty())
        {
            time++;
            continue;
        }
        else
        {
            int temp2_index = find_min_servetime(temp2); // 服务时间最短的进程
            int index = find_process(pcb, temp2, temp2_index);
            int temp_index = find_process(temp, temp2, temp2_index);
            pcb[index].start_time = time;
            pcb[index].end_time = time + pcb[index].serve_time;
            pcb[index].round_time = pcb[index].end_time - pcb[index].arrive_time;
            pcb[index].weight_round_time = (double)pcb[index].round_time / (double)pcb[index].serve_time;
            pcb[index].status = "F";
            time = pcb[index].end_time;
            temp.erase(temp.begin() + temp_index);
        }
    }
    return pcb;
}

#endif