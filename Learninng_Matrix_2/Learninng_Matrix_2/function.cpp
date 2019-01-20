#include "matrix.h"
# include "pch.h"
# include <iostream>
using namespace std;

const double EPS = 1e-10;
//��ʼ������Ĵ�С��
void Matrix::initialize()
{
	p = new double*[rows_num];//����rows_num��ָ��
	for (int i = 0; i < rows_num; ++i)
	{
		p[i] = new double[cols_num];//Ϊp[i]���ж�̬�ڴ���䣬��СΪcols
	}
}

//Claim a matrix ,the value is special
Matrix::Matrix(int rows, int cols, double value)
{
	rows_num = rows;
	cols_num = cols;
	initialize();
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			p[i][j] = value;
		}
	}
}
//xigou function 
Matrix::~Matrix()
{

}

//complishment the matrix copy
Matrix&Matrix::operator=(const Matrix& m)
{
	if (this == &m){
		return *this;
	}

	if (rows_num != m.rows_num || cols_num != m.cols_num)//judge rows and cilums of the matrix 
	{
		for (int i = 0; i < rows_num; i++)
		{
			delete[]p[i];//delete the point;
		}
		delete[] p;
		rows_num = m.rows_num;
		cols_num = m.cols_num;
		initialize();
	}
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			p[i][j] = m.p[i][j];
		}
	}
	return *this;
}
// Transmit the value to the matrix

Matrix &Matrix::operator=(double *a)
{
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			p[i][j] = *(a + i*cols_num + j);
		}
		}
	return *this;
}

//operator+=
Matrix& Matrix::operator+=(const Matrix& m)
{
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			p[i][j] += m.p[i][j];
		}
	}
	return *this;
}

//operaor -=
Matrix& Matrix::operator-=(const Matrix& m)
{
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < rows_num; j++)
		{
			p[i][j] -= m.p[i][j];
		}
	}
	return *this;
}

//operator *=
Matrix & Matrix::operator*=(const Matrix&m)
{
	Matrix temp(rows_num, m.cols_num);//if matrix C=AB ,the row of matrix is equal the raw of matrix B,
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			for (int k = 0; k < cols_num; k++)
			{
				temp.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	*this = temp;
	return *this;
}
//Matrix multiplix
Matrix Matrix::operator*(const Matrix & m) const
{
	Matrix ba_M(rows_num, m.cols_num, 0.0);
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < m.cols_num; j++)
		{
			for (int k = 0; k < cols_num; k++)
			{
				ba_M.p[i][j] += (p[i][k] * m.p[k][j]);
			}
		}
	}
	return ba_M;
}

Matrix Matrix::Hadamand(const Matrix&m, const Matrix & n)
{
	if ((m.cols_num != n.cols_num) || (m.rows_num != n.rows_num))
	{
		cout << "the colums of  matrixs must be equal, " << endl;
		abort();
	}
	Matrix ans(m.rows_num, m.cols_num, 0.0);//construct the new matrix;
	for (int i = 0; i < m.rows_num; i++)
	{
		for (int j = 0; j < m.cols_num; j++)
		{
			ans.p[i][j] = m.p[i][j] * n.p[i][j];
		}
	}
	return ans;
}


//Ax=b
Matrix Matrix::Solve(const Matrix&A, const Matrix &b)
{
	for (int i = 0; i < A.rows_num; i++)
	{
		if (A.p[i][i] = 0 = )
		{
			cout << "Please input" << endl;
			for (int j = i + 1; j < A.rows_num; j++)
			{
				for (int k = i + 1; k < A.cols_num; k++)
				{
					A.p[j][k] -= A.p[i][k] * (A.p[j][i] / A.p[i][i]);
					if (abs(A.p[j][k]) < EPS)
						A.p[j][k] = 0;
				}
				b.p[j][0] -= b.p[i][0] * (A.p[j][i] / A.p[i][i]);
				if (abs(A.p[j][0]) < EPS)
				{
					A.p[j][0] = 0;
				}
				A.p[j][i] = 0;
			}
		}

	}

	Matrix x(b.rows_num, 1);
	x.p[x.rows_num - 1][0] = b.p[x.rows_num - 1][0] / A.p[x.rpws_num - 1][x.rows_num - 1];
	if (abs(x.p[x.rows_num - 1][0]) < EPS)
		x.p[x.rows_num - 1][0] = 0;
	for (int i = x.rows_num - 2; i >= 0; i--) {
		double sum = 0;
		for (int j = i + 1; j < x.rows_num; j++) {
			sum += A.p[i][j] * x.p[j][0];
		}
		x.p[i][0] = (b.p[i][0] - sum) / A.p[i][i];
		if (abs(x.p[i][0]) < EPS)
			x.p[i][0] = 0;
	}

	return x;
}

//show the matrix
void Matrix::Show()const
{
	for (int i = 0; i < rows_num; i++)
	{
		for (int j = 0; j < cols_num; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// complish the change of raws

void Matrix::swapRows(int a, int b)
{
	a--;
	b--;
	double *temp = p[a];
	p[a] = p[b];
	p[b] = temp;

}

//caculate the value of det
double Matrix::det() {
	//Ϊ��������ʽ��һ������
	double ** back_up;
	back_up = new double *[rows_num];
	for (int i = 0; i < rows_num; i++) {
		back_up[i] = new double[cols_num];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			back_up[i][j] = p[i][j];
		}
	}
	if (rows_num != cols_num) {
		std::abort();//ֻ�з�����ܼ�������ʽ����������ж�ǿ��ֹͣ����
	}
	double ans = 1;
	for (int i = 0; i < rows_num; i++) {
		//ͨ���б仯����ʽ��ʹ�þ���Խ����ϵ���Ԫ�ز�Ϊ0
		if (abs(p[i][i]) <= EPS) {
			bool flag = false;
			for (int j = 0; (j < cols_num) && (!flag); j++) {
				//�������һ���Խ����ϵ�Ԫ�ؽӽ���0���ܹ�ͨ���б任ʹ�þ���Խ����ϵ�Ԫ�ز�Ϊ0
				if ((abs(p[i][j]) > EPS) && (abs(p[j][i]) > EPS)) {
					flag = true;
					//ע�����л�����,p[i][j]��Ϊp[j][j]��p[j][i]��Ϊp[i][i]
					//�Ծ�������б任
					double temp;
					for (int k = 0; k < cols_num; k++) {
						temp = p[i][k];
						p[i][k] = p[j][k];
						p[j][k] = temp;
					}
				}
			}
			if (flag)
				return 0;
		}
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = i + 1; j < rows_num; j++) {
			for (int k = i + 1; k < cols_num; k++) {
				p[j][k] -= p[i][k] * (p[j][i] * p[i][i]);
			}
		}
	}
	for (int i = 0; i < rows_num; i++) {
		ans *= p[i][i];
	}
	for (int i = 0; i < rows_num; i++) {
		for (int j = 0; j < cols_num; j++) {
			p[i][j] = back_up[i][j];
		}
	}
	return ans;
}

double Matrix::Point(int i, int j)const
{
	return this->p[i][j];
}
/*
Matrix Matrix::inv(Matrix A)
{
	if (A.rows_num != A.cols_num)
	{
		std::cout << "ֻ�з�������������" << endl;
		abort();
	}
	double temp;
	Matrix A_B = Matrix(A.rows_num, A.cols_num);
	A_B = A;
	Matrix B = eye(A.rows_num);
}

*/