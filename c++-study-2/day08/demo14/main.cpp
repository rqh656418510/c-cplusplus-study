/**
 * 标准输入流案例
 */
#include <iostream>
#include <limits>

using namespace std;

/**
 * 案例一：判断用户输入的是字符串还是数字
 */
void test01() {
    cout << "请输入一串数字或字符串" << endl;
    char c = cin.peek();

    if (c >= '0' && c <= '9') {
        int num;
        cin >> num;
        cout << "你输入的是数字, 数字为：" << num << endl;
    } else {
        char buffer[1024];
        cin.get(buffer, 1024);
        cout << "你输入的是字符串, 字符串为：" << buffer << endl;
    }
}

/**
 * 案例二：让用户输入一个 1 到 10 的数字, 如果输入有误, 提示重新输入
 */
void test02() {
    int num;
    cout << "请输入一个 1 到 10 之间的数字：" << endl;

    while (true) {
        cin >> num;

        // 判断输入流的错误标志位, 0 - 正常的, 1 - 不正常的
        if (cin.fail()) {
            // 重置输入流的错误标志位
            cin.clear();
            // 在输入流中忽略（跳过）剩余的输入内容, 直到遇到换行符为止, 确保后续的输入操作是干净的, 不会受到之前无效输入的影响
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "输入无效，请输入一个数字" << endl;
        } else if (num >= 1 && num <= 10) {
            cout << "输入的数字为：" << num << endl;
            break;
        } else {
            cout << "数字不在范围内，请重新输入" << endl;
        }
    }
}

int main() {
    // test01();
    test02();
    return 0;
}
