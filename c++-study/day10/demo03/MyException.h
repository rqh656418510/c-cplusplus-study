#pragma once

#include <iostream>

using namespace std;

// 异常抽象类
class SizeException {

public:
    // 纯虚函数
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
        cout << "数组大小不能小于零, 当前大小为 " << this->size << endl;
    }

};

class TooBigException : public SizeException {

public:
    TooBigException(int size) {
        this->size = size;
    }

    void printErr() {
        cout << "数组大小太大, 当前大小为 " << this->size << endl;
    }

};

class ZeroException : public SizeException {

public:
    ZeroException(int size) {
        this->size = size;
    }

    void printErr() {
        cout << "数组大小不允许为零" << endl;
    }
};