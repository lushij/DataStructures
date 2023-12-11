#include<iostream> 
#include<stdlib.h>
#include<fstream>
#include<time.h> //Ϊ�����clock����ʹ��
#include<graphics.h>//Easyx���ͷ�ļ�
#include<conio.h>//windows�µ�apiͷ�ļ�
#include<WinBase.h>//windowsͼ�γ����ͷ�ļ�
#pragma comment(lib,"winmm.lib")//�������߳̿⣬Ϊ����Ч����Ϸͬʱ����
//��ת���Ӻ���ʵ��
inline char T(char c)//���������������ڴ濪����c++�е����������Ⱥ꺯������ȫ�����ǲ���Ҳ�����ú꺯����
{
	return (c == 'B') ? 'W' : 'B';//��Ŀ������ ���c==B�����ص���W�����򷵻ص���B
}


using namespace std;
/***********************************ע������********************************/
							//ʹ�û���vs2022+Easyxͼ�ο�
							//�мǰ��ֽڼ���Ϊ���ֽ�ģʽ
							//��Ҫ��Ϊwindow������ʽ
/**************************************************************************/
//const�ؼ��ֶ��峣��
const int difficult = 6;	// �Ѷȣ�Ϊ����Ķ�̬�����ķ�Χ������
//�����ά���飨8��2�У���8������
const int moveFunc[8][2] = {
	{-1, 0},  // �����ƶ�  �м������±꣨x,y)xΪ�м�����ģ�yΪ�м�Ϊ�����
	{1, 0},   // �����ƶ�
	{0, -1},  // �����ƶ�
	{0, 1},   // �����ƶ�
	{-1, -1}, // �����ƶ�
	{1, -1},  // �����ƶ�
	{1, 1},   // �����ƶ�
	{-1, 1}   // �����ƶ�
};

// �˸�������չ
char map[8][8];				// ���̣�����ȫ�ֱ���Ĭ�ϳ�ʼ��Ϊ0��
//                             ����ʡ�£������ڹ�����˵��ȫ�ֱ������Ǿ�������
IMAGE img[5];				// ����ͼƬ
int black, white;			// ��¼˫������������ȫ�ֱ���Ĭ��Ϊ0������Ϊ�����������Ϊ�û�
int X, Y;					// ��������ӵ�

/**********************************��������*****************************/
void load(void);				// �����ز�
void print(void);				// ������
void draw(int, int, char);		// �µ�ǰ�Ӽ�����ֵ�����Ա��ڻ����̣�
int judge(int, int, char);		// �жϵ�ǰ�Ƿ��������
bool baidu(char);				// �ж��Ƿ�����ɳ� 
bool quit(char);				// �ж��Ƿ�������ж���Ӯ
bool ask(void);					// �����Ի���
int D(char, int);				// ��̬�滮�㷨
void play(void);				// ��Ϸ����
void reset();                   //ÿ�ο�ʼǰ��������
void loadGame();				// ���̺���
int startMenu();				// ��ʼ����(�˵����棩
/**********************************���庯��*****************************/
void load()		// �����ز�
{
	// ����ͼƬ
	loadimage(&img[0], "ͼƬ\\��λ.bmp");
	loadimage(&img[1], "ͼƬ\\����.bmp");
	loadimage(&img[2], "ͼƬ\\����.bmp");
	loadimage(&img[3], "ͼƬ\\����1.bmp");
	loadimage(&img[4], "ͼƬ\\����1.bmp");
	

	// ��������
	mciSendString("open ����\\��������.wma", NULL, 0, NULL);
	mciSendString("open ����\\�;�.wma", NULL, 0, NULL);
	mciSendString("open ����\\ʤ��.wma", NULL, 0, NULL);
	mciSendString("open ����\\ʧ��.wma", NULL, 0, NULL);
	mciSendString("open ����\\����.wma", NULL, 0, NULL);

	// ��ʼ������
	initgraph(340, 340,1);//��ʼ��������Ҫ���closegraph()ʹ��
	
	IMAGE qipan;//����ͼƬ����
	loadimage(&qipan, "ͼƬ\\����.bmp");//��ӡ������ͼƬ
	putimage(0, 0, &qipan);//��ӡ����
	setorigin(26, 26);//������ԭ������Ϊ��26,26����Ĭ��Ϊ��0��0��
	SetWindowText(GetHWnd(), "�ڰ���");//���ô��ڱ����ı�
}

