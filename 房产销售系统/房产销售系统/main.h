#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
//房源信息
//source.txt
struct PropertyInfo {
	int id;
	char direct[20];//朝向
	char floor[12];
	char Sarea[20];
	int price;
	int cnt;//有购买意向的人数
};

//客户信息
//guest.txt
struct PeopleInfo {
	char phone[12];
	char name[20];
	char hnum[128];//住房编号
	int num;//通话次数
	char time[256];//最近电话回访日期
};

//已销售房产的信息
//sold.txt
struct soldInfo {
	int id;
	char Sarea[20];
	int price;
	char time[256];//售出时间
	char Cno[128];//合同号
	char hname[256];//房主姓名
	char phone[12];
};

//链表
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
//创建Prolist头结点
Prolist* createProHeadList();
//创建Prolist节点
Prolist* createProNode(PropertyInfo data);
//添加Prolist信息
void insertProlist(Prolist*& Head, PropertyInfo data);
//遍历房地产信息
void insearchPro(Prolist* Head);
//链表读取Source文件操作
void readSource(Prolist* headNode, const char* fileURL);
//链表写Source文件
void saveSource(Prolist* headNode, const char* fileURL);


//创建Peolist头结点
Peolist* createPeoHeadList();
//创建Peolist节点
Peolist* createPeoNode(PeopleInfo data);
//添加Peolist信息
void insertPeolist(Peolist*& Head, PeopleInfo data);
//遍历客户信息
void insearchPeo(Peolist* Head);
//链表读取Source文件操作
void readGuest(Peolist* headNode, const char* fileURL);

void saveGuest(Peolist* headNode, const char* fileURL,const char*t);

//创建slist头结点
slist* createSHeadList();
//创建slist节点
slist* createSNode(soldInfo data);
//添加slist信息
void insertSlist(slist*& Head, soldInfo data);
//链表读取sold文件操作
void readSold(slist* headNode, const char* fileURL);
//链表写sold文件
void saveSold(slist* headNode, const char* fileURL);