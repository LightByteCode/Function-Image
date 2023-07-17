#include <graphics.h>
#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <string.h>
#include <cmath>

using namespace std;

void linear_function(int k, int b) {
	b = b * 10;
	setlinecolor(GREEN);
	int x, y; int xx, yy; int xxx, yyy;
	{
		x = -320;
		y = k * x + b;
		xxx = xx = x + 320;
		yyy = yy = -y + 240;
		line(xx, yy, xx, yy);
		for (int x = -319; x <= 320; x++)
		{
			y = k * x + b;
			xx = x + 320;
			yy = -y + 240;
			line(xx, yy, xxx, yyy);
			xxx = x + 320;
			yyy = -y + 240;
		}
	}
}

void quadratic_function(int a, int b, int c) {
	double a1 = double(a), b1 = double(b), c1 = double(c);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(YELLOW);
	x = -32;
	y = a1 * x * x + b1 * x + c1;
	xxx = xx = round(x * 10 + 320);
	yyy = yy = round(y * (-10) + 240);
	line(xx, yy, xx, yy);
	for (x = -31.9; x <= 32; x += 0.1)
	{
		if (x != 0)
		{
			y = a1 * x * x + b1 * x + c1;
			xx = round(x * 10 + 320);
			yy = round(y * (-10) + 240);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + 320);
			yyy = round(y * (-10) + 240);
		}
	}
}

void inverse_proportional_function(int k) {
	double k1 = double(k);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(LIGHTBLUE);
	x = -32;
	y = k * 1.0 / x;
	xxx = xx = round(x * 10 + 320);
	yyy = yy = round(y * (-10) + 240);
	line(xx, yy, xx, yy);
	for (x = -31.9; x <= 32; x += 0.1)
	{
		if (x != 0)
		{
			y = k / x;
			xx = round(x * 10 + 320);
			yy = round(y * (-10) + 240);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + 320);
			yyy = round(y * (-10) + 240);
		}
	}
}

void draw_canvas() {
	//��ʼ--���ƻ���
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(LIGHTCYAN);
	line(0, 240, 640, 240);
	line(320, 0, 320, 480);
	for (int x = 0; x <= 640; x += 10){
		for (int y = 0; y <= 480; y += 10){
			if (x == 320 || y == 240) {
				continue;
			}
			else {
				putpixel(x, y, LIGHTGRAY);
			}
		}
	}
}

int main()
{
	initgraph(640, 480, SHOWCONSOLE);
	/*
		SHOWCONSOLE  ��ʾС�ڴ�
		NOCLOSE      no close
		NOMINIMIZE   no ��С��
		DBLCLKS      �ڻ�ͼ������֧�����˫���¼�
	*/
	draw_canvas();
	//�������
	char type;
	int a, b, c, k;
	//����
	cout << "��ӭʹ�ú���ͼ����ƹ��ߣ�\n����2:���κ���;\n����1:һ�κ���;\n����0:����������\n����3:�˳�(exit)\n����4:���ͼ��\n\n";
	while (true) {
		type = _getch();//����ѡ��
		if (type == '2') {
			cout << "�������ʽ:y=ax^2+bx+c\na=";
			cin >> a;
			cout << "b=";
			cin >> b;
			cout << "c=";
			cin >> c;
			quadratic_function(a, b, c);
		}
		else if (type == '1') {
			cout << "�������ʽ:y=kx+b\nk=";
			cin >> k;
			cout << "b=";
			cin >> b;
			linear_function(k, b);
		}
		else if (type == '0') {
			cout << "k=";
			cin >> k;
			inverse_proportional_function(k);
		}
		else if (type == '3') {
			return 0;
		}
		else if (type == '4') {
			cleardevice();
			draw_canvas();
		}
		cout << '\n';
	}
	//�������
	_getwch();
	closegraph();
	return 0;
}