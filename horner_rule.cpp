
/*
Using Horner's Rule evaluating a polynomial p(x) at x = a;
 then compute the quotient and the remainder of the division of p(x) by x - a;(x-a !=0)
 the coefficients of the polynomial is produced by random;
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

/**
** Դ�ļ��� horner_rule.cpp
** ����˵����
** ���Գ��򣬻��ɷ������ڼ������ʽֵ��һ�ֹ��ϵ��㷨����ȴʮ�����ź͸�Ч��
** ���ɷ�����һЩ���õĸ���Ʒ�������ж���ʽP(x)���ڼ���P(a)��ֵ���̲������м����֣�
	����֯��ΪP(X)����X-a����������������㷨��������ơ�6.5.1���ɷ���
** ���ڻ��ɷ������http://baike.baidu.com/view/3060869.htm
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

typedef	unsigned int ParmaType;

ParmaType Horner(ParmaType H[], int n, ParmaType x, vector<ParmaType>& h_vec)
{
    ParmaType	result = H[n];
    for (int i=n-1; i>=0; i--)
    {
        h_vec.push_back(result);
        result = x * result + H[i];
    }
    return	result;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    char c;
    do
    {
        system("cls");
        cout << "\n\n\n	���������ʽ������ݣ�";
        int n;
        ParmaType P;
        cin >> n;
        ParmaType*	hData = new ParmaType[n+1];
        assert (hData);
        vector<ParmaType>	hVec;
        cout << "\n ��������Ķ���ʽP(x)Ϊ��";
        for (int i=n; i>=0; i--)
        {
            hData[i] = rand()%100;
            cout << hData[i] << "X^" << i;
            if (i!=0)
                cout  << " + ";
        }

        cout << "\n	������X=a��ֵ��";
        int x;
        cin >> x;

        P = Horner(hData, n, x, hVec);

        cout << "	��X = " << x << " ʱ������ʽ��ֵΪ��" << P << endl;
        cout << "\n ����ʽP(x)����X-a�̣�";
        for (int i=0; i<hVec.size(); i++)
        {
            cout << hVec[i] << "X^" << n-i-1;
            if (i!=n-1)
                cout  << " + ";
        }
        cout << "\n ����ʽP(x)����X-a������" << P;
        delete[] hData;
        cout << "\n\n	!!!�������������Esc�˳�����!!!" << endl;

    }
    while( (c=getch())!=27 );

    return 0;
}
