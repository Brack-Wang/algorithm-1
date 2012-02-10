
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <cassert>
using namespace std;

//---------------------------------------------------------------------------
typedef struct
{
    unsigned int weight;
    unsigned int parent, lchild, rchild;
} HTNode; 

typedef std::vector<HTNode> HuffmanTree;	//�洢�շ�����
typedef std::vector<string> HuffmanCode;	//�洢�շ��������

vector<char>			g_codes;
vector<unsigned int>	g_weights;
vector<unsigned int>	g_huff_code_len_ptr;
HuffmanTree		g_huff_tree;
HuffmanCode		g_huff_code;


/**
** Դ�ļ��� huffman_code.cpp. huffman_code.h
** ����˵����
** ���Գ��򣬻���������ļ�Ӧ�ü�����ʾ����������л������Զ����빦��Ч�����£�
��������Ҫ���б�����ַ�����abbcccddddeeeeeffffff
          �ַ�  Ȩֵ  ����      ���볤��
           a      1   1110      4
           b      2   1111      4
           c      3    110      3
           d      4     00      2
           e      5     01      2
           f      6     10      2
** wiki���ܣ�http://zh.wikipedia.org/zh/%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81
** ����ʵ�֣����Դ����ע��˵����

** ���ߣ�junkun huang
** �������ڣ�2008-11 ǰ /
*/

//---------------------------------------------------------------------------
//��������

int mmin( HuffmanTree& t, int i );
void select(HuffmanTree& t, int i, int &s1, int &s2);
void do_huff_code();
void free_data();
int init_huff_code();
void print_huff_code();
int	add_huff_code();
int	modify_huff_code();
int	delete_huff_code();
int	encode_telegra();
int	decode_telegra();
int auto_huff_code();
void menu();
void do_demo();
void say_goodbye();



