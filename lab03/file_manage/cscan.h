#ifndef C_SCAN_H
#define C_SCAN_H

#include "disk.h"
#include "scan.h"

void CSCAN()
{
    int current_track = MAX_DISK_TRACK / 2;
    std::vector<int> right_disk_track;
    std::vector<int> left_disk_track;
    int total_distance = 0;
    std::cout << "按照 CSCAN 算法磁道的访问顺序为：";
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
    total_distance = total_distance + current_track;
    current_track = 0;
    int min_distance = abs(current_track - left_disk_track[0]);
    int min_index = 0;
    for (int j = 0; j < left_disk_track.size(); j++)
    {
        if (abs(current_track - left_disk_track[j]) < min_distance) // 距离磁头最近的磁道
        {
            min_distance = abs(current_track - left_disk_track[j]);
            min_index = j;
        }
    }
    total_distance -= min_distance;
    current_track = left_disk_track[min_index];
    std::cout << current_track << " ";
    left_disk_track.erase(left_disk_track.begin() + min_index);
    find_min_distance(left_disk_track, current_track, total_distance);
    std::cout << std::endl;
    std::cout << "移动磁道数为：" << total_distance << std::endl;
    std::cout << "平均寻道长度为：" << std::fixed << std::setprecision(1) << (double)total_distance / (double)MAX_DISK_REQUEST << std::endl;
}

#endif