/**
 * 1. C 语言封装与 C++ 封装的区别
 */

#include <stdio.h>
#include <string.h>

struct Person {
    char name[32];
    int age;
};

void eat(struct Person *p) {
    printf("%s 正在吃饭 ...\n", p->name);
}

int main() {
    struct Person a = {"Tom", 23};
    eat(&a);
    return 0;
}