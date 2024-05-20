/**
 * 向上类型转换和向下类型转换
 */

#include <iostream>

using namespace std;

class Base {

public:
    virtual void foo() {

    }

};

class Derived : public Base {

};

void test01() {
    Derived derived;
    Base *basePtr = &derived;   // 向上类型转换，派生类转换为基类（安全）
}

void test02() {
    Base baseObj;
    Base *basePtr = &baseObj;

    // 向下类型转换，基类转换为派生类（不安全）
    Derived *derivedPtr = dynamic_cast<Derived *>(basePtr);
    if (derivedPtr) {
        // 转换成功
    } else {
        // 转换失败
    }
}

int main() {
    test01();
    test02();
}
