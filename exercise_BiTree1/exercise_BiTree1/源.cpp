# include <iostream>
#include <malloc.h>

typedef int ElemType;
using namespace std;
typedef struct node
{
	ElemType data;
	struct node *lchild, *rchild, *parent;

}SNode, *STree;

//�����в���һ���ڵ㣬���нڵ㲻������ͬ��ֵ
int tree_insert(STree *root, ElemType e);

//����һ���ؼ����Ƿ���ڶ������У����ڵĻ�����ָ��ýڵ��ָ�룬���򷵻�NULL

STree tree_find(STree root, ElemType e);

//ɾ���ؼ���Ϊe�Ľڵ㣬ɾ���ɹ�����1,���򷵻��㣻
int tree_delete(STree *root, ElemType e);
//ɾ���ڵ�֮����Ȼ��һ�ö��������
void replace_node(STree *root, STree u, STree v);//��v�ڵ����U�ڵ㣻

void mid_travesal(STree root);//�����������


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
�����������ɾ����3�������
1���ýڵ�û�к��ӣ�ֱ��ɾ�������޸��丸�ڵ㡣
2���ýڵ�ֻ��һ�����ӣ����ýڵ�ĺ���ֱ���������ýڵ㴦�����޸ĸ���Ӧ��ָ��
3������z�ڵ����������ӣ�������Ƚϸ��ӣ��ҵ��ýڵ�ĺ��y������y���Һ����滻y�ڵ㣬����y�ڵ��滻z��z��������Ϊy������
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
