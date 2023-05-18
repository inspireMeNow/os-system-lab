#include <iostream>

#include <cstdlib>

#include <cstring>

#include <iomanip> //输出对齐的头文件

using namespace std;

typedef struct node

{
    char name[20]; /*进程标识符*/

    int prio; /*进程优先数*/

    int round; /*进程时间轮转时间片*/

    int cputime; /*进程占用CPU时间*/

    int needtime; /*进程到完成还要的时间*/

    int count; /*计数器*/

    char state; /*进程的状态*/

    struct node *next; /*链指针*/

} PCB;

PCB *finish, *ready, *run, *tail; /*队列指针:就绪队列、执行队列、完成队列*/

int N; /*进程数*/

/*将就绪队列中的第一个进程投入运行*/

void firstin()

{
    run = ready; /*就绪队列头指针赋值给运行头指针*/

    if (ready != NULL)
    {

        run->state = 'R'; /*进程状态变为运行态*/

        ready = ready->next; /*就绪对列头指针后移到下一进程*/

        run->next = NULL;
    }
}

char toupper(char x)
{ // 确定为优先数法或轮转法

    return x;
}

void prt1(char a) /*标题输出函数*/

{
    if (toupper(a) == 'P' || toupper(a) == 'p') /*优先数法*/

        cout << "进程名  占用cpu时间  还需时间  进程优先数  进程状态" << endl;

    else /*轮转法*/

        cout << "进程名  占用cpu时间  还需时间  计数  时间片  进程状态" << endl;
}

void prt2(char a, PCB *q) /*进程PCB输出*/

{
    if (toupper(a) == 'P' || toupper(a) == 'p')
    { /*优先数法的输出*/

        cout << setw(12) << std::left << q->name << setw(12) << std::left << q->cputime << setw(12) << std::left << q->needtime << setw(12) << std::left << q->prio << setw(12) << std::left << q->state;

        cout << endl;
    }

    else
    { /*轮转法的输出*/

        cout << setw(10) << std::left << q->name << setw(10) << std::left << q->cputime << setw(10) << std::left << q->needtime << setw(10) << std::left << q->count << setw(10) << std::left << q->round << setw(10) << std::left << q->state;

        cout << endl;
    }
}

void prt(char algo) /*输出函数*/

{
    PCB *p;

    prt1(algo); /*输出标题*/

    if (run != NULL) /*如果运行指针不空*/

        prt2(algo, run); /*输出当前正在运行的PCB*/

    p = ready; /*输出就绪队列PCB*/

    while (p != NULL)

    {
        prt2(algo, p);

        p = p->next;
    }

    p = finish; /*输出完成队列的PCB*/

    while (p != NULL)

    {
        prt2(algo, p);

        p = p->next;
    }
}

void insert1(PCB *q) /*优先数的插入算法*/

{
    PCB *p1, *s, *r;

    int b;

    s = q; /*待插入的PCB指针*/

    p1 = ready; /*就绪队列头指针*/

    r = p1; /*r做p1的前驱指针*/

    b = 1;

    while ((p1 != NULL) && b) /*根据优先数确定插入位置*/

        if (p1->prio >= s->prio)

        {
            r = p1;

            p1 = p1->next;
        }

        else

            b = 0;

    if (r != p1) /*如果条件成立说明插入在r与p1之间*/

    {
        r->next = s;

        s->next = p1;
    }

    else

    {
        s->next = p1; /*否则插入在就绪队列的头*/

        ready = s;
    }
}

void insert2(PCB *p2) /*轮转法插入函数*/

{
    tail->next = p2; /*将新的PCB插入在当前就绪队列的尾*/

    tail = p2;

    p2->next = NULL;
}

void create1(char alg) /*优先数创建初始PCB信息*/

