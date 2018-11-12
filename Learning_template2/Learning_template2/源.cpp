#include<iostream>
#include<iomanip>
#include<cstdlib>  //使用库函数exit()
using namespace std;
template<typename TYPE> //类模板声明以此开头
class array
{
	int _size;
	TYPE * data;    //区分不同类模板实例的有关类型应使用虚拟类型
public:
	array(int n);
	~array(){ delete[]data; }
	TYPE &operator [](int i);
	int size()const{ return _size; }
};

template<typename TYPE>
array<TYPE>::array(int n)
{
	if (n<1){
		cout << "Error dimension description";
		exit(1);
	}
	_size = n;
	data = new TYPE[_size];
}

template<typename TYPE>
TYPE &array<TYPE>::operator [](int i){
	if (i<1 || i>_size){
		cout << endl << "Subscript out of range";
		delete[]data;
		exit(2);
	}
	return data[i - 1];
}

int main(){
	array<int> a(5);
	int i;
	for (i = 1; i <= a.size(); i++) a[i] = i;
	for (i = 1; i <= a.size(); i++) cout << setw(5) << a[i];
	cout << endl << endl;
	array<double> b(5);
	for (i = 1; i <= b.size(); i++) b[i] = i + i / 10.0;
	cout.precision(2);
	for (i = 1; i <= b.size(); i++) cout << setw(5) << b[i] << ' ';
	cout << endl << endl;

	system("pause");
	return 0;
}
