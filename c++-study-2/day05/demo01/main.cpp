/**
 * 数组类的封装
 */
#include <iostream>
#include "MyArray.h"

using namespace std;

void test01() {
    MyArray *myArray1 = new MyArray(20);

    // 第一种写法，会自动调用拷贝构造函数
    // MyArray myArray2 = *myArray1;

    // 第二种写法，会自动调用拷贝构造函数
    MyArray *myArray2 = new MyArray(*myArray1);

    // 尾插数据
    for (int i = 0; i < 10; i++) {
        myArray2->push_back(i);
    }

    // 设置数据
    myArray2->set_data(3, 42);

    // 获取数据
    for (int i = 0; i < 10; i++) {
        cout << myArray2->get_data(i) << endl;
    }

    delete myArray2;
    delete myArray1;
}

int main() {
    test01();
    return 0;
}