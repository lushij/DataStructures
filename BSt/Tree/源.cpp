#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
#include<vector>
#include<string>
#include<map>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    vector<int> _preorder;
    vector<int> _inorder;
    map<int, int>p;//映射
    TreeNode* dfs(int al, int ar, int bl, int br)
    {
        if (al > ar)
        {
            return nullptr;//回溯
        }
        auto root = new TreeNode(_preorder[al]);//根
        int k = p[root->val];//找到中序根的位置
        auto left = dfs(al + 1, al + k - bl, bl, k - 1);//左边部分
        auto right = dfs(al + k - bl + 1, ar, k + 1, br);//右边部分
        root->left = left;
        root->right = right;
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        _preorder = preorder;//先转换为成员
        _inorder = inorder;
        for (int i = 0; i < inorder.size(); ++i)
        {
            p[inorder[i]] = i;//存入映射
        }
        return dfs(0, preorder.size() - 1, 0, inorder.size() - 1);

    }
};

//给定：
//前序遍历是：[3, 9, 20, 15, 7]
//中序遍历是：[9, 3, 15, 20, 7]

int main()
{
    vector<int>a = { 3, 9, 20, 15, 7 };
    vector<int>b = { 9, 3, 15, 20, 7 };
    Solution s;
    TreeNode*Head= s.buildTree(a, b);
	return 0;
}