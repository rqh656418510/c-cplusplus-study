/**
 * 1. C++中的引用之指针引用
 */

#include <iostream>
#include <string.h>

using namespace std;

struct Teacher {
    char name[64];
    int age;
};

// 二级指针作函数参数
int getTe(Name **myp) {
    Name *p = (Name *) malloc(sizeof(Name));
    if (p == NULL) {
        return -1;
    }
    memset(p, 0, sizeof(Name));
    p->age = 33;
    *myp = p;
    return 0;
}

// 指针引用作函数参数
int getTe2(Name *&myp) {
    myp = (Name *) malloc(sizeof(Name));
    if (myp == NULL) {
        return -1;
    }
    myp->age = 34;
    return 0;
}

int main() {
    Name *p = NULL;
    getTe(&p);
    printf("age:%d \n", p->age);

    Name *pp = NULL;
    getTe2(pp);
    printf("age:%d \n", pp->age);
    return 0;
}
