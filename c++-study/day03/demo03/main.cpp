/**
 * 1. 浅拷贝与深拷贝
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

int main() {
    return 0;
}