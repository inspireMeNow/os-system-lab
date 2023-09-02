#ifndef FCFS_FILE_H
#define FCFS_FILE_H

#include "disk.h"

void FCFS()
{
    int total_distance = 0;
    int current_track = MAX_DISK_TRACK / 2;
    std::cout << "按照 FCFS 算法磁道的访问顺序为：";
    for (int i = 0; i < MAX_DISK_REQUEST; i++)
    {
        total_distance += abs(current_track - disk_track[i]);
        current_track = disk_track[i];
        std::cout << current_track << " ";
    }
    std::cout << std::endl;
    std::cout << "移动磁道数为：" << total_distance << std::endl;
    std::cout << "平均寻道长度为：" << std::fixed << std::setprecision(1) << (double)total_distance / (double)MAX_DISK_REQUEST << std::endl;
}
#endif