void print(void)	// ������
{
	int x, y;
	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			switch (map[x][y])
			{
			case 0://����Ĭ��Ϊ0
				putimage(37 * y, 37 * x, &img[0]);//����ÿһ���������̣��Ĵ�С����37*37��������
				break;
			case 'B'://��Ϸ�����и��ݺ���ı仯��������Ӧ�仯
				putimage(37 * y, 37 * x, &img[1]);
				black++;//�����������һ
				break;
			case 'W':
				putimage(37 * y, 37 * x, &img[2]);
				white++;//�����������һ
				break;
			}
}

void draw(int x, int y, char a)	// �µ�ǰ�Ӳ���ͬʱ�ж��Ƿ���з�ת
{
	char b = T(a);									// �з���
	int i, x1, y1, x2, y2; 
	
	bool sign;
	for (i = 0; i < 8; i++)//���̱߽�
	{
		sign = false;
		x1 = x + moveFunc[i][0];//����λ��
		y1 = y + moveFunc[i][1];
		//һ��Ҫ���жϱ߽������⣬���ж���������
		while ( 0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1] )//map[][]�Ƿ�Ϊ�漴����λ���Ƿ�������
		{
			if (map[x1][y1] == b)
				sign = true;
			else
			{
				if (sign)
				{
					x1 -= moveFunc[i][0]; //���˵��������ӵ�λ�á�
					y1 -= moveFunc[i][1];
					x2 = x + moveFunc[i][0]; //��ǵ�ǰ��ҵ����ӵ�λ�á�
					y2 = y + moveFunc[i][1];
					while (((x <= x2 && x2 <= x1) || (x1 <= x2 && x2 <= x)) && ((y <= y2 && y2 <= y1) || (y1 <= y2 && y2 <= y)))
					{
						//�ڵ�ǰ��ҺͶ�������֮����з�ת��
						map[x2][y2] = a;//�����ֵ����ӷ�ת�ɵ�ǰ��ҵ�����
						x2 += moveFunc[i][0];//����ǰ��
						y2 += moveFunc[i][1];
					}
				}
				break;
			}
			x1 += moveFunc[i][0];
			y1 += moveFunc[i][1];
		}
	}
	map[x][y] = a; //���ʼ��(x, y) λ�÷��õ�ǰ��ҵ�����
}

int judge(int x, int y, char a)	// �жϵ�ǰ�Ƿ�������£�ͬdraw����
{
	if (map[x][y])						// �����ǰ���ǿվ�˵���Ѿ������ӣ�����0ֵ
		return 0;
	char b = T(a);           //��ת�壬�����ж��Ƿ���ԳԶԷ��壬����¼���ԳԵ�����
	int i, x1, y1;
	int n = 0, sign;
	for (i = 0; i < 8; i++)
	{
/*���ȣ���鵱ǰλ��(x, y) �Ƿ��Ѿ������ӣ��������ֱ�ӷ��� 0����ʾ���������λ�����ӡ�
Ȼ�󣬶������ b ��ʾ�з����ӵ���ɫ��ͨ������ T ������ȡ��T �����������ǽ��������ɫ��ת��
������Ǻ��ӣ��򷵻ذ��ӣ�����ǰ��ӣ��򷵻غ��ӡ�
ʹ��һ��ѭ������ moveFunc �����еİ˸����򣬶�ÿ��������м�⡣
��ÿ�������ϣ��ӵ�ǰλ��(x, y) �����������������һֱ�ƶ���
������ڵ�λ�����Ƿ��ез����ӡ�����У��ۼƼ�����sign++����
������Լ��������ӣ�������ѭ�����������ģ�����ڵ�ǰ�����ϳԵ��з����ӵĹ��̡�
��ÿ�������ϳԵ��ĵз����������ۼӵ����� n �С�
���շ��� n����ʾ�ڵ�ǰλ�ÿ��ԳԵ��ĵз����ӵ���������*/

		sign = 0;//ÿ��ѭ�����ǲ�ͬ�ķ������Ե�ǰ����Ŀ��ԳԵ���������������0��ʼ
		x1 = x + moveFunc[i][0];
		y1 = y + moveFunc[i][1];
		while (0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1])
		{
			if (map[x1][y1] == b)
				sign++;
			else
			{
				n += sign;
				break;
			}
			x1 += moveFunc[i][0];
			y1 += moveFunc[i][1];
		}
	}
	return n;		// ���ؿɳ�����
}

bool baidu(char c)	// �ж��Ƿ�����ɳ�
{
	int x, y;
	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			if (judge(x, y, c))
				return true;
	return false;
}

