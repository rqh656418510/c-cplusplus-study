/**
 * 类型转换：static_cast等
 */

#include <iostream>

using namespace std;

class Father {

public:
    Father(string name, int age) {
        this->m_Name = name;
        this->m_Age = age;
    }

    // 虚函数
    virtual void print() {
        cout << endl << "name = " << this->m_Name << ", age = " << this->m_Age << endl;
    }

protected:
    string m_Name;
    int m_Age;

};

class Son : public Father {

public:
    Son(string name, int age, string hobby) : Father(name, age) {
        this->m_Name = name;
        this->m_Age = age;
        this->m_hobby = hobby;
    }

    void print() override {
        cout << endl << "name = " << this->m_Name << ", age = " << this->m_Age << ", hobby = " << m_hobby << endl;
    }

private:
    string m_hobby;

};

// 隐式类型转换，系统自动进行，不需要开发人员介入
void test1() {
    int m = 3 + 35.63;
    cout << "m = " << m << endl;
}

// 显式类型转换 - static_cast（静态类型转换）
void test2() {
    int k = 5 % static_cast<int>(3.2);
    cout << "k = " << k << endl;

    int i = 10;
    int *p = &i;
    void *q = p; // void * 可以指向任何指针类型（也称为万能指针）
    int *n = static_cast<int *>(q);

    Father father("Father", 60);
    Son son("Son", 25, "Game");

    // 上行转换（将派生类的指针转换成基类表示），是安全的
    Son *son1 = new Son("Son", 25, "Game");
    Father *father1 = static_cast<Father *>(son1);
    father1->print();   // 发生多态，调用派生类的 print() 函数

    // 下行转换（将基类的指针转换成派生类表示），是不安全的（编译通过，但运行可能出错）
    Father *father2 = new Father("Father", 60);
    Son *son2 = static_cast<Son *>(father2);
    son2->print();  // 调用基类的 print() 函数
}

// 显式类型转换 - dynamic_cast（动态类型转换）
void test3() {
    Father father("Father", 60);
    Son son("Son", 25, "Game");

    // 上行转换（将派生类的引用转换成基类表示），是安全的
    Father &father1 = dynamic_cast<Father &>(son);
    father1.print(); // 发生多态，调用派生类的 print() 函数

    // 下行转换（将基类的引用转换成派生类表示），是不安全的，无法进行类型转换（编译通过，但运行可能出错）
    // Son &son2 = dynamic_cast<Son &>(father);
    // son2.print();

    // 上行转换（将派生类的指针转换成基类表示），是安全的
    Son *son1 = new Son("Son", 25, "Game");
    Father *father2 = dynamic_cast<Father *>(son1);
    father2->print(); // 发生多态，调用派生类的 print() 函数

    // 下行转换（将基类的指针转换成派生类表示），是不安全的，无法进行类型转换（编译通过，但运行可能出错）
    Father *father3 = new Father("Father", 60);
    // Son *son2 = dynamic_cast<Son *>(father2);
    // son2->print();
}

// 显式类型转换 - const_cast（常量类型转换）
void test4() {
    const int *p = nullptr;
    // 常量指针被转换成非常量指针
    int *newP = const_cast<int *>(p);

    int *p2 = nullptr;
    // 非常量指针被转换成常量指针
    const int *newP2 = const_cast<const int *> (p2);

    int age = 20;
    const int &ageRef = age;
    // 常量引用被转换成非常量引用
    int &ageRef2 = const_cast<int &>(ageRef);

    int num = 10;
    int &numRef = num;
    // 非常量引用被转换成常量引用
    const int &numRef2 = const_cast<const int &>(numRef);

    const int a = 10;
    // 不能直接对非指针和非引用的变量使用 const_cast 操作符去直接赋予或者去除它的 const 只读属性
    // int a = const_cast<int>(a);
}

// 显式类型转换 - reinterpret_cast（重新解释类型）
void test5() {
    int a = 10;
    // 将整数强制转换成指针（不安全，非常危险）
    int *p = reinterpret_cast<int * >(a);
}

int main() {
//    test1();
//    test2();
//    test3();
    test4();
//    test5();
    return 0;
}