# include"matrix.h"
# include <iostream>
# include <vector>

using namespace std;

template <class T>
matrix<T>::matrix(int theRows, int theColums)
{
	if (theRows < 0 || theColuns < 0)
	{
		throw illegalParameterValue("Rows and colums must be >=0");
		}
	if ((theRows == 0 || theColums == 0) && (theRows!= 0 || theColums != 0))
		throw illegalParamerterValue("Eiher both or neither rows and colums shoule be zero");

	this->theRows = theRows;
	this->theColums = theColums;

}

template <class T>
matrix<T>::matrix(const matrix <T>&m)
{
	theRows = m.theRows;
	theColums = m.theColums;
	elements = new T[theRows * theColums];
	copy(m.elements, m.elements + theRows*theColums, elements);

}
//对矩阵的（）操作符重载
template <class T>
T& matrix<T>::operator() (int i, int j) const
{
	if (i<1 || i>theRows || j<1 || j>theColums)
		throw matrixIndexOutOfBounds();
	return elements[(i - 1)*theColums + j - 1];
}

//maitrix add 
template <class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	if (theRows != m.theRows || theColums != m.theColums)
	{
		throw matrixIndexOutOfBounds();

	}
	matrix<T> w(theRows, theColums);
	for (int i = 0; i < theRows*theColums; i++)
	{
		w.elements = elements[i] + m.elements[i];
	}
	return w;

}

//maitrix multiplux
template <class T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	if (theColums != m.theRows)
	{
		throw matrixIndexOutOfBounds();

	}
	matrix<T> w(theRows, theColums);
	
	int ct = 0; cm = 0; cw = 0;
	for (int i = 1; i <= theRows; i++)
	{
		for (int j = 1; j <= m.theColums; j++)
		{
			T sum = elements[ct] * m.elements[cm];
			for (int k = 2; k <= m.elements; k++)
			{
				ct++;
				cm += m.theColums[k];
				sum += elements[ct] * m.elements[cm];
			}
			w.elements[cw++] = sum;
			ct -= theColums - 1;
			cm = j;
		}
		ct += theColums;
		cm = 0;
	}
	return w;
}