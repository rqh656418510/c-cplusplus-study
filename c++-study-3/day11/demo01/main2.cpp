/**
 * function类模板的应用示例
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
    // 通过 function 函数对象类型，调用类的成员函数
    Test t;
    function<void(Test*, string)> function1 = &Test::hello;
    function1(&t, "peter");
    function1(&Test(), "peter");    // 或者使用临时变量

    return 0;
}