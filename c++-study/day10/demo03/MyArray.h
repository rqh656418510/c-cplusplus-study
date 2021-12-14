#pragma once

#include <iostream>
#include "MyException.h"

using namespace std;

class MyArray {

public:
    // ���캯��
    MyArray(int size) {
        // �����ʼ����С��飬��С���Ϸ����׳��쳣
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

    // �������캯��
    MyArray(const MyArray& obj) {
        // ���
        this->m_size = obj.m_size;
        this->m_space = new int[obj.m_size];
        for (int i = 0; i < obj.m_size; i++) {
            this->m_space[i] = obj.m_space[i];
        }
    }

    // ��������
    ~MyArray() {
        if (this->m_space) {
            delete[] this->m_space;
            this->m_space = NULL;
            this->m_size = 0;
        }
    }

public:
    // ʹ�����Ա��������������� "[]"
    int& operator[](int index) {
        return this->m_space[index];
    }

    // ʹ�����Ա��������������� "="
    MyArray& operator=(const MyArray& obj) {
        // �ͷ�ԭ�����ڴ�ռ�
        if (this->m_space) {
            delete[] this->m_space;
            this->m_space = NULL;
            this->m_size = 0;
        }
        // ���
        this->m_size = obj.m_size;
        this->m_space = new int[obj.m_size];
        for (int i = 0; i < obj.m_size; i++) {
            this->m_space[i] = obj.m_space[i];
        }
        return *this;
    }

    // ʹ����Ԫ��������������� "<<"
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

// ʹ����Ԫ��������������� "<<"
ostream& operator<<(ostream& out, const MyArray& obj) {
    for (int i = 0; i < obj.m_size; i++) {
        out << obj.m_space[i] << ", ";
    }
    return out;
}