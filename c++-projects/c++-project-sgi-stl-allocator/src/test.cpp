﻿#include<iostream>
#include<vector>
#include<cstring>
#include "allocator.h"

using namespace std;

// 自定义数据类型
class Person {

private:
    char *name;
    int age;

    // 深拷贝字符串
    void deepCopy(const char *source) {
        if (source) {
            name = new char[strlen(source) + 1];
            strcpy(name, source);
        } else {
            name = nullptr;
        }
    }

public:
    // 构造函数
    Person(const char *name, int age) : age(age) {
        cout << "Person(name, age)" << endl;
        deepCopy(name);
    }

    // 拷贝构造函数
    Person(const Person &other) : age(other.age) {
        cout << "Person(const Person&)" << endl;
        deepCopy(other.name);
    }

    // 赋值运算符
    Person &operator=(const Person &other) {
        cout << "Person& operator=(const Person&)" << endl;
        // 防止自赋值
        if (this != &other) {
            // 先释放原有内存
            delete[] name;

            // 拷贝新数据
            age = other.age;
            deepCopy(other.name);
        }
        return *this;
    }

    // 析构函数
    ~Person() {
        cout << "~Person()" << endl;
        delete[] name;
    }

    const char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void display() const {
        cout << "Name: " << (name ? name : "[Unnamed]") << ", Age: " << age << endl;
    }

};

// 测试基础类型的内存分配
void test01() {
    // 设置随机种子
    srand(time(nullptr));

    // 使用 SGI STL 二级空间配置器
    vector<int, simple_alloc<int, default_alloc>> vec1;

    for (int i = 0; i < 10; ++i) {
        vec1.push_back(rand() % 10 + 1);
    }

    for (const int &item : vec1) {
        cout << item << " ";
    }

    cout << endl;
}

// 测试自定义类型的内存分配
void test02() {
    // 使用 SGI STL 二级空间配置器
    vector<Person, simple_alloc<Person, default_alloc>> vec2;

    // 如果不想频繁触发容器扩容，可以强制指定容器的预留容量
    // vec2.reserve(5);

    vec2.push_back(Person("Jim", 18));
    vec2.push_back(Person("Peter", 23));

    for (auto it = vec2.begin(); it != vec2.end(); ++it) {
        it->display();
    }
}

int main() {
    test01();
    test02();
    return 0;
}
