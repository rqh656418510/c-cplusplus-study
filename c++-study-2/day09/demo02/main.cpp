/*
 * 1. string容器的构造与赋值
*/

#include <iostream>

using namespace std;

int main() {
    // 默认构造函数
    string str1;

    // 拷贝构造函数
    string str2 = str1;

    // 有参构造函数
    string str3("abced");
    string str4(5, 'f');

    // 基本赋值
    str1 = "123456";
    str2 = str3;
    str3.assign("mnopq", 3);
    str4.assign("45678", 1, 3);     // 从0开始索引，1表示第2个字符
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    cout << "str3 = " << str3 << endl;
    cout << "str4 = " << str4 << endl;

    return 0;
}