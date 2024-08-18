/**
 * 异常的接口声明
 */
#include <iostream>

using namespace std;

class A {

};

class B {

};

class C {

};

class D {

};

// 能够且只能抛出类型 A、B、C、D 及其子类型的异常
void func1() throw(A, B, C, D) {
    throw A();
}

// 不能抛出任何类型的异常
void func2() throw() {

}

// 可以抛出任何类型的异常
void func3() {
    throw B();
}

int main() {
    try {
        func1();
    }
    catch (A a) {
        cout << "发生 A 异常" << endl;
    }
    catch (...) {
        cout << "发生未知其他异常 ..." << endl;
    }
    return 0;
}
