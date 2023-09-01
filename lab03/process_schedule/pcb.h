#ifndef PCB_H
#define PCB_H
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

#define TIME_SLICE 1 // 时间片大小

typedef struct PCB
{
    std::string id;                  // 进程名
    int priority = 50;               // 优先级
    int arrive_time = 0;             // 到达时间
    int serve_time = 0;              // 服务时间
    int start_time = 0;              // 开始时间
    int end_time = 0;                // 完成时间
    int round_time = 0;              // 周转时间
    int need_time = 0;               // 剩余服务时间
    double weight_round_time = 0.00; // 带权周转时间
    std::string status = "W";        // 程序状态
} PCB;

int find_process(std::vector<PCB> pcb1, std::vector<PCB> pcb2, int n)
{
    int index = -1;
    for (int i = 0; i < pcb1.size(); i++)
    {
        if (pcb1[i].id == pcb2[n].id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void print_pcb_status(std::vector<PCB> pcb, int n)
{
    switch (n)
    {
    case 1:
    case 2:
        std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << "进程名\t" << std::setw(15) << std::setfill(' ') << "优先级\t" << std::setw(15) << std::setfill(' ') << "到达时间\t" << std::setw(20) << std::setfill(' ') << "服务时间" << std::setw(15) << std::setfill(' ') << "开始时间\t" << std::setw(15) << std::setfill(' ') << "完成时间\t" << std::setw(15) << std::setfill(' ') << "周转时间\t" << std::setw(15) << std::setfill(' ') << "带权周转时间\t" << std::setw(15) << std::setfill(' ') << "程序状态" << std::resetiosflags(std::ios::left) << std::endl;
        for (int i = 0; i < pcb.size(); i++)
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << pcb[i].id << std::setw(15) << std::setfill(' ') << pcb[i].priority << std::setw(15) << std::setfill(' ') << pcb[i].arrive_time << std::setw(20) << std::setfill(' ') << pcb[i].serve_time << std::setw(15) << std::setfill(' ') << pcb[i].start_time << std::setw(15) << std::setfill(' ') << pcb[i].end_time << std::setw(15) << std::setfill(' ') << pcb[i].round_time << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << pcb[i].weight_round_time << std::setw(15) << std::setfill(' ') << pcb[i].status << std::resetiosflags(std::ios::left) << std::endl;
        }
        break;
    case 3:
        std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << "进程名\t" << std::setw(15) << std::setfill(' ') << "优先级\t" << std::setw(15) << std::setfill(' ') << "到达时间\t" << std::setw(20) << std::setfill(' ') << "服务时间" << std::setw(15) << std::setfill(' ') << "完成时间\t" << std::setw(15) << std::setfill(' ') << "周转时间\t" << std::setw(15) << std::setfill(' ') << "带权周转时间\t" << std::setw(15) << std::setfill(' ') << "程序状态" << std::resetiosflags(std::ios::left) << std::endl;
        for (int i = 0; i < pcb.size(); i++)
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << pcb[i].id << std::setw(15) << std::setfill(' ') << pcb[i].priority << std::setw(15) << std::setfill(' ') << pcb[i].arrive_time << std::setw(20) << std::setfill(' ') << pcb[i].serve_time << std::setw(15) << std::setfill(' ') << pcb[i].end_time << std::setw(15) << std::setfill(' ') << pcb[i].round_time << std::setw(15) << std::setfill(' ') << std::fixed << std::setprecision(2) << pcb[i].weight_round_time << std::setw(15) << std::setfill(' ') << pcb[i].status << std::resetiosflags(std::ios::left) << std::endl;
        }
    default:
        break;
    }
    double sum_round_time = 0.0;
    double sum_weight_round_time = 0.0;

    for (int i = 0; i < pcb.size(); i++)
    {
        sum_round_time = sum_round_time + pcb[i].round_time;
        sum_weight_round_time = sum_weight_round_time + pcb[i].weight_round_time;
    }
    std::cout << "平均周转时间为：" << std::fixed << std::setprecision(2) << (double)sum_round_time / (double)pcb.size() << "，"
              << "平均带权周转时间为：" << std::fixed << std::setprecision(2) << (double)sum_weight_round_time / (double)pcb.size() << std::endl;
}

void print_pcb(std::vector<PCB> pcb)
{
    std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << "进程名\t" << std::setw(15) << std::setfill(' ') << "优先级\t" << std::setw(15) << std::setfill(' ') << "服务时间\t" << std::setw(20) << std::setfill(' ') << "剩余服务时间" << std::setw(15) << std::setfill(' ') << "程序状态" << std::resetiosflags(std::ios::left) << std::endl;
    for (int i = 0; i < pcb.size(); i++)
    {
        std::cout << std::setiosflags(std::ios::left) << std::setw(15) << std::setfill(' ') << pcb[i].id << std::setw(15) << std::setfill(' ') << pcb[i].priority << std::setw(15) << std::setfill(' ') << pcb[i].serve_time << std::setw(20) << std::setfill(' ') << pcb[i].need_time << std::setw(15) << std::setfill(' ') << pcb[i].status << std::resetiosflags(std::ios::left) << std::endl;
    }
}

#endif