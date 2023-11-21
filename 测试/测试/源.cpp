#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<queue>
using namespace std;
typedef struct task_s {
    int netFd;//传递文件描述符
    int size;//队列的长度
    //pthread_mutex_t mutex;//锁
    //pthread_cond_t cond;//条件变量
}task_t;

queue<task_t>taskQue;
int main()
{
    
  
}