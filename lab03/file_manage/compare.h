#ifndef COMPARE_H
#define COMPARE_H

#include "fcfs.h"
#include "sstf.h"
#include "scan.h"
#include "cscan.h"

void COMPARE()
{
    std::cout << std::endl;
    std::cout << "先来先服务算法（FCFS）" << std::endl;
    FCFS();
    std::cout << std::endl;
    std::cout << "最短寻道时间优先算法（SSTF）" << std::endl;
    SSTF();
    std::cout << std::endl;
    std::cout << "扫描算法（SCAN）" << std::endl;
    SCAN();
    std::cout << std::endl;
    std::cout << "循环扫描算法（CSCAN）" << std::endl;
    CSCAN();
}

#endif