/**
 * 1. 拷贝构造函数的第一种调用场景
 */

#include <iostream>

using namespace std;

class Test {

private :
    int _a;

public:
    Test() {
        cout << "无参构造函数自动被调用了" << endl;
    }

    Test(int a) {
        _a = a;
        cout << "有参构造函数被调用了" << endl;
    }

    Test(const Test &obj) {
        _a = obj._a + 10;
        cout << "拷贝构造函数被调用了" << endl;
    }

    ~Test() {
        cout << "析构函数被调用了" << endl;
    }

    int getA() {
        return _a;
    }
};

void functionA() {
    Test t1(1);
    Test t0(2);
    t0 = t1;            // 普通的赋值操作，拷贝构造函数不会被调用
    Test t2 = t1;       // 类的初始化操作(等号法)，拷贝构造函数会被调用
    cout << "a = " << t2.getA() << endl;
}

int main() {
    functionA();
    return 0;
}