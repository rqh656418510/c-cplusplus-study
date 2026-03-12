/**
 * 临时对象深入探讨、解析，提高性能手段
 */

#include <iostream>

// 统计某个字符在字符串中出现的次数
int calc(const std::string& str, char ch) {
    int count = 0;
    for (const char& c : str) {
        if (ch == c) {
            count++;
        }
    }
    return count;
}

int main() {
    char str[50] = "I Love China, Yeah!";

    // 隐式类型转换（char[] 转 string）以保证函数调用成功，这里会产生 string 临时对象
    int count = calc(str, 'a');
    std::cout << "count = " << count << std::endl;

    // 优化后的写法，不使用隐式类型转换，不会产生 string 临时对象，性能更高
    std::string str2 = "I Love China, Yeah!";
    int count2 = calc(str, 'a');
    std::cout << "count2 = " << count2 << std::endl;

    return 0;
}