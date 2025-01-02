/**
 * string字符串对象的迭代器iterator实现
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

    // 中括号运算符重载（读写）
    char &operator[](int index) {
        return _pstr[index];
    }

    // 中括号运算符重载（只读）
    const char &operator[](int index) const {
        return _pstr[index];
    }

    // 返回字符串自身
    const char *c_str() const {
        return _pstr;
    }

    // 获取字符串长度
    long length() const {
        long length = strlen(_pstr);

        // 空字符串
        if (0 == length) {
            return 0;
        }

        // 以 '\0' 结尾的字符串
        if (_pstr[length] == '\0') {
            return length;
        }

        // 不以 '\0' 结尾的字符串
        return length + 1;
    }

private:
    char *_pstr;
};

MyString operator+(const MyString &str1, const MyString &str2) {
    char *_pnew = new char[strlen(str1._pstr) + strlen(str2._pstr) + 1];
    strcpy(_pnew, str1._pstr);
    strcat(_pnew, str2._pstr);
    MyString newstr(_pnew);
    delete[] _pnew;
    return newstr;
}

ostream &operator<<(ostream &out, const MyString &str) {
    out << str._pstr;
    return out;
}

int main() {
    // 调用构造函数
    MyString str1("abcde");
    cout << str1 << endl;

    // 调用构造函数
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

    // 中括号运算符重载
    MyString str5("hello");
    str5[4] = 'k';
    cout << "str5[3] = " << str5[4] << endl;

    // 获取字符串长度
    MyString str6("world");
    cout << "str6.length = " << str6.length() << endl;

    // 返回字符串自身
    const char *tmpstr = str6.c_str();
    cout << tmpstr << endl;

    return 0;
}
