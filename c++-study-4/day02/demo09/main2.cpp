/*
 * 友元函数、友元类、友元成员函数
 */

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Human {
public:
    Human() {
        cout << "Human::Human()" << endl;
    }

    Human(const string& name, int age) : m_Name(name), m_Age(age) {
        cout << "Human::Human(string, int)" << endl;
    }

    ~Human() {
        cout << "Human::~Human()" << endl;
    }

    void eat() const {
        cout << m_Name << "Human eat food" << endl;
    }

public:
    // 声明友元类
    friend class Game;

private:
    int m_Age;
    string m_Name;
};

class Game {
public:
    explicit Game(shared_ptr<Human> h) : m_Human(std::move(h)) {
        cout << "Game::Game()" << endl;
    }

    ~Game() {
        cout << "Game::~Game()" << endl;
    }

    void getHuman() const {
        if (m_Human) {
            // 在友元类中，可以访问其他类的私有成员变量或者私有成员函数
            cout << "name = " << m_Human->m_Name << ", age = " << m_Human->m_Age << endl;
        }
    }

private:
    shared_ptr<Human> m_Human;
};

int main() {
    shared_ptr<Human> human = make_shared<Human>("Jim", 28);
    Game game(human);
    game.getHuman();
    return 0;
}