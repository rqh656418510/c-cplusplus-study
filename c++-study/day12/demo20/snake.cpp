#include "snake.h"

Snake::Snake(Wall& tempWall, Food& tempFood) :wall(tempWall), food(tempFood) {
	pHead = NULL;
	isDead = false;
	isRool = false;
}

void Snake::initSnake()
{
	// �������нڵ�
	this->destroy();
	// ��������ڵ�
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

	// �����ƶ���λ��
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

	// ����β�ڵ�
	Point* pPre = pHead;
	Point* pEnd = pHead->next;
	while (pEnd->next != NULL) {
		pPre = pPre->next;
		pEnd = pEnd->next;
	}

	// �ж�����ƶ���һ������������β�ͣ���Ӧ������
	if (pEnd->x == x && pEnd->y == y) {
		isRool = true;
	}
	else {
		// �ж��ƶ���λ���Ƿ�Ϸ������Ϸ�����Ϸ����
		if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=') {
			// �������״̬
			isDead = true;
			// �������һ��
			addPoint(x, y);
			// ��ʾ��Ϸ����
			wall.showGameOver();
			// ��ʾ��Ϸ�÷�
			showScore();
			return false;
		}
	}

	// �ж��ƶ��ɹ����Ƿ�Ե�ʳ��
	if (wall.getWall(x, y) == '#') {
		// ��ӽڵ�
		addPoint(x, y);
		// ��������ʳ���λ��
		food.setFood();
	}
	else {
		// ��ӽڵ�
		addPoint(x, y);
		// ɾ��β�ڵ�
		deleteEndPoint();
		// ������ʾͷ�ڵ�
		if (isRool) {
			wall.setWall(x, y, '@');
		}
	}

	return true;
}

void Snake::addPoint(int x, int y)
{
	// �µ�ͷ�ڵ�
	Point* newPoint = new Point();
	newPoint->x = x;
	newPoint->y = y;

	// ����ɵ�ͷ��㲻Ϊ�գ������Ϊ���ӽڵ�
	if (pHead != NULL) {
		wall.setWall(pHead->x, pHead->y, '=');
	}

	// ����ͷ�ڵ�
	newPoint->next = pHead;
	pHead = newPoint;
	wall.setWall(newPoint->x, newPoint->y, '@');
}

void Snake::deleteEndPoint()
{
	// �����������ڵ����ϣ�������ִ��ɾ������
	if (pHead == NULL || pHead->next == NULL) {
		return;
	}

	// ����β�ڵ�
	Point* pPre = pHead;
	Point* pEnd = pHead->next;
	while (pEnd->next != NULL) {
		pPre = pPre->next;
		pEnd = pEnd->next;
	}

	// ɾ��β�ڵ�
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
	cout << "\n��Ϸ�÷֣�" << getScore() << endl;
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
	// �����ߵĳ��ȣ����Ƶȴ�ʱ�䣬�Դ˴ﵽ������Ϸ�Ѷȵ�Ŀ��
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
