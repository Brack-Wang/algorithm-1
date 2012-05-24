
#include<iostream>
#include<stack>
#include<string>
#include<cstdlib>
#include <conio.h>
#include<windows.h>
#include<string>
#include <cassert>
using namespace std;


/**
** Դ�ļ��� evaluate_ expr.cpp
** ����˵����
** ���Գ��򣬱��ʽ��ֵ�ⷨ��ջ���ݽṹ����Ӧ�ã���ҪԤ�ȶ��������op�����ȼ���
	1. ��׺���ʽ����׺���ʽ��ת����
	2. ��׺���ʽ��ֵ��
ת��

��׺���ʽ����׺���ʽ��ת��
����Ҫ�ѱ��ʽ����׺���ʽ����ʽת�����ú�׺��ʾ����ʾ�ĵȼ۱��ʽ�������˽�����������ȼ��ͽ���ԡ�
  ���ȼ�����˵��������ǿ�Ⱦ�����ֵ˳�����ȼ��ߵĲ����������ȼ��͵Ĳ���������ֵ�� ������в��������ȼ�һ����
  ��ô��ֵ˳���ȡ�������ǵĽ���ԡ��������Ľ���Զ�������ͬ���ȼ���������ϵ�˳�򣨴��������������ң���
  ת�����̰�����������㷨������׺���ʽ�Ĳ������������������ţ�
	1. ��ʼ��һ���ն�ջ��������ַ��������ÿա�
	2. �����Ҷ�����׺���ʽ��ÿ��һ���ַ���
	3. ����ַ��ǲ�������������ӵ�����ַ�����
	4. ����ַ��Ǹ���������������pop����������ֱ�����������ţ�opening parenthesis�������ȼ��ϵ͵Ĳ���������ͬһ���ȼ����ҽ�Ϸ��š�
	�����������ѹ�루push����ջ��
	5. ����ַ��Ǹ������ţ�����ѹ���ջ��
	6. ����ַ��Ǹ������ţ�closing parenthesis����������������ǰ���������в�������Ȼ���������ӵ�����ַ�����
	7. ������������ַ�����ĩβ���������в���������ӵ�����ַ�����

��׺���ʽ��ֵ
�Ժ�׺���ʽ��ֵ��ֱ�Ӷ���׺���ʽ��ֵ�򵥡��ں�׺���ʽ�У�����Ҫ���ţ����Ҳ����������ȼ�Ҳ�����������ˡ�
�������������㷨�Ժ�׺���ʽ��ֵ��
	1. ��ʼ��һ���ն�ջ
	2. �����Ҷ����׺���ʽ
	3. ����ַ���һ��������������ѹ���ջ��
	4. ����ַ��Ǹ�������������������������ִ��ǡ��������Ȼ��ѽ��ѹ���ջ����������ܹ�������������������׺���ʽ���﷨�Ͳ���ȷ��
	5. ����׺���ʽĩβ���Ӷ�ջ�е������������׺���ʽ��ʽ��ȷ����ô��ջӦ��Ϊ�ա�


** ���ߣ�junkun huang
** �������ڣ�2008-09 ǰ /
*/

double four_operations(double a,char theta,double b);
char pre_proccess(char a,char b);
template <class T>
void out_stack (const stack<T>& s);
int is_symbol (char c);
void say_goodbye();

