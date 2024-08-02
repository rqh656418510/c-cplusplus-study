#pragma once

#include <iostream>

using namespace std;

template<class T>
class MyArray {

public:

    // 构造函数
    explicit MyArray(int capacity) {
        this->m_Size = 0;
        this->m_Capacity = capacity;
        // 分配内存空间
        this->pAddress = new T[capacity];
    }

    // 拷贝构造函数
    MyArray(const MyArray &array) {
        this->m_Size = array.m_Size;
        this->m_Capacity = array.m_Capacity;
        // 深拷贝
        this->pAddress = new T[array.m_Capacity];
        for (int i = 0; i < array.m_Size; i++) {
            this->pAddress[i] = array.pAddress[i];
        }
    }

    // 析构函数
    ~MyArray() {
        // 释放内存空间
        if (this->pAddress != nullptr) {
            delete[] this->pAddress;
            this->pAddress = nullptr;
            this->m_Size = 0;
        }
    }

    // 赋值操作符重载
    MyArray &operator=(const MyArray &array) {
        // 释放原本的内存空间
        if (this->pAddress != nullptr) {
            delete[] this->pAddress;
            this->pAddress = nullptr;
            this->m_Size = 0;
        }

        this->m_Size = array.m_Size;
        this->m_Capacity = array.m_Capacity;
        // 深拷贝
        this->pAddress = new T[array.m_Capacity];
        for (int i = 0; i < array.m_Size; i++) {
            this->pAddress[i] = array.pAddress[i];
        }
    }

    // << 操作符重载
    friend ostream &operator<<(ostream &out, const MyArray &array) {
        for (int i = 0; i < array.m_Size; i++) {
            cout << array.pAddress[i] << '\t';
        }
        return out;
    }

    // [] 操作符重载
    T &operator[](int index) {
        return this->pAddress[index];
    }

    // 尾部插入元素
    void pushBack(T item) {
        this->pAddress[this->m_Size] = item;
        this->m_Size++;
    }

    // 获取容量
    int capacity() {
        return this->m_Capacity;
    }

    // 获取元素数量
    int size() {
        return this->m_Size;
    }

private:
    T *pAddress = nullptr;  // 指向堆区的指针
    int m_Capacity = 0;     // 容量
    int m_Size = 0;         // 元素数量
};
