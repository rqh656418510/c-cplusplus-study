#pragma once

#include <iostream>
#include "Role.h"

using namespace std;

// 怪物
class Monster : public Role {

public:

    Monster();

    // 攻击
    virtual void attack(Role *hero) override;

};
