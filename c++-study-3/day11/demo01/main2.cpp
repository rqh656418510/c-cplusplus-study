/**
 * function��ģ���Ӧ��ʾ��
 */

#include <iostream>
#include <functional>
#include <string>

using namespace std;

class Test {

public:

    void hello(string str) {
        cout << "hello " << str << endl;
    }

};

int main() {
    // ͨ�� function �����������ͣ�������ĳ�Ա����
    Test t;
    function<void(Test*, string)> function1 = &Test::hello;
    function1(&t, "peter");
    function1(&Test(), "peter");    // ����ʹ����ʱ����

    return 0;
}