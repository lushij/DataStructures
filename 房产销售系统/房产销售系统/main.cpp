#include"main.h"
typedef struct cntInfo
{
	int id;//住房编号
	int cnt;
}Cinfo;

typedef struct Cnt_s{
	Cinfo data;
	struct Cnt_s* next;
}Cnt_t;

//创建Cnt_t头结点
Cnt_t* createCnt_tHead()
{
	Cnt_t* HeadList = NULL;
	HeadList = (Cnt_t*)calloc(1, sizeof(Cnt_t));
	HeadList->next = NULL;
	return HeadList;
}

Cnt_t* createCnt_t(Cinfo data)
{
	Cnt_t* newNode = (Cnt_t*)calloc(1, sizeof(Cnt_t));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void insertCnt_t(Cnt_t*& Head, Cinfo data)
{
	Cnt_t* newList = createCnt_t(data);
	newList->next = Head->next;
	Head->next = newList;
}
Cnt_t* chead = createCnt_tHead();
//菜单
void menu()
{
	printf("欢迎来到房产销售管理系统\n");
	printf("   1.新客户登记 \n");
	printf("   2.老客户信息修改\n" );
	printf("   3.提供房源信息查询 \n") ;
	printf("   4.热门房源信息 \n");
	printf("   5.增加销售合同 \n");
	printf("   0.退出系统\n") ;
}

//
//用户交互按键封装
int keyDown()
{
	printf("请选择:");
	int cmd=0;
	scanf("%d", &cmd);
	return cmd;
}

void dealcnt(Cnt_t* &head,int id)
{
	Cnt_t* Move = head->next;
	while (Move)
	{
		if (Move->data.id == id)
		{
			++Move->data.cnt;
		}
		Move = Move->next;
	}
	cntInfo cinfo;
	cinfo.id = id;
	cinfo.cnt = 1;
	insertCnt_t(head, cinfo);
}

void updateProCnt(Cnt_t*& h)
{
	Prolist* head = createProHeadList();
	readSource(head, "source.txt");
	Cnt_t* cnt = h->next;
	Prolist* incnt = head->next;
	while (cnt)
	{
		while (incnt)
		{
			if (incnt->data.id == cnt->data.id)
			{
				incnt->data.cnt = cnt->data.cnt;
			}
			incnt = incnt->next;
		}
		cnt = cnt->next;
	}
	saveSource(head, "source.txt");
}

void newPeoInfo(Peolist *&PeoHead)
{
	system("cls");
	printf("请输入信息:姓名 电话 有购买意向的住房编号(最多3个，用英文逗号隔开)\n");
	PeopleInfo newPeo;
	scanf("%s%s%s", &newPeo.name, &newPeo.phone, &newPeo.hnum);
	char buf[256] = { 0 };
	strcpy(buf, newPeo.hnum);
	char* s = strtok(buf, ",");
	while (s)
	{
		dealcnt(chead,atoi(s));
		s = strtok(NULL, ",");
	}
	updateProCnt(chead);//更新房源信息
	newPeo.num = 0;
	strcpy(newPeo.time, "null");
	insertPeolist(PeoHead, newPeo);
	saveGuest(PeoHead, "guest.txt","a+");
	printf("登记成功\n");
}

void changeData(PeopleInfo &t)
{
	printf("请输入你要更改的数据：1.修改有购买意向的住房编号2.最近修改回访日期3.修改通话次数4.修改客户电话0退出\n");
	int num = 0;
	scanf("%d", &num);
	while (num)
	{
		char buf[256] = { 0 };
		printf("请输入更改的数据:");
		scanf("%s", buf);
		switch (num)
		{
		case 1:
			memset(&t.hnum, 0, sizeof(t.hnum));
			strcpy(t.hnum, buf);
			break;
		case 2:
			memset(&t.time, 0, sizeof(t.time));
			strcpy(t.time, buf);
			break;
		case 3:
			t.num = atoi(buf);
			break;
		case 4:
			memset(&t.phone, 0, sizeof(t.phone));
			strcpy(t.phone, buf);
			break;
		}
		printf("是否继续，继续写入相应序号即可，退出写0\n");
		scanf("%d", &num);
	}
	
}
void oldChangeInfo()
{
	Peolist* oldPeoHead = createPeoHeadList();
	readGuest(oldPeoHead, "guest.txt");
	Peolist* Move = oldPeoHead->next;
	char name[256] = { 0 };
	printf("输入你的姓名:");
	scanf("%s", &name);
	while (Move)
	{
		if (strcmp(Move->data.name, name) == 0)
		{
			printf("姓名\t电话\t\t有意向住房编号\t通话次数\t最近电话回访日期\n");
			printf("%s\t%s\t%s\t %d\t  %s\n", Move->data.name, Move->data.phone, Move->data.hnum, Move->data.num, Move->data.time);
			changeData(Move->data);
			printf("修改后的数据如下：\n");
			printf("%s\t%s\t%s\t %d\t  %s\n", Move->data.name, Move->data.phone, Move->data.hnum, Move->data.num, Move->data.time);
			break;
		}
		Move = Move->next;
	}
	saveGuest(oldPeoHead, "guest.txt","w");
	if (oldPeoHead)
	{
		free(oldPeoHead);
	}
}

// 在字符串中查找下划线的位置
char* _floor(char*str)
{
    char* underscorePos = strchr(str, '_');
	char* afterUnderscore = underscorePos + 1;
	printf("%s", afterUnderscore + 1);
	return afterUnderscore;
}

// 查询房源信息，并将符合条件的信息存储到新链表中
Prolist* queryAndStorePropertyInfo(Prolist* headNode, const char* direct, const char* floor, const char* sarea, int minPrice, int maxPrice) {
	int count = 0;  // 符合条件的房源数量

	// 创建用于存储结果的链表头结点
	Prolist* resultHead = createProHeadList();
	Prolist* resultCurrent = resultHead;

	Prolist* current = headNode->next;
	while (current != NULL) {
		// 检查每个房源是否符合条件
		if (strcmp(current->data.direct, direct) == 0 &&
			strcmp(_floor(current->data.floor), floor) == 0 &&
			strcmp(current->data.Sarea, sarea) == 0 &&
			current->data.price >= minPrice &&
			current->data.price <= maxPrice) {
			// 创建新节点存储符合条件的房源信息
			Prolist* newNode = createProNode(current->data);

			// 将新节点插入结果链表
			resultCurrent->next = newNode;
			resultCurrent = resultCurrent->next;

			// 输出符合条件的房源信息
			printf("房源编号：%d\n", current->data.id);
			printf("朝向：%s\n", current->data.direct);
			printf("楼层：%s\n", current->data.floor);
			printf("面积：%s\n", current->data.Sarea);
			printf("价格：%d\n", current->data.price);
			printf("------------------------\n");

			count++;
		}

		current = current->next;
	}

	// 输出符合条件的房源数量
	printf("符合条件的房源数量：%d\n", count);

	return resultHead;
}
void searchProInfo()
{
	Prolist* head = createProHeadList();
	readSource(head, "source.txt");
	char direct[20];
	char floor[12];
	char sarea[20];
	int minPrice, maxPrice;
	printf("请输入查询条件：\n");
	printf("朝向：");
	scanf("%s", direct);

	printf("楼层：");
	scanf("%s", floor);
	printf("面积：");
	scanf("%s", sarea);
	printf("最低价格：");
	scanf("%d", &minPrice);
	printf("最高价格：");
	scanf("%d", &maxPrice);
	// 执行查询并输出结果
	
	Prolist* resultHead = queryAndStorePropertyInfo(head, direct, floor, sarea, minPrice, maxPrice);
	Prolist* Move = resultHead;
	while (Move)
	{
		printf("%d\t%s\t%s\t%s\t%d\t%d\n", Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
	}
}

// 比较函数，用于按照 cnt 从大到小排序
int compareByCnt(const void* a, const void* b) {
	const Prolist* nodeA = *(const Prolist**)a;
	const Prolist* nodeB = *(const Prolist**)b;
	return nodeA->data.cnt - nodeB->data.cnt;
}

// 排序链表
void sortByCnt(Prolist* head) {
	// 统计链表长度
	size_t length = 0;
	Prolist* current = head->next;
	while (current != NULL) {
		length++;
		current = current->next;
	}

	// 分配数组用于存储链表节点指针
	Prolist** nodeArray = (Prolist**)malloc(length * sizeof(Prolist*));
	if (nodeArray == NULL) {
		// 处理内存分配失败的情况
		return;
	}

	// 将链表节点指针存储到数组中
	size_t index = 0;
	current = head->next;
	while (current != NULL) {
		nodeArray[index++] = current;
		current = current->next;
	}

	// 使用 qsort 对数组进行排序
	qsort(nodeArray, length, sizeof(Prolist*), compareByCnt);

	// 重新链接排序后的链表节点
	head->next = NULL;
	for (size_t i = 0; i < length; ++i) {
		nodeArray[i]->next = head->next;
		head->next = nodeArray[i];
	}

	// 释放数组内存
	free(nodeArray);
}

void sortPro()
{
	int ret = 0;
	Prolist* head = createProHeadList();
	readSource(head, "source.txt");
	// 调用排序函数
	sortByCnt(head);
	// 输出排序后的结果
	Prolist* Move = head->next;
	printf("热门前十房源信息\n");
	printf("编号\t朝向\t楼层(总层数_层位)\t面积\t\t价格  \t购买意向的人数\n");
	while (Move != NULL) {
		// 输出节点的数据
		printf("%d\t%s \t%s\t\t%s\t       %d\t   %d\n"
			, Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
		++ret;
		if (ret == 10)
		{
			break;
		}
	}
	// 释放链表内存
	Move = head;
	while (Move != NULL) {
		Prolist* next = Move->next;
		free(Move);
		Move = next;
	}
}
void deleteProById(int id)
{
	Prolist* head = createProHeadList();
	readSource(head, "source.txt");

	Prolist* current = head->next;
	Prolist* prev = head;

	while (current != NULL)
	{
		if (current->data.id == id)
		{
			// 找到待删除节点
			prev->next = current->next; // 跳过待删除节点
			free(current); // 释放待删除节点的内存
			break;
		}

		// 移动到下一个节点
		prev = current;
		current = current->next;
	}

	saveSource(head, "source.txt");
}

void soldData(slist* &Shead)
{
	printf("增加合同信息：住房编号 面积 价格 销售时间 合同号 房主姓名 电话号码\n");
	int num = 0;
	soldInfo newInfo;
	do
	{
		memset(&newInfo,0, sizeof(newInfo));
		scanf("%d%s%d%s%s%s%s", &newInfo.id, &newInfo.Sarea, &newInfo.price, &newInfo.time, &newInfo.Cno, &newInfo.hname, &newInfo.phone);
		printf("是否继续添加，是1否0\n");
		scanf("%d", &num);
	} while (num);
	insertSlist(Shead, newInfo);
	saveSold(Shead, "sold.txt");
	//还要改房源信息
	deleteProById(newInfo.id);
	printf("添加成功\n");
}
int main()
{
	setlocale(LC_ALL, "");  // 设置本地化信息为系统默认
	Peolist* PeoHead = createPeoHeadList();
	slist* Shead = createSHeadList();
	/*list* Headlist = createHeadList();
	readFile(Headlist, ".txt");*/
	while (1)
	{
		menu();
		int choice=keyDown();
		switch (choice)
		{
		case 0:
			printf("欢迎下次来访\n");
			exit(0);
		case 1:
			newPeoInfo(PeoHead);
			break;
		case 2:
			oldChangeInfo();
			break;
		case 3:
			searchProInfo();
			break;
		case 4:
			sortPro();
			break;
		case 5:
			soldData(Shead);
			break;
		}
		system("pause");
		system("cls");
	}


	return 0;
}