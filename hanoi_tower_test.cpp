
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cmath>
#include <cassert>

using namespace std;

/**
** Դ�ļ��� hanoi_tower_test.cpp
** ����˵����
** ���Գ��򣬺������ļ��㣨���˴���������ʾ���˹��̡�
** ���ߣ�junkun huang  e-mail��huangjunkun@gmail.com
** �������ڣ�2008-11 /
*/

int loop_num = 0;

unsigned move(char x, int n, char z)
{
	cout << x << "->" << z <<"; "; 
	loop_num++;
	return 1;
}

unsigned hanoi(int n, char x, char y, char z)
{
	/// ��Ϊ�ú����ݹ���õ�Ƶ�ʻ�ܸ����У����ں����ڶ������move_times��ô�ͼӴ��ˣ������ĵݹ���ۣ�
	/// ��ʹ�����������¼���˴���������ݹ鸺������������϶ȡ�
	/// ��Ҫ�������������ȡ�ᡣ
	unsigned move_times = 0;
	if(n == 1)
		move_times += move(x, 1, z);
	else
	{
		move_times += hanoi(n-1, x, z, y);
		move_times += move(x, n, z);
		move_times += hanoi(n-1, y, x, z);
	}
	return move_times;
}

int main()
{
	char c;
	do
	{
		char x = 'A',y = 'B', z = 'C';
		loop_num = 0;
		int	hanoi_num;

		cout <<"	�����뺺ŵ���ϵ�������Ŀ��";
		cin >> hanoi_num;

		hanoi(hanoi_num, x, y, z);	
		cout << "\n\n���˴�����" << loop_num << endl;
		cout << "	!!!�������������Esc�˳�����!!!" << endl;

	}while( (c=getch())!=27 );

	return 0;
}