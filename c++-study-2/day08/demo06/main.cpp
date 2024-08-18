/**
 * 对自定义异常进行捕获
 */
#include <iostream>

using namespace std;

// 自定义异常类
class MyException {

public:
    MyException(string message) {
        this->message = message;
    }

    void printError() {
        cout << "Exception: " << this->message << endl;
    }

private:
    string message;

};

int devide(int a, int b) {
    if (b == 0) {
        // 抛出自定义异常
        throw MyException("被除数不能为零");   // 匿名对象的写法
    }
    return a / b;
}


int main() {
    try {
        int result = devide(9, 0);
        cout << "result = " << result << endl;
    } catch (MyException e) {
        e.printError();
    }

    cout << "程序正常结束运行" << endl;
    return 0;
}
