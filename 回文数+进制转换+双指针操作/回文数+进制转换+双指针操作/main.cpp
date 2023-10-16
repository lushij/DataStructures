#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

//判断是否为回文数字
bool isNum(vector<int>k)
{
    //类似双指针方法
    int i = 0;
    int j = k.size() - 1;
  /*  while (i < j)
    {
        if (k[i++] == k[j--]);
        else return false;
    }
    return true;*/

   ////方法二
   // for (i = 0; i < j; i++)
   // {
   //     if (k[i] == k[j - i]);
   //     else return false;
   // }
   // return true;

    ////方法三
    ////转换字符串
    //string s;//存储原始的数据 
    //for (int x : k)
    //{
    //    s.push_back(x);
    //}
    //string st = s;//用来存储翻转的字符串
    //reverse(st.begin(), st.end());
    //return s == st;
}

//itoa的实现
vector<int> Myitoa(int num, int n)
{
    vector<int>a;
    do {
        a.push_back(num % n);
        num /= n;
    } while (num != 0);
    reverse(a.begin(), a.end());//逆序存储或者顺序存储逆序打印也行
    return a;
}

int main()
{
    int num = 0;//数字
    int cnt = 0;//转换的进制
    cin >> num >> cnt;
    vector<int>ret = Myitoa(num, cnt);
    isNum(ret) ? puts("Yes") : puts("No");
    for (int i : ret)
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}