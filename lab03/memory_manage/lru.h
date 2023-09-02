#ifndef LRU_H
#define LRU_H

#include "page.h"

int find_max_time()
{
    int max = memory_page[0].time;
    int index = 0;
    for (int i = 0; i < memory_page.size(); i++)
    {
        if (memory_page[i].time > max)
        {
            max = memory_page[i].time;
            index = i;
        }
    }
    return index;
}

void LRU()
{
    memory_page.clear();
    int insufficient = 0;
    Page current_page;
    for (int i = 0; i < INST_SIZE; i++)
    {
        current_page.page_num = inst[i] / PAGE_SIZE;
        std::cout<< "指令所在地址为：" << inst[i] << "，";
        std::cout << "所在页表为：" << current_page.page_num << "，";
        if (memory_page.size() >= 3)
        {
            int flag = 1;
            for (int i = 0; i < memory_page.size(); i++)
            {
                if (memory_page[i].page_num == current_page.page_num)
                {
                    flag = 0;
                    memory_page[i].time = 0;
                }
                else
                {
                    memory_page[i].time++;
                }
            }
            if (flag)
            {
                int index = find_max_time();
                std::cout << "产生缺页，置换页面：" << memory_page[index].page_num << "，";
                memory_page[index] = current_page;
                insufficient++;
            }
        }
        else
        {
            int flag = 1;
            for (int i = 0; i < memory_page.size(); i++)
            {
                if (memory_page[i].page_num == current_page.page_num)
                {
                    flag = 0;
                    memory_page[i].time = 0;
                }
                else
                {
                    memory_page[i].time++;
                }
            }
            if (flag)
            {
                memory_page.push_back(current_page);
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