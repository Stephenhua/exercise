#  include <iostream>
# include <windows.h>
using namespace std;

int factorial(int n);
int factorial_Recursion(int n);

int factorial(int n)
{
	int ans = 1;
	for (int i = 1; i <= n; i++)
	{
		ans *= i;
	}
	return ans;
}

int factorial_Recursion(int n)
{
	if (n == 1)
		return 1;
	else
		return factorial_Recursion(n - 1)*n;
}
//斐波那契数列
int Fib(int n)//递归数列
{
	if (n < 2)
		return 1;
	return Fib(n - 1) + Fib(n - 2);
}
/*
int main( int n)
{
	double time = 0;
	double counts = 0;
	LARGE_INTEGER nFreq;
	LARGE_INTEGER nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&nBeginTime);
	long double ans,ans1;
	ans = factorial_Recursion(10);
	ans1 = factorial(100);
	cout << "1000！" << ans << endl;
	cout << "1000!" << ans1 << endl;
	QueryPerformanceCounter(&nEndTime);
	time = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / (double)nFreq.QuadPart;
	cout << "程序执行时间：" << time * 1000 << "ms" << endl;
	system("pause");
	return EXIT_SUCCESS;
}
*/
//斐波那契数列
int main()
{
	int n;
	cin >> n;
	int fib1[10], fib2[10];
	fib1[0] = 1;
	fib1[1] = 1;
	fib2[0] = 1;
	fib2[1] = 1;
	for (int i = 2; i < n; i++) {
		fib1[i] = Fib(i);
		fib2[i] = fib2[i - 1] + fib2[i - 2];
	}
	cout << "use func Fib() " << endl;
	for (int i = 0; i < n; i++) {
		cout << fib1[i] << ' ';
	}
	cout << endl;
	cout << "use for loop " << endl;
	for (int i = 0; i < n; i++) {
		cout << fib2[i] << ' ';
	}
	cout << endl;

	system("pause");
	return EXIT_SUCCESS;
}