/**
 * 强化训练字符串封装
 */

#include <iostream>
#include "MyString.h"

using namespace std;

void test01() {
    cout << "----------- test01() -----------" << endl;
    MyString str1("C++");
    MyString str2 = str1;

    cout << str1 << endl;
    cout << str2 << endl;

    cout << "Please input a string :" << endl;
    cin >> str2;
    cout << str2 << endl;
}

void test02() {
    cout << "----------- test02() -----------" << endl;
    MyString str1("C");
    MyString str2("C++");
    cout << str1 << endl;
    cout << str2 << endl;

    str2 = str1;
    str1 = "Python";

    cout << str1 << endl;
    cout << str2 << endl;
}

void test03() {
    cout << "----------- test03() -----------" << endl;
    MyString str1("Go");
    cout << str1[0] << endl;

    str1[1] = 'a';
    cout << str1 << endl;
}

void test04() {
    cout << "----------- test04() -----------" << endl;
    MyString str1("Python");
    MyString str2 = str1 + ", C++";
    cout << str2 << endl;

    MyString str4(", Java");
    MyString str5 = str1 + str4;
    cout << str5 << endl;
}

void test05() {
    cout << "----------- test05() -----------" << endl;
    MyString str1("Python");
    MyString str2("C++");
    bool result1 = str1 == str2;
    bool result2 = str1 == "Python";
    cout << (result1 ? "true" : "false") << endl;
    cout << (result2 ? "true" : "false") << endl;
}

int main() {
    // test01();
    // test02();
    // test03();
    test04();
    // test05();
    return 0;
}
