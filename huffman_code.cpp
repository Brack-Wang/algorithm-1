
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <limits.h>
#include <cassert>
using namespace std;

#include "huffman_code.h"

//  ��շ������롣
//---------------------------------------------------------------------------
int mmin( HuffmanTree& t, int i )
{
    int flag;
    unsigned int k = UINT_MAX; // ȡkΪ��С�ڿ��ܵ�ֵ
    for(int j = 1; j<= i; j++)
        if (t[j].weight< k&& t[j].parent == 0)
            k = t[j].weight, flag = j;
    t[flag].parent = 1;
    return flag;
}
//---------------------------------------------------------------------------
void select(HuffmanTree& t, int i, int &s1, int &s2)
{
    // s1Ϊ��С������ֵ�����С���Ǹ�
    s1 = mmin(t, i);
    s2 = mmin(t, i);
    if (s1>s2)
    {
        int j = s1;
        s1 = s2;
        s2 = j;
    }
}
//---------------------------------------------------------------------------
void do_huff_code()
{
	int n = g_codes.size();
    // w���n���ַ���Ȩֵ(��>0), ����շ�����HT, �����n���ַ��ĺշ�������HC
    if (n < 1)
        return;
    int i, m = 2*n-1;
    //g_huff_tree = (HuffmanTree)malloc((m+1)*sizeof(HTNode));
	g_huff_tree.resize(m+1); // 0�ŵ�Ԫδ��
    for(i = 1; i<= n; ++i)
    {
        g_huff_tree[i].weight = g_weights[i-1];//
        g_huff_tree[i].parent = 0;
		g_huff_tree[i].lchild = 0;
        g_huff_tree[i].rchild = 0;
    }
    for(; i<= m; ++i)
        g_huff_tree[i].parent = 0;

    for(i = n+1; i<= m; ++i) // ���շ�����
    {
        // ��HT[1~i-1]��ѡ��parentΪ0��weight��С���������, ����ŷֱ�Ϊs1��s2
		int s1, s2;
        select(g_huff_tree, i-1, s1, s2);
        g_huff_tree[s1].parent = g_huff_tree[s2].parent = i;
        g_huff_tree[i].lchild = s1;
        g_huff_tree[i].rchild = s2;
        g_huff_tree[i].weight = g_huff_tree[s1].weight+g_huff_tree[s2].weight;
    }
    // ��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
    // ����n���ַ������ͷָ������([0]����)
	g_huff_code.resize(n+1);
	std::string temp;
	temp.resize(n);
    for(i = 1; i<= n; i++)
    {
        // ����ַ���շ�������
        int start = temp.size(); // ���������λ��
        for(unsigned c = i, f = g_huff_tree[i].parent; f != 0;
			c = f, f = g_huff_tree[f].parent)
            // ��Ҷ�ӵ������������
            if (g_huff_tree[f].lchild == c)
                temp[--start] = '0';
            else
                temp[--start] = '1';

        g_huff_code[i].assign(temp.begin() + start, temp.end());
    }
}
//---------------------------------------------------------------------------
void menu()
{
    system("cls");
    cout << "\n\n\n\n";
    cout<<"	������������������������������������������������������\n"
        <<"	����ѡ����������Իس�����  0--��ʾ��������         ��\n"
        <<"	���������������������������Щ�������������������������\n"
        <<"	��1--��ʼ������           ��2--��ӱ�������         ��\n"
        <<"	��3--�޸ı�������         ��4--ɾ����������         ��\n"
        <<"	��5--���ı���             ��6--��������             ��\n"
        <<"	��7--�����Զ�����         ��8--�˳�ϵͳ             ��\n"
        <<"	���������������������������ة�������������������������\n";

}

//---------------------------------------------------------------------------
int get_weight()
{
    unsigned int weight;
    int		i  =  0;
    char	ch_num, chars[10]  =  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    cout << "\n��������ַ���Ȩֵ(����)��";
    cin.get(ch_num);
    while(ch_num != '\n')
    {
        if ( !(isdigit(ch_num)) )
        {
            cout << "\n		�Բ���������루Ȩֵ������\n";
            system("pause");
            return -1;
        }
        chars[i++]  =  ch_num;
        cin.get(ch_num);
    }
    weight  =  atoi(chars);

    return weight;
}
//---------------------------------------------------------------------------
int init_huff_code()
{
    g_codes.clear();
    g_weights.clear();

    void	print_HuffmanCode();
    char	ch;
    int		n = 0;//unsigned
    cout << "����������ַ���������Esc�˳���";
    ch  =  getch();
    cout << ch;

    while(ch != 27)
    {
        unsigned int weight = 0;
        int	 nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes.push_back(ch);
        g_weights.push_back(weight);
        do_huff_code();
        cout << "		!��ӱ����ַ��ɹ�! \n\n";

        cout << "�������������ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
        {
            if (ch == g_codes[i])
            {
                cout << "\n	��ӱ����ַ�ʧ�ܣ��ַ���������" << ch <<"���ڣ�����" <<endl;
                system("pause");
                return 0;
            }
        }
    }
    print_huff_code();
    return 1;
}

