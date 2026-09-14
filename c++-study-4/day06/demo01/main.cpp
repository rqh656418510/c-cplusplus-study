/**
 * new、delete的进一步认识
 *
 * (a) 如果是一个空类，使用 `new` 创建对象时，加括号与不加括号没有任何区别
 */

#include <iostream>

class MyTest {};

int main() {
    // 加括号 ()
    MyTest* mt = new MyTest();
    // 不加括号 ()
    MyTest* mt2 = new MyTest;
    return 0;
}