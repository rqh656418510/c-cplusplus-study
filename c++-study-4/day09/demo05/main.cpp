/**
 * 分析 .obj 目标文件，构造函数语义
 * 
 * (a) 类中包含带有 "非平凡（Non-trivial）" 默认构造函数的成员对象（如果成员的默认构造函数是 "平凡（Trivial）" 的，编译器不会触发合成 "非平凡" 构造函数的动作）
 */

#include <iostream>

class MATX {
public:
    // 自定义的默认构造函数（非平凡）
    MATX() {
        
    }
};

class MBTX {
public:
    void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_i;      // 基本类型成员变量
    MATX m_matx;  // 类类型成员变量（非平凡）
};

int main() {
    MBTX b;
    return 0;
}