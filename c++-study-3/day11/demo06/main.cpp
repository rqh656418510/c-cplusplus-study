/**
 * Lambda表达式的实现原理
 */

#include <iostream>

using namespace std;

template<typename T=void>
class MyLambda1 {

public:
    MyLambda1() {

    }

    T operator()() {
        cout << "Hello World" << endl;
    }

};

void test01() {
    auto func1 = []() -> void { cout << "Hello World" << endl; };
    func1();

    // 上面的 Lambda 表达式等价于以下代码
    MyLambda1<> t1;
    t1();
}

template<typename T>
class MyLambda2 {

public:
    MyLambda2() {

    }

    T operator()(int a, int b) const {
        return a + b;
    }

};

void test02() {
    auto fun2 = [](int a, int b) -> int { return a + b; };
    cout << fun2(3, 5) << endl;

    // 上面的 Lambda 表达式等价于以下代码
    MyLambda2<int> t2;
    cout << t2(3, 5) << endl;
}

template<typename T=void>
class MyLambda3 {

public:
    MyLambda3(int a, int b) : _a(a), _b(b) {

    }

    T operator()() const {
        // 交换两个变量的值
        int temp = _a;
        _a = _b;
        _b = temp;
    }

private:
    mutable int _a;
    mutable int _b;

};

void test03() {
    int a = 10;
    int b = 30;

    // 按值传递，并没有真正交换两个变量的值
    auto func3 = [a, b]() mutable -> int {
        int temp = a;
        a = b;
        b = temp;
    };
    func3();
    cout << "a = " << a << ", b = " << b << endl;

    // 上面的 Lambda 表达式等价于以下代码
    MyLambda3<int> t3(a, b);    // 按值传递，并没有真正交换两个变量的值
    t3();
    cout << "a = " << a << ", b = " << b << endl;
}

template<typename T=void>
class MyLambda4 {

public:
    MyLambda4(int &a, int &b) : _a(a), _b(b) {

    }

    T operator()() const {
        // 交换两个变量的值
        int temp = _a;
        _a = _b;
        _b = temp;
    }

private:
    int &_a;
    int &_b;

};

void test04() {
    int a = 10;
    int b = 30;

    // 按引用传递，可以真正交换两个变量的值
    auto func4 = [&a, &b]() mutable -> int {
        int temp = a;
        a = b;
        b = temp;
    };
    func4();
    cout << "a = " << a << ", b = " << b << endl;

    // 上面的 Lambda 表达式等价于以下代码
    MyLambda4<int> t4(a, b);    // 按引用传递，可以真正交换两个变量的值
    t4();
    cout << "a = " << a << ", b = " << b << endl;
}

int main() {
    test01();
    cout << "----------------" << endl;
    test02();
    cout << "----------------" << endl;
    test03();
    cout << "----------------" << endl;
    test04();
    cout << "----------------" << endl;
    return 0;
}
