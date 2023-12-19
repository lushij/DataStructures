#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
//��Դ��Ϣ
//source.txt
struct PropertyInfo {
	int id;
	char direct[20];//����
	char floor[12];
	char Sarea[20];
	int price;
	int cnt;//�й������������
};

//�ͻ���Ϣ
//guest.txt
struct PeopleInfo {
	char phone[12];
	char name[20];
	char hnum[128];//ס�����
	int num;//ͨ������
	char time[256];//����绰�ط�����
};

//�����۷�������Ϣ
//sold.txt
struct soldInfo {
	int id;
	char Sarea[20];
	int price;
	char time[256];//�۳�ʱ��
	char Cno[128];//��ͬ��
	char hname[256];//��������
	char phone[12];
};

//����
typedef struct PropertyInfolist {
	struct PropertyInfo data;
	struct PropertyInfolist* next;
}Prolist;

typedef struct PeopleInfolist {
	struct PeopleInfo data;
	struct PeopleInfolist* next;
}Peolist;

typedef struct soldInfolist {
	struct soldInfo data;
	struct soldInfolist* next;
}slist;
//����Prolistͷ���
Prolist* createProHeadList();
//����Prolist�ڵ�
Prolist* createProNode(PropertyInfo data);
//���Prolist��Ϣ
void insertProlist(Prolist*& Head, PropertyInfo data);
//�������ز���Ϣ
void insearchPro(Prolist* Head);
//�����ȡSource�ļ�����
void readSource(Prolist* headNode, const char* fileURL);
//����дSource�ļ�
void saveSource(Prolist* headNode, const char* fileURL);


//����Peolistͷ���
Peolist* createPeoHeadList();
//����Peolist�ڵ�
Peolist* createPeoNode(PeopleInfo data);
//���Peolist��Ϣ
void insertPeolist(Peolist*& Head, PeopleInfo data);
//�����ͻ���Ϣ
void insearchPeo(Peolist* Head);
//�����ȡSource�ļ�����
void readGuest(Peolist* headNode, const char* fileURL);

void saveGuest(Peolist* headNode, const char* fileURL,const char*t);

//����slistͷ���
slist* createSHeadList();
//����slist�ڵ�
slist* createSNode(soldInfo data);
//���slist��Ϣ
void insertSlist(slist*& Head, soldInfo data);
//�����ȡsold�ļ�����
void readSold(slist* headNode, const char* fileURL);
//����дsold�ļ�
void saveSold(slist* headNode, const char* fileURL);