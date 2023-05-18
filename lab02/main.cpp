#include <iostream>
#include <string>
using namespace std;

typedef struct node
{
    int adr = 0;       // 分区首地址
    int size = 0;      // 分区大小
    node *next = NULL; // 指向下一个分区的指针
} node;

node *head1;  // 空闲区队列首指针
node *back1;  // 指向释放区node结构的指针
node *assign; // 指向申请的内存分区node结构的指针 申请区队列

void into_assign(node *p) // 首次适应 将申请的节点p按照首址从小到大插入到assign中
{
    node *i, *j;
    for (i = assign->next, j = assign; i != NULL && (i->adr <= p->adr); j = i, i = i->next)
        ; // 查找比要插入节点首址大的节点，插入到其前面
    j->next = p;
    p->next = i;
}

void edit_head1_1(node *p, int free) // 分配后 空闲分区有剩余 首次适应算法 空闲区仅修改大小的首址即可（按照首址排序，队列中的位置不变）
{
    // 修改空闲区节点
    p->adr = p->adr + free;
    p->size = p->size - free;
}

void edit_head1_2(node *i, node *j, int free) // 分配后 空闲分区有剩余 最佳适应方法，将剩余分区按照空间大小重新插入到队列中 j为i之前的节点指针
{
    i->adr = i->adr + free;
    j->next = i->next; // 先从队列中删除 之后按顺序插入
    i->size = i->size - free;
    node *p, *q;
    for (q = head1, p = head1->next; p != NULL && (p->size < i->size); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或空间大于i的节点结束
    q->next = i;
    i->next = p;
}

void into_head1_1(node *n) // 首次适应 将释放节点n 按照首址插入到空闲队列中 之后合并分区
{
    node *p, *q;
    // 按照首址从小到大插入到空闲队列中
    for (q = head1, p = head1->next; p != NULL && (p->adr < n->adr); q = p, p = p->next)
        ;        // 从空闲区第一个节点开始访问 访问到最后一个或p地址大于释放区的节点结束
    q->next = n; // 插入到空闲区
    n->next = p;

    // 合并分区
    if (q->adr + q->size == n->adr) // 与前面的节点合并
    {
        q->size = q->size + n->size;
        q->next = n->next;
        delete n;
        n = q; // 保证与前分区合并后还能与后分区合并
    }
    if (p != NULL && (n->adr + n->size == p->adr)) // 与后面的节点合并
    {
        n->size = n->size + p->size;
        n->next = p->next;
        delete p;
    }
}

void into_head1_2(node *n) // 最佳适应 先合并分区 再按空间从小到大插入到空闲队列中
{
    node *p, *q;
    // 找与n 前面的 能与n合并的节点
    for (q = head1, p = head1->next; p != NULL && (p->adr + p->size != n->adr); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或p能与n合并的前面的节点结束
    if (p != NULL)
    {
        p->size = p->size + n->size; // 合并
        q->next = p->next;           // 从队列中删除p 待重新插入
        p->next = NULL;
        delete n;
        n = p; // 保证与前面的节点合并后还能与后面的合并也能插入到空闲队列中
    }
    // 找与n 后面的 能与n合并的节点
    for (q = head1, p = head1->next; p != NULL && (n->adr + n->size != p->adr); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或p能与n合并的后面的节点结束
    if (p != NULL)
    {
        p->size = p->size + n->size; // 合并
        p->adr = p->adr - n->size;
        q->next = p->next; // 从队列中删除p 待重新插入
        p->next = NULL;
        delete n;
        n = p; // 保证合并后还能插入到空闲队列中
    }
    // 合并完成 插入到空闲队列中
    for (q = head1, p = head1->next; p != NULL && (p->size < n->size); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或空间大于n的节点结束
    q->next = n;
    n->next = p;
}

void output() // 输出空闲区 （和申请区）
{
    int i;
    node *p;
    cout << "------------------------- 空闲区 -------------------------" << endl;
    for (p = head1->next, i = 0; p != NULL; p = p->next, i++)
    {
        cout << "编号：" << i << "     首址：" << p->adr << "     终址：" << p->adr + p->size - 1 << "     大小：" << p->size << endl;
    }
    //*
    cout << "------------------------- 申请区 -------------------------" << endl;
    for (p = assign->next, i = 0; p != NULL; p = p->next, i++)
    {
        cout << "编号：" << i << "     首址：" << p->adr << "     终址：" << p->adr + p->size - 1 << "     大小：" << p->size << endl;
    }
    //*/
}

void assignment(int free, int cho_1) // 实现动态分配算法 首次适应 和最佳适应
{
    node *p, *q;
    // 确定输入的分区大小是否能够分配 p 指针即为所求
    for (q = head1, p = head1->next; p != NULL && (p->size < free); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或空间满足的节点结束
    if (p == NULL)
    {
        cout << "空间不足！" << endl;
        return;
    }
    // 为新申请空间设置一个新节点
    node *n = new node;
    n->adr = p->adr; // 新首址等于空闲分区的首址
    n->size = free;
    n->next = NULL;

    into_assign(n);     // 将新节点插入到申请队列中 按照首地址排序
    if (p->size > free) // 空闲分区有剩余
    {
        if (cho_1 == 1) // 选择首次适应
        {
            edit_head1_1(p, free); // 首次适应 修改分区
        }
        else
        {
            edit_head1_2(p, q, free); // 最佳适应 修改分区
        }
    }
    else // 删除p节点
    {
        q->next = p->next;
        delete p;
    }
}

void acceptment(int adr, int cho_1) // 实现动态分配的回收算法 首次适应和最佳适应
{
    node *p, *q, *n;
    // 确定输入的分区地址是否正确 p 指针即为所求
    for (q = assign, p = assign->next; p != NULL && (p->adr != adr); q = p, p = p->next)
        ; // 从空闲区第一个节点开始访问 访问到最后一个或地址满足的节点结束
    if (p == NULL)
    {
        cout << "输入首址错误！" << endl;
        return;
    }
    // 将释放的分区移出申请区
    q->next = p->next;
    p->next = NULL;
    back1->next = p; // 准备释放到空闲区
    n = p;
    if (cho_1 == 1) // 选择首次适应
    {
        into_head1_1(n); // 插入到空闲分区 之后与前后分区合并
    }
    else
    {
        into_head1_2(n); // 先合并分区 再插入空闲分区
    }
}
int main()
{
    int free = 0; // 申请区的大小
    int adr = 0;  // 释放区的首地址
    // 指针初始化
    head1 = new node;
    back1 = new node;
    assign = new node;
    head1->size = -1; // 分区合并时不会把头结点 与后面的节点合并
    back1->size = -1;
    assign->size = -1;
    head1->next = NULL;
    back1->next = NULL;
    assign->next = NULL;

    // 空闲队列赋初值
    node *n = new node;
    n->adr = 0;
    n->size = 32767;
    n->next = NULL;
    head1->next = n;

    int cho_1, cho_2;
    cout << "请输入要使用的算法？\n1.首次适应算法\n2.最佳适应算法" << endl;
    cin >> cho_1;
    cout << "初始状态：" << endl;
    output();
    do
    {
        cout << "请选择要进行的操作：\n1.分配\n2.回收\n3.退出" << endl;
        cin >> cho_2;
        switch (cho_2)
        {
        case 1:
            cout << "请输入申请区大小：" << endl;
            cin >> free;
            assignment(free, cho_1);
            output();
            break;
        case 2:
            cout << "请输入释放区首址：" << endl;
            cin >> adr;
            acceptment(adr, cho_1);
            output();
            break;
        case 3:
            break;
        default:
            cout << "输入不正确，请重新输入" << endl;
            break;
        }
    } while (cho_2 != 3);
    return 0;
}
/*
测试数据一
1
1
300
1
200
1
100
1
400
2
0
2
500
1
100
2
0
2
300
2
600
3
测试数据二
2
1
300
1
200
1
100
1
400
2
0
2
500
1
100
2
500
2
600
2
300
3
*/