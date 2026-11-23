/**
 * 拷贝构造函数语义续
 */

#include <iostream>

class MATX {
public:
    int m_a;
};

int main() {
    MATX a1;
    a1.m_a = 10;
    MATX a2 = a1;  // 这里并没有真正调用拷贝构造函数，而是执行逐成员拷贝
    return 0;
}