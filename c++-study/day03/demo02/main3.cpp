/**
 * 1. 拷贝构造函数的第三种调用场景
 */

#include "iostream"

using namespace std;

class Location {
private :
    int X, Y;

public:
    Location(int xx = 0, int yy = 0) {
        X = xx;
        Y = yy;
        cout << "有参构造函数被调用了" << endl;
    }

    Location(const Location &p) {
        X = p.X;
        Y = p.Y;
        cout << "拷贝构造函数被调用了" << endl;
    }

    ~Location() {
        cout << "析构函数被调用了" << endl;
    }

    int getX() {
        return X;
    }

    int getY() {
        return Y;
    }
};

void functionA(Location b) {
    cout << b.getX() << "," << b.getY() << endl;
}

int main() {
    Location a(1, 2);
    functionA(a);         // 拷贝构造函数会被调用，这里会使用实参变量（a）初始化形参变量（b），同时会多创建一个Location对象（匿名对象），所以最后析构函数会被调用两次
    return 0;
}
