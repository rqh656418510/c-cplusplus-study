#ifndef _WALL_HEAD
#define _WALL_HEAD

#include <iostream>
#include "windows.h"

using namespace std;

class Wall
{
public:
	enum {
		ROW = 26, // ����
		COL = 26  // ����
	};

	// ���캯��
	Wall();

	// ��������
	~Wall();

	// ��ʼ��ǽ
	void initWall();

	// ��ǽ��������̨
	void drawWall();

	// ��ʾ��Ϸ����
	void showGameOver();

	// ��λ����̨�Ĺ��λ��
	void gotoXY(int x, int y);

	// ��ȡǽ������
	char getWall(int x, int y);

	// ����ǽ������
	void setWall(int x, int y, char c);

private:
	// ����ǽ�Ķ�ά����
	char gameArray[ROW][COL];

	// ������ʾ�����
	HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);
};

#endif
