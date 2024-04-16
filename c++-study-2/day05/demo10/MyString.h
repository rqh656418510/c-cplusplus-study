#pragma once

#include <iostream>

using namespace std;

class MyString {

public:
    explicit MyString(const char *str);

    MyString(const MyString &str);

    ~MyString();

    // 声明友元函数实现 << 左移运算符的重载
    friend ostream &operator<<(ostream &out, const MyString &str);

    // 声明友元函数实现 >> 右移运算符的重载
    friend istream &operator>>(istream &in, MyString &str);

private:
    char *pString;
    int m_Size;

};
