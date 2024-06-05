#pragma once

#include <iostream>

using namespace std;

// 游戏角色
class Role {

public:

    string m_Name;  //名称

    int m_Atk;  // 攻击力

    int m_Def;  // 防御力

    int m_Hp;   // 血量

    bool m_Hold;    // 定身

    // 攻击
    virtual void attack(Role *hero) = 0;

};