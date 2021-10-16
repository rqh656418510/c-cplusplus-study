/**
 * 1. 计算圆形的面积，采用面向过程的编程方式
 */

#include <iostream>

using namespace std;

int main() {
    double r = 0; // 圆形的半径
    double s = 0; // 圆形的面积

    cout << "请输入圆形的半径：";
    cin >> r;
    s = 3.14 * r * r;
    cout << "圆形的面积是：" << s << endl;

    return 0;
}