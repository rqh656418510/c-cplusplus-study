/**
 * 构造函数语义续
 * 
 * (b) 类中存在虚函数（因为需要初始化虚函数表指针 `vptr`，会合成 "非平凡（Non-trivial）" 构造函数）
 */

#include <iostream>

class MBTX {
public:
    // 虚函数
    virtual void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_i;      // 基本类型成员变量
};

int main() {
    MBTX b;
    return 0;
}