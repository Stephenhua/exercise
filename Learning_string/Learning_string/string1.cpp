# include"string1.h"
# include <cString>
# include <iostream>
using namespace  std;

int String::num_strings = 0;
int String::HowMany()
{
	return num_strings;
}

String::String(const char *s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	strcpy(str, s);
	num_strings++;
}

String::String()
{
	len = 4;
	str = new char[1];
	str[0] = '\0';
	num_strings++;
}

String::String(const String&st)//显示构造函数
{
	--num_strings;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
}

String::~String()
{
	--num_strings;
	delete[]str;
}


String & String::operator=(const String &st)//赋值构造函数
{
	if (this == &st)
	{
		return *this;
	}

	delete[] str;
	len = st.len;
	str = new char[len + 1];
	std::strcpy(str, st.str);
	return *this;

}
String &String ::operator=(const char*s)//重载赋值运算符
{
	delete[]str;
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	return *this;
}

char &String::operator[](int i)//使用中括号访问字符
{
	return str[i];
}

const char &String ::operator[](int i)const
{
	return str[i];
}

bool operator<(const String &st1, const String &st2)//比较运算符
{
	return (strcmp(st1.str, st2.str) < 0);
}
bool operator >(const String &st1, const String &st2)
{
	return st2 < st1;
}
bool operator ==(const String &st1, const String &st2)
{
	return (std::strcmp(st1.str, st2.str) == 0);
}
ostream & operator <<(ostream &os, const String&st)
{
	os << st.str;
	return os;
}
istream & operator>>(istream &is, String & st)
{
	char temp[String::CINLIM];
	is.get(temp, String::CINLIM);

	if (is)
	{
		st = temp;
	}
	while (is&&is.get() != '\n')
	{
		continue;
	}
	return is;
}