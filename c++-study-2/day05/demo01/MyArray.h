#pragma once

#include <iostream>

using namespace std;

class MyArray {

public:
    MyArray();

    MyArray(int capacity);

    MyArray(const MyArray &array);

    ~MyArray();

    void push_back(int value);

    int get_data(int index);

    void set_data(int index, int value);

    int &operator[](int index);

private:
    int *pAddress;      // 指向真正存储数据的指针
    int m_Size;         // 数组大小
    int m_Capacity;     // 数组容量

};