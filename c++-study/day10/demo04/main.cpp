/*
 * 1. �쳣�������
 * a) C++ ��׼�쳣���ʹ��
*/

#include <iostream>

using namespace std;

class Teacher {
public:
    Teacher(int age) {
        if (age > 100) {
            // �׳���׼���ڵ��쳣
            throw out_of_range("����̫��");
        }
        this->age = age;
    }

private:
    int age;

};

// �̳б�׼���ڵ��쳣
class MyException : public exception {
public:
    MyException(const char* p) {
        this->m_p = p;
    }

    virtual const char* what() {
        cout << "MyException ���͵��쳣 : " << m_p << endl;
        return m_p;
    }

private:
    const char* m_p;
};

int main() {
    try {
        // Teacher teacher(105);
        throw MyException("�����Զ����쳣!");
    }
    catch (out_of_range e) {
        cout << "out_of_range ���͵��쳣 : " << e.what() << endl;
    }
    catch (MyException& e) {
        e.what();
    }
    catch (...) {
        cout << "����δ֪���͵��쳣!" << endl;
    }
    return 0;
}