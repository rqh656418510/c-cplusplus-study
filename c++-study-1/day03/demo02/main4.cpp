#include <iostream>

using namespace std;

class Location {

private:
    int x, y;

public:
    Location(int xx = 0, int yy = 0) {
        x = xx;
        y = yy;
        cout << "有参构造函数被调用了" << endl;
    }

    Location(const Location& p) {
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

void test01() {
    // 第一种情况
    // 在 Debug 模式下，若使用函数 functionA() 的返回值（局部对象），赋值给另外一个同类型的对象时，会自动调用拷贝构造函数
    // 在 Release 模式下，若使用函数 functionA() 的返回值（局部对象），赋值给另外一个同类型的对象时，不会自动调用拷贝构造函数（编译器优化结果）
    Location A;
    A = functionA();
}

void test02() {
    // 第二种情况
    // 在 Debug 模式下，若使用函数 functionA() 的返回值（局部对象），来初始化另外一个同类型的对象时，会自动调用拷贝构造函数
    // 在 Release 模式下，若使用函数 functionA() 的返回值（局部对象），来初始化另外一个同类型的对象时，不会自动调用拷贝构造函数（编译器优化的结果）
    Location B = functionA();
}

int main() {
    // 局部对象的去与留，关键是看返回局部对象时如何被接收，一般有以下两种情况

    cout << "----------call test1()----------" << endl;
    test01();

    cout << "----------call test2()----------" << endl;
    test02();

    return 0;
}
