#include <iostream>
#include <string >
# include<cctype>
# include "stacketp.h"

using namespace std;

int main()
{
	Stack<std::string> st;
	char ch;
	std::string po;
	cout << "Please enter A to add a purchase order,\n" << "p to process a P0,or Q to quie .\n";
	while (cin >> ch&&std::toupper(ch) != 'Q')
	{
		while (cin.get() != '\n')
		{
			continue;
		}
		if (!std::isalpha(ch))
		{
			cout << '\a';
			continue;
		}

		switch (ch)
		{
		case 'A':
		case'a':cout << "Enter a po number to add :";
			cin >> po;
			if (st.isfull())
			{
				cout << "Stack already full\n";
			}
			else
			{
				st.push(po);
			}
			break;
		case'P':
		case'p':
			if (st.isempty())
			{
				cout << "Stack already empty.\n";
			}
			else
			{
				st.pop(po);
				cout << "po#" << po << " popped\n";
				break;
			}
		}

		cout << "Please enter A to add a purchase order,\n"
			<< "p oto process a Po,or Q to quit .\n";
	}
	cout << "Bye\n";
	system("pause");
	return EXIT_SUCCESS;
}