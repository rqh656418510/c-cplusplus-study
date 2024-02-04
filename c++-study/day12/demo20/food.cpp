#include "food.h"
#include "wall.h"

Food::Food(Wall& tempWall) :wall(tempWall)
{

}

void Food::setFood()
{
	while (true) {
		x = rand() % (Wall::ROW - 2) + 1;
		y = rand() % (Wall::COL - 2) + 1;

		// ��������λ������ͷ�����������������������
		if (wall.getWall(x, y) == ' ') {
			wall.setWall(x, y, '#');
			break;
		}
	}
}
