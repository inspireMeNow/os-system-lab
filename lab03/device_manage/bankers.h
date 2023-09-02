#ifndef BANKERS_H
#define BANKERS_H

#include "resource.h"

bool check_secure(int AVAILABLE[], int ALLOCATION[][M], int NEED[][M], int i)
{
    int WORK[M];    // 系统可提供给进程继续运行所需的各类资源数目
    bool FINISH[N]; // 进程是否完成标志
    int temp = 0;
    int safe_list[N];
    int k = 0;
    for (int i = 0; i < N; i++)
    {
        FINISH[i] = false;
    }
    for (int j = 0; j < M; j++)
    {
        WORK[j] = AVAILABLE[j];
        temp = i;
        while (temp < N)
        {
            if (NEED[temp][j] <= WORK[j] && FINISH[temp] == false)
            {
                WORK[j] += ALLOCATION[temp][j];
                FINISH[temp] = true;
                safe_list[k] = temp;
                k++;
                temp = 0;
            }
            else
            {
                temp++;
            }
        }
    }
    // for (int j = 0; j < N; j++)
    // {
    //     for (int i = 0; i < M; i++)
    //     {
    //         FINISH[j] = false;
    //         if (NEED[j][i] <= WORK[i])
    //         {
    //             WORK[i] += ALLOCATION[j][i];
    //             FINISH[j] = true;
    //         }
    //     }
    // }
    for (int i = 0; i < N; i++)
    {
        if (FINISH[i] == false)
        {
            return false;
        }
    }
    std::cout << "经安全性检查，系统安全，本次安全序列为：";
    for (int i = 0; i < N; i++)
    {
        if (i == N - 1)
            std::cout << "进程" << safe_list[i];
        else
            std::cout << "进程" << safe_list[i] << " -> ";
    }
    std::cout << "，";
    return true;
}

void print_status()
{
    std::cout << "各进程还需要的资源量：" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << "进程" << i << "：";
        for (int j = 0; j < M; j++)
        {
            std::cout << "资源" << j << "：" << NEED[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "各进程已经得到的资源量：" << std::endl;
    for (int i = 0; i < N; i++)
    {
        std::cout << "进程" << i << "：";
        for (int j = 0; j < M; j++)
        {
            std::cout << "资源" << j << "：" << ALLOCATION[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void yin_hang_jia(int i)
{
    for (int j = 0; j < M; j++)
    {
        if (REQUEST[j] > NEED[i][j])
        {
            std::cout << "申请资源数大于所需资源数，申请失败" << std::endl;
            return;
        }
    }
    int TEMP_AVAILABLE[M];
    int TEMP_ALLOCATION[N][M];
    int TEMP_NEED[N][M];
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            TEMP_ALLOCATION[j][i] = ALLOCATION[j][i];
            TEMP_NEED[j][i] = NEED[j][i];
        }
        TEMP_AVAILABLE[i] = AVAILABLE[i];
    }
    for (int j = 0; j < M; j++)
    {
        if (REQUEST[j] <= TEMP_AVAILABLE[j])
        {
            TEMP_AVAILABLE[j] -= REQUEST[j];
            TEMP_ALLOCATION[i][j] += REQUEST[j];
            TEMP_NEED[i][j] -= REQUEST[j];
        }
        else
        {
            std::cout << "资源不足，申请失败" << std::endl;
            return;
        }
    }
    bool is_safe = check_secure(TEMP_AVAILABLE, TEMP_ALLOCATION, TEMP_NEED, i);
    if (is_safe == true)
    {
        for (int i = 0; i < M; i++)
        {
            AVAILABLE[i] = TEMP_AVAILABLE[i];
            for (int j = 0; j < N; j++)
            {
                ALLOCATION[j][i] = TEMP_ALLOCATION[j][i];
                NEED[j][i] = TEMP_NEED[j][i];
            }
        }
        std::cout << "资源分配成功" << std::endl;
        std::cout << std::endl;
        print_status();
    }
    else
    {
        std::cout << "资源不足，申请失败" << std::endl;
    }
}

#endif