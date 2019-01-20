# include <iostream>
# include "Matrix.h"
int main()
{
	int a[4][4];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cin >> a[i][j];
		}
	}
	Matrix mat(4, 0, 4, 4);
	mat.input(a);
	mat.find();
	mat.show();
	
	system("pause");
	return EXIT_SUCCESS;

}
