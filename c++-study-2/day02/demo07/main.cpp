/**
 * 1. C 语言封装与 C++ 封装的区别
 *
 * <p> C++ 中的封装，有严格的类型转换检测，可以将属性和行为绑定在一起
 * <p> C++ 中属性和行为作为一个整体来表示生活中的事物
 * <p> C++ 中控制权限分为：public、protected、private
 * <p> C++ 中 struct 和 class 可以认为是同一个意思，唯一不同的是默认权限，struct 的默认权限是 public，而 class 的默认权限是 private
 */

#include <iostream>

using namespace std;

struct Person {

    char name[32];
    int age;

    void eat() {
        cout << this->name << "正在吃饭 ..." << endl;
    }
};

void test01() {
    struct Person p = {"张三", 23};
    p.eat();
}

class Student {

public:
    Student(string name, int age) {
        this->name = name;
        this->age = age;
    }

    void study() {
        cout << this->name << "正在学习 ..." << endl;
    }

private:
    string name;
    int age;

};

void test02() {
    Student s("李四", 18);
    s.study();
}

int main() {
    test01();
    test02();
    return 0;
}
