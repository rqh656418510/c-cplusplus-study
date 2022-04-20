/**
 * 1. 构造函数与析构函数的定义
 */

#include <iostream>

using namespace std;

class Teacher {

public:

    // 定义无参构造函数
    Teacher() {
        cout << "调用构造函数" << endl;
    }

    // 定义析构函数
    ~Teacher() {
        cout << "调用析构函数" << endl;
    }

};

int main() {
    Teacher teacher;
    return 0;
}