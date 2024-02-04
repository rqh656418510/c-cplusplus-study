#ifndef _FOOD_HEAD
#define _FOOD_HEAD

#include <iostream>
#include "wall.h"

using namespace std;

class Food
{
public:

	// 构造函数
	Food(Wall & tempWall);

	// 食物的X坐标
	int x;

	// 食物的Y坐标
	int y;

	// 墙
	Wall& wall;

	// 设置食物
	void setFood();

};

#endif
