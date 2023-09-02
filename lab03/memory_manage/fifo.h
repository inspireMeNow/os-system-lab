#ifndef FIFO_H
#define FIFO_H

#include "page.h"

// 检查页表是否在内存中
int check_deque(int current_page)
{
    int flag = 1;
    for (int i = 0; i < memory_page.size(); i++)
    {
        if (memory_page[i].page_num == current_page)
        {
            flag = 0;
            break;
        }
    }
    return flag;
}

void FIFO()
{
    memory_page.clear();
    int insufficient = 0;
    Page current_page;
    for (int i = 0; i < INST_SIZE; i++)
    {
        current_page.page_num = inst[i] / PAGE_SIZE;
        std::cout << "指令所在地址为：" << inst[i] << "，";
        std::cout << "所在页表为：" << current_page.page_num << "，";
        if (memory_page.size() >= 3)
        {
            if (check_deque(current_page.page_num))
            {
                std::cout << "产生缺页，置换页面：" << memory_page[0].page_num << "，";
                memory_page.pop_front();
                memory_page.push_back(current_page);
                insufficient++;
            }
        }
        else
        {
            if (check_deque(current_page.page_num))
            {
                memory_page.push_back(current_page);
            }
            else
            {
                current_page.time = 0;
            }
        }
        std::cout << "内存中的页表为:";
        for (int i = 0; i < memory_page.size(); i++)
        {
            std::cout << memory_page[i].page_num << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "命中" << INST_SIZE - insufficient << "次，缺页" << insufficient << "次，缺页率为" << (double)insufficient / INST_SIZE << std::endl;
}

#endif