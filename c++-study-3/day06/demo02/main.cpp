/**
 * 菱形继承的问题
 */

#include <iostream>

using namespace std;

class A {

public:
    A(int data) : ma(data) {
        cout << "A()" << endl;
    }

    ~A() {
        cout << "~A()" << endl;
    }

public:
    int ma;

};

class B : virtual public A {

public:
    B(int data) : A(data), mb(data) {
        cout << "B()" << endl;
    }

    ~B() {
        cout << "~B()" << endl;
    }

public:
    int mb;

};

class C : virtual public A {

public:
    C(int data) : A(data), mc(data) {
        cout << "C()" << endl;
    }

    ~C() {
        cout << "~C()" << endl;
    }

public:
    int mc;

};

class D : public B, public C {

public:
    D(int data) : A(data), B(data), C(data), md(data) {
        cout << "D()" << endl;
    }

    ~D() {
        cout << "~D()" << endl;
    }

public:
    int md;

};

int main() {
    D d(20);
    cout << d.ma << endl;        // 正确写法，不存在二义性
    return 0;
}
