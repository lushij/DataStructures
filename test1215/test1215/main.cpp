#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<WinBase.h>
#include<iostream>
#include<fstream>
using namespace std;
void fanzhuanqi(int x, int y, char c);
bool gameover(char c);
char fanzhuan(char c)//得到对手的棋子
{
	return c == 'B' ? 'W' : 'B';
}
int kechiqi(int x, int y, char c);
char qipan[9][9];
int move[9][2] = {
	{0,0},//没用，占个地方，使之后的循环可以从1开始
	{-1,0},//往上
	{1,0},//往下
	{0,1},//往右
	{0,-1},//往左
	{1,1},//往右下
	{1,-1},//往左下
	{-1,-1},//往左上
	{-1,1},//往右上
};
int difangx = 0;
int difangy = 0;//这是白子的落子点
int blacknum = 0;
int whitenum = 0;//记录双方的棋子数
int difficult = 6;
void fresh()//初始化棋盘
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			qipan[i][j] = '#';
		}
	}
	qipan[4][4] = qipan[5][5] = 'W';
	qipan[5][4] = qipan[4][5] = 'B';
}
void print()//打印棋盘
{
	initgraph(640, 640, 1);
	cleardevice();
	IMAGE img;
	loadimage(&img, "底片/木板.jpg");
	putimage(0, 0, &img);
	setlinecolor(BLACK);
	for (int i = 80; i <= 640; i += 80)
	{
		line(0, i, 640, i);
		line(i, 0, i, 640);
	}

	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (qipan[i][j] == 'W')
			{
				whitenum++;
				setfillcolor(WHITE);
				fillcircle(i * 80 - 40, j * 80 - 40, 35);
			}
			if (qipan[i][j] == 'B')
			{
				blacknum++;
				setfillcolor(BLACK);
				fillcircle(i * 80 - 40, j * 80 - 40, 35);
			}
		}
	}

}
void start()//开始界面，可选择开始，读盘或退出
{
	setbkcolor(WHITE);
    cleardevice();
	SetWindowText(GetHWnd(), _T("黑白棋"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, _T("黑体"));
	outtextxy(200, 150, _T("黑白棋人机对战"));
	settextstyle(25, 0, _T("黑体"));
	outtextxy(250, 300, _T("1.开始新游戏"));
	outtextxy(250, 400, _T("2.读盘"));
	outtextxy(250, 500, _T("3.退出"));

}
int click()
{
	int choice = 0;
	ExMessage m;
	//MOUSEMSG m;
	while (1)
	{
		while (MouseHit())
		{
			m = getmessage(EX_MOUSE);
			//m = GetMouseMsg();
			if (m.message == WM_LBUTTONDOWN && m.x >= 250 && m.x <= 400 && m.y >= 300 && m.y <= 400)
			{
				choice = 1;
				/*break;*/
			}
			if (m.message == WM_LBUTTONDOWN && m.x >= 250 && m.x <= 400 && m.y >= 400 && m.y <= 500)
			{
				choice = 2;
				/*break;*/
			}
			if (m.message == WM_LBUTTONDOWN && m.x >= 250 && m.x <= 400 && m.y >= 500 && m.y <= 600)
			{
				choice = 3;
				/*break;*/
			}
			/*if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 250 && m.x <= 400 && m.y >= 300 && m.y <= 400) {
					choice = 1;
				}
				else if (m.x >= 250 && m.x <= 400 && m.y >= 400 && m.y <= 500) {
					choice = 2;
				}
				else if (m.x >= 250 && m.x <= 400 && m.y >= 500 && m.y <= 600) {
					choice = 3;
				}
			}*/
		}
		if (choice != 0)
		{
			return choice;
		}
		
	}
	
}
void cunchu()//把未完成的游戏存入文件
{
	ofstream save("save.txt", ios::trunc);
	if (save.is_open())
	{
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				save << qipan[i][j];
			}
			save << endl;
		}
		save.close();
	}
	else
	{
		cout << "存档失败" << endl;
	}
}
void dupan()//继续玩上一次未完成的游戏
{
	ifstream save("save.txt");
	if (save.is_open())
	{
		for (int i = 1; i <= 8; i++)
		{
			for (int j = 1; j <= 8; j++)
			{
				save >> qipan[i][j];
			}
		}
		save.close();
	}
	else
	{
		cout << "读档失败，请重新开始" << endl;
	}
}
int bestoption(char c, int step)//动态规划找到最优解
{
	// 判断是否结束递归
	if (step > difficult)	// 约束步数之内
		return 0;
	if (!gameover(c))
	{
		if (gameover(fanzhuan(c)))
			return -bestoption(fanzhuan(c), step);//递归
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// 建立临时数组
	char** t = new char* [9];
	for (i = 0; i < 8; i++)
		t[i] = new char[9];
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
			t[i][j] = qipan[i][j];

	// 搜索解法
	for (i = 0; i < 8; i++)
		for (j = 0; j < 8; j++)
			if (temp = kechiqi(i, j, c))
			{
				fanzhuanqi(i, j, c);
				temp -= bestoption(fanzhuan(c), step + 1);
				if (temp > max || !ans)
				{
					max = temp;
					x = i;
					y = j;
					ans = true;
				}
				for (int k = 1; k <= 8; k++)
					for (int l = 1; l <= 8; l++)
						qipan[k][l] = t[k][l];
			}

	// 释放空间
	for (i = 0; i <= 8; i++)
		delete[] t[i];
	delete[] t;

	// 如果是第一步则标识白棋下子点
	if (step == 1)
	{
		difangx = x;
		difangy = y;
	}

	return max;	// 返回最优解
}
/************************************************************************/

int kechiqi(int x, int y, char c)//x,y为棋子坐标，如果该地方没有棋子且有对方的棋子可吃，则返回可吃棋数
{
	int move[9][2] = {
	{0,0},//没用，占个地方，使之后的循环可以从1开始
	{-1,0},//往上
	{1,0},//往下
	{0,1},//往右
	{0,-1},//往左
	{1,1},//往右下
	{1,-1},//往左下
	{-1,-1},//往左上
	{-1,1},//往右上
	};
	int sum = 0;
	if (qipan[x][y] != '#')
	{
		return 0;//该地已有棋子，返回0表示不能放在这里
	}
	else
	{
		char duishou = fanzhuan(c);//得到对手的棋子
		for (int i = 1; i <= 8; i++)
		{
			int temp = 0;
			int newx = x + move[i][0];
			int newy = y + move[i][1];
			while (newx >= 1 && newx <= 8 && newy >= 1 && newy <= 8 && qipan[newx][newy] != '#')//如果这个方向的棋子还在棋盘中且有棋子，则继续移动
			{
				if (qipan[newx][newy] == duishou)
				{

					temp++;
				}
				else
				{
					break;
				}
				newx += move[i][0];
				newy += move[i][0];//继续往这个方向延伸
			}
			sum += temp;
		}
	}
	return sum;
}
bool fangqi(int x, int y, char c)//如果这个地方可放棋，就把棋子落下
{
	if (kechiqi(x, y, c) != 0)
	{
		qipan[x][y] = c;
		return true;
	}
	else
	{
		return false;
	}
}
void fanzhuanqi(int x, int y, char c)//如果可放棋，则翻转对手的棋子
{
	int move[9][2] = {
	{0,0},//没用，占个地方，使之后的循环可以从1开始
	{-1,0},//往上
	{1,0},//往下
	{0,1},//往右
	{0,-1},//往左
	{1,1},//往右下
	{1,-1},//往左下
	{-1,-1},//往左上
	{-1,1},//往右上
	};
	char duishou = fanzhuan(c);
	bool flag = false;
	if (fangqi(x, y, c))
	{
		for (int i = 1; i <= 8; i++)
		{
			int newx = x + move[i][0];
			int newy = y + move[i][1];
			while (newx >= 1 && newx <= 8 && newy >= 1 && newy <= 8 && qipan[newx][newy] != '#')//如果该方向有棋，则继续往这边走
			{
				if (qipan[newx][newy] == c)//做个标志表示遇到了敌方棋子，可继续延伸
				{
					flag = true;
				}
				else//如果遇到的是己方棋子，且己方棋子间有敌方棋子
				{
					if (flag == true)
					{
						int x1 = newx - move[i][0];
						int y1 = newy - move[i][1];
						int x2 = x + move[i][0];
						int y2 = y + move[i][1];
						while (((x2 >= x && x2 <= x1) || (x2 >= x1 && x2 <= x)) && ((y2 >= y && y2 <= y1) || (y2 >= y1 && y2 <= y)))
						{
							qipan[x2][y2] = c;
							x2 += move[i][0];
							y2 += move[i][1];
						}
					}
					break;//退出当前循环
				}
				newx += move[i][0];
				newy += move[i][1];
			}

			flag = false;
		}
	}
}
bool gameover(char c)//判断是否结束，此处是没地放棋
{
	int temp = 0;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			temp += kechiqi(i, j, c);

		}
	}
	if (temp == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool fullfill()//此处是棋盘已满
{
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if (qipan[i][j] == '#')
			{
				return false;
			}
		}
	}
	return true;
}
void playgame()//开始玩游戏
{
	ExMessage m;
	print();
	int x = 0;
	int y = 0;//获取鼠标点击坐标
	while (!fullfill())//如果棋盘还没满
	{
		if (!gameover('B'))
		{
		dianji:
			while (true)
			{
				m = getmessage();
				if (m.message == WM_LBUTTONDOWN && m.x >= 0 && m.x <= 640 && m.y >= 0 && m.y <= 640)
				{
					break;
				}
				x = m.x / 80 + 1;
				y = m.y / 80 + 1;
				if (fangqi(x, y, 'B'))
				{
					fanzhuanqi(x, y, 'B');
					print();
				}
				else
				{
					goto dianji;
				}

			}
			if (gameover('W') || fullfill())
			{
				break;
			}
		}
		if (!gameover('W'))
		{
			bestoption('W', 1);
			Sleep(1000);//让程序暂停一秒
			fanzhuanqi(difangx, difangy, 'W');
			print();
			if (gameover('B') || fullfill())
			{
				break;
			}
		}
		if (_kbhit())
		{
			int temp = _getch();
			if (temp == 27)//27是Ecs的码
			{
				int flag = MessageBox(GetHWnd(), _T("是否保存当前进度"), _T("提示"), MB_YESNO);
				if (flag == IDYES)
				{
					cunchu();
					MessageBox(GetHWnd(), _T("保存成功"), _T("提示"), MB_OK);
				}
				else
				{
					MessageBox(GetHWnd(), _T("未存档"), _T("提示"), MB_OK);
					return;
				}
			}
		}
	}
}
bool rechoose()
{
	int temp = 0;
	if (blacknum > whitenum)
	{
		temp = MessageBox(GetHWnd(), _T("恭喜您获胜"), _T("提示"), MB_OKCANCEL);
	}
	else if (blacknum < whitenum)
	{
		temp = MessageBox(GetHWnd(), _T("非常可惜，要不要再来一局？"), _T("提示"), MB_OKCANCEL);
	}
	/*else
	{
		temp = MessageBox(GetHWnd(), _T("平局"), _T("提示"), MB_OKCANCEL);
	}*/
	if (temp == IDYES)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int NCmdShow)
{
	initgraph(640, 640,1);

	do
	{
		start();
		/*while (1);*/
		int choice=click();
		cout << choice;
	/*	while (1);*/
		//choice = 1;
		if (choice == 1)
		{
			fresh();
			print();
			playgame();
		}
		else if (choice == 2)
		{
			dupan();
			print();
			playgame();
		}
		else if (choice == 3)
		{
			return 0;
		}
	} while (rechoose());
	closegraph();
	return 0;
}