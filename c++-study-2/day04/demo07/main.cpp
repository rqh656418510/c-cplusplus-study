/**
 * 空指针访问成员函数
 */

#include <iostream>

using namespace std;

class Person {

public:

    void showPerson() {
        cout << "Show person" << endl;
    }

    void showAge() {
        cout << "Show age is " << mAge << endl;
    }

    void printAge() {
        // 判断 this 指针是否为空
        if (this == NULL) {
            return;
        }
        cout << "Print age is " << this->mAge << endl;
    }

private:
    int mAge;

};

int main() {
    Person *p = NULL;
    p->showPerson();    // 空指针可以访问 showPerson() 成员函数
    p->printAge();      // 空指针可以访问 printAge() 成员函数
    // p->showAge();    // 空指针不可以访问 showAge() 成员函数，代码编译会通过，但运行期间会异常退出
    return 0;
}
