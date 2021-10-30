/**
 * 1. 静态成员变量的使用
 */

#include <iostream>

using namespace std;

class Counter {
private:
    // 声明静态成员变量
    static int num;

public :

    // 成员函数访问静态成员变量
    void setNum(int i) {
        num = i;
    }

    void showNum() {
        cout << num << endl;
    }
};

// 定义静态成员变量
int Counter::num = 0;

int main() {
    Counter a, b;
    a.showNum();
    b.showNum();
    a.setNum(10);
    a.showNum();
    b.showNum();
    return 0;
}