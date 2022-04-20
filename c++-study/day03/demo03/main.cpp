/**
 * 1. 浅拷贝与深拷贝
 * 由于在下述的代码中，没有自定义拷贝构造函数，使用的是 C++ 编译器提供的默认拷贝构造函数，因此程序无法正常运行
 * 造成程序无法正常运行的根本原因是，C++ 提供的默认拷贝构造函数属于浅拷贝，在调用下面的析构函数时会出现错误（同一块内存空间被释放两次）
 */

#include <iostream>
#include "string.h"

using namespace std;

class Name {

private:
    char *p;
    int len;

public:

    Name(const char *name) {
        cout << "有参构造函数被调用了" << endl;
        int length = strlen(name);
        p = (char *) malloc(length + 1);
        strcpy(p, name);
        len = length;
    }

    ~Name() {
        cout << "析构函数被调用了" << endl;
        if (p != NULL) {
            free(p);
            p = NULL;
            len = 0;
        }
    }

    char *getP() const {
        return p;
    }

    int getLen() const {
        return len;
    }
};

int main() {
    Name obj1("Peter");
    Name obj2 = obj1;       // 自动调用C++提供的默认拷贝构造函数，属于浅拷贝
    cout << "obj1.name: " << obj1.getP() << ", obj1.len:  " << obj1.getLen() << endl;
    cout << "obj2.name: " << obj2.getP() << ", obj2.len:  " << obj2.getLen() << endl;
    return 0;
}