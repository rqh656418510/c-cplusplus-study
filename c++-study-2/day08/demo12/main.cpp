/**
 * 编写自己的异常类
 */
#include <iostream>
#include <stdexcept>

using namespace std;

// 继承自 C++ 的标准异常类
class MyOutOfRangeException : public exception {

public:
    explicit MyOutOfRangeException(const string &str) {
        this->m_Error = str.c_str();
    }

    virtual ~MyOutOfRangeException() {

    }

    virtual const char *what() {
        return this->m_Error;
    }

private:
    const char *m_Error;

};

class Person {

public:
    Person(string name, int age) {
        if (age < 0 || age > 150) {
            // 抛出自定义异常类
            throw MyOutOfRangeException("发生自定义异常：年龄超出范围");
        }

        this->m_Name = name;
        this->m_Age = age;
    }

private:
    string m_Name;
    int m_Age;

};

int main() {
    try {
        Person person("Tom", 200);
    }
    catch (MyOutOfRangeException &e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "发生未知类型的异常!" << endl;
    }

    return 0;
}
