/**
 * 整个类做友元类
 */
#include <iostream>

using namespace std;

class Building {

    // 声明友元类
    friend class GoodGay;

public:
    Building();

public:
    string m_SittingRoom;

private:
    string m_BedRoom;
};

Building::Building() {
    this->m_SittingRoom = "sitting room";
    this->m_BedRoom = "bed room";
}

class GoodGay {

public:
    GoodGay();

    void visit();

private :
    Building *building;

};

GoodGay::GoodGay() {
    this->building = new Building();
}

void GoodGay::visit() {
    cout << "Good friend visiting " << this->building->m_SittingRoom << endl;
    // 友元类可以直接访问另一个类的私有成员变量
    cout << "Good friend visiting " << this->building->m_BedRoom << endl;
}

void test01() {
    GoodGay goodGay;
    goodGay.visit();
}

int main() {
    test01();
    return 0;
}
