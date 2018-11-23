# include <iostream>
# include <fstream>
#include <string>
# include <cstdlib>

int main()
{
	using namespace std;
	ifstream fin;
	fin.open("E:\\C++code\\exercise\\strfile\\tobuy.txt");
	if (fin.is_open() == false)
	{
		cerr << "Can't open file,Bye\n";
		exit(EXIT_FAILURE);
	}
	string item;
	int count = 0;
	getline(fin, item, ':');
	while (fin)
	{
		++count;
		cout << count << " : " << item << endl;
		getline(fin, item, ':');

	}
	cout << "Done\n";
	
	fin.close();

	system("pause");
	return EXIT_SUCCESS;
}