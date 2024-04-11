/**
 * 前置后置递增运算符重载
 */

#include <iostream>

using namespace std;

class MyInteger {

public:
    MyInteger() {
        this->m_Num = 0;
    }

    MyInteger(int num) {
        this->m_Num = num;
    }

    // 前置++（++i）： 在使用前置++时，变量会先递增，然后表达式的值是递增后的值
    // 使用类成员函数完成 "前置++" 运算符的重载
    MyInteger &operator++() {
        this->m_Num++;
        return *this;
    }

    // 后置++（i++）： 在使用后置++时，表达式的值是变量当前的值，然后再递增变量
    // 使用类成员函数与占位参数完成 "后置++" 运算符的重载
    MyInteger operator++(int) {
        MyInteger temp(this->m_Num);
        this->m_Num++;
        return temp;
    }

    // 声明友元函数实现 "<<" 左移运算符的重载
    friend ostream &operator<<(ostream &out, MyInteger &integer);

private:
    int m_Num;

};

// 定义友元函数实现 "<<" 左移运算符的重载
ostream &operator<<(ostream &out, MyInteger &integer) {
    cout << "num = " << integer.m_Num;
    return out;
}

void test01() {
    MyInteger myInteger1;

    // 前置++
    ++myInteger1;
    cout << myInteger1 << endl;

    // 后置++
    MyInteger myInteger2 = myInteger1++;
    cout << myInteger2 << endl;
    cout << myInteger1 << endl;
}

int main() {
    test01();
    return 0;
}
