#ifndef RESOURCE_H
#define RESOURCE_H

#include <iostream>

#define M 3 // 资源种类数
#define N 5 // 进程数

int MAX[N][M] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};        // N 个进程对 M 类资源最大资源需求量
int AVAILABLE[M] = {10, 5, 7};                                                  // 系统可用资源数
int ALLOCATION[N][M] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}; // N 个进程已经得到 M 类资源的资源量
int NEED[N][M] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};       // N 个进程还需要 M 类资源的资源量
int REQUEST[M] = {0, 0, 0};                                                     // 初始化需要申请的资源数目

#endif