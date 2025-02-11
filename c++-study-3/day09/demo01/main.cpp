/**
 * MyString的代码问题
 */

#include <iostream>
#include <cstring>

using namespace std;

class MyString {

public:
    // 构造函数
    MyString(const char* p = nullptr) {
        cout << "MyString(const char *p = nullptr)" << endl;
        if (p != nullptr) {
            _pstr = new char[strlen(p) + 1];
            strcpy(_pstr, p);
        }
        else {
            _pstr = new char[1];
            *_pstr = '\0';
        }
    }

    // 析构函数
    ~MyString() {
        cout << "~MyString()" << endl;
        delete[] _pstr;
        _pstr = nullptr;
    }

    // 带左值引用参数的拷贝构造函数
    MyString(const MyString& str) {
        cout << "MyString(const MyString &str)" << endl;
        // 深拷贝
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }

    // 带右值引用参数的拷贝构造函数
    MyString(MyString&& str) {
        cout << "MyString(MyString&& str)" << endl;
        // 浅拷贝临时对象（可以提高代码执行效率，减少内存的拷贝次数）
        _pstr = str._pstr;
        str._pstr = nullptr;
    }

    // 带左值引用参数的赋值运算符重载
    MyString& operator=(const MyString& str) {
        cout << "operator=(const MyString &str)" << endl;
        // 防止自赋值
        if (this == &str) {
            return *this;
        }

        // 释放原来的内存空间
        delete[] _pstr;

        // 深拷贝
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);

        return *this;
    }

    // 带右值引用参数的赋值运算符重载
    MyString& operator=(MyString&& str) {
        cout << "operator=(MyString&& str)" << endl;
        // 防止自赋值
        if (this == &str) {
            return *this;
        }

        // 释放原来的内存空间
        delete[] _pstr;

        // 浅拷贝临时对象（可以提高代码执行效率，减少内存的拷贝次数）
        _pstr = str._pstr;
        str._pstr = nullptr;

        return *this;
    }


    // 加法运算符重载
    friend MyString operator+(const MyString& str1, const MyString& str2);

    // 左移运算符重载
    friend ostream& operator<<(ostream& out, const MyString& str);

    // 返回字符串自身
    const char* c_str() const {
        return _pstr;
    }

private:
    char* _pstr;
};

MyString operator+(const MyString& str1, const MyString& str2) {
    MyString tmpStr;
    tmpStr._pstr = new char[strlen(str1._pstr) + strlen(str2._pstr) + 1];
    strcpy(tmpStr._pstr, str1._pstr);
    strcat(tmpStr._pstr, str2._pstr);
    return tmpStr;
}

ostream& operator<<(ostream& out, const MyString& str) {
    out << str._pstr;
    return out;
}

MyString getString(MyString& str) {
    const char* pstr = str.c_str();
    MyString tmpStr(pstr);
    return tmpStr;
}

int main() {
    MyString str1("aaaaaaa");
    MyString str2;
    str2 = getString(str1);
    cout << str2.c_str() << endl;
	return 0;
}
