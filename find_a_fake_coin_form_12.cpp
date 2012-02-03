

//---------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <cstdarg>
#include <limits.h>

using namespace std;

/**
** Դ�ļ��� find_a_fake_coin_form_12.cpp
** ����˵����
** ���Գ��򣬼ٱ����⣺12ö����д���һ�ٱң��Ҳ�֪�ٱҽ������أ���һ�����޳�3���ҳ����еļٱҲ�֪�����ء�
    �������г����в�ͬ�Ľⷨ����2*12�֡�

** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 ǰ /
*/

int sum_coins(const int A[], int from, int to )
{
    int sum = 0;
    for (int i=from; i<=to; i++)
        sum += 	A[i];

    return sum;
}

void print_comp_tips(const char* format, ...)
{
    va_list arg_ptr;
    va_start(arg_ptr, format);
    vector<int> args;
    while (true)
    {
        int para = va_arg(arg_ptr, int);
        if (-1 == para)
            break;
        args.push_back(para);
    }

    cout << " ���ұȽϣ�{";
    assert (0 == args.size() % 2);
    const size_t comp_num = args.size()/2;
    for (size_t i = 0; i < comp_num; ++i)
        cout << args[i] << " ";

    cout << "} VS {";
    for (size_t i = comp_num; i < args.size(); ++i)
        cout << args[i] << " ";
    cout << "}" << endl;

    va_end(arg_ptr);
}

bool find_a_fake_coin(const int A[], int& fake_coin, int& fake_state)
{
    if (print_comp_tips("%d%d%d%d%d%d%d%d%d", 1, 2, 3, 4, 5, 6, 7, 8, -1),
            sum_coins(A, 1, 4)==sum_coins(A, 5, 8) )
    {
        //�ٻ�������δ֪
        if ( print_comp_tips("%d%d%d%d%d", 1, 9, 10, 11, -1),
            (A[1]+A[9])==sum_coins(A, 10, 11) )
        {
            //A[12]�Ǽٱ�
            if (print_comp_tips("%d%d%d", 1, 12, -1),
                    A[1] < A[12])//�ٱҽ���
                fake_state = 1;
            else//�ٱҽ���
                fake_state = 0;
            fake_coin = 12;
        }
        else if ( (A[1]+A[9])>sum_coins(A, 10, 11) )
        {
            if (print_comp_tips("%d%d%d", 10, 11, -1),
                    A[10]==A[11])
            {
                //A[9]�ٱң�����
                fake_state = 1;
                fake_coin = 9;
            }
            else if (A[10]>A[11])
            {
                //A[11]�ٱң�����
                fake_state = 0;
                fake_coin = 11;
            }
            else//if (A[10]<A[11])
            {
                //A[10]�ٱң�����
                fake_state = 0;
                fake_coin = 10;
            }
        }
        else if (print_comp_tips("%d%d%d", 10, 11, -1),
                 A[10]==A[11])
        {
            //A[9]�ٱң�����
            fake_state = 0;
            fake_coin = 9;
        }
        else if (A[10]>A[11])
        {
            //A[10]�ٱң�����
            fake_state = 1;
            fake_coin = 10;
        }
        else//if (A[10]<A[11])
        {
            //A[11]�ٱң�����
            fake_state = 1;
            fake_coin = 11;
        }
    }
    else if ( sum_coins(A, 1, 4)>sum_coins(A, 5, 8) )
    {
        if ( print_comp_tips("%d%d%d%d%d%d%d%d%d", 1, 6, 7, 8, 5, 9, 10, 11, -1),
            (A[1]+sum_coins(A, 6, 8))==(A[5]+sum_coins(A, 9, 11)) )
        {
            //�ٻ�����������
            if ( print_comp_tips("%d%d%d", 2, 3, -1),
                    A[2]==A[3] )
                fake_coin = 4;
            else
                fake_coin = A[2]>A[3] ? 2:3;
            fake_state = 1;
        }
        else if ( (A[1]+sum_coins(A, 6, 8)) > (A[5]+sum_coins(A, 9, 11)) )
        {
            if (print_comp_tips("%d%d%d", 1, 9, -1),
                    A[1]==A[9])
            {
                fake_coin = 5;//�ٻ�����������
                fake_state = 0;
            }
            else
            {
                fake_coin = 1;//�ٻ�����������
                fake_state = 1;
            }
        }
        else//if ( (A[1]+Sum_Coin(A, 6, 8)) < (A[5]+Sum_Coin(A, 9, 11)) )
        {
            //�ٻ�����������
            if (print_comp_tips("%d%d%d", 6, 7, -1),
                    A[6]==A[7])
                fake_coin = 8;
            else
                fake_coin = A[6]<A[7] ? 6:7;
            fake_state = 0;
        }
    }
    //( Sum_Coin(A, 1, 4) < Sum_Coin(A, 5, 8) )
    else if (print_comp_tips("%d%d%d%d%d%d%d%d%d", 1, 6, 7, 8, 5, 9, 10, 11, -1),
             (A[1]+sum_coins(A, 6, 8))==(A[5]+sum_coins(A, 9, 11)) )
    {
        //�ٻ�����������
        if (print_comp_tips("%d%d%d", 2, 3, -1),
                A[2]==A[3] )
            fake_coin = 4;
        else
            fake_coin = A[2]<A[3] ? 2:3;
        fake_state = 0;
    }
    else if ( (A[1]+sum_coins(A, 6, 8)) > (A[5]+sum_coins(A, 9, 11)) )
    {
        //�ٻ�����������
        if (print_comp_tips("%d%d%d", 6, 7, -1),
                A[6]==A[7])
            fake_coin = 8;
        else
            fake_coin = A[6]>A[7] ? 6:7;
        fake_state = 1;

    }
    else if (print_comp_tips("%d%d%d", 1, 9, -1),
             A[1]==A[9])
    {
        fake_coin = 5;//�ٻ�����������
        fake_state = 1;
    }
    else
    {
        fake_coin = 1;//�ٻ�����������
        fake_state = 0;
    }

    return true;
}

