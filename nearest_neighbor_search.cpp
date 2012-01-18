
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

/**
** Դ�ļ��� nearest_neighbor_search.cpp
** ����˵����
** ���Գ�������������������������������η���������´��롣
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

//---------------------------------------------------------------------------
//��ṹ
typedef	struct Pair
{
    int		x;
    int		y;
} Pair;

//�����Խṹ
typedef	struct Closest_Pair
{
    Pair	pair_a, pair_b;
    double	distance;
} Closest_Pair;

//��Խṹ
typedef	struct Points
{
    Pair*	p_pair;
    int		pair_nums;//�����Ŀ
} Points;

//---------------------------------------------------------------------------

Points			points;
Closest_Pair	closest_pair;
//int		pair_nums;

//---------------------------------------------------------------------------
double Account_Distance_2(const Pair& A, const Pair& B )
{

    return ( (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y) );

}

//---------------------------------------------------------------------------
void Print_Points(ostream& outs, const Points&	points, const Closest_Pair&	closest_pair )
{
    outs << "\n\n	�������������£�\n";
    for(int i=0; i<points.pair_nums; ++i)
    {
        outs << "   (" << points.p_pair[i].x << ",  " << points.p_pair[i].y << " ) ";
        if((i+1)%5==0)
        {
            outs << endl;
        }
    }
    outs << "\n\n	�����ϵ�Կɵ�������Ϊ�� ( "
    << closest_pair.pair_a.x << ",  " << closest_pair.pair_a.y << " ), ( "
    << closest_pair.pair_b.x << ",  " << closest_pair.pair_b.y << " ) ";
    outs << "\n	�õ�Ծ���Ϊ��" << closest_pair.distance << endl;

}
//---------------------------------------------------------------------------

bool Brute_Force(const Points& points, Closest_Pair& closest_pair, int from, int to)
{


    for(int i=from; i<=to; ++i)
    {
        for(int j=i+1; j<=to; ++j)
        {
            double		next = Account_Distance_2(points.p_pair[i], points.p_pair[j]);//sqrt(  )
            if(closest_pair.distance > next )
            {
                closest_pair.pair_a = points.p_pair[i];
                closest_pair.pair_b = points.p_pair[j];
                closest_pair.distance = next;
            }
        }
    }

    return	true;
}
//---------------------------------------------------------------------------

// ��˳���L���鲢����

void Merge(char sign, Pair SR[], Pair TR[], long i, long m, long n)
{
    // �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
    int j=m+1,k=i;
    for(; i<=m&&j<=n; ++k) // ��SR�м�¼��С����ز���TR
    {

        if(sign=='x')
        {
            if ( SR[i].x < SR[j].x )
                TR[k]=SR[i++];
            else
                TR[k]=SR[j++];
        }
        else
        {
            if ( SR[i].y < SR[j].y )
                TR[k]=SR[i++];
            else
                TR[k]=SR[j++];
        }


    }
    if(i<=m)
    {
        for(int l=0; l<=m-i; l++)
        {
            TR[k+l]=SR[i+l]; // ��ʣ���SR[i..m]���Ƶ�TR

        }
    }
    else  //if(j<=n)
    {
        for(int l=0; l<=n-j; l++)
        {
            TR[k+l]=SR[j+l]; // ��ʣ���SR[j..n]���Ƶ�TR
        }
    }

}
//---------------------------------------------------------------------------

void MSort(char sign, Pair SR[], Pair TR1[], long s,  long t)
{
    // ��SR[s..t]�鲢����ΪTR1[s..t].

    if(s==t)
    {
        TR1[s] = SR[s];
    }
    else
    {
//      int length = t-s+1;//
        Pair* TR2 = new Pair[points.pair_nums];
        long	m = (s+t)/2; // ��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
        MSort(sign, SR, TR2, s, m); // �ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
        MSort(sign, SR, TR2, m+1, t); // �ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
        Merge(sign, TR2, TR1, s, m, t); // ��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]

        delete[] TR2;
    }
}
//---------------------------------------------------------------------------

void Comp_CP(const Points& points, Closest_Pair& closest_pair, int	mid, int mid_value)
{
    int		i,  j;
    int		distance = sqrt( closest_pair.distance );

    i = mid;
    while( i >= 0 && points.p_pair[i].x > (mid_value-distance) )
    {
        j = mid;
        while( points.p_pair[++j].x < (mid_value+distance) && j < points.pair_nums )
        {
            if( points.p_pair[j].y > (points.p_pair[i].y+distance) ||
                    points.p_pair[j].y < (points.p_pair[i].y-distance) )
                //�ж���y���Ƿ����
                continue;

            double		next = Account_Distance_2( points.p_pair[i], points.p_pair[j]);//sqrt( )
            if(closest_pair.distance > next )
            {
                closest_pair.pair_a = points.p_pair[i];
                closest_pair.pair_b = points.p_pair[j];
                closest_pair.distance = next;

                //cout << "Comp_CP:	" << closest_pair.distance << endl;
            }

        }
        i--;
    }


}
//---------------------------------------------------------------------------

void Divide_and_Conquer(const Points& points, Closest_Pair& closest_pair, int from, int to)
{
    if( (to-from+1) <4 )
    {
        /*
        if( (to-from)==1 )
        {
        	double		next = Account_Distance_2( points.p_pair[from], points.p_pair[to]);//sqrt(  )
        	if(closest_pair.distance > next )
        	{
        		closest_pair.pair_a = points.p_pair[from];
        		closest_pair.pair_b = points.p_pair[to];
        		closest_pair.distance = next;
        	}
        	cout << "2	" << closest_pair.distance <<endl;

        }
        else		*/
        {
            Brute_Force(points, closest_pair, from, to );
            //cout << "<4	" << closest_pair.distance << endl;
            //system("pause");
        }

    }
    else
    {
        int		mid = (from+to)/2;
        int		mid_value = points.p_pair[mid].x;

        Divide_and_Conquer(points, closest_pair, from, mid);
        Divide_and_Conquer(points, closest_pair, mid+1, to);
        Comp_CP(points, closest_pair, mid, mid_value);
    }

    return	;
}
//---------------------------------------------------------------------------

