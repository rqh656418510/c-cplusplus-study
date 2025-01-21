/**
 * 继承多态笔试题实战分析
 *
 * <p> 高频面试题四
 */

#include <iostream>
#include <cstring>

using namespace std;

class Base {

public:
    Base() {
        cout << "call Base()" << endl;
        clear();
    }

    virtual void show() {
        cout << "call Base::show()" << endl;
    }

    void clear() {
        // 将当前对象的内存区域全部置为 0
        // 相当于当前对象的内存不再有 vfptr 虚函数指针
        memset(this, 0, sizeof(*this));
    }

};

class Device : public Base {

public:
    Device() {
        cout << "call Device()" << endl;
    }

    void show() {
        cout << "call Device::show()" << endl;
    }

};

int main() {
    Base *bptr1 = new Base();
    bptr1->show();  // 动态绑定，异常终止执行
    delete bptr1;

    Base *bptr2 = new Device();
    bptr2->show();  // 动态绑定，正常执行结束
    delete bptr2;

    return 0;
}