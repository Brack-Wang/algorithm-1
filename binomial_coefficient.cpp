
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <limits.h>
#include <cassert>
using namespace std;

typedef	int* TypePoint;
TypePoint* binomialData = NULL;

int DoBinomial(int n ,int k)
{
	for (int i=0; i<=n; i++)
	{
		for (int j=0; j<= (i<k ? i:k); j++)
		{
			if (j==0 || j==i)
				binomialData[i][j] = 1;
			else
				binomialData[i][j] = binomialData[i-1][j-1]+binomialData[i-1][j];
		}
	}
	return	binomialData[n][k];
}
int main()
{
	char c;
	do
	{
		system("cls");

		cout << "\n\n\n	���������ʽϵ��C(n,k)��n ,k ��ֵ��";
		int		n , k;
		cin >> n >> k;
		binomialData = new int*[n+1];
		assert (binomialData);
		for (int i=0; i<n+1; i++)
		{
			binomialData[i] = new int [k+1];
		}

		for (int i=0; i<=n; i++)
		{
			for (int j=0; j<=k; j++)
				binomialData[i][j] = 0;
		}

		cout << "\n	����ʽϵ��C(n,k)��ֵ��" << DoBinomial(n ,k) << endl;
		for (int i=0; i<=n; i++)
		{
			cout << "	";
			for (int j=0; j<=k; j++)
				cout << "   " << binomialData[i][j];
			cout << endl;
		}

		for (int i=0; i<=n; i++)
			delete[] binomialData[i];
		delete[] binomialData;

		cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

	}while( (c=getch())!=27 );
	return 0;
	

}


