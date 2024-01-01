#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#define KeyType int
using namespace std;
typedef struct BSTreeNode {
    KeyType val;
    BSTreeNode* left;
    BSTreeNode* right;
    BSTreeNode(KeyType x) : val(x), left(nullptr), right(nullptr) {}
}*BST;

//��һ�֣�����
//int BST_Insert(BST& T, KeyType k)
//{
//    if (nullptr == T)
//    {	
//        BST TreeNew=new BSTreeNode(k);
//        T = TreeNew;
//    }
//    else if (k == T->val)
//        return 0;//������ͬԪ�أ��Ͳ�����
//    else if (k < T->val)//���Ҫ����Ľ�㣬С�ڵ�ǰ���
//        //�������ý��������Ӻ�ԭ���ĸ��׻�����������������������û���
//        return BST_Insert(T->left, k);
//    else
//        return BST_Insert(T->right, k);
//}

//�ڶ���,ָ��
//BST BstInsert(BST T, KeyType k)
//{
//    if (T == nullptr)
//    {
//        return new BSTreeNode(k);
//    }
//    else if (k == T->val)
//    {
//        return nullptr;
//    }
//    else if (k < T->val)
//    {
//        T->left = BstInsert(T->left, k);
//    }
//    else
//    {
//        T->right = BstInsert(T->right, k);
//    }
//    return T;
//}

//������,�㷨����ܼ�����
BST BstInsert(BST T, KeyType k)
{
    if (T == nullptr)
    {
        return new BSTreeNode(k);
    }
    else if (k == T->val)
    {
        return nullptr;
    }
    else if (k < T->val)
    {
        auto left = BstInsert(T->left, k);
        T->left = left;
    }
    else
    {
        auto right = BstInsert(T->right, k);
        T->right = right;
    }
   
   
    return T;
}


//BST��ֻ�����������
void inorderTraversal(BST root)
{
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

int main()
{
    BST Head = nullptr;
    int data[10] = { 54,20,66,40,28,79,58 };
    for (int i = 0; i < 10; ++i) 
    {
       // BST_Insert(Head, data[i]);//��һ��
        Head = BstInsert(Head, data[i]);//�ڶ���
    }
    inorderTraversal(Head);
	return 0;
}