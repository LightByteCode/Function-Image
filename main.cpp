#include <graphics.h>
#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <ctime>
#include <cstring>
#include <cmath>

using namespace std;

int screen_width=640,screen_height=480;

void linear_function(int k, int b) {
	/*һ�κ���*/
	b = b * 10;
	setlinecolor(GREEN);
	int x, y; int xx, yy; int xxx, yyy;
	{
		x = -screen_width/2;
		y = k * x + b;
		xxx = xx = x + screen_width/2;
		yyy = yy = -y + screen_height/2;
		line(xx, yy, xx, yy);
		for (int x = -(screen_width/2-1); x <= screen_width/2; x++)
		{
			y = k * x + b;
			xx = x + screen_width/2;
			yy = -y + screen_height/2;
			line(xx, yy, xxx, yyy);
			xxx = x + screen_width/2;
			yyy = -y + screen_height/2;
		}
	}
}

void quadratic_function(int a, int b, int c) {
	/*���κ���*/
	double a1 = double(a), b1 = double(b), c1 = double(c);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(YELLOW);
	x = -32;
	y = a1 * x * x + b1 * x + c1;
	xxx = xx = round(x * 10 + screen_width/2);
	yyy = yy = round(y * (-10) + screen_height/2);
	line(xx, yy, xx, yy);
	for (x = -(screen_width/20.0-0.1); x <= screen_width/20; x += 0.1)
	{
		if (x != 0)
		{
			y = a1 * x * x + b1 * x + c1;
			xx = round(x * 10 + screen_width/2);
			yy = round(y * (-10) + screen_height/2);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + screen_width/2);
			yyy = round(y * (-10) + screen_height/2);
		}
	}
}

void inverse_proportional_function(int k) {
	/*������*/
	double k1 = double(k);
	double x, y, xx, yy, xxx, yyy;
	setlinecolor(LIGHTBLUE);
	x = -32;
	y = k * 1.0 / x;
	xxx = xx = round(x * 10 + screen_width/2);
	yyy = yy = round(y * (-10) + screen_height/2);
	line(xx, yy, xx, yy);
	for (x = -(screen_width/20.0-0.1); x <= screen_height/20; x += 0.1)
	{
		if (x != 0)
		{
			y = k / x;
			xx = round(x * 10 + screen_width/2);
			yy = round(y * (-10) + screen_height/2);
			line(xx, yy, xxx, yyy);
			xxx = round(x * 10 + screen_width/2);
			yyy = round(y * (-10) + screen_height/2);
		}
	}
}

void draw_canvas() {
	/*��ʼ--���ƻ���*/
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(LIGHTCYAN);
	line(0, screen_height/2, screen_width, screen_height/2);
	line(screen_width/2, 0, screen_width/2, screen_height);
	for (int x = 0; x <= screen_width; x += 10){
		for (int y = 0; y <= screen_height; y += 10){
			if (x == screen_width/2 || y == screen_height/2) {
				continue;
			}
			else {
				putpixel(x, y, LIGHTGRAY);
			}
		}
	}
}

int main(){
	initgraph(screen_width, screen_height, SHOWCONSOLE);
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
	cout << "��ӭʹ�ú���ͼ����ƹ��ߣ�\n����2:���κ���;\n����1:һ�κ���;\n����0:����������\n����3:�˳�(exit)\n����4:���ͼ��\n����5:�ı仭����С\n\n";
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
		else if(type=='5'){
			cout<<"�����:";
			cin>>screen_width;
			cout<<"�����:";
			cin>>screen_height;
			initgraph(screen_width,screen_height,SHOWCONSOLE);
			draw_canvas();
		}
		cout << '\n';
	}
	//�������
	closegraph();
	return 0;
}
