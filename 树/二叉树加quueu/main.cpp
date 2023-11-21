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

queue<BTree>qTree;//��������
void hierarchical_insertion(BTree &root)
{
	BTree newTree;
	char c;
	while (scanf("%c", &c))
	{
		if (c == '\n') break;
		newTree = (BTree)calloc(1, sizeof(Tree));//ÿ��һ���µľ�Ҫ����һ���µ��ڴ�
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
				qTree.pop();//���������˾ͳ��ӻ���һ��Ϊ���ڵ�
			}
			qTree.push(newTree);
		}
	}
}

void PreForeach(BTree root)
{
	//������
	if (root != NULL)
	{
		cout << root->data << " ";
		PreForeach(root->lc);
		PreForeach(root->rc);
	}
	
}

//�������  �����
void MidForeach(BTree root) 
{
	if (root != NULL)
	{
		PreForeach(root->lc);
		cout << root->data << " ";
		PreForeach(root->rc);
	}
}

//�������  ���Ҹ�
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
	//��β���
	hierarchical_insertion(root);
	cout << "ǰ�����:";
	PreForeach(root);
	puts("");
	cout << "�������:";
	MidForeach(root);
	puts("");
	cout << "�������:";
	AfterForeach(root);
	puts("");
	return 0;
}