{
    PCB *p;

    int i, time;

    char na[10];

    ready = NULL; /*就绪队列头指针*/

    finish = NULL; /*完成队列头指针*/

    run = NULL; /*运行队列指针*/

    cout << "Enter name and time of process" << endl; /*输入进程标识和所需时间创建PCB*/

    for (i = 1; i <= N; i++)

    {
        p = (PCB *)malloc(sizeof(PCB));

        cin >> na;

        cin >> time;

        strcpy(p->name, na);

        p->cputime = 0;

        p->needtime = time;

        p->state = 'w';

        p->prio = 50 - time;

        if (ready != NULL) /*就绪队列不空调用插入函数插入*/

            insert1(p);

        else

        {
            p->next = ready; /*创建就绪队列的第一个PCB*/

            ready = p;
        }
    }

    cout << "          output of priority:" << endl;

    cout << "************************************************" << endl;

    prt(alg); /*输出进程PCB信息*/

    run = ready; /*将就绪队列的第一个进程投入运行*/

    ready = ready->next;

    run->state = 'R';
}

void create2(char alg) /*轮转法创建进程PCB*/

{
    PCB *p;

    int i, time;

    char na[10];

    ready = NULL;

    finish = NULL;

    run = NULL;

    cout << "Enter name and time of round process" << endl;

    for (i = 1; i <= N; i++)

    {
        p = (PCB *)malloc(sizeof(PCB));

        cin >> na;

        cin >> time;

        strcpy(p->name, na);

        p->cputime = 0;

        p->needtime = time;

        p->count = 0; /*计数器*/

        p->state = 'w';

        p->round = 2; /*时间片*/

        if (ready != NULL)

            insert2(p);

        else

        {
            p->next = ready;

            ready = p;

            tail = p;
        }
    }

    cout << "              output of round" << endl;

    cout << "************************************************" << endl;

    prt(alg); /*输出进程PCB信息*/

    run = ready; /*将就绪队列的第一个进程投入运行*/

    ready = ready->next;

    run->state = 'R';
}

void priority(char alg) /*优先数调度算法*/

{
    while (run != NULL) /*当运行队列不空时，有进程正在运行*/

    {
        run->cputime = run->cputime + 1;

        run->needtime = run->needtime - 1;

        run->prio = run->prio - 3; /*每运行一次优先数降低3个单位*/

        if (run->needtime == 0) /*如所需时间为0将其插入完成队列*/

        {
            run->next = finish;

            finish = run;

            run->state = 'F'; /*置状态为完成态*/

            run = NULL; /*运行队列头指针为空*/

            if (ready != NULL) /*如就绪队列不空*/

                firstin(); /*将就绪对列的第一个进程投入运行*/
        }

        else /*没有运行完同时优先数不是最大，则将其变为就绪态插入到就绪队列*/

            if ((ready != NULL) && (run->prio < ready->prio))

            {
                run->state = 'W';

                insert1(run);

                firstin(); /*将就绪队列的第一个进程投入运行*/
            }

        prt(alg); /*输出进程PCB信息*/
    }
}

void roundrun(char alg) /*时间片轮转法*/

{
    while (run != NULL)

    {
        run->cputime = run->cputime + 1;

        run->needtime = run->needtime - 1;

        run->count = run->count + 1;

        if (run->needtime == 0) /*运行完将其变为完成态，插入完成队列*/

        {
            run->next = finish;

            finish = run;

            run->state = 'F';

            run = NULL;

            if (ready != NULL)

                firstin(); /*就绪对列不空，将第一个进程投入运行*/
        }

        else

            if (run->count == run->round) /*如果时间片到*/

        {
            run->count = 0; /*计数器置0*/

            if (ready != NULL) /*如就绪队列不空*/

            {
                run->state = 'W'; /*将进程插入到就绪队列中等待轮转*/

                insert2(run);

                firstin(); /*将就绪对列的第一个进程投入运行*/
            }
        }

        prt(alg); /*输出进程信息*/
    }
}

/*主函数*/

int main()

{
    char algo; /*算法标记*/

    char anykey;

    // clrscr();

    cout << "P/p---priority(优先级算法)" << endl;

    cout << "R/r---roundrobin(时间片轮转算法)" << endl;

    cout << "choose the algorithm (请输入P(p)或者R(r)!!) :" << endl;

    cin >> algo; /*输入字符确定算法*/

    toupper(algo);

    cout << "Enter process number" << endl;

    cin >> N; /*输入进程数*/

    if (algo == 'P' || algo == 'p')
    {
        create1(algo); /*优先数法*/

        priority(algo);
    }

    else if (algo == 'R' || algo == 'r')
    {

        create2(algo); /*轮转法*/

        roundrun(algo);
    }

    return 0;
}