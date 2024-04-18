/**
 * 继承方式
 */
#include <iostream>

using namespace std;

class Base {

public:
    int m_A;

protected:
    int m_B;

private:
    int m_C;

};

class Son1 : public Base {

public:
    void func() {
        cout << m_A << endl;        // public 继承，父类成员在子类中保持原有的访问级别
        cout << m_B << endl;        // public 继承，父类成员在子类中保持原有的访问级别
        // cout << m_C << endl;     // public 继承，无法访问父类的 private 成员
    }

};

class Son2 : protected Base {

public:
    void func() {
        cout << m_A << endl;        // protected 继承，父类中 public 成员会变成 protected 成员
        cout << m_B << endl;        // protected 继承，父类中 protected 成员仍然为 protected 成员
        // cout << m_C << endl;     // protected 继承，无法访问父类的 private 成员
    }

};

class Son3 : private Base {

public:
    void func() {
        cout << m_A << endl;        // private 继承，父类成员在子类中都变为 private 成员
        cout << m_B << endl;        // private 继承，父类成员在子类中都变为 private 成员
        // cout << m_C << endl;     // private 继承，无法访问父类的 private 成员
    }

};

int main() {
    return 0;
}
