#include "Monster.h"

Monster::Monster() {
    this->m_Hp = 300;
    this->m_Atk = 70;
    this->m_Def = 40;
    this->m_Hold = false;
    this->m_Name = "大魔王";
}

// 攻击
void Monster::attack(Hero *hero) {

}
