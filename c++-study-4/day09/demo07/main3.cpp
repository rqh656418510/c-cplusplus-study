/**
 * 拷贝构造函数语义续
 */

#include <iostream>

class MATX {
public:
    MATX() = default;

    // 自定义的拷贝构造函数（非平凡）
    MATX(const MATX&) {
        std::cout << "MATX::MATX(const MATX&) called" << std::endl;
    }
};

class MBTX {
public:
    void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_i = 0;  // 基本类型成员变量
    MATX m_matx;  // 类类型成员变量（拷贝构造为非平凡）
};

int main() {
    MBTX b;
    MBTX b2 = b;  // 调用 MBTX 的拷贝构造函数
    return 0;
}
