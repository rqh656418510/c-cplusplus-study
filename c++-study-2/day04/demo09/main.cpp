/**
 * 全局函数作为友元函数
 */

#include <iostream>

using namespace std;

class Building {

public:
    Building() {
        this->m_SittingRom = "sitting rom";
        this->m_BedRoom = "bed room";
    }

    // 声明友元函数
    friend void visit(Building *building);

public :
    string m_SittingRom;

private :
    string m_BedRoom;

};

// 定义普通函数（全局函数）
void play(Building *building) {
    cout << "好朋友正在访问" << building->m_SittingRom << endl;

    // 错误写法，在普通函数（全局函数）内，类的私有成员不能在类外被访问
    // cout << "好朋友正在访问" << building->m_BedRoom << endl;
}

// 定义友元函数（全局函数）
void visit(Building *building) {
    cout << "Good friend visiting " << building->m_SittingRom << endl;

    // 通过友元函数，在类外可以访问类的私有成员
    cout << "Good friend visiting " << building->m_BedRoom << endl;
}

int main() {
    Building *building = new Building();
    // 调用友元函数
    visit(building);
    return 0;
}
