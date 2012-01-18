
#include <iostream>
#include <vector>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits.h>

using namespace std;

/**
** Դ�ļ��� min_spanning_tree.cpp
** ����˵����
** ���Գ�����С����������CMST�������Prim�㷨��Kruskal�㷨��
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

// ��������Prim�㷨�����С�������ṹ�壺
// flag�� ��־��Ӧ�ĵ��Ƿ������С���������㣩����
// A[i][j]����ŵ�i����j��Ȩ��
// points����¼����С�������ĵ���
typedef	struct P_Chart
{
    bool	*flag;
    int		**A;
    int		points;
} P_Chart;

// ���һ���ߵ�������
typedef	struct Point
{
    int		P1;
    int		P2;
} Point;
// /*��������Kruskal�㷨�����С�������ṹ�壺
// value ����¼�ߵ�Ȩ��
// point����Ÿñߵ�������
//  */
typedef	struct K_Chart
{
    int		value;
    Point	point;
} K_Chart;
//��ŵ�ļ���--����
typedef	vector<int> Int_Vec;
//��ŵ㼯�ļ���--�������ģ�����
typedef vector<Int_Vec>	Int_Vec_Vec;//

Int_Vec_Vec		int_vec_vec;
Int_Vec		    int_vec;

P_Chart		G,  E;
K_Chart		*K;
int		K_i = 0;
long	distance_P, distance_K;

void Print_P_Chart(const P_Chart& G, const K_Chart *K );


void Merge( K_Chart *K, K_Chart *TR,int i,int m,int n)
{
    // �������K1[i..m]��K1[m+1..n]�鲢Ϊ�����TR[i..n] �㷨10.12
    int j,k,l;
    for (j=m+1,k=i; i <=m&&j<=n; ++k) // ��K1�м�¼��С����ز���TR
    {
        if ( K[i].value < K[j].value )
            TR[k]=K[i++];
        else
            TR[k]=K[j++];

    }
    if (i <=m)
        for (l=0; l<=m-i; l++)
        {
            TR[k+l]=K[i+l]; // ��ʣ���K1[i..m]���Ƶ�TR

        }
    if (j<=n)
        for (l=0; l<=n-j; l++)
        {
            TR[k+l]=K[j+l]; // ��ʣ���K1[j..n]���Ƶ�TR

        }
}

void MSort( K_Chart *K1, K_Chart *K2, int s, int t)
{
    // ��K1[s..t]�鲢����ΪK2[s..t]��
    int m;
    K_Chart *TR2 = new K_Chart[K_i+1];//
    //K_Chart TR2[101];
    if (s==t)
        K2[s]=K1[s];
    else
    {
        m=(s+t)/2; // ��K1[s..t]ƽ��ΪK1[s..m]��K1[m+1..t]
        MSort(K1,TR2,s,m); // �ݹ�ؽ�K1[s..m]�鲢Ϊ�����TR2[s..m]
        MSort(K1,TR2,m+1,t); // �ݹ�ؽ�K1[m+1..t]�鲢Ϊ�����TR2[m+1..t]
        Merge(TR2,K2,s,m,t); // ��TR2[s..m]��TR2[m+1..t]�鲢��K2[s..t]
    }
    delete[] TR2;//
}
/// ������С��������Prim�㷨
///	���룺��Ȩ��ͨͼ G
///	�����E ����� G ����С�������ıߵļ���
void Prim( P_Chart& G, P_Chart& E )
{
    //��ʼ����С���������㼯��
    G.flag[0] = true;

    for (int i=0; i < G.points-1; i++)
    {
        int		P1, P2;
        int		min = INT_MAX;

        for (int j=1; j< G.points; j++)
        {
            if (G.flag[j]==false )
            {
                for (int k=0; k< G.points; k++)
                    if (  G.flag[k]==true )//G.flag[j]==false &&
                    {
                        if ( G.A[j][k] < min )
                        {
                            min = G.A[j][k];
                            P1 = j;
                            P2 = k;
                        }
                    }
            }
        }
        G.flag[P1] = true;
        distance_P += E.A[P1][P2] = E.A[P2][P1] = min;

    }

}
//Point	Find_i( int point )
int		Find_i( int point )
{
    //���ҵ�point ����һ���㼯����int_vec_vec����һ���㼯��
    //���ҳɹ����ظõ㼯λ�ã����򷵻�-1
    for (int i=0; i < int_vec_vec.size(); i++)
        for (int j=0; j< int_vec_vec[i].size(); j++)
        {
            if ( point==int_vec_vec[i][j] )
            {
                //position = i;
                return	i;
            }
        }
    return -1;
}
void Print_Vec()
{
    //������е㼯int_vec_vec
    for (int i=0; i < int_vec_vec.size(); i++)
    {
        for (int j=0; j< int_vec_vec[i].size(); j++)
        {
            cout << int_vec_vec[i][j] <<"  " ;
        }
        cout << endl;
    }

}

