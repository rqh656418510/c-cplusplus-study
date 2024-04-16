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

    // 成员函数实现 [] 运算符重载
    char &operator[](int index);

    // 成员函数实现 = 赋值运算符重载
    MyString &operator=(const MyString &str);

    // 成员函数实现 = 赋值运算符重载
    MyString &operator=(const char *str);

    // 成员函数实现 + 运算符重载
    MyString operator+(const MyString &str);

    // 成员函数实现 + 运算符重载
    MyString operator+(const char *str);

    // 成员函数实现 == 运算符重载
    bool operator==(const MyString &str);

    // 成员函数实现 == 运算符重载
    bool operator==(const char *str);

private:
    char *pString;
    int m_Size;

};
