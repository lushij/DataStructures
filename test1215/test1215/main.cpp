#include<graphics.h>
#include<conio.h>
#include<windows.h>
#include<WinBase.h>
#include<iostream>
#include<fstream>
using namespace std;
void fanzhuanqi(int x, int y, char c);
bool gameover(char c);
char fanzhuan(char c)//�õ����ֵ�����
{
	return c == 'B' ? 'W' : 'B';
}
int kechiqi(int x, int y, char c);
char qipan[9][9];
int move[9][2] = {
	{0,0},//û�ã�ռ���ط���ʹ֮���ѭ�����Դ�1��ʼ
	{-1,0},//����
	{1,0},//����
	{0,1},//����
	{0,-1},//����
	{1,1},//������
	{1,-1},//������
	{-1,-1},//������
	{-1,1},//������
};
int difangx = 0;
int difangy = 0;//���ǰ��ӵ����ӵ�
int blacknum = 0;
int whitenum = 0;//��¼˫����������
int difficult = 6;
void fresh()//��ʼ������
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
void print()//��ӡ����
{
	initgraph(640, 640, 1);
	cleardevice();
	IMAGE img;
	loadimage(&img, "��Ƭ/ľ��.jpg");
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
void start()//��ʼ���棬��ѡ��ʼ�����̻��˳�
{
	setbkcolor(WHITE);
    cleardevice();
	SetWindowText(GetHWnd(), _T("�ڰ���"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(40, 0, _T("����"));
	outtextxy(200, 150, _T("�ڰ����˻���ս"));
	settextstyle(25, 0, _T("����"));
	outtextxy(250, 300, _T("1.��ʼ����Ϸ"));
	outtextxy(250, 400, _T("2.����"));
	outtextxy(250, 500, _T("3.�˳�"));

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
void cunchu()//��δ��ɵ���Ϸ�����ļ�
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
		cout << "�浵ʧ��" << endl;
	}
}
void dupan()//��������һ��δ��ɵ���Ϸ
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
		cout << "����ʧ�ܣ������¿�ʼ" << endl;
	}
}
int bestoption(char c, int step)//��̬�滮�ҵ����Ž�
{
	// �ж��Ƿ�����ݹ�
	if (step > difficult)	// Լ������֮��
		return 0;
	if (!gameover(c))
	{
		if (gameover(fanzhuan(c)))
			return -bestoption(fanzhuan(c), step);//�ݹ�
		else
			return 0;
	}

	int i, j, max = 0, temp, x, y;
	bool ans = false;

	// ������ʱ����
	char** t = new char* [9];
	for (i = 0; i < 8; i++)
		t[i] = new char[9];
	for (i = 1; i <= 8; i++)
		for (j = 1; j <= 8; j++)
			t[i][j] = qipan[i][j];

	// �����ⷨ
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

	// �ͷſռ�
	for (i = 0; i <= 8; i++)
		delete[] t[i];
	delete[] t;

	// ����ǵ�һ�����ʶ�������ӵ�
	if (step == 1)
	{
		difangx = x;
		difangy = y;
	}

	return max;	// �������Ž�
}
/************************************************************************/

int kechiqi(int x, int y, char c)//x,yΪ�������꣬����õط�û���������жԷ������ӿɳԣ��򷵻ؿɳ�����
{
	int move[9][2] = {
	{0,0},//û�ã�ռ���ط���ʹ֮���ѭ�����Դ�1��ʼ
	{-1,0},//����
	{1,0},//����
	{0,1},//����
	{0,-1},//����
	{1,1},//������
	{1,-1},//������
	{-1,-1},//������
	{-1,1},//������
	};
	int sum = 0;
	if (qipan[x][y] != '#')
	{
		return 0;//�õ��������ӣ�����0��ʾ���ܷ�������
	}
	else
	{
		char duishou = fanzhuan(c);//�õ����ֵ�����
		for (int i = 1; i <= 8; i++)
		{
			int temp = 0;
			int newx = x + move[i][0];
			int newy = y + move[i][1];
			while (newx >= 1 && newx <= 8 && newy >= 1 && newy <= 8 && qipan[newx][newy] != '#')//��������������ӻ����������������ӣ�������ƶ�
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
				newy += move[i][0];//�����������������
			}
			sum += temp;
		}
	}
	return sum;
}
bool fangqi(int x, int y, char c)//�������ط��ɷ��壬�Ͱ���������
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
void fanzhuanqi(int x, int y, char c)//����ɷ��壬��ת���ֵ�����
{
	int move[9][2] = {
	{0,0},//û�ã�ռ���ط���ʹ֮���ѭ�����Դ�1��ʼ
	{-1,0},//����
	{1,0},//����
	{0,1},//����
	{0,-1},//����
	{1,1},//������
	{1,-1},//������
	{-1,-1},//������
	{-1,1},//������
	};
	char duishou = fanzhuan(c);
	bool flag = false;
	if (fangqi(x, y, c))
	{
		for (int i = 1; i <= 8; i++)
		{
			int newx = x + move[i][0];
			int newy = y + move[i][1];
			while (newx >= 1 && newx <= 8 && newy >= 1 && newy <= 8 && qipan[newx][newy] != '#')//����÷������壬������������
			{
				if (qipan[newx][newy] == c)//������־��ʾ�����˵з����ӣ��ɼ�������
				{
					flag = true;
				}
				else//����������Ǽ������ӣ��Ҽ������Ӽ��ез�����
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
					break;//�˳���ǰѭ��
				}
				newx += move[i][0];
				newy += move[i][1];
			}

			flag = false;
		}
	}
}
bool gameover(char c)//�ж��Ƿ�������˴���û�ط���
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
bool fullfill()//�˴�����������
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
void playgame()//��ʼ����Ϸ
{
	ExMessage m;
	print();
	int x = 0;
	int y = 0;//��ȡ���������
	while (!fullfill())//������̻�û��
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
			Sleep(1000);//�ó�����ͣһ��
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
			if (temp == 27)//27��Ecs����
			{
				int flag = MessageBox(GetHWnd(), _T("�Ƿ񱣴浱ǰ����"), _T("��ʾ"), MB_YESNO);
				if (flag == IDYES)
				{
					cunchu();
					MessageBox(GetHWnd(), _T("����ɹ�"), _T("��ʾ"), MB_OK);
				}
				else
				{
					MessageBox(GetHWnd(), _T("δ�浵"), _T("��ʾ"), MB_OK);
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
		temp = MessageBox(GetHWnd(), _T("��ϲ����ʤ"), _T("��ʾ"), MB_OKCANCEL);
	}
	else if (blacknum < whitenum)
	{
		temp = MessageBox(GetHWnd(), _T("�ǳ���ϧ��Ҫ��Ҫ����һ�֣�"), _T("��ʾ"), MB_OKCANCEL);
	}
	/*else
	{
		temp = MessageBox(GetHWnd(), _T("ƽ��"), _T("��ʾ"), MB_OKCANCEL);
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