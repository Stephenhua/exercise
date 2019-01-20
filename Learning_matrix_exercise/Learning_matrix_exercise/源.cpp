# include "Matrix.h"
#  include <iostream>

using namespace std;
Matrix::Matrix(int n, int x, int row, int col)
{
	m_n = 4;
	m_x = 0;
	m_row = 0;
	m_col = 0;

}

void Matrix::input(int a[][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_p[i][j] = a[i][j];
		}
	}
}

void Matrix::find()
{
	int m_x = m_p[0][0];
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (m_p[i][j] < m_x)
			{
				m_x = m_p[i][j];
				m_row = i;
				m_col = j;
			}
		}

	cout << "x=" << m_x << endl;
	cout << "min_row" << m_row << endl;
	cout << "min_col" << m_col << endl;
}
void Matrix::show()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << m_p[i][j] << endl;
			count++;
		}
		if( count  % 4 == 0)
		{
			cout << endl;
		}
}
}