/**
 * 全局函数做友元函数
 */

#include <iostream>

using namespace std;

class Building {

public:
    Building() {
        this->m_SittingRom = "客厅";
        this->m_BedRoom = "卧室";
    }

    // 声明友元函数
    friend void goodGay(Building *building);

public :
    string m_SittingRom;

private :
    string m_BedRoom;

};

// 定义普通函数（全局函数）
void goodGay(Building *building) {
    cout << "好朋友正在访问" << building->m_SittingRom << endl;

    // 通过友元函数，在类外可以访问类的私有成员
    cout << "好朋友正在访问" << building->m_BedRoom << endl;
}

int main() {
    Building *building = new Building();
    goodGay(building);
    return 0;
}
