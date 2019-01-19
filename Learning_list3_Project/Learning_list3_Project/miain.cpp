# include "linkList.h"
# include <iostream>
# include <string >
# include <list>

using namespace std;

int main()
{
	LinkList head;
	info val1, val2, val3, val4;
	val1.ID = 1, val1.name = "Jason";
	val2.ID = 2, val2.name = "Kevin";
	val3.ID = 3, val2.name = "July";
	val4.ID = 4, val4.name = "mark";

	cout << "Insert test" << endl;
	head.InsertHead(val1);
	head.PritList();
	head.Insert(val2, 1);
	head.PritList();
	head.Insert(val3, 4);
	head.PritList();
	head.InsertHead(val3);
	head.Insert(val4, 2);
	head.PritList();

	cout << "Reverse test " << endl;
	head.ReverstList();
	cout << "revered linklist is" << endl;
	head.PritList();


	cout << "remove list " << endl;
	cout << "the length of linklist is " << endl;
	cout << head.Length() << endl;
	head.RemoveNode(val4);
	head.PritList();

	cout << "the lenght of list is :" << endl;
	cout << head.Length() << endl;
	head.RemoveNode(val4);
	head.PritList();
	system("pause");
	return 0;
}