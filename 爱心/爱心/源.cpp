#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include<graphics.h>
#include<time.h>
#include<math.h>

struct love {
    int height;
    double angle;
    double r; //r0..1)
    double curR;
    int x;
    int y;
};

struct love mylove[400];
int offX = 260;
int offY = 180;
double R = 60;

void init() {
    initgraph(600, 480);
    memset(mylove, 0, sizeof(mylove));
    srand(time(NULL));
}

void getRandAngles(int* buf, int count) {
    int rangle = 314 * 2 * 2;
    for (int i = 0; i < count; i++) {
        int randTmp = 0;
        while (1) {
            randTmp = rand() % rangle;
            int j;
            for (j = 0; j < i && buf[j] != randTmp; j++);
            if (j >= i) break;
        }
        buf[i] = randTmp;
    }
}

void xiugaiData() {
    for (int i = 0; i < 400; i++) {
        if (mylove[i].curR == 0) continue;
        mylove[i].curR++;
        if (mylove[i].curR > 80) {
            memset(&mylove[i], 0, sizeof(struct love));
        }
        mylove[i].height++;
        mylove[i].x = (int)(-mylove[i].curR * mylove[i].r * cos(mylove[i].angle) + offX);
        mylove[i].y = -mylove[i].curR * mylove[i].r * sin(mylove[i].angle) + offY - mylove[i].curR;
    }
}

void addNewHeart() {
    int buf[20];
    getRandAngles(buf, 20);
    int k;
    for (k = 0; k < 400 && mylove[k].curR > 0; k++);

    for (int i = k; i < k + 20; i++) {
        double angle = mylove[i].angle = buf[i - k] * 0.01;
        mylove[i].r = sin(angle) * sqrt(fabs(cos(angle))) / (sin(angle) + 1.4142) - 2 * sin(angle) + 2;
        mylove[i].curR = R;
        mylove[i].height = 0;
        mylove[i].x = mylove[i].curR * mylove[i].r * cos(mylove[i].angle) + offX;
        mylove[i].y = -mylove[i].curR * mylove[i].r * sin(mylove[i].angle) + offY - mylove[i].curR;
    }
}

void updateWindow()
{
    BeginBatchDraw();
    cleardevice();
    settextcolor(RED);
    for (int i = 0; i < 400; i++) {
        if (mylove[i].curR == 0)continue;
        settextstyle(mylove[i].height + 10, 0, "Webdings");
        setbkmode(TRANSPARENT);
        outtextxy(mylove[i].x + 20, mylove[i].y + 20, 'Y'); //89
    }
    EndBatchDraw();
}

void mySleep(int delay) {
    unsigned long long start = GetTickCount();
    if (GetTickCount() < start + delay) Sleep(1);
}

int main() {
    init();
    while (1) {
        addNewHeart();
        updateWindow();
        xiugaiData();
        mySleep(30);
    }
    return 0;
}
