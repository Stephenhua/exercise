# include <iostream>
#include <malloc.h>

typedef int ElemType;
using namespace std;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild, *parent;

}SNode, *STree;

//向数中插入一个节点，树中节点不能有相同的值
int tree_insert(STree *root, ElemType e);

//查找一个关键字是否存在二叉树中，存在的话返回指向该节点的指针，否则返回NULL

STree tree_find(STree root, ElemType e);

//删除关键字为e的节点，删除成功返回1,否则返回零；
int tree_delete(STree *root, ElemType e);
//删除节点之后任然是一棵二叉查找树
void replace_node(STree *root, STree u, STree v);//用v节点代替U节点；

void mid_travesal(STree root);//进行中序遍历


int main()
{
	STree root = NULL;
	int data;
	cout << "please input ten inetger numbers:  " << endl;
	for (int i = 0; i < 10; i++)
	{
		cin >> data;
		tree_insert(&root, data);
	}

	STree temp = tree_find(root, 13);
	if (temp != NULL)
	{
		cout << "find this node: " << temp->data << endl;
	}

	cout << " please delete this node :" << endl;
	mid_travesal(root);
	if (tree_delete(&root, 30))
	{
		cout << "\n After delete the number, " << endl;
		mid_travesal(root);
	}
	cout << endl;
	system("pause");
	return EXIT_SUCCESS;

}
int tree_insert(STree *root, ElemType e)
{
	STree temp = (STree)malloc(sizeof(SNode));
	temp->data = e;
	temp->lchild = NULL;
	temp->rchild = NULL;
	temp->parent = NULL;
	if (*root == NULL)
	{
		*root = temp;
		return 1;
	}
	STree x = *root;
	STree y = x;
	while (x != NULL)
	{
		y = x;
		if (x->data == e)
		{
			return 0;
		}
		else if (x->data < e)
		{
			x = x->rchild;
		}
		else
			x = x->lchild;
	}
	if (y->data > e)
	{
		y->lchild = temp;
	}
	else
	{
		y->rchild = temp;
	}
	temp->parent = y;
	return 1;
}
void mid_travesal(STree root)
{
	if (root!=NULL)
	{
		mid_travesal(root->lchild);
		cout << root->data << " ";
		mid_travesal(root->rchild);
	}
}

STree tree_find(STree root, ElemType e)
{
	while (root != NULL&&root->data != e)
	{
		if (root->data > e)
		{
			root = root->lchild;
		}
		else
		{
			root = root->rchild;
		}
	}
	return root;
}
/*
二叉查找树的删除有3中情况：
1、该节点没有孩子：直接删除，并修改其父节点。
2、该节点只有一个孩子：将该节点的孩子直接提升到该节点处，并修改该相应的指针
3、若该z节点有两个孩子：此情况比较复杂，找到该节点的后继y，并用y的右孩子替换y节点，再用y节点替换z，z的左孩子置为y的左孩子
*/
int tree_delete(STree *root, ElemType e)
{
	STree temp = tree_find(*root, e);
	if (temp == NULL)
	{
		return 0;
	}
	if (temp->lchild != NULL && temp->rchild != NULL)
	{
		STree y = temp->rchild;
		while (y->lchild != NULL)
		{
			y = y->lchild;
		}
		if (y != temp->rchild)
		{
			replace_node(root, y, y->lchild);
			replace_node(root, temp, y);
			y->lchild = temp->lchild;
			y->rchild = temp->rchild;
			temp->lchild->parent = y;
			temp->rchild->parent = y;
		}
		else
		{
			replace_node(root, temp, y);
			y->lchild = temp->lchild;
			temp->lchild->parent = y;
		}

	}
	else if (temp->lchild!=NULL||temp->rchild !=NULL)

	{
		if (temp->lchild != NULL)
		{
			replace_node(root, temp, temp->lchild);

		}
		else
		{
			replace_node(root, temp, temp->rchild);

		}
	}
	else
	{
		replace_node(root, temp, NULL);
	}
	free(temp);
	return 1;
}

void replace_node(STree *root, STree u, STree v)
{
	if (u->parent == NULL)
	{
		*root = v;
	}
	else if (u == u->parent->rchild)
		u->parent->rchild = v;
	else
		u->parent->lchild = v;
	if (v != NULL)
	{
		v->parent = u->parent;
	}
}
