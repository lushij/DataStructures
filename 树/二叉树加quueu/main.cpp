#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<queue>
using namespace std;

typedef struct Tree_t {
	char data;
	Tree_t* lc, * rc;
}Tree,*BTree;

queue<BTree>qTree;//辅助队列
void hierarchical_insertion(BTree &root)
{
	BTree newTree;
	char c;
	while (scanf("%c", &c))
	{
		if (c == '\n') break;
		newTree = (BTree)calloc(1, sizeof(Tree));//每来一个新的就要申请一个新的内存
		newTree->data = c;
		if (root == NULL)
		{
			root = newTree;
			qTree.push(newTree);
		}
		else
		{
			if (qTree.front()->lc == NULL)
			{
				qTree.front()->lc = newTree;
			}
			else
			{
				qTree.front()->rc=newTree;
				qTree.pop();//右子树满了就出队换下一个为根节点
			}
			qTree.push(newTree);
		}
	}
}

void PreForeach(BTree root)
{
	//根左右
	if (root != NULL)
	{
		cout << root->data << " ";
		PreForeach(root->lc);
		PreForeach(root->rc);
	}
	
}

//中序遍历  左根右
void MidForeach(BTree root) 
{
	if (root != NULL)
	{
		PreForeach(root->lc);
		cout << root->data << " ";
		PreForeach(root->rc);
	}
}

//后序遍历  左右根
void AfterForeach(BTree root)
{

	if (root != NULL)
	{
		PreForeach(root->lc);
		PreForeach(root->rc);
		cout << root->data << " ";
	}
}
int main()
{
	BTree root = NULL;
	//层次插入
	hierarchical_insertion(root);
	cout << "前序遍历:";
	PreForeach(root);
	puts("");
	cout << "中序遍历:";
	MidForeach(root);
	puts("");
	cout << "后序遍历:";
	AfterForeach(root);
	puts("");
	return 0;
}