/**
 * 异常变量的生命周期
 */
#include <iostream>

using namespace std;

class MyException {

public:

    MyException() {
        cout << "调用构造函数" << endl;
    }

    MyException(const MyException &e) {
        cout << "调用拷贝构造函数" << endl;
    }

    ~MyException() {
        cout << "调用析构函数" << endl;
    }

};

void doWork() {
    throw MyException();    // 匿名对象的写法
}

int main() {
    try {
        doWork();
    }
    // 如果捕获异常的时候，使用了引用，则会使用 throw 时候的那个对象
    // 也就是说，捕获异常时使用引用，不会调用自定义异常类的拷贝构造函数，即会少一份数据开销
    catch (MyException &e) {
        cout << "捕获到自定义异常 ..." << endl;
    }
    catch (...) {
        cout << "捕获到未知异常 ..." << endl;
    }

    return 0;
}
