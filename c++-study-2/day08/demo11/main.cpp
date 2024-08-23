/**
 * 使用系统标准异常
 */
#include <iostream>
#include <stdexcept>

using namespace std;

class Person {

public:
    Person(string name, int age) {
        if (age < 0 || age > 150) {
            // 抛出 C++ 的标准异常类
            throw out_of_range("年龄超出范围");
        }

        if (name.length() <= 0 || name.length() > 32) {
            throw length_error("姓名长度错误");
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
    catch (out_of_range &e) {
        cout << e.what() << endl;
    }
    catch (length_error &e) {
        cout << e.what() << endl;
    }
    catch (...) {
        cout << "发生未知类型的异常!" << endl;
    }

    return 0;
}
