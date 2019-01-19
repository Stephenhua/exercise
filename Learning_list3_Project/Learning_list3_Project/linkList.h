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
	//在链表的头部插入节点
	void InsertHead(info val);
	//插入节点
	void Insert(info val, int pos);
	//删除节点
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