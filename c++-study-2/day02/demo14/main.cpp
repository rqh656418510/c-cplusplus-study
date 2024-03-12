/**
 * 深拷贝与浅拷贝
 */

#include <iostream>
#include <string.h>>

using namespace std;

class Person {

public:

    Person(char *name, int age) {
        this->name = (char *) malloc(strlen(name) + 1);
        strcpy(this->name, name);
        this->age = age;
    }

    Person(const Person &p) {
        // 深拷贝
        this->name = (char *) malloc(strlen(p.getName()) + 1);
        strcpy(this->name, p.getName());
        this->age = p.getAge();
    }

    ~Person() {
        if (this->name != NULL) {
            free(this->name);
            this->name = NULL;
        }
        this->age = 0;
    }

    char *getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

private:
    char *name;
    int age;

};

int main() {
    Person p1("Jim", 18);
    cout << "name = " << p1.getName() << ", age = " << p1.getAge() << endl;

    // 自动调用C++提供的默认拷贝构造函数，属于浅拷贝
    Person p2 = p1;
    cout << "name = " << p2.getName() << ", age = " << p2.getAge() << endl;

    // 如果上面不自定义拷贝构造函数（实现深拷贝），那么会因为 C++ 提供的默认拷贝构造函数使用了浅拷贝，从而导致上面的代码对同一块内存空间执行了两次释放操作，最终程序异常终止运行

    return 0;
}
