#ifndef _MATRIX_H_
#define _MATRIX_H_
# include "pch.h"
using namespace std;
class Matrix{
private:
	int rows_num, cols_num;
	double **p;
	void initialize();
public:
	Matrix(int, int);
	Matrix(int, int, double);
	virtual ~Matrix();
	Matrix& operator=(const Matrix&);//copy the matrix 
	Matrix & operator=(double*);//trasmitting the value to the matrix
	Matrix& operator+=(const Matrix&);
	Matrix&operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix operator*(const Matrix&) const;
	static Matrix Hadamand(const Matrix & m, const Matrix&n);
	static Matrix Solve(const Matrix&, const Matrix&);//sloving the liner function Ax=b;
	void Show() const;//show the matrix;
	void swapRows(int, int);
	double det();//soving the det
	double Point(int i, int j)const;
	static Matrix inv(Matrix);//sloving the matrix ni ;



};
#endif