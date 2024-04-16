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

char &MyString::operator[](int index) {
    return this->pString[index];
}

MyString &MyString::operator=(const MyString &str) {
    // 释放原有的内存空间
    if (nullptr != this->pString) {
        delete[] this->pString;
        this->pString = nullptr;
        this->m_Size = 0;
    }

    // 重新分配内存空间
    int length = strlen(str.pString);
    this->pString = new char[length + 1];
    strcpy(this->pString, str.pString);
    this->m_Size = length;

    return *this;
}

MyString &MyString::operator=(const char *str) {
    // 释放原有的内存空间
    if (nullptr != this->pString) {
        delete[] this->pString;
        this->pString = nullptr;
        this->m_Size = 0;
    }

    // 重新分配内存空间
    int length = strlen(str);
    this->pString = new char[length + 1];
    strcpy(this->pString, str);
    this->m_Size = length;

    return *this;
}

MyString MyString::operator+(const MyString &str) {
    // 字符串拼接后的长度
    int newSize = this->m_Size + strlen(str.pString) + 1;

    // 分配临时内存空间
    char *tmp = new char[newSize];
    memset(tmp, 0, newSize);

    // 拼接字符串
    strcat(tmp, this->pString);
    strcat(tmp, str.pString);

    MyString newString(tmp);

    // 释放临时内存空间
    delete[]tmp;

    return newString;
}

MyString MyString::operator+(const char *str) {
    // 字符串拼接后的长度
    int newSize = this->m_Size + strlen(str) + 1;

    // 分配临时内存空间
    char *tmp = new char[newSize];
    memset(tmp, 0, newSize);

    // 拼接字符串
    strcat(tmp, this->pString);
    strcat(tmp, str);

    // 创建新的字符串
    MyString newString(tmp);

    // 释放临时内存空间
    delete[]tmp;

    return newString;
}

bool MyString::operator==(const MyString &str) {
    return strcmp(this->pString, str.pString) == 0 && this->m_Size == str.m_Size;
}

bool MyString::operator==(const char *str) {
    return strcmp(this->pString, str) == 0 && this->m_Size == strlen(str);
}
