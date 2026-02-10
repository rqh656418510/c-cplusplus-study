#pragma once

// Copyable 类被继承以后，派生类对象可以正常地执行构造和析构操作，同时派生类对象还可以进行拷贝构造和赋值操作
class Copyable {
protected:
    Copyable() = default;
    ~Copyable() = default;
};