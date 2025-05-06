/**
 * C++11容器emplace方法原理剖析一
 */

#include <iostream>
#include <vector>

using namespace std;

class Test {

public:

    Test(int a) {
        cout << "Test(int)" << endl;
    }

    Test(int a, int b) {
        cout << "Test(int, int)" << endl;
    }

    // 析构函数
    ~Test() {
        cout << "~Test()" << endl;
    }

    // 带左值引用的拷贝构造函数
    Test(const Test &) {
        cout << "Test(const Test &)" << endl;
    }

    // 带右值引用的拷贝构造函数
    Test(Test &&) {
        cout << "Test(Test &&)" << endl;
    }

};

void test01() {
    cout << "============ test01 ===========" << endl;

    Test t1(10);
    vector<Test> v1;
    v1.reserve(100);

    // 如果直接插入普通对象，两者没有任何区别
    v1.push_back(t1);
    v1.emplace_back(t1);
}

void test02() {
    cout << "============ test02 ===========" << endl;

    vector<Test> v1;
    v1.reserve(100);

    // 如果直接插入临时对象，两者没有任何区别
    v1.push_back(Test(20));
    v1.emplace_back(Test(20));
}

void test03() {
    cout << "============ test03 ===========" << endl;

    vector<Test> v1;
    v1.reserve(100);

    // 给emplace_back()传入Test对象构造所需要的参数，会直接在容器底层调用对象的构造函数，即不会产生临时对象
    v1.emplace_back(30);
    v1.emplace_back(40, 50);
}

int main() {
    test01();
    test02();
    test03();
    return 0;
}
