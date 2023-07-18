#pragma once
#include<iostream>
#include<graphics.h>
#include<string>
#include<ctime>
#include<Windows.h>
#include<tchar.h>
#include<cmath>
#include<vector>

using namespace std;
/*ȫ�ֱ���(Ĭ����)*/
int toolNavWidth = 100;					// ���������(�߶Ⱥʹ��ڸ߶���ͬ)
int canvasWidth = 400;					// �������(�߶Ⱥʹ��ڸ߶���ͬ)
int msgNavWidth = 100;					// ��Ϣ���Ŀ��
int width = canvasWidth + toolNavWidth + msgNavWidth, height = 400;				// ��ͼ����Ĭ�Ͽ�͸�
int scale = 10;							// Ĭ������
int msgFontSize = 20;					// ��Ϣ�ı��������С
int halfCW = round(canvasWidth / 2);	// ����һ��Ŀ��
int halfH = round(height / 2);			// �߶ȵ�һ��
COLORREF functionImageColor = BLUE;		// Ĭ�Ϻ���ͼ����ɫ
vector<string> functionsList;			// �����б�

// ����ʵ��
using funp = int(*)(int);

// ����һ���ַ��Ƿ���һ��(C���Է��)�ַ�����,�ҵ��˷����±�,�Ҳ�������-1
int find(const char* str, char c) {
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == c) {
			return i;  // �ҵ��˷����±�
		}
	}
	return -1; // �Ҳ�������-1
}
/*���ַ������ʽת��Ϊ����������*/
funp getFunction(string strExpression) {
	// ����ַ���Ϊ��ֱ�ӽ���
	if (strExpression.empty()) {
		return nullptr;
	}
	// �ַ�����Ϊ�������
	int length = strExpression.size();
	string expression;
	// ȥ���ո񲢴��浽expreesion��
	for (int i = 0; i < length; i++) {
		if (strExpression[i] != ' ') {
			expression += strExpression[i];
		}
	}
	// �����ַ������ʽ
	length = expression.size();
	string num;
	double k, b;		// k��b
	double x, y;		// �Ա���x�������y
	// �ж��ַ������ʽ�Ƿ�����﷨�淶
	if (expression[0] != 'y' || expression[1] != '=') { // �����ж��Ƿ����"y=..."
		return nullptr;
	}
	for (int i = 0; i < length; i++) {
		// ���ж�ÿ���ַ�
		if ((expression[i] < '0' || expression[i]>'9') && (expression[i] != '+' && expression[i] != '-' && expression[i] != '*' && expression[i] != '/' && expression[i] != '^' && expression[i] != '(' && expression[i] != ')')) {
			// �������ַ��Ȳ�������Ҳ����֧�ֵ������
			return nullptr;
		}
	}

	// ������Ϲ淶�ͼ���
	if (expression.find('.') == string::npos) { // ���û��С����
		for (int i = 1; i < length; i++) {
			if (expression[i] < '9' && expression[i]>'0') {
				num += expression[i];
			}
			else if (expression[i] == 'x') {
				// ��������Ա���x���Ͱ�xǰ�沿�ֵ��ַ���ת��Ϊ����(����k)
				k = atoi(num.c_str());
			}
			else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
				// ����������

			}
		}
	}
	else { // �����С����
		for (int i = 1; i < length; i++) {
			if ((expression[i] < '9' && expression[i]>'0') || expression[i] == '.') {
				num += expression[i];
			}
			else if (expression[i] == 'x') {
				k = atof(num.c_str());
			}
		}
	}

	cout << expression << endl;
	return nullptr;
}
// ������ѧ����ϵ�е����꣬���ػ���������(������)
int offsetX(int x) {
	return (x + halfCW);
}
// ������ѧ����ϵ�е����꣬���ػ���������(������)
int offsetY(int y) {
	if (y > 0) {
		return (halfH-y);
	}
	else if (y == 0) {
		return halfH;
	}
	else {
		return ((-y) + halfH);
	}
}
// ����������
void positiveProportionalFunc(float k) {
	setlinecolor(BLUE);
	line(offsetX(-halfCW), offsetY(round((-halfCW) * k)), offsetX(halfCW), offsetY(round(halfCW * k)));
}
// һ�κ���
void linearFunc(float k,float b) {
	b *= scale;
	for (int x = -halfCW; x < halfCW; x++){
		putpixel(offsetX(x), offsetY(round(k * x + b)), RGB(255, 184, 32));
	}
}
// ����������
void inverseProportionalFunc(float k) {
	double x, y, xCanvas, yCanvas, xLast, yLast;
	setlinecolor(GREEN);
	x = -(halfCW*1.0/scale);
	y = k * 1.0 / x;
	xLast = xCanvas = offsetX(round(x * scale));
	yLast = yCanvas = offsetY(round(y * (-scale)));
	line(xCanvas, yCanvas, xCanvas, yCanvas);
	for (x = -(halfCW*1.0/scale); x <= (halfCW*1.0/scale); x += 0.1) {
		if (x != 0)
		{
			y = k * 1.0 / x;
			xCanvas = offsetX(round(x * scale));
			yCanvas = offsetY(round(y * (-scale)));
			line(xCanvas, yCanvas, xLast, yLast);
			xLast = xCanvas;
			yLast = yCanvas;
		}
	}
}
// ���κ���
void quadraticFunc(float a, float b, float c) {
	c *= scale;
	int xLast=offsetX(-halfCW), yLast=offsetY(round(a*(-halfCW)*(-halfCW)+b*(-halfCW)+c));	// ��һ��������
	int x=0, y=0;
	setlinecolor(RGB(255, 130, 0));
	for (int i = -halfCW+1; i <= halfCW; i++) {
		x = offsetX(i);
		y = offsetY(round(a * i * i + b * i + c));
		line(xLast, yLast, x, y);	// �������
		xLast = x, yLast = y;
	}
}
// �ݺ���
void powerFunc(float a) {
	int xLast = offsetX(-halfCW), yLast = offsetY(round(pow((-halfCW),a)));	// ��һ��������
	int x = 0, y = 0;
	setlinecolor(RED);
	for (int i = -halfCW+1; i <= halfCW; i++) {
		x = offsetX(i);
		y = offsetY(round(pow(i,a)));
		line(xLast, yLast, x, y);	// �������
		xLast = x, yLast = y;
	}
}
/*Button��*/
class Button {
public:
	int posX, posY, posXRight, posYBottom;
	int btnWidth = round(toolNavWidth * 0.7), btnHeight = round(btnWidth * 0.3);
	int textX, textY;
	const char* text;
	// ���캯�������Զ�����
	Button(int posY, const char* text) {
		this->posX = round((toolNavWidth - btnWidth) / 2) + canvasWidth;
		this->posY = posY;
		posXRight = posX + btnWidth;
		posYBottom = posY + btnHeight;
		this->text = text;
	}
	// ���캯����������λ�úʹ�С
	Button(int posX, int posY, int width, int height, const char* text) {
		this->posX = posX + canvasWidth;
		this->posY = posY;
		btnWidth = width;
		btnHeight = height;

		posXRight = posX + btnWidth;
		posYBottom = posY + btnHeight;

		this->text = text;
	}
	void show() {
		setlinecolor(RGB(127,127,127));
		setfillcolor(WHITE);
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
	}
	void showText() {
		char text_[50] = { 0 };
		strcpy_s(text_, text);
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(round(btnWidth / 4), 0, "΢���ź�");
		textX = posX + (btnWidth - textwidth(text)) / 2;
		textY = posY + (btnHeight - textheight(text)) / 2;
		outtextxy(textX, textY, text_);
	}
	// ��ť�����ʱִ�д���ĺ���
	void onButtonClick() {
		setlinecolor(BLACK);
		setfillcolor(RGB(173, 255, 242));
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
	}
	// ��갴��̧��
	void onButtonUp(void (*func)()) {
		setlinecolor(RGB(127,127,127));
		setfillcolor(WHITE);
		fillrectangle(this->posX, this->posY, this->posXRight, this->posYBottom);
		showText();
		(*func)();
	}
};
/*����������*/
void resetScale() {

}
/*����ָ������*/
void clearArea(int x1, int y1, int x2, int y2, COLORREF bgColor) {
	setfillcolor(bgColor);
	setlinecolor(bgColor);
	fillrectangle(x1, y1, x2, y2);
}
/*��������*/
void splashScreen() {
	IMAGE splashImage;
	int splashImageSize = round(min(width, height) * 0.7);
	loadimage(&splashImage, "icon.png", splashImageSize, splashImageSize);
	putimage(round((width - splashImageSize) / 2), round((height - splashImageSize) / 2), &splashImage);
	Sleep(2000);
	cleardevice();
}
/*��ʼ������*/
void initCanvas() {
	clearArea(0, 0, canvasWidth, height, BLACK);
	// �������յ�
	for (int i = 0; i <= canvasWidth; i += 10) {
		for (int j = 0; j <= height; j += 10) {
			putpixel(i, j, LIGHTBLUE);
		}
	}
	// ����������
	setlinecolor(YELLOW);
	line(0, round(height / 2), canvasWidth, round(height / 2));	// x��
	line(round(canvasWidth / 2), 0, round(canvasWidth / 2), height); // y��
}
void initToolNav() {
	// �������������
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(canvasWidth, 0, width - msgNavWidth, height);
}

