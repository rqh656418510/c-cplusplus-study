#pragma once

#include <iostream>
#include "Weapon.h"
#include "Monster.h"

using namespace std;

// 英雄
class Hero {

public:

    Hero();

    // 攻击
    void attack(Monster *monster);

    // 装备武器
    void equipWeapon(Weapon *weapon);

    string m_Name;  //名称

    int m_Atk;  // 攻击力

    int m_Def;  // 防御力

    int m_Hp;   // 血量

    Weapon *weapon;   // 武器

};
