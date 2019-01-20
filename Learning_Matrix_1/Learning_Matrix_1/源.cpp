# include <iostream>
# include<stack>

using namespace std;

int main(void)
{
	int numberOfRows = 5;
	int length[5] = { 6, 3, 4, 2, 7 };

	int **irregulerArray = new int *[numberOfRows];

	for (int i = 0; i < numberOfRows; i++)
	{
		irregulerArray[i] = new int[length[i]];
	}

	irregulerArray[2][3] = 5;
	irregulerArray[4][6] = irregulerArray[2][3] + 2;
	irregulerArray[1][1] = 3;

	cout << irregulerArray[2][3] << endl;
	cout << irregulerArray[4][6] << endl;
	cout << irregulerArray[1][1] << endl;
	system("pause");
	return 0;

}


