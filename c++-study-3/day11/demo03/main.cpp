/**
 * bind和function实现线程池
 * 
 * <p> bind 是函数模板，可以自动推演模板类型参数
 * <p> bind 绑定器的返回结果是一个函数对象
 */

#include <iostream>
#include <functional>

using namespace std;

void hello(string str) {
    cout << str << endl;
}

int sum(int a, int b) {
    return a + b;
}

class Test {

public:
    int sum(int a, int b) {
        return a + b;
    }

};

int main() {
    // 例子一，绑定拥有一个参数的普通函数
    bind(hello, "Hello Bind!")();

    // 例子二，绑定拥有两个参数的普通函数
    int result1 = bind(sum, 3, 5)();
    cout << result1 << endl;

    // 例子三，调用类的成员函数
	int result2 = bind(&Test::sum, Test(), 5, 9)();
    cout << result2 << endl;

    // 例子四，使用参数占位符（最多可以有20个参数占位符）
    bind(hello, placeholders::_1)("Hello Rust!");

    // 例子五，使用 function 类模板实现 bind 绑定器的复用
    function<void(string)> func1 = bind(hello, placeholders::_1);
    func1("Hello Python");
    func1("Hello Golang");

    // 例子六，使用参数占位符 + function 类模板
    function<int(int)> func2 = bind(sum, 6, placeholders::_1);    // 绑定 6 作为第一个参数，第二个参数则手动传入
    int result3 = func2(5);     // 输出 11，相当于 sum(6, 5)
    cout << result3 << endl;

    return 0;
}