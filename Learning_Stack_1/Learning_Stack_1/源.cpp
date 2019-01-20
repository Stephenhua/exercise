# include <iostream>
# include <stack>
using namespace std;

//检查表达式括号匹配，可以兼顾三种括号
bool paren(const char exp[], int lo, int hi)
{
	stack<char > s;
	for(int i = lo; i <= hi; i++)
		{
			switch (exp[i])//左括号直接进栈，右括号若与栈顶失配，则表达式必定不匹配
			{
			case'(':case'[':case'{':s.push(exp[i]); break;
			case')':if ((s.empty()) || ('(' != s.pop()))return false; break;
			case']':if ((s.empty()) || (']' != s.pop()))return false; break;
			case'}':if ((s.empty()) || ('}' != s.pop()))return false; break;
			default:break;//非括号一律忽略
			}
			return s.empty();//整个表达式扫描过后，栈中若残留（左）括号，则不匹配；否则（栈空）匹配
		}

}