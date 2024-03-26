/**
 * 静态成员变量
 */

#include <iostream>

using namespace std;

class Counter {

public:

    Counter() {

    }

    Counter(const Counter &p) {
        this->number = p.number;
    }

    ~Counter() {

    }

    void setNumber(const int num) {
        this->number = num;
    }

    void showNumber() const {
        cout << "number = " << this->number << endl;
    }

private:
    static int number;

};

// 定义静态成员变量，这里不是简单的变量赋值，更重要的是告诉C++编译器，给静态成员变量分配内存
int Counter::number = 0;

int main() {
    Counter c1;
    c1.setNumber(10);
    c1.showNumber();

    Counter c2;
    c2.showNumber();

    return 0;
}