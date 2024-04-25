/**
 * 虚基类的内部工作原理解析
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

    cout << "----------虚基类的内部工作原理分析，以下代码需要在 Visual Studio 中运行才会得到正确的结果-----------" << endl;

    // 获取 Sheep 的内存偏移量
    cout << *(int *) ((int *) *(int *) &camelSheep + 1) << endl;

    // 获取 Camel 的内存偏移量
    cout << *((int *) ((int *) *((int *) &camelSheep + 1) + 1)) << endl;

    // 通过 Sheep 的内存偏移量得到 Age
    cout << ((Animal *) ((char *) &camelSheep + *(int *) ((int *) *(int *) &camelSheep + 1)))->m_Age << endl;

    return 0;
}
