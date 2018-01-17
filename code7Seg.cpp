#include <iostream>
#include <conio.h>
#include <winbgim.h>
using namespace std;

int rect[][10] = {
    {60, 30, 180, 30, 180, 40, 60, 40, 60, 30},
    {190, 45, 200, 45, 200, 165, 190, 165, 190, 45},
    {190, 185, 200, 185, 200, 305, 190, 305, 190, 185},
    {60, 310, 180, 310, 180, 320, 60, 320, 60, 310},
    {40, 185, 50, 185, 50, 305, 40, 305, 40, 185},
    {40, 45, 50, 45, 50, 165, 40, 165, 40, 45},
    {60, 170, 180, 170, 180, 180, 60, 180, 60, 170}
};

void initGraph() {
	initwindow(350, 450);
	setbkcolor(15);
	cleardevice();
	setwindowtitle("Code Led7seg - John McTavish");
	setcolor(0);
	settextstyle(3, 0, 2);
	outtextxy(240, 40, "Mode:");
	outtextxy(40, 350, "Bin code : ");
	outtextxy(40, 380, "Hexa code: ");
}

char* hexa(int* led, int mode) {
	char* st = new char[6];
	char hex[17] = "0123456789ABCDEF";
	strcpy(st, "0x");
	int tmp1 = (led[7] * 8 + led[6] * 4 + led[5] * 2 + led[4]) % 16,
		tmp2 = (led[3] * 8 + led[2] * 4 + led[1] * 2 + led[0]) % 16;
	if(mode){
		tmp1 = 15 - tmp1;
		tmp2 = 15 - tmp2;
	}
	st[2] = hex[tmp1];
	st[3] = hex[tmp2];
	st[4] = ' ';
	st[5] = '\0';
	return st;
}

int main() {
	initGraph();
	int led[8];
	for(int i = 0; i < 8; i++) led[i] = 0;
	int mode = 1;
	while(true) {
		// mode
		setcolor(0);
		if(mode){
			setbkcolor(14);
			outtextxy(240, 60, "  AC  ");
			setbkcolor(15);
			outtextxy(240, 80, "  CC  ");
		} else {
			setbkcolor(15);
			outtextxy(240, 60, "  AC  ");
			setbkcolor(14);
			outtextxy(240, 80, "  CC  ");
		}
		// led7seg
		setcolor(1);
		for(int i = 0; i < 7; i++){
			if(!led[i]) setfillstyle(1, 15);
			else setfillstyle(1, 1);
			fillpoly(5, rect[i]);
		}
		if(led[7]){
			circle(205, 325, 10);
			setfillstyle(1, 1);
			floodfill(205, 325, 1);
		}
		else {
			setfillstyle(1, 15);
			setcolor(15);
			bar(195, 315, 215, 335);
			setcolor(1);
			circle(205, 325, 10);
		}
		// code
		// binary
		setcolor(4);
		setbkcolor(15);
		for(int i = 7; i >= 0; i--){
			if(mode)
				outtextxy(170 + (7 - i) * 10, 350, (led[i] ? "0" : "1"));
			else
				outtextxy(170 + (7 - i) * 10, 350, (led[i] ? "1" : "0"));
		}
		// hexa
		outtextxy(200, 380, hexa(led,mode));
		// click
		while(!kbhit() && !ismouseclick(WM_LBUTTONDOWN));
		if(kbhit()) {
			char key = getch();
			if(key == 27) break;
		}
		if(ismouseclick(WM_LBUTTONDOWN)) {
			int x, y;
			getmouseclick(WM_LBUTTONUP, x, y);
			if(240 <= x && x <= 285){
				if(60 <= y && y < 80) mode = 1;
				else if(80 <= y && y < 100) mode = 0;
			}
			else if(60 <= x && x <= 180){
				if(30 <= y && y <= 40) led[0] = !led[0];
				else if(310 <= y && y <= 320) led[3] = !led[3];
				else if(170 <= y && y <= 180) led[6] = !led[6];
			}
			else if(45 <= y && y <= 165){
				if(190 <= x && x <= 200) led[1] = !led[1];
				else if(40 <= x && x <= 50) led[5] = !led[5];
			}
			else if(185 <= y && y <= 305){
				if(190 <= x && x <= 200) led[2]= !led[2];
				else if(40 <= x && x <= 50) led[4]= !led[4];
			}
			else if((x - 205) * (x - 205) + (y - 325) * (y - 325) <= 100) led[7] = !led[7];
		}
		Sleep(10);
	}
}