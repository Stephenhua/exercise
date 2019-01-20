# include <iostream>
# include <stack>
using namespace std;

//�����ʽ����ƥ�䣬���Լ����������
bool paren(const char exp[], int lo, int hi)
{
	stack<char > s;
	for(int i = lo; i <= hi; i++)
		{
			switch (exp[i])//������ֱ�ӽ�ջ������������ջ��ʧ�䣬����ʽ�ض���ƥ��
			{
			case'(':case'[':case'{':s.push(exp[i]); break;
			case')':if ((s.empty()) || ('(' != s.pop()))return false; break;
			case']':if ((s.empty()) || (']' != s.pop()))return false; break;
			case'}':if ((s.empty()) || ('}' != s.pop()))return false; break;
			default:break;//������һ�ɺ���
			}
			return s.empty();//�������ʽɨ�����ջ���������������ţ���ƥ�䣻����ջ�գ�ƥ��
		}

}