double evaluate_expr(const std::string& expr )
{
    stack<double> data_stack;
    stack<char>	 symbol_stack, temp_symbols;
    symbol_stack.push('#');
    int mul_flag = 0;

    const char* next_ptr = expr.c_str();
    char symbol, next, pre_next = '#', after_next;
    next = *(next_ptr++);
    while ( next != '#' || symbol_stack.top()!='#')
    {
        if (!is_symbol(next) || (next=='-' && is_symbol(pre_next)) )//����������������ָ��źͼ��ţ���-����
        {
            if (!is_symbol(next) && !isdigit(next) && next!='.' )//�ж��Ƿ�Ƿ��ַ�--��isalpha(next) ||next == ' '
            {
                std::cerr << " 1. The expression of input is error.\n";
                break;
            }
            int j=0;
            char num[10] = {' ',' ',' ',' ',' ',' ',' ',' ',' ',' '} ;//
            while ( isdigit(next) || next == '.'||(next=='-'&&is_symbol(pre_next)))
            {
                num[j] = next;
                j++;
                pre_next = next;
                next = *(next_ptr++);
            }

            if ( num[0]=='-'&& !isdigit(num[1]) )//���ź���Ϊ�Ƿ��ַ�
            {
                std::cerr << " 4. The data after '-' is error.\n";
                break;
            }
            double d_num = atof(num);
            data_stack.push(d_num);
        }
        else switch ( pre_proccess(symbol_stack.top(), next) )
            {
            case '<' ://ջ��Ԫ������Ȩ��
                symbol_stack.push(next);
                pre_next = next;

                if	(mul_flag == 1)
                {
                    next = after_next;
                    mul_flag = 0;
                }
                else
                    next = *(next_ptr++);

                break;
            case '=' ://�����Ų�������һ���ַ�
                if ( (next != '#') )
                    temp_symbols.push( next );
                temp_symbols.push( symbol_stack.top() );
                symbol_stack.pop();
                pre_next = next;

                if	(mul_flag == 1)
                {
                    next = after_next;
                    mul_flag = 0;
                }
                else
                    next = *(next_ptr++);

                break;
            case '>' ://��ջ������������ջ
            {
                if (data_stack.size() < 2 )
                {
                    std::cerr << " 2. The data of input is too little.\n";
                    symbol_stack.pop();
                    break;
                }

                symbol = symbol_stack.top();
                temp_symbols.push(symbol);
                symbol_stack.pop();
                double b = data_stack.top();
                data_stack.pop();
                double a = data_stack.top();
                data_stack.pop();
                if (symbol == '/' && b == 0 )
                {
                    std::cerr << " 3. Division by zero.\n";
                    break;
                }

                data_stack.push(four_operations(a, symbol, b));
                break;
            }

            default:
                std::cerr << "\n 5. The symbol of input is error.\n";
            }

        if ( next=='(' && (isdigit(pre_next)|| pre_next==')') ||(isdigit(next)&& pre_next==')'))
        {
            //�����������������磺(5+6)(3-5)
            after_next = next;
            next = '*';
            mul_flag = 1;
        }
    }

    cout << " The result of the Expression is:\n";
    double ret = data_stack.empty() ? 0 : data_stack.top();
    out_stack (data_stack);
    cout << " At the end the data in stack:\n";
    out_stack (symbol_stack);
    cout << " The sequence of pop from the stack while do calculating:\n";
    out_stack (temp_symbols);

    return ret;
}

int main ()
{
    do
    {
        cin.clear();
        cout << "\n\n\n Input the expression(Tips: q. exit). Expr:";
        std::string expr;
        std::getline(std::cin, expr);
        if ( expr[0]=='q'||expr[0]=='Q'||expr[0]=='27')
            break;
        // ��������ַ� '#'
        expr.push_back('#');
        evaluate_expr(expr);

    }
    while (true);
    /// test-case.
    std::cout << " (1+2-(-1))*5/(3+1) = " << evaluate_expr("(1+2-(-1))*5/(3+1)#") << "\n";
    std::cout << " (5+2)(7-2) = " << evaluate_expr("(5+2)(7-2)#") << "\n";
    std::cout << " ((5+5)/(7-2)) = " << evaluate_expr("((5+5)/(7-2))#") << "\n";
    std::cout << " 2+1*10/5 = " << evaluate_expr("2+1*10/5#") << "\n";
    say_goodbye();
    return 0;
}
int is_symbol (char c)
{
    int flag;
    switch(c)
    {
    case'#' :
    case'+' :
    case'-' :
    case'*' :
    case'/' :
    case'(' :
    case')' :
        flag = 1;
        break;
    default:
        flag = 0;
        break;
    }
    return flag;
}

template <class T>
void out_stack (stack<T> s)
{
    while ( !s.empty() )
    {
        cout << " " << s.top();
        s.pop();
        cout << "\n";
    }
    cout << endl;
}
double four_operations(double a, char symbol, double b)
{
    double sum = 0;
    switch (symbol)
    {
    case '+':
        sum	= a + b;
        break;
    case '-' :
        sum	= a - b;
        break;
    case '*' :
        sum	= a * b;
        break;
    case '/' :
        sum	= a / b;
        break;
    default	:
        assert (false);
    }
    return	sum;
}


char pre_proccess(char a, char b)
{
    if (a == '#' && b == '#')
        return	'=';

    if (a == '#')
        return	'<';
    if (b == '#')
        return	'>';

    if (a == '(' && b == ')')
        return	'=';
    if (a == '(' && b != ')')
        return	'<';
    if (a != '(' && b == ')')
        return	'>';
    if (a == ')')
        return	'>';
    if (b == ')')
        return	'>';
    if (b == '(')
        return	'<';
    if ( (a == '+' && b == '+')||(a == '+' && b == '-')||(a == '-' && b == '-')||(a == '-' && b == '+') )
        return	'>';
    if ( (a == '*' && b == '*')||(a == '*' && b == '/')||(a == '/' && b == '/')||(a == '/' && b == '*') )
        return	'>';
    if ( (b == '+' || b == '-')&&(a == '*' || a == '/') )
        return	'>';
    if ( (a == '+' || a == '-')&&(b == '*' || b == '/') )
        return	'<';

    assert (false);
    return '0';//error
}
void say_goodbye()
{
    std::cout << " Hello Goodbye.\n";
    system("pause");
}
