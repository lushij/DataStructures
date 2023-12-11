#include<iostream> 
#include<stdlib.h>
#include<fstream>
#include<time.h> //为下面的clock（）使用
#include<graphics.h>//Easyx库的头文件
#include<conio.h>//windows下的api头文件
#include<WinBase.h>//windows图形程序的头文件
#pragma comment(lib,"winmm.lib")//启动多线程库，为了音效和游戏同时进行
//翻转棋子函数实现
inline char T(char c)//内联函数，减少内存开销（c++中的内联函数比宏函数更安全，若是不会也可以用宏函数）
{
	return (c == 'B') ? 'W' : 'B';//三目操作符 如果c==B，返回的是W，否则返回的是B
}


using namespace std;
/***********************************注意事项********************************/
							//使用环境vs2022+Easyx图形库
							//切记把字节集改为多字节模式
							//还要改为window窗口形式
/**************************************************************************/
//const关键字定义常量
const int difficult = 6;	// 难度，为下面的动态搜索的范围作限制
//定义二维数组（8行2列）（8个方向）
const int moveFunc[8][2] = {
	{-1, 0},  // 向上移动  切记数组下标（x,y)x为行即纵向的，y为列即为横向的
	{1, 0},   // 向下移动
	{0, -1},  // 向左移动
	{0, 1},   // 向右移动
	{-1, -1}, // 左上移动
	{1, -1},  // 右上移动
	{1, 1},   // 右下移动
	{-1, 1}   // 左下移动
};

// 八个方向扩展
char map[8][8];				// 棋盘，定义全局变量默认初始化为0，
//                             好用省事，但对于工程来说，全局变量还是尽量少用
IMAGE img[5];				// 保存图片
int black, white;			// 记录双方的棋子数，全局变量默认为0，白棋为计算机，黑棋为用户
int X, Y;					// 白棋的下子点

/**********************************函数声明*****************************/
void load(void);				// 加载素材
void print(void);				// 画棋盘
void draw(int, int, char);		// 下当前子即（赋值数据以便于画棋盘）
int judge(int, int, char);		// 判断当前是否可以落下
bool baidu(char);				// 判断是否有棋可吃 
bool quit(char);				// 判断是否有棋存活，判断输赢
bool ask(void);					// 弹出对话框
int D(char, int);				// 动态规划算法
void play(void);				// 游戏过程
void reset();                   //每次开始前重置棋盘
void loadGame();				// 读盘函数
int startMenu();				// 开始界面(菜单界面）
/**********************************定义函数*****************************/
void load()		// 加载素材
{
	// 加载图片
	loadimage(&img[0], "图片\\空位.bmp");
	loadimage(&img[1], "图片\\黑子.bmp");
	loadimage(&img[2], "图片\\白子.bmp");
	loadimage(&img[3], "图片\\黑子1.bmp");
	loadimage(&img[4], "图片\\白子1.bmp");
	

	// 加载音乐
	mciSendString("open 音乐\\背景音乐.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\和局.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\胜利.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\失败.wma", NULL, 0, NULL);
	mciSendString("open 音乐\\下子.wma", NULL, 0, NULL);

	// 初始化棋盘
	initgraph(340, 340,1);//初始化画布，要配合closegraph()使用
	
	IMAGE qipan;//定义图片对象
	loadimage(&qipan, "图片\\棋盘.bmp");//打印棋盘总图片
	putimage(0, 0, &qipan);//打印棋盘
	setorigin(26, 26);//将坐标原点设置为（26,26），默认为（0，0）
	SetWindowText(GetHWnd(), "黑白棋");//设置窗口标题文本
}

void print(void)	// 画棋盘
{
	int x, y;
	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			switch (map[x][y])
			{
			case 0://棋盘默认为0
				putimage(37 * y, 37 * x, &img[0]);//坐标每一个方格（棋盘）的大小都是37*37的正方形
				break;
			case 'B'://游戏过程中根据后面的变化来做出相应变化
				putimage(37 * y, 37 * x, &img[1]);
				black++;//黑棋的数量加一
				break;
			case 'W':
				putimage(37 * y, 37 * x, &img[2]);
				white++;//白棋的数量加一
				break;
			}
}

void draw(int x, int y, char a)	// 下当前子并且同时判断是否进行翻转
{
	char b = T(a);									// 敌方子
	int i, x1, y1, x2, y2; 
	
	bool sign;
	for (i = 0; i < 8; i++)//棋盘边界
	{
		sign = false;
		x1 = x + moveFunc[i][0];//相邻位置
		y1 = y + moveFunc[i][1];
		//一定要先判断边界性问题，在判断数据问题
		while ( 0 <= x1 && x1 < 8 && 0 <= y1 && y1 < 8 && map[x1][y1] )//map[][]是否为真即相邻位置是否有棋子
		{
			if (map[x1][y1] == b)
				sign = true;
			else
			{
				if (sign)
				{
					x1 -= moveFunc[i][0]; //回退到对手棋子的位置。
					y1 -= moveFunc[i][1];
					x2 = x + moveFunc[i][0]; //标记当前玩家的棋子的位置。
					y2 = y + moveFunc[i][1];
					while (((x <= x2 && x2 <= x1) || (x1 <= x2 && x2 <= x)) && ((y <= y2 && y2 <= y1) || (y1 <= y2 && y2 <= y)))
					{
						//在当前玩家和对手棋子之间进行翻转。
						map[x2][y2] = a;//将对手的棋子翻转成当前玩家的棋子
						x2 += moveFunc[i][0];//继续前进
						y2 += moveFunc[i][1];
					}
				}
				break;
			}
			x1 += moveFunc[i][0];
			y1 += moveFunc[i][1];
		}
	}
	map[x][y] = a; //在最开始的(x, y) 位置放置当前玩家的棋子
}

