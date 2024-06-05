#pragma once

#include <iostream>
#include "Weapon.h"

using namespace std;

// 屠龙刀
class DragonSword : public Weapon {

public:

    DragonSword();

    // 获取基础伤害
    virtual int getBaseDamage() override;

    // 获取吸血
    virtual int getSuckBlood() override;

    // 获取是否定身
    virtual bool getHold() override;

    // 获取是否暴击
    virtual bool getCrit() override;

    // 是否触发
    bool isTrigger(int rate);

    // 吸血率
    int suckRate;

    // 定身率
    int holdRate;

    // 暴击率
    int critRate;

};
