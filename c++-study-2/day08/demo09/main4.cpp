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
    throw new MyException();
}

int main() {
    try {
        doWork();
    }
    // 接收异常的时候，指针可以和引用/元素同时出现，但是引用与元素不能同时出现
    catch (MyException *e) {

        // 自定义异常类的指针 e 可以继续使用，因为自定义异常类的析构函数还没有被调用
        e->printError();

        // 需要手动调用自定义异常类的析构函数来释放内存
        delete e;

        cout << "捕获到自定义异常" << endl;
    }
    catch (...) {
        cout << "捕获到未知异常" << endl;
    }

    return 0;
}
