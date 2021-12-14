#pragma once

#include <iostream>

using namespace std;

// �쳣������
class SizeException {

public:
    // ���麯��
    virtual void printErr() = 0;

public:
    int getSize() {
        return this->size;
    }

protected:
    int size = 0;
};

class NegativeException : public SizeException {

public:
    NegativeException(int size) {
        this->size = size;
    }

    void printErr() {
        cout << "�����С����С����, ��ǰ��СΪ " << this->size << endl;
    }

};

class TooBigException : public SizeException {

public:
    TooBigException(int size) {
        this->size = size;
    }

    void printErr() {
        cout << "�����С̫��, ��ǰ��СΪ " << this->size << endl;
    }

};

class ZeroException : public SizeException {

public:
    ZeroException(int size) {
        this->size = size;
    }

    void printErr() {
        cout << "�����С������Ϊ��" << endl;
    }
};