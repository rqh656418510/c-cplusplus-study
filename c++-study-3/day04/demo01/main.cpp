/**
 * 学习复数类 CComplex（二元运算符的重载）
 */

#include <iostream>

using namespace std;

class CComplex {

public:
    CComplex(int r = 0, int i = 0) : mreal(r), mimage(i) {

    }

    // 在局部作用域加法运算符的重载函数
    // 这里不能返回引用，因为在栈上分配内存空间的对象，随着函数的运行结束，内存空间会自动释放
    CComplex operator+(const CComplex &other) {
        return CComplex(this->mreal + other.mreal, this->mimage + other.mimage);
    }

    // 利用友元函数实现加法运算符的重载
    friend CComplex operator+(const CComplex &left, const CComplex &right);

    // 利用友元函数实现左移运算符的重载
    friend ostream &operator<<(ostream &out, const CComplex &c);

    void print() {
        cout << "mreal: " << mreal << ", mimage: " << mimage << endl;
    }

private:
    int mreal;
    int mimage;

};

// 在全局作用域实现加法运算符的重载
CComplex operator+(const CComplex &left, const CComplex &right) {
    return CComplex(left.mreal + right.mreal, left.mimage + right.mimage);
}

// 在全局作用域实现左移运算符的重载
ostream &operator<<(ostream &out, const CComplex &c) {
    out << "mreal: " << c.mreal << ", mimage: " << c.mimage << endl;
    return out;
}

int main() {
    CComplex c1(10, 10);
    CComplex c2(20, 20);

    CComplex c3 = c1 + c2;       // 相当于 CComplex c3 = c1.operator+(c2);
    c3.print();

    CComplex c4 = c1 + 20;      // 默认可以正常编译运行，会自动调用 CComplex(int r = 0, int i = 0) 构造函数，然后再执行加法运算
    c4.print();

    // 编译器做对象运算的时候，会调用对象的运算符重载函数（优先调用成员方法）；如果没有成员方法，就会在全局作用域找合适的运算符重载函数。
    CComplex c5 = 30 + c1;      // 默认不可以正常编译运行，除非是在全局作用域实现加法运算符的重载
    c5.print();

    cout << c1 << endl;     // 左移运算符的重载

    return 0;
}
