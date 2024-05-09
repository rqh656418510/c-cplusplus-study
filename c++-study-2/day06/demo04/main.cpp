/**
 * 抽象类和纯虚函数
 *
 * <p> 如果类中存在纯虚函数，通常称这个类为抽象类
 * <p> 如果类中存在纯虚函数，则这个类不能创建对象（实例化）
 * <p> 如果基类中存在纯虚函数，那么派生类必须实现所有的纯虚函数，否则这个派生类也是一个抽象类
 */

#include <iostream>

using namespace std;

// 抽象计算器
class AbstractCalculator {

public:
    // 声明纯虚函数
    virtual int getResult() = 0;

    int getValue1() const {
        return this->value1;
    }

    void setValue1(int value1) {
        this->value1 = value1;
    }

    int getValue2() const {
        this->value2;
    }

    void setValue2(int value2) {
        this->value2 = value2;
    }

public:
    int value1;
    int value2;

};

// 加法计算器
class AdditionCalculator : public AbstractCalculator {

public:
    // 纯虚函数实现
    virtual int getResult() override {
        return this->value1 + this->value2;
    }

};

// 减法计算器
class SubtractionCalculator : public AbstractCalculator {

public:
    // 纯虚函数实现
    virtual int getResult() override {
        return this->value1 - this->value2;
    }

};

int main() {
    AbstractCalculator *calculator;

    calculator = new AdditionCalculator();
    calculator->setValue1(3);
    calculator->setValue2(5);
    cout << calculator->getResult() << endl;

    calculator = new SubtractionCalculator();
    calculator->setValue1(3);
    calculator->setValue2(5);
    cout << calculator->getResult() << endl;

    return 0;
}
