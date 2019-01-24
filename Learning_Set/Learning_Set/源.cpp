#  include <iostream>
#  include <set>
using namespace std;
int main()
{
	set<int> s;
	int n=10;
	//cin >> n;
	for (int i = 1; i <= n; i++)
	{
		//int x;
		// cin >> x;
		s.insert(i);
	}
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++)
	{
		printf("%d\n", *it);
	}
	
	cout << "s.begin()" << *s.begin() << endl;

	cout << "lower_bound 3" << *s.lower_bound(3) << endl;

	cout << "upper_bound 3" << *s.upper_bound(3) << endl;

	cout << "find() 3" << *s.find(3) << endl;
	cout << "s.size()" << s.size() << endl;
	
	cout << "4 apperance of times in set £º" << s.count(3) << endl;
	//iterator return back 
	pair<set<int>::const_iterator, set<int>::const_iterator> pr;
	pr = s.equal_range(3);
	cout << "the nubmer bigger than  4 is :" << *pr.first << endl;
	cout << "the first number bigger 5 is " << *pr.second << endl;
	
	
	//delete iterator pointer the value;

	set<int>::iterator first;
	set<int >::iterator second;
	s.erase(s.begin());
	first = s.begin();
	second = s.begin();
	second++;
	second++;
	s.erase(first, second);
	s.erase(8);
	cout << "After delete the value ,the set will become : ";
	for (it = s.begin(); it!= s.end(); it++)
	{
		cout << *it << endl;
	}
	if ((it = s.find(4)) != s.end())
	{
		cout << *it << endl;
	}
	system("pause");
	return 0;

}