
/*
Practice 11
Solving the knapsack problem by the memory function algorithm; the weight and
value of those items are produce by rand or acquired from the keyboard.
  */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <cassert>

using namespace std;

/**
** Դ�ļ��� knapsack _test.cpp
** ����˵����
** ���Գ��򣬱�����������书�ܡ��㷨��ϸ����������㷨��������ơ�8.4������������书�ܡ�
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

int**	calcValues = NULL;
int		*pWeight = NULL, *pValue = NULL;

int MFKnapsack(int i, int j)
{
    if (calcValues[i][j]<0)
    {
        int		value;
        if (j<pWeight[i])
            value = MFKnapsack(i-1, j);
        else
        {
            int		value1 = MFKnapsack(i-1, j);
            int		value2 = pValue[i] + MFKnapsack(i-1, j-pWeight[i]);
            value = max(value1, value2);

            calcValues[i][j] = value;
        }


    }
    return	calcValues[i][j];
}
void PrinrCalcValue(int** values, int m, int n)
{
	for (int i=0; i<m+1; i++)
	{
		cout << "	";
		for (int j=0; j<n+1; j++)
		{
			cout << " " << values[i][j];
		}
		cout << endl;
	}
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        system("cls");
        cout << "\n\n	�Ա�������ʵ�ּ��书�ܷ�����ʾ�������£�\n";
        cout << "	��������Ʒ����M������������N ��";
        int		M, N;
        cin >> M >> N;
        pValue = new int [M+1];
        pWeight = new int [N+1];
		assert (pValue && pWeight);
        //�����ʼ��Value ��Weight
        for (int i=1; i<=M; i++)
        {
            pValue[i] = rand()%20+1;
            pWeight[i] = rand()%(N/2)+1 ;
        }
        cout << "\n	���������ƷΪ�������£� \n";
        for (int i=1; i<=M; i++)
        {
            cout << "	Value[" << i << "] = " << pValue[i]
                 << ",   Weight[" << i << "] = " << pWeight[i] <<endl;
        }
        //��̬����V[][]�ռ�
		calcValues = new int*[M+1];
		assert (calcValues);
        for (int i=0; i<M+1; i++)
        {
            calcValues[i] = new int [N+1];
			assert (calcValues[i]);
        }
        //��ʼ��V[][]
        for (int i=0; i<M+1; i++)
            for (int j=0; j<N+1; j++)
            {
                if (i==0||j==0)
                    calcValues[i][j] = 0;
                else
                    calcValues[i][j] = -1;
            }
        PrinrCalcValue(calcValues, M, N);

        MFKnapsack(M,N);
        PrinrCalcValue(calcValues, M, N);

		//�ͷ�V[][]�ռ�
		for (int i=0; i<M+1; i++)
			delete[] calcValues[i];
		delete[] calcValues;

        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
