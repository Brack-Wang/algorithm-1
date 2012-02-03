
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <limits.h>

using namespace std;

/**
** Դ�ļ��� josephus_problem.cpp
** ����˵����
** ���Գ���ģ��Լɪ���������ʾ�����²����������ݽṹʵ�֣�
	1. ���飻2. ѭ������
	�����ϣ�ѭ������Ҫ�������飬�������ʵ�ֿ��ܽ������������롣

** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

// ����ģ��Լɪ������
typedef struct Kill_Man
{
    int*	men;
    int killed_men;
    int order_survivors;
    int cur_survivors;
    int every_kill;

    Kill_Man()
        : men(0) {}
    ~Kill_Man()
    {
        if (men)
            delete men;
    }
} Kill_Man;


// n Ϊ��������kΪ��һ����ʼ�������ˣ�mΪ�����ߺ���������
void JosephusProblem1(int n, int m, int k)
{
    Kill_Man	kill_man;
    kill_man.order_survivors = 1;

    int man_num = n;
    int sign = k;
    int killed = 0;

    kill_man.every_kill = m;

    kill_man.men = new int [man_num];
    assert (kill_man.men);
    kill_man.killed_men = 0;
    kill_man.cur_survivors = man_num;
    //���

    for (int i=0; i<man_num; i++)
    {
        kill_man.men[i] = i+1;//���
    }
    do
    {
        int count = 0;
        //int kill;
        do
        {
            //
            sign = sign%man_num;
            if (kill_man.men[sign] != -1)
            {
                count++;
            }
            sign++;
        }
        while(count != kill_man.every_kill);

        //Kill man
        kill_man.men[sign-1] = -1;
        cout << ++killed << "	Kill man : "<< sign << endl;//���

        kill_man.killed_men++;
        kill_man.cur_survivors--;

    }
    while(kill_man.order_survivors !=kill_man.cur_survivors);

    for (int i=0; i<man_num; i++)
    {
        if (kill_man.men[i] != -1 )
        {
            //���
            cout << "	Survivors : "<< kill_man.men[i] << endl;
        }
    }
    cout << endl;
}


// ѭ������ģ��Լɪ������
typedef struct LNode
{
    int data;
    struct LNode *link;
} LNode, *LinkList;

// n Ϊ��������kΪ��һ����ʼ�������ˣ�mΪ�����ߺ���������
void JosephusProblem2(int n, int m, int k)
{
    assert (n >= k);
    LinkList p, r, curr;
    p = (LinkList) malloc(sizeof(LNode));
    p->data = 1;
    p->link = p;
    curr = p;
    for (int i=2; i<=n; i++)
    {
        LinkList t = (LinkList)malloc(sizeof(LNode));
        t->data = i;
        t->link = curr->link;
        curr->link = t;
        curr = t;
    }
    r = curr;
    while(k--)
        r=p, p=p->link;
    while(n--)
    {
        for (int s=m-1; s--; r=p, p=p->link)
            ;
        r->link = p->link;
        printf("%d->", p->data);
        free(p);
        p = r->link;
    }
}

int main()
{
    char c;
    do
    {
        system("cls");
        int all, mark;
        cout << "\n\n\n	Josephus problem ��ʾ ��\n"
             << "	������������ ";
        cin >> all;
        cout << "	�����룬��� Kill Man ���� ";
        cin >> mark;
        cout << "#1 ����ģ��Լɪ�����⣺\n";
        JosephusProblem1(all, mark, 0);
        cout << "#2 ѭ������ģ��Լɪ�����⣺\n";
        JosephusProblem2(all, mark, 0);
        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
