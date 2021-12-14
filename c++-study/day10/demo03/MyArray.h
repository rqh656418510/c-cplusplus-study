#pragma once

#include <iostream>
#include "MyException.h"

using namespace std;

class MyArray {

public:
    // 构造函数
    MyArray(int size) {
        // 数组初始化大小检查，大小不合法则抛出异常
        if (size < 0) {
            throw NegativeException(size);
        }
        else if (size == 0) {
            throw ZeroException(size);
        }
        else if (size > this->m_max_size) {
            throw TooBigException(size);
        }
        this->m_size = size;
        this->m_space = new int[size];
    }

    // 拷贝构造函数
    MyArray(const MyArray& obj) {
        // 深拷贝
        this->m_size = obj.m_size;
        this->m_space = new int[obj.m_size];
        for (int i = 0; i < obj.m_size; i++) {
            this->m_space[i] = obj.m_space[i];
        }
    }

    // 析构函数
    ~MyArray() {
        if (this->m_space) {
            delete[] this->m_space;
            this->m_space = NULL;
            this->m_size = 0;
        }
    }

public:
    // 使用类成员函数，重载运算符 "[]"
    int& operator[](int index) {
        return this->m_space[index];
    }

    // 使用类成员函数，重载运算符 "="
    MyArray& operator=(const MyArray& obj) {
        // 释放原本的内存空间
        if (this->m_space) {
            delete[] this->m_space;
            this->m_space = NULL;
            this->m_size = 0;
        }
        // 深拷贝
        this->m_size = obj.m_size;
        this->m_space = new int[obj.m_size];
        for (int i = 0; i < obj.m_size; i++) {
            this->m_space[i] = obj.m_space[i];
        }
        return *this;
    }

    // 使用友元函数，重载运算符 "<<"
    friend ostream& operator<<(ostream& out, const MyArray& obj);

public:
    int getsize() {
        return m_size;
    }

private:
    int* m_space;
    int m_size;
    int m_max_size = 1000;
};

// 使用友元函数，重载运算符 "<<"
ostream& operator<<(ostream& out, const MyArray& obj) {
    for (int i = 0; i < obj.m_size; i++) {
        out << obj.m_space[i] << ", ";
    }
    return out;
}