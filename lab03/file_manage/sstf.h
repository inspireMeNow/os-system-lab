#ifndef SSTF_H
#define SSTF_H

#include "disk.h"

void SSTF()
{
    int total_distance = 0;
    int current_track = MAX_DISK_TRACK / 2;
    std::vector<int> temp = disk_track;
    std::cout << "按照 SSTF 算法磁道的访问顺序为：";
    for (int i = 0; i < MAX_DISK_REQUEST; i++)
    {
        int min_distance = abs(current_track - temp[0]);
        int min_index = 0;
        for (int j = 0; j < temp.size(); j++)
        {
            if (abs(current_track - temp[j]) < min_distance) // 距离磁头最近的磁道
            {
                min_distance = abs(current_track - temp[j]);
                min_index = j;
            }
        }
        total_distance += min_distance;
        current_track = temp[min_index];
        std::cout << current_track << " ";
        temp.erase(temp.begin() + min_index);
    }
    std::cout << std::endl;
    std::cout << "移动磁道数为：" << total_distance << std::endl;
    std::cout << "平均寻道长度为：" << std::fixed << std::setprecision(1) << (double)total_distance / (double)MAX_DISK_REQUEST << std::endl;
}

#endif