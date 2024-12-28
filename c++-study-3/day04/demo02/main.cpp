/**
 * 模拟实现C++的string类代码
 */
#include <iostream>
#include <cstring>

using namespace std;

class MyString {

public:
    // 构造函数
    MyString(const char *p = nullptr) {
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        } else {
            _pstr = new char[1];
            *_pstr = '\0';
        }
    }

    // 析构函数
    ~MyString() {
        delete[] _pstr;
        _pstr = nullptr;
    }

    // 拷贝构造函数
    MyString(const MyString &str) {
        // 深拷贝
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }

    // 赋值运算符重载
    MyString& operator=(const MyString &str) {
        if (this == &str) {
            return *this;
        }

        // 释放原来的内存空间
        delete [] _pstr;

        // 深拷贝
        _pstr = new char(strlen(str._pstr) + 1);
        strcpy(_pstr, str._pstr);

        return *this;
    }

private:
    char *_pstr;
};

int main() {
    return 0;
}