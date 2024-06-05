#include "Hero.h"
#include "Weapon.h"

Hero::Hero() {
    this->m_Hp = 500;
    this->m_Atk = 50;
    this->m_Def = 50;
    this->m_Name = "法师";
    this->weapon = nullptr;
}

// 攻击
void Hero::attack(Role *monster) {
    int damage = 0; // 伤害
    int addHp = 0;  // 吸血
    bool isHold = false;
    bool isCrit = false;

    if (this->weapon == nullptr) {
        damage = this->m_Atk;
    } else {
        // 伤害
        damage = this->m_Atk + this->weapon->getBaseDamage();
        // 吸血
        addHp = this->weapon->getSuckBlood();
        // 定身
        isHold = this->weapon->getHold();
        // 暴击
        isCrit = this->weapon->getCrit();
    }

    if (addHp > 0) {
        cout << "英雄的武器触发了吸血效果，英雄增加的血量为 " << addHp << endl;
    }

    if (isHold) {
        cout << "英雄的武器触发了定身效果，怪物停止攻击一回合" << endl;
    }

    if (isCrit) {
        damage = damage * 2;
        cout << "英雄的武器触发了暴击效果，怪物受到双倍伤害: " << damage << endl;
    }

    // 设置怪物定身
    monster->m_Hold = isHold;

    // 计算怪物真实伤害
    int realDamage = (damage - monster->m_Def) > 0 ? damage - monster->m_Def : 1;

    // 设置怪物血量
    monster->m_Hp -= realDamage;

    // 设置英雄吸血
    this->m_Hp += addHp;

    cout << "英雄" << this->m_Name << "攻击了怪物" << monster->m_Name << "，造成了 " << realDamage << " 点伤害" << endl;
}

// 装备武器
void Hero::equipWeapon(Weapon *weapon) {
    this->weapon = weapon;
    cout << "英雄" << this->m_Name << "装备了武器" << this->weapon->m_WeaponName << endl;
}
