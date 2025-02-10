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

    // 迭代器
    class iterator {
    public:
        iterator(char *p = nullptr) : _p(p) {

        }

        // 重载不等于运算符
        bool operator!=(const iterator &other) const {
            return _p != other._p;
        }

        // 重载前置 ++ 运算符
        iterator &operator++() {
            _p++;
            return *this;
        }

        // 重载后置 ++ 运算符
        iterator operator++(int) {
            return iterator(_p++);
        }

        // 解引用运算符重载
        char &operator*() const {
            return *_p;
        }

    private:
        char *_p;
    };

    // 返回的是容器底层首元素的迭代器的表示
    iterator begin() {
        return iterator(_pstr);
    }

    // 返回的是容器末尾元素后继位置的迭代器的表示
    iterator end() {
        return iterator(_pstr + length());
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
    MyString str1 = "Hello World";
    // 使用迭代器遍历字符串
    for (MyString::iterator it = str1.begin(); it != str1.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
}

void test02() {
    MyString str2 = "Golang";
    // 使用 For 循环遍历字符串，会自动调用字符串类的 begin() 和 end() 函数
    for (char ch: str2) {
        cout << ch << " ";
    }
    cout << endl;
}

int main() {
    test01();
    test02();
    return 0;
}
