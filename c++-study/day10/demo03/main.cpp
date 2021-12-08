/*
 * 1. 异常处理机制
 * a) 异常在继承中的使用
*/

#include "MyArray.h"

int main() {
    try {
        // 调用构造函数
        MyArray array1(-6);
        // MyArray array1(5);
        // MyArray array1(0);
        // MyArray array1(2000);

        // 重载运算符 "[]"
        for (int i = 0; i < array1.getsize(); i++) {
            array1[i] = 20 + i;
        }

        // 重载运算符 "<<"
        cout << array1 << endl;

        // 调用拷贝构造函数
        MyArray array2 = array1;
        cout << array2 << endl;

        MyArray array3(3);
        array3[0] = 43;
        array3[1] = 56;
        array3[2] = 79;
        cout << array3 << endl;

        // 重载运算符 "="
        array3 = array2;
        cout << array3 << endl;

    }
    // 使用引用捕获异常（多态）
    catch (SizeException& e) {
        e.printErr();
    }
    catch (...) {
        cout << "发生未知异常" << endl;
    }
    return 0;
}