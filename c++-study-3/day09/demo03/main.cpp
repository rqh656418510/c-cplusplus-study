/**
 * CMyString在vector上的应用
 */

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class MyString {

public:
    // 构造函数
    MyString(const char *p = nullptr) {
        cout << "MyString(const char *p = nullptr)" << endl;
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
        cout << "~MyString()" << endl;
        delete[] _pstr;
        _pstr = nullptr;
    }

    // 带左值引用参数的拷贝构造函数
    MyString(const MyString &str) {
        cout << "MyString(const MyString &str)" << endl;
        // 深拷贝
        _pstr = new char[strlen(str._pstr) + 1];
        strcpy(_pstr, str._pstr);
    }

    // 带右值引用参数的拷贝构造函数
    MyString(MyString &&str) {
        cout << "MyString(MyString &&str)" << endl;
        _pstr = str._pstr;
        str._pstr = nullptr;
    }

    // 带左值引用参数的赋值运算符重载
    MyString &operator=(const MyString &str) {
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
    MyString tmpStr;
    tmpStr._pstr = new char[strlen(str1._pstr) + strlen(str2._pstr) + 1];
    strcpy(tmpStr._pstr, str1._pstr);
    strcat(tmpStr._pstr, str2._pstr);
    return tmpStr;
}

ostream &operator<<(ostream &out, const MyString &str) {
    out << str._pstr;
    return out;
}

void test01() {
    cout << "\n============ test01() ============" << endl;

    MyString str1 = "aaa";
    vector<MyString> v1;

    cout << "----------------------------------" << endl;
    v1.push_back(str1);
    cout << "----------------------------------" << endl;
}

void test02() {
    cout << "\n============ test02() ============" << endl;

    MyString str1 = "aaa";
    vector<MyString> v1;
    cout << "----------------------------------" << endl;
    v1.push_back(MyString("bbb"));
    cout << "----------------------------------" << endl;
}

int main() {
    test01();
    test02();
    return 0;
}