#include "DragonSword.h"


DragonSword::DragonSword() {
    this->m_BaseDamage = 20;
    this->m_WeaponName = "屠龙刀";
    this->suckRate = 20;
    this->holdRate = 30;
    this->critRate = 40;
}

// 获取基础伤害
int DragonSword::getBaseDamage() {
    return this->m_BaseDamage;
}

// 获取吸血
int DragonSword::getSuckBlood() {
    if (isTrigger(this->suckRate)) {
        // 按照武器基础伤害一半吸血
        return this->m_BaseDamage * 0.5;
    }
    return 0;
}

// 获取是否定身
bool DragonSword::getHold() {
    return isTrigger(this->holdRate);
}

// 获取是否暴击
bool DragonSword::getCrit() {
    return isTrigger(this->critRate);
}

// 是否触发
bool DragonSword::isTrigger(int rate) {
    int num = rand() % 100 + 1;
    return num < rate;
}
