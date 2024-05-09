/**
 * 多态案例-计算器案例
 */

#include <iostream>

using namespace std;

// 抽象计算器
class AbstractCalculator {

public:
    // 定义虚函数
    virtual int getResult() {
        return 0;
    }

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
    // 虚函数重写
    virtual int getResult() override {
        return this->value1 + this->value2;
    }

};

// 减法计算器
class SubtractionCalculator : public AbstractCalculator {

public:
    // 虚函数重写
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
