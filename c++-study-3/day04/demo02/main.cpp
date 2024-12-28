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
    MyString &operator=(const MyString &str) {
        // 防止自赋值
        if (this == &str) {
            return *this;
        }

        // 释放原来的内存空间
        delete[] _pstr;

        // 深拷贝
        _pstr = new char(strlen(str._pstr) + 1);
        strcpy(_pstr, str._pstr);

        return *this;
    }

    // 加法运算符重载
    friend MyString operator+(const MyString &str1, const MyString &str2);

    // 左移运算符重载
    friend ostream &operator<<(ostream &out, const MyString &str);

    // 大于运算符重载
    bool operator>(const MyString &str) const {
        return strcmp(_pstr, str._pstr) > 0;
    }

    // 小于运算符重载
    bool operator<(const MyString &str) const {
        return strcmp(_pstr, str._pstr) < 0;
    }

    // 双等号运算符重载
    bool operator==(const MyString &str) const {
        return strcmp(_pstr, str._pstr) == 0;
    }

    long length() const {
        return strlen(_pstr) - 1;
    }

private:
    char *_pstr;
};

MyString operator+(const MyString &str1, const MyString &str2) {
    char *_pnew = new char[strlen(str1._pstr) + strlen(str2._pstr) + 1];
    strcpy(_pnew, str1._pstr);
    strcat(_pnew, str2._pstr);
    return MyString(_pnew);
}

ostream &operator<<(ostream &out, const MyString &str) {
    out << str._pstr;
    return out;
}

int main() {
    // 调用构造函数
    MyString str1("abcde");
    cout << str1 << endl;

    MyString str2 = "fghij";
    cout << str2 << endl;

    // 调用拷贝构造函数
    MyString str3 = str2;
    cout << str3 << endl;

    // 赋值运算符重载
    str3 = str1;
    cout << str3 << endl;

    // 加法运算符重载
    MyString str4 = str1 + str2;
    cout << str4 << endl;

    // 大于运算符重载
    bool result1 = str1 > str2;
    cout << (result1 ? "true" : "false") << endl;

    // 小于运算符重载
    bool result2 = str1 < str2;
    cout << (result2 ? "true" : "false") << endl;

    // 双等号运算符重载
    str1 = str2;
    bool result3 = str1 == str2;
    cout << (result3 ? "true" : "false") << endl;

    cout << "length = " << str1.length() << endl;

    return 0;
}
