/**
 * 类对象作为类成员的案例
 * <p> 当类中有成员变量是其它类的对象时，首先调用成员变量的构造函数，调用顺序与声明顺序相同，之后再调用类自身的构造函数
 * <p> 析构函数的调用顺序与对应的构造函数调用顺序相反
 */

#include <iostream>
#include <string>

using namespace std;

class Phone {

public:

    Phone() {
        cout << "手机的无参构造函数被调用" << endl;
    }

    Phone(string &number) : m_number(number) {
        cout << "手机的有参构造函数被调用" << endl;
    }

    ~Phone() {
        cout << "手机的析构函数被调用" << endl;
    }

    const string &getNumber() const {
        return m_number;
    }

    void setNumber(const string &mNumber) {
        m_number = mNumber;
    }

private:
    string m_number;

};

class Game {

public:

    Game() {
        cout << "游戏的无参构造函数被调用" << endl;
    }

    Game(string &name) : m_name(name) {
        cout << "游戏的有参构造函数被调用" << endl;
    }

    ~Game() {
        cout << "游戏的析构函数被调用" << endl;
    }

    const string &getName() const {
        return m_name;
    }

    void setName(const string &mName) {
        m_name = mName;
    }

private:
    string m_name;

};

class Student {

public:

    Student() {
        cout << "学生的无参构造函数被调用" << endl;
    }

    Student(string &name) : m_name(name) {
        cout << "学生的有参构造函数被调用" << endl;
    }

    Student(string &name, string &phone, string &gameName) : m_name(name), m_phone(phone), m_game(gameName) {
        cout << "学生的有参构造函数被调用" << endl;
    }

    ~Student() {
        cout << "学生的析构函数被调用" << endl;
    }

    const string &getName() const {
        return m_name;
    }

    void setName(const string &mName) {
        m_name = mName;
    }

    const Phone &getPhone() const {
        return m_phone;
    }

    const Game &getGame() const {
        return m_game;
    }

private:
    string m_name;
    Phone m_phone;
    Game m_game;
};

void test01() {
    Student s;
}

void test02() {
    string name = "Jim";
    string phone = "110";
    string gameName = "LOL";
    Student s(name, phone, gameName);
}

int main() {
    cout << "-------- test01() --------" << endl;
    test01();

    cout << "-------- test02() --------" << endl;
    test02();

    return 0;
}
