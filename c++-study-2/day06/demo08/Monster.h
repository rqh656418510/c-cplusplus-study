#pragma once

#include <iostream>
#include "Hero.h"

using namespace std;

// 怪物
class Monster {

public:

    Monster();

    // 攻击
    void attack(Hero *hero);

    string m_Name;  //名称

    int m_Atk;  // 攻击力

    int m_Def;  // 防御力

    int m_Hp;   // 血量

    bool m_Hold;    // 定身

};
