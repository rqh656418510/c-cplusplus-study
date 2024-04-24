/**
 * 菱形继承的问题以及解决方案
 *
 * <p> 使用虚继承解决菱形继承的问题
 */

#include <iostream>

using namespace std;

// 动物
class Animal {

public:
    int m_Age;

};

// 羊，虚继承
class Sheep : virtual public Animal {

};

// 驼，虚继承
class Camel : virtual public Animal {

};

// 羊驼
class CamelSheep : public Sheep, public Camel {

};

int main() {
    CamelSheep camelSheep;

    camelSheep.Sheep::m_Age = 10;
    camelSheep.Camel::m_Age = 20;

    // 使用虚继承后，不再存在二义性，因为数据只有一份
    cout << camelSheep.m_Age << endl;
    cout << camelSheep.Sheep::m_Age << endl;
    cout << camelSheep.Camel::m_Age << endl;

    return 0;
}
