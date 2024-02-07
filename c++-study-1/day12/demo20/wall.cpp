#include "wall.h"

#include "windows.h"


Wall::Wall() {

}

Wall::~Wall() {

}

void Wall::initWall()
{
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1) {
				gameArray[i][j] = '*';
			}
			else {
				gameArray[i][j] = ' ';
			}
		}
	}
}

void Wall::drawWall() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << gameArray[i][j] << " ";
		}
		if (i == 5) {
			cout << "create by clay";
		}
		if (i == 6) {
			cout << "a: left";
		}
		if (i == 7) {
			cout << "d: right";
		}
		if (i == 8) {
			cout << "w: top";
		}
		if (i == 9) {
			cout << "s: bottom";
		}
		cout << "\n";
	}
}

void Wall::showGameOver()
{
	string tip = "GameOver!";
	for (int i = 0; i < tip.length(); i++) {
		setWall(12, 8 + i, tip.at(i));
	}
}

void Wall::gotoXY(int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut1, pos);
}

char Wall::getWall(int x, int y)
{
	return gameArray[x][y];
}

void Wall::setWall(int x, int y, char c)
{
	gameArray[x][y] = c;
	// 通过定位光标修改控制台的内容
	gotoXY(y * 2, x);
	cout << c;
}
