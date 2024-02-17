/**
 * 1. 双冒号作用域限定运算符
 *
 * <p> 用于对当前作用域之外的同名变量进行访问
 */

#include <iostream>

using namespace std;

int atk = 200;

int main() {

    int atk = 100;

    cout << "atk = " << atk << endl;

    // 双冒号作用域限定运算符，表示全局作用域
    cout << "atk = " << ::atk << endl;
}
