/**
 * function的实现原理
 */

#include <iostream>
#include <functional>
#include <string>

using namespace std;

// 定义类模板
// 这里的 Fty 代表任意函数签名，如 R(ARG)
template<typename Fty>
class myfunction {

};

/**
 * @brief 模板类的特化，支持特定的函数签名 R(ARG)
 * @tparam R 代表返回值类型
 * @tparam ARG 代表参数类型
 */
template<typename R, typename ARG>
class myfunction<R(ARG)> {

public:
    // 定义函数指针类型，指向 R(ARG) 类型的函数
    using PFUNC = R(*)(ARG);

    // 构造函数，接收一个函数指针，并存储起来
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {

    }

    /**
     * @brief 重载小括号运算符，使对象可以像函数一样调用
     * @param arg 传递给存储函数的参数
     * @return 调用存储函数的返回值
    */
    R operator()(ARG arg) {
        return _pfunc(arg);
    }

private:
    // 存储函数指针
    PFUNC _pfunc;

};

void hello(string str) {
    cout << "hello " << str << endl;
}

int main() {
    // 创建 myfunction 对象，并绑定 hello 函数
    myfunction<void(string)> func1 = hello;

    // 通过 func1 调用 hello
    func1("peter");

    return 0;
}