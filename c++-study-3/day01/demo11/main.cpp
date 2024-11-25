/**
 * 详解函数重载
 *
 * <p> 一组函数，其中函数名相同，参数列表的个数、类型、顺序不同，那么这一组函数就称为 - 函数重载。
 * <p> 特别注意，一组函数要称得上是函数重载，那么这组函数必须是处于同一个作用域当中的。
 */

#include <iostream>
#include <cstring>

using namespace std;

bool compare(int a, int b) {
    cout << "compare_int_int" << endl;
    return a > b;
}

bool compare(double a, double b) {
    cout << "compare_double_double" << endl;
    return a > b;
}

bool compare(const char *a, const char *b) {
    cout << "compare_char*_char*" << endl;
    return strcmp(a, b) > 0;
}

int main() {
    compare(10, 20);
    compare(3.4, 2.4);
    compare("abc", "efd");
    return 0;
}
