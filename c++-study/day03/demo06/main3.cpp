/**
 * 1. 静态成员函数的使用
 */

#include <iostream>

using namespace std;

class Counter {
private:
    int num;

public:
    // 声明静态成员函数
    static int getNum(Counter *p);

    static void setNum(int i, Counter *p);
};

// 定义静态成员函数
int Counter::getNum(Counter *p) {
    return p->num;
}

void Counter::setNum(int i, Counter *p) {
    p->num = i;
}

int main() {
    Counter obj;

    // 访问静态成员函数的方法1（通过类名直接访问）
    Counter::setNum(1, &obj);
    cout << "num = " << Counter::getNum(&obj) << endl;

    // 访问静态成员函数的方法2（通过对象访问）
    obj.setNum(3, &obj);
    cout << "num = " << obj.getNum(&obj) << endl;
    return 0;
}
