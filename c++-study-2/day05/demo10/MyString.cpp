#include <iostream>
#include <cstring>
#include "MyString.h"

using namespace std;

MyString::MyString(const char *str) {
    cout << "有参构造函数" << endl;
    int length = strlen(str);
    this->pString = new char[length + 1];
    strcpy(this->pString, str);
    this->m_Size = length;
}

MyString::MyString(const MyString &str) {
    cout << "拷贝构造函数" << endl;
    int length = strlen(str.pString);
    this->pString = new char[length + 1];
    strcpy(this->pString, str.pString);
    this->m_Size = length;
}

MyString::~MyString() {
    cout << "析构函数" << endl;
    if (nullptr != this->pString) {
        delete[] this->pString;
        this->pString = nullptr;
        this->m_Size = 0;
    }
}

ostream &operator<<(ostream &out, const MyString &str) {
    out << str.pString;
    return out;
}

istream &operator>>(istream &in, MyString &str) {
    // 释放原有的内存空间
    if (nullptr != str.pString) {
        delete[] str.pString;
        str.pString = nullptr;
        str.m_Size = 0;
    }

    // 从标准输入流中读取字符串，并存储到字符数组中
    const int maxLength = 1024;
    char buffer[maxLength];
    cin.getline(buffer, maxLength);

    // 重新分配内存空间
    int length = strlen(buffer);
    str.pString = new char[length + 1];
    strcpy(str.pString, buffer);
    str.m_Size = length;

    return in;
}
