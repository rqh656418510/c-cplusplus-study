#include "snake.h"

Snake::Snake(Wall& tempWall, Food& tempFood) :wall(tempWall), food(tempFood) {
	pHead = NULL;
	isDead = false;
	isRool = false;
}

void Snake::initSnake()
{
	// 销毁所有节点
	this->destroy();
	// 设置蛇身节点
	for (int i = 0; i < INIT_LENGTH; i++) {
		this->addPoint(12, 10 + i);
	}
}

void Snake::destroy()
{
	Point* pCur = pHead;
	while (pHead != NULL) {
		pCur = pHead->next;
		pHead = pCur;
	}
}

bool Snake::move(char key)
{
	isRool = false;
	int x = pHead->x;
	int y = pHead->y;

	// 计算移动的位置
	switch (key) {
	case TOP:
		x--;
		break;
	case BOTTOM:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	// 查找尾节点
	Point* pPre = pHead;
	Point* pEnd = pHead->next;
	while (pEnd->next != NULL) {
		pPre = pPre->next;
		pEnd = pEnd->next;
	}

	// 判断如果移动下一步后碰到的是尾巴，则不应该死亡
	if (pEnd->x == x && pEnd->y == y) {
		isRool = true;
	}
	else {
		// 判断移动的位置是否合法，不合法则游戏结束
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=') {
			// 标记死亡状态
			isDead = true;
			// 死后多走一步
			addPoint(x, y);
			// 显示游戏结束
			wall.showGameOver();
			// 显示游戏得分
			showScore();
			return false;
		}
	}

	// 判断移动成功后，是否吃到食物
	if (wall.getWall(x, y) == '#') {
		// 添加节点
		addPoint(x, y);
		// 重新设置食物的位置
		food.setFood();
	}
	else {
		// 添加节点
		addPoint(x, y);
		// 删除尾节点
		deleteEndPoint();
		// 重新显示头节点
		if (isRool) {
			wall.setWall(x, y, '@');
		}
	}

	return true;
}

void Snake::addPoint(int x, int y)
{
	// 新的头节点
	Point* newPoint = new Point();
	newPoint->x = x;
	newPoint->y = y;

	// 如果旧的头结点不为空，则将其改为身子节点
	if (pHead != NULL) {
		wall.setWall(pHead->x, pHead->y, '=');
	}

	// 更新头节点
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(newPoint->x, newPoint->y, '@');
}

void Snake::deleteEndPoint()
{
	// 蛇身有两个节点以上，才允许执行删除操作
	if (pHead == NULL || pHead->next == NULL) {
		return;
	}

	// 查找尾节点
	Point* pPre = pHead;
	Point* pEnd = pHead->next;
	while (pEnd->next != NULL) {
		pPre = pPre->next;
		pEnd = pEnd->next;
	}

	// 删除尾节点
	wall.setWall(pEnd->x, pEnd->y, ' ');
	delete pEnd;
	pEnd = NULL;

	pPre->next = NULL;
}

int Snake::getScore()
{
	int length = getLength();
	int score = (length - INIT_LENGTH) * 100;
	return score;
}

void Snake::showScore() {
	wall.gotoXY(0, Wall::ROW);
	cout << "\n游戏得分：" << getScore() << endl;
}

int Snake::getLength() {
	int length = 0;
	Point* pCur = pHead;
	while (pCur != NULL) {
		length++;
		pCur = pCur->next;
	}
	return length;
}

int Snake::getSleepTime() {
	// 根据蛇的长度，控制等待时间，以此达到控制游戏难度的目的
	int length = getLength();
	if (length <= 5) {
		return 200;
	}
	else if (length <= 10) {
		return 100;
	}
	else {
		return 50;
	}
}
