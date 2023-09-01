#ifndef SCAN_H
#define SCAN_H

#include "disk.h"

void find_min_distance(std::vector<int> direction_disk_track, int &current_track, int &total_distance)
{
    std::vector<int> temp = direction_disk_track;
    for (int i = 0; i < direction_disk_track.size(); i++)
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
}

void SCAN()
{
    int current_track = MAX_DISK_TRACK / 2;
    std::vector<int> right_disk_track;
    std::vector<int> left_disk_track;
    int total_distance = 0;
    std::cout << "按照 SCAN 算法磁道的访问顺序为：";
    for (int k = 0; k < MAX_DISK_REQUEST; k++)
    {
        if (disk_track[k] >= current_track)
        {
            right_disk_track.push_back(disk_track[k]);
        }
        else
        {
            left_disk_track.push_back(disk_track[k]);
        }
    }
    find_min_distance(right_disk_track, current_track, total_distance);
    find_min_distance(left_disk_track, current_track, total_distance);
    std::cout << std::endl;
    std::cout << "移动磁道数为：" << total_distance << std::endl;
    std::cout << "平均寻道长度为：" << std::fixed << std::setprecision(1) << (double)total_distance / (double)MAX_DISK_REQUEST << std::endl;
}

#endif