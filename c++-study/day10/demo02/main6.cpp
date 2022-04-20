/*
 * 1. 异常处理机制
 * a) 异常类型和异常变量的生命周期
*/

#include <iostream>

using namespace std;

class BadSrcType {
};

class BadDestType {
};

class BadProcessType {
public:
    BadProcessType() {
        cout << "BadProcessType的构造函数被调用" << endl;
    }


    BadProcessType(const BadProcessType& obj) {
        cout << "BadProcessType的拷贝构造函数被调用" << endl;
    }

    ~BadProcessType() {
        cout << "BadProcessType的析构函数被调用" << endl;
    }

};

void myStrcpy(char* to, char* from) {
    if (to == NULL) {
        throw BadDestType();
    }
    if (from == NULL) {
        throw BadSrcType();
    }

    if (*from == 'a') {
        throw BadProcessType();
    }
    if (*from == 'b') {
        // 不建议使用这种写法
        throw& (BadProcessType());
    }
    if (*from == 'c') {
        throw new BadProcessType;
    }

    while (*from != '\0') {
        *to = *from;
        to++;
        from++;
    }
    *to = '\0';
}

int main() {
    int ret = 0;
    char buf1[] = "cbbcdefg";
    char buf2[1024] = { 0 };

    try {
        myStrcpy(buf2, buf1);
    }
    catch (BadSrcType e) {
        cout << " BadSrcType 类型异常" << endl;
    }
    catch (BadDestType e) {
        cout << " BadDestType 类型异常" << endl;
    }
    /*
    // 结论1: 如果接收异常的时候，使用一个异常变量，则拷贝构造该异常变量
    catch (BadProcessType e)
    {
        cout << " BadProcessType 类型异常" << endl;
    }

    // 结论2: 如果接收异常的时候，使用了引用，则会使用throw时候的那个对象
    catch (BadProcessType& e)
    {
        cout << " BadProcessType 类型异常" << endl;
    }

    // 结论3: 接收异常的时候，指针可以和引用/元素同时出现，但是引用与元素不能同时出现
    catch (BadProcessType* e)
    {
        cout << " BadProcessType 类型异常" << endl;
        delete e;
    }

    // 结论4: 如果抛出的是类对象类型的异常，则使用引用进行异常捕获比较合适

    */
    catch (...) {
        cout << "未知 类型异常" << endl;
    }
    return 0;
}