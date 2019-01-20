# include <iostream>
using namespace std;

template <class T>
class matrix
{
	friend ostream& operator<<(ostream&, const matrix<T>&)
public:
	matrix(int theRows = 0, int theColums= 0);
	matrix(const matrix<T>&);
	~matrix(){ delete[] element; }
	int rows() const { return theRow; }
	int colums() const{ return theColums; }
	T &operator)(int i, int j) const;
	matrix<T>& operator=(const matrix<T>&);
	matrix<T>operator+()const;
	matrix <T>operator+(const matrix<T>&)const;
	matrix<T> operator-()const;
	matrix<T> operator-(const matrix<T>&)const;
	matrix<T> operator*(const matrix<T>&)const;
	matrix<T>&operator+=(const T&);
private:
	int theRows, theColums;
	T *elements;
};