//#ifdef _MA_H_
//# define _MA_H_
# include <iostream>
using namespace std;

class Matrix
{
private:
	int m_p[4][4];
	int m_n;
	int m_x;
	int m_row;
	int m_col;
public:
	Matrix(int n, int x, int row, int col);
	void input(int a[][4]);
	void find();
	void show();
};
//#endif
