/**
 * 多态案例二 - PK游戏开发
 */

#include <iostream>
#include "Hero.h"
#include "Weapon.h"
#include "Monster.h"
#include "Knife.h"
#include "DragonSword.h"

using namespace std;

void playGame() {
    // 创建英雄
    Hero *hero = new Hero();

    // 创建怪物
    Monster *monster = new Monster();

    // 创建武器
    Weapon *knife = new Knife();
    Weapon *dragonSword = new DragonSword();

    cout << "请选择武器:" << endl;
    cout << "1. 赤手空拳" << endl;
    cout << "2. 小刀" << endl;
    cout << "3. 屠龙刀" << endl;

    int operation;
    cin >> operation;

    switch (operation) {
        case 1:
            cout << "赤手空拳能打赢，那就算你厉害" << endl;
            break;
        case 2:
            hero->equipWeapon(knife);
            break;
        case 3:
            hero->equipWeapon(dragonSword);
            break;
        default:
            break;
    }

    // 输入缓冲区里有一个回车键，多获取一次输入值
    getchar();

    int round = 1;
    while (true) {
        getchar();
        system("clear");

        cout << "------ 当前是第 " << round << " 几回合 " << endl;

        if (hero->m_Hp <= 0) {
            cout << "英雄" << hero->m_Name << "已经死亡，游戏结束" << endl;
            break;
        }

        // 英雄攻击怪物
        hero->attack(monster);

        if (monster->m_Hp <= 0) {
            cout << "怪物" << monster->m_Name << "已经死亡，游戏顺利通关" << endl;
            break;
        }

        // 怪物攻击英雄
        monster->attack(hero);

        if (hero->m_Hp <= 0) {
            cout << "英雄" << hero->m_Name << "已经死亡，游戏结束" << endl;
            break;
        }

        cout << "英雄剩余血量：" << hero->m_Hp << endl;
        cout << "怪物剩余血量：" << monster->m_Hp << endl;

        round++;
    }

    delete knife;
    delete dragonSword;
    delete hero;
    delete monster;
}

int main() {
    // 使用当前时间作为随机种子
    srand(static_cast<unsigned int>(time(nullptr)));

    playGame();

    return 0;
}
