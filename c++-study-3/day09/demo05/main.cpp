/**
 * 对象使用过程中背后调用了哪些方法
 */

#include <iostream>

using namespace std;

class Test {

public:
    Test(int a = 10) : _a(a) {
		cout << "Test(int)" << endl;
    }

    ~Test() {
        cout << "~Test()" << endl;
    }

    Test(const Test& t) : _a(t._a) {
        cout << "Test(const Test& t)" << endl;
	}

	Test& operator=(const Test& t) {
		cout << "operator=(const Test& t)" << endl;
        this->_a = t._a;
        return *this;
    }

    int getNum() {
		return this->_a;
    }

private:
    int _a;
};

void test01() {
    cout << "============ test01() ============" << endl;

    // 调用普通构造函数
    Test t1;

    // 调用拷贝构造函数
    Test t2(t1);

    // 调用拷贝构造函数
    Test t3 = t1;

    // 调用普通构造函数
    // 执行效果相当于 `Test t4(30);`
    // Test(30) 通常会显式生成临时对象，临时对象的生存周期是所在语句
    // 但是，如果用临时对象去拷贝构造新对象，那么临时对象就不会产生，也就是直接构造新对象就行，这是任意 C++ 编译器都会做的优化
    Test t4 = Test(30);

    cout << "--------- 1 ---------" << endl;

    // 调用赋值运算符重载函数
    t4 = t2;

    // 先调用普通构造函数，然后再调用赋值运算符重载函数
    // Test(20) 会显式生成临时对象，临时对象的生存周期是所在语句
    t4 = Test(20);

    cout << "--------- 2 ---------" << endl;

    // 先调用普通构造函数，然后再调用赋值运算符重载函数
    // (Test)20 会显式生成临时对象，临时对象的生存周期是所在语句
    // 执行效果相当于 `t4 = Test(20);`，这里要求 Test 类拥有 int 类型的构造函数
    t4 = (Test)20;

    cout << "--------- 3 ---------" << endl;

    // 先调用普通构造函数，然后再调用赋值运算符重载函数
    // 会隐式生成临时对象，临时对象的生存周期是所在语句
    // 执行效果相当于 `t4 = Test(20);`，这里要求 Test 类拥有 int 类型的构造函数
    t4 = 20;

    cout << "--------- 4 ---------" << endl;
}

void test02() {
    cout << "\n============ test02() ============" << endl;

    // 调用普通构造函数
    // (Test)20 会显式生成临时对象，临时对象的生存周期是所在语句
    // 当临时对象出了所在语句，会立刻被析构，同时指针 p 会成为野指针
    // 结论：使用指针变量指向临时对象是不安全的
    Test* p = &Test(20);

    // 调用普通构造函数
    // (Test)20 会显式生成临时对象，临时对象的生存周期是所在函数
    // 但是，这里的临时对象出了所在语句，不会立刻被析构，而是直到出了函数作用域才会被析构
    // 在函数作用域内，ref 引用会一直有效
    // 结论：使用引用变量指向临时对象是安全的
    Test& ref = Test(20);

    cout << "--------- 1 ---------" << endl;
}

int main() {
    test01();
    test02();
    return 0;
}