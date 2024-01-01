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

//第一种，引用
//int BST_Insert(BST& T, KeyType k)
//{
//    if (nullptr == T)
//    {	
//        BST TreeNew=new BSTreeNode(k);
//        T = TreeNew;
//    }
//    else if (k == T->val)
//        return 0;//发现相同元素，就不插入
//    else if (k < T->val)//如果要插入的结点，小于当前结点
//        //函数调用结束后，左孩子和原来的父亲会关联起来，巧妙利用了引用机制
//        return BST_Insert(T->left, k);
//    else
//        return BST_Insert(T->right, k);
//}

//第二种,指针
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

//第三种,算法题可能见到的
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


//BST树只考察中序遍历
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
       // BST_Insert(Head, data[i]);//第一种
        Head = BstInsert(Head, data[i]);//第二种
    }
    inorderTraversal(Head);
	return 0;
}