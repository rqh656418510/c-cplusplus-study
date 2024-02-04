#ifndef _SNAKE_HEAD
#define _SNAKE_HEAD

#include <iostream>
#include "wall.h"
#include "food.h"

using namespace std;

class Snake
{

public:

	// 构造函数
	Snake(Wall& tempWall, Food& tempFood);

	// 移动的方向
	enum {
		TOP = 'w',
		BOTTOM = 's',
		LEFT = 'a',
		RIGHT = 'd'
	};

	// 蛇的初始长度
	const int INIT_LENGTH = 3;

	// 节点
	struct Point {
		int x;
		int y;
		Point* next;
	};

	// 头节点
	Point* pHead;

	// 墙
	Wall& wall;

	// 食物
	Food& food;

	// 死亡标识
	bool isDead;

	// 循环追尾
	bool isRool;

	// 初始化蛇
	void initSnake();

	// 销毁所有节点
	void destroy();

	// 移动蛇
	bool move(char key);

	// 添加节点
	void addPoint(int x, int y);

	// 删除尾节点
	void deleteEndPoint();

	// 获取游戏分数
	int getScore();

	// 显示游戏得分
	void showScore();

	// 获取蛇的长度
	int getLength();

	// 获取等待的时间（毫秒）
	int getSleepTime();

};

#endif
