#include "mprpcapplication.h"

#include <iostream>

// 构造函数
MprpcApplication::MprpcApplication() {
}

// 析构函数
MprpcApplication::~MprpcApplication() {
}

// 获取单例对象
MprpcApplication* MprpcApplication::GetInstance() {
    // 局部静态变量（线程安全）
    static MprpcApplication singleton;
    return &singleton;
}

// 初始化 RPC 框架
void MprpcApplication::Init(int argc, char** argv) {
}