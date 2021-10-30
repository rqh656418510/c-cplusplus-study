/**
 * 1. 静态成员变量的使用
 */

#include <iostream>

using namespace std;

class Counter {
public:
    int mem;             // 公有成员变量
    static int smem;     // 公有静态成员变量

public :
    Counter(int num) {
        mem = num;
    }
};

// 定义静态成员变量
int  Counter::smem = 0;

int main() {
    Counter c(5);
    for (int i = 0; i < 5; i++) {
        // 访问静态成员变量的方法1（通过类名直接访问）
        Counter::smem += i;
        cout << "Counter::smem = "<< Counter::smem << endl;
    }

    // 访问静态成员变量的方法2（通过对象访问）
    cout << "c.smem = " << c.smem << endl;
    return 0;
}