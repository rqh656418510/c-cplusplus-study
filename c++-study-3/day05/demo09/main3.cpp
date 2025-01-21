/**
 * 继承多态笔试题实战分析
 *
 * <p> 高频面试题三
 */

#include <iostream>

using namespace std;

class Base {

public:
    // 虚函数
    virtual void show() {
        cout << "call Base::show()" << endl;
    }

};

class Device : public Base {

private:
    // 私有方法
    void show() {
        cout << "call Device::show()" << endl;
    }

};

int main() {
    Base *b = new Device();

    // 可以正常调用，发生动态（运行时期）绑定，输出：call Device::show()
    // 成员函数能不能被调用，就是说函数的访问权限是不是 public，这是在编译阶段就需要确定好的，而动态绑定是发生在运行时期
    b->show();
    delete b;

    return 0;
}
