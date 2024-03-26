/**
 * 静态成员函数
 */

#include <iostream>

using namespace std;

class Counter {

private:
    int num;

public:

    // 声明并定义静态成员函数
    static int getNum(Counter *p) {
        return p->num;
    }

    // 声明静态成员函数
    static void setNum(int i, Counter *p);

};

// 定义静态成员函数
void Counter::setNum(int i, Counter *p) {
    p->num = i;
}

int main() {
    Counter obj;

    // 访问静态成员函数的第一种方法（通过类名直接访问）
    Counter::setNum(1, &obj);
    cout << "num = " << Counter::getNum(&obj) << endl;

    // 访问静态成员函数的第二种方法（通过对象名访问）
    obj.setNum(3, &obj);
    cout << "num = " << obj.getNum(&obj) << endl;
    return 0;
}
