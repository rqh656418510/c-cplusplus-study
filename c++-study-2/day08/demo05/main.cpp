/**
 * 异常的基本使用
 */
#include <iostream>

using namespace std;

int devide(int a, int b) {
    if (b == 0) {
        // 抛出 int 类型异常
        throw -1;

        // 抛出 double 类型异常
        // throw 3.14;

        // 抛出其他异常
        // throw 'a';
    }
    return a / b;
}

int main() {
    try {
        int a = 10;
        int b = 0;
        int c = devide(a, b);
        cout << "result: " << c << endl;
    }
    // 捕获 int 类型异常
    catch (int) {
        cout << "int 类型异常捕获，被除数不能为零" << endl;
    }
    // 捕获 double 类型异常
    catch (double) {
        cout << "double 类型异常捕获，被除数不能为零" << endl;
    }
    // 捕获其他异常
    catch (...) {
        // 抛出异常
        throw "发生未知的异常 ...";
    }

    cout << "程序正常结束运行" << endl;
    return 0;
}