void Kruskal( K_Chart *K, P_Chart& E )
{
    /*������С��������Kruskal�㷨
    ���룺��Ȩ��ͨͼ K
    �����E ����� G ����С�������ıߵļ��� */
    for (int i=0; i < E.points; i++)
    {
        E.flag[i] = false;
        for (int j=i; j< E.points; j++)
        {
            E.A[j][i] = E.A[i][j] = INT_MAX;
        }
    }
    MSort( K, K, 0, K_i-1);

    int		k = 0,  counter = 0;
    int		P1;
    int		P2;
    do
    {
        P1 = K[k].point.P1;
        P2 = K[k].point.P2;

        if ( E.flag[P1]==false && E.flag[P2]==false)
        {
            E.flag[P1] = true;
            E.flag[P2] = true;

            int_vec.clear();
            int_vec.push_back(P1);
            int_vec.push_back(P2);
            int_vec_vec.push_back(int_vec);

            counter++;
            distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
            //continue;
        }
        else
        {
            if ( E.flag[P1 ]==false || E.flag[P2]==false)
            {
                int		i;

                if ( E.flag[P1]==false )
                {
                    E.flag[P1] = true;
                    //
                    i  = Find_i(P2);
                    int_vec_vec[i].push_back(P1);
                }
                else//if ( E.flag[P2]==false )
                {
                    E.flag[P2] = true;
                    //
                    i  = Find_i(P1);
                    int_vec_vec[i].push_back(P2);
                }
                distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
                counter++;
            }

            else//if ( E.flag[P1 ]==true && E.flag[P2]==true)
            {
                int		P1_i = Find_i(P1);
                int		P2_i = Find_i(P2);
                if (P1_i != P2_i )
                {
                    if (int_vec_vec[P1_i].size() > int_vec_vec[P2_i].size() )
                    {
                        for (int i=0; i < int_vec_vec[P2_i].size(); i++)
                        {
                            int_vec_vec[P1_i].push_back( int_vec_vec[P2_i][i] );
                        }
                        int_vec_vec.erase(int_vec_vec.begin()+P2_i);//ɾ���㼯
                    }
                    else
                    {
                        for (int i=0; i < int_vec_vec[P1_i].size(); i++)
                        {
                            int_vec_vec[P2_i].push_back( int_vec_vec[P1_i][i] );
                        }
                        int_vec_vec.erase(int_vec_vec.begin()+P1_i);//ɾ���㼯
                    }

                    distance_K += E.A[P1][P2] = E.A[P2][P1] = K[k].value;
                    counter++;
                }
            }
        }
        k++;
    }
    while( counter < E.points-1 );

    return;
}
//ΪG��E ��K����ռ䣬�ҳ�ʼ��������
void Init_P_Chart(int points)
{
    //ΪG��E ��K����ռ�
    G.A = new int*[points];
    E.A = new int*[points];
    G.flag = new bool[points];
    E.flag = new bool[points];
    K = new K_Chart [points*(points-1)/2];

    E.points = G.points = points;

    for (int i=0; i < points; i++)
    {
        G.A[i] = new int [points];
        E.A[i] = new int [points];
        G.flag[i] = E.flag[i] = false;
    }
    //	//Ϊ G, E , K��ʼ��������
    K_i = 0;

    for (int i=0; i < points; i++)
        for (int j=i; j< points; j++)
        {
            E.A[j][i] = E.A[i][j] = INT_MAX;
            if ( i==j )
            {
                G.A[j][i] = G.A[i][j] = 0;
                //continue;
            }/**/
            else
            {
                K[K_i].value = G.A[j][i] = G.A[i][j] = rand()%20+1;
                K[K_i].point.P1 = i;
                K[K_i++].point.P2 = j;
            }

        }

}
//�ͷ�ͼ�Ŀռ�G ��E ��K
void Delete_Chart(int points)
{
    for (int i=0; i < points; i++)
    {
        delete[] G.A[i];
        delete[] E.A[i];

    }
    delete[] K;
    delete[] G.A;
    delete[] E.A;

}
//���ͼP, ͼK
void Print_P_Chart(const P_Chart& G, const K_Chart *K )
{
    cout << "\n\n";
    for (int i=0; i < G.points; i++)
    {
        cout << "	";
        for (int j=0; j< G.points; j++)
        {
            if (G.A[i][j]==INT_MAX)
                cout << "��" <<"  ";
            else
                cout << G.A[i][j] <<"  ";
        }
        cout << endl;
    }
    /*
    for (i=0; i < K_i; i++)
    {
    	cout << "	"<< K[i].point.P1 << " -- " << K[i].point.P2 << " :  " <<K[i].value << endl;
    }
    */
}

int main()
{
    time_t		t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        //��ճ�ʼ��
        int_vec_vec.clear();
        distance_P = 0;
        distance_K = 0;
        int		points;
        do
        {
            system("cls");
            cout << "\n\n\n	�������������ĵ���( > 0 ) ��";
            cin >> points;
        }
        while( points <=0 );
        //ΪG��E ����ռ䣬�ҳ�ʼ��������
        Init_P_Chart( points);
        Print_P_Chart( G, K );


        Prim( G, E );//
        cout << "\n	������������Prim�㷨�����С������Ϊ�����£��� ";//
        Print_P_Chart( E,  K );//
        cout << "	������С������·�����ȣ� " <<  distance_P << endl;//

        Kruskal( K, E );
        cout << "\n	������������Kruskal�㷨�����С������Ϊ�����£��� ";//
        Print_P_Chart( E,  K  );
        cout << "	������С������·�����ȣ� " <<  distance_K << endl;//

        Delete_Chart(points);
        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while((c=getch())!=27 );
    return 0;
}

