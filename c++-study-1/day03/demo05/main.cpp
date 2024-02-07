/**
 * 1. 对象的动态建立和释放
 */

#include <iostream>

using namespace std;

class Teacher {
private:
    int _age;

public:
    Teacher(int age) {
        this->_age = age;
        cout << "构造函数被调用" << endl;
    }

    ~Teacher() {
        cout << "析构函数被调用" << endl;
    }

    void setAget(int age) {
        this->_age = age;
    }

    int getAge() {
        return this->_age;
    }
};

// C语言分配基础类型
void functionA() {
    int *p = (int *) malloc(sizeof(int));
    *p = 3;
    cout << "functionA -> p = " << *p << endl;
    free(p);
}

// C++分配基础类型
void functionB() {
    int *a = new int;
    *a = 3;
    cout << "functionB -> a = " << *a << endl;
    delete a;

    int *b = new int(30);
    cout << "functionB -> b = " << *b << endl;
    delete b;
}

// C语言分配数组类型
void functionC() {
    char *p = (char *) malloc(sizeof(char) * 3);
    p[0] = 'a';
    p[1] = 'b';
    p[2] = 'c';
    cout << "functionC -> p = " << p[0] << p[1] << p[2] << endl;
    free(p);
}

// C++分配数组类型
void functionD() {
    char *p = new char[3];
    p[0] = 'e';
    p[1] = 'f';
    p[2] = 'g';
    cout << "functionD -> p = " << p[0] << p[1] << p[2] << endl;
    delete []p;
}

// C语言分配对象
void functionE() {
    // 这里不会自动调用类的构造函数和析构函数
    Teacher *p = (Teacher *) malloc(sizeof(Teacher));
    p->setAget(33);
    cout << "functionE -> age = " << p->getAge() << endl;
    free(p);
}

// C++分配对象
void functionF() {
    // new和delete会分别自动调用类的构造函数和析构函数
    Teacher *p = new Teacher(35);
    cout << "functionF -> age = " << p->getAge() << endl;
    delete p;
}

int main() {
    functionA();
    functionB();
    functionC();
    functionD();
    functionE();
    functionF();
    return 0;
}
