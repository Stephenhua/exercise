#include <iostream>
using namespace std;

typedef struct BinaryTreeNode
{
	char data;
	BinaryTreeNode * leftChild;
	BinaryTreeNode * rightChild;
}Node;

void MakeBinaryTree(Node** root, char* preOrder, char* midOrder, int length)
{
	if (length == 0)
	{
		(*root) = NULL;
		return;
	}
	(*root) = new Node;
	(*root)->data = *preOrder;

	char * rootplace = strchr(midOrder, (*root)->data);
	if (rootplace == NULL)
	{
		cout << "input wrong order sample!" << endl;
	}
	int leftTreeLength = strlen(midOrder) - strlen(rootplace);
	int rightTreeLength = length - leftTreeLength - 1;

	MakeBinaryTree(&(*root)->leftChild, preOrder + 1, midOrder, leftTreeLength);
	MakeBinaryTree(&(*root)->rightChild, preOrder + leftTreeLength + 1, rootplace + 1, rightTreeLength);
}

void PostTraverse(Node* root)
{
	if (root == NULL)
		return;
	PostTraverse(root->leftChild);
	PostTraverse(root->rightChild);
	cout << root->data;
}

int main(int argc, const char** argv)
{
	char pre[] = "abdeijcfg";
	char mid[] = "dbiejafcg";
	Node* r;
	MakeBinaryTree(&r, pre, mid, strlen(pre));
	PostTraverse(r);
	system("pause");
	return 0;
}