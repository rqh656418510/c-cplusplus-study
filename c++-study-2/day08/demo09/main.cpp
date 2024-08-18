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
    throw MyException();
}

int main() {
    try {
        doWork();
    }

    /*
    // 会调用自定义异常类的拷贝构造函数，也就是会多一份数据开销
    catch (MyException e) {
        cout << "捕获到自定义异常" << endl;
    }

    // 捕获异常时使用引用，不会调用自定义异常类的拷贝构造函数
    catch (MyException &e) {
        cout << "捕获到自定义异常" << endl;
    }
    */

    // 推荐使用引用进行异常捕获
    catch (MyException &e) {
        cout << "捕获到自定义异常" << endl;
    }
    catch (...) {
        cout << "捕获到未知异常" << endl;
    }

    return 0;
}
