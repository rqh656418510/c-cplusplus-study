/**
 * C++的四种类型转换
 */

#include <iostream>

using namespace std;

// 抽象类
class Base {

public:
    // 纯虚函数
    virtual void show() = 0;
};

class Device1 : public Base {

public:
    void show() {
        cout << "call Device1::show()" << endl;
    }

};

class Device2 : public Base {

public:
    void show() {
        cout << "call Device2::show()" << endl;
    }

    void print() {
        cout << "call Device2::print()" << endl;
    }

};

void show(Base *base) {
    // 判断 base 指针指向的是不是 Device2 对象
    // 如果是，则 dynamic_cast 转换成功，并返回 Device2 对象的地址，否则返回 nullptr
    Device2 *pDevice2 = dynamic_cast<Device2 *>(base);
    if (pDevice2 == nullptr) {
        base->show();
    } else {
        pDevice2->print();
    }
}

int main() {

    // const_cast：去掉常量属性的类型转换
    const int a = 10;
    int *p1 = const_cast<int * > (&a);
    cout << *p1 << endl;

    // static_cast：提供编译器认为安全的类型转换
    int b = 65;
    char c = static_cast<char>(b);
    cout << c << endl;

    // reinterpret_cast：类似于 C 语言风格的类型转换
    int d = 20;
    int *p2 = reinterpret_cast<int *> (d);

    // dynamic_cast：主要用在类的继承结构中，可以支持 RTTI 类型识别的上下类型转换
    Device1 device1;
    Device2 device2;
    show(&device1);
    show(&device2);

    return 0;
}
