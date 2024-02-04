#ifndef _SNAKE_HEAD
#define _SNAKE_HEAD

#include <iostream>
#include "wall.h"
#include "food.h"

using namespace std;

class Snake
{

public:

	// ���캯��
	Snake(Wall& tempWall, Food& tempFood);

	// �ƶ��ķ���
	enum {
		TOP = 'w',
		BOTTOM = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	// �ߵĳ�ʼ����
	const int INIT_LENGTH = 3;

	// �ڵ�
	struct Point {
		int x;
		int y;
		Point* next;
	};

	// ͷ�ڵ�
	Point* pHead;

	// ǽ
	Wall& wall;

	// ʳ��
	Food& food;

	// ������ʶ
	bool isDead;

	// ѭ��׷β
	bool isRool;

	// ��ʼ����
	void initSnake();

	// �������нڵ�
	void destroy();

	// �ƶ���
	bool move(char key);

	// ��ӽڵ�
	void addPoint(int x, int y);

	// ɾ��β�ڵ�
	void deleteEndPoint();

	// ��ȡ��Ϸ����
	int getScore();

	// ��ʾ��Ϸ�÷�
	void showScore();

	// ��ȡ�ߵĳ���
	int getLength();

	// ��ȡ�ȴ���ʱ�䣨���룩
	int getSleepTime();

};

#endif
