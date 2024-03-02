/**
 * 1. C 语言封装与 C++ 封装的区别
 *
 * <p> C语言中的封装，没有严格的类型转换检测，而且无法将属性和行为绑定在一起
 */

#include <stdio.h>

struct Person {
    char name[32];
    int age;
};

void eat(struct Person *p) {
    printf("%s正在吃饭 ...\n", p->name);
}

struct Dog {
    char name[32];
    char color[10];
};

void play(struct Dog *d) {
    printf("%s正在玩 ...\n", d->name);
}

void test01() {
    struct Person p = {"张三", 23};
    eat(&p);

    struct Dog d = {"旺财", "黑色"};
    play(&d);
}

void test02() {
    struct Person p = {"张三", 23};
    play(&p);   // 这里的参数即使传入了 Person 的结构体，编译器也不会报错，因为 C 语言没有严格的类型转换检测
}

int _main() {
    test01();
    test02();
    return 0;
}