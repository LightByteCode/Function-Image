#include<iostream>
#include<graphics.h>
#include<string>
#include<ctime>
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include<vector>
//#include "function.h"
#include "base.hpp"

using namespace std;

/*������*/
int main() {
	// ��ʼ����ͼ����
	initgraph(width, height);
	setbkcolor(BLACK);
	cleardevice();
	// ��������
	splashScreen();
	// ��ʼ��
	initWindow();
	// ��ť
	Button newFunc(15, "���ƺ���"), clearCanvas(50, "��ջ���");
	newFunc.show();
	clearCanvas.show();
	// ѭ�������������Ϣ
	ExMessage m;
	while (true) {
		m = getmessage(EX_MOUSE | EX_KEY);
		if (m.message == WM_LBUTTONDOWN) {
			if (m.x>newFunc.posX&&m.x<newFunc.posXRight&&m.y>newFunc.posY&&m.y<newFunc.posYBottom) {
				newFunc.onButtonClick();
			}
			else if (m.x > clearCanvas.posX && m.x<clearCanvas.posXRight && m.y>clearCanvas.posY && m.y < clearCanvas.posYBottom) {
				clearCanvas.onButtonClick();
			}
		}
		else if (m.message == WM_LBUTTONUP) {
			if (m.x > newFunc.posX && m.x<newFunc.posXRight && m.y>newFunc.posY && m.y < newFunc.posYBottom) {
				newFunc.onButtonUp(inputFunction);
			}
			else if (m.x > clearCanvas.posX && m.x<clearCanvas.posXRight && m.y>clearCanvas.posY && m.y < clearCanvas.posYBottom) {
				clearCanvas.onButtonUp(initCanvas);
			}
		}
	}
	// �رջ�ͼ����
	getmessage(EX_KEY);
	closegraph();
	return 0;
}