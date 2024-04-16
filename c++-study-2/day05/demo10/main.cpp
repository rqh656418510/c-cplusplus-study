/**
 * 强化训练字符串封装
 */
#include <iostream>
#include "MyString.h"

using namespace std;

void test01() {
    MyString str1("Hello");
    MyString str2 = str1;

    cout << str1 << endl;
    cout << str2 << endl;

    cout << "Please input a string :" << endl;
    cin >> str2;
    cout << str2 << endl;
}

int main() {
    test01();
    return 0;
}