/**
 * 继承多态笔试题实战分析
 *
 * <p> 高频面试题二
 */

#include <iostream>

using namespace std;

class Base {

public:
    // 虚函数
    virtual void show(int i = 10) {
        cout << "call Base::show i : " << i << endl;
    }

};

class Device : public Base {

public:
    void show(int i = 20) {
        cout << "call Device::show i : " << i << endl;
    }
};

int main() {
    Base *b = new Device();

    // 函数调用，参数压栈是在编译时期决定的，因此这里参数压栈时使用的是基类中虚函数的默认参数值
    // 动态绑定，p -> Device vfptr -> Device vftable -> Device::show()，输出： call Device::show i : 10
    b->show();
    delete b;

    return 0;
}
