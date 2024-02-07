/*
 * 1. 函数对象（仿函数）简单使用的案例
*/

#include <iostream>

using namespace std;

// 函数对象
class MyPrint {

public:
    // 重载 () 操作符
    void operator()(const int &num) {
        cout << "num = " << num << endl;
    }

};

// 普通函数
void MyPrint2(int num) {
    cout << "num2 = " << num << endl;
}

// 函数对象作为参数
void doPrint(MyPrint print, int num) {
    print(num);
}

int main() {

    // 初始化函数对象（函数对象是一个类）
    MyPrint myPrint;

    // 函数对象调用
    myPrint(2);

    // 函数对象调用（使用匿名对象的写法）
    MyPrint()(3);

    // 普通函数调用
    MyPrint2(4);

    // 函数对象作为参数
    doPrint(myPrint, 5);

    return 0;
}
