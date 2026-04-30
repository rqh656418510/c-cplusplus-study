#pragma once

#include <iostream>

using namespace std;

// 定义类模板（使用类型模板参数和非类型模板参数）
template <typename T, int C = 10>
class MyVector {
public:
    // 定义迭代器类型
    using iterator = T*;

    // 构造函数
    MyVector();

    // 析构函数
    ~MyVector();

    // 拷贝构造函数
    MyVector(const MyVector& v);

    // 赋值运算符
    MyVector& operator=(const MyVector& v);

    // 返回迭代器的起始位置
    iterator begin();

    // 返回迭代器的最后一个元素的下一个位置
    iterator end();

    // 往容器末尾添加元素
    bool push_back(const T& t);

private:
    T* m_data;          // 底层数组
    size_t m_size;      // 元素个数
    size_t m_capacity;  // 最大容量
};

// 构造函数
template <typename T, int C>
MyVector<T, C>::MyVector() {
    m_size = 0;
    m_capacity = C > 0 ? C : 10;

    // 申请内存空间
    m_data = new T[m_capacity];
}

// 析构函数
template <typename T, int C>
MyVector<T, C>::~MyVector() {
    if (m_data) {
        delete[] m_data;
        m_data = nullptr;
    }
}

// 拷贝构造函数
template <typename T, int C>
MyVector<T, C>::MyVector(const MyVector<T, C>& v) {
    m_size = v.m_size;
    m_capacity = v.m_capacity;

    // 深拷贝
    m_data = new T[m_capacity];
    for (size_t i = 0; i < m_size; ++i) {
        m_data[i] = v.m_data[i];
    }
}

// 赋值运算符
template <typename T, int C>
MyVector<T, C>& MyVector<T, C>::operator=(const MyVector<T, C>& v) {
    // 防止自赋值
    if (this == &v) {
        return *this;
    }

    // 申请新的内存空间
    T* new_data = new T[v.m_capacity];
    for (size_t i = 0; i < v.m_size; ++i) {
        new_data[i] = v.m_data[i];
    }

    // 释放旧的内存空间
    delete[] m_data;

    m_data = new_data;
    m_size = v.m_size;
    m_capacity = v.m_capacity;

    return *this;
}

// 返回迭代器的起始位置
template <typename T, int C>
typename MyVector<T, C>::iterator MyVector<T, C>::begin() {
    return m_data;
}

// 返回迭代器的最后一个元素的下一个位置
template <typename T, int C>
typename MyVector<T, C>::iterator MyVector<T, C>::end() {
    return m_data + m_size;
}

// 往容器末尾添加元素
template <typename T, int C>
bool MyVector<T, C>::push_back(const T& t) {
    if (m_size == m_capacity) {
        return false;
    }

    m_data[m_size] = t;
    ++m_size;

    return true;
}
