
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits.h>
#include <cmath>
using namespace std;


//#define	INT_MAX		32767

/**
** Դ�ļ��� shortest_path.cpp
** ����˵����
** ���Գ������·��������������Floyd�㷨��Dijkstra�㷨��������´��롣
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

int 	**W = NULL,  **D = NULL;
char	**DPath = NULL;


typedef	struct G_Chart
{
	bool	*flag;	//��ʶ��Ӧ�ĵ��Ƿ񱻼����ˡ�
	int 	**A;	//��ŵ㼯������
	int 	points;	//��¼���ٸ���

	G_Chart()
		: flag(NULL), A(NULL), points(0)
	{}

} G_Chart;

G_Chart		G;
int 		*Q, *P;

void Delete_Data(int points )
{
	for (int i=0; i < points; i++)
	{
		delete[] W[i];
		delete[] D[i];
		delete[] G.A[i];
	}
	if (W) delete[] W;
	if (D) delete[] D;
	if (G.A) delete[] G.A;
}

template<class T>
void Print_W( T **W, int points)
{
	cout << "\n\n";
	for (int i=0; i < points; i++)
	{
		cout << "	";
		for (int j=0; j< points; j++)
		{/**/
			if (W[i][j]==INT_MAX)
				cout << "��";
			else
				cout << W[i][j];
			cout << "  ";
		}
		cout << endl;
	}
}
void Print_PQ()
{
	for (int i=0; i < G.points; i++)
		cout << "	" << P[i] << ": " << Q[i] << endl;
}

void Floyd(int **D, char **DPath, int points)
{
	for (int i=0; i < points; i++)
		for (int j=0; j< points; j++)
			for (int k=0;k< points;k++)
			{
				//D[j][k] = MIN( D[j][k], (D[j][i]+D[i][k]) );
				if ( D[j][k] > ((__int64)D[j][i]+D[i][k]) )
				{// ע�����ϼӷ����ֹ��������
					D[j][k] = D[j][i]+D[i][k];
					DPath[j][k] = DPath[i][k];
				}
			}
	return;
}
void Print_DPath(char** DPath, int points)
{
	for (int i=0; i < points; i++)
	{
		cout << "	";
		for (int j=0; j< points; j++)
			cout << DPath[i][j] << "  ";
		cout << endl;
	}
}

void Init_WD( int points )
{
	W = new int* [points];
	D = new int* [points];
	DPath = new char* [points];

	for (int i=0; i < points; i++)
	{
		W[i] = new int [points];
		D[i] = new int [points];
		DPath[i] = new char [points];
	}
	for (int i=0; i < points; i++)
	{
		for (int j=i; j< points; j++)
		{
			if ( i==j )
			{
				D[j][i] = D[i][j] = W[j][i] = W[i][j] = 0;
			}/**/
			else
			{
				if ( rand()%2 ==0 )//
					D[j][i] = D[i][j] = W[j][i] = W[i][j] = INT_MAX;//continue;
				else
					D[j][i] = D[i][j] = W[j][i] = W[i][j] = rand()%20+1;
			}
		}
		for (int k=0;k< points;k++)
			DPath[i][k] = 'A' + i;
	}
}

int DeleteMin( int *Q, bool *flag, int points )//queue<int>& Q
{
	int 	min_i = -1, min = INT_MAX;
	for (int i=0; i < points; i++)
	{
		if ( flag[i]==false && min > Q[i] )
		{
			min = Q[i];
			min_i = i;
		}
	}
	if ( min_i!=-1)
		flag[min_i] = true;

	return	min_i;
}

void Init_QPFlag(int *Q, int *P, int points)//,int from
{/*
	for (int i=0; i < from; i++)
		G.flag[i] = true;
*/
	for (int i=0; i < points; i++)
	{
		Q[i] = INT_MAX;
		P[i] = -1;//
		G.flag[i] = false;
	}
}
void Decrease(int *Q, int s, int d )
{
	Q[s] = d;
}
void Dijkstra( G_Chart& G )//,int s
{
	Q = new int [G.points];
	P = new int [G.points];

	for (int s=0; s< G.points;s++)
	{
		Init_QPFlag( Q, P, G.points );
		Decrease(Q, s, 0 );//Q[0] = 0;

		for (int i=0; i < G.points-1; i++)
		{
			int 	u = DeleteMin(Q, G.flag, G.points);
			if ( u==-1 )
			{
				//cout << "\n	�Ҳ�����С�ڵ���� break \n";
				break;
			}
			for (int j=0; j< G.points; j++)
			{
				if ( G.flag[j]==false && ((__int64)Q[u]+G.A[u][j])<Q[j])
				{	// ע�����ϼӷ����ֹ��������
					P[j] = u;
					Decrease(Q, j, Q[u]+G.A[u][j] );//Q[j] = Q[u]+G.A[u][j];
				}
			//system("pause");
			}
		}
		for (int i=0; i < G.points; i++)
		{
			G.A[i][s] = G.A[s][i] = Q[i];
		}
// 		cout << "\n	  --- �ҵ�һ�����·�� ---\n";//
// 		Print_PQ();//
	}
}

void Init_G_Chart(int points)
{
		//Ϊ G ����ռ�
	G.A = new int*[points];
	G.flag = new bool[points];
	G.points = points;

	for (int i=0; i < points; i++)
	{
		G.A[i] = new int [points];
		G.flag[i] = false;
	}
	for (int i=0; i < G.points; i++)
		for (int j=i; j< G.points; j++)
		{
			G.A[i][j] = G.A[j][i] = W[i][j];
		}
}

int main()
{
	time_t		t;
    srand((unsigned) time(&t));

	char c;
	do
	{
		int 	points;
		do
		{
			system("cls");
			cout << "\n\n\n	�������������ĵ���( > 0 ) ��";
			cin >> points;
		} while( points <=0 );
		//ΪW ����ռ䣬�ҳ�ʼ����
		Init_WD( points);
		cout << "\n	�������ͼ��Ȩ�ؾ��� ";
		Print_W( D, points );
		Print_DPath(DPath, points);
		//
		Floyd(D, DPath, points);
		cout << "\n	��Floyd�㷨��ø�ͼ�ľ������ ";
		Print_W( D, points );
		Print_DPath(DPath, points);
		/**/
		Init_G_Chart(points);
		//Print_W( G.A, points );
		Dijkstra(G);//
		cout << "\n	��Dijkstra�㷨��ø�ͼ�ľ������ \n";//
		Print_W( G.A, points );//
		//Print_PQ();


		Delete_Data( G.points );
		cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

	}while( (c=getch())!=27 );
	return 0;
}
