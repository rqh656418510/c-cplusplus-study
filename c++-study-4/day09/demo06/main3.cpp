/**
 * 构造函数语义续
 * 
 * (c) 类继承自虚基类（因为需要初始化虚基类表指针 `vbptr` 等，会合成 "非平凡（Non-trivial）" 构造函数）
 */

#include <iostream>

// 基类
class Grand {

};

// 派生类（虚继承）
class A : virtual public Grand {

};

// 派生类（虚继承）
class B : virtual public Grand {

};

// 派生类
class C : public A, public B {

};

int main() {
    C c;
    return 0;
}