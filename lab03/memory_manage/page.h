#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include <deque>

#define PAGE_SIZE 1024   // 页大小
#define MEMORY_SIZE 8192 // 内存大小
#define MAX_PAGE 3       // 最大页数
#define INST_SIZE 50     // 指令流大小

typedef struct Page
{
    int page_num; // 页号
    int time = 0; // 留存时间
} Page;

int inst[INST_SIZE];          // 指令流
std::deque<Page> memory_page; // 页表队列

// 初始化指令流
void init_inst()
{
    srand((unsigned)time(NULL));
    for (int i = 0; i < INST_SIZE / 2; i++)
    {
        inst[i] = i;
    }
    for (int i = INST_SIZE / 2; i < INST_SIZE * 3 / 4; i++)
    {
        inst[i] = rand() % (MEMORY_SIZE - MEMORY_SIZE / 2 + 1) + MEMORY_SIZE / 2;
    }
    for (int i = INST_SIZE * 3 / 4; i < INST_SIZE; i++)
    {
        inst[i] = rand() % (MEMORY_SIZE / 2 - INST_SIZE / 2 + 1) + INST_SIZE / 2;
    }
}
int init_page()
{
    return MEMORY_SIZE / PAGE_SIZE;
}
#endif