

#include <iostream>
#include <stack>
#include "queen_problem.h"
using namespace std;
class Board;

//---------------------------------------------------------------------------

/**
** Դ�ļ��� queen_problem.cpp, queen_problem.h
** ����˵����
** N�ʺ�����Ľⷨ��Ӧ�û��ݷ������������нⷨ��
���ݷ��ٿ�
���ݷ�(̽������ݷ�)��һ��ѡ������������ѡ��������ǰ�������ԴﵽĿ�ꡣ����̽����ĳһ��ʱ��
����ԭ��ѡ�񲢲��Ż�ﲻ��Ŀ�꣬���˻�һ������ѡ�������߲�ͨ���˻����ߵļ���Ϊ���ݷ���
���������������ĳ��״̬�ĵ��Ϊ�����ݵ㡱��


����ṹ˵����
	1.	�Ƚ���һ���ʺ�Q1�̶��ڵ�һ�е�һ�е�λ��pos[1][1]��
	2.	������һ�У�Ѱ�Һ���λ�ðڷŻʺ󣬼����������ʺ󶼲��ܴ���ͬһ�С�ͬһ�л�ͬһб���ϡ�
	2.1	���ҵ�����λ�ã����¼�����ݵ㡱��ջ����������Ѱ����һ�аڷ���һ�ʺ�ĺ���λ�ã�
	ֱ�����һ��Ϊֹ����ʱ���ҵ���һ�����������Ļʺ����У�Ȼ����в���2.2��
	2.2	���Ҳ�������λ�ã����ջ������ջ�����ݵ㡱����Ѱ����һ����λ�ã��ٽ��в���2��
	ֱ�����ݵ���һ�е�λ�ã�Ȼ��ʼ����3��
	3.	������Q1�̶�����һλ��pos[x+1][1]��������ʼ����2��ѭ��ֱ��Q1�̶���pos[n+1][1]��

** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 ǰ /
*/


/// ���ݷ�ʵ����Ҫ���㷨

void solve_problem(int nQ)
{
    int is_print_on_screen = 0;//��ʼ������ģʽ��־��1 ��ֱ������ȫ�������0 �����������һ�ֽ��
    Board myBoard(nQ); //��ʼ������
    //for (qRow = 0;qRow <(myBoard.N_Queen+1)/2;qRow++)//(N_Queen+1)/2����N_Queen�����ھ���ĶԳ��ԣ��������ȷ������
    //for (qCol = 0;qCol <(myBoard.N_Queen+1)/2;qCol++)//ͬʱ�������˳���Ч�ʣ�����
    for (int row0 = 0; row0 < myBoard.nQueen; ++row0)
	{
		myBoard.initBoard();
        myBoard.placeQueen(row0, 0);
        stack<int>	rowStack;
        int row = 0, col = 1;
        do
        {
            while(row < myBoard.nQueen)  //����
            {
                if (!(myBoard.isAttacked(row, col)))
                {
                    //���޻ʺ���������
                    myBoard.placeQueen(row, col); //�Żʺ�
                    rowStack.push(row); //��ջ�Ա�����еľ���λ�÷���֮��ļ�������
                    row = 0;
                    col++;
                    break;
                }
                else
                    row++;    // ����һ��
            }

            if (col == myBoard.nQueen)
            {
                myBoard.incrementSol(row0);
                myBoard.saveSolution();
                //Ϊ���Ƴ�Esc������������������--Ӧ�÷���if���桢����
                if (is_print_on_screen != 1)
                {
                    myBoard.printSolution();
                    if (27 == getch())//Esc��ACSII��
                    {
                        is_print_on_screen = 1;
                        system("cls");
                        cout << "\n\n\n\n\n	��⣡����N �ʺ���������У������ĵȴ�������\n";
                        g_timer.set_begin();//��ʼ��ʱ
                    }
                }
                row = myBoard.nQueen;
            }

            if (row == myBoard.nQueen)
            {
                if (!rowStack.empty())
                {
                    row = rowStack.top();
                    rowStack.pop();//��ջ�Լ������ҷ�����������һ��ʺ�
                }
                col--; //�˻ص�ǰһ��
                if (col == 0)
                    col--;
                else if (col > 0)
                    myBoard.removeQueen(row, col); //��ȥ�ʺ�

                row++;  //����һ��λ��--���в���
            }
        }
        while (col >= 0);   //�ص�0��
    }

    g_timer.set_end();//��ֹ��ʱ

    // ��Ļ������ļ����棡
    myBoard.printResult();
    myBoard.saveResult();

}

//---------------------------------------------------------------------------
void hello()
{
    system("cls");
    char 	next;
    ifstream	in_stream;
    in_stream.open("hello.txt");
    if (in_stream.fail())
        return;
    cout << "\n";
    while(in_stream.get(next))
    {
        cout << next;
    }


    cout <<"\n	���������ʼ��ʾ�˻ʺ�������⡣\n"
         <<"˵������������ʱ��������������һ�ֽⷨ����ֱ��Esc���ȫ���ⷨ\n\n";
    system("pause");
}
//---------------------------------------------------------------------------
int main()
{
    system("color 02");//��ʼ�����屳����������ɫ
    char c;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n	��������ӭѧϰ����ʾ N �ʺ�������⡷���򣡣���\n";
        cout << "						--�ƿ���(only)\n\n	";
        system("pause");
        hello();
        int nQ;
        do
        {
            system("cls");
            cout << "\n\n	��������Ҫ��ʾ N �ʺ��������� N(<15) : ";
            string	str;
            cin >> str;
            nQ = atoi(str.c_str());
        }
        while(nQ >= 16 || nQ <=0);

        solve_problem(nQ);

        cout << "\n���Ƿ����ִ�в������밴q(Q)��Esc���˳�,����������˻أ� ";
        c = getch();
    }
    while (c != 'q' && c != 'Q' && c != 27);

    return 0;
}
//---------------------------------------------------------------------------

