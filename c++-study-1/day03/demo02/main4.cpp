/**
 * 1. 拷贝构造函数的第四种调用场景
 */

#include <iostream>

using namespace std;

class Location {

private :
    int x, y;

public:
    Location(int xx = 0, int yy = 0) {
        x = xx;
        y = yy;
        cout << "有参构造函数被调用了" << endl;
    }

    Location(const Location &p) {
        x = p.x;
        y = p.y;
        cout << "拷贝构造函数被调用了" << endl;
    }

    ~Location() {
        cout << "析构函数被调用了" << endl;
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }
};

Location functionA() {
    Location l(1, 2);
    return l;
}

int main() {
    // 匿名对象的去与留，关键是看返回匿名对象时如何接收，一般有以下两种情况：

    // 若将函数functionA()返回的匿名对象，赋值给另外一个同类型的对象，那么匿名对象会被析构
    // 此时有参构造函数和析构函数被调用两次
    Location A;
    A = functionA();

    // 若使用函数functionA()的匿名对象，来初始化另外一个同类型的对象，那么匿名对象会直接转成B对象
    // 此时有参构造函数与析构函数各被调用一次
    // Location B = functionA();
    return 0;
}