int	main()
{
    time_t t;
    srand((unsigned) time(&t));

    char c;
    do
    {
        system("cls");

        cout << "\n\n	��������Ҫ���������ԵĶ����� ";
        cin >> points.pair_nums;
        if (points.pair_nums <= 0 || points.pair_nums > 1000)
        {
            cout << "���������˳�����\n";
            break;
        }

        points.p_pair = new Pair[points.pair_nums];

        for(int i=0; i<points.pair_nums; ++i)
        {
            points.p_pair[i].x= rand()%101;
            points.p_pair[i].y= rand()%101;
        }
        /// ���η���⣬������ȷ������������η���������һ�¡�
        MSort('x', points.p_pair, points.p_pair, 0, points.pair_nums-1 );

        //���������
        cout << "\n\n--- ��������� ---\n";
        closest_pair.distance = ULONG_MAX;//MAX_SIZE
        Brute_Force(points, closest_pair, 0, points.pair_nums-1 );
        closest_pair.distance = sqrt( closest_pair.distance );
        Print_Points( cout,  points, closest_pair );

// 		/// ���η���⣬������
// 		MSort('x', points.p_pair, points.p_pair, 0, points.pair_nums-1 );

        //���η����
        cout << "\n\n--- ���η���� ---\n";
        closest_pair.distance = ULONG_MAX;//MAX_SIZE
        Divide_and_Conquer(points, closest_pair, 0, points.pair_nums-1 );
        closest_pair.distance = sqrt( closest_pair.distance );
        Print_Points( cout,  points, closest_pair );
        delete[] points.p_pair;

        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );
    return 0;
}
//---------------------------------------------------------------------------

