/**
 * 学习复数类 CComplex（一元运算符的重载）
 */

#include <iostream>

using namespace std;

class CComplex {

public:
    CComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {

    }

    // "前置++" 运算符的重载
    CComplex &operator++() {
        this->mreal++;
        this->mimage++;
        return *this;
    }

    // "后置++" 运算符的重载
    // 使用占位参数进行函数重载，是为了解决与 "前置++" 类成员函数冲突的问题
    CComplex operator++(int) {
        return CComplex(this->mreal++, this->mimage++);
    }

    void print() {
        cout << "mreal: " << mreal << ", mimage: " << mimage << endl;
    }

private:
    int mreal;
    int mimage;

};

int main() {
    CComplex c1(10, 10);

    // 前置++
    CComplex c2(20, 20);
    c2 = ++c1;
    c1.print();     // 11 11
    c2.print();     // 11 11

    // 后置++
    CComplex c3(30, 30);
    c3 = c1++;
    c1.print();     // 12 12
    c3.print();     // 11 11

    return 0;
}
