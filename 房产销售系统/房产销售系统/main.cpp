#include"main.h"
typedef struct cntInfo
{
	int id;//ס�����
	int cnt;
}Cinfo;

typedef struct Cnt_s{
	Cinfo data;
	struct Cnt_s* next;
}Cnt_t;

//����Cnt_tͷ���
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
//�˵�
void menu()
{
	printf("��ӭ�����������۹���ϵͳ\n");
	printf("   1.�¿ͻ��Ǽ� \n");
	printf("   2.�Ͽͻ���Ϣ�޸�\n" );
	printf("   3.�ṩ��Դ��Ϣ��ѯ \n") ;
	printf("   4.���ŷ�Դ��Ϣ \n");
	printf("   5.�������ۺ�ͬ \n");
	printf("   0.�˳�ϵͳ\n") ;
}

//
//�û�����������װ
int keyDown()
{
	printf("��ѡ��:");
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
	printf("��������Ϣ:���� �绰 �й��������ס�����(���3������Ӣ�Ķ��Ÿ���)\n");
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
	updateProCnt(chead);//���·�Դ��Ϣ
	newPeo.num = 0;
	strcpy(newPeo.time, "null");
	insertPeolist(PeoHead, newPeo);
	saveGuest(PeoHead, "guest.txt","a+");
	printf("�Ǽǳɹ�\n");
}

