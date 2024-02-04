#ifndef _WALL_HEAD
#define _WALL_HEAD

#include <iostream>
#include "windows.h"

using namespace std;

class Wall
{
public:
	enum {
		ROW = 26, // 行数
		COL = 26  // 列数
	};

	// 构造函数
	Wall();

	// 析构函数
	~Wall();

	// 初始化墙
	void initWall();

	// 将墙画到控制台
	void drawWall();

	// 显示游戏结束
	void showGameOver();

	// 定位控制台的光标位置
	void gotoXY(int x, int y);

	// 获取墙的内容
	char getWall(int x, int y);

	// 设置墙的内容
	void setWall(int x, int y, char c);

private:
	// 定义墙的二维数组
	char gameArray[ROW][COL];

	// 定义显示器句柄
	HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);
};

#endif
