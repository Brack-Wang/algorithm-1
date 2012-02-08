
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
int mmin( HuffmanTree t, int i )
{
    // ����void select()����
    int j, flag;
    unsigned int k = UINT_MAX; // ȡkΪ��С�ڿ��ܵ�ֵ
    for(j = 1; j<= i; j++)
        if (t[j].weight<k&&t[j].parent == 0)
            k = t[j].weight, flag = j;
    t[flag].parent = 1;
    return flag;
}
//---------------------------------------------------------------------------
void select(HuffmanTree t, int i, int &s1, int &s2)
{
    // s1Ϊ��С������ֵ�����С���Ǹ�
    int j;
    s1 = mmin(t, i);
    s2 = mmin(t, i);
    if (s1>s2)
    {
        j = s1;
        s1 = s2;
        s2 = j;
    }
}
//---------------------------------------------------------------------------
void do_huff_code(HuffmanTree &HT, HuffmanCode &HC, vector<unsigned int> vec_int, int n)
//void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int* w, unsigned int n)
{
    // w���n���ַ���Ȩֵ(��>0), ����շ�����HT, �����n���ַ��ĺշ�������HC
    int m, i, s1, s2, start;
    unsigned c, f;
    HuffmanTree p;
    char *cd;
    if (n<1)
        return;
    m = 2*n-1;
    HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode)); // 0�ŵ�Ԫδ��
    for(p = HT+1, i = 1; i<= n; ++i, ++p)
    {
        (*p).weight = vec_int[i-1];//
        (*p).parent = 0;
        (*p).lchild = 0;
        (*p).rchild = 0;
    }
    for(; i<= m; ++i, ++p)
        (*p).parent = 0;
    for(i = n+1; i<= m; ++i) // ���շ�����
    {
        // ��HT[1~i-1]��ѡ��parentΪ0��weight��С���������, ����ŷֱ�Ϊs1��s2
        select(HT, i-1, s1, s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight+HT[s2].weight;
    }
    // ��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
    HC = (HuffmanCode)malloc((n+1)*sizeof(char*));
    // ����n���ַ������ͷָ������([0]����)
    huff_code_len_ptr = (int*)malloc((n+1)*sizeof(int));

    cd = (char*)malloc(n*sizeof(char)); // ���������Ĺ����ռ�
    cd[n-1] = '\0'; // ���������
    for(i = 1; i<= n; i++)
    {
        // ����ַ���շ�������
        start = n-1; // ���������λ��
        for(c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)
            // ��Ҷ�ӵ������������
            if (HT[f].lchild == c)
                cd[--start] = '0';
            else
                cd[--start] = '1';
        HC[i] = (char*)malloc((n-start)*sizeof(char));

        huff_code_len_ptr[i]  =  (int)malloc(sizeof(int));
        huff_code_len_ptr[i]  =  n-start-1;//
        // Ϊ��i���ַ��������ռ�
        strcpy(HC[i], &cd[start]); // ��cd���Ʊ���(��)��HC
    }
    free(cd); // �ͷŹ����ռ�
}
//---------------------------------------------------------------------------
void menu()
{
    system("cls");
    //system("color 24");
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

    vec_char.clear();
    vec_int.clear();

    void	print_HuffmanCode();
    char	ch;
    int		n = 0;//unsigned
    cout << "����������ַ���������Esc�˳���";
    ch  =  getch();
    cout << ch;

    while(ch != 27)
    {
        unsigned int weight;
        int		nums;
        if ( (nums = get_weight()) != -1 )
            weight  =  nums;
        else
            return 0;

        vec_char.push_back(ch);
        vec_int.push_back(weight);
        do_huff_code(huff_tree, huff_code, vec_int, vec_char.size());
        cout << "		!��ӱ����ַ��ɹ�! \n\n";

        cout << "�������������ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<vec_char.size(); i++)
        {
            if (ch == vec_char[i])
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

    for(unsigned int m = 1; m<= vec_char.size(); m++) //static_cast<int>(vec_char_size)
    {
        cout << "	   "<< vec_char[m-1] <<setw(7)<<vec_int[m-1]<<setw(7)<< huff_code[m]<<setw(7)<<huff_code_len_ptr[m]<<endl;
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
    for(int i = 0; i<vec_char.size(); i++)
    {
        if (ch == vec_char[i])
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

        vec_char.push_back(ch);
        vec_int.push_back(weight);

        do_huff_code( huff_tree, huff_code, vec_int, vec_char.size() );
        cout << "		!��ӱ����ַ��ɹ�! \n\n";

        cout << "�����������Ҫ��ӵı����ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<vec_char.size(); i++)
        {
            if (ch == vec_char[i])
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
        for(pos = 0; pos<vec_char.size(); pos++)
            if (vec_char[pos] == pre_ch)
                break;
        if (pos == vec_char.size())
        {
            cout << "\n��Ǹ��û����Ҫ�޸ĵı����ַ�: "<<ch <<endl;
            system("pause");
            return 0;
        }
        cout << "\n��������ȷ�ı����ַ���������Esc�˳���";
        ch  =  getch();
        cout << ch;
        for(int i = 0; i<vec_char.size(); i++)
            if (ch == vec_char[i] && ch != pre_ch)
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

        vec_char[pos]  =  ch;
        vec_int[pos]  =  weight;
        do_huff_code(huff_tree, huff_code, vec_int, vec_char.size());
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
    //cin.get(ch);
    //cin.ignore(2, '\n');
    int		delete_flag  =  0;
    while(ch != 27)
    {
        for(i = 0; i<vec_char.size(); i++)
            if (vec_char[i] == ch)
            {
                vec_char.erase(vec_char.begin()+i);//
                delete_flag  =  1;
                break;
            }
        if (delete_flag == 0)
        {
            cout << "\n��Ǹ��û����Ҫɾ���ı����ַ�: " <<ch <<endl;
            system("pause");
            return 0;
        }
        vec_int.erase(vec_int.begin()+i);

        do_huff_code(huff_tree, huff_code, vec_int, vec_char.size());
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
        for(int j = 0; j<vec_char.size(); j++)
            if (telegra[i] == vec_char[j])
            {
                telegra_code.append(huff_code[j+1]);
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
    int		HT_length  =  2*vec_char.size();//0�ŵ�Ԫδ�ã�
    int		character_exist_flag  =  1;
    int		i = 0, j = 0;

    cout << "\n	��������Ҫ��������ĵ��� ��";
    cin >> telegra_code;

    for(trans_pos = 0, j  =  HT_length-1; trans_pos < telegra_code.size(); trans_pos++)
    {
        character_exist_flag  =  1;
        if (telegra_code[trans_pos] == '1')
            j  =  huff_tree[j].rchild;
        else if (telegra_code[trans_pos] == '0')
            j  =  huff_tree[j].lchild;

        if (j <=  vec_char.size())
        {
            telegra.push_back(vec_char[j-1]);
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
    getline(cin, str_code, '\n');
    for(int i = 0; i<str_code.size(); i++)
    {
        char_exist_flag  =  1;
        for(int j = 0; j<vec_char.size(); j++)
            if (str_code[i] == vec_char[j])
            {
                vec_int[j]++;
                char_exist_flag  =  0;
            }
        if (char_exist_flag == 1)
        {
            vec_char.push_back(str_code[i]);
            vec_int.push_back(1);
        }
    }
    do_huff_code(huff_tree, huff_code, vec_int, vec_char.size());
    return 1;
}

//---------------------------------------------------------------------------
void say_goodbye()
{
    cout << "\n		       !!! GOODBYE, BYE-BYE !!!		\n";
}
//---------------------------------------------------------------------------
void play()
{
    menu();
    static int Init_flag  =  0;
    char	c;
    do
    {
        cin >> c;
        cin.ignore(100, '\n');
        if	(c != '1' && Init_flag != 1 && c != '8')
        {
            printf("�ַ�������δ��ʼ��������ѡ�� 1--��ʼ������ !!! \n");
            system("pause");
            menu();
        }

        else
            break;
    }
    while (c != '1' && Init_flag != 1 && c != '8');

    switch (c)
    {
    case '0':
        print_huff_code();
        break;
    case '1':
        init_huff_code();
        Init_flag  =  1;
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
        cout << "\n		���Ƿ����Ҫ�˳�ϵͳ���밴Y(y)ȷ���˳�, ����������˻أ� ";
        cin >> c;
        cin.ignore(100, '\n');
        if (c == 'y'||c == 'Y')
        {
            say_goodbye();
            return ;
        }
        break;
    default:
        printf(" \n	����������������������ѡ�� !\n");

    }
    cout << endl;
    //return 0;
}
//---------------------------------------------------------------------------
int main()
{
    do
    {
        play();
    }
    while (true);
    return 0;
}

//---------------------------------------------------------------------------
