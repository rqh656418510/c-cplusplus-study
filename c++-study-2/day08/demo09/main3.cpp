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

    void printError() {
        cout << "Exception Message: null" << endl;
    }

};

void doWork() {
    MyException exception;   // 在栈内存上创建一个对象
    throw &exception;   // 抛出一个内存地址，不建议使用这种写法，相当于 throw &(MyException());
}

int main() {
    try {
        doWork();
    }
    // 在接收异常的时候，使用了指针
    catch (MyException *e) {

        // 执行到这里的时候，自定义异常类的析构函数已经被调用，即指针 e 已经被释放了（变成了野指针），不能再继续使用
        // e->printError();

        cout << "捕获到自定义异常 ..." << endl;
    }
    catch (...) {
        cout << "捕获到未知异常 ..." << endl;
    }

    return 0;
}
