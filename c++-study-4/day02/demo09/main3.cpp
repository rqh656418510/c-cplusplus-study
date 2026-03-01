/**
 * 友元函数、友元类、友元成员函数
 */

#include <iostream>
#include <memory>
#include <string>

using namespace std;

// 类前向声明
class Human;

// 先完整声明 Game 类
class Game {
public:
    Game(shared_ptr<Human> h);

    ~Game();

    void getHuman() const;

private:
    shared_ptr<Human> m_Human;
};

// 声明与定义 Human 类
class Human {
public:
    Human(const string& name, int age) : m_Name(name), m_Age(age) {
        cout << "Human::Human(string, int)" << endl;
    }

    ~Human() {
        cout << "Human::~Human()" << endl;
    }

private:
    int m_Age;
    string m_Name;

    // 声明友元成员函数
    friend void Game::getHuman() const;
};

/////////////// 定义 Game 类 ///////////////

Game::Game(shared_ptr<Human> h) : m_Human(h) {
    cout << "Game::Game()" << endl;
}

Game::~Game() {
    cout << "Game::~Game()" << endl;
}

void Game::getHuman() const {
    if (m_Human) {
        // 在友元成员函数中，可以访问其他类的私有成员变量或者私有成员函数
        cout << "name = " << m_Human->m_Name << ", age = " << m_Human->m_Age << endl;
    }
}

int main() {
    shared_ptr<Human> human = make_shared<Human>("Jim", 28);
    Game game(human);
    game.getHuman();
}