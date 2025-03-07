/**
 * function函数对象类型的应用示例
 */

#include <iostream>
#include <functional>
#include <string>

using namespace std;

void hello1() {
    cout << "hello world" << endl;
}

void hello2(string str) {
	cout << "hello " << str << endl;
}

int sum(int a, int b) {
	return a + b;
}

int main() {
    // function 函数对象类型
    function<void()> function1 = hello1;
    function1();

    function<void(string)> function2 = hello2;
    function2("peter");

    function<int(int, int)> function3 = sum;
    int total = function3(1, 2);
    cout << "total = " << total << endl;

    // function 函数对象类型 + Lambda 表达式
    function<int(int, int)> function4 = [](int a, int b) {return a + b; };
    int total2 = function4(3, 5);
    cout << "total2 = " << total2 << endl;

    return 0;
}
