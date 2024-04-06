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
    // 类 GoodGay 是类 Building 的友元类，因此 GoodGay 类的所有成员函数都可以直接访问 Building 类的私有成员或者保护成员
    cout << "Good friend visiting " << this->building->m_BedRoom << endl;
}

int main() {
    GoodGay goodGay;
    goodGay.visit();
    return 0;
}
