/**
 * 结构体、权限修饰符、类简介
 */

#include <iostream>
#include <cstring>

using namespace std;

struct student {
    int id;
    char name[50];
};

// 结构体作为形参（效率低，会发生数据拷贝）
void func1(student stu) {
    stu.id = 2;
    strcpy(stu.name, "Bob");
}

// 结构体作为引用形参（效率高，不会发生数据拷贝）
void func2(student &stu) {
    stu.id = 2;
    strcpy(stu.name, "Jim");
}

// 结构体作为指针形参（效率高，不会发生数据拷贝）
void func3(student *stu) {
    stu->id = 2;
    strcpy(stu->name, "Tom");
}

// 结构体
void test01() {
    student student1;
    student1.id = 1;
    strcpy(student1.name, "Peter");
    cout << "id = " << student1.id << ", name = " << student1.name << endl;

    func1(student1);
    cout << "id = " << student1.id << ", name = " << student1.name << endl;

    func2(student1);
    cout << "id = " << student1.id << ", name = " << student1.name << endl;

    func3(&student1);
    cout << "id = " << student1.id << ", name = " << student1.name << endl;
}

int main() {
    test01();
}