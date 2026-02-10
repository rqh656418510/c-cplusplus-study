#pragma once

// NonCopyable 类被继承以后，派生类对象可以正常地执行构造和析构操作，但是派生类对象不能进行拷贝构造和赋值操作
class NonCopyable {
public:
    NonCopyable(const NonCopyable&) = delete;
    void operator=(const NonCopyable&) = delete;

protected:
    NonCopyable() = default;
    ~NonCopyable() = default;
};