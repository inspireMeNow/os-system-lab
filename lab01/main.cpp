#include <iostream>
#include <cstring>
#include <iomanip>
typedef struct PCB
{
    std::string NAME;
    int CPUTIME;
    int NEEDTIME;
    int PRIO;
    int COUNT;
    int ROUND;
    char STATE;
    struct PCB *next = nullptr;
} PCB;
PCB *READY = nullptr, *RUN = nullptr, *TAIL = nullptr, *FINISH = nullptr;
int N;
void INSERT1(PCB *p)
{
    PCB *p1, *s, *r;
    int b;
    s = p;      // 待插入的pcb指针
    p1 = READY; // 就绪队列指针
    r = p1;
    b = 1;
    while ((p1 != NULL) && b) // 根据优先数确定位置
    {
        if (p1->PRIO >= s->PRIO)
        {
            r = p1;
            p1 = p1->next;
        }
        else
        {
            b = 0;
        }
    }

    if (r != p1)
    {
        r->next = s;
        s->next = p1;
    }
    else
    {
        s->next = p1;
        READY = s;
    }
}
void INSERT2(PCB *p2)
{
    TAIL->next = p2;
    TAIL = p2;
    p2->next = nullptr;
}
void FISRTIN()
{
    RUN = READY;
    if (READY != nullptr)
    {
        RUN->STATE = 'R';
        READY = READY->next;
        RUN->next = nullptr;
    }
}
void PRINT1()
{
    PCB *p;
    std::cout << "name" << std::setw(10) << "cputime" << std::setw(10) << "needtime" << std::setw(10) << "prio" << std::setw(10) << "state" << std::endl;
    if (RUN != NULL)
    {
        std::cout << RUN->NAME << std::setw(10) << RUN->CPUTIME << std::setw(10) << RUN->NEEDTIME << std::setw(10) << RUN->PRIO << std::setw(10) << RUN->STATE << std::endl;
    }
    p = READY;
    while (p != NULL)
    {
        std::cout << p->NAME << std::setw(10) << p->CPUTIME << std::setw(10) << p->NEEDTIME << std::setw(10) << p->PRIO << std::setw(10) << p->STATE << std::endl;
        p = p->next;
    }
    p = FINISH;
    while (p != NULL)
    {
        std::cout << p->NAME << std::setw(10) << p->CPUTIME << std::setw(10) << p->NEEDTIME << std::setw(10) << p->PRIO << std::setw(10) << p->STATE << std::endl;
        p = p->next;
    }
}
void PRINT2()
{
    PCB *p;
    std::cout << "name" << std::setw(10) << "cputime" << std::setw(10) << "needtime" << std::setw(10) << "count" << std::setw(10) << "round" << std::setw(10) << "state" << std::endl;
    if (RUN != NULL)
    {
        std::cout << RUN->NAME << std::setw(10) << RUN->CPUTIME << std::setw(10) << RUN->NEEDTIME << std::setw(10) << RUN->COUNT << std::setw(10) << RUN->ROUND << std::setw(10) << RUN->STATE << std::endl;
    }
    p = READY;
    while (p != NULL)
    {
        std::cout << p->NAME << std::setw(10) << p->CPUTIME << std::setw(10) << p->NEEDTIME << std::setw(10) << p->COUNT << std::setw(10) << p->ROUND << std::setw(10) << p->STATE << std::endl;
        p = p->next;
    }
    p = FINISH;
    while (p != NULL)
    {
        std::cout << p->NAME << std::setw(10) << p->CPUTIME << std::setw(10) << p->NEEDTIME << std::setw(10) << p->COUNT << std::setw(10) << p->ROUND << std::setw(10) << p->STATE << std::endl;
        p = p->next;
    }
}
void CREATE(int algorithm)
{
    PCB *p;
    int i, time;
    std::string na;
    READY = nullptr;
    FINISH = nullptr;
    RUN = nullptr;
    printf("请输入进程名和相应的NEEDTIME值：\n");
    for (int i = 1; i <= N; i++)
    {
        std::cin >> na >> time;
        p = new PCB;
        p->NAME = na;
        p->NEEDTIME = time;
        if (algorithm == 1)
        {
            p->PRIO = 50 - time;
        }
        else
        {
            p->ROUND = 2;
            p->COUNT = 0;
        }
        p->STATE = 'W';
        p->CPUTIME = 0;
        p->next = NULL;
        if (READY != NULL)
        {
            if (algorithm == 1)
            {
                INSERT1(p);
            }
            else
            {
                INSERT2(p);
            }
        }
        else
        {
            p->next = READY;
            READY = p;
            if (algorithm == 2)
            {
                TAIL = p;
            }
        }
    }
    if (algorithm == 1)
        PRINT1();
    else
        PRINT2();
    RUN = READY;
    READY = READY->next;
    RUN->STATE = 'R';
}
void PRISCH()
{
    while (RUN != NULL)
    {
        RUN->CPUTIME++;
        RUN->NEEDTIME--;
        RUN->PRIO = RUN->PRIO--;
        if (RUN->NEEDTIME == 0)
        {
            RUN->next = FINISH;
            FINISH = RUN;
            RUN->STATE = 'F';
            RUN = NULL;
            if (READY != NULL)
            {
                FISRTIN();
            }
        }
        else
        {
            if ((READY != NULL) && (RUN->PRIO < READY->PRIO))
            {
                RUN->STATE = 'W';
                INSERT1(RUN);
                FISRTIN();
            }
        }
        PRINT1();
    }
}
void ROUNDSCH()
{
    while (RUN != nullptr)
    {
        RUN->CPUTIME+=1;
        RUN->NEEDTIME-=1;
        RUN->COUNT++;
        if (RUN->NEEDTIME == 0)
        {
            RUN->next = FINISH;
            FINISH = RUN;
            RUN->STATE = 'F';
            RUN = nullptr;
            if (READY != nullptr)
            {
                FISRTIN();
            }
        }
        else
        {
            if (RUN->COUNT == RUN->ROUND)
            {
                RUN->COUNT = 0;
                if (READY != nullptr)
                {
                    RUN->STATE = 'W';
                    INSERT2(RUN);
                    FISRTIN();
                }
            }
        }
        PRINT2();
    }
}
int main()
{
    int algorithm;
    printf("请输入你要使用的算法：\n1.优先级调度算法\n2.时间片轮转调度算法\n");
    std::cin >> algorithm;
    printf("你要输入几个进程？\n");
    std::cin >> N;
    if (algorithm == 1)
    {
        CREATE(1);
        PRISCH();
    }
    if (algorithm == 2)
    {
        CREATE(2);
        ROUNDSCH();
    }
    return 0;
}