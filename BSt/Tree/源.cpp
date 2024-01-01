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
    map<int, int>p;//ӳ��
    TreeNode* dfs(int al, int ar, int bl, int br)
    {
        if (al > ar)
        {
            return nullptr;//����
        }
        auto root = new TreeNode(_preorder[al]);//��
        int k = p[root->val];//�ҵ��������λ��
        auto left = dfs(al + 1, al + k - bl, bl, k - 1);//��߲���
        auto right = dfs(al + k - bl + 1, ar, k + 1, br);//�ұ߲���
        root->left = left;
        root->right = right;
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        _preorder = preorder;//��ת��Ϊ��Ա
        _inorder = inorder;
        for (int i = 0; i < inorder.size(); ++i)
        {
            p[inorder[i]] = i;//����ӳ��
        }
        return dfs(0, preorder.size() - 1, 0, inorder.size() - 1);

    }
};

//������
//ǰ������ǣ�[3, 9, 20, 15, 7]
//��������ǣ�[9, 3, 15, 20, 7]

int main()
{
    vector<int>a = { 3, 9, 20, 15, 7 };
    vector<int>b = { 9, 3, 15, 20, 7 };
    Solution s;
    TreeNode*Head= s.buildTree(a, b);
	return 0;
}