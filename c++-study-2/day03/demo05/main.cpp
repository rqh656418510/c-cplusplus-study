/**
 * 拷贝构造函数的调用时机
 */

#include <iostream>

using namespace std;

class Person {

public:
    Person() {
        cout << "无参构造函数" << endl;
    }

    Person(string name, int age) {
        this->name = name;
        this->age = age;
        cout << "有参构造函数" << endl;
    }

    Person(const Person &p) {
        this->name = p.name;
        this->age = p.age;
        cout << "拷贝构造函数" << endl;
    }

    ~Person() {
        cout << "析构函数" << endl;
    }

    int getAge() const {
        return this->age;
    }

    void setAge(int age) {
        this->age = age;
    }

private:
    string name;
    int age;

};

void work(Person p) {
    p.setAge(28);
}

Person play() {
    Person p("Peter", 23);
    return p;
}

void test01() {
    Person p1("Jim", 23);

    // 第一种情况：自动调用拷贝构造函数
    Person p2 = p1;

    // 第二种情况：自动调用拷贝构造函数
    Person p3(p1);

    // 第三种情况：自动调用拷贝构造函数
    Person p4 = Person(p1);
}

void test02() {
    Person p("Tom", 14);

    // 第四种情况：自动调用拷贝构造函数，以值传递的方式给函数参数传值
    work(p);

    cout << "age = " << p.getAge() << endl;
}

void test03() {
    // 第五种情况：自动调用拷贝构造函数，函数以值方式返回局部对象
    // 注意：以下的写法，在 Debug 模式下才会调用拷贝构造函数，Release 模式不会调用拷贝构造函数（编译器优化的结果）
    Person p = play();

}

int main() {
    cout << "----------call test1()----------" << endl;
    test01();

    cout << "----------call test2()----------" << endl;
    test02();

    cout << "----------call test3()----------" << endl;
    test03();

    return 0;
}
