#ifndef _FOOD_HEAD
#define _FOOD_HEAD

#include <iostream>
#include "wall.h"

using namespace std;

class Food
{
public:

	// ���캯��
	Food(Wall & tempWall);

	// ʳ���X����
	int x;

	// ʳ���Y����
	int y;

	// ǽ
	Wall& wall;

	// ����ʳ��
	void setFood();

};

#endif