void changeData(PeopleInfo &t)
{
	printf("��������Ҫ���ĵ����ݣ�1.�޸��й��������ס�����2.����޸Ļط�����3.�޸�ͨ������4.�޸Ŀͻ��绰0�˳�\n");
	int num = 0;
	scanf("%d", &num);
	while (num)
	{
		char buf[256] = { 0 };
		printf("��������ĵ�����:");
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
		printf("�Ƿ����������д����Ӧ��ż��ɣ��˳�д0\n");
		scanf("%d", &num);
	}
	
}
void oldChangeInfo()
{
	Peolist* oldPeoHead = createPeoHeadList();
	readGuest(oldPeoHead, "guest.txt");
	Peolist* Move = oldPeoHead->next;
	char name[256] = { 0 };
	printf("�����������:");
	scanf("%s", &name);
	while (Move)
	{
		if (strcmp(Move->data.name, name) == 0)
		{
			printf("����\t�绰\t\t������ס�����\tͨ������\t����绰�ط�����\n");
			printf("%s\t%s\t%s\t %d\t  %s\n", Move->data.name, Move->data.phone, Move->data.hnum, Move->data.num, Move->data.time);
			changeData(Move->data);
			printf("�޸ĺ���������£�\n");
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

// ���ַ����в����»��ߵ�λ��
char* _floor(char*str)
{
    char* underscorePos = strchr(str, '_');
	char* afterUnderscore = underscorePos + 1;
	printf("%s", afterUnderscore + 1);
	return afterUnderscore;
}

// ��ѯ��Դ��Ϣ������������������Ϣ�洢����������
Prolist* queryAndStorePropertyInfo(Prolist* headNode, const char* direct, const char* floor, const char* sarea, int minPrice, int maxPrice) {
	int count = 0;  // ���������ķ�Դ����

	// �������ڴ洢���������ͷ���
	Prolist* resultHead = createProHeadList();
	Prolist* resultCurrent = resultHead;

	Prolist* current = headNode->next;
	while (current != NULL) {
		// ���ÿ����Դ�Ƿ��������
		if (strcmp(current->data.direct, direct) == 0 &&
			strcmp(_floor(current->data.floor), floor) == 0 &&
			strcmp(current->data.Sarea, sarea) == 0 &&
			current->data.price >= minPrice &&
			current->data.price <= maxPrice) {
			// �����½ڵ�洢���������ķ�Դ��Ϣ
			Prolist* newNode = createProNode(current->data);

			// ���½ڵ����������
			resultCurrent->next = newNode;
			resultCurrent = resultCurrent->next;

			// ������������ķ�Դ��Ϣ
			printf("��Դ��ţ�%d\n", current->data.id);
			printf("����%s\n", current->data.direct);
			printf("¥�㣺%s\n", current->data.floor);
			printf("�����%s\n", current->data.Sarea);
			printf("�۸�%d\n", current->data.price);
			printf("------------------------\n");

			count++;
		}

		current = current->next;
	}

	// ������������ķ�Դ����
	printf("���������ķ�Դ������%d\n", count);

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
	printf("�������ѯ������\n");
	printf("����");
	scanf("%s", direct);

	printf("¥�㣺");
	scanf("%s", floor);
	printf("�����");
	scanf("%s", sarea);
	printf("��ͼ۸�");
	scanf("%d", &minPrice);
	printf("��߼۸�");
	scanf("%d", &maxPrice);
	// ִ�в�ѯ��������
	
	Prolist* resultHead = queryAndStorePropertyInfo(head, direct, floor, sarea, minPrice, maxPrice);
	Prolist* Move = resultHead;
	while (Move)
	{
		printf("%d\t%s\t%s\t%s\t%d\t%d\n", Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
	}
}

// �ȽϺ��������ڰ��� cnt �Ӵ�С����
int compareByCnt(const void* a, const void* b) {
	const Prolist* nodeA = *(const Prolist**)a;
	const Prolist* nodeB = *(const Prolist**)b;
	return nodeA->data.cnt - nodeB->data.cnt;
}

// ��������
void sortByCnt(Prolist* head) {
	// ͳ��������
	size_t length = 0;
	Prolist* current = head->next;
	while (current != NULL) {
		length++;
		current = current->next;
	}

	// �����������ڴ洢����ڵ�ָ��
	Prolist** nodeArray = (Prolist**)malloc(length * sizeof(Prolist*));
	if (nodeArray == NULL) {
		// �����ڴ����ʧ�ܵ����
		return;
	}

	// ������ڵ�ָ��洢��������
	size_t index = 0;
	current = head->next;
	while (current != NULL) {
		nodeArray[index++] = current;
		current = current->next;
	}

	// ʹ�� qsort �������������
	qsort(nodeArray, length, sizeof(Prolist*), compareByCnt);

	// ������������������ڵ�
	head->next = NULL;
	for (size_t i = 0; i < length; ++i) {
		nodeArray[i]->next = head->next;
		head->next = nodeArray[i];
	}

	// �ͷ������ڴ�
	free(nodeArray);
}

void sortPro()
{
	int ret = 0;
	Prolist* head = createProHeadList();
	readSource(head, "source.txt");
	// ����������
	sortByCnt(head);
	// ��������Ľ��
	Prolist* Move = head->next;
	printf("����ǰʮ��Դ��Ϣ\n");
	printf("���\t����\t¥��(�ܲ���_��λ)\t���\t\t�۸�  \t�������������\n");
	while (Move != NULL) {
		// ����ڵ������
		printf("%d\t%s \t%s\t\t%s\t       %d\t   %d\n"
			, Move->data.id, Move->data.direct, Move->data.floor, Move->data.Sarea, Move->data.price, Move->data.cnt);
		Move = Move->next;
		++ret;
		if (ret == 10)
		{
			break;
		}
	}
	// �ͷ������ڴ�
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
			// �ҵ���ɾ���ڵ�
			prev->next = current->next; // ������ɾ���ڵ�
			free(current); // �ͷŴ�ɾ���ڵ���ڴ�
			break;
		}

		// �ƶ�����һ���ڵ�
		prev = current;
		current = current->next;
	}

	saveSource(head, "source.txt");
}

void soldData(slist* &Shead)
{
	printf("���Ӻ�ͬ��Ϣ��ס����� ��� �۸� ����ʱ�� ��ͬ�� �������� �绰����\n");
	int num = 0;
	soldInfo newInfo;
	do
	{
		memset(&newInfo,0, sizeof(newInfo));
		scanf("%d%s%d%s%s%s%s", &newInfo.id, &newInfo.Sarea, &newInfo.price, &newInfo.time, &newInfo.Cno, &newInfo.hname, &newInfo.phone);
		printf("�Ƿ������ӣ���1��0\n");
		scanf("%d", &num);
	} while (num);
	insertSlist(Shead, newInfo);
	saveSold(Shead, "sold.txt");
	//��Ҫ�ķ�Դ��Ϣ
	deleteProById(newInfo.id);
	printf("��ӳɹ�\n");
}
int main()
{
	setlocale(LC_ALL, "");  // ���ñ��ػ���ϢΪϵͳĬ��
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
			printf("��ӭ�´�����\n");
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