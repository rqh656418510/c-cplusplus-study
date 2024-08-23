/*
 * 1. 异常处理机制
 * a) C++ 标准异常库的使用
*/

#include <iostream>
#include <stdexcept>

using namespace std;

class Teacher {
public:
    Teacher(int age) {
        if (age > 100) {
            // 抛出标准库内的异常
            throw out_of_range("年龄太大");
        }
        this->age = age;
    }

private:
    int age;

};

// 继承标准库内的异常
class MyException : public exception {
public:
    MyException(const char* p) {
        this->m_p = p;
    }

    virtual const char* what() {
        cout << "MyException 类型的异常 : " << m_p << endl;
        return m_p;
    }

private:
    const char* m_p;
};

int main() {
    try {
        // Teacher teacher(105);
        throw MyException("发生自定义异常!");
    }
    catch (out_of_range e) {
        cout << "out_of_range 类型的异常 : " << e.what() << endl;
    }
    catch (MyException& e) {
        e.what();
    }
    catch (...) {
        cout << "发生未知类型的异常!" << endl;
    }
    return 0;
}