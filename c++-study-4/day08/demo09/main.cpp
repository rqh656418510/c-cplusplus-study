/**
 * Lambda 表达式捕获模式的陷阱分析和展示
 *
 * (a) Lambda 表达式使用陷阱 - 悬垂引用问题
 */

#include <ctime>
#include <functional>
#include <iostream>
#include <vector>

std::vector<std::function<bool(int)>> vec;

void process() {
    srand(static_cast<unsigned>(time(nullptr)));
    int rand_num = rand() % 6;

    // 按引用捕获，存在未定义行为（悬垂引用）
    vec.push_back([&](const int val) {
        return val % rand_num == 0;
    });
}

int main() {
    process();
    int result = vec[0](5);
    std::cout << result << std::endl;
    return 0;
}