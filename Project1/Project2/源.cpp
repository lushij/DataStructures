#define _CRT_SECURE_NO_WARNINGS 1
//#include<iostream>
//#include<vector>
//#include<cmath>
//using namespace std;
//int n;
//vector<long>s;
//
//int main()
//{
//    cin >> n;
//    long a, b, c;
//   long long sum = 0;
//    for (int i = 0; i < n; i++)
//    {
//       long long m;
//        cin >> m;
//        a = m / 10;
//        b = m %10;
//        c =pow(a,b);//数值限制
//        s.push_back(c);
//        cout << a << " " << b << " " << c<<endl;
//    }
//    for (auto x : s)  sum += x;
//    cout << sum;
//}
//
//#include<iostream>
//using namespace std;
//int n;
//int main()
//{
//    cin >> n;
//    int res = 0;
//   /* while (n)
//    {
//        if (n % 2 == 0) res++;
//        n /= 2;
//    }*/
//    /*cout << res;*/
//   
//}

#include<iostream>
#include<unordered_set>
using namespace std;
int cnt(int n)
{
    unordered_set<int>s;

    int count = 0;//记录符合要求的数字
    int a = 0;
    int b = 0;
    for (int i = 1; i <= n; i++)
    {
        
        a = i;
        b = i - 1;
        while (b >= 0)
        {
            
            int dfs = a * a - b * b;
            if (dfs > i) {
                a--;
                b--; 
            }
            else if (dfs == i) { 
                count++;
                break;
            } 
            else {
                b--;
            }
        }
      
    }
    return count;
}


int main()
{
    int n;
    cin >> n;
    int num = cnt(n);
    cout << num;
}