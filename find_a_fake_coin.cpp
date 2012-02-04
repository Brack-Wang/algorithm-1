
//---------------------------------------------------------------------------

#include  <iostream>
#include  <vector>
#include  <cstdio>
#include  <conio.h>
#include  <cstdlib>
#include  <ctime >
#include  <cmath >
#include  <cassert>
#include  <limits.h>

using namespace std;

/**
** Դ�ļ��� find_a_fake_coin.cpp
** ����˵����
** ���Գ��򣬼ٱ����⣺�����ɽ�ҡ�3-1000��������һ�ٱң��Ҳ�֪�ٱҽ������أ���һ�����ҳ����еļٱ���֪�����أ�
	Ҫ��Ƚϴ���Խ��Խ�á�
** ���³����Է��η����ݹ����ʽ�����������ַ������ַ����ķַ��������߼���һ�������ԣ���Ч�ʲ�һ��������Ч�ʣ�
** ���ַ� >= �ķַ� >= ���ַ�
** ����ʵ�֣����Դ����ע��˵����

** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 ǰ /
*/

#define		WHICH_HEAVY_LEFT	-1
#define		WHICH_HEAVY_UNKNOWN	0
#define		WHICH_HEAVY_RIGHT	1

#define		FAKE_STATE_HEAVY	2
#define		FAKE_STATE_UNKNOWN	1
#define		FAKE_STATE_LIGHT	0

static int s_which_heavy = WHICH_HEAVY_UNKNOWN;//��һ�߱Ƚ��أ���ʼ��Ϊ0 ����δȷ��
static int s_fake_state	= FAKE_STATE_UNKNOWN;//�ٱ����ر�־,��ʼ��Ϊ1 ����δȷ��
static int s_fake_coin = -1; //��ʼ���ٱ�λ��

/// ͳ�Ʋ�ͬ�ⷨ�ĵݹ����
static size_t s_find_2_comp_count = 0;
static size_t s_find_3_comp_count = 0;
static size_t s_find_4_comp_count = 0;
void init()
{
    s_fake_coin = -1; //��ʼ���ٱ�λ��
    s_fake_state = FAKE_STATE_UNKNOWN;//���ر�־,��ʼ��Ϊ1 ����δȷ��
    s_which_heavy = WHICH_HEAVY_UNKNOWN;//��һ�߱Ƚ��أ���ʼ��Ϊ0 ����δȷ��

    s_find_2_comp_count = 0;
    s_find_3_comp_count = 0;
    s_find_4_comp_count = 0;

}
void print_find_result()
{
    cout <<  "	���, �ٱ�λ�ã�" <<  s_fake_coin;
    if (s_fake_state == FAKE_STATE_LIGHT)
        cout <<  "	�ٱҽ��ᣡ";
    else if (s_fake_state == FAKE_STATE_HEAVY)
        cout <<  "	�ٱҽ��أ�";
    else
        cout <<  "	�޼ٱң�";
    cout << "�Ƚϴ�����"<< s_find_2_comp_count+s_find_3_comp_count+s_find_4_comp_count << endl;
}
void uninit()
{
    print_find_result();
}

//���ַ����
int sum_coins(const int A[], int from, int to)
{
    int sum = 0;
    for (int i=from; i <=to; i++)
    {
        sum += 	A[i];
    }
    return	sum;
}
//---------------------------------------------------------------------------
bool calc_fake_coin(int A[], int c1, int c2)
{
    //��ȷ�����A[0]��ǰ���£�ʣ��2��Ӳ�һ�һ����c1==c2�������ٱҵ�����λ�ú����ء�
    if (c1 == c2)
    {
        if (A[0] != A[c1])
        {
            s_fake_coin = c1;
            s_fake_state = (A[0] < A[c1] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);
        }
        else
            return false;
    }
    if (A[0] == A[c1])
    {
        s_fake_coin = c2;
        if (s_fake_state == FAKE_STATE_UNKNOWN)
            s_fake_state = (A[0] < A[c2] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);

    }
    else
    {
        s_fake_coin = c1;
        if (s_fake_state == FAKE_STATE_UNKNOWN)
            s_fake_state = (A[0] < A[c1] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT);

    }
    return true;
}

//---------------------------------------------------------------------------
bool find_a_fake_coin_2(const int A[], int from, int to)
{
    //    /*/*�ٱ�������⣺���ַ�*/
    ++s_find_2_comp_count;
    if (to == from)
    {
        return calc_fake_coin(const_cast<int*>(A), from, to);
    }
    else
    {
        if ((to-from+1)%2 == 0)
        {
            int mid = (from+to)/2;
            if (sum_coins(A, from, mid) == sum_coins(A, mid+1, to))
                return	false;
            else
            {
                if (find_a_fake_coin_2(A, from, mid))
                    return	true;
                else
                    find_a_fake_coin_2(A, mid+1, to);
            }
        }
        else if (A[to] != A[0])
        {
            s_fake_coin = to;
            s_fake_state = A[to] > A[0] ? FAKE_STATE_HEAVY : FAKE_STATE_LIGHT;
            return	true;
        }
        else
        {
            to = to-1;
            int mid = (from+to)/2;
            if (sum_coins(A, from, mid) == sum_coins(A, mid+1, to))
                return	false;
            else
            {
                if (find_a_fake_coin_2(A, from, mid))
                    return	true;
                else
                    find_a_fake_coin_2(A, mid+1, to);
            }
        }
    }
    return	false;
}
//---------------------------------------------------------------------------
void find_a_fake_coin_3(int A[], int from, int to)
{
    ++s_find_3_comp_count;
//    /*�ٱ�������⣺���ַ�*/
    if ((to-from+1) < 3)
    {
        //
        //ȷ����ҵ�����--����
        if (from > 1)
            A[0] = A[1];
        else
            A[0] = A[to+1];
        calc_fake_coin(A, from, to);
    }
    else
    {
        int i = (to-from+1)/3;
        int mid1 = from+i-1;
        int mid2 = mid1+i;

        if (sum_coins(A, from, mid1) == sum_coins(A, mid1+1, mid2))
        {
            if (s_fake_state == FAKE_STATE_UNKNOWN)
            {
                //�жϼٱҵ�����
                if (s_which_heavy == WHICH_HEAVY_LEFT)
                    s_fake_state = FAKE_STATE_LIGHT;
                if (s_which_heavy == WHICH_HEAVY_RIGHT)
                    s_fake_state = FAKE_STATE_HEAVY;
            }

            find_a_fake_coin_3(A, mid2+1, to);
        }
        else
        {
            if (s_fake_state == FAKE_STATE_UNKNOWN)
            {
                //��¼�������
                if (sum_coins(A, from, mid1) > sum_coins(A, mid1+1, mid2))
                    s_which_heavy = WHICH_HEAVY_LEFT;
                else
                    s_which_heavy = WHICH_HEAVY_RIGHT;
            }

            find_a_fake_coin_3(A, from, mid2);
        }
    }
}