bool quit(char c)	// �ж��Ƿ�������ж���Ϸ�Ƿ����
{
	int x, y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (map[x][y] == c)
				return false;//��ʾ����������͵����ӣ���Ϸ������
		}
	}
	return true;
}

bool ask(void)	// �����Ի���
{
	HWND wnd = GetHWnd();//���
	int key;
	if (black == white)
		//�̶�ģ�壬���þ��У���һ�������Ǿ�������ľ���Ĭ�ϲ����������Ǻͷ�ѡ�
		key = MessageBox(wnd,  "�;�","GameOver" ,MB_YESNO);
	else if (black > white)
		key = MessageBox(wnd, "��ʤ","GameOver", MB_YESNO);
	else
		key = MessageBox(wnd,  "��ʤ","GameOver", MB_YESNO);
	if (key == IDYES)//����ǵ�ѡ��
		return true;
	else
		return false;
	
}

/*************************�ⲿ���Ҳ���*******************************************/
//��̬�滮�㷨������Ҳ�Ǹ�ģ�壬������û��ѧ��
int D(char c, int step)
{
	// �ж��Ƿ�����ݹ�
	if (step > difficult)	// Լ������֮��
		return 0;
	if (!baidu(c))
	{
		if (baidu(T(c)))
			return -D(T(c), step);//�ݹ�
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// ������ʱ����
	char** t = new char* [8];
	for (i = 0; i < 8; i++)
		t[i] = new char[8];
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			t[i][j] = map[i][j];

	// �����ⷨ
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (temp = judge(i, j, c))
			{
				draw(i, j, c);
				temp -= D(T(c), step + 1);
				if (temp > max || !ans)
				{
					max = temp;
					x = i;
					y = j;
					ans = true;
				}
				for (int k = 0; k < 8; k++)
					for (int l = 0; l < 8; l++)
						map[k][l] = t[k][l];
			}

	// �ͷſռ�
	for (i = 0; i < 8; i++)
		delete[] t[i];
	delete[] t;

	// ����ǵ�һ�����ʶ�������ӵ�
	if (step == 1)
	{
		X = x;
		Y = y;
	}

	return max;	// �������Ž�
}
/************************************************************************/

// ���̺���
void loadGame() {
	ifstream file("save.txt");
	if (file.is_open()) {
		// ��ȡÿһ��
		for (int i = 0; i < 8; i++) {
			// ��ȡÿ��Ԫ��
			for (int j = 0; j < 8; j++) {
				char value;
				file >> value;
				cout << value << " ";//���Դ���
				if (value == '*') {
					map[i][j] = 0;
				}
				else {
					map[i][j] = value;
				}
			}
			cout << endl;
		}
		file.close();
	}
	else {
		cout << "�޷��򿪱������Ϸ״̬�ļ���" << endl;
	}
}


void play(void)			// ��Ϸ����
{
	MOUSEMSG m;//���ṹ��
	int x, y;
	// ��ʼ��Ϸ
	print();
	//��Ϸ��ʼ��������
	mciSendString("play ����\\��������.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// ������������λ��							
		{
		A:
			while (true)//һֱ����ȴ��û������Чλ����ˢ�½���
			{
				m = GetMouseMsg();							// ��ȡ�����Ϣ
				//�������ı߽���(26, 26) ��(26 + 37 * 8, 26 + 37 * 8)��
				if (m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
					// ���������
					break;
			}
			/*
			ע�⣺���������������+----------------->x(����
								|
								|
								|
								|
								|
								y������
			*/   
			cout << m.x << "," << m.y << endl;
			x = (m.y - 26) / 37;//����ת��Ϊ�������±꣨����������
			y = (m.x - 26) / 37;//����ת��Ϊ���������꣨���������
			if (judge(x, y, 'B'))							// �����ǰλ����Ч�������±꣩
			{
				draw(x, y, 'B');							// ���ӣ��û���
				mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// ��ʶ���ӵ㲢չʾ
			}
			else//�����λ�ò��Ϸ��ͷ���ԭ���������ظ��ȴ�
				goto A;
			if (quit('W'))									// ������Ƿ�ʧ��
				break;
		}
		if (baidu('W'))										// ��������������λ��
		{
			clock_t start;
			start = clock();
			D('W', 1);										// ��̬�滮�����ⷨ
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play ����\\����.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// ��ʶ���ӵ�
			if (quit('B'))									// ����Ƿ�ʧ��
				break;
		}

		// ����Ƿ��� ESC ��
		if (_kbhit()) {//�жϼ����Ƿ����
			int key = _getch();
			if (key == 27) {  // 27 �� ESC ���� ASCII ��
				// ������ʾ��ѯ���û��Ƿ񱣴���Ϸ״̬���˳�
				int choice = MessageBox(GetHWnd(), _T("�Ƿ񱣴���Ϸ״̬��"), _T("��ʾ"), MB_YESNOCANCEL);
				if (choice == IDYES) {
					ofstream saveFile("save.txt", ios::trunc);//�Զ�����Դ�ļ�
					// ����ǰ����״̬���浽�ļ�
					for (int i = 0; i < 8; i++) {
						for (int j = 0; j < 8; j++) {
							if (map[i][j] != 0)
								saveFile << map[i][j];
							else
								saveFile << "*";
						}
						saveFile << endl;
					}
					saveFile.close();

					MessageBox(GetHWnd(), _T("��Ϸ״̬�ѱ��档"), _T("��ʾ"), MB_OK);
				}
				else if (choice == IDNO) {
					MessageBox(GetHWnd(), _T("��Ϸδ���棬ֱ���˳���"), _T("��ʾ"), MB_OK);
					return;
				}
			}
		}
	} while (baidu('B') || baidu('W'));
	// ������ף����
	mciSendString("stop ����\\��������.wma", NULL, 0, NULL);
	if (black > white)
		mciSendString("play ����\\ʤ��.wma from 0", NULL, 0, NULL);
	else if (black < white)
		mciSendString("play ����\\ʧ��.wma from 0", NULL, 0, NULL);
	else
		mciSendString("play ����\\�;�.wma from 0", NULL, 0, NULL);
}

void reset()
{
	//��Ϊÿ�ν����������û�����ǣ������¿�ʼ
	//������ȫ�ֱ��������Բ���Ҫ����
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			map[x][y] = 0;
	//��Ϸ��ʼʱ����Ĭ��������������
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';
}

// ��ʼ����
int startMenu() {
	// ��ʼ������
	initgraph(400, 300, 1);
	setbkcolor(WHITE);//������ɫ
	cleardevice();//��������
	// ���ƿ�ʼ����
	settextcolor(BLACK);//����������ɫ
	settextstyle(24, 0, _T("����"));
	outtextxy(150, 50, _T("�ڰ�����Ϸ"));
	// ����ѡ��
	settextstyle(16, 0, _T("����"));
	outtextxy(150, 120, _T("1. ��ʼ����Ϸ"));
	outtextxy(150, 150, _T("2. ����"));
	outtextxy(150, 180, _T("3. �˳�"));
	int choice = 0;
	int textW = textwidth(16);  // ���������СΪ16
	int textH =textheight("��ʼ����Ϸ");  // ��ȡ��ǰ����ĸ߶�
	cout << textW << textH << endl;//�ֿ�16���߶�16
	while (true) {
		// ���������¼�
		MOUSEMSG m;
		while (MouseHit()) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 150 && m.x <= 250 && m.y >= 120 && m.y <= 135) {
					choice = 1;
				}
				else if (m.x >= 150 && m.x <= 250 && m.y >= 150 && m.y <= 165) {
					choice = 2;
				}
				else if (m.x >= 150 && m.x <= 250 && m.y >= 180 && m.y <= 195) {
					choice = 3;
				}
			}
		}
		if (choice != 0) {
			return choice;
		}
	}
}

// ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	do
	{
		//do while ���������������ж������Ƿ����
		int menuChoice = startMenu();
		switch (menuChoice) {
		case 1:  // ��ʼ����Ϸ
			load();
			reset();
			play();
			break;
		case 2:  // ����
			// ��Ӷ�����صĴ���
			load();
			loadGame();
			/*���Դ���
			* for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					cout << map[i][j] << " ";
				}
				cout << endl;
			}
			*/
			play();
			break;
		case 3:  // �˳�
			break;
		}
	
	} while (ask());

	// �ر�ȫ������
	//�̶�ģ�壬���þ��У���һ���������Ըı䣬�����Ķ���Ĭ�ϲ���
	mciSendString("close ����\\��������.wma", NULL, 0, NULL);
	mciSendString("close ����\\�;�.wma", NULL, 0, NULL);
	mciSendString("close ����\\ʤ��.wma", NULL, 0, NULL);
	mciSendString("close ����\\ʧ��.wma", NULL, 0, NULL);
	mciSendString("close ����\\����.wma", NULL, 0, NULL);
	closegraph();
	return 0;
}

