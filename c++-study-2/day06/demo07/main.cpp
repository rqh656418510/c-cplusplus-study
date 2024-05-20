/**
 * 向上类型转换和向下类型转换
 *
 * 向上类型转换:
 *      向上类型转换是指将派生类对象指针或引用转换为基类对象指针或引用的过程。
 *      在继承关系中，派生类对象可以被看作是基类对象的一种，因此可以将派生类对象的指针或引用隐式地转换为基类类型。
 *      这种类型转换是安全的，因为派生类对象包含了基类的所有成员，但是基类不能访问派生类特有的成员。
 *
 *  向下类型转换:
 *      向下类型转换是指将基类对象的指针或引用转换为派生类类型的指针或引用。
 *      这种类型转换是不安全的，因为基类对象可能没有派生类特有的成员，而尝试访问这些特有成员可能导致未定义的行为。
 *      在进行向下类型转换时，可以使用 dynamic_cast 来进行类型转换，这样可以检查类型转换的有效性。
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
