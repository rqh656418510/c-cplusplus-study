/**
 * 构造函数语义续
 * 
 * (a) 类继承自带有 "非平凡（Non-trivial）" 默认构造函数的基类（如果基类的默认构造函数是 "平凡（Trivial）" 的，编译器不会触发合成 "非平凡" 构造函数的动作）
 */

#include <iostream>

// 基类
class Parent {

public:
    Parent() {
        std::cout << "Parent::Parent() called" << std::endl;
    }

};

// 派生类
class MBTX : public Parent {
public:
    void func() {
        std::cout << "MBTX::func() called" << std::endl;
    }

public:
    int m_i;      // 基本类型成员变量
};

int main() {
    MBTX b;
    return 0;
}