# include "linkList.h"
# include <iostream>
# include <stack>
# include <list>
using namespace std;

LinkList::LinkList()
{
	head = NULL;
	length = 0;
}

LinkList::~LinkList()
{
	Node *temp;
	for (int i = 0; i < length; i++)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

int LinkList::Length()
{
	return length;
}
void LinkList::InsertHead(info val)
{
	Insert(val, 0);
}

void LinkList::Insert(info val, int pos)
{
	if (pos < 0)
	{
		cout << "pos must be greater than 0" << endl;
		return;
	}
	int index = 1;
	Node *temp = head;
	Node *node = new Node(val);
	if (pos == 0)
	{
		node->next = temp;
		head = node;
		length++;
		return;
	}
	while (temp != NULL&&index < pos)
	{
		temp = temp->next;
		index++;
	}
	if (temp == NULL)
	{
		cout << "Insert failed" << endl;
		return;
	}
	node->next = temp->next;
	temp->next = node;
	length++;
}

int LinkList::FindNode(info val)
{
	Node *temp = head;
	int index = 1;
	while (temp != NULL)
	{
		if (temp->val.name == val.name&&temp->val.ID == val.ID)
		{
			return index;
		}
		temp = temp->next;
		index++;
	}
	return -1;
}
//remove Node in list 
void LinkList::RemoveNode(info val){
	int pos = FindNode (val);
	if (pos == -1)
	{
		cout << "Delete failed" << endl;
		return;
	}
	if (pos == 1){
		head = head->next;
		length--;
		return;
	}
	int index = 2;
	Node *temp = head;
	while (index < pos);
	{
		temp = temp->next;
	}
	temp->next = temp->next->next;
	length--;

}
//reverse List 
void LinkList::ReverstList()
{
	if (head == NULL)
	{
		return;
	}
	Node *curNode = head;
	Node *nextNode = head->next;
	Node *temp;
	while (nextNode != NULL)
	{
		temp = nextNode->next;
		nextNode->next = curNode;
		curNode = nextNode;
		nextNode = temp;
	}
	head->next = NULL;
	head = curNode;
}

//printLsit

void LinkList::PritList()
{
	if (head == NULL)
	{
		cout << "LinkList is empty" << endl;
		return;
	}
	Node *temp = head;
	while (temp != NULL)
	{
		cout << temp->val.name<< "," <<  temp->val.ID  << endl;
		temp = temp->next;
	}
	cout << endl;
}