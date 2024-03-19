/**
 * explicit 关键字的作用
 *
 * <p> 使用 explicit 关键字修饰函数后，可以防止隐式类型转换
 */

#include <iostream>

using namespace std;

class MyString {

public:
    MyString(char *str) {
        m_str = str;
    }

    explicit MyString(int size) {
        m_size = size;
    }

private:
    char *m_str;
    int m_size;
};

int main() {
    MyString str("abc");
    MyString str2 = "abc";

    MyString str3(10);
    // MyString str4 = 10;     // 默认情况下，这里会发生隐式类型转换，使用 explicit 关键字修饰函数后，可以禁止隐式类型转换

    return 0;
}
