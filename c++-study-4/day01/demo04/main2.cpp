/**
 * 结构体、权限修饰符、类简介
 */

#include <iostream>
#include <cstring>

using namespace std;

class Student {

public:
    int id;
    char name[50];

    // 构造函数
    Student() {

    }

    // 构造函数
    Student(int id, const char *name) {
        this->id = id;
        strcpy(this->name, name);
    }

    void show() {
        cout << "id = " << id << ", name = " << name << endl;
    }

};

int main() {
    Student student1;
    student1.id = 1;
    strcpy(student1.name, "Jim");
    student1.show();

    const char *name = "Tom";
    Student student2(2, name);
    student2.show();

    return 0;
}