void initMsgNav() {
	// ���������Ϣ��
	setlinecolor(BLACK);
	setfillcolor(WHITE);
	fillrectangle(canvasWidth + toolNavWidth, 0, width, height);
}

void initWindow() {
	// ��ʼ��
	initCanvas();
	initToolNav();
	initMsgNav();
}
/*���ô��ڴ�С*/
void resetWindowSize(int width, int height) {
	Resize(NULL, width, height);
	initWindow();
}
/*��ʾ��Ϣ*/
void showMsg(const char* text, COLORREF textColor) {
	char text_[50] = { 0 };
	strcpy_s(text_, text);
	settextcolor(textColor);
	setbkmode(TRANSPARENT);
	settextstyle(msgFontSize, 0, "΢���ź�");
	int textX = (msgNavWidth - textwidth(text)) / 2 + canvasWidth + toolNavWidth;
	BeginBatchDraw();
	for (int i = height; i >= 10; i -= 3) {
		FlushBatchDraw();
		initMsgNav();
		outtextxy(textX, i, text_);
		Sleep(1);
	}
	EndBatchDraw();

	initMsgNav();
}
/*����ֵ��������ֵ(InputBox)*/
float inputNum(const char* prompt, const char* title = "����") {
	char content[1000];
	float result;
	InputBox(content, 1000, prompt, title);
	if (strlen(content) > 0) {
		result = atof(content);
		return result;
	}
	else {
		showMsg("����Ϊ��", RED);
	}
}
/*��ȡ�û����뺯��(InputBox)*/
void inputFunction() {
	char choice[3];
	char content[1000];
	/*InputBox(content, 1000, "���뺯�����ʽ", "����");
	functionsList.push_back(content);
	if (strlen(content) == 0) {
		showMsg("���ʽΪ��", RED);
	}
	getFunction(content);*/

	int minChoice = 1, maxChoice = 5; // ��С�����ѡ��Χ
	if (InputBox(choice, 3, "1.����������\n2.һ�κ���\n3.����������\n4.���κ���\n5.�ݺ���\nѡ�������ʽ����:", "����", 0, 0, 0, false)) {
		// ���û�а�"ȡ��"
		int choiceNum = choice[0] - 48;
		if (choiceNum<minChoice||choiceNum>maxChoice) { // �ж��Ƿ���ѡ��Χ��,��������ھͽ���
			showMsg("����ѡ��Χ��",RED);
			return;
		}
		if (choiceNum==1) {
			float k=inputNum("����k:");
			positiveProportionalFunc(k);
		}
		else if(choiceNum==2) {
			float k = inputNum("����k:");
			float b = inputNum("����b:");
			linearFunc(k, b);
		}
		else if (choiceNum == 3) {
			float k = inputNum("����k");
			inverseProportionalFunc(k);
		}
		else if (choiceNum == 4) {
			float a = inputNum("����a:");
			float b = inputNum("����b:");
			float c = inputNum("����c:");
			quadraticFunc(a, b, c);
		}
		else if (choiceNum == 5) {
			float a = inputNum("����a:");
			powerFunc(a);
		}
	}
}