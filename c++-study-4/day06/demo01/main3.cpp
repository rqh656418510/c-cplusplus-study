/**
 * new、delete的进一步认识
 *
 * (c) 如果类中有成员变量，且有自定义的空构造函数，两种写法没有任何区别
 */

#include <iostream>

class MyTest {
public:
    // 空构造函数
    MyTest() {
    }

private:
    int m_i;  // 成员变量
};

int main() {
    // 加括号 ()，成员变量 m_i 的值为随机数
    MyTest* mt = new MyTest();
    // 不加括号 ()，成员变量 m_i 的值为随机数
    MyTest* mt2 = new MyTest;
    return 0;
}