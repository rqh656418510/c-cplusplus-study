/**
 * new、delete的进一步认识
 */

#include <iostream>

class MyTest {

public:
    MyTest() {

    }

private:
    int m_i;
};

int main() {
    // 加括号 ()，成员变量 m_i 的值为随机数
    MyTest* mt = new MyTest();
    // 不加括号 ()，成员变量 m_i 的值为随机数
    MyTest* mt2 = new MyTest;
    return 0;
}