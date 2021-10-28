/**
 * 1. 浅拷贝与深拷贝
 * 在以下的代码中，`obj3 = obj1;` 依旧属于浅拷贝（这里不会自动调用拷贝构造函数），最终程序也会异常终止运行
 * 若希望解决该问题，需要重载 C++ 的 `=` 操作符，这里暂时不展开讨论
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
    Name obj3("Tom");
    obj3 = obj1;       // 浅拷贝，不会自动调用拷贝构造函数
    cout << "obj1.name: " << obj1.getP() << ", obj1.len:  " << obj1.getLen() << endl;
    cout << "obj3.name: " << obj3.getP() << ", obj3.len:  " << obj3.getLen() << endl;
    return 0;
}