//---------------------------------------------------------------------------
void print_huff_code()
{
    cout << "\n	  �ַ�  Ȩֵ  ����	���볤��\n" ;

    for(unsigned int m = 1; m<= g_codes.size(); m++) //static_cast<int>(vec_char_size)
    {
        cout << "	   "<< g_codes[m-1] <<setw(7)<<g_weights[m-1]<<setw(7)<< g_huff_code[m]<<setw(7)<<g_huff_code[m].size()<<endl;
    }
    system("pause");
}
//---------------------------------------------------------------------------
int	add_huff_code()
{
    char	ch;
    int		n = 0;//unsigned
    cout << "��������Ҫ��ӵı����ַ���������Esc�˳���";
    ch  =  getch();
    cout << ch;
    for(int i = 0; i<g_codes.size(); i++)
    {
        if (ch == g_codes[i])
        {
            cout << "\n	��ӱ����ַ�ʧ�ܣ��ַ���������" << ch <<"���ڣ�����" <<endl;
            system("pause");
            return 0;
        }
    }

    while(ch != 27)
    {
        unsigned int weight;
        int		nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes.push_back(ch);
        g_weights.push_back(weight);

        do_huff_code();
        cout << "		!��ӱ����ַ��ɹ�! \n\n";

        cout << "�����������Ҫ��ӵı����ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
        {
            if (ch == g_codes[i])
            {
                cout << "\n	��ӱ����ַ�ʧ�ܣ��ַ���������" << ch <<"���ڣ�����" <<endl;
                system("pause");
                return 0;
            }
        }
    }
    print_huff_code();
    return 1;
}
//---------------------------------------------------------------------------
int	modify_huff_code()
{
    int		n = 0;
    int		pos;
	cout << "��������Ҫ�޸ĵı����ַ���������Esc�˳���";
	char	pre_ch;
    pre_ch  =  getch();
    cout << pre_ch;
	char ch = pre_ch;
    while(ch != 27)
    {
        for(pos = 0; pos<g_codes.size(); pos++)
            if (g_codes[pos] == pre_ch)
                break;
        if (pos == g_codes.size())
        {
            cout << "\n��Ǹ��û����Ҫ�޸ĵı����ַ�: "<<ch <<endl;
            system("pause");
            return 0;
        }
        cout << "\n��������ȷ�ı����ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<g_codes.size(); i++)
            if (ch == g_codes[i] && ch != pre_ch)
            {
                cout << "\n	�޸ı����ַ�ʧ�ܣ��ַ���������" << ch <<"���ڣ�����" <<endl;
                system("pause");
                return 0;
            }
        unsigned int weight;
        int		nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        g_codes[pos]  =  ch;
        g_weights[pos]  =  weight;
        do_huff_code();
        cout << "\n		!�޸ı����ַ��ɹ�! ";

        cout << "\n�����������Ҫ�޸ĵı����ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
    }

    print_huff_code();

    return 1;
}
//---------------------------------------------------------------------------
int	delete_huff_code()
{
    char	ch;
    int		n = 0, i = 0;//unsigned
    cout << "��������Ҫɾ���ı����ַ���������Esc�˳���";
    ch  =  getch();
    cout << ch;

    int		delete_flag  =  0;
    while(ch != 27)
    {
        for(i = 0; i<g_codes.size(); i++)
            if (g_codes[i] == ch)
            {
                g_codes.erase(g_codes.begin()+i);//
                delete_flag  =  1;
                break;
            }
        if (delete_flag == 0)
        {
            cout << "\n��Ǹ��û����Ҫɾ���ı����ַ�: " <<ch <<endl;
            system("pause");
            return 0;
        }
        g_weights.erase(g_weights.begin()+i);

        do_huff_code();
        cout << "\n		!ɾ�������ַ��ɹ�! ";

        cout << "\n����������Ҫɾ���ı����ַ���������, Esc�˳���";
        ch  =  getch();
        cout << ch;
    }

    print_huff_code();

    return 1;

}
//---------------------------------------------------------------------------
int	encode_telegra()
{

    string	telegra, telegra_code;

    cout << "\n	��������Ҫ���б���ĵ��� ��";
    getline(cin, telegra);

    for(int i = 0; i<telegra.size(); i++)
    {
        int		character_exist_flag  =  0;
        for(int j = 0; j<g_codes.size(); j++)
            if (telegra[i] == g_codes[j])
            {
                telegra_code.append(g_huff_code[j+1]);
                character_exist_flag  =  1;
            }
        if ( character_exist_flag == 0 )
        {
            cout << "\n��Ǹ��û���ַ�"<<telegra[i]<<"�ı���! "<<endl;
            system("pause");
            return 0;
        }
    }
    cout <<"������Ϊ��";
    cout <<	telegra_code <<endl;
    print_huff_code();

    return 1;
}
//---------------------------------------------------------------------------
int	decode_telegra()
{
    string	telegra_code, str_telegra;
    vector<char>	telegra;
    int		trans_pos = 0;
    int		HT_length  =  2*g_codes.size();//0�ŵ�Ԫδ�ã�
    int		character_exist_flag  =  1;
    int		i = 0, j = 0;

    cout << "\n	��������Ҫ��������ĵ��� ��";
    cin >> telegra_code;

    for(trans_pos = 0, j  =  HT_length-1; trans_pos < telegra_code.size(); trans_pos++)
    {
        character_exist_flag  =  1;
        if (telegra_code[trans_pos] == '1')
            j  =  g_huff_tree[j].rchild;
        else if (telegra_code[trans_pos] == '0')
            j  =  g_huff_tree[j].lchild;

        if (j <=  g_codes.size())
        {
            telegra.push_back(g_codes[j-1]);
            j  =  HT_length-1;
            character_exist_flag = 0;
        }
    }

    if ( character_exist_flag == 1 )
    {
        cout << "\n		��Ǹ���������" <<endl;
        for(i = 0; i<telegra.size(); i++)
            cout << telegra[i];
        cout << "	������" <<endl;

        for(i = 0; i < trans_pos; i++)
            cout << telegra_code[i];
        cout << "�ڴ˳����ˣ�\n";

        return 0;
    }
    cout <<"������Ϊ��";
    for(i = 0; i<telegra.size(); i++)
        cout << telegra[i];
    cout << endl;

    return 1;
}
//---------------------------------------------------------------------------
int auto_huff_code()
{
    string		str_code;
    int 	char_exist_flag  =  1;
    cout << "��������Ҫ���б�����ַ�����";
	cin.ignore(100, '\n');
    getline(cin, str_code, '\n');
    for(int i = 0; i<str_code.size(); i++)
    {
        char_exist_flag  =  1;
        for(int j = 0; j<g_codes.size(); j++)
            if (str_code[i] == g_codes[j])
            {
                g_weights[j]++;
                char_exist_flag  =  0;
            }
        if (char_exist_flag == 1)
        {
            g_codes.push_back(str_code[i]);
            g_weights.push_back(1);
        }
    }
    do_huff_code();
    return 1;
}

//---------------------------------------------------------------------------
void say_goodbye()
{
    cout << "\n		       !!! GOODBYE, BYE-BYE !!!		\n";
}
//---------------------------------------------------------------------------
void do_demo(char which)
{
    switch (which)
    {
    case '0':
        print_huff_code();
        break;
    case '1':
        init_huff_code();

        break;
    case '2':
        print_huff_code();
        add_huff_code();
        break;
    case '3':
        print_huff_code();
        modify_huff_code();

        break;
    case '4':
        print_huff_code();
        delete_huff_code();
        break;
    case '5':
        encode_telegra();
        break;
    case '6':
        print_huff_code();
        decode_telegra();
        system("pause");

        break;
    case '7':
        auto_huff_code();
        print_huff_code();

        break;
    case '8':
        cout << " ... �˳�ϵͳ...\n";

        break;
    default:
        printf(" \n	����������������������ѡ�� !\n");
    }
    cout << endl;
}
//---------------------------------------------------------------------------
int main()
{
    do
    {
		menu();
		char c;
		cin >> c;
        do_demo(c);
		cin.ignore(100, '\n');
    }
	while (true);
	say_goodbye();
    return 0;
}

//---------------------------------------------------------------------------
