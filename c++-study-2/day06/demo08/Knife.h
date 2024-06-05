#pragma once

#include <iostream>
#include "Weapon.h"

using namespace std;

// 小刀
class Knife : public Weapon {

public:

    Knife();

    // 获取基础伤害
    virtual int getBaseDamage() override;

    // 获取吸血
    virtual int getSuckBlood() override;

    // 获取是否定身
    virtual bool getHold() override;

    // 获取是否暴击
    virtual bool getCrit() override;

};
