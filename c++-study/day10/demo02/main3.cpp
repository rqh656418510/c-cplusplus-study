/*
 * 1. 异常处理机制
 * a) 设置默认的异常处理器
*/

#include <iostream>

using namespace std;

// 自定义 terminate() 函数
void myTerminate() {
    cout << "函数 myTerminate() 被 terminate() 调用!" << endl;
    exit(-1);
}

int divide(int x, int y) {
    return x / y;
}

int main() {
    // 设置默认的异常处理器
    set_terminate(myTerminate);

    int x = 10, y = 0, result;
    try {
        if (y == 0) {
            throw "被除数为零!";   //抛出异常，由 terminate() 函数捕获
        }
        else {
            result = x / y;
        }
    }
    // 不会被整型异常捕获
    catch (int e) {
        cout << "捕获到整型异常!" << endl;
    }

    cout << "程序正常结束运行!" << endl;
    return 0;
}