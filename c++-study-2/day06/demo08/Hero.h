#pragma once

#include <iostream>
#include "Role.h"
#include "Weapon.h"
#include "Monster.h"

using namespace std;

// 英雄
class Hero : public Role {

public:

    Hero();

    // 攻击
    virtual void attack(Role *hero) override;

    // 装备武器
    void equipWeapon(Weapon *weapon);

    Weapon *weapon;   // 武器

};
