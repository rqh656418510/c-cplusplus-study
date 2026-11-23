/**
 * 拷贝构造函数语义续
 */

#include <iostream>

class MATX {
public:
    int m_a;
};

class MBTX {
public:
    void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_b = 0;  // 基本类型成员变量
    MATX m_matx;  // 类类型成员变量
};

int main() {
    MBTX b;
    b.m_b = 10;
    b.m_matx.m_a = 20;
    MBTX b2 = b;  // 这里并没有真正调用拷贝构造函数，而是执行逐成员拷贝
    return 0;
}