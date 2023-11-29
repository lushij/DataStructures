#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int signup()
{
    printf("username:");
    char name[128] = { 0 };
    char pwd1[128] = { 0 };
    char checkpwd[128] = { 0 };
    cin >> name;
    cin >> pwd1;
    cin >> checkpwd;
    if (strcmp(pwd1, checkpwd) == 0)
    {
        return 1;
    }
    return 0;
}
int main()
{
    int chose = 0;
    int res;
	while (1)
	{
        printf("1:×¢²á\n2:µÇÂ¼\n");
        scanf("%d", &chose);
        if (chose == 1)
        {
             res = signup();
             if(res == 1)
             {
                 break;
             }
           
        }
        else
        {
            /* res = login(socFd);
             if(res  == 1)
             {
                 break;
             }*/
        }
	}

	return 0;
}