//---------------------------------------------------------------------------
void find_a_fake_coin_4(int A[], int from, int to)
{
//    /*/*�ٱ�������⣺�ķַ�*/
    ++s_find_4_comp_count;
    if ((to-from+1) < 4)
    {
        find_a_fake_coin_3(A, from, to);
    }
    else
    {
        int i = (to-from+1)/4;
        int mid1 = from+i-1;
        int mid2 = mid1+i;
        if (sum_coins(A, from, mid1) == sum_coins(A, mid1+1, mid2))
        {
// 			/// ����ע���߼�����ȱ�ݣ����ʺ������ַ���
// 			if (s_fake_state == FAKE_STATE_UNKNOWN)
// 			{	//�жϼٱҵ�����
// 				if (s_which_heavy == WHICH_HEAVY_LEFT)
// 					s_fake_state = FAKE_STATE_LIGHT;
// 				if (s_which_heavy == WHICH_HEAVY_RIGHT)
// 					s_fake_state = FAKE_STATE_HEAVY;
// 			}
            find_a_fake_coin_4(A, mid2+1, to);
        }
        else
        {
// 			/// ����ע���߼�����ȱ�ݣ����ʺ������ַ���
// 			if (s_fake_state == FAKE_STATE_UNKNOWN)
// 			{	//��¼�������
// 				if (sum_coins(A, from, mid1) > sum_coins(A, mid1+1, mid2))
// 					s_which_heavy = WHICH_HEAVY_LEFT;
// 				else
// 					s_which_heavy = WHICH_HEAVY_RIGHT;
// 			}
            find_a_fake_coin_4(A, from, mid2);
        }
    }
}

void print_coins(const int pCoins[], int count)
{
    cout <<  "[���]����";
    for (int i=1; i <=count; ++i)
    {
        cout <<  " [" <<  i <<  "]" << pCoins[i];
    }
    cout <<  endl;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    char c;
    const unsigned MAX_COIN_COUNT = 1000;
    int pCoins[MAX_COIN_COUNT];
    do
    {
        system("cls");
        /// ������Ҫ��3�����Ҳ��бȽ����壡
        cout <<  "\n\n	���������������3-1000���� ";
        int coin_count = 100;
        cin >>  coin_count;
        if (coin_count <= MAX_COIN_COUNT && coin_count > 2)
        {

            int fake_s = rand()%2;//���ֵ:1 �ٱҽ���, 0 �ٱҽ���.
            int fake_pos = (rand()%coin_count)+1;//���ֵ,�ٱҳ��ֵ�λ��.
            // �������� 2 * 100
// 			for (int fake_s = 0; fake_s < 2; ++fake_s)
// 				for (int fake_pos = 1; fake_pos <= 100; ++fake_pos)
            {
                // ��ʼ��pCoins[0]�����ң���Ϊ�жϱ�׼��
                for (int i=0; i <=coin_count; ++i)
                    pCoins[i] = 1;

                if (fake_s == 0)
                    pCoins[fake_pos] = 0;
                else
                    pCoins[fake_pos] = 2;

                int pos2, pos3, pos4;
                int state2, state3, state4;
                print_coins(pCoins, coin_count);

                cout <<  "\n	���ַ����:\n";
                init();
                find_a_fake_coin_2(pCoins, 1, coin_count);
                uninit();
                pos2 = s_fake_coin;
                state2 = s_fake_state;

                cout <<  "\n	���ַ����:\n";
                init();
                find_a_fake_coin_3(pCoins, 1, coin_count);
                uninit();
                pos3 = s_fake_coin;
                state3 = s_fake_state;

                cout <<  "\n	�ķַ����:\n";
                init();
                find_a_fake_coin_4(pCoins, 1, coin_count);
                uninit();
                pos4 = s_fake_coin;
                state4 = s_fake_state;
                cout << " pos:" << pos2 << " " << pos3 << " "  << pos4
                     << " state:" << state2 << " " << state3 << " " << state4 << "\n";

                /// ���������Ƿ���ȷ��
                if (!((pos2 == pos3 && pos3 == pos4) && (state2 == state3 && state3 == state4)))
                {
                    cout <<  " --- ERROR ---\n";
                    print_coins(pCoins, coin_count);
                }
            }

        }
        else
            cout <<  " ��������";

        cout <<  "\n\n	!!!�������������Esc�˳�����!!!" <<  endl;

    }
    while( (c=getch())!=27);

    return 0;
}