int judge(int x, int y, char a)	// 判断当前是否可以落下，同draw函数
{
	if (map[x][y])						// 如果当前不是空就说明已经有棋子，返回0值
		return 0;
	char b = T(a);           //翻转棋，进行判断是否可以吃对方棋，并记录可以吃的数字
	int i, x1, y1;
	int n = 0, sign;
	for (i = 0; i < 8; i++)
	{
/*首先，检查当前位置(x, y) 是否已经有棋子，如果有则直接返回 0，表示不能在这个位置落子。
然后，定义变量 b 表示敌方棋子的颜色，通过调用 T 函数获取。T 函数的作用是将输入的颜色反转，
即如果是黑子，则返回白子，如果是白子，则返回黑子。
使用一个循环遍历 moveFunc 数组中的八个方向，对每个方向进行检测。
在每个方向上，从当前位置(x, y) 出发，沿着这个方向一直移动，
检查相邻的位置上是否有敌方棋子。如果有，累计计数（sign++）；
如果是自己方的棋子，则跳出循环。这个过程模拟了在当前方向上吃掉敌方棋子的过程。
将每个方向上吃掉的敌方棋子数量累加到变量 n 中。
最终返回 n，表示在当前位置可以吃掉的敌方棋子的总数量。*/

		sign = 0;//每次循环就是不同的方向，所以当前方向的可以吃的棋子数量继续从0开始
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
	return n;		// 返回可吃棋数
}

bool baidu(char c)	// 判断是否有棋可吃
{
	int x, y;
	for (x = 0; x < 8; x++)
		for (y = 0; y < 8; y++)
			if (judge(x, y, c))
				return true;
	return false;
}

bool quit(char c)	// 判断是否有棋存活，判断游戏是否结束
{
	int x, y;
	for (x = 0; x < 8; x++)
	{
		for (y = 0; y < 8; y++)
		{
			if (map[x][y] == c)
				return false;//表示还有这个类型的棋子，游戏不结束
		}
	}
	return true;
}

bool ask(void)	// 弹出对话框
{
	HWND wnd = GetHWnd();//句柄
	int key;
	if (black == white)
		//固定模板，会用就行，第一个参数是句柄，最后的就是默认参数（出现是和否选项）
		key = MessageBox(wnd,  "和局","GameOver" ,MB_YESNO);
	else if (black > white)
		key = MessageBox(wnd, "黑胜","GameOver", MB_YESNO);
	else
		key = MessageBox(wnd,  "白胜","GameOver", MB_YESNO);
	if (key == IDYES)//点击是的选项
		return true;
	else
		return false;
	
}

/*************************这部分我不会*******************************************/
//动态规划算法，好像也是个模板，但是我没有学到
int D(char c, int step)
{
	// 判断是否结束递归
	if (step > difficult)	// 约束步数之内
		return 0;
	if (!baidu(c))
	{
		if (baidu(T(c)))
			return -D(T(c), step);//递归
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// 建立临时数组
	char** t = new char* [8];
	for (i = 0; i < 8; i++)
		t[i] = new char[8];
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			t[i][j] = map[i][j];

	// 搜索解法
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

	// 释放空间
	for (i = 0; i < 8; i++)
		delete[] t[i];
	delete[] t;

	// 如果是第一步则标识白棋下子点
	if (step == 1)
	{
		X = x;
		Y = y;
	}

	return max;	// 返会最优解
}
/************************************************************************/

// 读盘函数
void loadGame() {
	ifstream file("save.txt");
	if (file.is_open()) {
		// 读取每一行
		for (int i = 0; i < 8; i++) {
			// 读取每个元素
			for (int j = 0; j < 8; j++) {
				char value;
				file >> value;
				cout << value << " ";//测试代码
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
		cout << "无法打开保存的游戏状态文件。" << endl;
	}
}


void play(void)			// 游戏过程
{
	MOUSEMSG m;//鼠标结构体
	int x, y;
	// 开始游戏
	print();
	//游戏开始播放音乐
	mciSendString("play 音乐\\背景音乐.wma from 0 repeat", NULL, 0, NULL);
	do
	{
		if (baidu('B'))										// 如果玩家有下子位置							
		{
		A:
			while (true)//一直陷入等待用户点击有效位置再刷新界面
			{
				m = GetMouseMsg();							// 获取鼠标消息
				//这个区域的边界是(26, 26) 到(26 + 37 * 8, 26 + 37 * 8)。
				if (m.uMsg == WM_LBUTTONDOWN && m.x - 26 < 37 * 8 && m.y - 26 < 37 * 8)
					// 如果左键点击
					break;
			}
			/*
			注意：这里面的坐标轴是+----------------->x(正）
								|
								|
								|
								|
								|
								y（正）
			*/   
			cout << m.x << "," << m.y << endl;
			x = (m.y - 26) / 37;//坐标转化为数组行下标（坐标轴纵向）
			y = (m.x - 26) / 37;//坐标转化为数组列坐标（坐标轴横向）
			if (judge(x, y, 'B'))							// 如果当前位置有效（数组下标）
			{
				draw(x, y, 'B');							// 下子（用户）
				mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
				print();
				putimage(37 * y, 37 * x, &img[3]);			// 标识下子点并展示
			}
			else//下棋的位置不合法就返回原函数继续重复等待
				goto A;
			if (quit('W'))									// 计算机是否失败
				break;
		}
		if (baidu('W'))										// 如果计算机有下子位置
		{
			clock_t start;
			start = clock();
			D('W', 1);										// 动态规划搜索解法
			while (clock() - start < CLOCKS_PER_SEC);
			draw(X, Y, 'W');
			print();
			mciSendString("play 音乐\\下子.wma from 0", NULL, 0, NULL);
			putimage(37 * Y, 37 * X, &img[4]);	// 标识下子点
			if (quit('B'))									// 玩家是否失败
				break;
		}

		// 检测是否按下 ESC 键
		if (_kbhit()) {//判断键盘是否就绪
			int key = _getch();
			if (key == 27) {  // 27 是 ESC 键的 ASCII 码
				// 弹出提示框询问用户是否保存游戏状态或退出
				int choice = MessageBox(GetHWnd(), _T("是否保存游戏状态？"), _T("提示"), MB_YESNOCANCEL);
				if (choice == IDYES) {
					ofstream saveFile("save.txt", ios::trunc);//自动覆盖源文件
					// 将当前棋盘状态保存到文件
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

					MessageBox(GetHWnd(), _T("游戏状态已保存。"), _T("提示"), MB_OK);
				}
				else if (choice == IDNO) {
					MessageBox(GetHWnd(), _T("游戏未保存，直接退出。"), _T("提示"), MB_OK);
					return;
				}
			}
		}
	} while (baidu('B') || baidu('W'));
	// 播放庆祝音乐
	mciSendString("stop 音乐\\背景音乐.wma", NULL, 0, NULL);
	if (black > white)
		mciSendString("play 音乐\\胜利.wma from 0", NULL, 0, NULL);
	else if (black < white)
		mciSendString("play 音乐\\失败.wma from 0", NULL, 0, NULL);
	else
		mciSendString("play 音乐\\和局.wma from 0", NULL, 0, NULL);
}

void reset()
{
	//因为每次结束后，若是用户点击是，则重新开始
	//并且是全局变量，所以不需要传参
	for (int x = 0; x < 8; x++)
		for (int y = 0; y < 8; y++)
			map[x][y] = 0;
	//游戏开始时现有默认棋子在棋盘上
	map[3][4] = map[4][3] = 'B';
	map[3][3] = map[4][4] = 'W';
}

// 开始界面
int startMenu() {
	// 初始化画布
	initgraph(400, 300, 1);
	setbkcolor(WHITE);//背景颜色
	cleardevice();//先清理背景
	// 绘制开始界面
	settextcolor(BLACK);//设置字体颜色
	settextstyle(24, 0, _T("黑体"));
	outtextxy(150, 50, _T("黑白棋游戏"));
	// 绘制选项
	settextstyle(16, 0, _T("宋体"));
	outtextxy(150, 120, _T("1. 开始新游戏"));
	outtextxy(150, 150, _T("2. 读盘"));
	outtextxy(150, 180, _T("3. 退出"));
	int choice = 0;
	int textW = textwidth(16);  // 假设字体大小为16
	int textH =textheight("开始新游戏");  // 获取当前字体的高度
	cout << textW << textH << endl;//字宽16，高度16
	while (true) {
		// 检测鼠标点击事件
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

// 主函数
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	do
	{
		//do while 函数是先运行再判断条件是否成立
		int menuChoice = startMenu();
		switch (menuChoice) {
		case 1:  // 开始新游戏
			load();
			reset();
			play();
			break;
		case 2:  // 读盘
			// 添加读盘相关的代码
			load();
			loadGame();
			/*测试代码
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
		case 3:  // 退出
			break;
		}
	
	} while (ask());

	// 关闭全部音乐
	//固定模板，会用就行，第一个参数可以改变，其他的都是默认参数
	mciSendString("close 音乐\\背景音乐.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\和局.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\胜利.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\失败.wma", NULL, 0, NULL);
	mciSendString("close 音乐\\下子.wma", NULL, 0, NULL);
	closegraph();
	return 0;
}

