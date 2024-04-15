/**
 * 函数运算符重载
 */
#include <iostream>

using namespace std;

class MyPrint {

public:
    // 函数调用运算符的重载
    void operator()(const string &content) {
        cout << content << endl;
    }

};

void test01() {
    MyPrint myPrint;
    myPrint("Hello World");
}

class MyAdd {

public:
    // 函数调用运算符的重载
    int operator()(const int a, const int b) {
        return a + b;
    }

};

void test02() {
    MyAdd add;

    int sum = add(1, 2);
    cout << sum << endl;

    // 匿名对象
    cout << MyAdd()(3, 4) << endl;
}

int main() {
    test01();
    test02();
    return 0;
}