#include <iostream>
#include <ctime>
#include "wall.h"
#include "food.h"
#include "snake.h"
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
	// 设置随机种子
	srand((unsigned int)time(NULL));

	// 上一次移动的方向
	char preKey = NULL;

	// 初始化墙
	Wall wall;
	wall.initWall();
	wall.drawWall();

	// 初始化食物
	Food food(wall);
	food.setFood();

	// 初始化蛇
	Snake snake(wall, food);
	snake.initSnake();

	// 显示游戏得分
	snake.showScore();

	while (true) {
		// 接收用户输入
		char key = _getch();

		// 判断蛇是否已经死亡
		if (snake.isDead) {
			continue;
		}

		// 如果第一次按了左键，则撤销蛇的移动操作
		if (key == snake.LEFT && preKey == NULL) {
			continue;
		}

		do {
			// 判断移动的方向是否有效
			if (key == snake.TOP || key == snake.BOTTOM || key == snake.LEFT || key == snake.RIGHT) {
				// 判断本次移动的方向与上次是否冲突
				if ((key == snake.LEFT && preKey == snake.RIGHT) ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.TOP && preKey == snake.BOTTOM) ||
					(key == snake.BOTTOM && preKey == snake.TOP)) {
					break;
				}

				// 记录上一次移动的方向
				preKey = key;

				// 让蛇移动一步
				if (snake.move(key)) {
					// 显示游戏得分
					snake.showScore();
					// 设置等待时间（控制游戏难度）
					Sleep(snake.getSleepTime());
				}
				else {
					break;
				}
			}
			else {
				// 强制将错误按键变为上一次的移动方向
				key = preKey;
				break;
			}
		} while (!_kbhit);
	}

	return 0;
}
