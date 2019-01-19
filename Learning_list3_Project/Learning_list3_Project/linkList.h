# include <string>
#include <iostream>

using namespace std;
struct info {
	string name;
	int ID;
};
struct Node{
	info val;
	Node *next;
	Node(info x) :val(x), next(NULL){}
};

class LinkList{
public :
	LinkList();
	//�������ͷ������ڵ�
	void InsertHead(info val);
	//����ڵ�
	void Insert(info val, int pos);
	//ɾ���ڵ�
	void RemoveNode(info val);
	//get link length 
	int Length();
	//reverse List
	void ReverstList();
	//find the node in list 
	int FindNode(info val);
	//print list
	void PritList();
	~LinkList();
private:
	Node *head;
	int length;
};