void print_coins(const int pCoins[], int count)
{
    cout << "[���]����";
    for (int i=1; i<=count; ++i)
    {
        cout << " [" << i << "]"<< pCoins[i];
    }
    cout << endl;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    char c;
    const int COINS_COUNT = 12;
    int pCoins[COINS_COUNT+1] = {0};
    do
    {
        system("cls");
        cout << " �ٱ����⣺12ö����д���һ�ٱң��Ҳ�֪�ٱҽ������أ���һ�����޳�3���ҳ����еļٱҲ�֪�����ء���ʾ���£�\n";

// 		int fake_s = rand()%2;//1 ���ٱҽ��أ� 0 ���ٱҽ���
// 		int fake_pos = (rand()%COINS_COUNT)+1;
        for (int fake_s = 0; fake_s < 2; ++fake_s)
            for (int fake_pos = 1; fake_pos <= COINS_COUNT; ++ fake_pos)
            {
                cout << " NO." << (fake_s)*COINS_COUNT + fake_pos << " --- --- --- --- --- --- --- --- --- --- --- ---\n";
                int fake_coin = -1; //�ٱ�λ��
                int fake_state = -1; //1 ���ٱҽ��أ� 0 ���ٱҽ���
                for (int i=1; i<=COINS_COUNT; ++i)
                    pCoins[i] = 1;

                if (fake_s==0)
                    pCoins[fake_pos] = 0;
                else
                    pCoins[fake_pos] = 2;

                print_coins(pCoins, COINS_COUNT);

                find_a_fake_coin(pCoins, fake_coin, fake_state);

                assert (-1 != fake_state && -1 != fake_coin);
                cout << " �ٱ�λ�ã�" << fake_coin;
                if ( fake_state==0 )
                    cout << " �ٱҽ��ᣡ\n";
                else //if (1 ==fake_state)
                    cout << " �ٱҽ��أ�\n";
                cout << " --- end ---\n";
            }

        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );

    return 0;
}
