#ifndef FCFS_H
#define FCFS_H
#include "pcb.h"

bool compare_arrive_time(PCB a, PCB b)
{
    return a.arrive_time < b.arrive_time;
}

std::vector<PCB> FCFS(std::vector<PCB> pcb) // FCFS算法
{
    std::sort(pcb.begin(), pcb.end(), compare_arrive_time);
    int time = 0;
    for (int i = 0; i < pcb.size(); i++)
    {
        if (pcb[i].arrive_time > time)
        {
            time = pcb[i].arrive_time;
        }
        pcb[i].start_time = time;
        pcb[i].end_time = time + pcb[i].serve_time;
        pcb[i].round_time = pcb[i].end_time - pcb[i].arrive_time;
        pcb[i].weight_round_time = (double)pcb[i].round_time / (double)pcb[i].serve_time;
        pcb[i].status = "F";
        time = pcb[i].end_time;
    }
    return pcb;
}
#endif