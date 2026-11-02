/**
 * 分析 .obj 目标文件，构造函数语义
 */

#include <iostream>

class MATX {
public:
    // 默认构造函数
    MATX() {
        std::cout << "MATX::MATX() called" << std::endl;
    }
};

class MBTX {
public:
    void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_i;      // 基本类型成员变量
    MATX m_matx;  // 类类型成员变量
};

int main() {
    MBTX b;
    return 0;
}