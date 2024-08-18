/**
 * 栈解旋
 */
#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        cout << "调用构造函数" << endl;
    }

    ~Person() {
        cout << "调用析构函数" << endl;
    }
};

int devide(int a, int b) {
    // 在栈上创建对象
    Person person;

    if (b == 0) {
        throw -1;
    }
    return a / b;
}

int main() {
    // 异常被抛出后，从进入 try 代码块起，到异常被抛掷前，这期间在栈上构造的所有对象，都会被自动析构，析构的顺序与构造的顺序相反
    try {
        int result = devide(9, 0);
        cout << "result = " << result << endl;
    } catch (int) {
        cout << "被除数不能为零" << endl;
    }

    cout << "程序正常结束运行" << endl;
    return 0;
}
