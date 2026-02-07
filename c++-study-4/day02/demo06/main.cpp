/**
 * 重载运算符、析构函数
 */

#include <iostream>

using namespace std;

class Time {
public:
    // 无参构造函数
    Time() : m_hour(0), m_minute(0), m_second(0) {
        cout << "Time()" << endl;
    }

    // 有参构造函数
    Time(int hour, int minute, int second) : m_hour(hour), m_minute(minute), m_second(second) {
        cout << "Time(int, int, int)" << endl;
    }

    // 析构函数
    ~Time() {
        cout << "~Time()" << endl;
    }

    // 重载 = 运算符（成员函数方式）
    Time& operator=(const Time& t) {
        m_hour = t.m_hour;
        m_minute = t.m_minute;
        m_second = t.m_second;
        return *this;
    }

    // 重载 == 运算符（成员函数方式）
    bool operator==(const Time& t) const {
        return m_hour == t.m_hour && m_minute == t.m_minute && m_second == t.m_second;
    }

    void time() const {
        cout << m_hour << ":" << m_minute << ":" << m_second << endl;
    }

private:
    int m_hour;
    int m_minute;
    int m_second;
};

// 重载 != 运算符（非成员函数方式）
bool operator!=(const Time& a, const Time& b) {
    return !(a == b);
}

void test01() {
    Time t1(20, 42, 15);
    t1.time();

    Time t2;
    t2 = t1;

    cout << (t1 == t2) << endl;
    cout << (t1 != t2) << endl;
}

int main() {
    test01();
    return 0;
}