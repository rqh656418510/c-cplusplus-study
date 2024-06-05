#include "Monster.h"
#include "Hero.h"

Monster::Monster() {
    this->m_Hp = 300;
    this->m_Atk = 70;
    this->m_Def = 40;
    this->m_Hold = false;
    this->m_Name = "大魔王";
}

// 攻击
void Monster::attack(Hero *hero) {
    if (this->m_Hold) {
        cout << "怪物" << this->m_Name << "被定身了，本回合无法攻击" << endl;
    }

    // 计算英雄真实伤害
    int realDamage = (this->m_Atk - hero->m_Def) > 0 ? this->m_Atk - hero->m_Def : 1;

    // 设置英雄血量
    hero->m_Hp -= realDamage;

    cout << "怪物" << this->m_Name << "攻击了英雄" << hero->m_Name << "，造成了 " << realDamage << " 点伤害" << endl;
}
