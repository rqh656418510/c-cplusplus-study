/**
 * 类和对象代码应用实践
 */

#include <iostream>
#include <cstring>

using namespace std;

class MyString {

public:
    // 普通构造函数
    MyString(const char *str = nullptr) {
        if (str != nullptr) {
            m_data = new char[strlen(str) + 1];
            strcpy(m_data, str);
        } else {
            m_data = new char[1];
            *m_data = '\0';
        }
    }

    // 拷贝构造函数
    MyString(const MyString &other) {
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
    }

    // 析构函数
    ~MyString() {
        if (m_data != nullptr) {
            delete[] m_data;
            m_data = nullptr;
        }
    }

    // 赋值运算符重载
    MyString &operator=(const MyString &other) {
        if (this == &other) {
            return *this;
        }
        if (m_data != nullptr) {
            delete[]m_data;
        }
        m_data = new char[strlen(other.m_data) + 1];
        strcpy(m_data, other.m_data);
        return *this;
    }

private :
    char *m_data;
};

int main() {
    // 调用普通构造函数
    MyString str1;
    MyString str2("abc");
    MyString str3 = "efg";

    // 拷贝构造函数
    MyString str4 = str3;
    MyString str5(str3);

    // 赋值运算符重载
    str1 = str2;
}