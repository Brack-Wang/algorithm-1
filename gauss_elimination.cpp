/***
Solve a system of n linear equations in n unknows using Gaussian elimination; assume that the coefficient matrix is not singular( if the coefficient matrix is produced by random,  you may verify singular );
Hints to the solution :
Step1: Gaussian elimination; page207, BetterGaussElimination
Step2: Backward substitution;
Backward substitution algorithm
for j �� n downto 1 do
      t �� 0
      for k �� j +1 to n do
            t �� t + A[j, k] * x[k]
      x[j] �� (A[j, n+1] - t) / A[j, j]

  */

/**
** Դ�ļ��� gauss_elimination.cpp
** ����˵����
** ���Գ����ø�˹��ȥ����ⷽ���飬������㷨��������ơ�6.2��˹��ȥ����
** �õ�������ĳ��ȱ任��
	1. �������������������̵�λ�ã�
	2. ��һ�������滻Ϊ���ķ��㱶��
	3. ��һ�������滻Ϊ������һ�����̱���֮��ĺͻ�
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

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

// �ò���ѡ��Ԫ��ʵ�ָ�˹��ȥ����
// ���룺����A[1...n, 1...n], B[1...n]��
// �����һ������A���������εȼ۾���ͼ����Ӧ���ұߵ�ֵλ�ڵ�n+1���С�
void BetterGaussElimination( double **A, double B[], int n )
{
    for (int i=1; i<=n; i++)
    {
        A[i][n+1] = B[i];
    }
    for (int i=1; i<=n-1; i++)
    {
        //�����Ԫ
        int pivotrow = i;
        for (int j=i+1; j<=n; j++)
        {
            //��֤ϵ����Ϊ0��ȡԪ�ؾ���ֵ���ֵ
            if ( fabs(A[j][i]) > fabs(A[pivotrow][i]) )
                pivotrow = j;
        }
        if (pivotrow != i)
        {
            for (int k=i; k<=n+1; k++)
            {
                //ֻ������0Ԫ�� A[][k]
                double	temp;
                temp = A[i][k];
                A[i][k] = A[pivotrow][k];
                A[pivotrow][k] = temp;
            }
        }
        for (int j=i+1; j<=n; j++)
        {
            //������Ԫ
            double	temp = A[j][i]/A[i][i];//��������
            for (int k=i; k<=n+1; k++)
            {
                //������Ԫ
                A[j][k] = A[j][k]-A[i][k]*temp;
            }
        }
    }
}
void BackwardSubstitution(double **A, double *C, int n)
{
    /*
    for j �� n downto 1 do
         t �� 0
         for k �� j +1 to n do
               t �� t + A[j, k] * x[k]
         x[j] �� (A[j, n+1] - t) / A[j, j]		*/
    for (int i=n; i>=1; i--)
    {
        double	t = 0;
        for (int j=i+1; j<=n; j++)
        {
            t = t + A[i][j]*C[j];
        }
        C[i] = (A[i][n+1] - t) / A[i][i];
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

        double	**A,  *B;
        cout << "\n\n\n	�������Ԫ����ʽ������: ";
        int n;
        cin >> n;

        A = new double*[n+1];//��
        assert (A);
        for (int i=0; i <n+1; i++)
        {
            //��
            A[i] = new double[n+2];
            assert (A[i]);
        }
        B = new double[n+1];//
        assert (B);

        for (int i=1; i <n+1; i++)
        {
            for (int j=1; j<n+1; j++)
            {
                A[i][j] = rand()%20+1;
            }
            B[i] = rand()%100+1;
        }
        for (int i=1; i <n+1; i++)
        {
            for (int j=1; j<n+1; j++)
            {
                cout << A[i][j] << "	";
            }
            cout << B[i];
            cout << endl;
        }

        BetterGaussElimination(A, B, n );

        cout <<"\n\n	�����ǵȼ۾������£���\n";
        for (int i=1; i <n+1; i++)
        {
            int j=1;
            for (; j<n+2; j++)
            {
                cout << A[i][j] << "	";
            }
            B[i] = A[i][j-1];//B[]�洢������ʽ�ұߵ�ֵ
            //cout << B[i];
            cout << endl;
        }
        //��ⷽ����A[][]--���ϵ��--�Ľ⣬������B[]
        BackwardSubstitution(A, B, n);
        /*	*/
        cout <<"\n\n	���Ϸ�����Ľ�Ϊ�����£���\n";
        for (int i=1; i <n+1; i++)
        {
            cout << "	X"<< i  <<" = " << B[i];
            cout << endl;
        }

        delete B;
        for (int i=0; i <n+1; i++)
            delete A[i];
        delete A;
        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;

    /*	*/
}

