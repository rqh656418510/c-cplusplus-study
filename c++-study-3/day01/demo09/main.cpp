/**
 * 掌握形参带默认值的函数
 *
 * <p> 形参设置默认值的时候，必须从右向左设置
 * <p> 形参是否设置默认值，对函数的调用效率会产生影响（底层生成的汇编指令会有差别）
 * <p> 函数定义时可以给形参设置默认值，函数声明时也可以给形参设置默认值
 * <p> 形参设置默认值的时候，不管是在函数定义处，还是在函数声明处，形参的默认值设置只能出现一次
 */

#include <iostream>

using namespace std;

// 函数的形参带默认值
int sum(int a = 30, int b = 40) {
    return a + b;
}

int main() {
    int a = 10;
    int b = 20;
    int result = a + b;
    cout << "result = " << result << endl;

    int result2 = sum(a);
    cout << "result2 = " << result2 << endl;

    int result3 = sum();
    cout << "result3 = " << result3 << endl;

    return 0;
}
