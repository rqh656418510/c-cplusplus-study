/**
 * 1. const 关键字增强
 */

#include <iostream>

using namespace std;

// 全局的常量，受到保护，不允许更改值
const int m_A = 10;

void test01() {
    // 局部的常量，无法通过指针更改值
    const int m_B = 20;
    int *p = (int *) &m_B;
    *p = 30;
    cout << "*p = " << *p << endl;
    cout << "m_B = " << m_B << endl;
}

int main() {
    test01();
    return 0;
}