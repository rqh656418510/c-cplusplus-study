/**
 * 1. 浅拷贝与深拷贝
 * 自定义拷贝构造函数，通过实现深拷贝（申请新的内存空间）来解决C++默认拷贝构造函数的浅拷贝问题
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

    // 深拷贝的实现
    Name(const Name &name) {
        cout << "拷贝构造函数被调用了" << endl;
        int length = name.getLen();
        p = (char *) malloc(length + 1);
        strcpy(p, name.getP());
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
    Name obj3 = obj1;       // 自动调用自定义的拷贝构造函数
    cout << "obj1.name: " << obj1.getP() << ", obj1.len:  " << obj1.getLen() << endl;
    cout << "obj3.name: " << obj3.getP() << ", obj3.len:  " << obj3.getLen() << endl;
    return 0;
}