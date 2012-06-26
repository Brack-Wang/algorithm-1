// test_special_sort.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h>

using namespace std;
int test_special_sort()
{
	// �����ԣ�http://groups.google.com/group/pongba/t/54146dfb71a67827
	// ����������Ŀ˵�����밴������˳��������ǵ����֣�Ҫ��O(N)ʱ�䡣
	// ��������names�����μ���ranks�����£�

	string names[] = {"�ź���", "���", "�����", "����ӱ", "������", "���غ�" };
	unsigned ranks[] = { 3, 2, 4, 0, 5, 1};
	assert (sizeof(ranks) / sizeof(ranks[0]) == sizeof(names) / sizeof(names[0]) );
	const all_count = sizeof(ranks) / sizeof(ranks[0]);

	// �ⷨһ�����ı�ԭ������˳��O(N)ʱ�䣬 O(N)�ռ䡣
	vector<unsigned> ranks_bak(all_count);
	for (size_t i = 0; i < all_count; ++i)
	{	// �����±��൱�������������¿ռ�������˳���¼������������
		ranks_bak[ranks[i]] = i;
	}
	// ��������
	for (size_t i = 0; i < all_count; ++i)
		std::cout << names[ranks_bak[i]] << " ";
	std::cout << "\n";

	//////////////////////////////////////////////////////////////////////////

	// �ⷨ������λ�������򣬸ı�ԭ������˳��O(N)ʱ�䣬 O(1)�ռ䡣
	for (size_t i = 0; i < all_count; ++i)
	{
		// ÿ��swapȷ��һԪ��λ�ã���๲N��swap��ȫ����λ��
		while (i != ranks[i])
		{
			std::swap(names[ranks[i]], names[i]);
			std::swap(ranks[ranks[i]], ranks[i]);
			//std::cout << " ranks[i]:" << ranks[i] << "\n";
		}
	}
	// ��������
	for (size_t i = 0; i < all_count; ++i)
		std::cout << names[i] << " ";
	std::cout << "\n";



// ��үү(Knuth)֤�����κλ��ڱȽϵ����򲻿���С��O(N \lg N)ô��
// ������֮���Կ���O(N)���������Ϊ��Ԫ�ص������ԣ�����һ����С�ķ�Χ֮�ڡ�
	return 0;
}

int main(int argc, char* argv[])
{
	test_special_sort();
	/**     */
	cout << "\n Input any char to end.\n" << endl;
	getch();
	return 0;
}

