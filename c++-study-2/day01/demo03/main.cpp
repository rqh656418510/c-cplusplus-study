/**
 * 1. 命名空间的使用，主要用于解决命名冲突的问题
 *
 * <p> 命名空间可以起别名
 * <p> 命名空间可以相互嵌套定义
 * <p> 命名空间必须定义在全局作用域下
 * <p> 命名空间内可以放常量、变量、函数、结构体、类等
 * <p> 命名空间是开放的，支持随时往原先的命名空间追加内容
 * <p> 在无名 / 匿名命名空间中定义变量，相当于使用了 `static` 关键字定义变量，如 `static int age;`
 */

#include "game1.h"
#include "game2.h"

int main() {
    game1::getAtk();
    game2::getAtk();

    // 命名空间可以起别名
    namespace game3 = game2;
    game3::getAtk();
}
