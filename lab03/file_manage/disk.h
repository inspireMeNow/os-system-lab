#ifndef DISK_H
#define DISK_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include <vector>
#include <map>

#define MAX_DISK_TRACK 500
#define MAX_DISK_REQUEST 10

std::vector<int> disk_track;

void get_disk_track()
{
    srand((unsigned)time(NULL));
    std::cout << "需要寻找的磁道号：" << std::endl;
    for (int i = 0; i < MAX_DISK_REQUEST; i++)
    {
        disk_track.push_back(rand() % MAX_DISK_TRACK);
        std::cout << disk_track[i] << " ";
    }
    std::cout << std::endl;
}

#endif