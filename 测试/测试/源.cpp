#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
#include<queue>
using namespace std;
typedef struct task_s {
    int netFd;//�����ļ�������
    int size;//���еĳ���
    //pthread_mutex_t mutex;//��
    //pthread_cond_t cond;//��������
}task_t;

queue<task_t>taskQue;
int main()
{
    
  
}